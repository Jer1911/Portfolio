import pygame
import time
import os
import math

def play_music():
    pygame.mixer.init()
    pygame.mixer.music.load('bwv1067_badineri_metal.mp3')
    pygame.mixer.music.play()
    time.sleep(10)
    pygame.mixer.music.stop()

def get_timer_time():
    h = int(raw_input('Hours: '))
    m = int(raw_input('Minutes: '))
    s = int(raw_input('Seconds: '))
    t_array = [h,m,s]
    return t_array

def get_total_seconds(t_array):
    s = t_array[0] * 3600 + t_array[1] * 60 + t_array[2]
    return s

def show_time(t_array):
    print(str(t_array[0]) + ':' + str(t_array[1]) + ':' + str(t_array[2]))

def execute_timer(s):
    i = 0
    while(i < s):
        time.sleep(1)
        i = i + 1

def main():
    t_array = get_timer_time()
    s = get_total_seconds(t_array)
    execute_timer(s)
    play_music()

if(__name__ == '__main__'):
    main()
    
