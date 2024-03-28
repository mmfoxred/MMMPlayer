#ifndef MUSICREMOTEWIDGETFORSQUARE_H
#define MUSICREMOTEWIDGETFORSQUARE_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicremotewidget.h"

/*! @brief The class of the desktop square remote widget.
 */
class MUSIC_REMOTE_EXPORT MusicRemoteWidgetForSquare : public MusicRemoteWidget
{
    Q_OBJECT
public:
    explicit MusicRemoteWidgetForSquare(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicRemoteWidgetForSquare();

    static QString getClassName();
    /*!
     * Get class object name.
     */

public Q_SLOTS:
    void enterTimeout();
    /*!
     * Mouse enter the geometry time out.
     */
    void leaveTimeout();
    /*!
     * Mouse leave the geometry time out.
     */

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    /*!
     * Override the widget event.
     */

    QGraphicsOpacityEffect *m_effect[4];
    QTimer m_enterTimer;
    QTimer m_leaveTimer;
    float m_interval;

};

#endif // MUSICREMOTEWIDGETFORSQUARE_H
