#!/usr/bin/python3

import numpy as np

def calc(x):
	y = np.uint32(x * 7 + 4)
	return y

def main():
	start = np.uint32(1)
	end = np.uint32(0xFFFFFFFF)
	while(start <= end):
		x = calc(start)
		if(x == 1337 and start > 1337):
			print("The answer is: " + str(start))
			break
		start += 1

if __name__ == '__main__':
	main()

