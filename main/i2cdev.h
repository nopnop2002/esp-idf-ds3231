#ifndef MAIN_I2CDEV_H_
#define MAIN_I2CDEV_H_

#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 2, 0))
#include "driver/i2c_master.h"
#else
#include "driver/i2c.h"
#endif

#define I2CDEV_TIMEOUT 1000 // millSecond

typedef struct {
	i2c_port_t port;	// I2C port number
	uint8_t addr;		// I2C address
	gpio_num_t sda_io_num;	// GPIO number for I2C sda signal
	gpio_num_t scl_io_num;	// GPIO number for I2C scl signal
	uint32_t clk_speed;		// I2C clock frequency for master mode
#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 2, 0))
	i2c_master_bus_handle_t _i2c_bus_handle;
	i2c_master_dev_handle_t _i2c_dev_handle;
#endif
} i2c_dev_t;

esp_err_t i2c_dev_init(i2c_dev_t *dev);
esp_err_t i2c_dev_read(const i2c_dev_t *dev, const void *out_data, size_t out_size, void *in_data, size_t in_size);
esp_err_t i2c_dev_write(const i2c_dev_t *dev, const void *out_reg, size_t out_reg_size, const void *out_data, size_t out_size);
inline esp_err_t i2c_dev_read_reg(const i2c_dev_t *dev, uint8_t reg, void *in_data, size_t in_size)
{
	return i2c_dev_read(dev, &reg, 1, in_data, in_size);
}

inline esp_err_t i2c_dev_write_reg(const i2c_dev_t *dev, uint8_t reg, const void *out_data, size_t out_size)
{
	return i2c_dev_write(dev, &reg, 1, out_data, out_size);
}
#endif /* MAIN_I2CDEV_H_ */
