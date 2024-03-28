#ifndef MUSICLEFTAREAWIDGET_H
#define MUSICLEFTAREAWIDGET_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QWidget>
#include "musicglobaldefine.h"

class MusicQualityChoiceWidget;

namespace Ui {
    class MusicApplication;
}

/*! @brief The class of the app left area widget.
 */
class MUSIC_GUI_EXPORT MusicLeftAreaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicLeftAreaWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    ~MusicLeftAreaWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */
    static MusicLeftAreaWidget *instance();
    /*!
     * Get class object instance.
     */
    void setupUi(Ui::MusicApplication* ui);
    /*!
     * Set up app ui.
     */
    void musictLoveStateClicked();
    /*!
     * Reset current music love icon state.
     */
    void switchToSelectedItemStyle(int index);
    /*!
     * Switch to selected item style.
     */

Q_SIGNALS:
    void currentLoveStateChanged();
    /*!
     * Current music love icon state changed.
     */
    void currentDownloadStateChanged();
    /*!
     * Current music download icon state changed.
     */

public Q_SLOTS:
    void musicDownloadSongToLocal();
    /*!
     * To download music data from net to load.
     */
    void musicDownloadSongFinished();
    /*!
     * To download music data from net finished.
     */
    void musicStackedSongListWidgetChanged();
    /*!
     * Change to song list widget.
     */
    void musicStackedToolsWidgetChanged();
    /*!
     * Change to tool sets widget.
     */
    void musicStackedRadioWidgetChanged();
    /*!
     * Change to radio widget.
     */
    void musicStackedMyDownWidgetChanged();
    /*!
     * Change to my download widget.
     */
    void musicStackedMobileWidgetChanged();
    /*!
     * Change to mobile widget.
     */
    void musicStackedCloudWidgetChanged();
    /*!
     * Change to shared cloud widget.
     */
    void musicAnalyzerSpectrumWidget();
    /*!
     * Show analyzer spectrum widget.
     */
    void musicProjectMSpectrumWidget();
    /*!
     * Show projectM spectrum widget.
     */

protected:
    Ui::MusicApplication *m_ui;
    QWidget *m_stackedWidget;
    MusicQualityChoiceWidget *m_qualityChoiceWidget;

    static MusicLeftAreaWidget *m_instance;
};

#endif // MUSICLEFTAREAWIDGET_H
