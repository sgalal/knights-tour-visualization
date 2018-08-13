/// Draw the chess board.
/// @param n board size
function drawBoard(n) {
    var c = document.getElementById('canvas');
    var ctx = c.getContext('2d');

    ctx.beginPath();
    ctx.fillStyle = '#ffffff';
    ctx.fillRect(0, 0, c.width, c.height);  
    ctx.closePath();

    ctx.lineWidth = 1;
    var x, y;
    var len = 500;
    var edge = len/(n-1);

    x = y = 0;
    for (var i = 0; i < n; i++) {
        ctx.beginPath();
        ctx.strokeStyle = 'black';
        ctx.moveTo(x,y);
        ctx.lineTo(len,y);
        ctx.stroke();
        ctx.closePath();
        y += edge;
    }
    x = y = 0;
    for (var i = 0; i < n; i++) {
        ctx.beginPath();
        ctx.strokeStyle = 'black';
        ctx.moveTo(x,y);
        ctx.lineTo(x,len);
        ctx.stroke();
        ctx.closePath();
        x += edge;
    }
}

/// @param n board size
/// @param ms sleep time after drawing a line, in ms
function draw(n, ms) {
    var c = document.getElementById('canvas');
    var ctx = c.getContext('2d');

    ctx.lineWidth = 1;
    var len = 500;
    var edge = len / (n - 1);
    
    var posX = 2;
    var posY = 0;
    var lastPosX = 0;
    var lastPosY = 1;

    (function() {
        var nextPos = Module.ccall('getNextPointSerialize', 'number', ['number', 'number', 'number', 'number', 'number'], [n, posX, posY, lastPosX, lastPosY]);

        var nextPosX = parseInt(nextPos / n);
        var nextPosY = nextPos % n;

        var beginX = edge * posX;
        var beginY = edge * posY;
        var endX = edge * nextPosX;
        var endY = edge * nextPosY;

        ctx.beginPath();
        ctx.moveTo(beginX, beginY);
        ctx.lineTo(endX, endY);
        ctx.strokeStyle = 'red';
        ctx.lineWidth = 1;
        ctx.stroke();
        ctx.closePath();

        ctx.beginPath();
        ctx.arc(endX, endY, 3, 0, 360, false);
        ctx.fillStyle = 'blue';
        ctx.fill();
        ctx.closePath();

        if (nextPosX != 2 || nextPosY != 0) {
            lastPosX = posX;
            lastPosY = posY;
            posX = nextPosX;
            posY = nextPosY;
            if (ms > 0)
                setTimeout(arguments.callee, ms);
            else
                arguments.callee();
        }
    })();
}

function doCalc() {
    var n = 2 * parseInt(document.getElementById('sizeparam').value);
    if (n < 6)
        n = 6;
    document.getElementById('sizeres').innerText = n + ' * ' + n;
    drawBoard(n);
}

function drawWrapper() {
    var n = 2 * parseInt(document.getElementById('sizeparam').value);
    if (n < 6)
        n = 6;
    draw(n, parseInt(document.getElementById('stroketime').value));
}

function disableEnter(e) {
    var et = e || window.event;
    var keycode = et.charCode || et.keyCode;
    if (keycode == 13) {
        if (window.event)
            window.event.returnValue = false;
        else
            e.preventDefault();  // For Firefox
    }
}
