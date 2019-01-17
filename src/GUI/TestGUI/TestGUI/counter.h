#ifndef COUNTER_H
#define COUNTER_H
#include <QObject>
#pragma once

class Counter : public QObject
{
    Q_OBJECT

public:
    Counter() { m_value = false; }

    bool value() const { return m_value; }

public slots:
    void setValue(bool value);

signals:
    void valueChanged(bool newValue);

private:
    bool m_value;
};

#endif // COUNTER_H
