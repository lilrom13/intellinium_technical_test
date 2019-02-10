#include "led_work.h"
#include "accel_work.h"
#include "gatt_services.h"
#include "button_interrupts.h"

void main(void)
{
	init_led_work();
	// init_accel_work();
	init_gatt_services();

	init_button_interrupts();

	return;
}
