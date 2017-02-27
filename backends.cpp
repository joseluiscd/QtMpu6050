#include "backends.h"

const char* AccelerometerBackend::id = "mpu6050.accelerometer";

AccelerometerBackend::AccelerometerBackend(Mpu6050 *d, QSensor *sensor, QObject *parent)
    :TimerSensorBackend(d, sensor, parent)
{
    this->setReading(driver->getAccelerometerReading());
}

const char* GyroscopeBackend::id = "mpu6050.gyroscope";

GyroscopeBackend::GyroscopeBackend(Mpu6050 *d, QSensor *sensor, QObject *parent)
    :TimerSensorBackend(d, sensor, parent)
{
    this->setReading(driver->getGyroscopeReading());
}

const char* TemperatureBackend::id = "mpu6050.temperature";

TemperatureBackend::TemperatureBackend(Mpu6050 *d, QSensor *sensor, QObject *parent)
    :TimerSensorBackend(d, sensor, parent)
{
    this->setReading(driver->getTemperatureReading());
}
