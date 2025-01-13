import serial
import struct
# Set up the serial port
ser = serial.Serial( port='COM4', baudrate=112500, timeout=1 )

msg = "Hello flash\r\n"

# new command ( 1 byte ) / command ( 1 byte ) / data size ( 2 bytes ) / data up to 252

new_cmd     = 0xab
led_set     = 0x01
led_toggle  = 0x02

struct_format = 'BBHB'
                                        
cmd_led_set     = ( new_cmd, led_set, 0x0001, 0x00 )
cmd_led_toggle  = ( new_cmd, led_toggle, 0x0000, 0x00 )

print("Start\n")

def uart_send_data( data ) :
    print("Send data\n")
    if ser.is_open:
        print("port is open\n")
        data_bytes = bytes( data, 'utf-8' )
        print("write\n")
        ser.write(data_bytes)
        print(f"data sent : {data} \n")
    else:
        print("serial port is not open\n")

def uart_send_hex( data_hex ):
    print("Send data\n")
    if ser.is_open:
        print("port is open\n")
        data_bytes = data_hex.to_bytes( 5, byteorder = 'big')
        print("write\n")
        ser.write(data_bytes)
        print(f"data sent : {data_bytes} \n")
    else:
        print("serial port is not open\n")

def uart_send_cmd( cmd ):
    print("Send data\n")
    if ser.is_open:
        print("port is open\n")
        data_bytes = struct.pack(struct_format, *cmd)
        print("write\n")
        ser.write(data_bytes)
        print(f"data sent : {data_bytes} \n")
    else:
        print("serial port is not open\n")

#uart_send_data(msg)
uart_send_cmd( cmd_led_toggle )

ser.close()
exit(0)

done = False
while True:
        if ser.in_waiting > 0:
            data = ser.read(ser.in_waiting)
            print(f"Received: {data.decode('utf-8')}")
            done = True
        if done :
            break


