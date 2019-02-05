#include "led_work.h"
#include "accel_work.h"
#include "accelerometer_gatt_service.h"

void main(void)
{
	init_led_work();
	init_accel_work();
	init_accelerometer_gatt_service();

	return;
}
