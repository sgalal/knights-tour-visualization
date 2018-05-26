function drawBoard(n)
{
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
    for(var i = 0; i < n; i++)
    {
        ctx.beginPath();
        ctx.strokeStyle = 'black';
        ctx.moveTo(x,y);
        ctx.lineTo(len,y);
        ctx.stroke();
        ctx.closePath();
        y += edge;
    }
    x = y = 0;
    for(var i = 0; i < n; i++)
    {
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
/// @param ns sleep time after drawing a line, in nanosecond
function draw(n, ns)
{
    var c = document.getElementById('canvas');
    var ctx = c.getContext('2d');

    ctx.lineWidth = 1;
    var x, y;
    var len = 500;
    var edge = len/(n-1);

    function doDraw(n, posX, posY, lastPosX, lastPosY)
    {
        sleepDo(ns, function()
        {
            var nextPos = Module.nextPoint(n, posX, posY, lastPosX, lastPosY);

            var nextPosX = Module.getFirst(nextPos);
            var nextPosY = Module.getSecond(nextPos);

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
            if(nextPosX != 2 || nextPosY != 0)
                doDraw(n, nextPosX, nextPosY, posX, posY);
            ctx.closePath();

            ctx.beginPath();
            ctx.arc(endX, endY, 3, 0, 360, false);
            ctx.fillStyle = 'blue';
            ctx.fill();
            ctx.closePath();
        });
    }

    doDraw(n, 2, 0, 0, 1);
}

function doCalc()
{
    var i = 2 * parseInt(document.getElementById('sizeparam').value);
    document.getElementById('sizeres').value = i + ' * ' + i;
    drawBoard(i);
}

function drawWrapper()
{
    draw(2 * parseInt(document.getElementById('sizeparam').value), parseInt(document.getElementById('stroketime').value));
}

function checkEnter(e)
{
    var et = e || window.event;
    var keycode = et.charCode || et.keyCode;
    if(keycode == 13)
    {
        if(window.event)
        {
            window.event.returnValue = false;
            drawWrapper();
        }
        else
            e.preventDefault();  // For Firefox
    }
}
