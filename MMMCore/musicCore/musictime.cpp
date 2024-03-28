#include "musictime.h"

#include <QFileInfo>
#include <QDir>

MusicTime::MusicTime()
{
    m_defaultType = All_Msec;
    init();
}

MusicTime::MusicTime(qint64 value, Type type)
    : MusicTime()
{
    m_defaultType = type;
    fromTimeStamp(value, type == All_Sec ? MT_S : MT_S2MS);
}

MusicTime::MusicTime(int day, int hour, int min, int sec, int msec)
    : MusicTime()
{
    m_defaultType = All_Msec;
    setHMSM(day, hour, min, sec, msec);
}

MusicTime::~MusicTime()
{

}

QString MusicTime::getClassName()
{
    return "MusicTime";
}

void MusicTime::init()
{
    m_day = 0;
    m_hour = 0;
    m_min = 0;
    m_sec = 0;
    m_msec = 0;
}

void MusicTime::setHMSM(int day, int hour, int min, int sec, int msec)
{
    init();

    int delta = 0;
    delta = msec >= MT_S2MS ? msec / MT_S2MS : 0;
    m_msec = msec % MT_S2MS;

    sec += delta;
    delta = sec >= MT_M2S ? sec / MT_M2S : 0;
    m_sec = sec % MT_M2S;

    min += delta;
    delta = min >= MT_H2M ? min / MT_H2M : 0;
    m_min = min % MT_H2M;

    hour += delta;
    m_day = hour >= MT_D2H ? hour / MT_D2H : 0;
    m_hour = hour % MT_D2H;

    m_day += day;
}

void MusicTime::fromTimeStamp(qint64 value, int delta)
{
    if(value < 0)
    {
        init();
        return;
    }

    m_day = value/MT_D2S/delta;
    value -= m_day*MT_D2S*delta;

    m_hour = value/MT_H2S/delta;
    value -= m_hour*MT_H2S*delta;

    m_min = value/MT_M2S/delta;
    value -= m_min*MT_M2S*delta;

    m_sec = value/delta;
    if(delta == MT_S2MS)
    {
        value -= (m_sec*delta);
        m_msec = value;
    }
}

bool MusicTime::isNull() const
{
    return (m_hour == 0 && m_min == 0 && m_sec == 0 && m_msec == 0);
}

bool MusicTime::isValid() const
{
    return !isNull();
}

MusicTime MusicTime::fromString(const QString &s, const QString &format)
{
    MusicTime musicTime;
    QTime t = QTime::fromString(s, format);
    musicTime.setHMSM(0, t.hour(), t.minute(), t.second(), t.msec());
    return musicTime;
}

QString MusicTime::toString(qint64 value, Type type, const QString &format)
{
    return MusicTime(value, type).toString(format);
}

QString MusicTime::toString(const QString &format)
{
    return QLocale::system().toString(
           QTime(m_hour, m_min, m_sec, m_msec), format);
}

qint64 MusicTime::getTimeStamp(Type type) const
{
    qint64 delta = (type == All_Sec) ? MT_S : MT_S2MS;
           delta = (m_day*MT_D2S + m_hour*MT_H2S + m_min*MT_M2S +
                    m_sec)*delta;
    return (type == All_Sec) ? delta : (delta + m_msec);
}

void MusicTime::timeSRand()
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
}

QString MusicTime::msecTime2LabelJustified()
{
    return toString("mm:ss");
}

QString MusicTime::msecTime2LabelJustified(qint64 time)
{
    MusicTime t(time, MusicTime::All_Msec);
    return t.toString("mm:ss");
}

QString MusicTime::normalTime2LabelJustified()
{
    return toString("hh:mm:ss");
}

QString MusicTime::normalTime2LabelJustified(qint64 time)
{
    MusicTime t(time, MusicTime::All_Msec);
    return t.toString("hh:mm:ss");
}

QString MusicTime::normalTime2Label() const
{
    if(m_day == 0 && m_hour == 0 && m_min == 0)
    {
        return QString::number(m_sec) + QObject::tr("ss");
    }
    else if(m_day == 0 && m_hour == 0 && m_min != 0)
    {
        return QString::number(m_min) + QObject::tr("mm");
    }
    else if(m_day == 0 && m_hour != 0)
    {
        return QString::number(m_hour) + QObject::tr("hh");
    }
    else if(m_day != 0)
    {
        return QString::number(m_day) + QObject::tr("day");
    }
    else
    {
        return QString();
    }
}

QString MusicTime::normalTime2Label(qint64 time)
{
    if(time < MT_M2S)
    {
        return QString::number(time) + QObject::tr("ss");
    }
    else if(MT_M2S <= time && time < MT_H2S)
    {
        return QString::number(time/MT_M2S) + QObject::tr("mm");
    }
    else if(MT_H2S <= time && time < MT_D2S)
    {
        return QString::number(time/MT_H2S) + QObject::tr("hh");
    }
    else
    {
        return QString::number(time/MT_D2S) + QObject::tr("day");
    }
}

MusicTime& MusicTime::operator= (const MusicTime &other)
{
    m_defaultType = other.getType();
    m_day = other.getDay();
    m_hour = other.getHour();
    m_min = other.getMinute();
    m_sec = other.getSecond();
    m_msec = other.getMillionSecond();
    return *this;
}

MusicTime& MusicTime::operator+= (const MusicTime &other)
{
    qint64 t = getTimeStamp(All_Msec) + other.getTimeStamp(All_Msec);
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

MusicTime& MusicTime::operator+= (const int other)
{
    qint64 t = getTimeStamp(All_Msec) + other;
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

MusicTime& MusicTime::operator-= (const MusicTime &other)
{
    qint64 t = getTimeStamp(All_Msec) - other.getTimeStamp(All_Msec);
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

MusicTime& MusicTime::operator-= (const int other)
{
    qint64 t = getTimeStamp(All_Msec) - other;
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

MusicTime& MusicTime::operator*= (const int other)
{
    qint64 t = getTimeStamp(All_Msec) * other;
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

MusicTime& MusicTime::operator/= (const int other)
{
    qint64 t = getTimeStamp(All_Msec) / other;
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

MusicTime MusicTime::operator+ (const MusicTime &other)
{
    qint64 t = getTimeStamp(All_Msec) + other.getTimeStamp(All_Msec);
    return MusicTime(t, m_defaultType);
}

MusicTime MusicTime::operator+ (const int other)
{
    qint64 t = getTimeStamp(All_Msec) + other;
    return MusicTime(t, m_defaultType);
}

MusicTime MusicTime::operator- (const MusicTime &other)
{
    qint64 t = getTimeStamp(All_Msec) - other.getTimeStamp(All_Msec);
    return MusicTime(t, m_defaultType);
}

MusicTime MusicTime::operator- (const int other)
{
    qint64 t = getTimeStamp(All_Msec) - other;
    return MusicTime(t, m_defaultType);
}

MusicTime MusicTime::operator* (const int other)
{
    qint64 t = getTimeStamp(All_Msec) * other;
    return MusicTime(t, m_defaultType);
}

MusicTime MusicTime::operator/ (const int other)
{
    qint64 t = getTimeStamp(All_Msec) / other;
    return MusicTime(t, m_defaultType);
}

bool MusicTime::operator== (const MusicTime &other) const
{
    return getTimeStamp(All_Msec) == other.getTimeStamp(All_Msec);
}

bool MusicTime::operator!= (const MusicTime &other) const
{
    return getTimeStamp(All_Msec) != other.getTimeStamp(All_Msec);
}
