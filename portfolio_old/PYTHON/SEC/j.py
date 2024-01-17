#!/usr/bin/python3
# -*- coding: utf-8 -*-
import base64

def encrypt(text,shift):
    flag = ''
    for i in range(len(text)):
        letter = text[i]
        if(letter != '{' and letter !='}' and letter != '_'):
            if(letter.isupper()):
                flag += chr((ord(letter) + shift - 65) % 26 + 65)
            elif(letter.islower()):
                flag += chr((ord(letter) + shift - 97) % 26 + 97)
        else:
            flag += letter
    return flag

with open('file.enc', 'r') as f:
    for line in f:
        answer = str(base64.b64decode(line)).lstrip("b'").rstrip("\\n'")
        flag = encrypt(answer,2)
        print('Original: ' + str(line) + 'Decoded b64: ' + answer
                + '\nDecoded flag: ' + flag + '\n')

