from flask import Flask, render_template
from flask_socketio import SocketIO


app = Flask(__name__)
app.config['SECRET_KEY'] = 'super secret'
socketio = SocketIO(app)


@app.get('/')
def index():
    return render_template('index.html')


@app.get('/welcome/<name>')
def welcome(name):
    return render_template('welcome.html', name=name)


@socketio.on('connect')
def test_connect():
    print('SocketIO connection established')


@socketio.on('disconnect')
def test_disconnect():
    print('SocketIO disconnected')


@socketio.on('message')
def handle_message(data):
   print(f'recieved message: {data}')


if __name__ == '__main__':
    socketio.run(app)

