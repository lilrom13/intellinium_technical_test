#ifndef MPU6050_DRIVER
#define MPU6050_DRIVER

#define MPU6050_I2C_ADDR      0x68
#define MPU6050_CHIP_ID_REG   0x75

#include <device.h>

int init_mpu6050(struct device *);
int update_accelerometer_values(struct device *);

u16_t get_accel_x(void);
u16_t get_accel_y(void);
u16_t get_accel_z(void);

#endif //MPU6050_DRIVER
