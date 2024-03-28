#ifndef MUSICMOREFUNCTIONSPOPWIDGET_H
#define MUSICMOREFUNCTIONSPOPWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musictoolmenuwidget.h"

/*! @brief The class of the more functions popup widget.
 */
class MUSIC_WIDGET_EXPORT MusicMoreFunctionsPopWidget : public MusicToolMenuWidget
{
    Q_OBJECT
public:
    explicit MusicMoreFunctionsPopWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */

    void setCurrentSongName(const QString &name);
    /*!
     * Set current song name.
     */

Q_SIGNALS:
    void musicSongMovieClicked(const QString &text);
    /*!
     * Video search that by string.
     */
    void musicSimilarFound(const QString &text);
    /*!
     * Music similar function that by string.
     */

private Q_SLOTS:
    void musicFunctionClicked(QAction *index);
    /*!
     * Music function button clicked.
     */

protected:
    void initWidget();
    /*!
     * Create all widget in layout.
     */

    QString m_currentSongName;

};

#endif // MUSICMOREFUNCTIONSPOPWIDGET_H
