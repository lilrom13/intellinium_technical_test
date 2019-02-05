#ifndef __BLUETOOTH_GATT_SERVICE_H__
#define __BLUETOOTH_GATT_SERVICE_H__

#include <zephyr/types.h>
#include <stddef.h>
#include <misc/printk.h>
#include <misc/util.h>
#include <misc/byteorder.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/gatt.h>

int init_accelerometer_gatt_service();

#endif // __BLUETOOTH_GATT_SERVICE_H__
