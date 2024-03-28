#ifndef MUSICDESKTOPWALLPAPERTHREAD_H
#define MUSICDESKTOPWALLPAPERTHREAD_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QThread>
#include "musicobject.h"
#include "musicglobaldefine.h"

/*! @brief The class of the desktop wallpaper thread.
 */
class MUSIC_TOOLSET_EXPORT MusicDesktopWallpaperThread : public QThread
{
    Q_OBJECT
public:
    explicit MusicDesktopWallpaperThread(QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicDesktopWallpaperThread();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setParamters(const MusicObject::MStriantMap &p);
    /*!
     * Set paramters(Time\Type\Func\Close).
     */
    void stopAndQuitThread();
    /*!
     * Stop and quit current thread.
     */

public Q_SLOTS:
    void start();
    /*!
     * Strat thread now.
     */
    void run();
    /*!
     * Thread run now.
     */

protected:
    void setWallpaper(const QString &path, int type) const;
    /*!
     * Set desktop wallpaper.
     */

    bool m_run;
    bool m_returnToOrigin;
    int m_currentImageIndex;
    int m_originType;
    MusicObject::MStriantMap m_paramter;
    QString m_originPath;

};

#endif // MUSICDESKTOPWALLPAPERTHREAD_H
