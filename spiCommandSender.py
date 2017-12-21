import sys
from Adafruit_BBIO.SPI import SPI

command = sys.argv[1]

WALK = 1
WALK_BACK = 31
STOP = 15
TURNL = 3
TURNR = 7

spi = SPI(0,0) 
spi.msh = 57600
spi.bpw = 8
#for debugging with keyboard input
#command = raw_input();
spi.xfer2([getCommandCode(command)])
spi.close() 

def getCommandCode(command):
      if command == 'walk':
    print("Walk!")
    return WALK
  elif command == 'back':
    print('Reverse')
    return WALK_BACK
  elif command == 'stop':
    print('Stop!')
    return STOP
  elif command == 'left': 
    print('Turn Left')
    return TURNL
  elif command == 'right':
    print('Turn Right')
    return TURNR
  return 0