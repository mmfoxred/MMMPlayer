#ifndef MUSICCONNECTMOBILEWIDGET_H
#define MUSICCONNECTMOBILEWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "musicglobaldefine.h"

class MusicAnimationStackedWidget;

/*! @brief The class of the connect mobile widget.
 */
class MUSIC_TOOL_EXPORT MusicConnectMobileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicConnectMobileWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicConnectMobileWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */

private Q_SLOTS:
    void changeStatckedWidgetFirst();
    /*!
     * Change to main widget.
     */
    void changeStatckedWidgetSecond();
    /*!
     * Change to wireless widget.
     */
    void changeStatckedWidgetThird();
    /*!
     * Change to wire widget.
     */
    void openTransferFiles2Mobile();
    /*!
     * Open transfer files to mobile widget.
     */
    void openTransferFiles2Wifi();
    /*!
     * Open transfer files to wifi widget.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Override the widget event.
     */
    void initFirstWidget();
    /*!
     * Init main widget.
     */
    void initSecondWidget();
    /*!
     * Init connect to wireless widget.
     */
    void initThirdWidget();
    /*!
     * Init connect to wire widget.
     */

    MusicAnimationStackedWidget *m_stackedWidget;

};

#endif // MUSICCONNECTMOBILEWIDGET_H
