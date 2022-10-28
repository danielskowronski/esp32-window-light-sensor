# ESP32 based Window Light Sensor with HomeKit and MQTT support

Used as a sensor for automatic shades closure when it's too bright for delicate eyes of nerd.

HomeKit for automation, MQTT for reporting to HomeAssistant. 

## Software

Arduino sketch - [./software/esp32-window-light-sensor/](./software/esp32-window-light-sensor/)

### Libraries

- ESP32
- HomeSpan
    - until https://github.com/HomeSpan/HomeSpan/issues/414 is resolved, fork https://github.com/danielskowronski/HomeSpan is required for "upgraded" Home

## Hardware

ESP32 board with breadboard components - [./hardware/HARDWARE.md](./hardware/HARDWARE.md)

## Usage

### HomeKit

Follow [HomeSpan User Guide](https://github.com/HomeSpan/HomeSpan/blob/master/docs/UserGuide.md)

### MQTT

TBD (not yet implemented)
