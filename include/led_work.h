#ifndef __LED_WORK_H__
#define __LED_WORK_H__

#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <gpio.h>

#define GPIO_DEV "GPIO_0"
#define LED_PIN 14

int init_led_work();

#endif // __LED_WORK_H__
