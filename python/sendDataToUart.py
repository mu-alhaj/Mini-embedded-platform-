import serial

# Set up the serial port
ser = serial.Serial( port='COM4', baudrate=112500, timeout=1 )

msg = '1234'

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


uart_send_data(msg)

exit(0)