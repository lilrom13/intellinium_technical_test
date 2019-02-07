#include "led_work.h"

static struct device *gpio_dev;

void toogle_led_work(struct k_work *work)
{
	u32_t led_value;

	gpio_pin_read(gpio_dev, LED, &led_value);
	gpio_pin_write(gpio_dev, LED, !led_value);
}
K_WORK_DEFINE(led_work, toogle_led_work);

void led_timer_handler(struct k_timer *dummy)
{
    k_work_submit(&led_work);
}
K_TIMER_DEFINE(led_timer, led_timer_handler, NULL);

void test(int value)
{
}

int init_led_work()
{
  int ret;

  gpio_dev = device_get_binding(LED_PORT);

  if (!gpio_dev) {
		printk("GPIO: Device driver not found.\n");
		return -1;
	}

  // Init led
  if ((ret = gpio_pin_configure(gpio_dev, LED, GPIO_DIR_OUT)) != 0)
  {
    printk("Error during gpio configuration %d.\n", ret);
    return -1;
  }

  k_timer_start(&led_timer, K_SECONDS(0.5), K_SECONDS(0.5));

  return 0;
}
