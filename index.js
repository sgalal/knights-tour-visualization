"use strict";

var boardSize = 500;
var timerId;

window.onload = handleResize;

/// Draw the chess board.
/// @param n board size
function drawBoard(n) {
    var c = document.getElementById("canvas");
    var ctx = c.getContext("2d");
    ctx.beginPath();
    ctx.fillStyle = "#ffffff";
    ctx.fillRect(0, 0, c.width, c.height);  
    ctx.closePath();

    ctx.lineWidth = 1;
    var x, y;
    var unitLen = boardSize/(n-1);

    x = y = 0;
    for (var i = 0; i < n; i++) {
        ctx.beginPath();
        ctx.strokeStyle = "black";
        ctx.moveTo(x,y);
        ctx.lineTo(boardSize,y);
        ctx.stroke();
        ctx.closePath();
        y += unitLen;
    }
    x = y = 0;
    for (var i = 0; i < n; i++) {
        ctx.beginPath();
        ctx.strokeStyle = "black";
        ctx.moveTo(x,y);
        ctx.lineTo(x,boardSize);
        ctx.stroke();
        ctx.closePath();
        x += unitLen;
    }
}

function drawPointOnCanvas(endX, endY) {
    var c = document.getElementById("canvas");
    var ctx = c.getContext("2d");
    ctx.beginPath();
    ctx.arc(endX, endY, 3, 0, 360, false);
    ctx.fillStyle = "blue";
    ctx.fill();
    ctx.closePath();
}

function drawLineOnCanvas(beginX, beginY, endX, endY) {
    var c = document.getElementById("canvas");
    var ctx = c.getContext("2d");
    ctx.beginPath();
    ctx.moveTo(beginX, beginY);
    ctx.lineTo(endX, endY);
    ctx.strokeStyle = "red";
    ctx.lineWidth = 1;
    ctx.stroke();
    ctx.closePath();
}

/// @param n board size
/// @param ms sleep time after drawing a line, in ms
function draw(n, ms) {
    var unitLen = boardSize / (n - 1);
    var posX = 2, posY = 0,
        lastPosX = 0, lastPosY = 1;

    function drawInner() {
        var nextPos = Module.ccall("getNextPointSerialize", "number", ["number", "number", "number", "number", "number"], [n, posX, posY, lastPosX, lastPosY]);
        var nextPosX = parseInt(nextPos / n), nextPosY = nextPos % n;
        var beginX = unitLen * posX, beginY = unitLen * posY,
            endX = unitLen * nextPosX, endY = unitLen * nextPosY;

        drawPointOnCanvas(beginX, beginY);
        drawLineOnCanvas(beginX, beginY, endX, endY);

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

function handleResize() {
    var n = parseInt(document.getElementById("boardSize").value);
    if (n < 6)
        n = 6;
    drawBoard(n);
}

function startDraw() {
    var inputBoardSize = parseInt(document.getElementById("boardSize").value),
        realBoardSize = inputBoardSize < 6 ? 6 : inputBoardSize,
        strokeTime = parseInt(document.getElementById("strokeTime").value);
    draw(realBoardSize, strokeTime);
}

function stopDraw() {
    if (timerId) {
        clearInterval(timerId);
        timerId = null;
    }
}
