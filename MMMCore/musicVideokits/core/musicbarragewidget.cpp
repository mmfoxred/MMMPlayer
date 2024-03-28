#include "musicbarragewidget.h"
#include "musictime.h"
#include "musicobject.h"
#include "musicutils.h"

MusicBarrageAnimation::MusicBarrageAnimation(QObject *parent)
    : QPropertyAnimation(parent)
{
    init();
}

MusicBarrageAnimation::MusicBarrageAnimation(QObject *target,
                                             const QByteArray &propertyName,
                                             QObject *parent)
    : QPropertyAnimation(target, propertyName, parent)
{
    init();
}

void MusicBarrageAnimation::animationFinished()
{
    setDuration(qrand()%(10*MT_S2MS) + MT_S2MS);
    setSize(m_parentSize);
    start();
}

QString MusicBarrageAnimation::getClassName()
{
    return staticMetaObject.className();
}

void MusicBarrageAnimation::setSize(const QSize &size)
{
    m_parentSize = size;
    int randHeight = qrand()%size.height();
    setStartValue(QPoint(0, randHeight));
    setEndValue(QPoint(size.width(), randHeight));
}

void MusicBarrageAnimation::init()
{
    setDuration(qrand()%10000 + MT_S2MS);
    setEasingCurve(QEasingCurve::Linear);

    connect(this, SIGNAL(finished()), SLOT(animationFinished()));
}


MusicBarrageWidget::MusicBarrageWidget(QObject *parent)
    : QObject(parent)
{
    m_parentClass = MStatic_cast(QWidget*, parent);
    m_barrageState = false;

    readBarrage();
}

MusicBarrageWidget::~MusicBarrageWidget()
{
    writeBarrage();
    deleteItems();
}

QString MusicBarrageWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicBarrageWidget::start()
{
    if(m_barrageState)
    {
        for(int i=0; i<m_labels.count(); i++)
        {
            m_labels[i]->show();
            m_animations[i]->start();
        }
    }
}

void MusicBarrageWidget::pause()
{
    if(m_barrageState)
    {
        for(int i=0; i<m_labels.count(); i++)
        {
            m_labels[i]->hide();
            m_animations[i]->pause();
        }
    }
}

void MusicBarrageWidget::stop()
{
    for(int i=0; i<m_labels.count(); i++)
    {
        m_labels[i]->hide();
        m_animations[i]->stop();
    }
}

void MusicBarrageWidget::setSize(const QSize &size)
{
    m_parentSize = size;
    foreach(MusicBarrageAnimation *anima, m_animations)
    {
        anima->setSize(size);
    }
}

void MusicBarrageWidget::barrageStateChanged(bool on)
{
    m_barrageState = on;
    if(m_barrageState && !m_barrageRecords.isEmpty())
    {
        deleteItems();
        createLabel();
        createAnimation();
        start();
    }
    else
    {
        stop();
    }
}

void MusicBarrageWidget::addBarrage(const MusicBarrageRecord &record)
{
    MusicTime::timeSRand();

    QLabel *label = createLabel(record);
    createAnimation(label);
    m_barrageRecords << record;

    if(m_barrageState)
    {
        start();
    }
}

void MusicBarrageWidget::deleteItems()
{
    while(!m_labels.isEmpty())
    {
        delete m_labels.takeLast();
        delete m_animations.takeLast();
    }
}

void MusicBarrageWidget::createLabel()
{
    MusicTime::timeSRand();
    foreach(const MusicBarrageRecord &record, m_barrageRecords)
    {
        createLabel(record);
    }
}

QLabel *MusicBarrageWidget::createLabel(const MusicBarrageRecord &record)
{
    QLabel *label = new QLabel(m_parentClass);
    label->setStyleSheet(QString("QLabel{ color:%1}").arg(record.m_color));
    label->setText(record.m_value);

    MusicUtils::UWidget::setLabelFontSize(label, record.m_size);
    QFontMetrics ftMcs(label->font());
    label->resize(ftMcs.width(label->text()), ftMcs.height());

    label->hide();
    m_labels << label;

    return label;
}

void MusicBarrageWidget::createAnimation()
{
    foreach(QLabel *label, m_labels)
    {
        createAnimation(label);
    }
}

void MusicBarrageWidget::createAnimation(QLabel *label)
{
    MusicBarrageAnimation *anim = new MusicBarrageAnimation(label, "pos");
    anim->setSize(m_parentSize);
    m_animations << anim;
}

void MusicBarrageWidget::readBarrage()
{
    MusicBarrageRecordConfigManager manager(this);
    if(!manager.readBarrageXMLConfig())
    {
        return;
    }
    manager.readBarrageConfig(m_barrageRecords);
}

void MusicBarrageWidget::writeBarrage()
{
    MusicBarrageRecordConfigManager manager(this);
    if(!manager.readBarrageXMLConfig())
    {
        return;
    }
    manager.writeBarrageConfig(m_barrageRecords);
}
