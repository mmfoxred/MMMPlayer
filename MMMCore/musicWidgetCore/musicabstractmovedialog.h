#ifndef MUSICABSTRACTMOVEDIALOG_H
#define MUSICABSTRACTMOVEDIALOG_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#define WIDTH  20
#define HEIGHT 20

#include <QLabel>
#include <QDialog>
#include "musicglobaldefine.h"

/*! @brief The class of the moving dialog base.
 */
class MUSIC_WIDGET_EXPORT MusicAbstractMoveDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MusicAbstractMoveDialog(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicAbstractMoveDialog();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    inline void drawWindowShadow(bool show) { m_showShadow = show;}
    /*!
     * Set or not draw window bound shadow.
     */
    inline void blockMoveOption(bool block) { m_moveOption = block;}
    /*!
     * Set or not block widget moving.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    /*!
     * Override the widget event.
     */
    void setBackgroundPixmap(QLabel *label, const QSize &size);
    /*!
     * Set background pixmap.
     */

    QPoint m_pressAt;
    bool m_moveOption, m_showShadow;
    bool m_leftButtonPress;

};

#endif // MUSICABSTRACTMOVEDIALOG_H
