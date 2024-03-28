#ifndef MUSICSETTINGWIDGET_H
#define MUSICSETTINGWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicabstractmovedialog.h"
#include "musicuiobject.h"
#include "musicsettingmanager.h"
#include "musicabstracttablewidget.h"

class QComboBox;

namespace Ui {
class MusicSettingWidget;
}

/*! @brief The class of the list table widget.
 */
class MUSIC_WIDGET_EXPORT MusicFunctionTableWidget : public MusicAbstractTableWidget
{
    Q_OBJECT
public:
    explicit MusicFunctionTableWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicFunctionTableWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void addFunctionItems(int index, const QStringList &icon, const QStringList &path);
    /*!
     * Add table list items by index and icons and paths.
     */

Q_SIGNALS:
    void currentIndexChanged(int index);
    /*!
     * Current list index changed.
     */

public Q_SLOTS:
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Table widget list cell click.
     */

protected:
    virtual void leaveEvent(QEvent *event) override;
    /*!
     * Override the widget event.
     */

    int m_listIndex;
};


/*! @brief The class of the setting parameters widget.
 */
class MUSIC_WIDGET_EXPORT MusicSettingWidget : public MusicAbstractMoveDialog
{
    Q_OBJECT
public:
    enum Type
    {
        Inline, ///*lrc inline type*/
        Desktop ///*lrc desktop type*/
    };

    explicit MusicSettingWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicSettingWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void initControllerParameter();
    /*!
     * Init controller parameter to widget.
     */

Q_SIGNALS:
    void parameterSettingChanged();
    /*!
     * Parameters setting changed emit.
     */
    void soundEqualizerClicked();
    /*!
     * Sound equalizer button clicked.
     */

public Q_SLOTS:
    void clearFunctionTableSelection();
    /*!
     * Clear all function tables selection.
     */
    void globalHotkeyBoxChanged(bool state);
    /*!
     * Set global hotkey box changed.
     */
    void changeInlineLrcWidget();
    /*!
     * Change to inline lrc widget.
     */
    void changeDesktopLrcWidget();
    /*!
     * Change to desktop lrc widget.
     */

    void inlineLrcFgChanged();
    /*!
     * Inline lrc foreground change.
     */
    void inlineLrcBgChanged();
    /*!
     * Inline lrc background change.
     */
    void defaultLrcColorChanged(int index);
    /*!
     * Default lrc color change by index.
     */
    void inlineLrcTransChanged(int index);
    /*!
     * Inline lrc transparent changed by index.
     */
    void showInlineLrcDemo();
    /*!
     * Show inline lrc preview.
     */
    void resetInlineParameter();
    /*!
     * Reset inline parameter.
     */

    void desktopFgChanged();
    /*!
     * Desktop lrc foreground change.
     */
    void desktopBgChanged();
    /*!
     * Desktop lrc background change.
     */
    void defaultDesktopLrcColorChanged(int index);
    /*!
     * Default desktop lrc color change by index.
     */
    void desktopLrcTransChanged(int index);
    /*!
     * Desktop lrc transparent changed by index.
     */
    void showDesktopLrcDemo();
    /*!
     * Show desktop lrc preview.
     */
    void resetDesktopParameter();
    /*!
     * Reset desktop parameter.
     */

    void downloadGroupCached(int index);
    /*!
     * Set enable or disable download cache.
     */
    void downloadGroupSpeedLimit(int index);
    /*!
     * Set enable or disable download speed limit.
     */
    void downloadDirSelected(int index);
    /*!
     * Set select download dir or lrc dir.
     */

    void setNetworkProxyControl(int enable);
    /*!
     * Set network proxy control enabled or not.
     */
    void testNetworkProxy();
    /*!
     * Test current proxy available.
     */
    void testProxyStateChanged(bool state);
    /*!
     * Test current proxy available changed.
     */
    void testNetworkConnection();
    /*!
     * Test current network connection available.
     */
    void testNetworkConnectionStateChanged(const QString &name);
    /*!
     * Test current network connection available changed.
     */

    void soundEffectCheckBoxChanged();
    /*!
     * Sound effect checkBox changed.
     */
    void soundEffectValueChanged(int index);
    /*!
     * Sound effect button value changed.
     */

    void commitTheResults();
    /*!
     * Save the change results.
     */
    virtual int exec();
    /*!
     * Override exec function.
     */

protected:
    void initNormalSettingWidget();
    /*!
     * Init normal setting stack widget.
     */
    void initInlineLrcWidget();
    /*!
     * Init inline lrc stack widget.
     */
    void initDesktopLrcWidget();
    /*!
     * Init desktop lrc stack widget.
     */
    void initDownloadWidget();
    /*!
     * Init download stack widget.
     */
    void initSoundEffectWidget();
    /*!
     * Init sound effect stack widget.
     */
    void initNetworkWidget();
    /*!
     * Init network stack widget.
     */
    void lcrColorValue(Type key, const QString &type, QPushButton *obj);
    /*!
     * Set lrc color value by type and value type.
     */
    void lrcColorByDefault(Type key, int index);
    /*!
     * Set lrc default color by type and index.
     */
    void lrcTransparentValue(Type key, int value) const;
    /*!
     * Set lrc transparent by type and value.
     */
    bool applyNetworkProxy();
    /*!
     * Apply current proxy available.
     */
    bool setNetworkProxyByType(int type);
    /*!
     * Set network proxy by type.
     */

    Ui::MusicSettingWidget *ui;
    QColor m_lrcSelectedFg, m_lrcSelectedBg;
    QColor m_DlrcSelectedFg, m_DlrcSelectedBg;

};

#endif // MUSICSETTINGWIDGET_H
