import serial
import struct
import time

hex_file_path = 'C:/Users/wxj509/Data/MicroRepo/CubeMX/App/Debug/App.hex'
application_start_address = 0x8040000

# commands list
new_cmd     = 0xab
ACK         = b'\x06'
NAK         = b'\x15'

# Led commands
id_led_set     = 0x0101
id_led_toggle  = 0x0102

#flash commnds
id_flash_write      = 0x0201
id_flash_erase_page = 0x0202

#fwUpgrade commands
id_fwUpgrade_erase_app = 0x0301
id_fwUpgrade_program_app = 0x0302
id_fwUpgrade_send_app_crc = 0x0303

# new command ( 1 byte ) / command id ( 2 byte ) / data size ( 2 bytes ) / data bytes / crc (4 bytes)
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
    crc = calculate_crc( cmd )
    cmd = cmd + struct.pack( '<I', crc )
    if ser.is_open:
        ser.write(cmd)
        hex_cmd = ' '.join( f'{byte:02x}' for byte in cmd )
        print(f"uart_send_cmd ,total size: {len(cmd)} , data sent :\n {hex_cmd}")
        
        # read stm response. 
        time.sleep(0.1)
        response = ser.read(1) 
        if response == ACK:
            print(f"Received ACK {response}\n")
            return True
        elif response == NAK:
            print(f"Received NAK {response}\n")
            return False
        else:
            print(f"No valid response received {response}\n")
            return False

    else:
        print("serial port is not open\n")
        return False

##################################
#       send command
##################################

def calculate_crc( data ):
    crc = 0xFFFFFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 1:
                crc = (crc >> 1) ^ 0x04C11DB7 
            else:
                crc >>= 1
    return crc ^ 0xFFFFFFFF

##################################
#       led commands
##################################

def led_set( set ):
    if( set ):
        data = bytearray([1])
        cmd_led_set = Command( id_led_set,1, data )
        return uart_send_cmd( ser, cmd_led_set.pack() )
    else:
        data = bytearray([0])
        cmd_led_set = Command( id_led_set,1, data )
        return uart_send_cmd( ser, cmd_led_set.pack() )

def led_toggle():
    cmd_led_toggle = Command( id_led_toggle, 0 )
    return uart_send_cmd( ser, cmd_led_toggle.pack() )


##################################
#       flash commands
##################################

def flash_write( add, data ):
    print ("flash write")
    data_bytes = add.to_bytes(4, byteorder='little')
    data_bytes += data.encode('utf-8')
    cmd_flash_write = Command( id_flash_write, len( data_bytes ), data_bytes )
    return uart_send_cmd( ser, cmd_flash_write.pack() )

def flash_erase_page( add ):
    print("flash erase page")
    data_bytes = add.to_bytes(4, byteorder='little')
    cmd_flash_erase_page = Command( id_flash_erase_page, len( data_bytes ), data_bytes )
    return uart_send_cmd( ser, cmd_flash_erase_page.pack() )

##################################
#       fwUpgrade commands
##################################

def fwUpgrade_erase_app():
    print("fwUpgrade erase app")
    cmd_fwUpgrade_erase_app = Command( id_fwUpgrade_erase_app, 0 )
    return uart_send_cmd( ser, cmd_fwUpgrade_erase_app.pack() )

def fwUpgrade_program_app(add, data):
    print ("fwUpgrade program")
    data_bytes = add.to_bytes(4, byteorder='little')
    data_bytes += data
    cmd_fwUpgrade_program = Command( id_fwUpgrade_program_app, len( data_bytes ), data_bytes )
    return uart_send_cmd( ser, cmd_fwUpgrade_program.pack() )

##################################
#       utilities
##################################

def read_hex_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    return lines

def binary_from_hexFile(file_path):
    # read hex file into byte array
    hex_lines = read_hex_file(file_path)
    binary_data = bytearray()
    for line in hex_lines:
        if line.startswith(':'):
            # Convert hex line to binary data

            # The Intel HEX file format consists of ASCII text lines, each representing a record. Each record contains the following fields:
            #:      : Start code
            #LL     : Byte count (number of data bytes in the record)
            #AAAA   : Address (16-bit address offset)
            #TT     : Record type (00 for data, 01 for end of file, 04 for extended linear address, etc.)
            #DD...DD: Data bytes
            #CC     : Checksum

            # Therefore we are interested of the data type (00) of records/lines.
            # exemple :020000040804EE       : index 7 and 8 in this string are the record type.

            if line[7] == '0' and line[8] == '0' : 
                data = bytes.fromhex( line[9:-3].strip() )
                binary_data.extend( data )
    return binary_data

def update_app():

    add         = application_start_address
    chunk_size  = 64

    # Set up the serial port
    global ser
    ser = serial.Serial( port='COM4', baudrate=115200, timeout=1 )

    #get binary array from intel hex.
    binary_data = binary_from_hexFile( hex_file_path )

    # Calculate CRC checksum for the whole application
    #TODO : try to send the checksum before programming the application and verifiy it afterwards and before jumping to app.
    crc_checksum = calculate_crc(binary_data)
    print(f"CRC Checksum: {crc_checksum:#010x}")
    size = len( binary_data )
    print( size  )

    # erase application flash area
    if ( not fwUpgrade_erase_app() ) : 
        return False
    time.sleep(3)

    wait_for_input  = True
    keep_going      = True
    i               = 0
    index           = 1
    
    # start writing application
    while keep_going :
        # if whole data was send, break
        if ( len( binary_data ) - i == 0 ):
            break
        # wait for me before sending new chunk
        if wait_for_input:
            user_input = input("Press Enter to send the next chunk or enter '1' to send all remaining chunks: ")
            if user_input == '1':
                wait_for_input = False    

        # determine if there is a whole cunck to be send, ohterwise, send what ever left
        if ( len( binary_data ) - i > chunk_size ):
            chunk = binary_data[i:i+chunk_size]
        else:
            chunk = binary_data[i:]

        # what we are trying to send:
        print( f"chunk index: {index}" )
        hex_chunck = ' '.join( f'{byte:02x}' for byte in chunk )
        print(f"hex_chunck of size {len(chunk)}: \n {hex_chunck}")

        if fwUpgrade_program_app( add, chunk ) : 
            # Chunck was sent successfully and stm acked.
            index   += 1
            add     += len(chunk)
            i       += len(chunk)
        
        else:
            # do not update address or index.
            #wait here
            finish = input("Press Enter to rety or enter '1' terminate. ")
            if( finish == '1' ):
                keep_going = False
    
    print("\n\n hex transferred successfully !!")
    ser.close()

def test():
    # Set up the serial port
    global ser
    ser = serial.Serial( port='COM4', baudrate=115200, timeout=1 )
    wait_for_input = True
    while wait_for_input :
        # wait for me before sending new chunk
        if wait_for_input:
            user_input = input("Press Enter to print the next chunk or enter '1' to print all remaining chunks: ")
            if user_input == '1':
                wait_for_input = False    

        led_toggle() 

    ser.close()

    exit(0)


##################################
#       Main function.
##################################
def main ():

    print("Start\n")
    update_app()

    exit(0)

main()

#test()

