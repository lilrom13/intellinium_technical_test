#ifndef __MPU6050_DRIVER__
#define __MPU6050_DRIVER__

#define MPU6050_I2C_ADDR      0x68
#define MPU6050_CHIP_ID_REG   0x75

#include <device.h>
#include <i2c.h>

int init_mpu6050(struct device *);
int fetch_accelerometer(struct device *);

#endif //__MPU6050_DRIVER__
