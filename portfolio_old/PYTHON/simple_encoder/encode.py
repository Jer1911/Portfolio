import sys

def to_bin(phrase):
    binary_phrase = [bin(ord(k))[2:].zfill(8) for k in phrase]
    return binary_phrase

def print_bin(binary_phrase):
    i = 0
    ret_str = ''
    while(i < len(binary_phrase)):
        ret_str = ret_str + binary_phrase[i]
        i += 1
    return ret_str

def to_hex(ret_str):
    ret_str = str(hex(int(ret_str,2))).lstrip('0x')
    return ret_str

def rot(phrase, rot_val):
    caesar_str = ''
    k = 0
    while(k < len(phrase)):
        if(phrase[k].isalpha()):
            num = ord(phrase[k])
            num += rot_val
            if(phrase[k].islower()):
                if(num > ord('z')):
                    num -= 26
                elif(num < ord('a')):
                    num += 26
            if(phrase[k].isupper()):
                if(num > ord('Z')):
                    num -= 26
                elif(num < ord('A')):
                    num += 26
            caesar_str += chr(num)
        else:
            caesar_str += phrase[k]
        k += 1
    return caesar_str

def vigenere(phrase, key):
    return 'placeholder'

def main():
    phrase = str(raw_input('\nEnter a phrase: '))
    print('\nChoose Operation:\n1 - bin\n2 - hex\n3 - rot\n4 - vigenere')
    choice = str(raw_input('choice: '))

    if(choice == '1'):
        binary_phrase = to_bin(phrase)
        bin_str = print_bin(binary_phrase)
        print('binary of phrase:\n' + bin_str)
    elif(choice == '2'):
        hex_str = to_hex(print_bin(to_bin(phrase)))
        print('hex of phrase:\n' + hex_str)
    elif(choice == '3'):
        rot_val = int(raw_input('Enter ROT value (1-26): '))
        rot_str = rot(phrase, rot_val)
        print('rot ' + str(rot_val) + ' of phrase:\n' + rot_str)
    elif(choice == '4'):
        key = str(raw_input('Enter a key: '))
        vig_str = vigenere(phrase, key)
        print('vigenere of phrase:\n' + vig_str)
    else:
        print('invalid choice.\n')

main()

