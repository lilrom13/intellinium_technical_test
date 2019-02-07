#include "led_work.h"
//#include "accel_work.h"
#include "gatt_services.h"

#include <i2c.h>

#define I2C_DEV "I2C_0"

void main(void)
{
	// init_led_work();
	init_accel_work();
	// init_gatt_services();

	return;
}
