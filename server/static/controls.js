const forwardControl = document.getElementById('forwardControl');
const leftControl = document.getElementById('leftControl');
const backControl = document.getElementById('backControl');
const rightControl = document.getElementById('rightControl');

let socketConnected = false;
let dataState = 0;
let oldDataState = 0;

let forwardPress = false;
let leftPress = false;
let backPress = false;
let rightPress = false;

let socket = io();
socket.on('connect', () => {
    console.log('SocketIO connection established');
    socketConnected = true;
    socket.emit('message', 'Confirmed connection');

    socket.on('disconnect', () => {
        console.log('SocketIO disconnected');
        socketConnected = false;
        socket.disconnect();
    });
});

function keyDown(event) {
    if (!socketConnected) {
        console.log('Not connected');
        document.removeEventListener('keydown', keyDown);
        document.removeEventListener('keyup', keyUp);
        return;
    }
    switch (event.keyCode) {
        case 38:
        case 87:
            if (!forwardPress) {
                forwardPress = true;
                dataState += 8;
                forwardControl.style.color = '#0095CB';
            }
            break;
        case 40:
        case 83:
            if (!backPress) {
                backPress = true;
                dataState += 4;
                backControl.style.color = '#0095CB';
            }
            break;
        case 37:
        case 65:
            if (!leftPress) {
                leftPress = true;
                dataState += 2;
                leftControl.style.color = '#0095CB';
            }
            break;
        case 39:
        case 68:
            if (!rightPress) {
                rightPress = true;
                dataState += 1;
                rightControl.style.color = '#0095CB';
            }
            break;
    }
    // send data if changed
    if (dataState !== oldDataState) {
        console.log(dataState);
        socket.emit('controls', dataState);
        oldDataState = dataState;
    }
}

function keyUp(event) {
    if (!socketConnected) {
        console.log('Not connected');
        document.removeEventListener('keydown', keyDown);
        document.removeEventListener('keyup', keyUp);
        return;
    }
    switch (event.keyCode) {
        case 38:
        case 87:
            if (forwardPress) {
                forwardPress = false;
                dataState -= 8;
                forwardControl.style.color = '';
            }
            break
        case 40:
        case 83:
            if (backPress) {
                backPress = false;
                dataState -= 4;
                backControl.style.color = '';
            }
            break;
        case 37:
        case 65:
            if (leftPress) {
                leftPress = false;
                dataState -= 2;
                leftControl.style.color = '';
            }
            break;
        case 39:
        case 68:
            if (rightPress) {
                rightPress = false;
                dataState -= 1;
                rightControl.style.color = '';
            }
            break;
    }
    // send data if changed
    if (dataState !== oldDataState) {
        console.log(dataState);
        socket.emit('controls', dataState);
        oldDataState = dataState;
    }
}

document.addEventListener('keydown', keyDown);
document.addEventListener('keyup', keyUp);
