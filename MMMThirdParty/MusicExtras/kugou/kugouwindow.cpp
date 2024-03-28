#include "kugouwindow.h"
#include "kugouuiobject.h"

#ifdef MUSIC_WEBKIT
# ifdef MUSIC_GREATER_NEW
#  include <QtWebKitWidgets/QWebView>
#  include <QtWebKitWidgets/QWebFrame>
# else
#  include <QWebView>
#  include <QWebFrame>
# endif
#endif
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QButtonGroup>

class KugouWindowPrivate : public MMMPrivate<KugouWindow>
{
public:
    KugouWindowPrivate();
    ~KugouWindowPrivate();

    QWidget *m_webView, *m_topWidget;
    QButtonGroup *m_buttonGroup;
};

KugouWindowPrivate::KugouWindowPrivate()
{
    m_buttonGroup = nullptr;
    m_topWidget = nullptr;
    m_webView = nullptr;
}

KugouWindowPrivate::~KugouWindowPrivate()
{
    delete m_buttonGroup;
    delete m_topWidget;
    delete m_webView;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
///

KugouWindow::KugouWindow(KuGouType type, QWidget *parent)
    : QWidget(parent)
{
    MMM_INIT_PRIVATE;
    switch(type)
    {
        case KuGouSong:
                createKugouSongWidget();
                break;
        case KuGouRadio:
                createKugouRadioWidget();
                break;
        case KuGouList:
                createKugouListWidget();
                break;
        case KugouMv:
                createKugouMVWidget();
                break;
        case KuGouLive: break;
        case KuGouLrc: break;
    }
}

QString KugouWindow::getClassName()
{
    return staticMetaObject.className();
}

void KugouWindow::kugouSongIndexChanged(int index)
{
    MMM_D(KugouWindow);
    changeClickedButtonStyle(index);
    QString url = KugouUrl::getSongRecommendUrl();
    switch(index)
    {
        case 0: url = KugouUrl::getSongRecommendUrl(); break;
        case 1: url = KugouUrl::getSongRankUrl(); break;
        case 2: url = KugouUrl::getSongSingerUrl(); break;
        case 3: url = KugouUrl::getSongCategoryUrl(); break;
        case 4: url = KugouUrl::getSongShowUrl(); break;
        case 5: url = KugouUrl::getSongHeroesUrl(); break;
    }
#ifdef MUSIC_WEBKIT
    static_cast<QWebView*>(d->m_webView)->setUrl(QUrl( url ));
#endif
}

void KugouWindow::kugouRadioIndexChanged(int index)
{
    MMM_D(KugouWindow);
    changeClickedButtonStyle(index);
    QString url = KugouUrl::getRadioPublicUrl();
    switch(index)
    {
        case 0: url = KugouUrl::getRadioPublicUrl(); break;
        case 1: url = KugouUrl::getRadioHighFmUrl(); break;
        case 2: url = KugouUrl::getRadioFxUrl(); break;
        case 3: url = KugouUrl::getRadioHomeUrl(); break;
    }
#ifdef MUSIC_WEBKIT
    static_cast<QWebView*>(d->m_webView)->setUrl(QUrl( url ));
#endif
}

void KugouWindow::kugouMVIndexChanged(int index)
{
    MMM_D(KugouWindow);
    changeClickedButtonStyle(index);
    QString url = KugouUrl::getMVRadioUrl();
    switch(index)
    {
        case 0: url = KugouUrl::getMVRadioUrl(); break;
        case 1: url = KugouUrl::getMVRecommendUrl(); break;
        case 2: url = KugouUrl::getMVFanxingUrl(); break;
        case 3: url = KugouUrl::getMVStarMusicUrl(); break;
    }
#ifdef MUSIC_WEBKIT
    static_cast<QWebView*>(d->m_webView)->setUrl(QUrl( url ));
#endif
}

void KugouWindow::createKugouSongWidget()
{
    MMM_D(KugouWindow);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
#ifdef MUSIC_WEBKIT
    d->m_topWidget = new QWidget(this);
    d->m_topWidget->setFixedHeight(25);
    d->m_topWidget->setStyleSheet(MusicUIObject::MPushButtonStyle01 + MusicUIObject::MWidgetStyle01);
    QHBoxLayout *topLayout = new QHBoxLayout(d->m_topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(25);

    d->m_buttonGroup = new QButtonGroup(this);
    QPushButton *bt = new QPushButton(tr(" SongRecommend "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 0);
    bt = new QPushButton(tr(" SongRank "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 1);
    bt = new QPushButton(tr(" SongSinger "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 2);
    bt = new QPushButton(tr(" SongCategory "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 3);
    bt = new QPushButton(tr(" SongShow "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 4);
    bt = new QPushButton(tr(" SongHeroes "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 5);
    connect(d->m_buttonGroup, SIGNAL(buttonClicked(int)), SLOT(kugouSongIndexChanged(int)));

    topLayout->addStretch(1);
    topLayout->addWidget(d->m_buttonGroup->button(0));
    topLayout->addWidget(d->m_buttonGroup->button(1));
    topLayout->addWidget(d->m_buttonGroup->button(2));
    topLayout->addWidget(d->m_buttonGroup->button(3));
    topLayout->addWidget(d->m_buttonGroup->button(4));
    topLayout->addWidget(d->m_buttonGroup->button(5));
    topLayout->addStretch(1);

    QWebView *view = new QWebView(this);
    view->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);

    layout->addWidget(d->m_topWidget);
    layout->addWidget(d->m_webView = view);

    kugouSongIndexChanged(0);
#else
    QLabel *pix = new QLabel(this);
    pix->setPixmap(QPixmap(":/image/lb_no_webkit_song"));
    layout->addWidget(pix);
#endif
    setLayout(layout);
}

void KugouWindow::createKugouRadioWidget()
{
    MMM_D(KugouWindow);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
#ifdef MUSIC_WEBKIT
    d->m_topWidget = new QWidget(this);
    d->m_topWidget->setFixedHeight(25);
    d->m_topWidget->setStyleSheet(MusicUIObject::MPushButtonStyle01 + MusicUIObject::MWidgetStyle01);
    QHBoxLayout *topLayout = new QHBoxLayout(d->m_topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(50);

    d->m_buttonGroup = new QButtonGroup(this);
    QPushButton *bt = new QPushButton(tr(" RadioPublic "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 0);
    bt = new QPushButton(tr(" RadioHigh "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 1);
    bt = new QPushButton(tr(" RadioFx "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 2);
    bt = new QPushButton(tr(" RadioHome "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 3);
    connect(d->m_buttonGroup, SIGNAL(buttonClicked(int)), SLOT(kugouRadioIndexChanged(int)));

    topLayout->addStretch(1);
    topLayout->addWidget(d->m_buttonGroup->button(0));
    topLayout->addWidget(d->m_buttonGroup->button(1));
    topLayout->addWidget(d->m_buttonGroup->button(2));
    topLayout->addWidget(d->m_buttonGroup->button(3));
    topLayout->addStretch(1);

    QWebView *view = new QWebView(this);
    view->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);

    layout->addWidget(d->m_topWidget);
    layout->addWidget(d->m_webView = view);

    kugouRadioIndexChanged(0);
#else
    QLabel *pix = new QLabel(this);
    pix->setPixmap(QPixmap(":/image/lb_no_webkit_radio"));
    layout->addWidget(pix);
#endif
    setLayout(layout);
}

void KugouWindow::createKugouListWidget()
{
    MMM_D(KugouWindow);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
#ifdef MUSIC_WEBKIT
    QWebView *view = new QWebView(this);
    view->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    view->setUrl(QUrl( KugouUrl::getListUrl() ));
    layout->addWidget(d->m_webView = view);
#else
    QLabel *pix = new QLabel(this);
    pix->setPixmap(QPixmap(":/image/lb_no_webkit_list"));
    layout->addWidget(pix);
#endif
    setLayout(layout);
}

void KugouWindow::createKugouMVWidget()
{
    MMM_D(KugouWindow);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
#ifdef MUSIC_WEBKIT
    d->m_topWidget = new QWidget(this);
    d->m_topWidget->setFixedHeight(25);
    d->m_topWidget->setStyleSheet(MusicUIObject::MPushButtonStyle01 + MusicUIObject::MWidgetStyle01);
    QHBoxLayout *topLayout = new QHBoxLayout(d->m_topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(50);

    d->m_buttonGroup = new QButtonGroup(this);
    QPushButton *bt = new QPushButton(tr(" MVRadio "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 0);
    bt = new QPushButton(tr(" MVRecommend "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 1);
    bt = new QPushButton(tr(" MVFanxing "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 2);
    bt = new QPushButton(tr(" MVStarMusic "), d->m_topWidget);
    bt->setCursor(QCursor(Qt::PointingHandCursor));
    d->m_buttonGroup->addButton(bt, 3);
    connect(d->m_buttonGroup, SIGNAL(buttonClicked(int)), SLOT(kugouMVIndexChanged(int)));

    topLayout->addStretch(1);
    topLayout->addWidget(d->m_buttonGroup->button(0));
    topLayout->addWidget(d->m_buttonGroup->button(1));
    topLayout->addWidget(d->m_buttonGroup->button(2));
    topLayout->addWidget(d->m_buttonGroup->button(3));
    topLayout->addStretch(1);

    QWebView *view = new QWebView(this);
    view->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);

    layout->addWidget(d->m_topWidget);
    layout->addWidget(d->m_webView = view);

    kugouMVIndexChanged(0);
#else
    QLabel *pix = new QLabel(this);
    pix->setPixmap(QPixmap(":/image/lb_no_webkit_mv"));
    layout->addWidget(pix);
#endif
    setLayout(layout);
}

void KugouWindow::changeClickedButtonStyle(int index)
{
    MMM_D(KugouWindow);
    for(int i=0; i<d->m_buttonGroup->buttons().count(); ++i)
    {
        d->m_buttonGroup->button(i)->setStyleSheet(MusicUIObject::MPushButtonStyle01);
    }
    d->m_buttonGroup->button(index)->setStyleSheet(MusicUIObject::MPushButtonStyle02);
}
