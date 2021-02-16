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

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>

#include <QByteArray>
#include <QDataStream>

// TODO: Share or join enums to different .h-files depends on using
enum PayloadId : uint8_t
{
    Undefined           = 0x00,
    Gpr                 = 0x01,
    GasDetector         = 0x02,
    Altimeter           = 0x04,
    EchoSounder         = 0x06,
    MetalDetector       = 0x07,

    SkyhubFlightController = 0x80,

    UserPayloadFirst    = 0xC0,
    UserPayloadLast     = 0xDF,

    Flatbuffers         = 0xEE, // TODO: equals Gpr now
    Firmware            = 0xEF, // TODO: equals Gpr now
    Settings            = 0xFA, // TODO: equals Gpr now
    OnBoardStatus       = 0xFB, // TODO: equals Gpr now
    VehicleStatus       = 0xFD, // TODO: equals Gpr now
    Text                = 0xFE, // TODO: equals Gpr now

    Broadcast           = 0xFF
};

enum MessageId : uint8_t
{
    StatusId  = 0x00,   // Status with text
    ArrayId   = 0x01,   // Data array
    ValueId   = 0x02,   // Single value
    TelemetryId = 0x03, // Telemetry message
    EventId = 0x04,     // Event message
    CommandId = 0x80,   // Command to payload
};

enum OnboardMessageId : uint8_t
{
    TelemetryMessageIndex = 0x02,
    PongMessageIndex = 0x04,
    CommandMessageIndex = 0xFC,
    PingMessageIndex = 0xFE
};

enum MonitorMessageId : uint16_t
{
    // Onboard -> Mobile
    InvalidMessageId = 0x00,
    VehicleStatusMessageId = 0x02, // TODO: Legacy
    GprStatusMessageId = 0x03,
    GprTraceMessageId = 0x04,
    MetalDetectorValueMessageId = 0x05,
    TerrainFollowingStatusMessageId = 0x06,
    AltimeterStatusMessageId = 0x07,
    GHStatusMessageId = 0x08,
    GasDetectorStatusMessageId = 0x09,
    EchoSounderStatusMessageId = 0x0A,
    FirmwareMessageId = 0x0B,
    ObstacleAvoidanceStatusMessageId = 0x0C,

    TextMessageId = 0xFE,
    ResultMessageId = 0xFF,

    // Mobile -> Onboard
    VehicleControlMessageId = 0x82,
    GprControlMessageId = 0x83,
    ConfigureTerrainFollowingMessageId = 0x84,
    StartTerrainFollowingMessageId = 0x85,
    ConfigureGrasshopperMessageId = 0x86,
    PayloadPowerMessageId = 0x87,
    PauseTerrainFollowingMessageId = 0x88,

    // Settings
    SettingsMessageId = 0x90,         // Send current setting to mobile
    UdpateSettingsMessageId = 0x91,   // Update setting from mobile

    // Firmware
    FirmwareAskedMessageId = 0x92,

    ConfigureObstacleAvoidanceMessageId = 0x93,
    ActivateObstacleAvoidanceMessageId = 0x94,
    DeactivateObstacleAvoidanceMessageId = 0x95,
    
    StartGrasshopperMessageId = 0x96,
    PauseGrasshopperMessageId = 0x97,

    FlatbuffersSendMessageId = 0xFA,
    FlatbuffersReceiveMessageId = 0xFB,

    TextCommandId = 0xFD,
    PingMessageId = 0xFE,
    RestartMessageId = 0xFF,
};

enum PayloadStatusLevel : uint8_t
{
    Inactive = 0,
    Normal = 1,
    Warning = 2
};

enum AutopilotStatusId : uint8_t
{
    Disconnected = 0,   // Not connected or in a bad state
    WaitingForData = 1, // Connected, but no data within 5 seconds
    Active = 2          // Connected and there is data
};

inline void checkEndian(QDataStream &stream) {
    constexpr union {
        uint32_t i;
        char c[4];
    } checker = { 0x01020304 };

    if (checker.c[0] != 1 && stream.byteOrder() != QDataStream::LittleEndian)
        stream.setByteOrder(QDataStream::LittleEndian);
}

template<typename T>
inline QByteArray toByteArray(T &data)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    checkEndian(stream);
    stream << data;
    return array;
}

template<typename T>
inline T toMessage(QByteArray data)
{
    T message;
    QDataStream stream(&data, QIODevice::ReadOnly);
    checkEndian(stream);
    stream >> message;
    return message;
}
#endif // PROTOCOL_H
