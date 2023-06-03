#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdbool.h>
#include "driver/i2c.h"

#include "i2cdev.h"

/**
 * Alarms
 */
typedef enum {
    DS3231_ALARM_NONE = 0,//!< No alarms
    DS3231_ALARM_1,       //!< First alarm
    DS3231_ALARM_2,       //!< Second alarm
    DS3231_ALARM_BOTH     //!< Both alarms
} ds3231_alarm_t;

typedef enum
{
    DS3231_1HZ          = 0x00,
    DS3231_1024HZ       = 0x01,
    DS3231_4096HZ       = 0x02,
    DS3231_8192HZ       = 0x03
} ds3231_sqw_t;

/**
 * First alarm rate
 */
typedef enum {
    DS3231_ALARM1_EVERY_SECOND = 0,
    DS3231_ALARM1_MATCH_SEC,
    DS3231_ALARM1_MATCH_SECMIN,
    DS3231_ALARM1_MATCH_SECMINHOUR,
    DS3231_ALARM1_MATCH_SECMINHOURDAY,
    DS3231_ALARM1_MATCH_SECMINHOURDATE
} ds3231_alarm1_rate_t;

/**
 * Second alarm rate
 */
typedef enum {
    DS3231_ALARM2_EVERY_MIN = 0,
    DS3231_ALARM2_MATCH_MIN,
    DS3231_ALARM2_MATCH_MINHOUR,
    DS3231_ALARM2_MATCH_MINHOURDAY,
    DS3231_ALARM2_MATCH_MINHOURDATE
} ds3231_alarm2_rate_t;

#define DS3231_ADDR 0x68 //!< I2C address

#define DS3231_STAT_OSCILLATOR 0x80
#define DS3231_STAT_32KHZ      0x08
#define DS3231_STAT_BUSY       0x04
#define DS3231_STAT_ALARM_2    0x02
#define DS3231_STAT_ALARM_1    0x01

#define DS3231_CTRL_SQUAREWAVE_BB 0x40
#define DS3231_CTRL_TEMPCONV      0x20
#define DS3231_CTRL_ALARM_INTS    0x04
#define DS3231_CTRL_ALARM2_INT    0x02
#define DS3231_CTRL_ALARM1_INT    0x01

#define DS3231_ALARM_WDAY   0x40
#define DS3231_ALARM_NOTSET 0x80

#define DS3231_ADDR_TIME    0x00
#define DS3231_ADDR_ALARM1  0x07
#define DS3231_ADDR_ALARM2  0x0b
#define DS3231_ADDR_CONTROL 0x0e
#define DS3231_ADDR_STATUS  0x0f
#define DS3231_ADDR_AGING   0x10
#define DS3231_ADDR_TEMP    0x11

#define DS3231_12HOUR_FLAG  0x40
#define DS3231_12HOUR_MASK  0x1f
#define DS3231_PM_FLAG      0x20
#define DS3231_MONTH_MASK   0x1f

uint8_t bcd2dec(uint8_t val);
uint8_t dec2bcd(uint8_t val);
esp_err_t ds3231_init_desc(i2c_dev_t *dev, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio);
esp_err_t ds3231_set_time(i2c_dev_t *dev, struct tm *time);
esp_err_t ds3231_get_raw_temp(i2c_dev_t *dev, int16_t *temp);
esp_err_t ds3231_get_temp_integer(i2c_dev_t *dev, int8_t *temp);
esp_err_t ds3231_get_temp_float(i2c_dev_t *dev, float *temp);
esp_err_t ds3231_get_time(i2c_dev_t *dev, struct tm *time);


/**
 * @brief Check which alarm(s) have past
 *
 * Sets alarms to `DS3231_ALARM_NONE`/`DS3231_ALARM_1`/`DS3231_ALARM_2`/`DS3231_ALARM_BOTH`
 *
 * @param dev Device descriptor
 * @param[out] alarms Alarms
 * @return ESP_OK to indicate success
 */
esp_err_t ds3231_get_alarm_flags(i2c_dev_t *dev, ds3231_alarm_t *alarms);

/**
 * @brief Clear alarm past flag(s)
 *
 * Pass `DS3231_ALARM_1`/`DS3231_ALARM_2`/`DS3231_ALARM_BOTH`
 *
 * @param dev Device descriptor
 * @param alarms Alarms
 * @return ESP_OK to indicate success
 */
esp_err_t ds3231_clear_alarm_flags(i2c_dev_t *dev, ds3231_alarm_t alarms);

/**
 * @brief Set alarms
 *
 * `alarm1` works with seconds, minutes, hours and day of week/month, or fires every second.
 * `alarm2` works with minutes, hours and day of week/month, or fires every minute.
 *
 * Not all combinations are supported, see `DS3231_ALARM1_*` and `DS3231_ALARM2_*` defines
 * for valid options you only need to populate the fields you are using in the `tm` struct,
 * and you can set both alarms at the same time (pass `DS3231_ALARM_1`/`DS3231_ALARM_2`/`DS3231_ALARM_BOTH`).
 *
 * If only setting one alarm just pass 0 for `tm` struct and `option` field for the other alarm.
 * If using ::DS3231_ALARM1_EVERY_SECOND/::DS3231_ALARM2_EVERY_MIN you can pass 0 for `tm` struct.
 *
 * If you want to enable interrupts for the alarms you need to do that separately.
 *
 * @return ESP_OK to indicate success
 */
esp_err_t ds3231_set_alarm(i2c_dev_t *dev, ds3231_alarm_t alarms, struct tm *time1,
        ds3231_alarm1_rate_t option1, struct tm *time2, ds3231_alarm2_rate_t option2);

/**
 * @brief enable alarm interrupts (and disables squarewave)
 *
 * Pass `DS3231_ALARM_1`/`DS3231_ALARM_2`/`DS3231_ALARM_BOTH`.
 *
 * If you set only one alarm the status of the other is not changed
 * you must also clear any alarm past flag(s) for alarms with
 * interrupt enabled, else it will trigger immediately.
 *
 * @param dev Device descriptor
 * @param alarms Alarms
 * @return ESP_OK to indicate success
 */
esp_err_t ds3231_enable_alarm_ints(i2c_dev_t *dev, ds3231_alarm_t alarms);

/*
 * @param dev Device descriptor
 * @param alarms Alarms
 * @return ESP_OK to indicate success
 */
esp_err_t ds3231_enable_sqw(i2c_dev_t *dev, ds3231_sqw_t mode);

/**
 * @brief Disable alarm interrupts
 *
 * Does not (re-)enable squarewave
 *
 * @param dev Device descriptor
 * @param alarms Alarm
 * @return ESP_OK to indicate success
 */
esp_err_t ds3231_disable_alarm_ints(i2c_dev_t *dev, ds3231_alarm_t alarms);

#ifdef __cplusplus
}
#endif
