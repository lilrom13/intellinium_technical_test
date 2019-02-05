#ifndef __ACCEL_WORK_H__
#define __ACCEL_WORK_H__

#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <i2c.h>

#define I2C_DEV "I2C_0"

int init_accel_work();

#endif // __ACCEL_WORK_H__
