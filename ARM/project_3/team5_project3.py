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
            elif (instruction_type == 'LSL' or instruction_type == 'LSR'
                    or instruction_type == 'ASR'):
                d.arg1.append(shamt)
                d.arg2.append(rn)
                d.arg3.append(rd)
                d.arg1_string.append('\tR' + str(rd))
                d.arg2_string.append(', R' + str(rn))
                d.arg3_string.append(', #' + str(shamt))
            elif (instruction_type == 'NOP'):
                d.arg1.append(0)
                d.arg2.append(0)
                d.arg3.append(0)
                d.arg1_string.append('')
                d.arg2_string.append('')
                d.arg3_string.append('')
            elif (instruction_type == 'EOR'):
                d.arg1.append(rm)
                d.arg2.append(rn)
                d.arg3.append(rd)
                d.arg1_string.append('\tR' + str(rd))
                d.arg2_string.append(', R' + str(rn))
                d.arg3_string.append(', R' + str(rm))
        # D-Type:
        elif (instruction_format == 'D'):
            d.data.append(0)
            d.arg1.append(address)
            d.arg2.append(rn)
            d.arg3.append(rt)
            d.arg1_string.append('\tR' + str(rt))
            d.arg2_string.append(', [R' + str(rn))
            d.arg3_string.append(', #' + str(address) + ']')
        # I-Type:
        elif (instruction_format == 'I'):
            d.data.append(0)
            d.arg1.append(immediateI)
            d.arg2.append(rn)
            d.arg3.append(rd)
            d.arg1_string.append('\tR' + str(rd))
            d.arg2_string.append(', R' + str(rn))
            d.arg3_string.append(', #' + str(immediateI))
        # IM-Type:
        elif (instruction_format == 'IM'):
            d.data.append(0)
            d.arg1.append(immediateIM)
            d.arg2.append(hw)
            d.arg3.append(rd)
            d.arg1_string.append('\tR' + str(rd))
            d.arg2_string.append(', ' + str(immediateIM))
            d.arg3_string.append(', LSL ' + str(hw * 16))
         # CB-Type:
        elif (instruction_format == 'CB'):
            d.data.append(0)
            d.arg1.append(addressCB)
            d.arg2.append(0)
            d.arg3.append(rt)
            d.arg1_string.append('\tR' + str(rt))
            d.arg2_string.append(', #' + str(addressCB))
            d.arg3_string.append('')
        # B-Type:
        elif (instruction_format == 'B'):
            d.data.append(0)
            d.arg1.append(addressB)
            d.arg2.append(0)
            d.arg3.append(0)
            d.arg1_string.append('\t#' + str(addressB))
            d.arg2_string.append('')
            d.arg3_string.append('')
        # Memory Data:
        elif (instruction_format == 'mem'):  # Memory Data
            d.arg1.append(0)
            d.arg2.append(0)
            d.arg3.append(0)
            d.arg1_string.append('')
            d.arg2_string.append('')
            d.arg3_string.append('')
            d.data.append(d.twos_comp(current_line))
        # For unsupported types (if bad instructions are encountered):
        else:
            d.data.append(0)
            d.arg1.append(0)
            d.arg2.append(0)
            d.arg3.append(0)
            d.arg1_string.append('')
            d.arg2_string.append('')
            d.arg3_string.append('')
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

#-----------------------end class Dissassembler.-------------------------------

#-----------------------Pipeline Class Begins:---------------------------------
class Pipeline:
    # Constructor (takes argument of Dissassembler object):
    def __init__(self, d):
        pass
    # end of constructor.

    # Print register method (for testing only):
    def print_registers(self):
        k = 0
        sys.stdout.write('\nr00:\t')
        while (k < 8):
            sys.stdout.write(str(p.registers[k]) + '\t')
            k += 1
        sys.stdout.write('\nr08:\t')
        while (k < 16):
            sys.stdout.write(str(p.registers[k]) + '\t')
            k += 1
        sys.stdout.write('\nr16:\t')
        while (k < 24):
            sys.stdout.write(str(p.registers[k]) + '\t')
            k += 1
        sys.stdout.write('\nr24:\t')
        while (k < 32):
            sys.stdout.write(str(p.registers[k]) + '\t')
            k += 1
    # end of method print_registers.

    # Print State of everything:
    def print_state(self):
        # header:
        p.f.write('-' * 20 + '\nCycle ' + str(p.cycle) + ':\n\n')

        # pre issue buffer:
        p.f.write('Pre-Issue Buffer:\n')
        k = 0
        while(k < len(p.pre_issue_buff)):
            p.f.write('\tEntry ' + str(k) + ':\t')
            if(p.pre_issue_buff[k] > 0):
                inst_str = (d.opcode_string[p.pre_issue_buff[k]]
                    + d.arg1_string[p.pre_issue_buff[k]]
                    + d.arg2_string[p.pre_issue_buff[k]]
                    + d.arg3_string[p.pre_issue_buff[k]])
                p.f.write('[' + inst_str + ']\n')
            else:
                p.f.write('\n')
            k += 1

        # pre alu buffer:
        p.f.write('Pre-ALU Queue:\n')
        k = 0
        while(k < len(p.pre_alu_buff)):
            p.f.write('\tEntry ' + str(k) + ':\t')
            if(p.pre_alu_buff[k] > 0):
                inst_str = (d.opcode_string[p.pre_alu_buff[k]]
                    + d.arg1_string[p.pre_alu_buff[k]]
                    + d.arg2_string[p.pre_alu_buff[k]]
                    + d.arg3_string[p.pre_alu_buff[k]])
                p.f.write('[' + inst_str + ']\n')
            else:
                p.f.write('\n')
            k += 1

        # post alu buffer(value, instruction_index):
        p.f.write('Post-Alu Queue:\n')
        p.f.write('\tEntry 0' + ':\t')
        if(p.post_alu_buff[1] > 0):
            inst_str = (d.opcode_string[p.post_alu_buff[1]]
                + d.arg1_string[p.post_alu_buff[1]]
                + d.arg2_string[p.post_alu_buff[1]]
                + d.arg3_string[p.post_alu_buff[1]])
            p.f.write('[' + inst_str + ']\n')
        else:
            p.f.write('\n')

        # pre mem buffer:
        p.f.write('Pre-Mem Queue:\n')
        k = 0
        while(k < len(p.pre_mem_buff)):
            p.f.write('\tEntry ' + str(k) + ':\t')
            if(p.pre_mem_buff[k] > 0):
                inst_str = (d.opcode_string[p.pre_mem_buff[k]]
                    + d.arg1_string[p.pre_mem_buff[k]]
                    + d.arg2_string[p.pre_mem_buff[k]]
                    + d.arg3_string[p.pre_mem_buff[k]])
                p.f.write('[' + inst_str + ']\n')
            else:
                p.f.write('\n')
            k += 1

        # post mem buffer:
        p.f.write('Post-Mem Queue:\n')
        k = 0
        while(k < len(p.post_mem_buff)):
            p.f.write('\tEntry ' + str(k) + ':\t')
            if(p.post_mem_buff[k] > 0):
                inst_str = (d.opcode_string[p.post_mem_buff[k]]
                    + d.arg1_string[p.post_mem_buff[k]]
                    + d.arg2_string[p.post_mem_buff[k]]
                    + d.arg3_string[p.post_mem_buff[k]])
                p.f.write('[' + inst_str + ']\n')
            else:
                p.f.write('\n')
            k += 1

        # registers:
        p.f.write('Registers\n')
        j = 0
        p.f.write('R00:\t')
        while (j < 8):
            p.f.write(str(p.registers[j]) + '\t')
            j += 1
        p.f.write('\nR08:\t')
        while (j < 16):
            p.f.write(str(p.registers[j]) + '\t')
            j += 1
        p.f.write('\nR16:\t')
        while (j < 24):
            p.f.write(str(p.registers[j]) + '\t')
            j += 1
        p.f.write('\nR24:\t')
        while (j < 32):
            p.f.write(str(p.registers[j]) + '\t')
            j += 1

        # cache:
        p.f.write('\n\nCache\n')
        i = 0
        while(i < 4):
            j = 0
            p.f.write('Set ' + str(i) + ': LRU=' + str(p.lru[i]) + '\n')
            while(j < 2):
                k = 0
                p.f.write('\tEntry ' + str(j) + ': [(')
                while(k < 3):
                    p.f.write(str(p.cache_array[i][j][k]))
                    if(k < 2):
                        p.f.write(',')
                    k += 1
                p.f.write(')<')
                while(k < 5):
                    p.f.write(str(p.cache_array[i][j][k]))
                    if(k < 4):
                        p.f.write(',')
                    else:
                        p.f.write('>]\n')
                    k += 1
                j += 1
            i += 1

        # memory:
        p.f.write('Data\n')
        k = 0
        while(k < len(p.memory)):
            if(k == 0):
                p.f.write(str(p.memory_pc[k]) + ':\t')
            elif(k % 8 == 0):
                p.f.write('\n' + str(p.memory_pc[k]) + ':\t')
            p.f.write(str(p.memory[k]) + ' ')
            k += 1
        p.f.write('\n')

    # end of method print_state.

    # Write Back Unit:
    def wb(self):
        # Post MEM buffer:
        # LDUR only.
        # instruction index (which gives you the destination reg for the
        # writeback unit) and data will be written to the post-MEM buffer.
        if(p.post_mem_buff[1] != -1):
            # inputs:
            value = p.post_mem_buff[0]
            instruction_index = p.post_mem_buff[1]

            # calculate destination:
            dest = d.arg3[instruction_index]

            # push operation to register file:
            p.registers[dest] = value

            # reset post mem buffer when finished:
            p.post_mem_buff[0] = -1
            p.post_mem_buff[1] = -1

        # Post ALU buffer:
        # The ALU handles all non-memory instructions (everything except LDUR
        # and STUR and branch instructions that are handled in the IF stage).
        # The post-ALU buffer has one entry that can store the instruction
        # with the destination register ID and the result of the ALU operation.
        if(p.post_alu_buff[1] != -1):
            # inputs:
            value = p.post_alu_buff[0]
            instruction_index = p.post_alu_buff[1]

            # calculate destination:
            dest = d.arg3[instruction_index]

            # push operation to register file:
            p.registers[dest] = value

            # reset post mem buffer when finished:
            p.post_alu_buff[0] = -1
            p.post_alu_buff[1] = -1
    # end of method wb.

    # ALU unit:
    def alu(self):
        if(p.pre_alu_buff[0] != -1):
            instruction_index = p.pre_alu_buff[0]
            local_regs = d.registers_per_instruction[instruction_index]
            result = local_regs[d.arg3[instruction_index]]

            p.post_alu_buff[0] = result
            p.post_alu_buff[1] = instruction_index

            p.pre_alu_buff[0] = p.pre_alu_buff[1]
            p.pre_alu_buff[1] = -1
    # end of method alu.

    # CHECK CACHE (modeled on LecProject3CacheUnitNoMid.pptx):
    def check_cache(self, mem_index, instruction_index, is_write, data_to_write):
        # find address of instruction or data location (slide 14):
        if(mem_index == -1): # it is an instruction.
            local_address = 96 + (4 * instruction_index)
        else: # it is data.
            local_address = 96 + d.break_index + (4 * mem_index)

        # find addresses for two words taking into account alignment (slide 15):
        if(local_address % 8 == 0): # alignment is okay.
            data_word = 0 # block 0 was the address.
            address1 = local_address
            address2 = local_address + 4
        else: # alignment is not okay.#print('You figure it out...')
            data_word = 1
            address1 = local_address - 4
            address2 = local_address

        # always go to memory and get contents (slide 16):
        # if instruction, get instruction from d.instruction[]
        if(address1 < 96 + (d.break_index * 4)):
            data1 = d.instruction[instruction_index]
        # if data, get data from memory:
        else:
            data1 = d.instruction[instruction_index]
            data2 = d.instruction[instruction_index + 1]

            #data1 = p.memory_pc[mem_index]
            #data2 = p.memory_pc[mem_index + 1]

            #mem_snapshot = p.memory_pc[mem_index]
            #data1 = mem_snapshot[address1]
            #data2 = mem_snapshot[address2] # ??? methinks..

        # writing to memory (slide 17):
        if(is_write and data_word == 0):
            data1 = data_to_write
        elif(is_write and data_word == 1):
            data2 = data_to_write

        # decode address for cache check (slide 18):
        set_num = (address1 & p.set_mask) >> 3
        tag = (address1 & p.tag_mask) >> 5

        # check for hit or miss (slide 20):
        hit = False # has to be initialized in case of miss.
        if(p.cache_array[set_num][0][0] == 1 and p.cache_array[set_num][0][2] == tag):
            hit = True
            assoc_block = 0
        elif(p.cache_array[set_num][1][0] == 1 and p.cache_array[set_num][1][2] == tag):
            hit = True
            assoc_block = 1

        # hit (slide 21):
        if(hit):
            if(hit and is_write):
                # set dirty bit:
                p.cache_array[set_num][assoc_block][1] = 1
                # set lru bit:
                p.lru[set_num] = (assoc_block + 1) % 2
                p.cache_array[set_num][assoc_block][data_word + 3] = data_to_write
            elif(hit):
                p.lru[set_num] = (assoc_block + 1) % 2

            # return true hit and data or instruction in word.
            # data word specifies either first or second word in block
            # based on what the instruction was. (slide 22):
            return[True, p.cache_array[set_num][assoc_block][data_word + 3]]

        # miss (slide 23):
        if(address1 in p.miss_list):
            while(p.miss_list.count(address1) > 0):
                p.miss_list.remove(address1)

        # write back if needed (slide 25):
        if(p.cache_array[set_num][p.lru[set_num]][1] == 1):
            wb_addr = p.cache_array[set_num][p.lru[set_num]][2] # tag
            wb_addr = (wb_addr << 5) + (set_num << 3)

            if(wb_addr >= d.break_index * 4 + 100):
                p.memory[d.memory_pc_of_memory_pc[instruction_index]] = (
                    p.cache_array[set_num][p.lru[set_num]][3] )

            if(wb_addr + 4 >= d.break_index * 4 + 100):
                p.memory[d.memory_pc_of_memory_pc[instruction_index + 4]] = (
                    p.cache_array[set_num][p.lru[set_num]][4] )

        # now write cache (slide 26):
        # update cache flag bits:
        p.cache_array[set_num][p.lru[set_num]][0] = 1 # valid we are writing a block
        p.cache_array[set_num][p.lru[set_num]][1] = 0 # reset dirty bit

        # dirty if is data mem is dirty again, instruction mem never dirty:
        if(is_write):
            p.cache_array[set_num][p.lru[set_num]][1] = 1

            # update both words in the actual cache block in set:
            p.cache_array[set_num][p.lru[set_num]][2] = tag
            p.cache_array[set_num][p.lru[set_num]][3] = data1
            p.cache_array[set_num][p.lru[set_num]][4] = data2

            # set lru to show block is recently used, 1 means block 0 MRU,
            # and 0 means block 1 MRU:
            p.lru[set_num] = (p.lru[set_num] + 1) % 2

            # datword was the actual word that generated the hit
            # p.lru[set_num] + 1 --- remember what lru bit means!
            # it gives the block number either LRU or MRU (need to reverse number):
            return [True, p.cache_array[set_num][(p.lru[set_num] + 1) % 2][data_word + 3]]

        # valid miss on cycle:
        else:
            # add the memory address to the just missed list:
            if(p.miss_list.count(address1) == 0):
                p.miss_list.append(address1)
            return [False, 0]

    # end of method check_cache.

    # MEM unit:
    '''The input for the cache is the desired memory location and the output
    is what is in the memory location and a bool true that there has been a
    hit.  I probably could have lost the bool but I like bits  So to fake it
    just return false so that you will always go to memory and get the value.
    That will at least allow you make sure everything else is working with
    only predictable one cycle delays being injected.'''
    def mem(self):
        # read the pre-mem buffer:
        instruction_index = p.pre_mem_buff[0]

        # if we have a mem operation:
        if(instruction_index != -1):
            # args from dis:
            rt = d.arg3[instruction_index]
            rn = d.arg2[instruction_index]
            imm = d.arg1[instruction_index]

            # if we have a STUR:
            if(d.opcode_string[instruction_index] == 'STUR'):
                # set source and dest:
                dest = p.registers[rn] + imm * 4
                source = p.registers[rt]
                #source_index = p.memory_pc.index(source)
                source_index = dest

                # set the 3rd arg for check_cache
                is_write = True

                # check the cache for space:
                space = p.check_cache(source_index, instruction_index, is_write, rn)

                # if we have room:
                if(space[0] == True):
                    p.pre_mem_buff[0] = p.pre_mem_buff[1]
                    p.pre_mem_buff[1] = -1

            # if we have a LDUR:
            elif(d.opcode_string[instruction_index] == 'LDUR'):
                source = p.registers[rn] + imm * 4
                dest = p.registers[rt]
                #source_index = p.memory_pc.index(source)
                source_index = source

                # set the 3rd arg for check_cache:
                is_write = False

                # see if we got a cache hit:
                # cache takes these args:
                # (mem_index, instruction_index, is_write, data_to_write)
                hit = p.check_cache(source_index, instruction_index, is_write, rn)

                # on hit, write to post_mem_buff and update pre_mem_buff:
                if(hit[0] == True):
                    print('hit!')
                    value = hit[1]

                    p.post_mem_buff[0] = value
                    p.post_mem_buff[1] = instruction_index

                    p.pre_mem_buff[0] = p.pre_mem_buff[1]
                    p.pre_mem_buff[1] = -1

    # end of method mem.

    # is mem op (helper for issue unit):
    def is_mem_op(self, instruction_index):
        if(d.opcode_string[instruction_index] == 'LDUR'
            or d.opcode_string[instruction_index] == 'STUR'):
            return True
        else:
            return False

    # issue unit:
    def issue(self):
        # curr is current pre-issue element:
        num_issued = 0
        curr = 0
        issue_me = True
        while(num_issued < 2 and p.pre_issue_buff[curr] >= 0 and curr < 4): # changed > to >= ...
            # get an instruction from pre-issue buffer starting with element 0:
            index = p.pre_issue_buff[curr]

            # make sure there is an instruction to execute:
            if(index == -1):
                break

            # structural hazard check pre-mem buffer:
            if(p.is_mem_op(index) and not -1 in p.pre_mem_buff):
                issue_me = False
                break

            # structural hazard check pre alu buff:
            if(not p.is_mem_op(index) and not -1 in p.pre_alu_buff):
                issue_me = False
                break

            # INSERT HAZARD CHECKING HERE !!

            # if instruction passes hazard checks then issue it and rearrange the 
            # pre issue buffer and look at the same slot again:
            if(issue_me):
                # debug print statement:
                print('issuing instruction:')
                p.print_instruction(index)

                num_issued += 1
                # copy instruction to appropriate buffer:
                # the assumption is that we will have a -1 in the right spot:
                if(p.is_mem_op(index)):
                    p.pre_mem_buff[p.pre_mem_buff.index(-1)] = index
                else:
                    p.pre_alu_buff[p.pre_alu_buff.index(-1)] = index

                # move the instruction in the pre issue buff down one level:
                p.pre_issue_buff[0] = p.pre_issue_buff[1]
                p.pre_issue_buff[1] = p.pre_issue_buff[2]
                p.pre_issue_buff[2] = p.pre_issue_buff[3]
                p.pre_issue_buff[3] = -1
                #p.num_in_pre_issue_buff -= 1
    # end of method issue.

    # helper method for fetch. Checks to see if all buffers are empty and
    # if so, returns True:
    def buffers_all_empty(self):
        i = 0
        while(i < 2):
            if(p.post_mem_buff[i] != -1 or p.post_alu_buff[i] != -1
                or p.pre_alu_buff[i] != -1 or p.pre_mem_buff[i] != -1
                or p.pre_issue_buff[i] != -1):
                return False
                i += 1
        while(i < 4):
            if(p.pre_issue_buff[i] != -1):
                return False
                i += 1
        return True
    # end of method buffers_all_empty.

    # helper for fetch. Counts how many slots in the 
    # pre issue buffer are free (returns int):
    def get_pib_count(self):
        pib_count = 0
        k = 0
        while(k < 4):
            if(p.pre_issue_buff[k] == -1):
                pib_count += 1
            k += 1
        return pib_count

    # debug method, prints an instruction:
    def print_instruction(self, i):
        print(d.instruction_spaced[i] + '\t' + d.opcode_string[i]
            + d.arg1_string[i] + d.arg2_string[i] + d.arg3_string[i] + '\n')

    # debug method, prints the pre-issue buffer:
    def print_pib(self):
        k = 0
        while(k < len(p.pre_issue_buff)):
            print('pre_issue_buff[' + str(k) + '] =\t' + str(p.pre_issue_buff[k]))
            k += 1
        print('')

    # Fetch Unit:
    def fetch(self):
        # check how full the pre issue buffer is:
        space = p.get_pib_count()

        # debug print:
        print('fetch index: ' + str(p.fetch_index))
        print('pib count = ' + str(space))
        print('pib contents:\n')
        p.print_pib()

        # if we reached the break, make sure to let anything left
        # in the buffers finish executing:
        #if(p.fetch_index >= d.break_index):
        if(d.opcode_string[p.fetch_index] == 'BREAK'):
            if(p.buffers_all_empty()):
                return False
            else:
                return True

        # if the pre issue buffer is full, we have to wait:
        if(space == 0):
            return True

        # grab a couple of instructions from memory:
        fetch_count = 0
        while(fetch_count < 2 and fetch_count <= space):
            instruction_index = p.fetch_index
            fetched = d.instruction[instruction_index]

            # check the cache for the fetch:
            hit = p.check_cache(-1, instruction_index, False, fetched)

            if(not hit):
                return True
            else: # we got a hit
                # debug print:
                print('hit on cycle ' + str(p.cycle) + ' with instruction:')
                p.print_instruction(instruction_index)

                # if the instruction is a branch:
                if(d.opcode_string[instruction_index] == 'B'
                    or d.opcode_string[instruction_index] == 'CBZ'
                    or d.opcode_string[instruction_index] == 'CBNZ'):
                    if(not p.buffers_all_empty()):
                        return True
                    else: # no problems in buffers so execute the branch:
                        p.fetch_index = d.print_indexes[p.fetch_index+1]
                        return True

                else: # not a branch:
                    # finally put the instruction in the pre_issue_buff:
                    if(p.pre_issue_buff[0] == -1):
                        p.pre_issue_buff[0] = instruction_index
                    elif(p.pre_issue_buff[1] == -1):
                        p.pre_issue_buff[1] = instruction_index
                    elif(p.pre_issue_buff[2] == -1):
                        p.pre_issue_buff[2] = instruction_index
                    elif(p.pre_issue_buff[3] == -1):
                        p.pre_issue_buff[3] = instruction_index
                    # increment the fetch index:
                    p.fetch_index += 1

            # increment fetch count:
            fetch_count += 1

        # if everything worked ok we need a True returned:
        return True

    # end of method fetch.

    # Runs the Pipeline:
    def run(self, outputFileName):
        # Registers:
        p.registers = []  # list of register contents (ints)
        register_index = 0
        while (register_index < 32):
            p.registers.append(0)
            register_index += 1

        # Buffers:
        p.post_mem_buff = [-1,-1] # value, instruction index
        p.post_alu_buff = [-1,-1] # value, instruction index
        p.pre_alu_buff = [-1,-1] # instruction index, instruction index
        p.pre_mem_buff = [-1,-1] # instruction index, instruction index
        p.pre_issue_buff = [-1,-1,-1,-1] # 4 instruction indexes

        # Cache Array: [valid, dirty, tag, data, data]
        p.cache_array = [[[0]*5, [0]*5],
                        [[0]*5, [0]*5],
                        [[0]*5, [0]*5],
                        [[0]*5, [0]*5]]

        # Cache LRU:
        p.lru = [0]*4

        # Miss List:
        p.miss_list = []

        # Cache tag and set masks:
        p.tag_mask = 4294967264
        p.set_mask = 24

        # Memory:
        if(len(d.memory_of_memory) > 0):
            p.memory = d.memory_of_memory[0]
            p.memory_pc = d.memory_pc_of_memory_pc[0]
        else:
            p.memory = []
            p.memory_pc = []

        # debug comment:
        print p.memory
        print p.memory_pc

        # Fetch:
        p.fetch_index = 0

        # Open File for writing:
        p.f = open(outputFileName + '_pipeline.txt', 'w')

        # Main pipeline loop:
        p.cycle = 1
        go = True
        while(go and p.cycle < 25):
            p.wb()
            p.alu()
            p.mem()
            p.issue()
            go = p.fetch()
            p.print_state()
            p.cycle += 1

        p.f.close()

    # end of method run.

#-----------------------end class Pipeline.------------------------------------

#-----------------------BEGIN PROGRAM:-----------------------------------------
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

    # Create Pipeline object:
    p = Pipeline(d)
    p.run(outputFileName)
#-----------------------EOF.---------------------------------------------------

