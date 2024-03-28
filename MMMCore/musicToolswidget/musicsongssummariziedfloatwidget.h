#ifndef MUSICSONGSSUMMARIZIEDFLOATWIDGET_H
#define MUSICSONGSSUMMARIZIEDFLOATWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QTimer>
#include <QLabel>
#include "musicglobaldefine.h"

class QPropertyAnimation;

/*! @brief The class of the songs summarizied float function widget.
 */
class MUSIC_TOOL_EXPORT MusicSongsSummariziedFloatWidget : public QLabel
{
    Q_OBJECT
public:
    explicit MusicSongsSummariziedFloatWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicSongsSummariziedFloatWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setGeometry(QObject *object);
    /*!
     * Set current geometry position.
     */

Q_SIGNALS:
    void musicSearch();
    /*!
     * Show searched text widget.
     */
    void musicCurrentPlayLocation();
    /*!
     * Show current play index.
     */
    void deleteObject();
    /*!
     * Delete self object.
     */

private Q_SLOTS:
    void leaveTimeout();
    /*!
     * Leave Time out.
     */
    void animationFinished();
    /*!
     * Animation finished.
     */

protected:
    void start(bool play, int end);
    /*!
     * Start to turn on animation.
     */
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    /*!
     * Override the widget event.
     */

    QTimer m_timer;
    QPropertyAnimation *m_animation;
    float m_currentAnimationValue;

};

#endif // MUSICSONGSSUMMARIZIEDFLOATWIDGET_H
