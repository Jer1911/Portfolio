import boto3

# Initialize a dynamodb for interaction:
def init_session():
    session = boto3.session.Session(region_name='us-east-2')
    dynamodb = session.resource('dynamodb')
    return dynamodb

# Create a new table:
def make_new_table(table_name, keys, attributes, throughput):
    dynamodb = init_session()
    table = dynamodb.create_table(TableName=table_name,
        KeySchema=keys, AttributeDefinitions=attributes,
        ProvisionedThroughput=throughput)
    table.meta.client.get_waiter('table_exists').wait(TableName=table_name)

# Initialize an existing table for interaction:
def init_table(table_name):
    dynamodb = init_session()
    table = dynamodb.Table(table_name)
    return table

# Get all items:
def get_items(table_name):
    table = init_table(table_name)
    response = table.scan()
    items = response['Items']
    return items

# add an item:
def add_item(table_name, item):
    table = init_table(table_name)
    table.put_item(Item=item)

# Parse list of items for prettier output:
def parse_items(table_name):
    items = get_items(table_name)
    parsed_items = ""
    for i in items:
        parsed_items += (str(i) + '\n')
    return parsed_items

