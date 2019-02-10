#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <i2c.h>

#include "accel_work.h"
#include "mpu6050_driver.h"

// accel fetching
static void fetch_accelerometer_work(struct k_work *work)
{
	update_accelerometer_values();
}
K_WORK_DEFINE(accel_work, fetch_accelerometer_work);

static void accel_timer_handler(struct k_timer *dummy)
{
    k_work_submit(&accel_work);
}
K_TIMER_DEFINE(accel_timer, accel_timer_handler, NULL);

int init_accel_work()
{
	struct device *i2c_dev;

	i2c_dev = device_get_binding(I2C_DEV);

	if (!i2c_dev) {
    printk("I2C: Device driver not found.\n");
    return -1;
  }

  // add return check
  init_mpu6050(i2c_dev);

  k_timer_start(&accel_timer, K_SECONDS(0.2), K_SECONDS(0.2));

  return 0;
}
