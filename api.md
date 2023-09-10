# API Reference

## Header files

- [include/pa1010d.h](#file-includepa1010dh)

## File include/pa1010d.h

## Structures and Types

| Type | Name |
| ---: | :--- |
| struct | [**pa1010d\_config\_t**](#struct-pa1010d_config_t) <br>_PA1010D driver configuration._ |
| typedef struct pa1010d\_t \* | [**pa1010d\_handle\_t**](#typedef-pa1010d_handle_t)  <br>_PA1010D driver handle._ |

## Functions

| Type | Name |
| ---: | :--- |
|  esp\_err\_t | [**pa1010d\_deinit**](#function-pa1010d_deinit) (pa1010d\_handle\_t handle) <br>_Deinitialize the PA1010D driver._ |
|  esp\_err\_t | [**pa1010d\_get\_nmea\_msg**](#function-pa1010d_get_nmea_msg) (pa1010d\_handle\_t handle, char \* out\_buf, size\_t out\_buf\_len, unsigned timeout\_ms) <br>_Get the NMEA message from the GPS._ |
|  esp\_err\_t | [**pa1010d\_init**](#function-pa1010d_init) (const [**pa1010d\_config\_t**](#struct-pa1010d_config_t)\* config, pa1010d\_handle\_t \* out\_handle) <br>_Initialize the PA1010D driver._ |


## Structures and Types Documentation

### struct `pa1010d_config_t`

_PA1010D driver configuration._
Variables:

-  uint8\_t i2c_dev_addr  <br>I2C device address of the GPS. Typically 0x10.

-  i2c\_port\_t i2c_port  <br>I2C bus number to which the GPS is connected

### typedef `pa1010d_handle_t`

_PA1010D driver handle._
```c
typedef struct pa1010d_t* pa1010d_handle_t;
```


## Functions Documentation

### function `pa1010d_deinit`

_Deinitialize the PA1010D driver._
```c
esp_err_t pa1010d_deinit (
    pa1010d_handle_t handle
) 
```

**Parameters:**


* `handle` Driver handle obtained from pa1010d\_init(), or NULL 


**Returns:**

esp\_err\_t ESP\_OK on success.
### function `pa1010d_get_nmea_msg`

_Get the NMEA message from the GPS._
```c
esp_err_t pa1010d_get_nmea_msg (
    pa1010d_handle_t handle,
    char * out_buf,
    size_t out_buf_len,
    unsigned timeout_ms
) 
```

Reads the NMEA message from the GPS. The resulting string is stripped of CR, LF and is null-terminated.



**Parameters:**


* `handle` Driver handle obtained from pa1010d\_init() 
* `out_buf` Destination buffer for the NMEA message, has to be at least 4 bytes long 
* `out_buf_len` Length of the destination buffer in bytes 
* `timeout_ms` Timeout in milliseconds for receiving a single character 


**Returns:**

esp\_err\_t
* ESP\_OK on success
* ESP\_ERR\_TIMEOUT if no message was received within the timeout
* ESP\_ERR\_INVALID\_ARG if the buffer too short
### function `pa1010d_init`

_Initialize the PA1010D driver._
```c
esp_err_t pa1010d_init (
    const pa1010d_config_t * config,
    pa1010d_handle_t * out_handle
) 
```

**Parameters:**


* `config` Pointer to the configuration struct. The driver makes a copy, so can point to a local variable. 
* `out_handle` Pointer to a variable to receive the driver handle. 


**Returns:**

esp\_err\_t ESP\_OK on success, ESP\_ERR\_NO\_MEM if out of memory.


