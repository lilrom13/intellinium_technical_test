#include <i2c.h>

#include "mpu6050_driver.h"

static u16_t accelerometer_mesures[3];

int update_accelerometer_values(struct device *i2c_dev)
{
  // int ret;

	// if ((ret = i2c_burst_read(i2c_dev, MPU6050_I2C_ADDR, 0x3B, (u8_t *)buf, 6)) < 0) {
  //   printk("Error %d during burst read reg 0x%2x.\n", ret, 0x3B);
	// 	return ret;
	// }

  return 0;
}

u16_t get_accel_x()
{
  return accelerometer_mesures[0];
}

u16_t get_accel_y()
{
  return accelerometer_mesures[1];
}

u16_t get_accel_z()
{
  return accelerometer_mesures[2];
}

int init_mpu6050(struct device *i2c_dev)
{
  int ret;
  u8_t chep_id;

  if ((ret = i2c_reg_update_byte (i2c_dev, MPU6050_I2C_ADDR, 0x6B, BIT(6), 0 << 6)) < 0)
  {
    printk("Error %d during read reg 0x%2x.\n", ret, 0x6B);
    return ret;
  }

  if ((ret = i2c_reg_read_byte(i2c_dev, MPU6050_I2C_ADDR, 0x75, &chep_id)) != 0)
  {
    printk("Error %d during read reg 0x%2x.\n", ret, 0x75);
    return ret;
  }

  printk("chep id = %x\n", chep_id);

  if ((ret = i2c_reg_write_byte(i2c_dev, MPU6050_I2C_ADDR, 0x6B, 0x0)) < 0)
  {
    printk("Error %d during write reg 0x%2x.\n", ret, 0x6B);
    return ret;
  }

  return 0;
}
