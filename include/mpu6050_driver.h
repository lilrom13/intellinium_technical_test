#ifndef MPU6050_DRIVER
#define MPU6050_DRIVER

#define ADDR              0x68
#define WHO_I_AM_REG      0x75
#define PWR_MGMT_1_REG    0x6B
#define ACCEL_CONFIG_REG  0x1C

#include <device.h>

int init_mpu6050(struct device *);
int update_accelerometer_values();

s16_t get_accel_x(void);
s16_t get_accel_y(void);
s16_t get_accel_z(void);

#endif //MPU6050_DRIVER
