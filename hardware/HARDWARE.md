# Hardware

## Bill of Materials

- MCU: ESP32 Dev Board - see [MCU.md](MCU.md)
- light sensor: **BH1750** (`BH1750FVI`) in GY-302 kit
- temperature sensor: **BMP280** in HW-611 kit
- 5x7cm double-sided prototype board
- IDC10 board connector: 1x angled, 1x straight
- IDC10 terminated ribbon cable to be routed at edge of window glass (so it can be behind shades), 3m
- plastic case - Kradex Z34B

### Light sensor selection

- photoresistor: random accuracy, external ADC required
- phototransistor TEMT6000: <570nm, external ADC required
- BH1750: cheap, +/-20% accurate
- TSL2581FN: more precise, but no ready-made integration, not easily available in reasonable package
- TSL25911: seems the best, but not easily available at all

### Cable selection

4 lines would be enough, but IDC10 is easier to obtain and is mure rigid. Future iterations may repurpose USB cable.

## Schematic

Fritzing project: [esp32-lightsensor.fzz](esp32-lightsensor.fzz)

[![](./breadboard.jpg)](./breadboard.jpg)

## I2C

### BMP280

I2C is enabled by default, pulling **CSB** pin low will turn I2C off and activate SPI. That means while it should be connected to VDD (but never pulled high when VDD is floating) it can be safely left floating.

I2C address is `0x76` when **SDO** pin is pulled low or floating, pulling it high will switch it to `0x77`. I2C address can be switched at any moment.

To set address in code, update following line in [`../software/esp32-window-light-sensor.ino`](../software/esp32-window-light-sensor.ino):

```c
#define BMP280_I2C_ADDRESS 0x76
```

### BH1750

I2C address is `0x23` when **SDO** pin is pulled low or floating, pulling it high will switch it to `0x5C`.

To set address in code, update following line in [`../software/esp32-window-light-sensor.ino`](../software/esp32-window-light-sensor.ino):

```c
#define BH1750_I2C_ADDRESS 0x23
```
