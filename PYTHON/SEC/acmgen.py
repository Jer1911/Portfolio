#!/usr/bin/python3

'''
acmgen.py
Author: Jeremy Ecker

Purpose: Print a grid for easy construction of visual access control matrix,
		or any other blank matrix you might need.

Example Use:

	python3 amcgen.py 3 4 5 > grid.txt

	Executing the above command will print a 3 x 4 matrix with width 5 cells,
	and store it in the file grid.txt. It can then be edited using vim with
	shift+R (replace mode) to preserve grid and insert data.
'''

import sys

def acmgen(rows,cols,width):
	row = 0
	print('\n' * 2)
	while(row < rows):
		print(' ' * width + ('+' + ('-' * width)) * cols + '+')
		print(' ' * width + ('|' + (" " * width)) * cols + '|')
		row += 1
	print(' ' * width + ('+' + ('-' * width)) * cols + '+\n')

def main():
	rows = int(sys.argv[1])
	cols = int(sys.argv[2])
	width = int(sys.argv[3])
	acmgen(rows,cols,width)

if __name__ == '__main__':
	main()

