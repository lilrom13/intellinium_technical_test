#include <i2c.h>
#include <misc/byteorder.h>

#include "mpu6050_driver.h"

static struct device * mpu6050;
static s16_t accel[3];

int update_accelerometer_values()
{
  int ret;

	if ((ret = i2c_burst_read(mpu6050, ADDR, 0x3B, (u8_t *)accel, 6)) < 0) {
    printk("Error %d during burst read reg 0x%2x.\n", ret, 0x3B);
		return ret;
	}

  accel[0] = sys_be16_to_cpu(accel[0]);
  accel[1] = sys_be16_to_cpu(accel[1]);
  accel[2] = sys_be16_to_cpu(accel[2]);

  printk("x = %d, y = %d, z = %d\n", accel[0], accel[1], accel[2]);

  return 0;
}

s16_t get_accel_x()
{
  return accel[0];
}

s16_t get_accel_y()
{
  return accel[1];
}

s16_t get_accel_z()
{
  return accel[2];
}

int init_mpu6050(struct device *dev)
{
  int ret;
  u8_t chep_id;

  mpu6050 = dev;

  if ((ret = i2c_reg_update_byte(mpu6050, ADDR, PWR_MGMT_1_REG, BIT(6), 0 << 6)) < 0)
  {
    printk("Error %d during read reg 0x%2x.\n", ret, PWR_MGMT_1_REG);
    return ret;
  }

  if ((ret = i2c_reg_read_byte(mpu6050, ADDR, WHO_I_AM_REG, &chep_id)) != 0)
  {
    printk("Error %d during read reg 0x%2x.\n", ret, WHO_I_AM_REG);
    return ret;
  }

  printk("chep id = %x\n", chep_id);

  int i;
  for (i = 0; i < 4; i++) {
		if (BIT(i+1) == 2) {
			break;
		}
	}

	if (i == 4) {
		printk("Invalid value for accel full-scale range.");
		return -1;
	}

	if (i2c_reg_write_byte(mpu6050, ADDR,
			       ACCEL_CONFIG_REG,
			       i << 3) < 0) {
		printk("Failed to write accel full-scale range.");
		return -1;
	}

  return 0;
}
