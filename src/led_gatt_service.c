#include <bluetooth/bluetooth.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#include "led_work.h"

static u8_t ct;

/* Acceleromter Service Variables */
static struct bt_uuid_128 led_uuid = BT_UUID_INIT_128(
	0xde, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static ssize_t write_ct(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			const void *buf, u16_t len, u16_t offset,
			u8_t flags)
{
	u8_t *value = attr->user_data;

	if (offset + len > sizeof(ct)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);

  test(*value);

	return len;
}

/* Acceleromter Service Declaration */
static struct bt_gatt_attr attrs[] = {
	BT_GATT_PRIMARY_SERVICE(&led_uuid),
	BT_GATT_CHARACTERISTIC(&led_uuid.uuid, BT_GATT_CHRC_WRITE, BT_GATT_PERM_WRITE_AUTHEN, NULL, write_ct, &ct),
};

static struct bt_gatt_service led_svc = BT_GATT_SERVICE(attrs);

int init_led_service()
{
  return bt_gatt_service_register(&led_svc);
}
