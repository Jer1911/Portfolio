#!/usr/bin/python3
# -*- coding: utf-8 -*-
import socket

def send_reply(d,r):
    s = d.split("'")[-2]
    print(s)
    c = chr(int(s,2))
    print(c)
    r.send((c+'\n').encode())

def get_info(r):
    d = r.recv(2048).decode()
    print(d)
    return d

def main():
    host = '127.0.0.1'
    port = 19999

    r = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    r.connect((host,port))

    i = 0
    while(i == 0):
        d = get_info(r)
        if('FLAG' in d):
            print(d)
            i = 1
            pass
        else:
            send_reply(d,r)

main()

