import serial
import struct

new_cmd     = 0xab
# commands list
id_led_set     = 0x0101
id_led_toggle  = 0x0102

# new command ( 1 byte ) / command id ( 2 byte ) / data size ( 2 bytes ) / data up to 252
class Command:
    def __init__(self, id, size, data):
        self.newCmd = 0xab
        self.id     = id
        self.size   = size
        self.data   = data

    def pack(self):
        # Pack the data into bytes
        return struct.pack( f'< B H H {self.size}s', self.newCmd, self.id, self.size, self.data)





def uart_send_cmd( ser, cmd ):
    print("Send data\n")
    if ser.is_open:
        print("port is open\n")
        print("write\n")
        ser.write(cmd)
        print(f"data sent : {cmd} \n")
    else:
        print("serial port is not open\n")


def set_led( set ):
    if( set ):
        data = bytearray([1])
        cmd_set_led = Command( id_led_set,1, data )
        uart_send_cmd( ser, cmd_set_led.pack() )
    else:
        data = bytearray([0])
        cmd_set_led = Command( id_led_set,1, data )
        uart_send_cmd( ser, cmd_set_led.pack() )
#uart_send_data(msg)







def main ():

    
    print("Start\n")
    # Set up the serial port
    global ser
    ser = serial.Serial( port='COM4', baudrate=112500, timeout=1 )

    set_led(False)
    
    ser.close()

    exit(0)

main()

