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

#ifndef CSVLOG_H
#define CSVLOG_H

#include "logfile.h"
#include <logged.h>

#include <QMutex>

#include <typeinfo>

namespace CsvLogConstants {

const int FloatPrecision = 2;
const int DoublePrecision = 6;

}

class CsvLog : public LogFile, public Logged
{
    Q_OBJECT
public:
    enum ParameterType : uint8_t {
        CONSTANT = 0,   // Constant values are written for each request of write(), writeGroup(...)
        OPTIONAL = 1    // Optional values are written only by request of writeGroup(...)
    };

    CsvLog(char separator = ',', QObject *parent = nullptr);

    void addParameter(const QString &name, const QString &group = "") { addParameter(CONSTANT, name, group); }
    void addParameters(const QStringList &names, const QString &group = "") { addParameters(CONSTANT, names, group); }

    void addParameter(ParameterType paramType, const QString &name, const QString &group = "");
    void addParameters(ParameterType paramType, const QStringList &names, const QString &group = "");

    void setValue(QString name, QString value, QString group = "");

    template<class T>
    void setValue(const QString &name, T value, const QString &group = "",
                  typename std::enable_if<std::is_floating_point<T>::value >::type* = 0)
    {
        setValue(name, QString().setNum(value, 'f', typeid(float) == typeid(value) ? CsvLogConstants::FloatPrecision
                                                                                   : CsvLogConstants::DoublePrecision), group);
    }

    template<class T>
    void setValue(const QString &name, T value, int precision, const QString &group = "",
                  typename std::enable_if<std::is_floating_point<T>::value >::type* = 0)
    {
        setValue(name, QString().setNum(value, 'f', precision), group);
    }

    template<class T>
    void setValue(const QString &name, T value, const QString &group = "", typename std::enable_if<std::is_integral<T>::value >::type* = 0)
    {
        setValue(name, QString().setNum(value), group);
    }

    void close() override;
    void clearValue(const QString &name, const QString &group = "") { m_values.remove(paramId(name, group)); }

    /**
     * @brief write
     * Set and write parameters passed into the method with constant parameters (time, geo coordinates, roll, pitch, yaw, etc).
     * Other columns write empty
     * @param params
     * @param group
     */
    void writeGroup(const QHash<QString, QString> &params, const QString &group = "");

public slots:
    /**
     * @brief write
     * Write constant parameters (time, geo coordinates, roll, pitch, yaw, etc)
     */
    void write();
    /**
     * @brief write
     * Set parameters and write constant parameters (time, geo coordinates, roll, pitch, yaw, etc).
     * @param params
     * @param group
     */
    void write(const QHash<QString, QString> &params, const QString &group = ""); // TODO: not used

protected:
    QString suffix() const override { return ".csv"; }

private:
    struct Parameter {
        Parameter() { }
        Parameter(const QString &name) : name(name) { }

        QString name;
        bool isNew = false;
        bool isConstant = true;

        bool operator== (const Parameter &other)
        {
            return (name == other.name);
        }
    };

    bool addParameterToHeader(const QString &name, const QString &group, ParameterType paramType);
    void writeHeader();
    QString paramId(const QString &name, const QString &group) { return group + ":" + name; }
    void write(QStringList values);

private:
    char m_separator;

    QMap<QString, QList<Parameter>> m_parameters;
    QHash<QString, QString> m_values;

    QMutex m_mutex;
};

#endif // CSVLOG_H
