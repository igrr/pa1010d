# PA1010D I2C GPS driver

[![Component Registry](https://components.espressif.com/components/igrr/pa1010d/badge.svg)](https://components.espressif.com/components/igrr/pa1010d)

This repository contains an ESP-IDF driver for a PA1010D GPS receiver connected over I2C.

## Using the component

Run the following command in your ESP-IDF project to install this component:
```bash
idf.py add-dependency "igrr/pa1010d"
```

## Example

To run the provided example, create it as follows:

```bash
idf.py create-project-from-example "igrr/pa1010d:pa1010d-example"
```

Then build as usual:
```bash
cd pa1010d-example
idf.py build
```

And flash it to the board:
```bash
idf.py -p PORT flash monitor
```

The example uses GPIOs 4 and 5 for SDA and SCL, respectively.

## License

This component is provided under Apache 2.0 license, see [LICENSE](LICENSE.md) file for details.

