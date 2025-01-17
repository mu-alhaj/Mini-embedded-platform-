import serial
import struct
import time
import random
import os

# commands list
new_cmd     = 0xab

# Led commands
id_led_set     = 0x0101
id_led_toggle  = 0x0102

#flash commnds
id_flash_write      = 0x0201
id_flash_erase_page = 0x0202

#fwUpgrade commands
id_fwUpgrade_erase_app = 0x0301
id_fwUpgrade_program_app = 0x0302

# new command ( 1 byte ) / command id ( 2 byte ) / data size ( 2 bytes ) / data up to 252
class Command:
    def __init__(self, id, size, data=bytearray([0])):
        self.newCmd = 0xab
        self.id     = id
        self.size   = size
        self.data   = data

    def print_self(self):
        # Print class members in hex
        print(f"newCmd: {self.newCmd:#04x}")
        print(f"id: {self.id:#06x}")
        print(f"size: {self.size:#06x}")
        print(f"data: {' '.join(f'{byte:#04x}' for byte in self.data)}")

    def pack(self):
        # Pack the data into bytes
        self.print_self()
        return struct.pack( f'< B H H {self.size}s', self.newCmd, self.id, self.size, self.data)



##################################
#       send command
##################################

def uart_send_cmd( ser, cmd ):
    #print("Send data\n")
    if ser.is_open:
        #print("port is open\n")
        #print("write\n")
        ser.write(cmd)
        print(f"data sent : {cmd} \n")
    else:
        print("serial port is not open\n")

##################################
#       led commands
##################################

def led_set( set ):
    if( set ):
        data = bytearray([1])
        cmd_led_set = Command( id_led_set,1, data )
        uart_send_cmd( ser, cmd_led_set.pack() )
    else:
        data = bytearray([0])
        cmd_led_set = Command( id_led_set,1, data )
        uart_send_cmd( ser, cmd_led_set.pack() )

def led_toggle():
    cmd_led_toggle = Command( id_led_toggle, 0 )
    uart_send_cmd( ser, cmd_led_toggle.pack() )


##################################
#       flash commands
##################################

def flash_write( add, data ):
    print ("flash write")
    data_bytes = add.to_bytes(4, byteorder='little')
    data_bytes += data.encode('utf-8')
    cmd_flash_write = Command( id_flash_write, len( data_bytes ), data_bytes )
    uart_send_cmd( ser, cmd_flash_write.pack() )

def flash_erase_page( add ):
    print("flash erase page")
    data_bytes = add.to_bytes(4, byteorder='little')
    cmd_flash_erase_page = Command( id_flash_erase_page, len( data_bytes ), data_bytes )
    uart_send_cmd( ser, cmd_flash_erase_page.pack() )

##################################
#       fwUpgrade commands
##################################

def fwUpgrade_erase_app():
    print("fwUpgrade erase app")
    cmd_fwUpgrade_erase_app = Command( id_fwUpgrade_erase_app, 0 )
    uart_send_cmd( ser, cmd_fwUpgrade_erase_app.pack() )

def fwUpgrade_program_app(add, data):
    print ("fwUpgrade program")
    data_bytes = add.to_bytes(4, byteorder='little')
    data_bytes += data
    cmd_fwUpgrade_program = Command( id_fwUpgrade_program_app, len( data_bytes ), data_bytes )
    uart_send_cmd( ser, cmd_fwUpgrade_program.pack() )

def read_hex_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    return lines

def main ():


    hex_file_path = 'c:/Users/wxj509/Data/MicroRepo/python/App.hex'
    application_start_address = 0x8040000
    add = application_start_address
    chunk_size = 64

    print("Start\n")

    # Set up the serial port
    global ser
    ser = serial.Serial( port='COM4', baudrate=112500, timeout=1 )

    # read hex file into byte array
    hex_lines = read_hex_file(hex_file_path)
    binary_data = bytearray()
    for line in hex_lines:
        if line.startswith(':'):
            # Convert hex line to binary data
            data = bytes.fromhex( line[1:].strip() )
            binary_data.extend( data )

    # erase application flash area
    fwUpgrade_erase_app()
    time.sleep(3)

    wait_for_input = True
    # start writing application
    index = 1
    for i in range ( 0, len( binary_data), chunk_size ):
        # wait for me before sending new chunk
        if wait_for_input:
            user_input = input("Press Enter to print the next chunk or enter '1' to print all remaining chunks: ")
            if user_input == '1':
                wait_for_input = False    

        chunk = binary_data[i:i+chunk_size]
        print( index )
        index += 1
        fwUpgrade_program_app( add, chunk )
        time.sleep(0.3)  # Small delay to avoid overwhelming the STM32
        add += chunk_size
    
    
    ser.close()

    exit(0)

main()

