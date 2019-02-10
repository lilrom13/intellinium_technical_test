#include <bluetooth/bluetooth.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#include "accelerometer_gatt_service.h"
#include "mpu6050_driver.h"

static s16_t axis[3] = {0, 1, 2};// x = 0, y = 1, z = 2

/* Acceleromter Service Variables */
static struct bt_uuid_128 accel_uuid = BT_UUID_INIT_128(
	0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 accel_x_uuid = BT_UUID_INIT_128(
	0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 accel_y_uuid = BT_UUID_INIT_128(
	0xde, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 accel_z_uuid = BT_UUID_INIT_128(
	0xbc, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

	static ssize_t read_accel(struct bt_conn *conn, const struct bt_gatt_attr *attr,
				void *buf, u16_t len, u16_t offset)
	{
		u16_t value;
		const s16_t *axis = attr->user_data;

		switch (*axis)
		{
			case 0:
				value = get_accel_x();
			case 1:
				value = get_accel_y();
			case 2:
				value = get_accel_z();
		}

		printk("read value = %d\n", value);

		return bt_gatt_attr_read(conn, attr, buf, len, offset, &value,
					 sizeof(value));
	}

/* Acceleromter Service Declaration */
static struct bt_gatt_attr attrs[] = {
	BT_GATT_PRIMARY_SERVICE(&accel_uuid),
	BT_GATT_CHARACTERISTIC(&accel_x_uuid.uuid, BT_GATT_CHRC_READ, BT_GATT_PERM_READ_AUTHEN, read_accel, NULL, &axis[0]),
	BT_GATT_CHARACTERISTIC(&accel_y_uuid.uuid, BT_GATT_CHRC_READ, BT_GATT_PERM_READ_AUTHEN, read_accel, NULL, &axis[1]),
	BT_GATT_CHARACTERISTIC(&accel_z_uuid.uuid, BT_GATT_CHRC_READ, BT_GATT_PERM_READ_AUTHEN, read_accel, NULL, &axis[2]),
};

static struct bt_gatt_service accel_svc = BT_GATT_SERVICE(attrs);

int init_acceleromter_service()
{
  return bt_gatt_service_register(&accel_svc);
}
