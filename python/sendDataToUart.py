import serial
import struct
import time
import random

new_cmd     = 0xab
# commands list
id_led_set     = 0x0101
id_led_toggle  = 0x0102

id_flash_write      = 0x0201
id_flash_erase_page = 0x0202

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
        #self.print_self()
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

def main ():

    
    print("Start\n")
    # Set up the serial port
    global ser
    ser = serial.Serial( port='COM4', baudrate=112500, timeout=1 )

    index = random.randint(0, 9)
    counter = 0
    address = 0x08040000

    print (f"index : {index}")

    flash_erase_page( address )

    while( counter < 5 ):

        led_toggle()
        time.sleep(2)
        flash_write( address,f"Hello{index}" )
        time.sleep(1)
        address += 6

        index = (index + 1 ) % 10
        counter += 1
    
    ser.close()

    exit(0)

main()

