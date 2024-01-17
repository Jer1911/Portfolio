# Flask-Scaffold
A boiler-plate, get up and running quickly Flask application. I frequently use
this as a jumping-off point for apps I make for Jerhub. No bells and whistles
or kitchen sink included - this is meant to be modified and added to.

## Requirements:
Python version >= 3.10.5

## Configuration:
generate_secret.py can help you come up with a secret key if you aren't feeling
creative. You should set the key as an environment variable in whatever way
makes sense for your OS.
```
python -m venv venv
set FLASK_SECRET_KEY=<your-secret-key>
```

## Installation:
```
venv\Scripts\activate.bat
pip install -r requirements.txt
```

## Database Initialization:
```
flask db init
flask db migrate
flask db upgrade
python app.py
```

## Create an admin user (exit app first):
```
flask shell
>>> from create_admin import CreateAdmin
>>> admin = CreateAdmin('Bob', 'bob@example.com')
Here is your login info; please store it someplace safe.
Username: Bob
Email: bob@example.com
Password: super-secret-password <-- Write this down; you won't see it again.
>>> exit()
```
