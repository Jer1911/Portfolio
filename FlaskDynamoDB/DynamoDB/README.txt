helpful links:
https://boto3.amazonaws.com/v1/documentation/api/latest/index.html
https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/DynamoDBLocal.html

+----------------------------------------------------------------------------+
+ SETUP PROCEDURES: --WORK IN PROGRESS-- you have been warned!               +
+----------------------------------------------------------------------------+
-- Get aws command line interface: --
curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
unzip awscliv2.zip
sudo ./aws/install

aws configure

(here you must enter your access key ID and secrect key, default region, and
output format. Default region for our server is: us-east-2. Your setup on
local machine may be different because you will need to setup a local
installation of DynamoDB for testing your code. Other option is make an aws
account, up to you how you want to do it.)

-- Next, make file create-table.json 

-- Use aws command line interface to create your new table:
aws dynamodb create-table --cli-input-json file://create-table.json

-- Confirm your new db exists:
aws dynamodb list-tables

-- Make a virtual environment to work in:
python3 -m venv infobotenv
source infobotenv/bin/activate

-- Install boto3:
pip install boto3

-- Make file aws_controller.py . It will contain methods to interact with
   tables in the database.

-- Make file db_test.py . It will be where you can test out your methods.

-- So far, I have made one table named 'Music', and two methods:
    get_items
    add_item

-- I will be making other methods such as batch writing items, once I have
   more time.
