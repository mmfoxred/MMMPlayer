#include "musicenhancedwidget.h"
#include "musicsettingmanager.h"
#include "musicuiobject.h"
#include "musicMMMuiobject.h"
#include "musicapplicationobject.h"

#include <QLabel>
#include <QButtonGroup>
#include <QPropertyAnimation>

#define LABEL_ANIMAT_WIDGET 156
#define LABEL_BUTTON_WIDGET 116
#define LABEL_BUTTON_HEIGHT 111

MusicEnhancedToolButton::MusicEnhancedToolButton(QWidget *parent)
    : QToolButton(parent)
{
    m_state = false;

    m_animationLabel = new QLabel(this);
    m_animationLabel->setGeometry(-LABEL_ANIMAT_WIDGET, 0, LABEL_ANIMAT_WIDGET, LABEL_BUTTON_HEIGHT);
    m_animationLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    m_foreLabel = new QLabel(this);
    m_foreLabel->setObjectName("ForeLabel");
    m_foreLabel->resize(LABEL_ANIMAT_WIDGET, LABEL_BUTTON_HEIGHT);

    m_animation = new QPropertyAnimation(m_animationLabel, "pos", this);
    m_animation->setDuration(500);
    m_animation->setStartValue(QPoint(-LABEL_ANIMAT_WIDGET, 0));
    m_animation->setEndValue(QPoint(LABEL_ANIMAT_WIDGET, 0));
    connect(m_animation, SIGNAL(finished()), SLOT(finished()));
}

MusicEnhancedToolButton::~MusicEnhancedToolButton()
{
    delete m_foreLabel;
    delete m_animationLabel;
    delete m_animation;
}

QString MusicEnhancedToolButton::getClassName()
{
    return staticMetaObject.className();
}

void MusicEnhancedToolButton::setStyleSheet(const QString &styleSheet, bool state)
{
    m_state = state;
    if(m_state)
    {
        m_animation->setDuration(2000);
        m_foreLabel->setStyleSheet(QString("#ForeLabel{%1}").arg(styleSheet));
        m_animationLabel->setStyleSheet("background-image:url(':/enhance/lb_selected')");
        QToolButton::setStyleSheet(QString("QToolButton{background-image:url(':/enhance/lb_blue');}"));
    }
    else
    {
        m_animation->setDuration(500);
        m_foreLabel->setStyleSheet(QString());
        m_animationLabel->setStyleSheet("background-image:url(':/enhance/lb_enter')");
        QToolButton::setStyleSheet(QString("QToolButton{%1}").arg(styleSheet));
    }
}

void MusicEnhancedToolButton::start()
{
    m_animation->start();
}

void MusicEnhancedToolButton::stop()
{
    m_animation->stop();
}

void MusicEnhancedToolButton::finished()
{
    if(m_state)
    {
        start();
    }
}

void MusicEnhancedToolButton::enterEvent(QEvent *event)
{
    QToolButton::enterEvent(event);
    if(!m_state)
    {
        start();
    }
}


MusicEnhancedWidget::MusicEnhancedWidget(QWidget *parent)
    : MusicToolMenuWidget(parent)
{
    setToolTip(tr("magic music"));

    initWidget();

    connect(MusicApplicationObject::instance(), SIGNAL(enhancedMusicChanged(int)),
                                                SLOT(setEnhancedMusicConfig(int)));
    connect(m_menu, SIGNAL(windowStateChanged(bool)), SLOT(buttonAnimationChanged(bool)));
}

MusicEnhancedWidget::~MusicEnhancedWidget()
{
    delete m_caseButton;
    while(!m_buttons.isEmpty())
    {
        delete m_buttons.takeLast();
    }
}

QString MusicEnhancedWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicEnhancedWidget::setEnhancedMusicConfig(int type)
{
    setObjectName("EnhancedWidget");
    QString style = MusicUIObject::MKGBtnMagic;
    switch(type)
    {
        case 0: style += "#EnhancedWidget{ margin-left: -2px; }"; break;
        case 1: style += "#EnhancedWidget{ margin-left: -46px; }"; break;
        case 2: style += "#EnhancedWidget{ margin-left: -178px; }"; break;
        case 3: style += "#EnhancedWidget{ margin-left: -90px; }"; break;
        case 4: style += "#EnhancedWidget{ margin-left: -134px; }"; break;
    }
    setStyleSheet( style );

    QString prfix = QString("background-image:url(':/enhance/lb_%1')");
    m_caseButton->setStyleSheet(type ? MusicUIObject::MKGEnhanceOn : MusicUIObject::MKGEnhanceOff);
    m_buttons[0]->setStyleSheet(prfix.arg(type == 1 ? "3dOn" : "3dOff"), type == 1);
    m_buttons[1]->setStyleSheet(prfix.arg(type == 2 ? "NICAMOn" : "NICAMOff"), type == 2);
    m_buttons[2]->setStyleSheet(prfix.arg(type == 3 ? "subwooferOn" : "subwooferOff"), type == 3);
    m_buttons[3]->setStyleSheet(prfix.arg(type == 4 ? "vocalOn" : "vocalOff"), type == 4);

    m_lastSelectedIndex = (type == 0) ? m_lastSelectedIndex : type;
    M_SETTING_PTR->setValue(MusicSettingManager::EqualizerEnableChoiced, 0);
    M_SETTING_PTR->setValue(MusicSettingManager::EnhancedMusicChoiced, type);
    emit enhancedMusicChanged(type);

    m_menu->close();
}

void MusicEnhancedWidget::caseButtonOnAndOff()
{
    setEnhancedMusicConfig( m_caseButton->styleSheet().contains(":/enhance/btn_magic_off_normal") ?
                            m_lastSelectedIndex : 0);
}

void MusicEnhancedWidget::buttonAnimationChanged(bool state)
{
    int index = M_SETTING_PTR->value(MusicSettingManager::EnhancedMusicChoiced).toInt();
    if(index < 1 || index > m_buttons.count())
    {
        return;
    }

    state ? m_buttons[index - 1]->start() : m_buttons[index - 1]->stop();
}

void MusicEnhancedWidget::initWidget()
{
    m_menu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint);
    m_menu->setAttribute(Qt::WA_TranslucentBackground);
    m_menu->setStyleSheet(MusicUIObject::MMenuStyle05);

    m_containWidget->setFixedSize(272, 370);
    m_containWidget->setObjectName("containWidget");
    m_containWidget->setStyleSheet(QString("#containWidget{%1%2}").arg(MusicUIObject::MCustomStyle05)
                                                   .arg("background:url(':/enhance/lb_background')"));

    QToolButton *labelButton = new QToolButton(m_containWidget);
    labelButton->setGeometry(80, 20, 126, 40);
    labelButton->setStyleSheet(MusicUIObject::MKGEnhanceTitle);
    labelButton->setCursor(Qt::PointingHandCursor);

    QToolButton *helpButton = new QToolButton(m_containWidget);
    helpButton->setGeometry(205, 3, 24, 24);
    helpButton->setStyleSheet(MusicUIObject::MKGEnhanceHelp);
    helpButton->setCursor(Qt::PointingHandCursor);

    QToolButton *shareButton = new QToolButton(m_containWidget);
    shareButton->setGeometry(230, 3, 24, 24);
    shareButton->setStyleSheet(MusicUIObject::MKGEnhanceShare);
    shareButton->setCursor(Qt::PointingHandCursor);

    QToolButton *closeButton = new QToolButton(m_containWidget);
    closeButton->setGeometry(255, 8, 16, 16);
    closeButton->setStyleSheet(MusicUIObject::MKGEnhanceClose);
    closeButton->setCursor(Qt::PointingHandCursor);
    connect(closeButton, SIGNAL(clicked()), m_menu, SLOT(close()));

    m_caseButton = new QToolButton(m_containWidget);
    m_caseButton->setGeometry(200, 70, 62, 38);
    m_caseButton->setStyleSheet(MusicUIObject::MKGEnhanceOn);
    m_caseButton->setCursor(Qt::PointingHandCursor);

    MusicEnhancedToolButton *button1 = new MusicEnhancedToolButton(m_containWidget);
    button1->setGeometry(15, 115, LABEL_BUTTON_WIDGET, LABEL_BUTTON_HEIGHT);
    button1->setStyleSheet("background-image:url(':/enhance/lb_3dOff')");
    button1->setCursor(Qt::PointingHandCursor);

    MusicEnhancedToolButton *button2 = new MusicEnhancedToolButton(m_containWidget);
    button2->setGeometry(145, 115, LABEL_BUTTON_WIDGET, LABEL_BUTTON_HEIGHT);
    button2->setStyleSheet("background-image:url(':/enhance/lb_NICAMOff')");
    button2->setCursor(Qt::PointingHandCursor);

    MusicEnhancedToolButton *button3 = new MusicEnhancedToolButton(m_containWidget);
    button3->setGeometry(15, 240, LABEL_BUTTON_WIDGET, LABEL_BUTTON_HEIGHT);
    button3->setStyleSheet("background-image:url(':/enhance/lb_subwooferOff')");
    button3->setCursor(Qt::PointingHandCursor);

    MusicEnhancedToolButton *button4 = new MusicEnhancedToolButton(m_containWidget);
    button4->setGeometry(145, 240, LABEL_BUTTON_WIDGET, LABEL_BUTTON_HEIGHT);
    button4->setStyleSheet("background-image:url(':/enhance/lb_vocalOff')");
    button4->setCursor(Qt::PointingHandCursor);

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(button1, 1);
    group->addButton(button2, 2);
    group->addButton(button3, 3);
    group->addButton(button4, 4);
    connect(group, SIGNAL(buttonClicked(int)), SLOT(setEnhancedMusicConfig(int)));

    m_buttons << button1 << button2 << button3 << button4;

    m_lastSelectedIndex = M_SETTING_PTR->value(MusicSettingManager::EnhancedMusicChoiced).toInt();
    connect(m_caseButton, SIGNAL(clicked()), SLOT(caseButtonOnAndOff()));
}
