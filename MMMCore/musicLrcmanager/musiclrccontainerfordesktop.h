#ifndef MUSICLRCCONTAINERFORDESKTOP_H
#define MUSICLRCCONTAINERFORDESKTOP_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musiclrccontainer.h"

#define TOOLBAR_HEIGHT      23
#define TOOLBAR_TEXT_LENGTH 58
#define TOOLBAR_WIDTH       600

class QPushButton;
class QToolButton;
class MusicLRCManagerForDesktop;

/*! @brief The class of the desktop lrc container.
 */
class MUSIC_LRC_EXPORT MusicLrcContainerForDesktop : public MusicLrcContainer
{
    Q_OBJECT
public:
    explicit MusicLrcContainerForDesktop(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicLrcContainerForDesktop();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    virtual void startTimerClock() override;
    /*!
     * Start timer clock to draw lrc.
     */
    virtual void stopLrcMask() override;
    /*!
     * Stop timer clock to draw lrc.
     */
    virtual void setMaskLinearGradientColor(QColor = CL_Mask) const override;
    /*!
     * Set mask linear gradient color.
     */
    virtual void setSettingParameter() override;
    /*!
     * Set setting parameter.
     */

    void showPlayStatus(bool status) const;
    /*!
     * Set current play state button.
     */
    void initCurrentLrc() const;
    /*!
     * Init current lrc when the first show.
     */
    void updateCurrentLrc(const QString &first, const QString &second, qint64 time);
    /*!
     * Update current lrc by first and second and time.
     */

Q_SIGNALS:
    void desktopLrcClosed();
    /*!
     * Desktop lrc close state changed emit.
     */
    void setWindowLockedChanged(bool lock);
    /*!
     * Lock current desktop lrc state changed emit.
     */

public Q_SLOTS:
    void setWindowLockedChanged();
    /*!
     * Lock current desktop lrc state changed.
     */
    void setLrcBiggerChanged();
    /*!
     * Set lrc bigger changed.
     */
    void setLrcSmallerChanged();
    /*!
     * Set lrc smaller changed.
     */

protected:
    void setSelfGeometry() const;
    /*!
     * Set self geometry.
     */
    void creatToolBarWidget();
    /*!
     * Creat toolBar widget.
     */
    void resizeLrcSizeArea();
    /*!
     * Resize lrc size area by change size.
     */
    void resizeLrcSizeArea(bool resize);
    /*!
     * Resize lrc size area to bigger or smaller.
     */
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    /*!
     * Override the widget event.
     */

    bool m_windowLocked, m_reverse;
    int m_currentLrcFontSize;
    QPoint m_offset, m_geometry;

    QWidget *m_supperClass, *m_toolBarWidget;
    QToolButton *m_toolPlayButton;

};

#endif // MUSICLRCCONTAINERFORDESKTOP_H
