#ifndef MUSICLRCMANAGERFORDESKTOP_H
#define MUSICLRCMANAGERFORDESKTOP_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musiclrcmanager.h"

/*! @brief The class of the desktop lrc manager.
 */
class MUSIC_LRC_EXPORT MusicLRCManagerForDesktop : public MusicLRCManager
{
    Q_OBJECT
public:
    explicit MusicLRCManagerForDesktop(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicLRCManagerForDesktop();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setSelfGeometry(const QPoint &point);
    /*!
     * Set self geometry by point.
     */
    void setSelfGeometry(int x, int y);
    /*!
     * Set self geometry by x and y.
     */
    int x() const;
    /*!
     * Get self geometry x.
     */
    int y() const;
    /*!
     * Get self geometry y.
     */
    void resetOrigin();
    /*!
     * Reset to origin state.
     */
    void setLrcFontSize(int size);
    /*!
     * Set adjust font szie by value.
     */
    inline int getFirstFontSize() const { return m_font.pointSize(); }
    /*!
     * Get current font szie.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    /*!
     * Override the widget event.
     */

};

#endif // MUSICLRCMANAGERFORDESKTOP_H
