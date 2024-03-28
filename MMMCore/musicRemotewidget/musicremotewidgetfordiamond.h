#ifndef MUSICREMOTEWIDGETFORDIAMOND_H
#define MUSICREMOTEWIDGETFORDIAMOND_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicremotewidget.h"

/*! @brief The class of the desktop diamond remote widget.
 */
class MUSIC_REMOTE_EXPORT MusicRemoteWidgetForDiamond : public MusicRemoteWidget
{
    Q_OBJECT
public:
    explicit MusicRemoteWidgetForDiamond(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    /*!
     * Override the widget event.
     */

};

#endif // MUSICREMOTEWIDGETFORDIAMOND_H
