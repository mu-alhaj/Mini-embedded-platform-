import serial

# Set up the serial port (adjust 'COM3' and baudrate as needed)
ser = serial.Serial('COM4', 38400)

def update():
    line = ser.readline().decode('utf-8').strip()
    # Remove any null bytes and filter out non-numeric characters
    line = ''.join(filter(str.isdigit, line))
    if line:
        print(line)


while( True ):
    update()

# Close the serial port when done
ser.close()