#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <misc/util.h>
#include <misc/printk.h>

#include "button_interrupts.h"
#include "led_work.h"

#define PORT	  SW0_GPIO_CONTROLLER
#define PIN     SW0_GPIO_PIN

#define EDGE    (SW0_GPIO_FLAGS | GPIO_INT_EDGE)
#define PULL_UP SW0_GPIO_FLAGS

static struct gpio_callback gpio_cb;

void button_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins)
{
	change_frequency();
}

int init_button_interrupts()
{
  struct device *gpiob;

	gpiob = device_get_binding(PORT);
	if (!gpiob) {
		printk("error\n");
		return -1;
	}

	gpio_pin_configure(gpiob, PIN,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE);

	gpio_init_callback(&gpio_cb, button_pressed, BIT(PIN));

	gpio_add_callback(gpiob, &gpio_cb);
	gpio_pin_enable_callback(gpiob, PIN);

  return 0;
}
