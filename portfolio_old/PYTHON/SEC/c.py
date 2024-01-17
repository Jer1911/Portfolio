#!/usr/bin/python3
# -*- coding: utf-8 -*-
import base64, socket

def get_data(r):
    d = r.recv(2048).decode()
    return d

def decode_data(d):
    s = base64.b64decode(d).decode()
    return s

def send_data(r,s):
    r.send((s+'\n').encode())

def main():
    host = '127.0.0.1'
    port = 11111

    r = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    r.connect((host,port))

    flag = ''
    finished = 0
    while(finished == 0):
        d = get_data(r)
        print(d)

        if('==' in d):
            s = decode_data(d)
            print(s)
            send_data(r,s)
        else:
            flag = get_data(r)
            print('The flag is: ' + flag)
            finished = 1

main()
