#ifndef MUSICREMOTEWIDGETFORRECTANGLE_H
#define MUSICREMOTEWIDGETFORRECTANGLE_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicremotewidget.h"

class MusicMarqueeWidget;

/*! @brief The class of the desktop rectangle remote widget.
 */
class MUSIC_REMOTE_EXPORT MusicRemoteWidgetForRectangle : public MusicRemoteWidget
{
    Q_OBJECT
public:
    explicit MusicRemoteWidgetForRectangle(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicRemoteWidgetForRectangle();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    virtual void setLabelText(const QString &value) override;
    /*!
     * Set current song text.
     */

protected:
    MusicMarqueeWidget *m_songNameLabel;
    QWidget *m_toolWidget;

};

#endif // MUSICREMOTEWIDGETFORRECTANGLE_H
