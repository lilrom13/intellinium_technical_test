#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <gpio.h>

#include "led_work.h"

#define STACKSIZE 1024
#define PRIORITY 7

static struct device *gpio_dev;
static s32_t sleep_time[3] = { 2000, 500, 1000 };
static int click = 1;

static void toogle_led_work()
{
	u32_t led_value;

	while (1)
	{
			gpio_pin_read(gpio_dev, LED, &led_value);
			gpio_pin_write(gpio_dev, LED, !led_value);

			k_sleep(sleep_time[click % 3]);
	}
}
K_THREAD_DEFINE(thread_led_id, STACKSIZE, toogle_led_work, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);

void test(int value)
{
	if (value)
		k_thread_resume(thread_led_id);
	else
		k_thread_suspend(thread_led_id);
}

void change_frequency()
{
	click++;
}

int init_led_work()
{
  int ret;

  gpio_dev = device_get_binding(LED_PORT);

  if (!gpio_dev) {
		printk("GPIO: Device driver not found.\n");
		return -1;
	}

  if ((ret = gpio_pin_configure(gpio_dev, LED, GPIO_DIR_OUT)) != 0)
  {
    printk("Error during gpio configuration %d.\n", ret);
    return -1;
  }

  return 0;
}
