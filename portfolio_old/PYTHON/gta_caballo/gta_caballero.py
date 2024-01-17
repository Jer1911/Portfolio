#Welcome to GTA Caballo Bot version 1.0
#This bot works using Python version 2.7.10
#and it is assuming you are using Windows 10 64 bit version
#Any other operating system or package versions, is not supported
#at this time.
#
#You will need the following installed (or current versions):
#python-2.7.10.amd64.msi
#numpy-1.9.2+mkl-cp27-none-win_amd64.whl
#Pillow-2.9.0-cp27-none-win_amd64.whl
#pywin32-219.win-amd64-py2.7.exe
#
#the libraries were downloaded from this site:
#http://www.lfd.uci.edu/~gohlke/pythonlibs/
#
#To get the libraries working:
#install the libraries using the 'pip' command from Windows admin cmd prompt.
#Then if error occurs, you may need to enter the following command in a admin cmd prompt:
#reg copy HKLM\SOFTWARE\Python HKLM\SOFTWARE\Wow6432Node\Python /s
#Finally, to make the bot work on your system, you will need to adjust the global variables
#to reflect your own screen and browser.

#imported libraries
from PIL import ImageGrab
import os
import time
import win32api, win32con
from PIL import ImageOps
from numpy import *
import win32com.client
import random
import pygame
import mail

#globals
x_pad = 558
y_pad = 250

# 559, 251
# 1360, 852

#-----------------------Music functions:----------------------------------------
# Play a 30 second alarm on the PC speakers:
def play_music():
    pygame.mixer.init()
    pygame.mixer.music.load('bwv1067_badineri_metal.mp3')
    pygame.mixer.music.play()
    time.sleep(30)
    pygame.mixer.music.stop()

#-------------------basic function definitions:---------------------------------
def screenGrab():
    box = (x_pad+1,y_pad+1,x_pad+800,y_pad+602)
    im = ImageGrab.grab(box)
    im.save(os.getcwd() + '\\full_snap__' + str(int(time.time())) + '.png', 'PNG')

def leftClick():
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0)
    time.sleep(.1)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0)
    
def leftDown():
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0)
    time.sleep(.1)
         
def leftUp():
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0)
    time.sleep(.1)

def rightClick():
    win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN,0,0)
    time.sleep(.1)
    win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP,0,0)

def mousePos(cord):
    win32api.SetCursorPos((x_pad + cord[0], y_pad + cord[1]))
     
def get_cords():
    x,y = win32api.GetCursorPos()
    x = x - x_pad
    y = y - y_pad

def click_gta():
    mousePos((394,270))
    leftClick()
    time.sleep(.5)

# Press ESC:
def press_esc():
    win32api.keybd_event(0x1B,0,0,0)
    time.sleep(0.1)
    win32api.keybd_event(0x1B,0,win32con.KEYEVENTF_KEYUP,0)

#------------------Fast-tracking Bunker Research:-------------------------------
def fast_track_click():
    print('fast track')
    mousePos((393,373)) # fast track
    leftClick()
    time.sleep(5)

def fast_track(): # bunker research
    fast_track_click()
    print('confirm')
    mousePos((453,339)) # confirm 1
    leftClick()
    time.sleep(10)
    print('confirm')
    mousePos((398,459)) # confirm 2
    leftClick()
    print('waiting 4 minutes')
    time.sleep(240) # wait 4 minutes

def fast_track_repeat():
    i = 0
    while(i < 12): # How many times you want to fast track
        print('iteration # i = ' + str(i))
        fast_track()
        i = i + 1

#--------------Horse Racing:----------------------------------------------------
# results page BET AGAIN button:
def bet_again():
    print('bet again')
    mousePos((325,550))
    leftClick()
    t=random.random()
    time.sleep(3+t)

# SINGLE EVENT PLACE BET button:
def place_bet():
    print('place bet')
    mousePos((550,480))
    leftClick()
    t=random.random()
    time.sleep(3+t)

# SINGLE EVENT HORSE #1 button:
def select_horse():
    print('select horse')
    mousePos((175,185))
    leftClick()
    t=random.random()
    time.sleep(3+t)

# SINGLE EVENT > (increase bet) button:
def adjust_bet():
    mousePos((618,288))
    leftClick()
    time.sleep(0.3)

# SINGLE EVENT drag from > button to PLACE BET button and hold:
def drag_bet_hold():
    print('do trick')
    mousePos((618,288))
    x=random.randint(385,600)
    y=random.randint(423,455)
    leftDown()
    mousePos((x,y))
    time.sleep(15)
    leftUp()

# Play horses, full sequence:
def play_horses():
    place_bet()
    mousePos((150,180))
    select_horse()
    print('adjust bet')
    i=0
    while(i<10):
        adjust_bet()
        i = i + 1
    drag_bet_hold()
    t = random.randint(20,30)
    time.sleep(t)
    mousePos((325,550))
    bet_again()

# Calculate how long we were betting:
def get_time_diff(start):
    end = time.time()
    elapsed = end - start
    if(elapsed > 60 and elapsed < 3600):
        return str(elapsed / 60) + ' minutes'
    elif(elapsed >= 3600):
        return str((elapsed / 60) / 60) + ' hours'
    else:
        return str(elapsed) + ' seconds'

# Repeat the horse playing k number of times:
def horse_repeat(k,start):
    i = 0
    while(i < k):
        print('ITERATION NUMBER: i = ' + str(i))
        local_start = time.time()        
        play_horses()
        print('ITERATION TIME = ' + get_time_diff(local_start))
        print('TOTAL TIME = ' + get_time_diff(start) + '\n')
        mousePos((575,485))
        time.sleep(4)
        i = i + 1

# Quit Betting:
def quit_betting():
    print('quit betting')
    press_esc()
    time.sleep(3)
    press_esc()
    time.sleep(5)
    mousePos((394,270))
    rightClick()
    time.sleep(1)
    rightClick()

#-----------------Database functions:-------------------------------------------

def write_data(start,time_difference,number_of_bets):
    filename = (os.getcwd() + '\\gta_record '
                + time.strftime("%Y-%m-%d %H_%M_%S", time.localtime()) + '.txt')
    outfile = open(filename,'w')
    gta_data = ('Time of sequence start: ' + str(start)
                  + '\nTime spent betting: ' + time_difference
                  + '\nNumber of bets: ' + str(number_of_bets))
    outfile.write(gta_data)
    outfile.close()
    msg = str('\nFile written to disk:\n' + str(filename) + '\nFile contents:\n'
                    + str(gta_data))
    mail.send_email(msg)

#---------------------MAIN:-----------------------------------------------------
def main():
    number_of_bets = 150 # 150 bets is approx 2.5 hours
    click_gta() # needs to click the gta window once initially
    start = time.time() # what time did we begin the sequence
    horse_repeat(number_of_bets,start) # play the horses number_of_bets times
    play_music() # sound the alarm when we are about to stop betting
    quit_betting() # cease betting and stand up
    time_difference = get_time_diff(start) # how long were we betting
    print('\n\nSequence complete.')
    print ('Total elapsed time for sequence is ' + time_difference)
    write_data(start,time_difference,number_of_bets) # save data & send email

if __name__ == '__main__':
    main()

