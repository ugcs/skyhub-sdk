/****************************************************************************
**
** Copyright (C) 2020, Smart Projects Holdings Ltd
** Contact: https://industrial.ugcs.com/contact
**
** This file is part of SkyHub SDK.
**
** BSD 3-Clause License Usage
**
** This file may be used under the terms of the BSD 3-Clause License
** as published by the Open Source Initiative and appearing in the file
** LICENSE included in the packaging of this file. Please review the
** following information to ensure the BSD 3-Clause License requirements
** will be met: https://opensource.org/licenses/BSD-3-Clause.
**
****************************************************************************/

#ifndef APP_H
#define APP_H

#include <QCoreApplication>
#include <QVariant>

#define SINGLETON(className) reinterpret_cast<className *>(app()->singleton(#className))
#define CREATE_SINGLETON(className) app()->addSingleton<className>(#className, new className(qApp))

#define REGISTER_TOPIC(name, type) Q_SIGNALS: void name(type value);

#define REGISTER_BOOL(name) REGISTER_TOPIC(name, bool)
#define REGISTER_F64(name) REGISTER_TOPIC(name, qreal)
#define REGISTER_F32(name) REGISTER_TOPIC(name, float)
#define REGISTER_I64(name) REGISTER_TOPIC(name, qint64)
#define REGISTER_U64(name) REGISTER_TOPIC(name, quint64)
#define REGISTER_I32(name) REGISTER_TOPIC(name, qint32)
#define REGISTER_U32(name) REGISTER_TOPIC(name, quint32)
#define REGISTER_I16(name) REGISTER_TOPIC(name, qint16)
#define REGISTER_U16(name) REGISTER_TOPIC(name, quint16)
#define REGISTER_I8(name) REGISTER_TOPIC(name, qint8)
#define REGISTER_U8(name) REGISTER_TOPIC(name, quint8)
#define REGISTER_INT(name) REGISTER_TOPIC(name, int)
#define REGISTER_STR(name) REGISTER_TOPIC(name, QString)

#define PUBLISH_TOPIC(name, type, value) QMetaObject::invokeMethod(app(), #name, Q_ARG(type, value))

#define PUBLISH_BOOL(name, value) PUBLISH_TOPIC(name, bool, value)
#define PUBLISH_F64(name, value) PUBLISH_TOPIC(name, qreal, value)
#define PUBLISH_F32(name, value) PUBLISH_TOPIC(name, float, value)
#define PUBLISH_I64(name, value) PUBLISH_TOPIC(name, qint64, value)
#define PUBLISH_U64(name, value) PUBLISH_TOPIC(name, quint64, value)
#define PUBLISH_I32(name, value) PUBLISH_TOPIC(name, qint32, value)
#define PUBLISH_U32(name, value) PUBLISH_TOPIC(name, quint32, value)
#define PUBLISH_I16(name, value) PUBLISH_TOPIC(name, qint16, value)
#define PUBLISH_U16(name, value) PUBLISH_TOPIC(name, quint16, value)
#define PUBLISH_I8(name, value) PUBLISH_TOPIC(name, qint8, value)
#define PUBLISH_U8(name, value) PUBLISH_TOPIC(name, quint8, value)
#define PUBLISH_INT(name, value) PUBLISH_TOPIC(name, int, value)
#define PUBLISH_STR(name, value) PUBLISH_TOPIC(name, QString, value)

#define SUBSCRIBE_TOPIC(name, parser) connect(app(), &App::name, this, parser)
// TODO: UNSUBSCRIBE_TOPIC may potentially not work for lambda expressions
#define UNSUBSCRIBE_TOPIC(name, parser) disconnect(app(), &App::name, this, parser)

#define BIND_TOPIC_TO_VAR(name, type, variable) SUBSCRIBE_TOPIC(name, [this](type value){ variable = value; })
#define BIND_TOPIC_TO_VAR_REF(name, type, variable) SUBSCRIBE_TOPIC(name, [this](const type &value){ variable = value; })

#define BIND_TOPIC_TO_BOOL(name, variable) BIND_TOPIC_TO_VAR(name, bool, variable)
#define BIND_TOPIC_TO_F64(name, variable) BIND_TOPIC_TO_VAR(name, qreal, variable)
#define BIND_TOPIC_TO_F32(name, variable) BIND_TOPIC_TO_VAR(name, float, variable)
#define BIND_TOPIC_TO_I64(name, variable) BIND_TOPIC_TO_VAR(name, qint64, variable)
#define BIND_TOPIC_TO_U64(name, variable) BIND_TOPIC_TO_VAR(name, quint64, variable)
#define BIND_TOPIC_TO_I32(name, variable) BIND_TOPIC_TO_VAR(name, qint32, variable)
#define BIND_TOPIC_TO_U32(name, variable) BIND_TOPIC_TO_VAR(name, quint32, variable)
#define BIND_TOPIC_TO_I16(name, variable) BIND_TOPIC_TO_VAR(name, qint16, variable)
#define BIND_TOPIC_TO_U16(name, variable) BIND_TOPIC_TO_VAR(name, quint16, variable)
#define BIND_TOPIC_TO_I8(name, variable) BIND_TOPIC_TO_VAR(name, qint8, variable)
#define BIND_TOPIC_TO_U8(name, variable) BIND_TOPIC_TO_VAR(name, quint8, variable)
#define BIND_TOPIC_TO_INT(name, variable) BIND_TOPIC_TO_VAR(name, int, variable)
#define BIND_TOPIC_TO_STR(name, variable) BIND_TOPIC_TO_VAR_REF(name, QString, variable)

#define BIND_SETTING_TO_VAR(group, param, type, variable, defaultValue) do { \
    connect(app(), &App::group##_##param, this, [this](type value){ variable = value; }); \
    variable = app()->setting_##type(#group, #param, defaultValue); \
    app()->addSettingsToSet(#group, #param, #type); \
    } while (false)

#define BIND_SETTING_TO_VAR_REF(group, param, type, variable, defaultValue) do { \
    connect(app(), &App::group##_##param, this, [this](const type &value){ variable = value; }); \
    variable = app()->setting_##type(#group, #param, defaultValue); \
    app()->addSettingsToSet(#group, #param, #type); \
    } while (false)

#define OVERLOADED_MACRO_4(_1, _2, _3, _4, NAME, ...) NAME

#define BIND_SETTING_TO_BOOL(...) OVERLOADED_MACRO_4(__VA_ARGS__, BIND_SETTING_TO_BOOL_4, BIND_SETTING_TO_BOOL_3)(__VA_ARGS__)
#define BIND_SETTING_TO_BOOL_4(group, param, variable, defaultValue) BIND_SETTING_TO_VAR(group, param, bool, variable, defaultValue)
#define BIND_SETTING_TO_BOOL_3(group, param, variable) BIND_SETTING_TO_BOOL_4(group, param, variable, QVariant())

#define BIND_SETTING_TO_F32(...) OVERLOADED_MACRO_4(__VA_ARGS__, BIND_SETTING_TO_F32_4, BIND_SETTING_TO_F32_3)(__VA_ARGS__)
#define BIND_SETTING_TO_F32_4(group, param, variable, defaultValue) BIND_SETTING_TO_VAR(group, param, float, variable, defaultValue)
#define BIND_SETTING_TO_F32_3(group, param, variable) BIND_SETTING_TO_F32_4(group, param, variable, QVariant())

#define BIND_SETTING_TO_F64(...) OVERLOADED_MACRO_4(__VA_ARGS__, BIND_SETTING_TO_F64_4, BIND_SETTING_TO_F64_3)(__VA_ARGS__)
#define BIND_SETTING_TO_F64_4(group, param, variable, defaultValue) BIND_SETTING_TO_VAR(group, param, qreal, variable, defaultValue)
#define BIND_SETTING_TO_F64_3(group, param, variable) BIND_SETTING_TO_F64_4(group, param, variable, QVariant())

#define BIND_SETTING_TO_U32(...) OVERLOADED_MACRO_4(__VA_ARGS__, BIND_SETTING_TO_U32_4, BIND_SETTING_TO_U32_3)(__VA_ARGS__)
#define BIND_SETTING_TO_U32_4(group, param, variable, defaultValue) BIND_SETTING_TO_VAR(group, param, quint32, variable, defaultValue)
#define BIND_SETTING_TO_U32_3(group, param, variable) BIND_SETTING_TO_U32_4(group, param, variable, QVariant())

#define BIND_SETTING_TO_U16(...) OVERLOADED_MACRO_4(__VA_ARGS__, BIND_SETTING_TO_U16_4, BIND_SETTING_TO_U16_3)(__VA_ARGS__)
#define BIND_SETTING_TO_U16_4(group, param, variable, defaultValue) BIND_SETTING_TO_VAR(group, param, quint16, variable, defaultValue)
#define BIND_SETTING_TO_U16_3(group, param, variable) BIND_SETTING_TO_U16_4(group, param, variable, QVariant())

#define BIND_SETTING_TO_U8(...) OVERLOADED_MACRO_4(__VA_ARGS__, BIND_SETTING_TO_U8_4, BIND_SETTING_TO_U8_3)(__VA_ARGS__)
#define BIND_SETTING_TO_U8_4(group, param, variable, defaultValue) BIND_SETTING_TO_VAR(group, param, quint8, variable, defaultValue)
#define BIND_SETTING_TO_U8_3(group, param, variable) BIND_SETTING_TO_U8_4(group, param, variable, QVariant())

#define BIND_SETTING_TO_INT(...) OVERLOADED_MACRO_4(__VA_ARGS__, BIND_SETTING_TO_INT_4, BIND_SETTING_TO_INT_3)(__VA_ARGS__)
#define BIND_SETTING_TO_INT_4(group, param, variable, defaultValue) BIND_SETTING_TO_VAR(group, param, int, variable, defaultValue)
#define BIND_SETTING_TO_INT_3(group, param, variable) BIND_SETTING_TO_INT_4(group, param, variable, QVariant())

#define BIND_SETTING_TO_STR(...) OVERLOADED_MACRO_4(__VA_ARGS__, BIND_SETTING_TO_STR_4, BIND_SETTING_TO_STR_3)(__VA_ARGS__)
#define BIND_SETTING_TO_STR_4(group, param, variable, defaultValue) BIND_SETTING_TO_VAR_REF(group, param, QString, variable, defaultValue)
#define BIND_SETTING_TO_STR_3(group, param, variable) BIND_SETTING_TO_STR_4(group, param, variable, QVariant())

#define UPDATE_SETTING(group, param, value) app()->updateSetting(group, param, value)

// Check for correct setting name at the compile time
#define SET_SETTING_DEFAULT(group, param, defaultValue) Q_UNUSED(&App::group##_##param) app()->setSettingDefault(#group, #param, defaultValue)

// Unstable code boundaries
//
// Example:
//
//     UNSTABLE_BEGIN(MY_FEATURE);
//     newUnstableCode();
//     UNSTABLE_END(MY_FEATURE);
//     UNLESS_STABLE_BEGIN(MY_FEATURE);
//     oldStableCode();
//     UNLESS_STABLE_END(MY_FEATURE);
//
#define UNSTABLE_BEGIN(feature) if (app()->setting_bool("UNSTABLE", #feature, false)) do { (void)&App::UNSTABLE_##feature
#define UNSTABLE_END(feature) Q_UNUSED(&App::UNSTABLE_##feature) } while (false)
#define UNLESS_STABLE_BEGIN(feature) if (!app()->setting_bool("UNSTABLE", #feature, false)) do { (void)&App::UNSTABLE_##feature
#define UNLESS_STABLE_END(feature) UNSTABLE_END(feature)

enum ScalarSensorStatusId : uint8_t {
    Good = 0x0,
    OverMax = 0x1,
    UnderMin = 0x2,
    SensorError = 0x4
};

enum MissionState : uint8_t {
    NotStarted = 0,
    Running = 1,
    Paused = 2,         // Paused by user
    Interrupted = 3,    // Interrupted from code (Ground not visible or altimeter error)
    Resumed = 4,
    Completed = 5,
    Waiting = 6        // Waiting for action from user
};

enum AlgorithmState : uint8_t {
    Disabled = 0,
    WaitingConfigure  = 1,
    Configured = 2,
    Activated = 3
};

enum FutureMissionAction : uint8_t {
    Other = 0,
    RequestStart = 1,
    RequestPause = 2
};

enum SafetyAction : uint8_t {
    NOTHING = 0,        // Do nothing, ignore such case
    WARNING = 1,        // Warn in error log, so operator can manualy react
    PAUSE_MISSION = 2,  // Pause auto mission if mission was running, warn operator
    STOP_MISSION = 3    // Stop and cancel mission, warn operator.
};

struct GeoCoordinates
{
    double latitude;
    double longitude;
};

struct ScalarSensorData
{
    float value = 0;
    uint8_t status = ScalarSensorStatusId::Good;

    ScalarSensorData() { }
    ScalarSensorData(float value) : value(value) { }
    ScalarSensorData(float value, ScalarSensorStatusId status) : value(value), status(status) { }
    ScalarSensorData(float value, float minValue, float maxValue) : value(value)
    {
        if (value > maxValue)
            status = ScalarSensorStatusId::OverMax;
        else if(value < minValue)
            status = ScalarSensorStatusId::UnderMin;
        else
            status = ScalarSensorStatusId::Good;
    }
};

struct PayloadConnectedData
{
    uint8_t PayloadId;
    bool isConnected;
};

struct SegYTraceNumber
{
    int trace;
    int channel;
};

struct TextToGround
{
    enum MessageType {
        InfoType = 0x0,
        ErrorType = 0x1,
    };
    Q_DECLARE_FLAGS(MessageTypes, MessageType)

    TextToGround()
    {
    }
    TextToGround(QString text, MessageTypes flags)
        : text(text), flags(flags)
    {
    }

    QString text;
    MessageTypes flags = InfoType;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TextToGround::MessageTypes)

class QSettings;

/*!
 * @brief
 * The main application class. Contains:
 *   - Embedded message broker for implementing the publish-subscribe pattern
 *   - Variables-to-settings binding
 * @example
 * Subscribing to topic:
 *     SUBSCRIBE_TOPIC(altitude, [this](float value){ m_altitude = value; });
 * or
 *     SUBSCRIBE_TOPIC(altitude, &Receiver::handler);
 * Topic publishing:
 *     PUBLISH_F32(altitude, 12.46f);
 * Setting-to-variable binding:
 *     BIND_SETTING_TO_F32(GENERAL, PARAMETER, m_parameter, 10.0f);
 * Updating setting and bound variable (may be called with non-const strings as parameters):
 *     UPDATE_SETTING_F32("GENERAL", "PARAMETER", 20.0f);
 */
class App: public QCoreApplication
{
    Q_OBJECT
public:
    App(int &argc, char **argv);

    void loadSettings(const QString &fileName);
    void syncSettings();

    QVariant settingValue(const char *group, const char *param, const QVariant &defaultValue);
    int setting_int(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return settingValue(group, param, defaultValue).toInt(); }
    qint32 setting_qint32(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return settingValue(group, param, defaultValue).toInt(); }
    quint8 setting_quint8(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return static_cast<quint8>(settingValue(group, param, defaultValue).toUInt()); }
    quint16 setting_quint16(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return static_cast<quint16>(settingValue(group, param, defaultValue).toUInt()); }
    quint32 setting_quint32(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return settingValue(group, param, defaultValue).toUInt(); }
    float setting_float(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return settingValue(group, param, defaultValue).toFloat(); }
    qreal setting_qreal(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return settingValue(group, param, defaultValue).toDouble(); }
    QString setting_QString(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return settingValue(group, param, defaultValue).toString(); }
    bool setting_bool(const char *group, const char *param, const QVariant &defaultValue = QVariant()) { return settingValue(group, param, defaultValue).toBool(); }

    void updateSetting(const char *group, const char *param, const QVariant &value);
    void setSettingDefault(const char *group, const char *param, const QVariant &value);
    void removeObsoleteSettings();
    void addSettingsToSet(const char *group, const char *param, const char *type);

    QStringList debugOptions() { return m_debugOptions.keys(); }
    void setDebugOption(const QString &option, bool value) { m_debugOptions.insert(option.toLower(), value); }
    bool isDebug(const QString &option) { return m_debugOptions.value(option.toLower(), false); }

    template <typename T> T* addSingleton(const QString &name, T *pointer) { m_singletons.insert(name, pointer); return pointer; }
    void *singleton(const QString &name) { return m_singletons.value(name, nullptr); }

    void sendMessage(const QString &message, TextToGround::MessageTypes flags = TextToGround::InfoType);
    void sendMessage(const QString &message, const QString &id, TextToGround::MessageTypes flags = TextToGround::InfoType);

    bool verbose() const { return m_verbose; }
    void setVerbose(bool verbose) { m_verbose = verbose; }

    const QSettings *constSettings() const { return m_settings; }

    // Vehicle data
    REGISTER_TOPIC(altitude, ScalarSensorData)
    REGISTER_TOPIC(altitudeAMSL, ScalarSensorData)
    REGISTER_TOPIC(rtkAltitude, ScalarSensorData)
    REGISTER_F32(roll)
    REGISTER_F32(pitch)
    REGISTER_F32(yaw)
    REGISTER_BOOL(isRtkPositionInfoGood)
    REGISTER_BOOL(timeIsSet)
    REGISTER_TOPIC(gpsCoordinate, GeoCoordinates)
    REGISTER_TOPIC(rtkCoordinate, GeoCoordinates)
    REGISTER_F64(velocity)
    REGISTER_F32(hdop)
    REGISTER_U16(nsv)

    // Algorithm data
    REGISTER_BOOL(flightControlledApp)
    REGISTER_U8(ttfMissionState)
    REGISTER_U8(ttfAlgorithmState)
    REGISTER_U8(ghMissionState)
    REGISTER_U8(ghAlgorithmState)
    REGISTER_U8(ttfRequestMissionAction)
    REGISTER_U8(ghRequestMissionAction)
    REGISTER_U8(oaRequestActivate)
    REGISTER_U8(autoMissionState)
    REGISTER_U8(oaAlgorithmState)
    // TODO: Legacy to write additional title in GPR SEG-Y log
    REGISTER_BOOL(isTerrainFollowingModeEnabled)
    REGISTER_INT(waypointIndex)
    REGISTER_F64(targetYaw)
    REGISTER_TOPIC(destination, GeoCoordinates)
    REGISTER_F64(nextPointHeight)

    // Payloads data
    REGISTER_TOPIC(SegYLogTraceNumber, SegYTraceNumber)
    REGISTER_TOPIC(rawAltimeterValue, ScalarSensorData)
    REGISTER_TOPIC(altimeterValue, ScalarSensorData)
    REGISTER_TOPIC(filteredAltimeterValue, ScalarSensorData)
    REGISTER_TOPIC(gprConnected, PayloadConnectedData)
    REGISTER_TOPIC(echosounderConnected, PayloadConnectedData)

    // Data to exchange between libs
    REGISTER_BOOL(daqEnabled)
    REGISTER_BOOL(takeOff)
    REGISTER_U64(freeSpaceMB)
    REGISTER_U32(currentWaypointIndex)
    REGISTER_U8(autopilotStatus)
    REGISTER_U8(traceQuality)

    // Text message will be sent to the 'ground'
    REGISTER_TOPIC(textToGround, TextToGround)

    // Application settings
    REGISTER_INT(APP_STATUS_PERIOD_MS)
    REGISTER_INT(APP_MIN_FREE_SPACE_MB)
    REGISTER_I32(APP_POSITION_LOG_PERIOD_MS)
    REGISTER_INT(APP_TELEMETRY_PERIOD_MS)
    REGISTER_INT(APP_PAYLOAD_START_DELAY_S)
    REGISTER_BOOL(APP_VERBOSE)
    REGISTER_BOOL(APP_DISABLE_WIFI_IN_AIR)
    REGISTER_U32(APP_LOG_SPLIT_WAYPOINTS)
    REGISTER_U32(APP_LOG_SPLIT_TIME_S)
    REGISTER_U32(APP_LOG_SPLIT_SIZE_MB)
    REGISTER_U32(APP_LOG_SPLIT_TRACES)

    // Common Altimeter Settings
    REGISTER_F32(ALTIMETER_MIN_ALTITUDE_M)
    REGISTER_F32(ALTIMETER_MAX_ALTITUDE_M)
    REGISTER_F32(ALTIMETER_ZERO_LEVEL_M)
    REGISTER_INT(ALTIMETER_LP_FILTER_LENGTH)
    REGISTER_INT(ALTIMETER_IGNORE_ERRORS)

    // Common Gas Detector Settings
    REGISTER_F32(GAS_DETECTOR_MIN_CONCENTRATION_PPM)
    REGISTER_F32(GAS_DETECTOR_MAX_CONCENTRATION_PPM)
    REGISTER_F32(GAS_DETECTOR_ZERO_LEVEL_PPM)

    // Common Metal Detector Settings
    REGISTER_F32(METAL_DETECTOR_MIN_OUTPUT_VALUE_MV)
    REGISTER_F32(METAL_DETECTOR_MAX_OUTPUT_VALUE_MV)

    // Common Echosounder Settings
    REGISTER_F32(ECHOSOUNDER_MIN_DEPTH_M)
    REGISTER_F32(ECHOSOUNDER_MAX_DEPTH_M)
    REGISTER_F32(ECHOSOUNDER_CABLE_LENGTH_M)

    // DJI Settings
    REGISTER_U32(DJI_APP_ID)
    REGISTER_STR(DJI_APP_KEY)
    REGISTER_STR(DJI_SERIAL_DEVICE)
    REGISTER_INT(DJI_BAUD_RATE)
    REGISTER_INT(DJI_RESPONSE_TIMEOUT_S)
    REGISTER_INT(DJI_SENDING_PERIOD_MS)

    // Mavlink Autopilot Settings
    REGISTER_STR(MAV_CONNECTION_TYPE)  // Uart or Tcp
    REGISTER_STR(MAV_SERIAL_DEVICE)
    REGISTER_INT(MAV_BAUD_RATE)
    REGISTER_U16(MAV_SYSTEM_ID)
    REGISTER_U16(MAV_COMPONENT_ID)
    REGISTER_INT(MAV_SENDING_PERIOD_MS)
    REGISTER_BOOL(MAV_V2_EXTENSION)

    // Terrain Following Settings
    REGISTER_F32(TF_FLIGHT_SPEED_MPS)
    REGISTER_F32(TF_FAIL_SAFE_ALTITUDE_M)
    REGISTER_F32(TF_TARGET_ALTITUDE_M)
    REGISTER_F32(TF_CLIMB_RATE)
    REGISTER_F32(TF_DESCENT_RATE)
    REGISTER_F32(TF_ALT_ACCEL)
    REGISTER_F32(TF_ALT_P)
    REGISTER_STR(TF_TURN_TYPE)
    REGISTER_STR(TF_ALTITUDE_SOURCE)
    REGISTER_BOOL(TF_DEBUG_LOG)
    REGISTER_F32(TF_ACCEPTANCE_RADIUS_M)
    REGISTER_F32(TF_POS_P)
    REGISTER_F32(TF_ACCEL_XY)
    REGISTER_BOOL(TF_POS_CTRL_DEBUG_LOG)
    REGISTER_BOOL(TF_VELOCITY_CONTROL)      // Used to switch between attitude and position contol

    // Grasshopper Setting
    REGISTER_F32(GH_ALTITUDE_PRECISION_M)
    REGISTER_F32(GH_DESCENT_SPEED_MPS)
    REGISTER_F32(GH_DESCENT_ALTITUDE_M)
    REGISTER_F32(GH_FLIGHT_SPEED_MPS)
    REGISTER_F32(GH_TARGET_ALTITUDE_M)
    REGISTER_INT(GH_HOVER_TIME_S)
    REGISTER_F32(GH_CLIMB_RATE)
    REGISTER_BOOL(GH_DEBUG_LOG)
    REGISTER_F32(GH_ACCEPTANCE_RADIUS_M)
    REGISTER_F32(GH_ALT_ACCEL)
    REGISTER_F32(GH_ALT_P)
    REGISTER_STR(GH_ALTITUDE_SOURCE)
    REGISTER_F32(GH_POS_P)
    REGISTER_F32(GH_ACCEL_XY)
    REGISTER_BOOL(GH_VELOCITY_CONTROL)      // Used to switch between attitude and position contol

    // Altimeter Simulator Settings
    REGISTER_INT(ALTIMETER_SIMULATOR_PERIOD_MS)
    REGISTER_F32(ALTIMETER_SIMULATOR_MIN_RANGE_M)
    REGISTER_F32(ALTIMETER_SIMULATOR_MAX_RANGE_M)
    REGISTER_F32(ALTIMETER_SIMULATOR_DELTA_M)

    // GPR Simulator Settings
    REGISTER_INT(GPR_SIMULATOR_PERIOD_MS)
    REGISTER_INT(GPR_SIMULATOR_SAMPLE_COUNT)
    REGISTER_INT(GPR_SIMULATOR_WAVE_COUNT)
    REGISTER_U8(GPR_SIMULATOR_SAMPLE_BIT_DEPTH)
    REGISTER_BOOL(GPR_SIMULATOR_MSBYTE_FIRST)
    REGISTER_INT(GPR_SIMULATOR_TELEMETRY_PERIOD_MS)

    // Attollo Wasp Altimeter Settings
    REGISTER_STR(ATTOLLO_WASP_SERIAL_DEVICE)
    REGISTER_INT(ATTOLLO_WASP_BAUD_RATE)
    REGISTER_INT(ATTOLLO_WASP_FREQUENCY_HZ)
    REGISTER_INT(ATTOLLO_WASP_AVERAGING)

    // Nano Radar Altimeter Settings
    REGISTER_STR(NANORADAR_NRA_SERIAL_DEVICE)
    REGISTER_INT(NANORADAR_NRA_BAUD_RATE)
    REGISTER_INT(NANORADAR_NRA_AVERAGING)

    // Lightware SF11/C Altimeter Settings
    REGISTER_STR(LIGHTWARE_SF_CONNECTION_TYPE)
    REGISTER_STR(LIGHTWARE_SF_UART_SERIAL_DEVICE)
    REGISTER_INT(LIGHTWARE_SF_UART_BAUD_RATE)
    REGISTER_STR(LIGHTWARE_SF_I2C_DEVICE_ADDRESS)

    // Lightware SF11/C Altimeter Simulator Settings
    REGISTER_STR(LIGHTWARE_SIMULATOR_SERIAL_DEVICE)
    REGISTER_F32(LIGHTWARE_SIMULATOR_MIN_RANGE_M)
    REGISTER_F32(LIGHTWARE_SIMULATOR_MAX_RANGE_M)
    REGISTER_F32(LIGHTWARE_SIMULATOR_DELTA_M)
    REGISTER_INT(LIGHTWARE_SIMULATOR_PERIOD_MS)

    // PadarTeam Cobra GPR Setting
    REGISTER_U16(RADARTEAM_COBRA_TIME_RANGE_NS)
    REGISTER_STR(RADARTEAM_COBRA_BLUETOOTH_NAME)
    REGISTER_INT(RADARTEAM_COBRA_TELEMETRY_PERIOD_MS)
    REGISTER_STR(RADARTEAM_COBRA_MODEL)

    // RadSys Zond GPR Settings
    REGISTER_STR(RADSYS_ZOND_IP_ADDRESS)
    REGISTER_INT(RADSYS_ZOND_PORT)
    REGISTER_INT(RADSYS_ZOND_SAMPLE_COUNT)
    REGISTER_STR(RADSYS_ZOND_MODE)
    REGISTER_STR(RADSYS_ZOND_SOUNDING_MODE)
    REGISTER_INT(RADSYS_ZOND_TELEMETRY_PERIOD_MS)

    REGISTER_U16(RADSYS_ZOND_TIME_RANGE_NS_1)
    REGISTER_STR(RADSYS_ZOND_FILTER_1)
    REGISTER_U16(RADSYS_ZOND_PULSE_DELAY_1)

    REGISTER_U16(RADSYS_ZOND_TIME_RANGE_NS_2)
    REGISTER_STR(RADSYS_ZOND_FILTER_2)
    REGISTER_U16(RADSYS_ZOND_PULSE_DELAY_2)
    REGISTER_BOOL(RADSYS_ZOND_RAW_LOG)

    REGISTER_F64(RADSYS_ZOND_OFFSET_FORWARD_M_1)
    REGISTER_F64(RADSYS_ZOND_OFFSET_FORWARD_M_2)
    REGISTER_F64(RADSYS_ZOND_OFFSET_RIGHT_M_1)
    REGISTER_F64(RADSYS_ZOND_OFFSET_RIGHT_M_2)

    // Pergam Simulator Settings
    REGISTER_STR(PERGAM_SIMULATOR_SERIAL_DEVICE)
    REGISTER_STR(PERGAM_SIMULATOR_MODEL)

    // Echologger Simulator Settings
    REGISTER_STR(ECHOLOGGER_SIMULATOR_SERIAL_DEVICE)
    REGISTER_BOOL(ECHOLOGGER_SIMULATOR_CONST_MODE)
    REGISTER_BOOL(ECHOLOGGER_SIMULATOR_SIN_MODE)
    REGISTER_F32(ECHOLOGGER_SIMULATOR_DELTA_M)

    // Pergam LMM Settings
    REGISTER_STR(PERGAM_LMM_SERIAL_DEVICE)
    REGISTER_F32(PERGAM_LMM_FREQUENCY_HZ)

    // Pergam Falcon Settings
    REGISTER_STR(PERGAM_FALCON_SERIAL_DEVICE)
    REGISTER_F32(PERGAM_FALCON_FREQUENCY_HZ)

    // Echologger ECT400 Settings
    REGISTER_INT(ECHOLOGGER_ECT_START_DELAY_S)
    REGISTER_STR(ECHOLOGGER_ECT_SERIAL_DEVICE)
    REGISTER_INT(ECHOLOGGER_ECT_BAUD_RATE)

    REGISTER_STR(ECHOLOGGER_ECT_MODE)
    REGISTER_F32(ECHOLOGGER_ECT_RANGE_M)
    REGISTER_F32(ECHOLOGGER_ECT_FREQUENCY_HZ)
    REGISTER_INT(ECHOLOGGER_ECT_DEADZONE_MM)
    REGISTER_INT(ECHOLOGGER_ECT_ALT_THRESHOLD_PCT)
    REGISTER_INT(ECHOLOGGER_ECT_TXLENGTH_US)
    REGISTER_INT(ECHOLOGGER_ECT_GAIN_DB)
    REGISTER_BOOL(ECHOLOGGER_ECT_RAW_LOG)
    REGISTER_F32(ECHOLOGGER_ECT_MIN_SENSOR_DEPTH_M)
    REGISTER_F32(ECHOLOGGER_ECT_MAX_SENSOR_ANGLE_DEG)

    // Geonics Simulator Settings
    REGISTER_STR(GEONICS_SIMULATOR_SERIAL_DEVICE)
    REGISTER_STR(GEONICS_SIMULATOR_MODE)
    REGISTER_F32(GEONICS_SIMULATOR_FREQUENCY_HZ)

    // Geonics EM 61 Metal Detector Settings
    REGISTER_STR(GEONICS_EM_61_CONNECTION_TYPE)
    REGISTER_STR(GEONICS_EM_61_SERIAL_DEVICE)
    REGISTER_STR(GEONICS_EM_61_BLUETOOTH_NAME)
    REGISTER_INT(GEONICS_EM_61_BAUD_RATE)
    REGISTER_INT(GEONICS_EM_61_START_DELAY_S)
    REGISTER_BOOL(GEONICS_EM_61_RAW_LOG)

    // Unstable features (add below)
    // Example: REGISTER_BOOL(UNSTABLE_MY_FEATURE)
    REGISTER_BOOL(UNSTABLE_FLATBUFFERS_MESSAGE)
    REGISTER_BOOL(UNSTABLE_ALGORITHM_OBSTACLE_AVOIDANCE)

    // Obstacle Avoidance Mode
    REGISTER_STR(OA_ALTITUDE_SOURCE)
    REGISTER_F32(OA_ALTITUDE_LIMIT_M)
    REGISTER_STR(OA_SAFETY_ACTION)
    REGISTER_BOOL(OA_AUTOSTART_ENABLE)
    REGISTER_F32(OA_AUTOSTART_ALT_OFFSET)

private:
    QSettings *settings();
    QString settingNameToKey(const char *group, const char *param, const char *separator = "/");

private:
    QSettings *m_settings = nullptr;
    QHash<QString, bool> m_debugOptions;
    QHash<QString, void*> m_singletons;
    QHash<QString, QString> m_settingsSet;
    bool m_verbose = false;
};

inline App *app() { return reinterpret_cast<App*>(qApp); }

#endif // APP_H
