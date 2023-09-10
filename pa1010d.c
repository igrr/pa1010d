#include <stdio.h>
#include "pa1010d.h"
#include "esp_log.h"
#include "esp_check.h"
#include "driver/i2c.h"

struct pa1010d_t {
    pa1010d_config_t config;
    /* no other state to store for now */
};

esp_err_t pa1010d_init(const pa1010d_config_t *config, pa1010d_handle_t *out_handle)
{
    struct pa1010d_t *result = calloc(1, sizeof(struct pa1010d_t));
    if (result == NULL) {
        return ESP_ERR_NO_MEM;
    }
    result->config = *config;
    *out_handle = result;
    return ESP_OK;
}
esp_err_t pa1010d_deinit(pa1010d_handle_t handle)
{
    free(handle);
    return ESP_OK;
}

static esp_err_t read_one_byte(pa1010d_handle_t handle, char *out_byte, unsigned timeout_ms)
{
    return i2c_master_read_from_device(
               handle->config.i2c_port, handle->config.i2c_dev_addr, (uint8_t *) out_byte, 1, pdMS_TO_TICKS(timeout_ms));
}

esp_err_t pa1010d_get_nmea_msg(pa1010d_handle_t handle, char *out_buf, size_t out_buf_len, unsigned timeout_ms)
{
    char c;
    size_t len = 0;
    esp_err_t err;

    if (out_buf_len < 4) {
        return ESP_ERR_INVALID_ARG;
    }

    do {
        err = read_one_byte(handle, &c, timeout_ms);
        if (err != ESP_OK) {
            return err;
        }
    } while (c != '$');

    out_buf[len++] = c;

    do {
        err = read_one_byte(handle, &c, timeout_ms);
        if (err != ESP_OK) {
            return err;
        }
        if (c == 0) {
            continue;
        }
        if (c == '\n') {
            break;
        }
        if (c == '\r') {
            continue;
        }
        out_buf[len++] = c;
    } while (len < out_buf_len - 1);

    out_buf[len] = '\0';

    return ESP_OK;
}
