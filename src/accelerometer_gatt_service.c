#include <bluetooth/bluetooth.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#include "accelerometer_gatt_service.h"

/* Acceleromter Service Variables */
static struct bt_uuid_128 accel_uuid = BT_UUID_INIT_128(
	0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

/* Acceleromter Service Declaration */
static struct bt_gatt_attr attrs[] = {
	BT_GATT_PRIMARY_SERVICE(&accel_uuid),
	BT_GATT_CHARACTERISTIC(&accel_uuid.uuid, BT_GATT_CHRC_READ, BT_GATT_PERM_READ, NULL, NULL, NULL),
};

static struct bt_gatt_service accel_svc = BT_GATT_SERVICE(attrs);

int init_acceleromter_service()
{
  return bt_gatt_service_register(&accel_svc);
}
