"use strict";

var boardLen = 500;
var canvas, ctx;
var timerId;

function getNextPointSerialize(n, posX, posY, lastPosX, lastPosY) {
    return Module.ccall('getNextPointSerialize', 'number', ['number', 'number', 'number', 'number', 'number'], [n, posX, posY, lastPosX, lastPosY]);
}

function drawPoint(posX, posY, step) {
    ctx.beginPath();
    ctx.arc(step * posX, step * posY, 3, 0, 360, false);
    ctx.fillStyle = 'royalblue';
    ctx.fill();
    ctx.closePath();
}

function drawLine(posX, posY, nextPosX, nextPosY, step, color) {
    ctx.beginPath();
    ctx.moveTo(step * posX, step * posY);
    ctx.lineTo(step * nextPosX, step * nextPosY);
    ctx.strokeStyle = color;
    ctx.stroke();
    ctx.closePath();
}

document.addEventListener('DOMContentLoaded', function() {
    canvas = document.getElementById('canvas');
    ctx = canvas.getContext('2d');
    ctx.lineWidth = 1;
    drawEmptyBoard();
});

function drawEmptyBoard() {
    var bs = document.getElementById('boardSize');
    if (bs.validity.valid) {
        // Clear original board
        ctx.fillStyle = 'white';
        ctx.fillRect(0, 0, canvas.width, canvas.height);

        // Draw new board
        var n = bs.value, step = boardLen / (n - 1);
        for (var i = 0; i < n; i++) {
            drawLine(i, 0, i, n, step, 'black');  // Draw a horizontal line from (i, 0) to (i, n)
            drawLine(0, i, n, i, step, 'black');  // Draw a vertical line from (0, i) to (n, i)
        }
    }
}

/// @param n board size
/// @param ms sleep time after drawing a line, in ms
function draw(n, ms) {
    var step = boardLen / (n - 1);
    var posX = 2, posY = 0, lastPosX = 0, lastPosY = 1;

    function drawInner() {
        var nextPos = getNextPointSerialize(n, posX, posY, lastPosX, lastPosY),
            nextPosX = nextPos / n | 0, nextPosY = nextPos % n;

        drawPoint(posX, posY, step);
        drawLine(posX, posY, nextPosX, nextPosY, step, 'deeppink');

        if (nextPosX == 2 && nextPosY == 0) /* the Knight has returned to the beginning point */ {
            stopDraw();  // Clear timer, for the case ms != 0
            return true;  // Indicate that the drawing has finished, for the case ms == 0
        } else {
            lastPosX = posX;
            lastPosY = posY;
            posX = nextPosX;
            posY = nextPosY;
            return false;
        }
    }

    if (ms == 0)
        while (!drawInner())
            continue;
    else
        timerId = setInterval(drawInner, ms);
}

function startDraw() {
    var bs = document.getElementById('boardSize'), st = document.getElementById('strokeTime');
    if (bs.validity.valid && st.validity.valid)
        draw(parseInt(bs.value), parseInt(st.value));
}

function stopDraw() {
    if (timerId) {
        clearInterval(timerId);
        timerId = null;
    }
}
