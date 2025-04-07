# Background


# Measurements

## Current Readings

control pin for LED when on: 0.40mA
control pin for LED when off: 0.08mA

Button Pin when not pressed: 0.00mA
Button Pin when pressed: 0.07mA

Therefore, current draw from the buttons and leds is a maximum of 3.76mA = `(0.40*8) + (0.07*8)`.

This is well below the chip's rated maximum of 240mA and should allow for a long life of the ESP32.
