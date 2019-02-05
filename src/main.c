#include <errno.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <i2c.h>

#include "mpu6050_driver.h"

#define I2C_DEV "I2C_0"

int led = 0;
// led blinking
void toogle_led_work(struct k_work *work)
{
    /* do the processing that needs to be done periodically */
		if ((led++ % 2) == 0 )
			printk("tic");
		else
			printk("tac");
}
K_WORK_DEFINE(led_work, toogle_led_work);

void led_timer_handler(struct k_timer *dummy)
{
    k_work_submit(&led_work);
}
K_TIMER_DEFINE(led_timer, led_timer_handler, NULL);

// accel fetching
void fetch_accelerometer_work(struct k_work *work)
{
	// fetch accelerometer here
}
K_WORK_DEFINE(accel_work, fetch_accelerometer_work);

void accel_timer_handler(struct k_timer *dummy)
{
    k_work_submit(&accel_work);
}
K_TIMER_DEFINE(accel_timer, accel_timer_handler, NULL);

void main(void)
{
	struct device *i2c_dev;

	i2c_dev = device_get_binding(I2C_DEV);
	if (!i2c_dev) {
		printk("I2C: Device driver not found.\n");
		return;
	}

	// add return check
	init_mpu6050(i2c_dev);

	k_timer_start(&led_timer, K_SECONDS(1), K_SECONDS(1));
	k_timer_start(&accel_timer, K_SECONDS(1), K_SECONDS(2));
}
