
# CX3AR0234CS Custom Camera Firmware

STATUS: DEVELOPMENT (need help)

This is the firmware for a custom camera using a AR0234CS Sensor and CX3 (CYUSB3065-BZXI) chip by Infineon. 

Requirements:
* Receive images from the camera at a monochrome resolution of 1920x1200 at 100fps in a lossless format.

## How to Help

See the issues for a detailed description of what where we need help. 


## Getting Started

### Prerequisites
1. Get the camera board and plug it in to your computer.
2. Install the [Cypress FX3 SDK](https://www.cypress.com/documentation/software-and-drivers/ez-usb-fx3-software-development-kit)

### Build the Firmware

1. Open the project in the EZ-USB Suite
2. Right click on the project and click "Build"

### Flash the Firmware
1. Press Ctrl + 6 to open the control center. There you should see any device that are available to flash.
2. Click on the device.
3. Select the Program menu > FX3 > RAM
4. After the firmware is flashed, the camera can be used with the default Camera App on Windows.


## AR0234CS Sensor
[Product Link](https://www.onsemi.com/products/sensors/image-sensors/ar0234cs)

This sensor is monochrome and has a resolution of 1920x1200. It can output images at 100fps.



## CX3 (CYUSB3065-BZXI) chip by Infineon
The CX3 Infineon chip is a USB 3.0 peripheral controller that enables developers to add USB 3.0 connectivity to any image sensor compliant with the Mobile Industry Processor Interface (MIPI) Camera Serial Interface Type 2 (CSI-2) standard.

