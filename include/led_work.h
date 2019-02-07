#ifndef __LED_WORK_H__
#define __LED_WORK_H__

#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <gpio.h>

#define LED_PORT LED0_GPIO_CONTROLLER
#define LED	LED0_GPIO_PIN

int init_led_work();
void test(int value);

#endif // __LED_WORK_H__
