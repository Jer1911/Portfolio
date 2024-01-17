#------------------------------------------------------------------------------
# BANNERS:
#------------------------------------------------------------------------------

def show_welcome():
	banner = """
 _    _      _                            _                                
| |  | |    | |                          | |                               
| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___                          
| |/\| |/ _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \                         
\  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |                        
 \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/                         
                                                                           
                                                                           
          _                  _                       _       _             
         | |                | |                     | |     | |            
__      _| |__  ___  __ _   | |_ _ __ __ _ _ __  ___| | __ _| |_ ___  _ __ 
\ \ /\ / / '_ \/ __|/ _` |  | __| '__/ _` | '_ \/ __| |/ _` | __/ _ \| '__|
 \ V  V /| |_) \__ \ (_| |  | |_| | | (_| | | | \__ \ | (_| | || (_) | |   
  \_/\_/ |_.__/|___/\__, |   \__|_|  \__,_|_| |_|___/_|\__,_|\__\___/|_|   
                     __/ |_____                                            
                    |___/______|                                           
               _ _   _               _                                     
              (_) | | |             | |          _                         
__      ___ __ _| |_| |_ ___ _ __   | |__  _   _(_)                        
\ \ /\ / / '__| | __| __/ _ \ '_ \  | '_ \| | | |                          
 \ V  V /| |  | | |_| ||  __/ | | | | |_) | |_| |_                         
  \_/\_/ |_|  |_|\__|\__\___|_| |_| |_.__/ \__, (_)                        
                                            __/ |                          
                                           |___/                           
 _____ _       ______                          __ _                        
/  ___(_)      | ___ \                        / _(_)                       
\ `--. _ _ __  | |_/ /_ __ _____      ___ __ | |_ _ _ __   __ _  ___ _ __  
 `--. \ | '__| | ___ \ '__/ _ \ \ /\ / / '_ \|  _| | '_ \ / _` |/ _ \ '__| 
/\__/ / | |    | |_/ / | | (_) \ V  V /| | | | | | | | | | (_| |  __/ |    
\____/|_|_|    \____/|_|  \___/ \_/\_/ |_| |_|_| |_|_| |_|\__, |\___|_|    
                                                           __/ |           
                                                          |___/            
                                                                           
"""
	print(banner)

def show_goodbye():
	banner = """
 _   _                                 _                _             _ 
| | | |                               (_)              | |           | |
| |_| | __ ___   _____    __ _   _ __  _  ___ ___    __| | __ _ _   _| |
|  _  |/ _` \ \ / / _ \  / _` | | '_ \| |/ __/ _ \  / _` |/ _` | | | | |
| | | | (_| |\ V /  __/ | (_| | | | | | | (_|  __/ | (_| | (_| | |_| |_|
\_| |_/\__,_| \_/ \___|  \__,_| |_| |_|_|\___\___|  \__,_|\__,_|\__, (_)
                                                                 __/ |  
                                                                |___/   """
	print(banner)

#------------------------------------------------------------------------------
# MENUS:
#------------------------------------------------------------------------------

def show_main_menu():
	print('\n' + '-' * 80)
	print('Choose from the following options:')
	print('-' * 80 + '\n')
	print('(1) Items')
	print('(2) Skills')
	print('(x) Exit')

def show_skills_menu():
	print('\n' + '-' * 80)
	print('Choose from the following options:')
	print('-' * 80 + '\n')
	print('(1) Change a single skill')
	print('(2) Change all skills')
	print('(x) Exit')

def show_item_menu():
	print('\n' + '-' * 80)
	print('Choose from the following options:')
	print('-' * 80 + '\n')
	print('(1) Item IDs')
	print('(2) Item Flags')
	print('(x) Exit')

def show_item_flag_menu():
	print('\n' + '-' * 80)
	print('Choose from the following options:')
	print('-' * 80 + '\n')
	print('(1) Display a list of possible item_flag integer values')
	print('(2) Translate an item_flag integer value and display its corresponding label')
	print('(x) Exit')

def show_item_ids_menu():
	print('\n' + '-' * 80)
	print('Choose from the following options:')
	print('-' * 80 + '\n')
	print('(1) Search by index value')
	print('(2) Search by name')
	print('(x) Exit')

#------------------------------------------------------------------------------
# ITEM FLAG FUNCTIONS:
#------------------------------------------------------------------------------

def get_imod_strings():
	imod_strings = ['plain','cracked','rusty','bent','chipped','battered','poor',
						'crude','old','cheap','fine','well_made','sharp','balanced',
						'tempered','deadly','exquisite','masterwork','heavy','strong',
						'powerful','tattered','ragged','rough','sturdy','thick',
						'hardened','reinforced','superb','lordly','lame','swaybacked',
						'stubborn','timid','meek','spirited','champion','fresh',
						'day_old','two_day_old','smelling','rotten','large_bag']
	return imod_strings

def get_modifier(item_flag):
	modifier = (item_flag >> 24) & 0xFF
	return modifier

def get_short_hex(value):
	if(value == 0):
		short_hex = '0'
	else:
		short_hex = hex(value).lstrip('0x').rstrip('L')
	return short_hex

def hextend(short_hex):
	n = 6
	ch = '0' * n
	full_hex = short_hex + ch
	return full_hex

def set_modifier(index):
	short_hex = get_short_hex(index)
	full_hex = hextend(short_hex)
	modifier = int(full_hex,16)
	return modifier

def set_modifiers():
	modifiers = [0] * 43
	i = 0
	while(i < 43):
		modifiers[i] = set_modifier(i)
		i = i + 1
	return modifiers

def set_imodbits():
	imodbits = [0] * 43
	i = 0
	while(i < len(imodbits)):
		imodbits[i] = 1 << i
		i = i + 1
	return imodbits

#------------------------------------------------------------------------------
# ITEM FLAG ACTIONS:
#------------------------------------------------------------------------------

# Display a list of possible item_flag integer values:
def item_flag_action1():
	modifiers = set_modifiers()
	labels = get_imod_strings()
	print('\nlabel:\t\titem_flag:\n')
	i = 0
	while(i < len(modifiers)):
		print(labels[i].rjust(12) + str(modifiers[i]).rjust(12))
		i = i + 1

# Translate an item_flag integer value and display its corresponding label:
def item_flag_action2():
	item_flag = int(raw_input('\nEnter an item_flag integer: '))
	labels = get_imod_strings()
	index = get_modifier(item_flag)
	print('\nFound ' + str(item_flag) + ' at index ' + str(index))
	print('label is: ' + labels[index] + '\n')

#------------------------------------------------------------------------------
# SKILL FUNCTIONS:
#------------------------------------------------------------------------------

def get_skills():
	skills = [0] * 6
	skills[0] = int(raw_input('Enter skills(0):'))
	skills[1] = int(raw_input('Enter skills(1):'))
	skills[2] = int(raw_input('Enter skills(2):'))
	skills[3] = int(raw_input('Enter skills(3):'))
	skills[4] = int(raw_input('Enter skills(4):'))
	skills[5] = 0
	return skills

def get_skills_hex(skills):
	# make string array of hex values for skills(0 through 5):
	skills_hex = [''] * 6
	i = 0
	while i < 6:
		skills_hex[i] = str(hex(skills[i])).lstrip('0x').rstrip('L')		
		i = i + 1
	# make sure each hex string has 8 values:
	i = 0
	while i < 6:	
		if(len(skills_hex[i]) < 8):		
			tmp = 8 - len(skills_hex[i])
			ch = '0'
			j = 1
			while j < tmp:
				ch = '0' + ch
				j = j + 1
			new = ch + skills_hex[i]
			skills_hex[i] = new			
		i = i + 1
	return skills_hex

def get_skill_array(skills,skills_hex):
	first_line = skills_hex[0]
	second_line = skills_hex[1]
	third_line = skills_hex[2]
	fourth_line = skills_hex[3]
	fifth_line = skills_hex[4]
	
	# first line:
	trade = first_line[7]
	leadership = first_line[6]
	prisoner_management = first_line[5]
	persuasion = first_line[0]

	# second line:
	engineer = second_line[7]
	first_aid = second_line[6]
	surgery = second_line[5]
	wound_treatment = second_line[4]
	inventory_management = second_line[3]
	spotting = second_line[2]
	pathfinding = second_line[1]
	tactics = second_line[0]

	# third line:
	tracking = third_line[7]
	trainer = third_line[6]
	looting = third_line[1]
	horse_archery = third_line[0]

	# fourth line:
	riding = fourth_line[7]
	athletics = fourth_line[6]
	shield = fourth_line[5]
	weapon_master = fourth_line[4]

	# fifth line:
	power_draw = fifth_line[6]
	power_throw = fifth_line[5]
	power_strike = fifth_line[4]
	iron_flesh = fifth_line[3]

	# make an array in which to store them:
	skill_array = [0] * 24
	skill_array[0] = trade
	skill_array[1] = leadership
	skill_array[2] = prisoner_management
	skill_array[3] = persuasion
	skill_array[4] = engineer
	skill_array[5] = first_aid
	skill_array[6] = surgery
	skill_array[7] = wound_treatment
	skill_array[8] = inventory_management
	skill_array[9] = spotting
	skill_array[10] = pathfinding
	skill_array[11] = tactics
	skill_array[12] = tracking
	skill_array[13] = trainer
	skill_array[14] = looting
	skill_array[15] = horse_archery
	skill_array[16] = riding
	skill_array[17] = athletics
	skill_array[18] = shield
	skill_array[19] = weapon_master
	skill_array[20] = power_draw
	skill_array[21] = power_throw
	skill_array[22] = power_strike
	skill_array[23] = iron_flesh	
	return skill_array

def get_string_array():
	string_array = [''] * 24
	string_array[0] = 'trade'
	string_array[1] = 'leadership'
	string_array[2] = 'prisoner_management'
	string_array[3] = 'persuasion'
	string_array[4] = 'engineer'
	string_array[5] = 'first_aid'
	string_array[6] = 'surgery'
	string_array[7] = 'wound_treatment'
	string_array[8] = 'inventory_management'
	string_array[9] = 'spotting'
	string_array[10] = 'pathfinding'
	string_array[11] = 'tactics'
	string_array[12] = 'tracking'
	string_array[13] = 'trainer'
	string_array[14] = 'looting'
	string_array[15] = 'horse_archery'
	string_array[16] = 'riding'
	string_array[17] = 'athletics'
	string_array[18] = 'shield'
	string_array[19] = 'weapon_master'
	string_array[20] = 'power_draw'
	string_array[21] = 'power_throw'
	string_array[22] = 'power_strike'
	string_array[23] = 'iron_flesh'	
	return string_array

def show_skills(skill_array,string_array):
	print('\nCurrent Skills:\n')
	i = 0
	while(i < len(skill_array)):
		print(string_array[i] + ' = ' + skill_array[i])
		i = i + 1

def show_skill_menu():
	print('\n' + '-' * 80)
	print('Skill Converter Menu:')
	print('-' * 80)
	print('\n(1) trade\t(2) leadership\t(3) prisoner management')
	print('(4) persuation\t(5) engineer\t(6) first aid')
	print('(7) surgery\t(8) wound treatment\t(9) inventory management')
	print('(10) spotting\t(11) pathfinding\t(12) tactics')
	print('(13) tracking\t(14) trainer\t(15) looting')
	print('(16) horse archery\t(17) riding\t(18) athletics')
	print('(19) shield\t(20) weapon master\t(21) power draw')
	print('(22) power throw\t(23) power strike\t(24) iron flesh')
	print('\n' + '-' * 80)

def alter_skill(skill_array,choice,new_val,skills_hex):
	first_line = skills_hex[0]
	second_line = skills_hex[1]
	third_line = skills_hex[2]
	fourth_line = skills_hex[3]
	fifth_line = skills_hex[4]
	new_line = [''] * 8
	if(choice < 4): # first line choice (1,2,3,4)
		i = 0
		while(i < 8):
			new_line[i] = first_line[i]
			i = i + 1
		if(choice == 0): # trade
			new_line[7] = new_val
		elif(choice == 1): # leadership
			new_line[6] = new_val
		elif(choice == 2): # prisoner management
			new_line[5] = new_val
		elif(choice == 3): # persuasion
			new_line[0] = new_val
	elif(choice > 3 and choice < 12): # second line choice (5,6,7,8,9,10,11,12)
		i = 0
		while(i < 8):
			new_line[i] = second_line[i]
			i = i + 1
		if(choice == 4): # engineer
			new_line[7] = new_val
		elif(choice == 5): # first aid
			new_line[6] = new_val
		elif(choice == 6): # surgery
			new_line[5] = new_val
		elif(choice == 7): # wound treatment
			new_line[4] = new_val
		elif(choice == 8): # inventory management
			new_line[3] = new_val
		elif(choice == 9): # spotting
			new_line[2] = new_val
		elif(choice == 10): # pathfinding
			new_line[1] = new_val
		elif(choice == 11): # tactics
			new_line[0] = new_val
	elif(choice > 11 and choice < 16): # third line choice (13,14,15,16)
		i = 0
		while(i < 8):
			new_line[i] = third_line[i]
			i = i + 1
		if(choice == 12): # tracking
			new_line[7] = new_val
		elif(choice == 13): # trainer
			new_line[6] = new_val
		elif(choice == 14): # looting
			new_line[1] = new_val
		elif(choice == 15): # horse archery
			new_line[0] = new_val
	elif(choice > 15 and choice < 20): # fourth line choice (17,18,19,20)
		i = 0
		while(i < 8):
			new_line[i] = fourth_line[i]
			i = i + 1
		if(choice == 16): # riding
			new_line[7] = new_val
		elif(choice == 17): # athletics
			new_line[6] = new_val
		elif(choice == 18): # shield
			new_line[5] = new_val
		elif(choice == 19): # weapon master
			new_line[4] = new_val
	elif(choice > 19 and choice < 24): # fifth line choice (21,22,23,24)
		i = 0
		while(i < 8):
			new_line[i] = fifth_line[i]
			i = i + 1
		if(choice == 20): # power draw
			new_line[6] = new_val
		elif(choice == 21): # power throw
			new_line[5] = new_val
		elif(choice == 22): # power strike
			new_line[4] = new_val
		elif(choice == 23): # iron flesh
			new_line[3] = new_val
		
	# now concatinate the thing together into a single string:
	new_hex = new_line[0]+new_line[1]+new_line[2]+new_line[3]+new_line[4]+new_line[5]+new_line[6]+new_line[7]
	return new_hex

def get_answer(new_hex):
	answer = int(new_hex,16)
	return answer

def show_answer(choice,new_val,answer,string_array):
	print('\nYou wish to change ' + string_array[choice] + ' to ' + new_val)
	if(choice < 4):
		print('change skill(0) to: ' + str(answer))
	elif(choice > 3 and choice < 12):
		print('change skill(1) to: ' + str(answer))
	elif(choice > 11 and choice < 15):
		print('change skill(2) to: ' + str(answer))
	elif(choice > 15 and choice < 20):
		print('change skill(3) to: ' + str(answer))
	elif(choice > 19 and choice < 24):
		print('change skill(4) to: ' + str(answer))

def get_new_skill_array(string_array):
	print('\n' + '-' * 80)
	print('Enter your desired skillset:')
	print('-' * 80 + '\n')
	skill_array = [0] * 24
	i = 0
	while(i < 24):
		skill_array[i] = raw_input(string_array[i] + ': ')
		if(skill_array[i] == '10'):
			skill_array[i] = 'A'		
		i = i + 1
	return skill_array

def get_skills_test():
	skills = [0] * 6
	skills[0] = 0
	skills[1] = 0
	skills[2] = 0
	skills[3] = 0
	skills[4] = 0
	skills[5] = 0
	return skills

def skills_to_hex(skill_array,skills_hex,new_skill_array):
	new_hex_array = skills_hex
	choice = 0
	n = 0
	while(choice < 24):
		new_hex = alter_skill(skill_array,choice,new_skill_array[choice],new_hex_array)
		if(choice < 4):
			n = 0
		elif(choice > 3 and choice < 12):
			n = 1
		elif(choice > 11 and choice < 16):
			n = 2
		elif(choice > 15 and choice < 20):
			n = 3
		elif(choice > 19 and choice < 24):
			n = 4
		new_hex_array[n] = new_hex
		choice = choice + 1
	return new_hex_array

def hex_to_int(new_hex_array):
	new_int_array = [0] * 6
	i = 0
	while(i < 6):
		new_int_array[i] = get_answer(new_hex_array[i])
		i = i + 1
	return new_int_array

def show_new_int_array(new_int_array):
	print('\n' + '-' * 80)
	print('Here are your new values:')
	print('-' * 80 + '\n')
	i = 0
	while(i < 6):
		print('skills(' + str(i) + '): ' + str(new_int_array[i]))
		i = i + 1

#------------------------------------------------------------------------------
# SKILL ACTIONS:
#------------------------------------------------------------------------------

# Change a single skill:
def skill_action1():
	skills = get_skills()
	skills_hex = get_skills_hex(skills)	
	skill_array = get_skill_array(skills,skills_hex)
	string_array = get_string_array()
	show_skills(skill_array,string_array)
	show_skill_menu()
	choice = int(raw_input('\nSelect a skill to change: '))
	choice = choice - 1	
	new_val = raw_input('\nEnter a new value: ')	
	new_hex = alter_skill(skill_array,choice,new_val,skills_hex)	
	answer = get_answer(new_hex)	
	show_answer(choice,new_val,answer,string_array)

# Change all skills:
def skill_action2():
	string_array = get_string_array()
	new_skill_array = get_new_skill_array(string_array)
	skills = get_skills_test()
	skills_hex = get_skills_hex(skills)
	skill_array = get_skill_array(skills,skills_hex)
	new_hex_array = skills_to_hex(skill_array,skills_hex,new_skill_array)
	new_int_array = hex_to_int(new_hex_array)
	show_new_int_array(new_int_array)

#------------------------------------------------------------------------------
# ID_ITEMS FUNCTIONS:
#------------------------------------------------------------------------------

def read_id_items_file_to_list():
	infile = open('ID_items.py','r')
	id_items = [line.split(' ')[0] for line in infile]
	i = 0
	while(i < len(id_items)):
		id_items[i] = id_items[i][4:]
		i = i + 1
	infile.close()
	return id_items

def show_id_items_list(id_items):
	for item in id_items:
		print(item)

def identify_item_by_code(id_items):
	code = int(raw_input('\nEnter item code: '))
	item = id_items[code]
	print('\ncode ' + str(code) + ' is ' + item +'\n')
	return item

def search_id_items(id_items):
	search_term = raw_input('\nEnter a search term: ')
	matches = [i for i in id_items if search_term in i]
	print('\nYour search resulted in the following matches:\n')
	print('Options:\tItem:\n')
	i = 0
	while(i < len(matches)):
		print('(' + str(i+1) + ') ' + matches[i].rjust(40))
		i = i + 1
	print('\nWhich one do you mean?\n')
	choice_index = int(raw_input('Enter a number: '))
	choice = matches[choice_index-1]
	true_match = str(id_items.index(choice))
	print('\nThe item ID matching your search is: ' + true_match)
	return int(true_match)

#------------------------------------------------------------------------------
# ID_ITEMS ACTIONS:
#------------------------------------------------------------------------------

def id_items_action1():
	id_items = read_id_items_file_to_list()
	item = identify_item_by_code(id_items)

def id_items_action2():
	id_items = read_id_items_file_to_list()
	index = search_id_items(id_items)

#------------------------------------------------------------------------------
# MAIN:
#------------------------------------------------------------------------------

def main():
	show_welcome()
	choice = '0'
	while(choice != 'x'):
		show_main_menu()
		choice = raw_input('\nChoose an option: ')
		if(choice == '1'): #Items
			show_item_menu()
			choice = raw_input('\nChoose an option: ')
			if(choice == '1'): #item_IDs
				show_item_ids_menu()
				choice = raw_input('\nChoose an option: ')
				if(choice == '1'): #index search
					id_items_action1()
				elif(choice == '2'): # name search
					id_items_action2()
			elif(choice == '2'): #item flags
				show_item_flag_menu()
				choice = raw_input('\nChoose an option: ')
				if(choice == '1'): #list flags
					item_flag_action1()
				elif(choice == '2'): #translate flags
					item_flag_action2()
		elif(choice == '2'): #Skills
			show_skills_menu()
			choice = raw_input('\nChoose an option: ')
			if(choice == '1'): #single skill
				skill_action1()
			elif(choice == '2'): #all skills
				skill_action2()
	show_goodbye()

main()
