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

#ifndef MONITORMESSAGES_H
#define MONITORMESSAGES_H

/** Description of messages 'Onboard -> Mobile' and 'Mobile -> Onboard' */

#include <app.h>
#include <protocol.h>

// ----------------------
// Onboard to Mobile
// ----------------------

inline uint16_t getMonitorMessageId(const QByteArray &data)
{
    QDataStream stream(data);
    checkEndian(stream);
    uint16_t typeMessage;
    stream >> typeMessage;
    return typeMessage;
}

/**
 * @brief The base message class
 */
template<typename T>
class Message
{
public:
    Message() : m_type(MonitorMessageId::InvalidMessageId) { }
    Message(MonitorMessageId type) : m_type(type) { }

    T *payload() { return &m_payload; }

    friend QDataStream &operator <<(QDataStream &stream, const Message &data)
    {
        stream << data.m_type;
        stream << data.m_payload;
        return stream;
    }

    friend QDataStream &operator >>(QDataStream &stream, Message &data)
    {
        stream >> data.m_type;
        stream >> data.m_payload;
        return stream;
    }

private:
    uint16_t m_type;
    T m_payload;
};

struct VehicleStateHeader
{
    uint8_t flightMode;
    uint8_t displayMode;
    uint8_t errorCode;
    uint8_t gnssHealth;
    float roll;
    float pitch;
    float yaw;
    double latitude;
    double longitude;
    float altitude;
    float height;

    friend QDataStream &operator <<(QDataStream &stream, const VehicleStateHeader &data);
};

struct GprTraceHeader
{
    uint16_t counter;
    uint8_t chunkCount;
    uint16_t timeRange;
    uint8_t chunkNumber;

    friend QDataStream &operator <<(QDataStream &stream, const GprTraceHeader &data);
};

struct GprTrace
{
    GprTraceHeader header;
    QByteArray data;

    friend QDataStream &operator <<(QDataStream &stream, const GprTrace &data);
};

struct GprStatus {
    uint8_t gprConnected;
    uint8_t daqEnabled;
    uint16_t freeSpaceMB;
    uint8_t loggerError;
    uint8_t powerStatus;
    uint8_t autopilotStatus;
    uint8_t traceQuality;

    friend QDataStream &operator <<(QDataStream &stream, const GprStatus &data);
};

struct AltimeterStatus
{
    float height;
    ScalarSensorStatusId statusId;

    friend QDataStream &operator <<(QDataStream &stream, const AltimeterStatus &data);
};

struct ScalarSensorStatus
{
    PayloadId payloadId;
    float value;
    ScalarSensorStatusId statusId;

    friend QDataStream &operator <<(QDataStream &stream, const ScalarSensorStatus &data);
};

struct TerrainFollowingStatusHeader
{
    double targetAltitude;
    double safeAltitude;
    double missionVelocity;
    double returnVelocity;
    AlgorithmState state;
    MissionState missionState;

    friend QDataStream &operator <<(QDataStream &stream, const TerrainFollowingStatusHeader &data);
};

struct TextHeader
{
    QByteArray textAsUtf8;

    friend QDataStream &operator <<(QDataStream &stream, const TextHeader &data)
    {
        stream.device()->write(data.textAsUtf8);
        return stream;
    }
};

struct FlatbuffersHeader
{
    std::vector<uint8_t> buffer;

    friend QDataStream &operator <<(QDataStream &stream, const FlatbuffersHeader &data)
    {
        stream.device()->write(QByteArray(reinterpret_cast<const char *>(data.buffer.data()), data.buffer.size()));
        return stream;
    }
    friend QDataStream &operator >>(QDataStream &stream, FlatbuffersHeader &data)
    {
        QByteArray buffer = stream.device()->readAll();
        data.buffer.clear();
        data.buffer.resize(buffer.size());
        memcpy(data.buffer.data(), buffer.data(), buffer.size());
        return stream;
    }
};

typedef Message<TerrainFollowingStatusHeader> TerrainFollowingStatusMessage;
typedef Message<VehicleStateHeader> VehicleStatusMessage;
typedef Message<GprTrace> GprTraceMessage;
typedef Message<GprStatus> GprStatusMessage;
typedef Message<AltimeterStatus> AltimeterStatusMessage;
typedef Message<ScalarSensorStatus> ScalarSensorStatusMessage;
typedef Message<TextHeader> TextMessage;
typedef Message<FlatbuffersHeader> FlatbuffersMessage;

// ----------------------
// Mobile to Onboard
// ----------------------

struct SimpleCommandHeader {
    uint8_t value;

    friend QDataStream &operator >>(QDataStream &stream, SimpleCommandHeader &data)
    {
        stream >> data.value;
        return stream;
    }
};

struct GrasshopperHeader {
    float descentAltitude;
    float descentSpeed;
    int hoverTime;
    AlgorithmState state;
    MissionState missionState;
    float targetAltitude;
    float speed; // missionVelocity

    friend QDataStream &operator <<(QDataStream &stream, const GrasshopperHeader &data);
    friend QDataStream &operator >>(QDataStream &stream, GrasshopperHeader &data);
};

struct ConfigureTerrainFollowingHeader {
    double targetAltitude;
    double safeAltitude;
    double missionVelocity;
    double returnVelocity;

    friend QDataStream &operator >>(QDataStream &stream, ConfigureTerrainFollowingHeader &data);
};


struct ObstacleAvoidanceHeader {
    float altitude;
    uint8_t safeAction;
    AlgorithmState state;

    friend QDataStream &operator <<(QDataStream &stream, const ObstacleAvoidanceHeader &data);
    friend QDataStream &operator >>(QDataStream &stream, ObstacleAvoidanceHeader &data);
};


typedef Message<SimpleCommandHeader> GprControlPayload;
typedef Message<GrasshopperHeader> ConfigureGrasshopperPayload;
typedef Message<SimpleCommandHeader> PowerControlPayload;
typedef Message<ConfigureTerrainFollowingHeader> ConfigureTerrainFollowingPayload;
typedef Message<ObstacleAvoidanceHeader> ConfigureObstacleAvoidancePayload;

// ----------------------
// Settings exchange between SkyHub and CPM
// ----------------------

struct SettingHeader {
    QString group;
    QString name;
    QString value;

    friend QDataStream &operator <<(QDataStream &stream, const SettingHeader &data);
    friend QDataStream &operator >>(QDataStream &stream, SettingHeader &data);
};

struct FirmwareHeader {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
    uint16_t build;

    friend QDataStream &operator <<(QDataStream &stream, const FirmwareHeader &data);
};

typedef Message<SettingHeader> SettingsMessage;
typedef Message<FirmwareHeader> FirmwareMessage;

#endif // MONITORMESSAGES_H
