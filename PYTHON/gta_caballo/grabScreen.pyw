from PIL import ImageGrab
import os
import time
import win32api, win32con
from PIL import ImageOps
from numpy import *
import win32com.client
import random

def screenGrab():
    box = ()
    im = ImageGrab.grab()
    im.save(os.getcwd() + '\\full_snap__' + str(int(time.time())) +
'.png', 'PNG')

def main ():
    screenGrab()

if __name__ == '__main__':
    main()
