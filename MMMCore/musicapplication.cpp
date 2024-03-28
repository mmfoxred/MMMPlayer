#include "musicapplication.h"
#include "ui_musicapplication.h"
#include "musicsongsearchonlinewidget.h"
#include "musicsongssummarizied.h"
#include "musicxmlconfigmanager.h"
#include "musicplayer.h"
#include "musicplaylist.h"
#include "musicbackgroundmanager.h"
#include "musicsettingmanager.h"
#include "musicversion.h"
#include "musicuiobject.h"
#include "musicmessagebox.h"
#include "musictime.h"
#include "musicbottomareawidget.h"
#include "musictopareawidget.h"
#include "musicrightareawidget.h"
#include "musicleftareawidget.h"
#include "musicapplicationobject.h"
#include "musicglobalhotkey.h"
#include "musicMMMuiobject.h"
#include "musictoastlabel.h"

MusicApplication *MusicApplication::m_instance = nullptr;

MusicApplication::MusicApplication(QWidget *parent)
    : MusicAbstractMoveResizeWidget(parent),
      ui(new Ui::MusicApplication)
{
    m_instance = this;
    m_applicationObject = new MusicApplicationObject(this);
    ////////////////////////////////////////////////
    ui->setupUi(this);

    m_musicPlayer = new MusicPlayer(this);
    m_musicList = new MusicPlaylist(this);
    m_musicSongTree = new MusicSongsSummarizied(this);
    ui->songsContainer->addWidget(m_musicSongTree);

    m_bottomAreaWidget = new MusicBottomAreaWidget(this);
    m_bottomAreaWidget->setupUi(ui);
    m_topAreaWidget = new MusicTopAreaWidget(this);
    m_topAreaWidget->setupUi(ui);
    m_rightAreaWidget = new MusicRightAreaWidget(this);
    m_rightAreaWidget->setupUi(ui);
    m_leftAreaWidget = new MusicLeftAreaWidget(this);
    m_leftAreaWidget->setupUi(ui);
    connect(m_topAreaWidget, SIGNAL(setTransparent(int)), m_musicSongTree, SLOT(setTransparent(int)));
    connect(m_rightAreaWidget, SIGNAL(updateBgThemeDownload()), m_topAreaWidget, SLOT(musicBgThemeDownloadFinished()));
    connect(m_rightAreaWidget, SIGNAL(updateBackgroundTheme()), m_topAreaWidget, SLOT(musicBgTransparentChanged()));
    connect(m_bottomAreaWidget, SIGNAL(setShowDesktopLrc(bool)), m_rightAreaWidget, SLOT(setDestopLrcVisible(bool)));
    connect(m_bottomAreaWidget, SIGNAL(setWindowLockedChanged()), m_rightAreaWidget, SLOT(setWindowLockedChanged()));
    connect(m_rightAreaWidget, SIGNAL(lockDesktopLrc(bool)), m_bottomAreaWidget, SLOT(lockDesktopLrc(bool)));
    connect(m_rightAreaWidget, SIGNAL(desktopLrcClosed()), m_bottomAreaWidget, SLOT(desktopLrcClosed()));

    setAcceptDrops(true);

    m_musicList->setPlaybackMode(MusicObject::MC_PlayOrder);
    ui->musicPlayMode->initWidget(this);
    //The default is the order of play

    m_musicPlayer->setPlaylist(m_musicList);
    m_musicPlayer->setVolume(100);
    //The default Volume is 100

    m_playControl = true;//The default in the suspended state
    m_currentMusicSongTreeIndex = -1;

    connect(m_musicPlayer, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(m_musicPlayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(m_musicPlayer, SIGNAL(stateChanged(MusicPlayer::State)), SLOT(stateChanged()));
    connect(m_musicList, SIGNAL(currentIndexChanged(int)), SLOT(showCurrentSong(int)));
    connect(m_musicList, SIGNAL(currentIndexChanged(int)), m_musicSongTree, SLOT(setMusicPlayCount(int)));

    connect(m_musicSongTree, SIGNAL(deleteItemAt(MusicObject::MIntList,bool)), SLOT(setDeleteItemAt(MusicObject::MIntList,bool)));
    connect(m_musicSongTree, SIGNAL(clearSearchText()), m_bottomAreaWidget, SLOT(clearSearchedText()));
    connect(m_musicSongTree, SIGNAL(updatePlayLists(QString)), m_musicList, SLOT(appendMedia(QString)));
    connect(m_musicSongTree, SIGNAL(updateMediaLists(QStringList, int)), m_musicList, SLOT(updateMediaLists(QStringList, int)));

    connect(ui->musicDesktopLrc, SIGNAL(clicked(bool)), m_rightAreaWidget, SLOT(setDestopLrcVisible(bool)));

    ui->lrcDisplayAllButton->hide();
    ui->musicKey->setFocus();
    ui->surfaceStackedWidget->setCurrentIndex(0);

    ui->musicTimeWidget->setObject(this);
    M_HOTKEY_PTR->connectParentObject(this);

    QObjectList result = foreachWidget(this);
    foreach(QObject *obj, result)
    {
        QWidget *widget = MObject_cast(QWidget*, obj);
        widget->installEventFilter(this);
        widget->setMouseTracking(true);
    }

    readXMLConfigFromText();
}

MusicApplication::~MusicApplication()
{
    delete m_musicPlayer;
    delete m_musicList;
    delete m_musicSongTree;
    delete m_bottomAreaWidget;
    delete m_topAreaWidget;
    delete m_rightAreaWidget;
    delete m_leftAreaWidget;
    delete m_applicationObject;
    delete ui;
}

QString MusicApplication::getClassName()
{
    return staticMetaObject.className();
}

MusicApplication *MusicApplication::instance()
{
    return m_instance;
}

#if defined(Q_OS_WIN)
#  ifdef MUSIC_GREATER_NEW
bool MusicApplication::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    m_applicationObject->nativeEvent(eventType, message, result);
    return MusicAbstractMoveResizeWidget::nativeEvent(eventType, message, result);
}
#  else
bool MusicApplication::winEvent(MSG *message, long *result)
{
    m_applicationObject->winEvent(message, result);
    return MusicAbstractMoveResizeWidget::winEvent(message, result);
}
#  endif
#endif

void MusicApplication::resizeEvent(QResizeEvent *event)
{
    M_SETTING_PTR->setValue(MusicSettingManager::WidgetSize, size());
    m_topAreaWidget->musicBgThemeChangedByResize();
    m_bottomAreaWidget->resizeWindow();
    MusicAbstractMoveResizeWidget::resizeEvent(event);
}

void MusicApplication::closeEvent(QCloseEvent *event)
{
    MusicAbstractMoveResizeWidget::closeEvent(event);
    event->ignore();
    if(!m_bottomAreaWidget->getSystemCloseConfig() &&
        m_bottomAreaWidget->systemTrayIsVisible() )
    {
       hide();
       m_bottomAreaWidget->showMessage(tr("Prompt"),
                                       tr("MMMMusicPlayer will run in the background"));
    }
    else
    {
       quitWindowClose();
    }
}

void MusicApplication::dragEnterEvent(QDragEnterEvent *event)
{
    MusicAbstractMoveResizeWidget::dragEnterEvent(event);
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void MusicApplication::dragMoveEvent(QDragMoveEvent *event)
{
    MusicAbstractMoveResizeWidget::dragMoveEvent(event);
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void MusicApplication::dropEvent(QDropEvent *event)
{
    MusicAbstractMoveResizeWidget::dropEvent(event);
    const QMimeData *data = event->mimeData();
    QStringList fileList;
    QString suffix;
    QStringList sfx = MusicPlayer::supportFormatsString();

    foreach(QUrl url, data->urls())
    {
        suffix = QFileInfo(url.toLocalFile()).suffix();
        if( sfx.contains(suffix.toLower()) )
        {
            fileList << url.toLocalFile();
        }
        else
        {
            MusicMessageBox message;
            message.setText(url.toString().split('/').back() + tr("not supported"));
            message.exec();
        }
    }
    musicImportSongsSettingPath(fileList);
}

void MusicApplication::contextMenuEvent(QContextMenuEvent *event)
{
    MusicAbstractMoveResizeWidget::contextMenuEvent(event);
    musicCreateRightMenu();
}

void MusicApplication::readXMLConfigFromText()
{
    MusicXMLConfigManager xml;
    int value = -1;

    //Path configuration song
    MusicSongItems songs;
    if(xml.readMusicXMLConfig())//open music file
    {
        xml.readMusicSongsConfig(songs);
    }
    m_musicSongTree->setMusicLists(songs);
    if(songs.count() > 0)
    {
        ui->musicPlayedList->setPlayListCount(songs.first().m_songs.count());
    }
    //////////////////////////////////////////////////////////////
    if(!xml.readXMLConfig())//open file
    {
        return;
    }

    //Configure playback mode
    ui->musicEnhancedButton->setEnhancedMusicConfig(xml.readEnhancedMusicConfig());
    xml.readOtherLoadConfig();

    switch( xml.readMusicPlayModeConfig() )
    {
        case MusicObject::MC_PlayOrder:
            musicPlayOrder();break;
        case MusicObject::MC_PlayRandom:
            musicPlayRandom();break;
        case MusicObject::MC_PlayListLoop:
            musicPlayListLoop();break;
        case MusicObject::MC_PlayOneLoop:
            musicPlayOneLoop();break;
        case MusicObject::MC_PlayOnce:
            musicPlayItemOnce();break;
        default:break;
    }
    //////////////////////////////////////////////////////////////
    //The size of the volume of the allocation of songs
    value = xml.readMusicPlayVolumeConfig();
    musicVolumeChanged(value);
    M_SETTING_PTR->setValue(MusicSettingManager::VolumeChoiced, value);
    ////////////////////////musicSetting
    //////////////////////////////////////////////////////////////
    //Set the inline lrc should be shown
    value = xml.readShowInlineLrc();
    M_SETTING_PTR->setValue(MusicSettingManager::ShowInlineLrcChoiced, value);
    m_rightAreaWidget->setInlineLrcVisible(value);
    //////////////////////////////////////////////////////////////
    //Set the desktop lrc should be shown
    value = xml.readShowDesktopLrc();
    M_SETTING_PTR->setValue(MusicSettingManager::ShowDesktopLrcChoiced, value);
    m_bottomAreaWidget->setDestopLrcVisible(value);
    m_rightAreaWidget->setDestopLrcVisible(value);
    //////////////////////////////////////////////////////////////
    //Set the current background color
    //Set the current alpha value
    m_topAreaWidget->setParameters(xml.readBackgroundTheme(),
                                   xml.readBackgroundTransparent().toInt(),
                                   xml.readBackgroundListTransparent().toInt());
    //////////////////////////////////////////////////////////////
    //Configuration from next time also stopped at the last record.
    QStringList keyList;
    xml.readSystemLastPlayIndexConfig(keyList);
    M_SETTING_PTR->setValue(MusicSettingManager::LastPlayIndexChoiced, keyList);
    //add new music file to playlist
    m_musicList->addMedia(m_musicSongTree->getMusicSongsFilePath(keyList[1].toInt()));
    if(keyList[0] == "1")
    {
        QTimer::singleShot(MT_MS, m_musicSongTree, SLOT(setCurrentIndex()));
        m_currentMusicSongTreeIndex = keyList[1].toInt();
        m_musicList->blockSignals(true);
        m_musicList->setCurrentIndex(keyList[2].toInt());
        m_musicList->blockSignals(false);
    }
    //////////////////////////////////////////////////////////////
    //Configure automatic playback
    value = xml.readSystemAutoPlayConfig();
    M_SETTING_PTR->setValue(MusicSettingManager::AutoPlayChoiced, value);
    if(value == 1)
    {
        m_playControl = true;
        musicStatePlay();
    }
    m_bottomAreaWidget->showPlayStatus(m_playControl);
    m_rightAreaWidget->showPlayStatus(m_playControl);
    //////////////////////////////////////////////////////////////
    //When the configuration is close to the direct exit
    value = xml.readSystemCloseConfig();
    M_SETTING_PTR->setValue(MusicSettingManager::CloseEventChoiced, value);
    m_bottomAreaWidget->setSystemCloseConfig(value);
    //////////////////////////////////////////////////////////////
    //Set the lrc color the user set
    M_SETTING_PTR->setValue(MusicSettingManager::LrcColorChoiced, xml.readShowLrcColor());
    M_SETTING_PTR->setValue(MusicSettingManager::LrcFgColorChoiced, xml.readShowLrcFgColor());
    M_SETTING_PTR->setValue(MusicSettingManager::LrcBgColorChoiced, xml.readShowLrcBgColor());
    M_SETTING_PTR->setValue(MusicSettingManager::LrcFamilyChoiced, xml.readShowLrcFamily());
    M_SETTING_PTR->setValue(MusicSettingManager::LrcTypeChoiced, xml.readShowLrcType());
    M_SETTING_PTR->setValue(MusicSettingManager::LrcColorTransChoiced, xml.readShowLrcTransparent());
    M_SETTING_PTR->setValue(MusicSettingManager::LrcSizeChoiced, xml.readShowLrcSize());
    //////////////////////////////////////////////////////////////
    //Set the lrc size the user set
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcColorChoiced, xml.readShowDLrcColor());
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcFgColorChoiced, xml.readShowDLrcFgColor());
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcBgColorChoiced, xml.readShowDLrcBgColor());
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcFamilyChoiced, xml.readShowDLrcFamily());
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcTypeChoiced, xml.readShowDLrcType());
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcColorTransChoiced, xml.readShowDLrcTransparent());
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcSizeChoiced, xml.readShowDLrcSize());
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcLockedChoiced, xml.readShowDLrcLocked());
    M_SETTING_PTR->setValue(MusicSettingManager::DLrcGeometryChoiced, xml.readShowDLrcGeometry());
    m_bottomAreaWidget->lockDesktopLrc(xml.readShowDLrcLocked());
    m_rightAreaWidget->setSettingParameter();
    //////////////////////////////////////////////////////////////
    M_SETTING_PTR->setValue(MusicSettingManager::EqualizerEnableChoiced, xml.readEqualizerEnale());
    M_SETTING_PTR->setValue(MusicSettingManager::EqualizerValueChoiced, xml.readEqualizerValue());
    M_SETTING_PTR->setValue(MusicSettingManager::EqualizerIndexChoiced, xml.readEqualizerIndex());
    m_musicPlayer->setEqInformation();
    //////////////////////////////////////////////////////////////
    M_SETTING_PTR->setValue(MusicSettingManager::CurrentLanIndexChoiced, xml.readLanguageIndex());

    ///init or reset the window
    setGeometry( xml.readWindowGeometry() );
}

void MusicApplication::writeXMLConfigToText()
{
    MusicXMLConfigManager xml;

    M_SETTING_PTR->setValue(MusicSettingManager::WidgetPosition, pos());
    M_SETTING_PTR->setValue(MusicSettingManager::EnhancedMusicChoiced, m_musicPlayer->getMusicEnhanced());
    M_SETTING_PTR->setValue(MusicSettingManager::PlayModeChoiced, m_musicList->playbackMode());
    M_SETTING_PTR->setValue(MusicSettingManager::VolumeChoiced, ui->musicSound->value());
    QStringList lastPlayIndexChoiced = M_SETTING_PTR->value(MusicSettingManager::LastPlayIndexChoiced).toStringList();
    if(lastPlayIndexChoiced.isEmpty())
    {
        lastPlayIndexChoiced << "0" << "0" << "-1";
    }
    else
    {
        lastPlayIndexChoiced[1] = QString::number(m_musicSongTree->getCurrentPlayToolIndex());
        lastPlayIndexChoiced[2] = QString::number(m_musicList->currentIndex());
    }
    M_SETTING_PTR->setValue(MusicSettingManager::LastPlayIndexChoiced, lastPlayIndexChoiced);
    M_SETTING_PTR->setValue(MusicSettingManager::BgThemeChoiced, m_topAreaWidget->getBgSkin());
    M_SETTING_PTR->setValue(MusicSettingManager::BgTransparentChoiced, m_topAreaWidget->getBgSkinAlpha());
    M_SETTING_PTR->setValue(MusicSettingManager::BgListTransparentChoiced, m_topAreaWidget->getListBgSkinAlpha());
    M_SETTING_PTR->setValue(MusicSettingManager::ShowDesktopLrcChoiced, m_rightAreaWidget->getDestopLrcVisible());
    xml.writeXMLConfig();
    xml.writeMusicSongsConfig( m_musicSongTree->getMusicLists() );
}

void MusicApplication::quitWindowClose()
{
    //Write configuration files
    writeXMLConfigToText();
    m_applicationObject->windowCloseAnimationOpacity();
}

void MusicApplication::positionChanged(qint64 position)
{
    m_rightAreaWidget->updateCurrentLrc(position, m_musicPlayer->duration(), m_playControl);
    ui->musicTimeWidget->setValue(position);
    if(m_musicList->isEmpty())
    {
        ui->playCurrentTime->setText("00:00");
    }
    else
    {
        ui->playCurrentTime->setText(MusicTime::msecTime2LabelJustified(position));
    }
    //Show the current play time
    m_musicSongTree->setTimerLabel(ui->playCurrentTime->text());
#if defined MUSIC_DEBUG && defined Q_OS_WIN && defined MUSIC_WINEXTRAS
    m_bottomAreaWidget->setValue(position);
#endif
}

void MusicApplication::durationChanged(qint64 duration)
{
    //Show the current play total time
    ui->musicTimeWidget->setRange(0, duration);
    ui->playTotalTime->setText("/" + MusicTime::msecTime2LabelJustified(duration));
    //Loading the current song lrc
    musicLoadCurrentSongLrc();
#if defined MUSIC_DEBUG && defined Q_OS_WIN && defined MUSIC_WINEXTRAS
    m_bottomAreaWidget->setRange(0, duration);
#endif
}

void MusicApplication::showCurrentSong(int index)
{
    QString name;
    if( index > -1 ) //The list to end
    {
        QStringList songsFileNames = m_musicSongTree->getMusicSongsFileName(m_musicSongTree->getCurrentPlayToolIndex());
        if(songsFileNames.count() > index)
        {
            name = songsFileNames[index].trimmed();
            ///detecting whether the file has been downloaded
            MusicSongs currentSongs = m_musicSongTree->getMusicLists()[m_musicSongTree->getCurrentPlayToolIndex()].m_songs;
            QString path = QString("%1/%2.%3").arg(M_SETTING_PTR->value(MusicSettingManager::DownloadMusicPathDirChoiced).toString())
                                              .arg(name).arg(currentSongs[index].getMusicType());
            bool exist = QFile::exists(path);
            M_SETTING_PTR->setValue(MusicSettingManager::DownloadMusicExistPathChoiced, path);
            M_SETTING_PTR->setValue(MusicSettingManager::DownloadMusicExistChoiced, exist);
            ui->musicDownload->setStyleSheet(exist ? MusicUIObject::MKGBtnDownload : MusicUIObject::MKGBtnUnDownload);
            //////////////////////////////////////////
            MusicSongs loveSongs = m_musicSongTree->getMusicLists()[MUSIC_LOVEST_LIST].m_songs;
            exist = loveSongs.contains(currentSongs[index]);
            M_SETTING_PTR->setValue(MusicSettingManager::MuiscSongLovedChoiced, exist);
            ui->musicBestLove->setStyleSheet(exist ? MusicUIObject::MKGBtnLove : MusicUIObject::MKGBtnUnLove);
            //////////////////////////////////////////
            m_musicSongTree->selectRow(index);
        }
    }
    else
    {
        ui->musicBestLove->setStyleSheet(MusicUIObject::MKGBtnUnLove);
        ui->musicDownload->setStyleSheet(MusicUIObject::MKGBtnUnDownload);
        ui->musicKey->setStyleSheet(MusicUIObject::MKGBtnPlay);
        m_playControl = true;
        m_musicPlayer->stop();
        m_rightAreaWidget->stopLrcMask();

        m_bottomAreaWidget->showPlayStatus(m_playControl);
        m_rightAreaWidget->showPlayStatus(m_playControl);
        m_topAreaWidget->showPlayStatus(m_playControl);
        ui->musicTimeWidget->setPlayState(m_playControl);

        durationChanged(0);
        positionChanged(0);
        m_rightAreaWidget->loadCurrentSongLrc(name, name);
    }
    ui->showCurrentSong->setText(name);
    ui->musicMoreFunction->setCurrentSongName(name);
    //Show the current play song information
    M_BACKGROUND_PTR->clearArtName();
    m_rightAreaWidget->musicCheckHasLrcAlready();
    m_bottomAreaWidget->setLabelText(name);
    m_topAreaWidget->setLabelText(name);
    //display current ArtTheme pic
    M_BACKGROUND_PTR->setArtName( getCurrentFileName() );
    m_topAreaWidget->musicBgThemeDownloadFinished();
}

void MusicApplication::stateChanged()
{
    m_playControl = true;
    ui->musicKey->setStyleSheet(MusicUIObject::MKGBtnPlay);
}

void MusicApplication::musicImportPlay()
{
    musicPlayIndex(m_musicList->mediaCount() - 1, 0);
}

void MusicApplication::musicCreateRightMenu()
{
    QMenu rightClickMenu(this);
    rightClickMenu.setStyleSheet(MusicUIObject::MMenuStyle02);
    rightClickMenu.addAction(QIcon(":/contextMenu/btn_login"), m_topAreaWidget->getUserLoginState() ? tr("logout") : tr("login"),
                             m_topAreaWidget, SLOT(musicUserContextLogin()));
    rightClickMenu.addSeparator();

    QMenu musicAddNewFiles(tr("addNewFiles"), &rightClickMenu);
    rightClickMenu.addMenu(&musicAddNewFiles);
    musicAddNewFiles.addAction(tr("openOnlyFiles"), this, SLOT(musicImportSongsOnlyFile()));
    musicAddNewFiles.addAction(tr("openOnlyDir"), this, SLOT(musicImportSongsOnlyDir()));

    QMenu musicPlaybackMode(tr("playbackMode"), &rightClickMenu);
    rightClickMenu.addMenu(&musicPlaybackMode);

    MusicObject::SongPlayType songplaymode = m_musicList->playbackMode();
    QAction *order = musicPlaybackMode.addAction(tr("OrderPlay"), this, SLOT(musicPlayOrder()));
    QAction *random = musicPlaybackMode.addAction(tr("RandomPlay"), this, SLOT(musicPlayRandom()));
    QAction *lCycle = musicPlaybackMode.addAction(tr("ListCycle"), this, SLOT(musicPlayListLoop()));
    QAction *sCycle = musicPlaybackMode.addAction(tr("SingleCycle"), this, SLOT(musicPlayOneLoop()));
    QAction *once = musicPlaybackMode.addAction(tr("PlayOnce"), this, SLOT(musicPlayItemOnce()));
    (songplaymode == MusicObject::MC_PlayOrder) ? order->setIcon(QIcon(":/contextMenu/btn_selected")) : order->setIcon(QIcon());
    (songplaymode == MusicObject::MC_PlayRandom) ? random->setIcon(QIcon(":/contextMenu/btn_selected")) : random->setIcon(QIcon());
    (songplaymode == MusicObject::MC_PlayListLoop) ? lCycle->setIcon(QIcon(":/contextMenu/btn_selected")) : lCycle->setIcon(QIcon());
    (songplaymode == MusicObject::MC_PlayOneLoop) ? sCycle->setIcon(QIcon(":/contextMenu/btn_selected")) : sCycle->setIcon(QIcon());
    (songplaymode == MusicObject::MC_PlayOnce) ? once->setIcon(QIcon(":/contextMenu/btn_selected")) : once->setIcon(QIcon());

    rightClickMenu.addSeparator();
    QMenu musicRemoteControl(tr("RemoteControl"), &rightClickMenu);
    rightClickMenu.addMenu(&musicRemoteControl);
    musicRemoteControl.addAction(tr("SquareRemote"), m_topAreaWidget, SLOT(musicSquareRemote()));
    musicRemoteControl.addAction(tr("RectangleRemote"), m_topAreaWidget, SLOT(musicRectangleRemote()));
    musicRemoteControl.addAction(tr("DiamondRemote"), m_topAreaWidget, SLOT(musicDiamondRemote()));
    musicRemoteControl.addAction(tr("SimpleStyleRemote"), m_topAreaWidget, SLOT(musicSimpleStyleRemote()));
    musicRemoteControl.addAction(tr("ComplexStyleRemote"), m_topAreaWidget, SLOT(musicComplexStyleRemote()));
    musicRemoteControl.addAction(tr("CircleRemote"), m_topAreaWidget, SLOT(musicCircleRemote()));
    musicRemoteControl.addAction(tr("DeleteRemote"), m_topAreaWidget, SLOT(musicDeleteRemote()));

    rightClickMenu.addAction(QIcon(":/contextMenu/btn_equalizer"), tr("Equalizer"), this, SLOT(musicSetEqualizer()));
    rightClickMenu.addAction(tr("AudioRecorder"), m_applicationObject, SLOT(musicAudioRecorder()));
    rightClickMenu.addAction(tr("TimingSettings"), m_applicationObject, SLOT(musicTimerWidget()));
    QMenu spectrumControl(tr("ShowingSpectrum"), &rightClickMenu);
    spectrumControl.addAction(tr("AnalyzerSpectrum"), m_leftAreaWidget, SLOT(musicAnalyzerSpectrumWidget()));
    spectrumControl.addAction(tr("ProjectMSpectrum"), m_leftAreaWidget, SLOT(musicProjectMSpectrumWidget()))->setEnabled(
#if !defined Q_OS_WIN || defined MUSIC_GREATER_NEW
    false);
#else
    true);
#endif
    rightClickMenu.addMenu(&spectrumControl);
    rightClickMenu.addSeparator();

    QAction *window = rightClickMenu.addAction(tr("windowTop"), m_applicationObject, SLOT(musicSetWindowToTop()));
    window->setIcon(QIcon(m_applicationObject->getWindowToTop() ? ":/contextMenu/btn_selected" : QString()));
    rightClickMenu.addAction(tr("resetWindow"), m_applicationObject, SLOT(musicResetWindow()));

    rightClickMenu.addAction(QIcon(":/contextMenu/btn_setting"), tr("Setting"), this, SLOT(musicSetting()));
    rightClickMenu.addAction(QIcon(":/contextMenu/btn_location"), tr("musicLocation"), this, SLOT(musicCurrentPlayLocation()));

    QMenu musicInfo(tr("musicAbout"), &rightClickMenu);
    rightClickMenu.addMenu(&musicInfo)->setIcon(QIcon(":/contextMenu/btn_about"));
    musicInfo.addAction(QIcon(":/contextMenu/btn_update"), tr("Update"), m_applicationObject, SLOT(musicVersionUpdate()));
    musicInfo.addAction(QIcon(":/contextMenu/btn_about"), tr("Version") + QString(MMMMUSIC_VERSION_STR) + QString(MMMMUSIC_VER_TIME_STR),
                        m_applicationObject, SLOT(musicAboutUs()));

    rightClickMenu.addSeparator();
    rightClickMenu.addAction(QIcon(":/contextMenu/btn_quit"), tr("quit"), this, SLOT(quitWindowClose()));
    rightClickMenu.exec(QCursor::pos());
}

void MusicApplication::musicStatePlay()
{
    if(m_musicList->isEmpty())
    {
        return;//The playlist is not performing space-time
    }
    if(m_playControl)
    {
        ui->musicKey->setStyleSheet(MusicUIObject::MKGBtnPause);
        m_playControl = false;
        m_musicPlayer->play();
        m_topAreaWidget->musicBgThemeDownloadFinished();
        m_rightAreaWidget->startTimerClock();
    }
    else
    {
        ui->musicKey->setStyleSheet(MusicUIObject::MKGBtnPlay);
        m_playControl = true;
        m_musicPlayer->pause();
        m_topAreaWidget->setTimerStop();
        m_rightAreaWidget->stopLrcMask();
    }
    m_bottomAreaWidget->showPlayStatus(m_playControl);
    m_rightAreaWidget->showPlayStatus(m_playControl);
    m_topAreaWidget->showPlayStatus(m_playControl);
    ui->musicTimeWidget->setPlayState(m_playControl);
}

void MusicApplication::musicPlayPrevious()
{
    if(m_musicList->isEmpty())
    {
        return;//The playlist is not performing space-time
    }
    if(m_musicList->playbackMode() == MusicObject::MC_PlayRandom)
    {
        m_musicList->setCurrentIndex();
    }
    else
    {
        m_musicPlayer->playPrevious();
    }
    m_playControl = true;
    musicStatePlay();
    m_playControl = false;
}

void MusicApplication::musicPlayNext()
{
    if(m_musicList->isEmpty())
    {
        return;//The playlist is not performing space-time
    }
    if(m_musicList->playbackMode() == MusicObject::MC_PlayRandom)
    {
        m_musicList->setCurrentIndex();
    }
    else
    {
        m_musicPlayer->playNext();
    }
    m_playControl = true;
    musicStatePlay();
    m_playControl = false;
}

void MusicApplication::musicPlayOrder()
{
    m_musicList->setPlaybackMode(MusicObject::MC_PlayOrder);
    ui->musicPlayMode->setPlaybackMode(MusicObject::MC_PlayOrder);
    m_musicSongTree->setPlaybackMode(MusicObject::MC_PlayOrder);
}

void MusicApplication::musicPlayRandom()
{
    m_musicList->setPlaybackMode(MusicObject::MC_PlayRandom);
    ui->musicPlayMode->setPlaybackMode(MusicObject::MC_PlayRandom);
    m_musicSongTree->setPlaybackMode(MusicObject::MC_PlayRandom);
}

void MusicApplication::musicPlayListLoop()
{
    m_musicList->setPlaybackMode(MusicObject::MC_PlayListLoop);
    ui->musicPlayMode->setPlaybackMode(MusicObject::MC_PlayListLoop);
    m_musicSongTree->setPlaybackMode(MusicObject::MC_PlayListLoop);
}

void MusicApplication::musicPlayOneLoop()
{
    m_musicList->setPlaybackMode(MusicObject::MC_PlayOneLoop);
    ui->musicPlayMode->setPlaybackMode(MusicObject::MC_PlayOneLoop);
    m_musicSongTree->setPlaybackMode(MusicObject::MC_PlayOneLoop);
}

void MusicApplication::musicPlayItemOnce()
{
    m_musicList->setPlaybackMode(MusicObject::MC_PlayOnce);
    ui->musicPlayMode->setPlaybackMode(MusicObject::MC_PlayOnce);
    m_musicSongTree->setPlaybackMode(MusicObject::MC_PlayOnce);
}

void MusicApplication::musicVolumeMute()
{
    m_musicPlayer->setMuted(!m_musicPlayer->isMuted());
    int volume = m_musicPlayer->volume();
    m_topAreaWidget->setVolumeValue(volume);
    m_bottomAreaWidget->setVolumeValue(volume);
    ui->musicSound->setValue(volume);
    M_SETTING_PTR->setValue(MusicSettingManager::VolumeChoiced, volume);
}

void MusicApplication::musicVolumeChanged(int volume)
{
    m_topAreaWidget->setVolumeValue(volume);
    m_bottomAreaWidget->setVolumeValue(volume);
    ui->musicSound->setValue(volume);
    m_musicPlayer->setVolume(volume);
    M_SETTING_PTR->setValue(MusicSettingManager::VolumeChoiced, volume);
}

void MusicApplication::musicActionVolumeSub()
{
    int currentVol = m_musicPlayer->volume();
    currentVol -= 15;
    if( currentVol < 0)
    {
        currentVol = 0;   //reset music volume
    }
    musicVolumeChanged( currentVol );
}

void MusicApplication::musicActionVolumePlus()
{
    int currentVol = m_musicPlayer->volume();
    currentVol += 15;
    if( currentVol > 100)
    {
        currentVol = 100;   //reset music volume
    }
    musicVolumeChanged( currentVol );
}

void MusicApplication::musicImportSongsOnlyFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles );
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilters( MusicPlayer::supportFormatsFilterDialogString() );

    if(dialog.exec())
    {
        musicImportSongsSettingPath(dialog.selectedFiles());
    }
}

void MusicApplication::musicImportSongsOnlyDir()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory );
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec())
    {
        QList<QFileInfo> file(dialog.directory().entryInfoList());
        QStringList fileList;
        foreach(const QFileInfo &info, file)
        {
            if( MusicPlayer::supportFormatsString().contains(info.suffix().toLower()) )
            {
               fileList << info.absoluteFilePath();
            }
        }
        musicImportSongsSettingPath(fileList);
    }
}

void MusicApplication::musicImportSongsSettingPath(const QStringList &path)
{
    if(path.isEmpty())
    {
        return;
    }

    m_musicSongTree->importOtherMusicSongs(path);//append in songsList
    if(m_currentMusicSongTreeIndex == 0)
    {
        m_musicList->appendMedia(path);
    }
    if(path.count() > 0 && m_musicList->currentIndex() < 0 && m_musicSongTree->getCurrentPlayToolIndex() == 0)
    {
        m_musicList->setCurrentIndex(0);
    }
}

void MusicApplication::musicImportSongs()
{
    QMenu menu;
    menu.setStyleSheet(MusicUIObject::MMenuStyle02);
    menu.addAction(tr("openOnlyFiles"), this, SLOT(musicImportSongsOnlyFile()));
    menu.addAction(tr("openOnlyDir"), this, SLOT(musicImportSongsOnlyDir()));
    menu.addSeparator();
    menu.addAction(tr("dragAnddrop"))->setEnabled(false);
    menu.exec(QCursor::pos());
}

void MusicApplication::musicPlayIndex(int row)
{
    m_musicPlayer->stop();

    m_musicList->clear();
    m_musicList->addMedia(m_musicSongTree->getMusicSongsFilePath(m_musicSongTree->currentIndex()));
    m_currentMusicSongTreeIndex = m_musicSongTree->currentIndex();
    m_musicSongTree->setCurrentMusicSongTreeIndex(m_currentMusicSongTreeIndex);

    if(row != -999)
    {
        m_musicList->setCurrentIndex(row);
    }
}

void MusicApplication::musicPlayIndex(int row, int)
{
    musicPlayIndex(-999); //just invalid
    if(!m_musicSongTree->searchFileListEmpty())
    {
        row = m_musicSongTree->getSearchFileListIndexAndClear(row);
    }

    m_musicList->setCurrentIndex(row);
    m_playControl = true;
    musicStatePlay();
    m_playControl = false;
}

void MusicApplication::musicPlayAnyTimeAt(int posValue)
{
    //Drag the progress indicator to rewind or fast-forward through the current song
    m_musicPlayer->setPosition(posValue);
    //Set lrc corrent to show
    m_rightAreaWidget->setSongSpeedAndSlow(posValue);
}

void MusicApplication::musicSetting()
{
    m_rightAreaWidget->showSettingWidget();
}

void MusicApplication::musicCurrentPlayLocation()
{
    if(m_musicList->isEmpty())
    {
        return;
    }
    m_musicSongTree->playLocation(m_musicList->currentIndex());
}

void MusicApplication::setDeleteItemAt(const MusicObject::MIntList &index, bool remove)
{
    if(index.isEmpty())
    {
        return;
    }

    QString prePlayName = m_musicList->currentMediaString();
    bool contains = false; ///the play one is delete list
    int oldIndex = m_musicList->currentIndex();
    ///check if delete one that the play one
    if(index.count() == 1 && index.first() == oldIndex)
    {
        contains = true;
    }
    ///other ways
    for(int i=index.count() - 1; i>=0; --i)
    {
        m_musicList->removeMedia(index[i]);
        if(i != 0 && !contains && oldIndex <= index[i] && oldIndex >= index[i-1])
        {
            oldIndex -= i;
            contains = true;
        }
    }

    if(!contains && m_musicList->currentIndex() > index[0])
    {
        oldIndex -= index.count();
    }
    if( oldIndex == m_musicList->mediaCount()) ///Play index error correction
    {
        --oldIndex;
    }
    m_musicList->setCurrentIndex(oldIndex);

    if(contains)
    {
        //The corresponding item is deleted from the QMediaPlaylist
        m_playControl = true;
        musicStatePlay();
        m_playControl = false;
        if(remove)
        {
            QFile::remove(prePlayName);
        }
    }
}

void MusicApplication::getParameterSetting()
{
    m_applicationObject->getParameterSetting();
    m_rightAreaWidget->getParameterSetting();
    bool config = M_SETTING_PTR->value(MusicSettingManager::CloseEventChoiced).toBool();
    m_bottomAreaWidget->setSystemCloseConfig(config);
         config = M_SETTING_PTR->value(MusicSettingManager::ShowDesktopLrcChoiced).toBool();
    m_bottomAreaWidget->setDestopLrcVisible(config);
    //This attribute is effective immediately.
}

void MusicApplication::musicSetEqualizer()
{
    m_applicationObject->musicSetEqualizer();
}

void MusicApplication::musicSearchIndexChanged(int, int index)
{
    m_musicSongTree->searchFileListCache(index, m_bottomAreaWidget->getSearchedText());
}

void MusicApplication::musicLoadCurrentSongLrc()
{
    //display current ArtTheme pic
    m_topAreaWidget->musicBgThemeDownloadFinished();
    //Loading the current song lrc
    if(m_musicList->currentIndex() == -1)
    {
        return;
    }

    QString filename = getCurrentFileName();
    QString path = QFile::exists(LRC_DIR_FULL + filename + LRC_FILE) ? (LRC_DIR_FULL + filename + LRC_FILE) : (LRC_DIR_FULL + filename + KRC_FILE);
    m_rightAreaWidget->loadCurrentSongLrc(filename, path);
}

QString MusicApplication::getCurrentFileName() const
{
    if(m_musicList->currentIndex() < 0 || m_currentMusicSongTreeIndex < 0)
    {
        return QString();
    }

    QStringList nanmes = m_musicSongTree->getMusicSongsFileName(m_currentMusicSongTreeIndex);
    return (nanmes.count() > m_musicList->currentIndex()) ? nanmes[m_musicList->currentIndex()].trimmed() : QString();
}

bool MusicApplication::checkMusicListCurrentIndex() const
{
    return (m_musicList->currentIndex() == -1);
}

void MusicApplication::updateCurrentArtist()
{
    m_musicSongTree->updateCurrentArtist();
}

void MusicApplication::musicCurrentLrcUpdated()
{
    QString filename = getCurrentFileName();
    QFile file(LRC_DIR_FULL + filename + LRC_FILE);
    if(file.exists())
    {
        file.remove();
    }
    m_rightAreaWidget->musicCheckHasLrcAlready();
}

void MusicApplication::updateCurrentTime(qint64 pos)
{
    if(!m_playControl) ///When pause just resume it
    {
        m_musicPlayer->setPosition(pos);
    }
}

void MusicApplication::musicAddSongToLovestListAt()
{
    int index = m_musicList->currentIndex();
    if(m_musicList->isEmpty() || index < 0)
    {
        return;
    }

    m_leftAreaWidget->musictLoveStateClicked();
    bool state = M_SETTING_PTR->value(MusicSettingManager::MuiscSongLovedChoiced).toBool();
    state ? m_musicSongTree->addMusicSongToLovestListAt(index) : m_musicSongTree->removeMusicSongToLovestListAt(index);

    if(m_currentMusicSongTreeIndex == 1)
    {
        setDeleteItemAt(MusicObject::MIntList() << index, false);
    }

    MusicToastLabel *toast = new MusicToastLabel(this);
    toast->setFontSize(25);
    toast->setFontMargin(20, 20);
    toast->setText(state ? tr("add music to lovest list done!") : tr("remove music to lovest list done!"));
    QPoint globalPoint = mapToGlobal(QPoint(0, 0));
    toast->move(globalPoint.x() + (width() - toast->width())/2, globalPoint.y() + (height() - toast->height())/2);
    toast->show();
}

void MusicApplication::setPlaySongChanged(int index)
{
    if(m_musicList->isEmpty() || index <0 || index >= m_musicList->mediaCount())
    {
        return;
    }
    musicPlayIndex(index, 0);
}

void MusicApplication::setStopSongChanged()
{
    m_playControl = false;
    musicStatePlay();
}

void MusicApplication::musicWindowConciseChanged()
{
    m_bottomAreaWidget->setWindowConcise();
    m_topAreaWidget->musicBgThemeDownloadFinished();
}

void MusicApplication::musicEnhancedMusicChanged(int type)
{
    m_musicPlayer->setMusicEnhanced(MStatic_cast(MusicPlayer::Enhanced, type));
}

void MusicApplication::getCurrentPlayList(QStringList &list)
{
    list = m_musicSongTree->getMusicSongsFileName(m_musicSongTree->currentIndex());
}
