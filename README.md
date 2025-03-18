# lolin32-ble-keyboard

This is a simple example of a BLE keyboard using the Lolin32 board and the ESP32's bluetooth stack.

## Circuit diagram

![Circuit diagram](./dia/circuit.svg)

## How it works

The code is pretty simple. It uses the ESP32's bluetooth stack to create a BLE HID device.

The device can send 3 keys: `a`, `b` and `c`.

The keys are sent when the corresponding button is pressed (or in my case, when the corresponding pin is grounded).

The built-in LED is turned on when the device is connected and turned off when it is disconnected to bluetooth.

Three separate LED's are turned on when the corresponding button is pressed:
i.e. `a` button turns on the left LED, `b` button turns on the middle LED and `c` button turns on the right LED.
