#include "accelerometer_gatt_service.h"
#include "mpu6050_driver.h"

/*
*
* Description of the Acccelerometer Service
*
* characteristics:
* 	- X axis value: 2 bytes
*		- Y axis value: 2 bytes
*   - Z axis value: 2 bytes
*
*/

static struct bt_uuid_128 accel_uuid = BT_UUID_INIT_128(
	0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 accel_x_uuid = BT_UUID_INIT_128(
	0x78, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 accel_y_uuid = BT_UUID_INIT_128(
	0x79, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 accel_z_uuid = BT_UUID_INIT_128(
	0x7a, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
	0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static ssize_t read_u16(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			void *buf, u16_t len, u16_t offset, u16_t axis_value)
{
	u16_t value = sys_cpu_to_le16(axis_value);

	return bt_gatt_attr_read(conn, attr, buf, len, offset, &value,
				 sizeof(value));
}

static ssize_t read_u16_x(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			void *buf, u16_t len, u16_t offset)
{
	return read_u16(conn, attr, buf, len, offset, get_accel_x());
}

static ssize_t read_u16_y(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			void *buf, u16_t len, u16_t offset)
{
	return read_u16(conn, attr, buf, len, offset, get_accel_y());
}

static ssize_t read_u16_z(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			void *buf, u16_t len, u16_t offset)
{
	return read_u16(conn, attr, buf, len, offset, get_accel_z());
}

static struct bt_gatt_attr accel_attrs[] = {
	BT_GATT_PRIMARY_SERVICE(&accel_uuid),
	BT_GATT_CHARACTERISTIC(&accel_x_uuid.uuid, BT_GATT_CHRC_READ, BT_GATT_PERM_READ, read_u16_x, NULL, NULL),
	BT_GATT_CHARACTERISTIC(&accel_y_uuid.uuid, BT_GATT_CHRC_READ, BT_GATT_PERM_READ, read_u16_y, NULL, NULL),
	BT_GATT_CHARACTERISTIC(&accel_z_uuid.uuid, BT_GATT_CHRC_READ, BT_GATT_PERM_READ, read_u16_z, NULL, NULL),
};

static struct bt_gatt_service accel_svc = BT_GATT_SERVICE(accel_attrs);

static void bt_ready(int err)
{
		if (err)
		{
			printk("Bluetooth init failed (err %d)\n", err);
			return;
		}

		printk("Bluetooth initialized\n");

		bt_gatt_service_register(&accel_svc);

		// err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
		if (err) {
			printk("Advertising failed to start (err %d)\n", err);
			return;
		}

		printk("Advertising successfully started\n");
}

static void connected(struct bt_conn *conn, u8_t err)
{
	if (err) {
		printk("Connection failed (err %u)\n", err);
	} else {
		printk("Connected\n");
	}
}

static void disconnected(struct bt_conn *conn, u8_t reason)
{
	printk("Disconnected (reason %u)\n", reason);
}

int init_accelerometer_gatt_service()
{
	int err;
	struct bt_conn_cb conn_callbacks;

	conn_callbacks.connected = connected;
	conn_callbacks.disconnected = disconnected;

	if ((err = bt_enable(bt_ready)))
	{
		printk("Bluetooth init failed (err %d)\n", err);
		return err;
	}

	// connection callback
	bt_conn_cb_register(&conn_callbacks);
	// authentificated connection callback
	// bt_conn_auth_cb_register(&auth_cb_display);

	return 0;
}
