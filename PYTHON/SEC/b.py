#!/usr/bin/python3
# -*- coding: utf-8 -*-
import base64

answer = ''
count = 0
with open('catchthemall.txt', 'r') as f:
    for line in f:
        if (count+1) % 8 == 0:
            l = str(base64.b64decode(line))
            i = 4
            while(i < 8):
                answer = answer + l[i]
                i = i + 1
        count = count + 1
print(answer)

