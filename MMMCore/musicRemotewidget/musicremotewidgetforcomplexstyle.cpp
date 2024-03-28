#include "musicremotewidgetforcomplexstyle.h"
#include "musicsettingmanager.h"

MusicRemoteWidgetForComplexStyle::MusicRemoteWidgetForComplexStyle(QWidget *parent)
    : MusicRemoteWidget(parent)
{
    setGeometry(200, 200, 320, 110);
    setAttribute(Qt::WA_TranslucentBackground);

    QSize windowSize = M_SETTING_PTR->value(MusicSettingManager::ScreenSize).toSize();
    move( windowSize.width() - width() - 150, height() + 70);

    m_iconLabel = new QLabel(this);
    m_songName = new QLabel(this);
    m_songArtist = new QLabel(this);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(5, 5, 5, 5);
    hbox->addWidget(m_mainWidget);
    setLayout(hbox);

    QWidget *mvWidget = new QWidget(m_mainWidget);
    QHBoxLayout *mhbox = new QHBoxLayout(m_mainWidget);
    mhbox->addWidget(m_iconLabel);
    mhbox->addWidget(mvWidget);
    m_mainWidget->setLayout(mhbox);

    QWidget *toolWidget = new QWidget(mvWidget);
    QHBoxLayout *toolbox = new QHBoxLayout(toolWidget);
    toolbox->setContentsMargins(0, 0, 0, 0);
    toolbox->setSpacing(1);
    toolbox->addWidget(m_PreSongButton);
    toolbox->addWidget(m_PlayButton);
    toolbox->addWidget(m_NextSongButton);
    toolbox->addWidget(m_volumeWidget);
    toolbox->addWidget(m_SettingButton);
    toolbox->addWidget(m_showMainWindow);
    toolWidget->setLayout(toolbox);

    QVBoxLayout *mvbox = new QVBoxLayout(mvWidget);
    mvbox->setContentsMargins(0, 0, 0, 0);
    mvbox->setSpacing(0);
    mvbox->addWidget(m_songName);
    mvbox->addWidget(m_songArtist);
    mvbox->addWidget(toolWidget);
    mvWidget->setLayout(mvbox);

    m_iconLabel->setFixedSize(80, 80);
    m_songName->setStyleSheet(MusicUIObject::MWidgetStyle01);
    m_songArtist->setStyleSheet(MusicUIObject::MWidgetStyle01);

}

MusicRemoteWidgetForComplexStyle::~MusicRemoteWidgetForComplexStyle()
{
    delete m_iconLabel;
    delete m_songName;
    delete m_songArtist;
}

QString MusicRemoteWidgetForComplexStyle::getClassName()
{
    return staticMetaObject.className();
}

void MusicRemoteWidgetForComplexStyle::setLabelText(const QString &value)
{
    QStringList strings = value.split("-");
    if(strings.count() == 1)
    {
        strings << "--";
    }

    m_songName->setText(strings.first().trimmed());
    m_songArtist->setText(strings.last().trimmed());

    if(!showArtPicture(strings.first().trimmed()) &&
       !showArtPicture(strings.last().trimmed()))
    {
        m_iconLabel->setPixmap(QPixmap(":/image/lb_defaultArt").scaled(80, 80));
    }
}

bool MusicRemoteWidgetForComplexStyle::showArtPicture(const QString &name)
{
    QPixmap originPath(QString(ART_DIR_FULL + name + SKN_FILE));
    if(!originPath.isNull())
    {
        m_iconLabel->setPixmap(originPath.scaled(80, 80));
        return true;
    }
    return false;
}
