#ifndef MUSICROUNDANIMATIONLABEL_H
#define MUSICROUNDANIMATIONLABEL_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QTimer>
#include <QWidget>
#include "musicglobaldefine.h"

/*! @brief The class of the round animation widget.
 */
class MUSIC_WIDGET_EXPORT MusicRoundAnimationLabel : public QWidget
{
    Q_OBJECT
public:
    explicit MusicRoundAnimationLabel(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicRoundAnimationLabel();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setPixmap(const QPixmap &pix);
    /*!
     * Set rotating widget background pixmap.
     */
    void setInterval(int value);
    /*!
     * Set rotating widget interval.
     */

public Q_SLOTS:
    void start();
    /*!
     * Start to rotating widget.
     */
    void stop();
    /*!
     * Stop to rotating widget.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    /*!
     * Override the widget event.
     */

    QPixmap m_pixmap;
    QTimer m_timer;
    int m_rotateAngle;

};

#endif // MUSICROUNDANIMATIONLABEL_H
