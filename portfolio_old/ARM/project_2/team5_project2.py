# team5_project2.py
# Authors: Jeremy Ecker, Kameron Bush

import sys

class Disassembler:
    # Constructor:
    def __init__(self):
        pass

    # Converts unsigned string of binary to signed integer:
    def twos_comp(self, binary_string):
        if (int(binary_string, 2) > 2 ** (len(binary_string) - 1) - 1):
            return int(binary_string, 2) - (1 << len(binary_string))
        else:
            return int(binary_string, 2)

    # Writes the DIS file:
    def write_dis(self, instruction_index, outputFileName):
        f = open(outputFileName + '_dis.txt', 'w')
        i = 0
        while (i < instruction_index):
            if (d.opcode_string[i] == 'memory_data'):
                f.write(d.instruction[i] + '\t' + str(96 + i * 4) + '\t'
                + str(d.data[i]) + '\n')
            else:
                f.write(d.instruction_spaced[i] + str(96 + i * 4) + '\t'
                    + d.opcode_string[i] + d.arg1_string[i] + d.arg2_string[i]
                    + d.arg3_string[i] + '\n')
            i += 1
        f.close()

    # Parses a line of the input file:
    def parse_line(self, current_line, instruction_index):
        # Add instruction to instruction list and instruction_spaced list:
        current_line = current_line.rstrip('\t\n')
        d.instruction.append(current_line)
        printable_instruction = str(current_line[0:8] + ' ' + current_line[8:11]
            + ' ' + current_line[11:16] + ' ' + current_line[16:21] + ' '
            + current_line[21:26] + ' ' + current_line[26:32] + '\t')
        d.instruction_spaced.append(printable_instruction)

        # Local variable declarations:
        instruction_type = ''
        instruction_format = ''
        rm = int(current_line[11:16], 2)  # Source 2 (arg2) (5 bits)
        shamt = int(current_line[16:22], 2)  # Shift amount (6 bits)
        rn = int(current_line[22:27], 2)  # Source 1 (arg1) (5 bits)
        rd = int(current_line[27:32], 2)  # Destination (arg3) (5 bits)
        #immediateI = d.twos_comp(current_line[10:22])  # (12 bits) <- WRONG!
        immediateI = d.twos_comp(current_line[11:22])  # 11 bits!
        immediateIM = int(current_line[11:27], 2)
        hw = int(current_line[9:11], 2)
        address = int(current_line[11:20], 2)  # (9 bits)
        addressB = d.twos_comp(current_line[6:32])
        addressCB = d.twos_comp(current_line[8:27])
        op2 = int(current_line[21:23], 2)  # (2 bits)
        rt = int(current_line[27:32], 2)  # (5 bits)
        shift_eor = int(current_line[8:10], 2)  # (2 bits)
        shift_eor_string = ''  # needed for alternate EOR...

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
        elif (int(current_line[0:11], 2) == 1692):  # ASR
            instruction_type = 'ASR'
            instruction_format = 'R'
            d.opcode.append(1692)
        elif (int(current_line[0:11], 2) == 1872):  # EOR: simple format
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
        # MOVZ: rd = LSL(imm) * hw * 16
        elif (int(current_line[0:11], 2) >= 1684 and
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
        elif (int(current_line[0:11], 2) == 2038):  # BREAK
            instruction_type = 'BREAK'
            instruction_format = 'BREAK'
            d.opcode.append(int(current_line[0:11], 2))
            d.break_flag = True
            d.break_index = instruction_index
        elif (d.break_flag == False and int(current_line, 2) == 0):  # NOP
            instruction_type = 'NOP'
            instruction_format = 'R'
            d.opcode.append(0)
        elif (d.break_flag):
            instruction_type = 'memory_data'  # memory data
            instruction_format = 'mem'
            d.opcode.append(int(current_line[0:11], 2))

        # Write the instruction type string to list:
        d.opcode_string.append(instruction_type)

        # Put args into respective lists by type:
        # R-Type:
        if (instruction_format == 'R'):
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
            elif (instruction_type == 'LSL' or instruction_type == 'LSR'
                    or instruction_type == 'ASR'):
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
        # D-Type:
        elif (instruction_format == 'D'):
            d.data.append(0)
            d.arg1.append(address)
            d.arg2.append(rn)
            d.arg3.append(rt)
            d.arg1_string.append('\tR' + str(rt))
            d.arg2_string.append(', [R' + str(rn))
            d.arg3_string.append(', #' + str(address) + ']')
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        # I-Type:
        elif (instruction_format == 'I'):
            d.data.append(0)
            d.arg1.append(immediateI)
            d.arg2.append(rn)
            d.arg3.append(rd)
            d.arg1_string.append('\tR' + str(rd))
            d.arg2_string.append(', R' + str(rn))
            d.arg3_string.append(', #' + str(immediateI))
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        # IM-Type:
        elif (instruction_format == 'IM'):
            d.data.append(0)
            d.arg1.append(immediateIM)
            d.arg2.append(hw)
            d.arg3.append(rd)
            d.arg1_string.append('\tR' + str(rd))
            d.arg2_string.append(', ' + str(immediateIM))
            d.arg3_string.append(', LSL ' + str(hw * 16))
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        # CB-Type:
        elif (instruction_format == 'CB'):
            d.data.append(0)
            d.arg1.append(addressCB)
            d.arg2.append(0)
            d.arg3.append(rt)
            d.arg1_string.append('\tR' + str(rt))
            d.arg2_string.append(', #' + str(addressCB))
            d.arg3_string.append('')
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        # B-Type:
        elif (instruction_format == 'B'):
            d.data.append(0)
            d.arg1.append(addressB)
            d.arg2.append(0)
            d.arg3.append(0)
            d.arg1_string.append('\t#' + str(addressB))
            d.arg2_string.append('')
            d.arg3_string.append('')
            d.arg4.append(shift_eor)
            d.arg4_string.append(shift_eor_string)
        # Memory Data:
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
        # For unsupported types (if bad instructions are encountered):
        else:
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

    # SIMULATOR:
    def simulate(self, instruction_index):
        # First deal with B and CB instructions:
        if (d.opcode_string[instruction_index] == 'B'
          or d.opcode_string[instruction_index] == 'CBZ'
          or d.opcode_string[instruction_index] == 'CBNZ'):

            addr = d.arg1[instruction_index]
            rt = d.registers[d.arg3[instruction_index]]

            if(d.opcode_string[instruction_index] == 'B'):
                if(addr >= 0):
                    d.pc_current += addr * 4
                elif(addr < 0):
                    d.pc_current -= abs(addr) * 4

            elif(d.opcode_string[instruction_index] == 'CBZ'):
                if(rt == 0):
                    if(addr >= 0):
                        d.pc_current += addr * 4
                    elif(addr < 0):
                        d.pc_current -= abs(addr) * 4
                else:
                    d.pc_current += 4

            elif(d.opcode_string[instruction_index] == 'CBNZ'):
                if(rt != 0):
                    if(addr >= 0):
                        d.pc_current += addr * 4
                    elif(addr < 0):
                        d.pc_current -= abs(addr) * 4
                else:
                    d.pc_current += 4

        # Then deal with all other instructions:
        else:
            # ADDI:
            if (d.opcode_string[instruction_index] == 'ADDI'):
                rd = d.arg3[instruction_index]
                rn = d.registers[d.arg2[instruction_index]]
                imm = d.arg1[instruction_index]
                d.registers[rd] = rn + imm

            # SUBI:
            elif (d.opcode_string[instruction_index] == 'SUBI'):
                rd = d.arg3[instruction_index]
                rn = d.registers[d.arg2[instruction_index]]
                imm = d.arg1[instruction_index]
                d.registers[rd] = rn - imm

            # ADD:
            elif (d.opcode_string[instruction_index] == 'ADD'):
                d.registers[d.arg3[instruction_index]] = (
                    d.registers[d.arg1[instruction_index]]
                    + d.registers[d.arg2[instruction_index]])

            # SUB:
            elif (d.opcode_string[instruction_index] == 'SUB'):
                d.registers[d.arg3[instruction_index]] = (
                    d.registers[d.arg2[instruction_index]]
                    - d.registers[d.arg1[instruction_index]])

            # AND: (rd = rn & rm)
            elif (d.opcode_string[instruction_index] == 'AND'):
                rn = d.registers[d.arg2[instruction_index]]
                rm = d.registers[d.arg1[instruction_index]]
                result = rn & rm
                d.registers[d.arg3[instruction_index]] = result

            # ORR: (rd = rn | rm)
            elif (d.opcode_string[instruction_index] == 'ORR'):
                rn = d.registers[d.arg2[instruction_index]]
                rm = d.registers[d.arg1[instruction_index]]
                result = rn | rm
                d.registers[d.arg3[instruction_index]] = result

            # LSL: (rd = rn << shamt)
            elif (d.opcode_string[instruction_index] == 'LSL'):
                rn = d.registers[d.arg2[instruction_index]]
                shamt = d.arg1[instruction_index]
                d.registers[d.arg3[instruction_index]] = rn << shamt

            # LSR: (rd = rn >> shamt)
            elif (d.opcode_string[instruction_index] == 'LSR'):
                mask = 1 << 64
                d.registers[d.arg3[instruction_index]] = (
                    (d.registers[d.arg2[instruction_index]] % mask)
                    >> d.arg1[instruction_index])

            # ASR: (R[arg3] = R[arg2] signextend >> arg1)
            elif(d.opcode_string[instruction_index] == 'ASR'):
                d.registers[d.arg3[instruction_index]] = (
                    d.registers[d.arg2[instruction_index]]
                    >> d.arg1[instruction_index])

            # EOR: (rd = rn ^ rm)
            elif (d.opcode_string[instruction_index] == 'EOR'):
                rn = d.registers[d.arg2[instruction_index]]
                rm = d.registers[d.arg1[instruction_index]]
                result = rn ^ rm
                d.registers[d.arg3[instruction_index]] = result

            # STUR:
            elif(d.opcode_string[instruction_index] == 'STUR'):
                rt = d.arg3[instruction_index]
                rn = d.arg2[instruction_index]
                imm = d.arg1[instruction_index]
                dest = d.registers[rn] + imm * 4
                source = d.registers[rt]

                # If no memory exists yet we have to create it:
                if(len(d.memory) == 0):
                    i = 96 + d.break_index * 4 + 4

                    # CHECK FOR BAD DESTINATION:
                    if(i > dest):
                        print('Invalid destination for STUR. Exiting program.')
                        sys.exit()

                    while(i <= dest):
                        d.memory_pc_array.append(i)
                        if(i < dest):
                            d.memory.append(0)
                        else:
                            d.memory.append(source)
                        i += 4

                # If memory already exists:
                else:
                    k = len(d.memory_pc_array) - 1
                    j = d.memory_pc_array[k]

                    # CHECK FOR BAD DESTINATION:
                    if(j < (96 + d.break_index * 4 + 4)):
                        print('Invalid destination for STUR. Exiting program.')
                        sys.exit()

                    # If target is outside the range of memory, expand:
                    if(j < dest):
                        while(j <= dest):
                            if(j < dest - 4):
                                d.memory.append(0)
                                d.memory_pc_array.append(j)
                            elif(j == dest):
                                d.memory.append(source)
                                d.memory_pc_array.append(j)
                            j += 4

                    # If target already exists, replace:
                    elif(j >= dest):
                        # CHECK FOR BAD DESTINATION:
                        try:
                            target = d.memory_pc_array.index(dest)
                            d.memory[target] = source
                        except:
                            print('Invalid destination for STUR. Exiting program.')
                            sys.exit()

            # LDUR:
            elif(d.opcode_string[instruction_index] == 'LDUR'):
                rt = d.arg3[instruction_index]
                rn = d.arg2[instruction_index]
                imm = d.arg1[instruction_index]

                try:
                    source = d.registers[rn] + imm * 4
                    dest = d.registers[rt]
                    source_index = d.memory_pc_array.index(source)
                    d.registers[rt] = d.memory[source_index]
                except:
                    print('Invalid source for LDUR. Exiting program.')
                    sys.exit()

            # MOVZ (rd = LSL(imm) * hw * 16):
            elif(d.opcode_string[instruction_index] == 'MOVZ'):
                rd = d.arg3[instruction_index]
                imm = d.arg1[instruction_index]
                lsl = d.arg2[instruction_index]

                dest = d.registers[rd]

                if(lsl == 0):
                    source = imm
                else:
                    source = (imm * lsl) << 16

                d.registers[rd] = source

            # MOVK (instruction[22:21]*16-15 = movimm):
            elif(d.opcode_string[instruction_index] == 'MOVK'):
                # Get args:
                rd = d.arg3[instruction_index]
                imm = d.arg1[instruction_index]
                lsl = d.arg2[instruction_index]

                # Get binary string of destination value:
                dest = str(bin(d.registers[rd])).lstrip('0b').zfill(64)

                # Get binary string of source value:
                source = str(bin(imm)).lstrip('0b').zfill(16)

                # Replace the appropriate slice with the new value:
                if(lsl == 0):
                    dest = dest[0:48] + source # originally 0:49
                elif(lsl == 1):
                    dest = dest[0:33] + source + dest[48:65]
                elif(lsl == 2):
                    dest = dest[0:17] + source + dest[32:65]
                elif(lsl == 3):
                    dest = source + dest[16:65]

                # Put the result in the destination register:
                d.registers[rd] = d.twos_comp(dest)

            # Increment the program counter:
            d.pc_current += 4

        # Put all current register contents in the list of lists:
        d.registers_per_instruction.append(d.registers[:])

        # Put memory into lists of lists:
        d.memory_of_memory.append(d.memory[:])
        d.memory_pc_of_memory_pc.append(d.memory_pc_array[:])

    # NEW SIM WRITER:
    def write_sim_new(self, outputFileName):
        f = open(outputFileName + '_sim.txt', 'w')

        x = 0
        while (x < len(d.print_indexes)):
            i = d.print_indexes[x]
            if((d.ex_flag_array[i] == True)
                and (d.opcode_string[i] != 'memory_data')):

                # Cycle, PC, Instruction:
                f.write('=' * 20 + '\ncycle:' + str(x + 1) + '\t'
                        + str(d.pc_current_array[x])
                        + '\t' + d.opcode_string[i] + d.arg1_string[i]
                        + d.arg2_string[i] + d.arg3_string[i]
                        + '\n\nregisters:\nr00:\t')

                # Registers:
                j = 0
                while (j < 8):
                    f.write(str(d.registers_per_instruction[x][j]) + '\t')
                    j += 1
                f.write('\nr08:\t')
                while (j < 16):
                    f.write(str(d.registers_per_instruction[x][j]) + '\t')
                    j += 1
                f.write('\nr16:\t')
                while (j < 24):
                    f.write(str(d.registers_per_instruction[x][j]) + '\t')
                    j += 1
                f.write('\nr24:\t')
                while (j < 32):
                    f.write(str(d.registers_per_instruction[x][j]) + '\t')
                    j += 1
                f.write('\n\ndata:\n')

                # Memory Data:
                k = 0
                m = 0
                local_mem = []
                local_mem_pc = []

                if(d.mem_flag == True):
                    local_mem = d.memory_of_memory[i+1]
                    local_mem_pc = d.memory_pc_of_memory_pc[i+1]
                else:
                    local_mem = d.memory_of_memory[i]
                    local_mem_pc = d.memory_pc_of_memory_pc[i]

                while(k <= int(len(local_mem) / 8)):
                    if(k < len(local_mem)):
                        if(m == 0):
                            f.write(str(local_mem_pc[m]) + ':\t')
                        else:
                            f.write(str(local_mem_pc[m+1]) + ':\t') # originally m+k-1
                        l = 0
                        if((l+m) < len(local_mem)):
                            while(l < 8):
                                if((l+m) < len(local_mem)):
                                    f.write(str(local_mem[l+m]) + '\t')
                                else:
                                    f.write('0\t')
                                l += 1
                        f.write('\n')
                    m += 8
                    k += 1

            f.write('\n')
            x += 1

        f.close()

        # Fix the trailing tab characters (and other monkey-business):
        f = open(outputFileName + '_sim.txt', 'rw+')
        #f.seek(0)
        for line in f:
            line = line.rstrip('\t')
        f.close()

    def run(self, inputFileName, outputFileName):
        # Create lists to hold instruction information:
        d.instruction = []  # list of full instruction (strings)
        d.instruction_spaced = []  # list of instruction spaced (strings)
        d.opcode = []  # list of opcode base-10 (integers)
        d.opcode_string = []  # list of opcode names (strings)
        d.arg1 = []  # list of args (integers)
        d.arg2 = []  # list of args (integers)
        d.arg3 = []  # list of args (integers)
        d.arg1_string = []  # list of printable args (strings)
        d.arg2_string = []  # list of printable args (strings)
        d.arg3_string = []  # list of printable args (strings)
        d.data = []  # memory data (strings)
        d.arg4 = []  # for EOR...
        d.arg4_string = []  # for EOR...

        # Create a flag to deal with BREAK instruction:
        d.break_flag = False

        # Registers:
        d.registers = []  # list of register contents (ints)
        register_index = 0
        while (register_index < 32):  # populate list with 32 zeroes
            d.registers.append(0)
            register_index += 1
        d.registers_per_instruction = []  # a list of a list of registers

        # Memory data:
        d.memory = []  # list of memory contents (ints)
        d.memory_pc_array = []
        d.break_index = 0
        d.memory_of_memory = []
        d.memory_pc_of_memory_pc = []
        d.mem_flag = False

        # Program counters:
        d.pc_mainline = 96 # for all instructions
        d.pc_current = 96 # for executed instructions
        d.pc_current_array = []
        d.pc_current_array.append(d.pc_current)

        # Execution flags:
        d.ex_flag = False
        d.ex_flag_array = []

        # Parse all lines in the file:
        instruction_index = 0
        infile = open(inputFileName, 'r')
        current_line = infile.readline()
        while (current_line != ''):
            d.parse_line(current_line, instruction_index)
            current_line = infile.readline()
            instruction_index += 1

        # Construct the memory list using parsed data:
        j = 0
        while(j < instruction_index):
            if(d.opcode_string[j] == 'memory_data'):
                d.memory.append(d.data[j])
                d.mem_flag = True
            j += 1

        # Construct the Memory PC array if memory exists:
        if(d.mem_flag == True):
            d.memory_of_memory.append(d.memory[:])
            mem_start = 96 + d.break_index * 4 + 4
            mem_end = mem_start + len(d.memory) * 4
            while(mem_start < mem_end):
                d.memory_pc_array.append(mem_start)
                mem_start += 4

        # Construct an array of indexes for printing:
        d.print_indexes = []

        # Simulate program:
        k = 0
        while (k < instruction_index):
            if (d.pc_current == d.pc_mainline):

                '''print(d.instruction_spaced[k] + str(d.pc_current) + '\t'
                    + d.opcode_string[k] + d.arg1_string[k] + d.arg2_string[k]
                    + d.arg3_string[k] + '\n')'''

                d.simulate(k)
                d.pc_current_array.append(d.pc_current)
                d.print_indexes.append(k)
                d.ex_flag = True
            else:
                d.ex_flag = False
            d.ex_flag_array.append(d.ex_flag)

            if(d.ex_flag == True and (d.opcode_string[k] == 'B'
                or d.opcode_string[k] == 'CBZ' or d.opcode_string[k] == 'CBNZ')):
                d.pc_mainline = d.pc_current
                k = (d.pc_current - 96) / 4
            else:
                d.pc_mainline += 4
                k += 1

        # Close the input file:
        infile.close()

        # Write the DIS file:
        d.write_dis(instruction_index, outputFileName)

        # new SIM writer:
        d.write_sim_new(outputFileName)

# BEGIN PROGRAM:
if __name__ == '__main__':

    # Get command line args:
    for i in range(len(sys.argv)):
        if (sys.argv[i] == '-i' and i < (len(sys.argv) - 1)):
            inputFileName = sys.argv[i + 1]
        elif (sys.argv[i] == '-o' and i < (len(sys.argv) - 1)):
            outputFileName = sys.argv[i + 1]

    # Create Disassembler object:
    d = Disassembler()
    d.run(inputFileName, outputFileName)

