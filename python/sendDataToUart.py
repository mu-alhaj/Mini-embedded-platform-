import serial

# Set up the serial port
ser = serial.Serial( port='COM4', baudrate=112500, timeout=1 )

msg = "Hello"
msg_hex= 0xabababab

print("Start\n")

def uart_send_data( data ) :
    print("Send data\n")
    if ser.is_open:
        print("port is open\n")
        data_bytes = bytes( data, 'utf-8' )
        print("write\n")
        ser.write(data_bytes)
        print(f"data sent : {data} \n")
        ser.close()
    else:
        print("serial port is not open\n")

def uart_send_hex( data_hex ):
    print("Send data\n")
    if ser.is_open:
        print("port is open\n")
        data_bytes = data_hex.to_bytes( 4, byteorder = 'big')
        print("write\n")
        ser.write(data_bytes)
        print(f"data sent : {data_bytes} \n")
        ser.close()
    else:
        print("serial port is not open\n")

#uart_send_data(msg)
uart_send_hex( msg_hex)

exit(0)