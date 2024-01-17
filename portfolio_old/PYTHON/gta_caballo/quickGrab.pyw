#imported libraries
from PIL import ImageGrab
import os
import time
import win32api, win32con
from PIL import ImageOps
from numpy import *
import win32com.client
import random
 
#globals
x_pad = 558
y_pad = 250

#basic function definitions
def screenGrab():
    box = (x_pad+1,y_pad+1,x_pad+800,y_pad+602)
    im = ImageGrab.grab(box)
    im.save(os.getcwd() + '\\full_snap__' + str(int(time.time())) +
'.png', 'PNG')

def main():
	screenGrab()

if __name__ == '__main__':
    main()
