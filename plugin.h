#ifndef PLUGIN_H
#define PLUGIN_H

#include <QSensorPluginInterface>
#include <QSensorBackendFactory>
#include "backends.h"

class Plugin: public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "mpu6050.json")
    Q_INTERFACES(QSensorPluginInterface)


public:
    QSensorBackend *createBackend(QSensor *sensor);
    void registerSensors();

private:
    Mpu6050 *driver;
};

#endif // PLUGIN_H
