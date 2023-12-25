def Serial_Port_Configuration(port):
    global ser
    try:
        ser = serial.Serial(port,115200,timeout=2)
    except:
        print("\n   Oops! That was not a valid port")
        
        port = serial_ports()
        if(not port):
            print("\n   No ports Detected")
        else:
            print("\n   Here are some available ports on your PC. Try Again!")
            print("\n   ",port)
        return -1
    if ser.is_open:
        print("\n   Port Open Success")
    else:
        print("\n   Port Open Failed")
    return 0

def CAN_Configuration(channel, baurate):
    return 0

