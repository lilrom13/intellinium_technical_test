#ifndef LED_WORK_H
#define LED_WORK_H

#include <device.h>

#define LED_PORT LED0_GPIO_CONTROLLER
#define LED	LED0_GPIO_PIN

int init_led_work(void);
void test(int value);
void change_frequency(void);

#endif // LED_WORK_H
