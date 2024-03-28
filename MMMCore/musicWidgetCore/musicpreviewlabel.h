#ifndef MUSICPREVIEWLABEL_H
#define MUSICPREVIEWLABEL_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QLabel>
#include "musicglobaldefine.h"

/*! @brief The class of the setting preview label.
 */
class MUSIC_WIDGET_EXPORT MusicPreviewLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MusicPreviewLabel(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setParameter(const QStringList &para);
    /*!
     * Set preview parameters(Family\PointSize\Bold or Italic).
     */
    void setLinearGradient(QColor &fg, QColor &bg);
    /*!
     * Set linear gradient and fg and bg.
     */
    void setTransparent(int trans) { m_transparent = trans;}
    /*!
     * Set current transparent.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    /*!
     * Override the widget event.
     */

    QFont m_font;
    QLinearGradient m_linearGradient;
    QLinearGradient m_maskLinearGradient;
    int m_transparent;

};

#endif // MUSICPREVIEWLABEL_H
