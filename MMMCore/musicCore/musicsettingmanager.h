#ifndef MUSICSETTINGMANAGER
#define MUSICSETTINGMANAGER

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QMetaEnum>
#include "musicobject.h"
#include "musicsingleton.h"

#define M_SETTING_PTR (MusicSingleton<MusicSettingManager>::createInstance())

/*! @brief The class of the paramater setting manager.
 */
class MUSIC_CORE_EXPORT MusicSettingManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(ConfigType)
public:
    enum ConfigType
    {
        Null = -1,                      ///*No Parameter*/
        ScreenSize,                     ///*Screen Size Parameter*/
        WidgetPosition,                 ///*Widget Position Parameter*/
        WidgetSize,                     ///*Widget Size Parameter*/

        PlayModeChoiced,                ///*Play Mode Parameter*/
        VolumeChoiced,                  ///*Volume Parameter*/

        AutoPlayChoiced,                ///*Auto Play Parameter*/
        EnhancedMusicChoiced,           ///*Enhanced Music Parameter*/
        CurrentLanIndexChoiced,         ///*Current LanIndex Parameter*/
        CloseEventChoiced,              ///*Close Event Parameter*/
        LastPlayIndexChoiced,           ///*Last Play Index Parameter*/
        CloseNetWorkChoiced,            ///*Close NetWork Parameter*/
        FileAssociationChoiced,         ///*File Association Parameter*/
        MuiscSongLovedChoiced,          ///*Muisc song has loved Parameter*/
        MobileDevicePathChoiced,        ///*Set Mobile Device Path Parameter*/

        BgThemeChoiced,                 ///*Bg Theme Parameter*/
        BgTransparentChoiced,           ///*Bg Transparent Parameter*/
        BgListTransparentChoiced,       ///*Bg List Transparent Parameter*/

        ShowInlineLrcChoiced,           ///*Show Inline Lrc Parameter*/
        ShowDesktopLrcChoiced,          ///*Show Desktop Lrc Parameter*/
        LrcColorChoiced,                ///*Lrc Color Parameter*/
        LrcSizeChoiced,                 ///*Lrc Size Parameter*/
        LrcTypeChoiced,                 ///*Lrc Type Parameter*/
        LrcFamilyChoiced,               ///*Lrc Family Parameter*/
        LrcFgColorChoiced,              ///*Lrc Fg Color Parameter*/
        LrcBgColorChoiced,              ///*Lrc Bg Color Parameter*/
        LrcColorTransChoiced,           ///*Lrc Color Trans Parameter*/

        DLrcColorChoiced,               ///*Desktop Lrc Color Parameter*/
        DLrcSizeChoiced,                ///*Desktop Lrc Size Parameter*/
        DLrcTypeChoiced,                ///*Desktop Lrc Type Parameter*/
        DLrcFamilyChoiced,              ///*Desktop Lrc Family Parameter*/
        DLrcFgColorChoiced,             ///*Desktop Lrc Fg Color Parameter*/
        DLrcBgColorChoiced,             ///*Desktop Lrc Bg Color Parameter*/
        DLrcColorTransChoiced,          ///*Desktop Lrc Color Trans Parameter*/
        DLrcLockedChoiced,              ///*Desktop Lrc Locked Parameter*/
        DLrcGeometryChoiced,            ///*Desktop Lrc Geometry Parameter*/

        EqualizerEnableChoiced,         ///*Equalizer Enable Parameter*/
        EqualizerValueChoiced,          ///*Equalizer Value Parameter*/
        EqualizerIndexChoiced,          ///*Equalizer Index Parameter*/

        TimerAutoIndexChoiced,          ///*Timer Auto Index Parameter*/
        TimerAutoPlayChoiced,           ///*Timer Auto Play Parameter*/
        TimerAutoPlayHourChoiced,       ///*Timer Auto Play Hour Parameter*/
        TimerAutoPlaySecondChoiced,     ///*Timer Auto Play Second Parameter*/
        TimerAutoPlayRepeatChoiced,     ///*Timer Auto Play Repeat Parameter*/
        TimerAutoPlayItemIndexChoiced,  ///*Timer Auto Play Item Index Parameter*/
        TimerAutoPlaySongIndexChoiced,  ///*Timer Auto Play Song Index Parameter*/
        TimerAutoStopChoiced,           ///*Timer Auto Stop Parameter*/
        TimerAutoStopHourChoiced,       ///*Timer Auto Stop Hour Parameter*/
        TimerAutoStopSecondChoiced,     ///*Timer Auto Stop Second Parameter*/
        TimerAutoStopRepeatChoiced,     ///*Timer Auto Stop Repeat Parameter*/
        TimerAutoShutdownChoiced,       ///*Timer Auto Shutdown Parameter*/
        TimerAutoShutdownHourChoiced,   ///*Timer Auto Shutdown Hour Parameter*/
        TimerAutoShutdownSecondChoiced, ///*Timer Auto Shutdown Second Parameter*/
        TimerAutoShutdownRepeatChoiced, ///*Timer Auto Shutdown Repeat Parameter*/

        DownloadMusicExistChoiced,      ///*Download Music song exist Parameter*/
        DownloadMusicExistPathChoiced,  ///*Download Music song exist path Parameter*/
        DownloadMusicPathDirChoiced,    ///*Download Music Path Dir Parameter*/
        DownloadLrcPathDirChoiced,      ///*Download Lrc Path Dir Parameter*/
        DownloadCacheLimitChoiced,      ///*Download Cache Limit Parameter*/
        DownloadCacheSizeChoiced,       ///*Download Cache Size Parameter*/
        DownloadLimitChoiced,           ///*Download Limit Parameter*/
        DownloadServerChoiced,          ///*Download Server Parameter*/
        DownloadDLoadLimitChoiced,      ///*Download DLoad Limit Parameter*/
        DownloadULoadLimitChoiced       ///*Download ULoad Limit Parameter*/

    };

    static QString getClassName()
    {
        return staticMetaObject.className();
    }
    /*!
     * Get class object name.
     */
    inline void setValue(ConfigType type, const QVariant &var)
    {
        m_para[type] = var;
    }
    /*!
     * Set current value by Config Type.
     */

    inline void setValue(const QString &stype, const QVariant &var)
    {
        m_para[typeStringToEnum(stype)] = var;
    }
    /*!
     * Set current value by String Type.
     */

    inline QVariant value(ConfigType type) const
    {
        return m_para[type];
    }
    /*!
     * Get current value by Config Type.
     */

    inline QVariant value(const QString &stype) const
    {
        return m_para[typeStringToEnum(stype)];
    }
    /*!
     * Get current value by String Type.
     */

    inline int count() const
    {
        return m_para.count();
    }
    /*!
     * Get parameter count.
     */

    inline bool isEmpty() const
    {
        return m_para.isEmpty();
    }
    /*!
     * Current parameter is empty.
     */

    inline bool contains(ConfigType type) const
    {
        return m_para.contains(type);
    }
    /*!
     * Current parameter contains type.
     */

protected:
    ConfigType typeStringToEnum(const QString &stype) const
    {
        int index = staticMetaObject.indexOfEnumerator("ConfigType");
        QMetaEnum metaEnum = staticMetaObject.enumerator(index);
        int key = metaEnum.keyToValue(stype.toStdString().c_str());
        return MStatic_cast(ConfigType, key);
    }
    /*!
     * Convert String type to Config Type.
     */

    QVariant m_variant;
    QMap<ConfigType, QVariant> m_para;

    DECLARE_SINGLETON_CLASS(MusicSettingManager)
};


#endif // MUSICSETTINGMANAGER

