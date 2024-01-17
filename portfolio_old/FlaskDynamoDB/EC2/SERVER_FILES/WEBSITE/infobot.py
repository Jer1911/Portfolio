from flask import Flask, render_template
app = Flask(__name__)

@app.route("/")
@app.route("/index")
def index():
    title = 'Home'
    img_src = '/static/images/kim_cardassian.jpg'
    img_alt='Kim Cardassian'
    img_style='width:331px;height:422px;'
    m1 = '--Welcome to Infobot--'
    m2 = 'brought to you by:'
    m3 = 'Keeping up with the Cardassians'

    return render_template('index.html', title=title, img_src=img_src,
            img_alt=img_alt, img_style=img_style, m1=m1, m2=m2, m3=m3)

@app.route("/about")
def about():
    title = 'About'
    img_src = '/static/images/kim_cardassian.jpg'
    img_alt='Kim Cardassian'
    img_style='width:331px;height:422px;'
    m1 = '--Welcome to Infobot--'
    m2 = 'brought to you by:'
    m3 = 'Keeping up with the Cardassians'
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

    return render_template('about.html', title=title, img_src=img_src,
            img_alt=img_alt, img_style=img_style, m1=m1, m2=m2, m3=m3, m4=m4)

if __name__ == "__main__":
    app.run(host='0.0.0.0')

