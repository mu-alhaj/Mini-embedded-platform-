# MicroRepo
This repo includes a simpel embedded paltform running on an stm32F3 but it can be easily ported to other microcontrollers.
#### Description of the project:
The boot will be able to receive commands via the serial uart and parse it into command, which will be redirected to a respective module to be executed. Each command have a unique ID reffering to a specific function. In order for the commands to work, they should be added in the sw of the stm and to the python script. In the command set there is command responsible for erasing flash memory and repogramming it to write new application (perfor an update over the uart). The boot should be able to verify the application software and jumb to the application when push the blue push button.
## content of the repo
The repo contains two parts, one on the PC side represented by a python script to communicate with the microcontroller and the other part is the software of the stm32 ( boot / app )
### CubeMx - Stm32
#### Share sources
Here is the place where all modules used by both boot and application exist. The folder is included in both procject but only needed modules are used.
#### Boot
The boot is the masterpiece of this repo. As soon as the boot starts, it will blink a led each 50ms by pasing the toggle function to a scheduler that will run it periodically when time is up. Anytime while the boot is running, the user should be able to run the python script to start a firmware upgrade for the application. The python script will erase the application flash area, read the hex file of the application, parse its data, calculate size and crc and send it over to the stm32. The stm32 will receive the data and place it in the applicatoin memory area and verify the crc. After pushing the blue push button, the boot will write a flag to the simulated eeprom to tell boot to go ahead and jump to application on the next restart, and then trigger a system restart ( this will save alot of struggle trying to deinitialize alot of peripherals before leaving the bool ). On the next start boot will check the eeprom for the flag, and if it was set tol keep going to application, the systemRestart module will perform a jump to application by setting the pointing the stack pointer and the reset handler to its respective in the application and call the reset handler of the application.
##### Some interesting modules used by the boot:
- serial :
- command queue:
- command handler:
- flash:
- 
#### Appicatoin
This project is not supposed to do much but blink and being able to change the blink delay time when pushing the blue button, just to demonstrate that interrupts still working after the jump to application.
### python
