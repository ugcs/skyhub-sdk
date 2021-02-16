#ifndef EXPIRABLEVALUE_H
#define EXPIRABLEVALUE_H

#include <QElapsedTimer>

template<typename T>
class ExpirableValue
{
public:
    explicit ExpirableValue<T>(T initialValue = T(), qint64 expireDelayMs = 5000)
        : m_expiredValue(initialValue),
          m_value(initialValue),
          m_timeoutMs(expireDelayMs)
    {
        m_time.start();
    }

    T& value()
    {
        if (m_time.elapsed() > m_timeoutMs) {
            m_value = m_expiredValue;
            m_time.restart();
        }
        return m_value;
    }

    T& operator=(const T &other)
    {
        setValue(other);
        return m_value;
    }

    void setExpiredValue(const T &value) { m_expiredValue = value; }

private:
    void setValue(const T &value)
    {
        m_value = value;
        m_time.restart();
    }

private:
    T m_expiredValue;
    T m_value;
    qint64 m_timeoutMs;

    QElapsedTimer m_time;
};

#endif // EXPIRABLEVALUE_H
