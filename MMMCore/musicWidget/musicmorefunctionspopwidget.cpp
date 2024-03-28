#include "musicmorefunctionspopwidget.h"
#include "musicsongsharingwidget.h"
#include "musicuiobject.h"

MusicMoreFunctionsPopWidget::MusicMoreFunctionsPopWidget(QWidget *parent)
    : MusicToolMenuWidget(parent)
{
    initWidget();
}

QString MusicMoreFunctionsPopWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicMoreFunctionsPopWidget::setCurrentSongName(const QString &name)
{
    m_currentSongName = name;
}

void MusicMoreFunctionsPopWidget::musicFunctionClicked(QAction *index)
{
    switch(index->data().toInt())
    {
        case 0:
            {
                break;
            }
        case 1:
            {
                emit musicSimilarFound(m_currentSongName);
                break;
            }
        case 2:
            {
                break;
            }
        case 3:
            {
                MusicSongSharingWidget shareWidget;
                shareWidget.setSongName(m_currentSongName);
                shareWidget.exec();
                break;
            }
        case 4:
            {
                emit musicSongMovieClicked(m_currentSongName);
                break;
            }
        default: break;
    }
}

void MusicMoreFunctionsPopWidget::initWidget()
{
    m_menu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint);
    m_menu->setAttribute(Qt::WA_TranslucentBackground);
    m_menu->setStyleSheet(MusicUIObject::MMenuStyle03);

    m_containWidget->setFixedSize(140, 160);
    m_menu->removeAction(m_menu->actions().first());

    QActionGroup *group = new QActionGroup(this);
    group->addAction(m_menu->addAction(QIcon(":/functions/btn_message_hover"), tr("message")))->setData(0);
    group->addAction(m_menu->addAction(QIcon(":/functions/btn_similar_hover"), tr("similar")))->setData(1);
    group->addAction(m_menu->addAction(QIcon(":/functions/btn_ablum_hover"), tr("ablum")))->setData(2);
    group->addAction(m_menu->addAction(QIcon(":/functions/btn_share_hover"), tr("share")))->setData(3);
    group->addAction(m_menu->addAction(QIcon(":/functions/btn_mv_hover"), tr("showMv")))->setData(4);
    connect(group, SIGNAL(triggered(QAction*)), SLOT(musicFunctionClicked(QAction*)));
}
