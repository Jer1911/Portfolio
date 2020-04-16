# team5_project1.py
# Authors: Jeremy Ecker, Kameron Bush

import sys

class Disassembler:

    def __init__(self):
        pass

    # Converts unsigned string of binary to signed integer:
    def twos_comp(self, binary_string):
        if (int(binary_string, 2) > 2 ** (len(binary_string) - 1) - 1):
            return int(binary_string, 2) - (1 << len(binary_string))
        else:
            return int(binary_string, 2)

    # Writes the file:
    def print_lines(self, instruction_index, outputFileName):
        f = open(outputFileName, 'w')
        i = 0
        while (i < instruction_index):
            if (d.opcode_string[i] == 'memory_data'):
                f.write(d.instruction[i] + '\t' + str(96 + i * 4) + '\t' + str(d.data[i]) + '\n')
            else:
                f.write(d.instruction_spaced[i] + str(96 + i * 4) + '\t' +
                        d.opcode_string[i] + d.arg1_string[i] + d.arg2_string[i] +
                        d.arg3_string[i] + '\n')#+ d.arg4_string[i] + '\n') 
            i += 1
        f.close()

    # Parses a line of the input file:
    def parse_line(self, current_line, instruction_index):
        # Add instruction to instruction list and instruction_spaced list:
        current_line = current_line.rstrip('\t\n')
        d.instruction.append(current_line)
        printable_instruction = str(current_line[0:8] + ' ' + current_line[8:11] +
            ' ' + current_line[11:16] + ' ' + current_line[16:21] + ' ' +
            current_line[21:26] + ' ' + current_line[26:32] + '\t')
        d.instruction_spaced.append(printable_instruction)

        # Local variable declarations:
        instruction_type = ''
        instruction_format = ''
        rm = int(current_line[11:16], 2)  # Source 2 (arg2) (5 bits)
        shamt = int(current_line[16:22], 2)  # Shift amount (6 bits)
        rn = int(current_line[22:27], 2)  # Source 1 (arg1) (5 bits)
        rd = int(current_line[27:32], 2)  # Destination (arg3) (5 bits)
        immediateI = d.twos_comp(current_line[10:22])  # (12 bits)
        immediateIM = int(current_line[11:27], 2)
        hw = int(current_line[9:11], 2)
        address = int(current_line[11:20], 2)  # (9 bits)
        #addressCB = int(current_line[8:27], 2)
        #addressB = int(current_line[6:32], 2)
	addressCB = d.twos_comp(current_line[8:27])
        addressB = d.twos_comp(current_line[6:32])
        op2 = int(current_line[21:23], 2)  # (2 bits)
        rt = int(current_line[27:32], 2)  # (5 bits)
        shift_eor = int(current_line[8:10], 2) # (2 bits)
        shift_eor_string = '' # needed for alternate EOR...

        # Detect type of instruction:
        if (int(current_line[0:11], 2) == 1112):  # ADD: rd = rn + rm
            instruction_type = 'ADD'
            instruction_format = 'R'
            d.opcode.append(1112)
        elif (int(current_line[0:11], 2) == 1624):  # SUB: rd = rn - rm
            instruction_type = 'SUB'
            instruction_format = 'R'
            d.opcode.append(1624)
        elif (int(current_line[0:11], 2) == 1104):  # AND: rd = rn & rm
            instruction_type = 'AND'
            instruction_format = 'R'
            d.opcode.append(1104)
        elif (int(current_line[0:11], 2) == 1360):  # ORR: rd = rn || rm
            instruction_type = 'ORR'
            instruction_format = 'R'
            d.opcode.append(1360)
        elif (int(current_line[0:11], 2) == 1690):  # LSR: rd = rn >> shamt
            instruction_type = 'LSR'
            instruction_format = 'R'
            d.opcode.append(1690)
        elif (int(current_line[0:11], 2) == 1691):  # LSL: rd = rn << shamt
            instruction_type = 'LSL'
            instruction_format = 'R'
            d.opcode.append(1691)
        elif (int(current_line[0:11], 2) == 1872): # EOR: simple format
            instruction_type = 'EOR'
            instruction_format = 'R'
            d.opcode.append(int(current_line[0:11], 2))
        elif (int(current_line[0:11], 2) == 1984):  # STUR: rn + address = rt
            instruction_type = 'STUR'
            instruction_format = 'D'
            d.opcode.append(1984)
        elif (int(current_line[0:11], 2) == 1986):  # LDUR: rt = rn + address
            instruction_type = 'LDUR'
            instruction_format = 'D'
            d.opcode.append(1986)
        elif (int(current_line[0:11], 2) >= 1160 and  # ADDI: ....
              int(current_line[0:11], 2) <= 1161):
            instruction_type = 'ADDI'
            instruction_format = 'I'
            d.opcode.append(int(current_line[0:11], 2))
        elif (int(current_line[0:11], 2) >= 1672 and  # SUBI: ....
              int(current_line[0:11], 2) <= 1673):
            instruction_type = 'SUBI'
            instruction_format = 'I'
            d.opcode.append(int(current_line[0:11], 2))
        elif (int(current_line[0:11], 2) >= 1684 and  # MOVZ: rd = LSL(imm) * hw * 16
              int(current_line[0:11], 2) <= 1687):
            instruction_type = 'MOVZ'
            instruction_format = 'IM'
            d.opcode.append(int(current_line[0:11], 2))
        elif (int(current_line[0:11], 2) >= 1940 and
              int(current_line[0:11], 2) <= 1943):
            instruction_type = 'MOVK'
            instruction_format = 'IM'
            d.opcode.append(int(current_line[0:11], 2))
        elif (int(current_line[0:11], 2) >= 1440 and
              int(current_line[0:11], 2) <= 1447):
            instruction_type = 'CBZ'
            instruction_format = 'CB'
            d.opcode.append(int(current_line[0:11], 2))
        elif (int(current_line[0:11], 2) >= 1448 and
              int(current_line[0:11], 2) <= 1455):
            instruction_type = 'CBNZ'
            instruction_format = 'CB'
            d.opcode.append(int(current_line[0:11], 2))
        elif (int(current_line[0:11], 2) >= 160 and
              int(current_line[0:11], 2) <= 191):
            instruction_type = 'B'
            instruction_format = 'B'
            d.opcode.append(int(current_line[0:11], 2))
        elif (int(current_line[0:11], 2) == 2038): # BREAK
            instruction_type = 'BREAK'
            instruction_format = 'BREAK'
            d.opcode.append(int(current_line[0:11], 2))
            d.break_flag = True
        elif (d.break_flag == False and int(current_line, 2) == 0): # NOP
            instruction_type = 'NOP'
            instruction_format = 'R'
            d.opcode.append(0)
        elif (d.break_flag):
            instruction_type = 'memory_data'  # memory data
            instruction_format = 'mem'
            d.opcode.append(int(current_line[0:11], 2))

        # Write the instruction type string to list:
        d.opcode_string.append(instruction_type)

        # Put args into respective lists:
        if (instruction_format == 'R'):  # R-Type
            d.data.append(0)
            if (instruction_type == 'ADD' or instruction_type == 'SUB' or
                    instruction_type == 'AND' or instruction_type == 'ORR'):
                d.arg1.append(rm)
                d.arg2.append(rn)
                d.arg3.append(rd)
                d.arg1_string.append('\tR' + str(rd))
                d.arg2_string.append(', R' + str(rn))
                d.arg3_string.append(', R' + str(rm))
                d.arg4.append(shift_eor)
                d.arg4_string.append(shift_eor_string)
            elif (instruction_type == 'LSL' or instruction_type == 'LSR'):
                d.arg1.append(shamt)
                d.arg2.append(rn)
                d.arg3.append(rd)
                d.arg1_string.append('\tR' + str(rd))
                d.arg2_string.append(', R' + str(rn))
                d.arg3_string.append(', #' + str(shamt))
                d.arg4.append(shift_eor)
                d.arg4_string.append(shift_eor_string)
            elif (instruction_type == 'NOP'):
                d.arg1.append(0)
                d.arg2.append(0)
                d.arg3.append(0)
                d.arg1_string.append('')
                d.arg2_string.append('')
                d.arg3_string.append('')
                d.arg4.append(shift_eor)
                d.arg4_string.append(shift_eor_string)

            elif (instruction_type == 'EOR'):
                d.arg1.append(rm)
                d.arg2.append(rn)
                d.arg3.append(rd)
                d.arg1_string.append('\tR' + str(rd))
                d.arg2_string.append(', R' + str(rn))
                d.arg3_string.append(', R' + str(rm))
                d.arg4.append(shift_eor)
                d.arg4_string.append(shift_eor_string)
                    
            ''' # ALTERNATE FOR EOR uses original opcode:
            elif (instruction_type == 'EOR'): # EOR <Xd>, <Xn>, <Xm>{, <shift> #<amount>}
                if(shamt == 0): # If there is zero shift, then we don't need to print the shift type.
                    d.arg1.append(rm)
                    d.arg2.append(rn)
                    d.arg3.append(rd)
                    d.arg1_string.append('\tR' + str(rd))
                    d.arg2_string.append(', R' + str(rn))
                    d.arg3_string.append(', R' + str(rm))
                    d.arg4.append(shift_eor)
                    d.arg4_string.append(shift_eor_string)
                else: # If shift amount is > 0, then we need to print the shift type. 
                    if(shift_eor == 0): # LSL variant
                        shift_eor_string = ' {LSL #' + str(shamt) + '}'
                    elif(shift_eor == 1): # LSR variant
                        shift_eor_string = ' {LSR #' + str(shamt) + '}'
                    elif(shift_eor == 2): # ASR variant
                        shift_eor_string = ' {ASR #' + str(shamt) + '}'
                    elif(shift_eor == 3): # ROR variant
                        shift_eor_string = ' {ROR #' + str(shamt) + '}'
                    d.arg1.append(rm)
                    d.arg2.append(rn)
                    d.arg3.append(rd)
                    d.arg1_string.append('\tR' + str(rd))
                    d.arg2_string.append(', R' + str(rn))
                    d.arg3_string.append(', R' + str(rm))
                    d.arg4.append(shift_eor)
                    d.arg4_string.append(shift_eor_string)
            '''
            
        elif (instruction_format == 'D'):  # D-Type
            d.data.append(0)
            d.arg1.append(address)
            d.arg2.append(op2)
            d.arg3.append(rt)
            d.arg1_string.append('\tR' + str(rt))
            d.arg2_string.append(', [R' + str(rn))
            d.arg3_string.append(', #' + str(address) + ']')
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        elif (instruction_format == 'I'):  # I-Type
            d.data.append(0)
            d.arg1.append(immediateI)
            d.arg2.append(rn)
            d.arg3.append(rd)
            d.arg1_string.append('\tR' + str(rd))
            d.arg2_string.append(', R' + str(rn))
            d.arg3_string.append(', #' + str(immediateI))
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        elif (instruction_format == 'IM'):  # IM-Type
            d.data.append(0)
            d.arg1.append(immediateIM)
            d.arg2.append(hw)
            d.arg3.append(rd)
            d.arg1_string.append('\tR' + str(rd))
            d.arg2_string.append(', ' + str(immediateIM))
            d.arg3_string.append(', LSL ' + str(hw * 16)) # fixed problem to account for the *16
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        elif (instruction_format == 'CB'):  # CB-Type
            d.data.append(0)
            d.arg1.append(addressCB) # NEEDS TWOS COMP
            d.arg2.append(0)
            d.arg3.append(rt)
            d.arg1_string.append('\tR' + str(rt))
            d.arg2_string.append(', #' + str(addressCB))
            d.arg3_string.append('')
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        elif (instruction_format == 'B'):
            d.data.append(0)
            d.arg1.append(addressB) # NEEDS TWOS COMP
            d.arg2.append(0)
            d.arg3.append(0)
            d.arg1_string.append('\t#' + str(addressB))
            d.arg2_string.append('')
            d.arg3_string.append('')
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        elif (instruction_format == 'mem'):  # Memory Data
            d.arg1.append(0)
            d.arg2.append(0)
            d.arg3.append(0)
            d.arg1_string.append('')
            d.arg2_string.append('')
            d.arg3_string.append('')
            d.data.append(d.twos_comp(current_line))
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        else:  # TEMPORARY, for types not yet supported (NEEDS LOGIC FOR INVALID INSTRUCTIONS HERE)
            d.data.append(0)
            d.arg1.append(0)
            d.arg2.append(0)
            d.arg3.append(0)
            d.arg1_string.append('')
            d.arg2_string.append('')
            d.arg3_string.append('')
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
    # end of function parse_line()

    def run(self, inputFileName, outputFileName):
        # Create lists to hold instruction information:
        d.instruction = []  # list of full instruction (strings)
        d.instruction_spaced = []  # list of full instruction spaced for printing (strings)
        d.opcode = []  # list of opcode base-10 (integers)
        d.opcode_string = []  # list of opcode names (strings)
        d.arg1 = []  # list of args (integers)
        d.arg2 = []  # list of args (integers)
        d.arg3 = []  # list of args (integers)
        d.arg1_string = []  # list of printable args (strings)
        d.arg2_string = []  # list of printable args (strings)
        d.arg3_string = []  # list of printable args (strings)
        d.data = []  # memory data (strings)
        d.arg4 = [] # for EOR...
        d.arg4_string = [] # for EOR...

        #Create a flag to deal with BREAK instruction:
        d.break_flag = False
        
        # Parse all lines in the file:
        instruction_index = 0
        infile = open(inputFileName, 'r')
        current_line = infile.readline()
        while (current_line != ''):
            d.parse_line(current_line, instruction_index)
            current_line = infile.readline()
            instruction_index += 1

        # Print all in proper format:
        d.print_lines(instruction_index, outputFileName)

        # Close the input file:
        infile.close()

# BEGIN PROGRAM:
if __name__ == '__main__':

    # Get command line args:
    for i in range(len(sys.argv)):
      if (sys.argv[i] == '-i' and i < (len(sys.argv) - 1)):
        inputFileName = sys.argv[i + 1]
      elif (sys.argv[i] == '-o' and i < (len(sys.argv) - 1)):
        outputFileName = sys.argv[i + 1] + '_dis.txt'
        
    # Create Disassembler object:
    d = Disassembler()
    d.run(inputFileName, outputFileName)
