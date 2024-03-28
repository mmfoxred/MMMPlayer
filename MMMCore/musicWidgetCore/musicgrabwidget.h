#ifndef MUSICGRABWIDGET_H
#define MUSICGRABWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "musicglobaldefine.h"

/*! @brief The class of the grab area widget.
 */
class MUSIC_WIDGET_EXPORT MusicGrabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicGrabWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicGrabWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    /*!
     * Override the widget event.
     */

    QPoint m_ptCursor, m_ptStart, m_ptEnd;
    bool m_isDrawing;

};

#endif // MUSICGRABWIDGET_H
