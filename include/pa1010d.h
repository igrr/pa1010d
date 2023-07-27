#pragma once

#include "esp_err.h"
#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    i2c_port_t i2c_port;
    uint8_t i2c_dev_addr;
} pa1010d_config_t;

typedef struct pa1010d_t *pa1010d_handle_t;

esp_err_t pa1010d_init(const pa1010d_config_t *config, pa1010d_handle_t *out_handle);
esp_err_t pa1010d_deinit(pa1010d_handle_t handle);
esp_err_t pa1010d_get_nmea_msg(pa1010d_handle_t handle, char *out_buf, size_t out_buf_len, unsigned timeout_ms);

#ifdef __cplusplus
}
#endif
