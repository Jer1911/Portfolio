    def MEM_test(self):
        # loop through executed instructions until we find a LDUR:
        k = 0
        while (k < len(d.print_indexes)):
            i = d.print_indexes[k]
            if(d.opcode_string[i] == 'LDUR' or d.opcode_string[i] == 'STUR'):
                print('\n\n' + d.opcode_string[i] + ' found at index ' + str(k))
                if(p.pre_mem_buff[0] == -1):
                    p.pre_mem_buff[0] = i
                elif(p.pre_mem_buff[1] == -1):
                    p.pre_mem_buff[1] = i
                p.MEM()
                p.WB()
                p.print_registers()
            k += 1
        p.MEM()
        p.WB()
        p.print_registers()

    def ALU_test(self):
        k = 0
        while(k < len(d.print_indexes)):
            i = d.print_indexes[k]
            if(d.opcode_string[i] == 'ADDI' or d.opcode_string[i] == 'SUBI'
            or d.opcode_string[i] == 'ADD' or d.opcode_string[i] == 'SUB'
            or d.opcode_string[i] == 'AND' or d.opcode_string[i] == 'ORR'
            or d.opcode_string[i] == 'LSL' or d.opcode_string[i] == 'LSR'
            or d.opcode_string[i] == 'ASR' or d.opcode_string[i] == 'EOR'
            or d.opcode_string[i] == 'MOVZ' or d.opcode_string[i] == 'MOVK'):
                print('\n\n' + d.opcode_string[i] + ' found at index ' + str(k))
                if(p.pre_alu_buff[0] == -1):
                    p.pre_alu_buff[0] = i
                elif(p.pre_alu_buff[1] == -1):
                    p.pre_alu_buff[1] = i
                p.ALU()
                p.WB()
                p.print_registers()
            k += 1

    def WB_test(self):
        # loop through executed instructions until we find a LDUR:
        k = 0
        while (k < len(d.print_indexes)):
            i = d.print_indexes[k]
            if(d.opcode_string[i] == 'LDUR'):
                print('\n\nLDUR found at index ' + str(k))

                if(k != 0):
                    # change P registers list to appropriate D list:
                    p.registers = d.registers_per_instruction[k-1]

                # list of local registers for k:
                local_regs = d.registers_per_instruction[k]

                # value of register:
                value = local_regs[d.arg3[k]]

                # set post mem buffer values (0=value, 1=instruction index):
                p.post_mem_buff[0] = value
                p.post_mem_buff[1] = k

                p.WB()
                p.print_registers()

            # loop through instructions finding ALU post buffer things:
            elif(d.opcode_string[i] == 'ADDI' or d.opcode_string[i] == 'SUBI'
            or d.opcode_string[i] == 'ADD' or d.opcode_string[i] == 'SUB'
            or d.opcode_string[i] == 'AND' or d.opcode_string[i] == 'ORR'
            or d.opcode_string[i] == 'LSL' or d.opcode_string[i] == 'LSR'
            or d.opcode_string[i] == 'ASR' or d.opcode_string[i] == 'EOR'
            or d.opcode_string[i] == 'MOVZ' or d.opcode_string[i] == 'MOVK'):
                print('\n\n' + d.opcode_string[i] + ' found at index ' + str(k))

                if(k != 0):
                    # change P registers list to appropriate D list:
                    p.registers = d.registers_per_instruction[k-1]

                # list of local registers for k:
                local_regs = d.registers_per_instruction[k]

                # value of register:
                value = local_regs[d.arg3[k]]

                # set post mem buffer values (0=value, 1=instruction index):
                p.post_alu_buff[0] = value
                p.post_alu_buff[1] = k

                p.WB()
                p.print_registers()

            k += 1
    # end WB_test method.



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


