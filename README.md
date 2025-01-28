# MicroRepo
This repo includes a simple embedded platform running on an STM32F3 but it can be easily ported to other microcontrollers.
#### Demonstration: 
In the video below you can see the python script running a fwUpgrade. In the upper right corner you can see the stm32 board, the software on the board is the boot, you can see the green led toggeled each 1 second. When running the script, the led will be toggled on each uart data receive. After the fw is updated successfully, the used pushes the blue button to jump to applicaton and the green led will be toggled each 50 ms, pressing the black button will reset the board and bring us back to the boot.
Ps: there is no audio in the video.

https://github.com/user-attachments/assets/d1ce435c-9aaf-48dc-96f6-a0d4c5c72878

#### Description of the project:
The boot will be able to receive commands via the serial uart and parse it into command, which will be redirected to a respective module to be executed. Each command have a unique ID referring to a specific function. In order for the commands to work, they should be added in the sw of the stm32 and to the python script. In the command set there is command responsible for erasing flash memory and repogramming it to write new application (perfor an update over the uart). The boot should be able to verify the application software and jumb to the application when push the blue push button.
## Content of the repo
The repo contains two parts, one on the PC side represented by a python script to communicate with the microcontroller and the other part is the software of the stm32 ( boot / app )
### CubeMx - Stm32
#### Shared sources
Here is the place where all modules used by both boot and application exist. The folder is included in both project but only the needed modules are used.
#### Boot
The boot is the masterpiece of this repo. As soon as the boot starts, it will toggle the green led each 1000 ms by pasing the toggle function to a scheduler that will run it periodically when time is up. Anytime while the boot is running, the user should be able to run the python script to start a firmware upgrade for the application. The python script will erase the application flash area, read the hex file of the application, parse its data, calculate size and crc and send it over to the stm32. The stm32 will receive the data and place it in the Application memory area and verify the crc. After pushing the blue push button, the boot will write a flag to the simulated eeprom to tell boot to go ahead and jump to application on the next restart, and then trigger a system restart ( this will save alot of struggle trying to deinitialize alot of peripherals before leaving the bool ). On the next start boot will check the eeprom for the flag, and if it was set to keep going to application, the systemRestart module will perform a jump to application by setting the stack pointer and the reset handler to its respective in the application and call the reset handler of the application.
##### Some interesting modules used by the boot:
- serial : The serial module should be able to listen to the uart, receive data and save it to dma. When new data is received, the crc of the data will be verified to ensure the integrity of the data and an ACK response is sent to the PC. After that, the new data will be pushed to the commands queue and the command handler call back ( that takes care about the command queue ) is pushed to the scheduler to be executed when leaving the interrupt context.
a command should look like this:
  **1 byte new command (0xab) | 2 bytes command id ( module & command ) | 2 bytes data size | data [...] | 4 bytes CRC**
  total command size should not exceed 256 bytes.
- command queue: other modules using this module, should be able to initiate queues, push and pop to a certain queue. When pushing data to a queue, the push function will parse the data into command ( id, data size, data ), allocate the needed memory dymanically and place it in the queue. The pop function will return a pointer to the oldest command in queue, and the free function is there to be called when the command handler is done with the command.
- command handler: this module owns both the serial and the command queue modules, the idea behind this is that the command handler should in theory be able to receive commands from different sources not only from uart ( in our case it is only uart though). Other modules should be able to register there so called module command handler ( module id and callback function ), for the command handler to be able to redirect commands for them.
- flash: some normal flash module, it should be able write read and erase the flash memory.
- eeprom: This is not a real eeprom, but a simulated one. One flash page was reserved to act as eeprom. The goal is to be able to save data over restart and power down. The eeprom module has a data struct to be saved the the flash, it contains data like the boot flag, crc and size of the application. The data will be rotating on the the whole page size. The page will be erased when it is full, and eeprom will start from the beginning.
- fwUpgrade: is the module responsible for updating the application, it will receive the size and crc of the application before the programming starts, and when it is done it will verify the crc of the program written to the flash. fwUpgrade will also save the application size and crc to the eeprom, to be used when verifing the application every time before jumping to it.
- systemRestart: this module is responsible for performing the jump to application when needed, the jump function updates the stack pointer and the reset handler to be able to jump to application. The system restart owns as well the boot flag that is saved into the eeprom when the used asks for application jump and perform a system restart. The first thing is done after restart is checking for that flag if set and jump to the boot before initializing the boot peripherals.
#### Application
This project is not supposed to do much but toggling the green led each 50 ms, just to demonstrate that interrupts still working after the jump to application.
### Python
The python script is used to send commands to the stm32 ( Boot ). A command class is defined to mirror the commands defined in stm32 code, the class also has a pack() method to convert a class instance into byte array to be sent via the uart. One python function is added for each command to load the command with id and data and lastly call the uart_send_cmd, where a check sum is calculated and appended to the data sent. When the stm32 receives the data, it will verify the crc and sent an ACK for the uart_send_cmd to receive before returning ture or false. The script includes also some functions to parse intel hex file and extract the data from it. there is other functions also for updating the program by erasing the memory and sending the new program to be written to flash be the fwUpgrade module on the stm32.
