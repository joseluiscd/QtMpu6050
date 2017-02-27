#ifndef ACCELEROMETERBACKEND_H
#define ACCELEROMETERBACKEND_H

#include <QSensorBackend>
#include <QTimer>
#include "mpu6050.h"

class TimerSensorBackend : public QSensorBackend
{
    Q_OBJECT

public:
    TimerSensorBackend(Mpu6050 *d, QSensor *sensor, QObject *parent=0);

    void start();
    void stop();

protected slots:
    void checkReading();

protected:
    Mpu6050 *driver;
    QTimer *timer;
};

#endif // ACCELEROMETERBACKEND_H
