import aws_controller

def test_make_new_table(table_name, keys, attributes, throughput):
	aws_controller.make_new_table(table_name, keys, attributes, throughput)

def test_get_items(table_name):
	# call our aws controller and cast as string:
	items = str(aws_controller.get_items(table_name))
	return items

# -- needs a new function to get the key schema from table !!
def test_add_item(table_name, HASH, RANGE, arg1, arg2):
	# make a dict which corresponds to the db fields:
	item = {HASH:arg1, RANGE:arg2}
	# call our aws controller:
	aws_controller.add_item(table_name, item)

def test_parse_items(table_name):
	items = aws_controller.get_items(table_name)
	parsed_items = ""
	for i in items:
		parsed_items += (str(i) + '\n')
	print(parsed_items)

def main():
	# -- Test making a new table: (This pauses on execution, waits for
	#    operation to complete. This is normal.)
	#table_name = 'Books'
	#keys = [{'AttributeName':'Author','KeyType':'HASH'},
	#		{'AttributeName':'Title','KeyType':'RANGE'}]
	#attributes = [{'AttributeName':'Author','AttributeType':'S'},
	#		{'AttributeName':'Title','AttributeType':'S'}]
	#throughput = {'ReadCapacityUnits':1,'WriteCapacityUnits':1}
	#test_make_new_table(table_name, keys, attributes, throughput)

	# -- Test adding a single item:
	#table_name = 'Books'
	#HASH = 'Author'
	#RANGE = 'Title'
	#arg1 = 'Orson Scott Card'
	#arg2 = 'Treason'
	#test_add_item(table_name, HASH, RANGE, arg1, arg2)

	# -- Test scanning a table for items:
	#table_name = 'Books'
	#items = test_get_items(table_name)
	#print('Here are the database items:\n' + items)

	# -- Test parse items for prettier output:
	table_name = 'Music'
	parsed_items = aws_controller.parse_items(table_name)
	print(parsed_items)
	#test_parse_items(table_name)

main()


'''
Getting Music database info:

[{'Artist': 'J.S. Bach', 'SongTitle': 'Passacaglia and Fugue in G minor'}, {'Artist': 'Megadeth', 'SongTitle': 'Symphony of Destruction'}, {'Artist': 'Slayer', 'SongTitle': 'Raining Blood'}]

Getting Books database info:

[{'Author': 'Orson Scott Card', 'Title': 'Treason'}]
'''
