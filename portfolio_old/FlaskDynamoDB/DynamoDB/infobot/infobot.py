from flask import Flask, render_template
import aws_controller
import splash

app = Flask(__name__)

@app.route("/")
@app.route("/index")
def index():
    title = 'Home'
    s = splash.get_splash()
    return render_template('index.html', title=title, img_src=s[0],
            img_alt=s[1], img_style=s[2], m1=s[3], m2=s[4], m3=s[5])

@app.route("/about")
def about():
    title = 'About'
    s = splash.get_splash()
    m4 = ('-' * 80 + '\n'
            + 'This web-app was created with Python Flask,\n'
            + 'and deployed on AWS EC2 Ubuntu 18.04 server instance.\n'
            + 'Its purpose is to dynamically display information\n'
            + 'from a database populated by web-spiders.\n'
            + '-' * 80 + '\n'
            + 'Features coming in Sprint 2:\n'
            + ' - web spider\n'
            + ' - database\n')
    m4 = m4.split('\n')

    return render_template('about.html', title=title, img_src=s[0],
            img_alt=s[1], img_style=s[2], m1=s[3], m2=s[4], m3=s[5], m4=m4)

@app.route("/db_test")
def db_test():
    title = 'DBTest'
    s = splash.get_splash()
    return render_template('db_test.html', title=title, img_src=s[0],
            img_alt=s[1], img_style=s[2], m1=s[3], m2=s[4], m3=s[5])

@app.route("/music")
def music():
    title = 'Music'
    s = splash.get_splash()
    music = str(aws_controller.parse_items('Music'))
    m4 = ('Getting Music database info:\n' + music)
    m4 = m4.split('\n')

    return render_template('music.html', title=title, img_src=s[0],
            img_alt=s[1], img_style=s[2], m1=s[3], m2=s[4], m3=s[5], m4=m4)

@app.route("/books")
def books():
    title = 'Books'
    s = splash.get_splash()
    books = str(aws_controller.parse_items('Books'))
    m4 = ('Getting Books database info:\n' + books)
    m4 = m4.split('\n')

    return render_template('books.html', title=title, img_src=s[0],
            img_alt=s[1], img_style=s[2], m1=s[3], m2=s[4], m3=s[5], m4=m4)

if __name__ == "__main__":
    app.run(host='0.0.0.0')

