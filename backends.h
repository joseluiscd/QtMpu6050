#ifndef BACKENDS_H
#define BACKENDS_H

#include "timersensorbackend.h"

class AccelerometerBackend : public TimerSensorBackend
{
    Q_OBJECT
public:
    AccelerometerBackend(Mpu6050 *d, QSensor *sensor, QObject *parent=0);
    static const char *id;
};

class GyroscopeBackend : public TimerSensorBackend
{
    Q_OBJECT
public:
    GyroscopeBackend(Mpu6050 *d, QSensor *sensor, QObject *parent=0);
    static const char *id;
};


class TemperatureBackend : public TimerSensorBackend
{
    Q_OBJECT
public:
    TemperatureBackend(Mpu6050 *d, QSensor *sensor, QObject *parent=0);
    static const char *id;
};
#endif // BACKENDS_H
