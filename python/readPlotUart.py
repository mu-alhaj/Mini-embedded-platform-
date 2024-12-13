import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Set up the serial port (adjust 'COM3' and baudrate as needed)
ser = serial.Serial('COM4', 38400)

# Create a figure and axis for the plot
fig, ax = plt.subplots()
xdata, ydata = [], []
ln, = plt.plot([], [], 'b-')

# Initialize the plot
def init():
    ax.set_xlim( 0, 10 )
    ax.set_ylim( 0, 5000 )
    return ln,

# Update the plot with new data
def update(frame):
    data = None
    sbyte = ser.read( 1 )
    #print (sbyte)
    if sbyte == b's':
        bytes = ser.read( 4 )
        #print (bytes)
        ebyte = ser.read( 1 )
        #print (ebyte)
        if ebyte == b'e':
            data = int.from_bytes( bytes, byteorder='little' )
    
    if data != None:
        #print(data)
        try:
            ydata.append(int(data))
            xdata.append(len(ydata))
            ln.set_data(xdata, ydata)
            ax.set_xlim(0, len(ydata))
            #ax.set_ylim(min(ydata), max(ydata))
        except ValueError:
            print(f"Invalid data received: {data}")
    return ln,

# Set up the animation
ani = animation.FuncAnimation(fig, update, init_func=init, blit=False)

# Show the plot
plt.show()

# Close the serial port when done
ser.close()