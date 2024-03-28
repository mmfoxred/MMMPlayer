#ifndef MUSICLRCFLOATWIDGET_H
#define MUSICLRCFLOATWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicfloatabstractwidget.h"

class QPushButton;
class MusicLrcFloatPhotoWidget;
class MusicLrcFloatSettingWidget;

/*! @brief The class of the lrc float widget.
 */
class MUSIC_LRC_EXPORT MusicLrcFloatWidget : public MusicFloatAbstractWidget
{
    Q_OBJECT
public:
    explicit MusicLrcFloatWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicLrcFloatWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    virtual void resizeWindow(int width, int height) override;
    /*!
     * Resize window bound by given width and height.
     */

public Q_SLOTS:
    void showFloatSettingWidget();
    /*!
     * Show float setting widget.
     */
    void closeFloatSettingWidget();
    /*!
     * Close float setting widget.
     */

protected:
    QPushButton *m_more, *m_update, *m_search;
    QPushButton *m_wallp, *m_photo;
    MusicLrcFloatPhotoWidget *m_floatPhotoWidget;
    MusicLrcFloatSettingWidget *m_floatSettingWidget;

};

#endif // MUSICLRCFLOATWIDGET_H
