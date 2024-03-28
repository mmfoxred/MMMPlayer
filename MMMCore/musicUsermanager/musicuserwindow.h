#ifndef MUSICUSERWINDOW_H
#define MUSICUSERWINDOW_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QStackedWidget>
#include "musicglobaldefine.h"

class MusicUserDialog;
class MusicUserManager;

namespace Ui {
class MusicUserWindow;
}

/*! @brief The class of the user window.
 */
class MUSIC_USER_EXPORT MusicUserWindow : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MusicUserWindow(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicUserWindow();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    bool isUserLogin() const;
    /*!
     * Check if the user is login now.
     */

public Q_SLOTS:
    void musicUserLogin();
    /*!
     * User widget button clicked.
     */
    void userStateChanged(const QString &uid, const QString &icon);
    /*!
     * User login state changed.
     */
    void musicUserContextLogin();
    /*!
     * Send user to login.
     */
    void checkToAutoLogin();
    /*!
     * Check current user to login auto automatic.
     */

protected:
    bool connectDatabase();
    /*!
     * Connect to database.
     */
    bool disConnectDatabase();
    /*!
     * Disconnect to database.
     */

    Ui::MusicUserWindow *ui;
    MusicUserManager *m_userManager;

};

#endif // MUSICUSERWINDOW_H
