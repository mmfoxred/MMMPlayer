#ifndef MUSICLRCSEARCHWIDGET_H
#define MUSICLRCSEARCHWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicabstractmovedialog.h"

namespace Ui {
class MusicLrcSearchWidget;
}

/*! @brief The class of the lrc search widget.
 */
class MUSIC_LRC_EXPORT MusicLrcSearchWidget : public MusicAbstractMoveDialog
{
    Q_OBJECT
public:
    explicit MusicLrcSearchWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicLrcSearchWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */

public Q_SLOTS:
    void lrcSearchFinished() const;
    /*!
     * Set lrc search finished.
     */
    void lrcSearchButtonClicked() const;
    /*!
     * Lrc search button clicked.
     */
    void lrcSearchDownloadClicked();
    /*!
     * Lrc search download clicked.
     */
    void lrcDownloadStateChanged(const QString &string);
    /*!
     * Lrc download state is finished.
     */
    void setCurrentSongName(const QString &name) const;
    /*!
     * Set current song name.
     */
    virtual int exec();
    /*!
     * Override exec function.
     */

protected:
    Ui::MusicLrcSearchWidget *ui;

};

#endif // MUSICLRCSEARCHWIDGET_H
