# Bare metal programming for popular microcontrollers:
## 1. Arduino Board - AtMega328P:
Bare metal C-programming code for blinking on board LED and UART.

### Execution instructions on Linux:
1. Install the ```avr-gcc``` toolchain:
      1. ```sudo apt-get update```
      2. ```sudo apt-get upgrade -y```
      3. ```sudo apt-get install gcc-avr binutils-avr avr-libc```
      4. ```sudo apt-get install avrdude```
3. Clone this repo.
4. Go to the project directory of interest: eg. [LED-Blink-UART]()
5. Open this directory in the Linux Terminal.
6. Connect the Arduino to your PC.
7. Run ```make```.
8. The code will get flashed into Arduino Memory.
9. You should be able to see the onboard led flashing.
10. Configure serial monitor on VS Code or similar to test the UART communication.

## 2. ItsyBitsy - AtMega32u4:
## 3. STM32F407VG Discovery Board:
## 4. STM32F411RE Nucleo Board:
