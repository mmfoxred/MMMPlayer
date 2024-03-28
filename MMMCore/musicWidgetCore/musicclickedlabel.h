#ifndef MUSICCLICKEDLABEL_H
#define MUSICCLICKEDLABEL_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QLabel>
#include "musicglobaldefine.h"

/*! @brief The class of the label widget that can click.
 */
class MUSIC_WIDGET_EXPORT MusicClickedLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MusicClickedLabel(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */

Q_SIGNALS:
    void clicked();
    /*!
     * Click the label emit.
     */

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    /*!
     * Override the widget event.
     */

};

#endif // MUSICCLICKEDLABEL_H
