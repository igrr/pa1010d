#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "pa1010d.h"

static const char* TAG = "example";

void app_main(void)
{
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 4,
        .scl_io_num = 5,
        .master.clk_speed = 100000,
    };

    ESP_ERROR_CHECK(
        i2c_param_config(I2C_NUM_0, &i2c_config));

    ESP_ERROR_CHECK(
        i2c_driver_install(I2C_NUM_0,
                           I2C_MODE_MASTER,
                           0, 0, 0));

    pa1010d_config_t config = {
        .i2c_port = I2C_NUM_0,
        .i2c_dev_addr = 0x10,
    };
    pa1010d_handle_t handle = NULL;
    ESP_ERROR_CHECK(pa1010d_init(&config, &handle));

    char nmea_msg_buf[200];
    while (true) {
        esp_err_t err = pa1010d_get_nmea_msg(handle,
                             nmea_msg_buf,
                             sizeof(nmea_msg_buf),
                             1000);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error getting NMEA message: 0x%x", err);
            continue;
        }

        ESP_LOGI(TAG, "Got message: '%s'", nmea_msg_buf);
    }
}
