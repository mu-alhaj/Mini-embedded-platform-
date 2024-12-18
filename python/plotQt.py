import serial
import pyqtgraph as pg
from PyQt5 import QtWidgets, QtCore

# Set up the serial port (adjust 'COM4' and baudrate as needed)
ser = serial.Serial('COM4', 38400)

# Create a PyQt application
app = QtWidgets.QApplication([])

# Create a window with a plot
win = pg.GraphicsLayoutWidget(show=True)
win.setWindowTitle('Real-time Data Plot')
plot = win.addPlot()
curve = plot.plot(pen='b')

# Initialize data lists
xdata, ydata = [], []

# Update function to read data and update the plot
def update():
    global xdata, ydata
    data = None
    sbyte = ser.read(1)
    if sbyte == b's':
        bytes = ser.read(4)
        ebyte = ser.read(1)
        if ebyte == b'e':
            data = int.from_bytes(bytes, byteorder='little')
    
    if data is not None:
        try:
            ydata.append(int(data))
            xdata.append(len(ydata))
            curve.setData(xdata, ydata)
            plot.setXRange(0, len(ydata))
            plot.setYRange(0, max(ydata) if ydata else 5000)
        except ValueError:
            print(f"Invalid data received: {data}")

# Set up a timer to call the update function periodically
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(50)  # Update every 50 ms

# Start the PyQt event loop
QtWidgets.QApplication.instance().exec_()

# Close the serial port when done
ser.close()