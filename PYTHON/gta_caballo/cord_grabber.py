import win32api, win32con
import win32com.client

x_pad = 558
y_pad = 250

def get_cords():
    x,y = win32api.GetCursorPos()
    x = x - x_pad
    y = y - y_pad
    print x,y

def main():
    pass
 
if __name__ == '__main__':
    main()

