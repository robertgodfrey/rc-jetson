from flask import render_template

from server import app

@app.get('/')
def index():
    return render_template('index.html')

@app.get('/welcome/<name>')
def welcome(name):
    return render_template('welcome.html', name=name)

