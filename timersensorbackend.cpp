#include "timersensorbackend.h"

TimerSensorBackend::TimerSensorBackend(Mpu6050 *d, QSensor *sensor, QObject *parent)
    :QSensorBackend(sensor, parent), driver(d), timer(0)
{
    timer = new QTimer(this);
    float interval = 1000.0/this->sensor()->dataRate();
    timer->setInterval(interval);

    addOutputRange(-20, 20, 0.09);

    connect(timer, SIGNAL(timeout()), driver, SLOT(pollAccelerometer()));
    connect(timer, SIGNAL(timeout()), this, SLOT(checkReading()));
}

void TimerSensorBackend::start()
{
    driver->start();
    timer->start();
}

void TimerSensorBackend::stop()
{
    timer->stop();
}

void TimerSensorBackend::checkReading()
{
    //TODO check if new reading is available
    newReadingAvailable();
}
