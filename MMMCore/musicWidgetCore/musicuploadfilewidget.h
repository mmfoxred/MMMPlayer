#ifndef MUSICUPLOADFILEWIDGET_H
#define MUSICUPLOADFILEWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "musicglobaldefine.h"

/*! @brief The class of the upload file widget.
 */
class MusicUploadFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicUploadFileWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */

    void adjustRect(int w, int h);
    /*!
     * Adjust the widget rect in the parent widget.
     */

Q_SIGNALS:
    void uploadFileClicked();
    /*!
     * Upload file button clicked.
     */
    void uploadFilesClicked();
    /*!
     * Upload files(dir) button clicked.
     */

};

#endif // MUSICUPLOADFILEWIDGET_H
