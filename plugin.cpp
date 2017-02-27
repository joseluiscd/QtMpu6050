#include "plugin.h"

QSensorBackend *Plugin::createBackend(QSensor *sensor)
{
    if(sensor->identifier() == AccelerometerBackend::id){
        return new AccelerometerBackend(driver, sensor);
    } else if(sensor->identifier() == GyroscopeBackend::id){
        return new GyroscopeBackend(driver, sensor);
    } else if(sensor->identifier() == TemperatureBackend::id){
        return new TemperatureBackend(driver, sensor);
    }
    return 0;
}

void Plugin::registerSensors()
{
    qWarning("Registering sensors");
    driver = new Mpu6050();
    QSensorManager::registerBackend(QAccelerometer::type, AccelerometerBackend::id, this);
    QSensorManager::registerBackend(QGyroscope::type, GyroscopeBackend::id, this);
    QSensorManager::registerBackend(QAmbientTemperatureSensor::type, TemperatureBackend::id, this);
}
