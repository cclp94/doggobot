from Adafruit_BBIO.SPI import SPI

WALK = 1
WALK_BACK = 31
STOP = 15
TURNL = 3
TURNR = 7

def getCommandCode(command):
  if command == 'w':
    print("Walk!")
    return WALK
  elif command == 'b':
    print('Reverse')
    return WALK_BACK
  elif command == 's':
    print('Stop!')
    return STOP
  elif command == 'l': 
    print('Turn Left')
    return TURNL
  elif command == 'r':
    print('Turn Right')
    return TURNR
  return 0

spi = SPI(0,0) 
spi.msh = 57600
spi.bpw = 8
while True:
  command = raw_input();
  spi.xfer2([getCommandCode(command)])
spi.close() 
