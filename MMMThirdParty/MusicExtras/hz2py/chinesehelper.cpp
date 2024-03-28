#include "chinesehelper.h"

#ifdef Q_CC_GNU
#  pragma GCC diagnostic ignored "-Wmultichar"
#endif

class ChineseHelperPrivate : public MMMPrivate<ChineseHelper>
{
public:
    ChineseHelperPrivate();

    QMap<QString, QString> m_data;

};

ChineseHelperPrivate::ChineseHelperPrivate()
{
    m_data = PinyinResource::getChineseResource();
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
///
ChineseHelper::ChineseHelper()
{
    MMM_INIT_PRIVATE;
}

QString ChineseHelper::getClassName()
{
    return "ChineseHelper";
}

QChar ChineseHelper::convertToSimplifiedChinese(const QChar &c)
{
    MMM_D(ChineseHelper);
    QString simplifiedChinese = d->m_data.value(c);
    return simplifiedChinese.isEmpty() ? c : simplifiedChinese.at(0);
}

QChar ChineseHelper::convertToTraditionalChinese(const QChar &c)
{
    MMM_D(ChineseHelper);
    QString simpTraditionaChinese = d->m_data.key(c);
    return simpTraditionaChinese.isEmpty() ? c : simpTraditionaChinese.at(0);
}

QString ChineseHelper::convertToSimplifiedChinese(const QString &str)
{
    QString sb;
    for(int i=0, len=str.length(); i<len; i++)
    {
        sb += convertToSimplifiedChinese(str[i]);
    }
    return sb;
}

QString ChineseHelper::convertToTraditionalChinese(const QString &str)
{
    QString sb;
    for(int i=0, len=str.length(); i<len; i++)
    {
        sb += convertToTraditionalChinese(str[i]);
    }
    return sb;
}

bool ChineseHelper::isTraditionalChinese(const QChar &c)
{
    MMM_D(ChineseHelper);
    return d->m_data.keys().indexOf(c) != -1;
}

bool ChineseHelper::isChinese(const QChar &c)
{
    return L'〇' == c || (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5);
}

bool ChineseHelper::containsChinese(const QString &str)
{
    for(int i=0, len=str.length(); i<len; i++)
    {
        if(isChinese(str[i]))
        {
            return true;
        }
    }
    return false;
}
