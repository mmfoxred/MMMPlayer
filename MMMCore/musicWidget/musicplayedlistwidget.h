#ifndef MUSICPLAYEDLISTWIDGET_H
#define MUSICPLAYEDLISTWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musictoolmenuwidget.h"

class QLabel;

/*! @brief The class of the played list widget.
 */
class MUSIC_WIDGET_EXPORT MusicPlayedListWidget : public MusicToolMenuWidget
{
    Q_OBJECT
public:
    explicit MusicPlayedListWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicPlayedListWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */

    void setPlayListCount(int count);

protected:
    void initWidget();
    /*!
     * Create all widget in layout.
     */

    QList<QLabel*> m_labels;

};

#endif // MUSICPLAYEDLISTWIDGET_H
