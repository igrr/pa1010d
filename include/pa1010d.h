#pragma once

#include "esp_err.h"
#include "driver/i2c.h"

/**
 * @file pa1010d.h
 * @brief Driver for the PA1010D GPS module
 *
 * To use this driver:
 * - Initialize the driver with pa1010d_init()
 * - Call pa1010d_get_nmea_msg() to get the NMEA message from the GPS
 * - Deinitialize the driver with pa1010d_deinit()
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief PA1010D driver configuration
 */
typedef struct {
    i2c_port_t i2c_port;    /*!< I2C bus number to which the GPS is connected */
    uint8_t i2c_dev_addr;   /*!< I2C device address of the GPS. Typically 0x10. */
} pa1010d_config_t;

/**
 * @brief PA1010D driver handle
 */
typedef struct pa1010d_t *pa1010d_handle_t;

/**
 * @brief Initialize the PA1010D driver
 *
 * @param config Pointer to the configuration struct. The driver makes a copy, so can point to a local variable.
 * @param[out] out_handle  Pointer to a variable to receive the driver handle.
 * @return esp_err_t  ESP_OK on success, ESP_ERR_NO_MEM if out of memory.
 */
esp_err_t pa1010d_init(const pa1010d_config_t *config, pa1010d_handle_t *out_handle);

/**
 * @brief Deinitialize the PA1010D driver
 *
 * @param handle Driver handle obtained from pa1010d_init(), or NULL
 * @return esp_err_t  ESP_OK on success.
 */
esp_err_t pa1010d_deinit(pa1010d_handle_t handle);

/**
 * @brief Get the NMEA message from the GPS
 *
 * Reads the NMEA message from the GPS. The resulting string is stripped of CR, LF and is null-terminated.
 *
 * @param handle Driver handle obtained from pa1010d_init()
 * @param out_buf Destination buffer for the NMEA message, has to be at least 4 bytes long
 * @param out_buf_len Length of the destination buffer in bytes
 * @param timeout_ms Timeout in milliseconds for receiving a single character
 * @return esp_err_t
 *      - ESP_OK on success
 *      - ESP_ERR_TIMEOUT if no message was received within the timeout
 *      - ESP_ERR_INVALID_ARG if the buffer too short
 */
esp_err_t pa1010d_get_nmea_msg(pa1010d_handle_t handle, char *out_buf, size_t out_buf_len, unsigned timeout_ms);

#ifdef __cplusplus
}
#endif
