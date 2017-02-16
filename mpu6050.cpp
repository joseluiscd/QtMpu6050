#include "mpu6050.h"
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>

Mpu6050::Mpu6050()
    :accelReading(), gyroReading(), tempReading()
{
}

quint64 produceTimestamp()
{
    struct timespec tv;
    int ok;

    ok = clock_gettime(CLOCK_MONOTONIC, &tv);
    Q_ASSERT(ok == 0);

    quint64 result = (tv.tv_sec * 1000000ULL) + (tv.tv_nsec * 0.001); // scale to microseconds
    return result;
}

void Mpu6050::start()
{
    //Copied from https://github.com/randrews7/rpi-mpu6050

    if ((fd = open(MPU_I2C, O_RDWR)) < 0) {
            printf("Failed to open i2c port\n");
            exit(1);
    }

    if (ioctl(fd, I2C_SLAVE, MPU_ADDRESS) < 0) {
            printf("Unable to get bus access to talk to slave\n");
            exit(1);
    }

    int8_t power = i2c_smbus_read_byte_data(fd, MPU_POWER1);
    i2c_smbus_write_byte_data(fd, MPU_POWER1, ~(1 << 6) & power);

    //https://github.com/Tijndagamer/mpu6050/
    //Set accelerometer to 2G
    i2c_smbus_write_byte_data(fd, MPU_ACCEL_CONFIG, 0);

    //Set gyroscope to 250 deg
    i2c_smbus_write_byte_data(fd, MPU_GYRO_CONFIG, 0);

    pollAccelerometer();
    pollGyroscope();
    pollTemperature();
}

void Mpu6050::pollAccelerometer()
{
    int16_t xaccel = i2c_smbus_read_word_data(fd, MPU_ACCEL_XOUT);
    int16_t yaccel = i2c_smbus_read_word_data(fd, MPU_ACCEL_YOUT);
    int16_t zaccel = i2c_smbus_read_word_data(fd, MPU_ACCEL_ZOUT);


    accelReading.setX(xaccel * GRAVITY / ACCEL_SCALE);
    accelReading.setY(yaccel * GRAVITY / ACCEL_SCALE);
    accelReading.setZ(zaccel * GRAVITY / ACCEL_SCALE);

    accelReading.setTimestamp(produceTimestamp());
}

void Mpu6050::pollGyroscope()
{
    int16_t xgyro = i2c_smbus_read_word_data(fd, MPU_GYRO_XOUT);
    int16_t ygyro = i2c_smbus_read_word_data(fd, MPU_GYRO_YOUT);
    int16_t zgyro = i2c_smbus_read_word_data(fd, MPU_GYRO_ZOUT);


    gyroReading.setX(xgyro / GYRO_SCALE);
    gyroReading.setY(ygyro / GYRO_SCALE);
    gyroReading.setZ(zgyro / GYRO_SCALE);

    gyroReading.setTimestamp(produceTimestamp());
}

void Mpu6050::pollTemperature()
{
    int16_t temp = i2c_smbus_read_word_data(fd, MPU_GYRO_XOUT);

    tempReading.setTemperature(temp / 340.0f + 36.53f);
    tempReading.setTimestamp(produceTimestamp());
}
