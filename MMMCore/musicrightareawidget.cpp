#include "musicrightareawidget.h"
#include "ui_musicapplication.h"
#include "musicapplication.h"
#include "musicuiobject.h"
#include "musiclrccontainerfordesktop.h"
#include "musicvideoplaywidget.h"
#include "musicdownloadstatuslabel.h"
#include "musicsettingwidget.h"
#include "musicmessagebox.h"
#include "musicsimilarfoundwidget.h"
#include "musicsongsearchonlinewidget.h"
#include "musicMMMuiobject.h"

#include "kugouwindow.h"

#include <QPropertyAnimation>

MusicRightAreaWidget *MusicRightAreaWidget::m_instance = nullptr;

MusicRightAreaWidget::MusicRightAreaWidget(QWidget *parent)
    : QWidget(parent)
{
    m_instance = this;
    m_stackedFuncWidget = nullptr;

    m_musiclrcfordesktop = new MusicLrcContainerForDesktop(parent);
    m_downloadStatusLabel = new MusicDownloadStatusLabel(parent);
    m_setting = new MusicSettingWidget(this);
    connect(m_setting, SIGNAL(parameterSettingChanged()), parent,
                       SLOT(getParameterSetting()));
    connect(m_setting, SIGNAL(soundEqualizerClicked()), parent,
                       SLOT(musicSetEqualizer()));
}

MusicRightAreaWidget::~MusicRightAreaWidget()
{
    delete m_setting;
    delete m_downloadStatusLabel;
    delete m_musiclrcfordesktop;
}

QString MusicRightAreaWidget::getClassName()
{
    return staticMetaObject.className();
}

MusicRightAreaWidget *MusicRightAreaWidget::instance()
{
    return m_instance;
}

void MusicRightAreaWidget::setupUi(Ui::MusicApplication* ui)
{
    m_ui = ui;
    ui->musiclrccontainerforinline->resize(ui->surfaceStackedWidget->size());

    ui->lrcDisplayAllButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->lrcDisplayAllButton->setIconSize(QSize(15, 56));
    connect(ui->lrcDisplayAllButton, SIGNAL(clicked()), SLOT(musicLrcDisplayAllButtonClicked()));
    ///////////////////////////////////////////////////////

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->musicSongWidgetButton, 0);
    group->addButton(ui->musicRadioWidgetButton, 1);
    group->addButton(ui->musicListWidgetButton, 2);
    group->addButton(ui->musicVideoWidgetButton, 3);
    group->addButton(ui->musicLiveWidgetButton, 4);
    group->addButton(ui->musicLrcWidgetButton, 5);
    group->addButton(ui->musicSearchButton, 6);
    group->addButton(ui->musicSearchRefreshButton, 6);
    connect(group, SIGNAL(buttonClicked(int)), SLOT(musicFunctionClicked(int)));

    ///////////////////////////////////////////////////////
    connect(m_musiclrcfordesktop, SIGNAL(theCurrentLrcUpdated()), MusicApplication::instance(),
                 SLOT(musicCurrentLrcUpdated()));
    connect(m_musiclrcfordesktop, SIGNAL(changeCurrentLrcColorSetting()), MusicApplication::instance(),
                 SLOT(musicSetting()));
    connect(m_musiclrcfordesktop, SIGNAL(changeCurrentLrcColorCustom()), m_setting,
                 SLOT(changeDesktopLrcWidget()));
    connect(m_musiclrcfordesktop, SIGNAL(desktopLrcClosed()), SIGNAL(desktopLrcClosed()));
    connect(m_musiclrcfordesktop, SIGNAL(setWindowLockedChanged(bool)), SIGNAL(lockDesktopLrc(bool)));
    ///////////////////////////////////////////////////////
    connect(ui->musiclrccontainerforinline, SIGNAL(changeCurrentLrcColorCustom()), m_setting,
                 SLOT(changeInlineLrcWidget()));
    connect(ui->musiclrccontainerforinline, SIGNAL(theCurrentLrcUpdated()), MusicApplication::instance(),
                 SLOT(musicCurrentLrcUpdated()));
    connect(ui->musiclrccontainerforinline, SIGNAL(theArtBgHasChanged()),
                 SIGNAL(updateBgThemeDownload()));
    connect(ui->musiclrccontainerforinline, SIGNAL(changeCurrentLrcColorSetting()), MusicApplication::instance(),
                 SLOT(musicSetting()));
    connect(ui->musiclrccontainerforinline, SIGNAL(updateCurrentTime(qint64)), MusicApplication::instance(),
                 SLOT(updateCurrentTime(qint64)));
    connect(ui->musicSongSearchLine, SIGNAL(enterFinished(QString)),
                 SLOT(songResearchButtonSearched(QString)));
    ///////////////////////////////////////////////////////
    connect(ui->musicMoreFunction, SIGNAL(musicSimilarFound(QString)), SLOT(musicSimilarFound(QString)));
    connect(ui->musicMoreFunction, SIGNAL(musicSongMovieClicked(QString)), SLOT(musicVideoButtonSearched(QString)));
    ///////////////////////////////////////////////////////
    QTimer::singleShot(MT_MS, this, SLOT(musicLoadSongIndexWidget()));
}

void MusicRightAreaWidget::stopLrcMask() const
{
    if( checkSettingParameterValue() )
    {
       m_ui->musiclrccontainerforinline->stopLrcMask();
       m_musiclrcfordesktop->stopLrcMask();
    }
}

void MusicRightAreaWidget::startTimerClock() const
{
    if( checkSettingParameterValue() )
    {
       m_ui->musiclrccontainerforinline->startTimerClock();
       m_musiclrcfordesktop->startTimerClock();
    }
}

void MusicRightAreaWidget::showPlayStatus(bool status) const
{
    m_musiclrcfordesktop->showPlayStatus(status);
}

bool MusicRightAreaWidget::getDestopLrcVisible() const
{
    return m_musiclrcfordesktop->isVisible();
}

void MusicRightAreaWidget::setInlineLrcVisible(bool status) const
{
    m_ui->musiclrccontainerforinline->setVisible(status);
}

bool MusicRightAreaWidget::getInlineLrcVisible() const
{
    return m_ui->musiclrccontainerforinline->isVisible();
}

void MusicRightAreaWidget::setSettingParameter() const
{
    m_musiclrcfordesktop->setSettingParameter();
    m_ui->musiclrccontainerforinline->setSettingParameter();
}

bool MusicRightAreaWidget::checkSettingParameterValue() const
{
    return ( M_SETTING_PTR->value(MusicSettingManager::ShowInlineLrcChoiced).toBool() ||
             M_SETTING_PTR->value(MusicSettingManager::ShowDesktopLrcChoiced).toBool() );
}

void MusicRightAreaWidget::updateCurrentLrc(qint64 current, qint64 total, bool playStatus) const
{
    m_ui->musiclrccontainerforinline->setCurrentTime(current);
    //Direct access to the audio file is the total time, in milliseconds
    QString currentLrc, laterLrc;
    qint64 intervalTime;
    if(m_ui->musiclrccontainerforinline->findText(total, currentLrc, laterLrc, intervalTime))
    {   //If this is a new line of the lyrics, then restart lyrics display mask
        if(currentLrc != m_ui->musiclrccontainerforinline->text())
        {
            if(!playStatus)
            {
                m_ui->musiclrccontainerforinline->updateCurrentLrc(intervalTime);
            }
            m_musiclrcfordesktop->setCurrentTime(intervalTime);
            m_musiclrcfordesktop->updateCurrentLrc(currentLrc, laterLrc, intervalTime);
        }
    }
}

void MusicRightAreaWidget::loadCurrentSongLrc(const QString &name, const QString &path) const
{
    if( checkSettingParameterValue() )
    {
        m_ui->musiclrccontainerforinline->stopLrcMask();
        m_ui->musiclrccontainerforinline->setCurrentSongName( name );

        m_musiclrcfordesktop->stopLrcMask();
        m_musiclrcfordesktop->setCurrentSongName( name );

        if(!m_ui->musiclrccontainerforinline->transLyricFileToTime( path ))
        {
            m_musiclrcfordesktop->updateCurrentLrc(tr("unFoundLrc"), QString(), 0);
        }
    }
}

void MusicRightAreaWidget::setSongSpeedAndSlow(qint64 time) const
{
    m_ui->musiclrccontainerforinline->setSongSpeedAndSlow(time);
}

void MusicRightAreaWidget::musicCheckHasLrcAlready() const
{
    m_downloadStatusLabel->musicCheckHasLrcAlready();
}

void MusicRightAreaWidget::showSettingWidget() const
{
    m_setting->initControllerParameter();
    m_setting->exec();
}

void MusicRightAreaWidget::getParameterSetting() const
{
    setSettingParameter();
    bool config = M_SETTING_PTR->value(MusicSettingManager::ShowInlineLrcChoiced).toBool();
    m_ui->musiclrccontainerforinline->setVisible(config);
         config = M_SETTING_PTR->value(MusicSettingManager::ShowDesktopLrcChoiced).toBool();
    m_musiclrcfordesktop->setVisible(config);
    m_ui->musicDesktopLrc->setChecked(config);
}

void MusicRightAreaWidget::musicFunctionClicked(int index)
{
    if(index == 5) ///lrc option
    {
        musicButtonStyleClear(false);
        m_ui->stackedFunctionWidget->setStyleSheet(QString("#stackedFunctionWidget{%1}").arg(MusicUIObject::MBackgroundStyle01));
        m_ui->musicSearchBackButton->setStyleSheet(MusicUIObject::MKGBtnBackBack);
        m_ui->musicSearchRefreshButton->setStyleSheet(MusicUIObject::MKGBtnBackFresh);
    }
    else
    {
        musicButtonStyleClear(true);
        m_ui->stackedFunctionWidget->setStyleSheet(QString("#stackedFunctionWidget{%1}").arg(MusicUIObject::MBackgroundStyle17));
        m_ui->musicSearchBackButton->setStyleSheet(MusicUIObject::MKGBtnForeBack);
        m_ui->musicSearchRefreshButton->setStyleSheet(MusicUIObject::MKGBtnForeFresh);
    }

    deleteStackedFuncWidget();
    m_ui->lrcDisplayAllButton->setVisible(false);
    if(m_ui->musiclrccontainerforinline->lrcDisplayExpand())
    {
        musicLrcDisplayAllButtonClicked();
    }

    switch(index)
    {
        case 0: //insert kugou song widget
            {
                m_stackedFuncWidget = new KugouWindow(KugouWindow::KuGouSong, this);
                m_ui->surfaceStackedWidget->addWidget(m_stackedFuncWidget);
                m_ui->surfaceStackedWidget->setCurrentWidget(m_stackedFuncWidget);
                m_ui->musicSongWidgetButton->setStyleSheet(MusicUIObject::MKGFuncSongForeClicked);
                emit updateBackgroundTheme();
                break;
            }
        case 1: //insert kugou radio widget
            {
                m_stackedFuncWidget = new KugouWindow(KugouWindow::KuGouRadio, this);
                m_ui->surfaceStackedWidget->addWidget(m_stackedFuncWidget);
                m_ui->surfaceStackedWidget->setCurrentWidget(m_stackedFuncWidget);
                m_ui->musicRadioWidgetButton->setStyleSheet(MusicUIObject::MKGFuncRadioForeClicked);
                emit updateBackgroundTheme();
                break;
            }
        case 2: //insert kugou list widget
            {
                m_stackedFuncWidget = new KugouWindow(KugouWindow::KuGouList, this);
                m_ui->surfaceStackedWidget->addWidget(m_stackedFuncWidget);
                m_ui->surfaceStackedWidget->setCurrentWidget(m_stackedFuncWidget);
                m_ui->musicListWidgetButton->setStyleSheet(MusicUIObject::MKGFuncListForeClicked);
                emit updateBackgroundTheme();
                break;
            }
        case 3: //insert video widget
            {
                MusicVideoPlayWidget *videoPlayer = new MusicVideoPlayWidget(false);
                videoPlayer->setObjectToClose(this);
                videoPlayer->blockMoveOption(true);
                connect(videoPlayer, SIGNAL(freshButtonClicked(bool)), SLOT(musicVideoSetPopup(bool)));
                connect(videoPlayer, SIGNAL(fullscreenButtonClicked(bool)), SLOT(musicVideoFullscreen(bool)));

                m_stackedFuncWidget = videoPlayer;
                m_ui->surfaceStackedWidget->addWidget(m_stackedFuncWidget);
                m_ui->surfaceStackedWidget->setCurrentWidget(m_stackedFuncWidget);
                m_ui->musicVideoWidgetButton->setStyleSheet(MusicUIObject::MKGFuncMVForeClicked);
                emit updateBackgroundTheme();
                break;
            }
        case 4: //insert kugou live widget
            {
                m_stackedFuncWidget = new KugouWindow(KugouWindow::KugouMv, this);
                m_ui->surfaceStackedWidget->addWidget(m_stackedFuncWidget);
                m_ui->surfaceStackedWidget->setCurrentWidget(m_stackedFuncWidget);
                m_ui->musicLiveWidgetButton->setStyleSheet(MusicUIObject::MKGFuncLiveForeClicked);
                emit updateBackgroundTheme();
                break;
            }
        case 5: //insert lrc display widget
            {
                m_ui->musicLrcWidgetButton->setStyleSheet(MusicUIObject::MKGFuncLrcForeClicked);

                m_ui->surfaceStackedWidget->setCurrentIndex(1);
                m_ui->lrcDisplayAllButton->setStyleSheet(MusicUIObject::MKGTinyBtnLrcCollapse);
                m_ui->lrcDisplayAllButton->setVisible(true);
                emit updateBgThemeDownload();
                break;
            }
        case 6: //insert search display widget
            {
                QString searchedQString = m_ui->musicSongSearchLine->text().trimmed();
                m_ui->surfaceStackedWidget->setCurrentIndex(0);
                emit updateBackgroundTheme();
                //The string searched wouldn't allow to be none
                if( !searchedQString.isEmpty() && searchedQString != tr("please input search text") )
                {
                    m_ui->songSearchWidget->startSearchQuery(searchedQString);
                }
                else
                {
                    MusicMessageBox message;
                    message.setText(tr("enter input search text first"));
                    message.exec();
                }
                break;
            }
        case 7: //insert similar found widget
            {
                MusicSimilarFoundWidget *similarFoundWidget = new MusicSimilarFoundWidget(this);
                m_ui->surfaceStackedWidget->addWidget(similarFoundWidget);
                m_ui->surfaceStackedWidget->setCurrentWidget(similarFoundWidget);
//                similarFoundWidget->setSongName(m_ui->showCurrentSong->text().trimmed());
                m_stackedFuncWidget = similarFoundWidget;
                emit updateBackgroundTheme();
                break;
            }
        default: break;
    }
}

void MusicRightAreaWidget::musicSimilarFound(const QString &text)
{
    musicFunctionClicked(7);
    MStatic_cast(MusicSimilarFoundWidget*, m_stackedFuncWidget)->setSongName(text);
}

void MusicRightAreaWidget::musicLoadSongIndexWidget()
{
    musicFunctionClicked(0);
}

void MusicRightAreaWidget::deleteStackedFuncWidget()
{
    delete m_stackedFuncWidget;
    m_stackedFuncWidget = nullptr;
}

void MusicRightAreaWidget::setDestopLrcVisible(bool visible) const
{
    m_ui->musicDesktopLrc->setChecked(visible);
    m_musiclrcfordesktop->setVisible(visible);
    m_musiclrcfordesktop->initCurrentLrc();
    M_SETTING_PTR->setValue(MusicSettingManager::ShowDesktopLrcChoiced, visible);
}

void MusicRightAreaWidget::setWindowLockedChanged()
{
    m_musiclrcfordesktop->setWindowLockedChanged();
}

void MusicRightAreaWidget::songResearchButtonSearched(const QString &name)
{
    m_ui->musicSongSearchLine->setText(name.trimmed());
    musicFunctionClicked(6);
}

void MusicRightAreaWidget::researchQueryByQuality(const QString &quality)
{
    m_ui->songSearchWidget->researchQueryByQuality(m_ui->showCurrentSong->text().trimmed(), quality);
    m_ui->surfaceStackedWidget->setCurrentIndex(0);
    emit updateBackgroundTheme();
}

void MusicRightAreaWidget::musicButtonStyleClear(bool fore)
{
    m_ui->musicSongWidgetButton->setStyleSheet(fore ? MusicUIObject::MKGFuncSongFore :
                                                      MusicUIObject::MKGFuncSongBack);
    m_ui->musicRadioWidgetButton->setStyleSheet(fore ?MusicUIObject::MKGFuncRadioFore :
                                                      MusicUIObject::MKGFuncRadioBack);
    m_ui->musicListWidgetButton->setStyleSheet(fore ? MusicUIObject::MKGFuncListFore :
                                                      MusicUIObject::MKGFuncListBack);
    m_ui->musicVideoWidgetButton->setStyleSheet(fore ? MusicUIObject::MKGFuncMVFore :
                                                       MusicUIObject::MKGFuncMVBack);
    m_ui->musicLiveWidgetButton->setStyleSheet(fore ? MusicUIObject::MKGFuncLiveFore :
                                                      MusicUIObject::MKGFuncLiveBack);
    m_ui->musicLrcWidgetButton->setStyleSheet(MusicUIObject::MKGFuncLrcFore);
}

void MusicRightAreaWidget::musicVideoButtonSearched(const QString &name)
{
    if(MObject_cast(MusicVideoPlayWidget*, m_stackedFuncWidget))
    {
        MusicVideoPlayWidget *video = MStatic_cast(MusicVideoPlayWidget*, m_stackedFuncWidget);
        if(video->isPopup())
        {
            video->raise();
            video->videoResearchButtonSearched(name);
            return;
        }
    }
    musicFunctionClicked(3);
    MusicVideoPlayWidget *video = MStatic_cast(MusicVideoPlayWidget*, m_stackedFuncWidget);
    if(video)
    {
        video->videoResearchButtonSearched(name);
    }
}

void MusicRightAreaWidget::musicVideoSetPopup(bool popup)
{
    if(popup)
    {
        musicFunctionClicked(5);

        MusicVideoPlayWidget *videoPlayer = new MusicVideoPlayWidget(true);
        videoPlayer->setObjectToClose(this);
        videoPlayer->show();
        m_stackedFuncWidget = videoPlayer;
        connect(videoPlayer, SIGNAL(freshButtonClicked(bool)), SLOT(musicVideoSetPopup(bool)));
        connect(videoPlayer, SIGNAL(fullscreenButtonClicked(bool)), SLOT(musicVideoFullscreen(bool)));
    }
    else
    {
        musicFunctionClicked(3);
    }
}

void MusicRightAreaWidget::musicVideoFullscreen(bool full)
{
    MusicVideoPlayWidget *video = MStatic_cast(MusicVideoPlayWidget*, m_stackedFuncWidget);
    if(video)
    {
        video->resizeWindow(full);
        video->blockMoveOption(full);
    }
}

void MusicRightAreaWidget::musicLrcDisplayAllButtonClicked()
{
    bool lrcDisplayAll = !m_ui->musiclrccontainerforinline->lrcDisplayExpand();
    m_ui->musiclrccontainerforinline->setLrcDisplayExpand(lrcDisplayAll);
    m_ui->songsContainer->setHidden(lrcDisplayAll);

    int height = M_SETTING_PTR->value(MusicSettingManager::WidgetSize).toSize().height() - WINDOW_HEIGHT_MIN;

    QPropertyAnimation *lrcDisplayAllAnimation = new QPropertyAnimation(m_ui->lrcDisplayAllButton, "pos", this);
    lrcDisplayAllAnimation->setDuration(100);
    lrcDisplayAllAnimation->setStartValue(QPoint(lrcDisplayAll ? 350 : -370, 220 + height/2));
    lrcDisplayAllAnimation->setEndValue(QPoint(0, 220 + height/2));
    lrcDisplayAllAnimation->start();

    m_ui->lrcDisplayAllButton->setStyleSheet(lrcDisplayAll ? MusicUIObject::MKGTinyBtnLrcExpand :
                                                             MusicUIObject::MKGTinyBtnLrcCollapse);
    m_ui->musicWindowConcise->setEnabled(!lrcDisplayAll);
}
