from flask import Flask, render_template
from flask_socketio import SocketIO


app = Flask(__name__)
app.config['SECRET_KEY'] = 'super secret'
socketio = SocketIO(app)


@app.get('/')
def index():
    return render_template('index.html')


@socketio.on('connect')
def test_connect():
    print('SocketIO connection established')


@socketio.on('disconnect')
def test_disconnect():
    print('SocketIO disconnected')


@socketio.on('message')
def handle_message(data):
   print(f'Received message: {data}')


@socketio.on('controls')
def handle_controls(command):
    """
    0000
    WSAD
    W: forward           8
    A: backward          4
    S: left              2
    D: right             1
    """
    status = ''
    if command >= 8:
        status += 'MOVING FORWARD'
        if command == 10:
            # left
            status += ' LEFT'
        elif command == 9:
            # right
            status += ' RIGHT'
        else:
            # just go forward
            pass
    elif command >= 4:
        # backward
        status += 'MOVING BACKWARD'
        if command == 6:
            # left
            status += ' LEFT'
        elif command == 5:
            # right
            status += ' RIGHT'
        else:
            # just reverse
            pass
    elif command == 2:
        # left
        status = 'TURNING LEFT'
    elif command == 1:
        # right
        status = 'TURNING RIGHT'
    else:
        status = 'STOPPING'
    print(status)
    return status


if __name__ == '__main__':
    socketio.run(app)
