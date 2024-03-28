#include "musiclrcfloatwidget.h"
#include "musiclrcfloatphotowidget.h"
#include "musiclrcfloatsettingwidget.h"
#include "musicMMMuiobject.h"

#include <QPushButton>

MusicLrcFloatWidget::MusicLrcFloatWidget(QWidget *parent)
    : MusicFloatAbstractWidget(parent)
{
    setStyleSheet(MusicUIObject::MBackgroundStyle08);

    m_floatPhotoWidget = new MusicLrcFloatPhotoWidget(parent);
    m_floatPhotoWidget->hide();
    m_floatSettingWidget = new MusicLrcFloatSettingWidget(parent);
    m_floatSettingWidget->hide();

    resizeWindow(0, 0);
    m_update = new QPushButton(tr(" Update"), this);
    m_search = new QPushButton(tr(" Search"), this);
    m_more = new QPushButton(tr(" More"), this);
    m_wallp = new QPushButton(tr(" Wallp"), this);
    m_photo = new QPushButton(tr(" Photo"), this);

    m_update->setGeometry(15, 10, 80, 20);
    m_search->setGeometry(15, 50, 80, 20);
    m_more->setGeometry(15, 90, 80, 20);
    m_wallp->setGeometry(15, 130, 80, 20);
    m_photo->setGeometry(15, 170, 80, 20);

    m_update->setStyleSheet(MusicUIObject::MKGInlineFloatUpdate + MusicUIObject::MPushButtonStyle09 +
                            MusicUIObject::MPushButtonStyle01);
    m_search->setStyleSheet(MusicUIObject::MKGInlineFloatSearch + MusicUIObject::MPushButtonStyle09 +
                            MusicUIObject::MPushButtonStyle01);
    m_more->setStyleSheet(MusicUIObject::MKGInlineFloatMore + MusicUIObject::MPushButtonStyle09 +
                          MusicUIObject::MPushButtonStyle01);
    m_wallp->setStyleSheet(MusicUIObject::MKGInlineFloatWallpaper + MusicUIObject::MPushButtonStyle09 +
                           MusicUIObject::MPushButtonStyle01);
    m_photo->setStyleSheet(MusicUIObject::MKGInlineFloatPhoto + MusicUIObject::MPushButtonStyle09 +
                           MusicUIObject::MPushButtonStyle01);

    m_update->setCursor(QCursor(Qt::PointingHandCursor));
    m_search->setCursor(QCursor(Qt::PointingHandCursor));
    m_more->setCursor(QCursor(Qt::PointingHandCursor));
    m_wallp->setCursor(QCursor(Qt::PointingHandCursor));
    m_photo->setCursor(QCursor(Qt::PointingHandCursor));

    connect(m_update, SIGNAL(clicked()), parent, SIGNAL(theCurrentLrcUpdated()));
    connect(m_search, SIGNAL(clicked()), parent, SLOT(searchMusicLrcs()));
    connect(m_photo, SIGNAL(clicked()), m_floatPhotoWidget, SLOT(show()));
    connect(m_floatSettingWidget, SIGNAL(widgetClose()), SLOT(closeFloatSettingWidget()));
    connect(m_more, SIGNAL(clicked()), this, SLOT(showFloatSettingWidget()));
}

MusicLrcFloatWidget::~MusicLrcFloatWidget()
{
    delete m_more;
    delete m_update;
    delete m_search;
    delete m_wallp;
    delete m_photo;
    delete m_floatPhotoWidget;
    delete m_floatSettingWidget;
}

QString MusicLrcFloatWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicLrcFloatWidget::resizeWindow(int width, int height)
{
    m_rectIn = QRect(548 + width, 120 + height/2, 115, 210);
    m_rectOut = QRect(658 + width, 171 + height/2, 115, 105);
    setGeometry( m_rectOut );

    m_floatSettingWidget->resizeWindow(width, height);
    m_floatPhotoWidget->resizeWindow(width, height);
}

void MusicLrcFloatWidget::showFloatSettingWidget()
{
    animationOut();
    m_floatSettingWidget->show();
    setBlockAnimation(true);
}

void MusicLrcFloatWidget::closeFloatSettingWidget()
{
    m_floatSettingWidget->close();
    setBlockAnimation(false);
}
