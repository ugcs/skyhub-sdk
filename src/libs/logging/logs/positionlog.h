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

#ifndef POSITIONLOG_H
#define POSITIONLOG_H

#include "csvlog.h"

#include <app.h>
#include <expirablevalue.h>

class PositionLog : public CsvLog
{
    Q_OBJECT
public:
    static PositionLog *instance();

    void write();
    void writeGroup(const QHash<QString, QString> &params, const QString &group);

    void start();
    void stop();

    void close() override;

    template<class T>
    void writeGroup(const QHash<QString, T> &params, const QString &group = "",
                    typename std::enable_if<std::is_floating_point<T>::value >::type* = 0)
    {
        QHash<QString, QString> values;
        const auto paramKeys = params.keys();
        for (const auto &name : paramKeys)
            values[name] = QString().setNum(params[name], 'f', typeid(float) == typeid(params[name]) ? CsvLogConstants::FloatPrecision
                                                                                                     : CsvLogConstants::DoublePrecision);
        writeGroup(values, group);
    }

    template<class T>
    void writeGroup(const QHash<QString, T> &params, const QHash<QString, int> &precision, const QString &group = "",
                    typename std::enable_if<std::is_floating_point<T>::value >::type* = 0)
    {
        QHash<QString, QString> values;
        const auto paramKeys = params.keys();
        for (const auto &name : paramKeys)
            values[name] = QString().setNum(params[name], 'f', precision[name]);
        writeGroup(values, group);
    }

    template<class T>
    void writeGroup(const QHash<QString, T> &params, int precision, const QString &group = "",
                    typename std::enable_if<std::is_floating_point<T>::value >::type* = 0)
    {
        QHash<QString, QString> values;
        const auto paramKeys = params.keys();
        for (const auto &name : paramKeys)
            values[name] = QString().setNum(params[name], 'f', precision);
        writeGroup(values, group);
    }

    template<class T>
    void writeGroup(const QHash<QString, T> &params, const QString &group = "",
                    typename std::enable_if<std::is_integral<T>::value >::type* = 0)
    {
        QHash<QString, QString> values;
        const auto paramKeys = params.keys();
        for (const auto &name : paramKeys)
            values[name] = QString().setNum(params[name]);
        writeGroup(values, group);
    }

protected:
    QString suffix() const override { return "-position.csv"; }

private:
    PositionLog(QObject *parent = nullptr);

    void timerEvent(QTimerEvent *event) override;
    void onSegYTrace (const SegYTraceNumber &value);

private:
    static int m_counter;

    int m_timerId = -1;
    int m_periodMs = 0;
    bool m_rtkIsValid = false;
    bool m_gprConnected = false;
    bool m_echosounderConnected = false;
    bool m_daqEnabled = false;

    ExpirableValue<bool> m_validValues;
    static int m_flushingCounter;
};

#endif // POSITIONLOG_H
