#include "qrcodewidget.h"

#include <QPainter>
#include <QPaintEvent>

class QRCodeQWidgetPrivate : public MMMPrivate<QRCodeQWidget>
{
public:
    QRCodeQWidgetPrivate();

    bool m_casesen;
    int m_margin;
    QString m_iconPath;
    qreal m_percent;
    QByteArray m_text;
    QColor m_foreground, m_background;
    QRencodeMode m_mode;
    QRecLevel m_level;

};

QRCodeQWidgetPrivate::QRCodeQWidgetPrivate()
{
    m_margin = 10;
    m_foreground = QColor("black");
    m_background = QColor("white");
    m_casesen = true;
    m_mode = QR_MODE_8;
    m_level = QR_ECLEVEL_Q;
    m_percent = 0.23f;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
///
QRCodeQWidget::QRCodeQWidget(const QByteArray &text, const QSize &size, QWidget *parent)
    : QWidget(parent)
{
    MMM_INIT_PRIVATE;
    MMM_D(QRCodeQWidget);
    if(text.isEmpty())
    {
    }
    else
    {
        d->m_text = text;
    }
    setFixedSize(size);

}

QString QRCodeQWidget::getClassName()
{
    return staticMetaObject.className();
}

void QRCodeQWidget::setMargin(const int margin)
{
    MMM_D(QRCodeQWidget);
    d->m_margin = margin;
    repaint();
}

int QRCodeQWidget::getMargin() const
{
    MMM_D(QRCodeQWidget);
    return d->m_margin;
}

void QRCodeQWidget::setIcon(const QString &path, qreal percent)
{
    MMM_D(QRCodeQWidget);
    setIconPercent(percent);
    d->m_iconPath = path;
    repaint();
}

QString QRCodeQWidget::getIcon() const
{
    MMM_D(QRCodeQWidget);
    return d->m_iconPath;
}

void QRCodeQWidget::setIconPercent(qreal percent)
{
    MMM_D(QRCodeQWidget);
    d->m_percent = percent < 0.5 ? percent : 0.3;
}

qreal QRCodeQWidget::getIconPercent() const
{
    MMM_D(QRCodeQWidget);
    return d->m_percent;
}

void QRCodeQWidget::setCaseSensitive(bool flag)
{
    MMM_D(QRCodeQWidget);
    d->m_casesen = flag;
    repaint();
}

bool QRCodeQWidget::caseSensitive() const
{
    MMM_D(QRCodeQWidget);
    return d->m_casesen;
}

void QRCodeQWidget::setText(const QByteArray &text)
{
    MMM_D(QRCodeQWidget);
    d->m_text = text;
}

QByteArray QRCodeQWidget::getText() const
{
    MMM_D(QRCodeQWidget);
    return d->m_text;
}

void QRCodeQWidget::setForegroundColor(const QColor &color)
{
    MMM_D(QRCodeQWidget);
    d->m_foreground = color;
}

QColor QRCodeQWidget::getForegroundColor() const
{
    MMM_D(QRCodeQWidget);
    return d->m_foreground;
}

void QRCodeQWidget::setBackgroundColor(const QColor &color)
{
    MMM_D(QRCodeQWidget);
    d->m_background = color;
}

QColor QRCodeQWidget::getBackgroundColor() const
{
    MMM_D(QRCodeQWidget);
    return d->m_background;
}

void QRCodeQWidget::setMode(QRencodeMode mode)
{
    MMM_D(QRCodeQWidget);
    d->m_mode = mode;
}

QRencodeMode QRCodeQWidget::getMode() const
{
    MMM_D(QRCodeQWidget);
    return d->m_mode;
}

void QRCodeQWidget::setLevel(QRecLevel level)
{
    MMM_D(QRCodeQWidget);
    d->m_level = level;
}

QRecLevel QRCodeQWidget::getLevel() const
{
    MMM_D(QRCodeQWidget);
    return d->m_level;
}

void QRCodeQWidget::paintEvent(QPaintEvent *event)
{
    MMM_D(QRCodeQWidget);
    QWidget::paintEvent (event);
    QPainter painter(this);

    QRcode *qrcode = QRcode_encodeString(d->m_text.constData(), 7,
                                         d->m_level, d->m_mode, d->m_casesen);
    if(qrcode != nullptr)
    {
        unsigned char *point = qrcode->data;
        painter.setPen(Qt::NoPen);
        painter.setBrush(d->m_background);
        painter.drawRect(0, 0, width(), height());
        double scale = (width () - 2.0 * d->m_margin) / qrcode->width;
        painter.setBrush(d->m_foreground);

        for(int x=0; x<qrcode->width; ++x)
        {
            for(int y =0; y<qrcode->width; ++y)
            {
                if(*point & 1)
                {
                    QRectF r(d->m_margin + y * scale, d->m_margin + x * scale, scale, scale);
                    painter.drawRects(&r, 1);
                }
                ++point;
            }
        }
        point = nullptr;
        QRcode_free(qrcode);

        /// draw icon
        painter.setBrush(d->m_background);
        double icon_width = (width () - 2.0 * d->m_margin) * d->m_percent;
        double icon_height = icon_width;
        double wrap_x = (width () - icon_width) / 2.0;
        double wrap_y = (width () - icon_height) / 2.0;
        QRectF wrap(wrap_x - 5, wrap_y - 5, icon_width + 10, icon_height + 10);
        painter.drawRoundRect(wrap, 50, 50);
        QPixmap image(d->m_iconPath);
        QRectF target(wrap_x, wrap_y, icon_width, icon_height);
        QRectF source(0, 0, image.width (), image.height ());
        painter.drawPixmap(target, image, source);
    }
    qrcode = nullptr;
    event->accept();
}
