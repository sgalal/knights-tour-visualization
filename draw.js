/// @param n board size
/// @param ns sleep time after drawing a line, in nanosecond
function draw(n, ns)
{
    var c = document.getElementById('canvas');
    var ctx = c.getContext('2d');
    c.height = c.height;  // Resize to force clear the canvas

    ctx.lineWidth = 1;
    var x, y;
    var len = 500;
    var edge = len/n;

    /* Draw board */

    x = y = 0;
    for(var i = 0; i <= n; i++)
    {
        ctx.moveTo(x,y);
        ctx.lineTo(len,y);
        ctx.stroke();
        y += edge;
    }
    x = y = 0;
    for(var i = 0; i <= n; i++)
    {
        ctx.moveTo(x,y);
        ctx.lineTo(x,len);
        ctx.stroke();
        x += edge;
    }

    async function doDraw(n, pos, lastPos)
    {
        var nextPos = Module.nextPoint(n, pos, lastPos);
        await new Promise((resolve) =>
        {
            setTimeout(resolve, ns);
        });
        ctx.beginPath();
        ctx.moveTo(edge*Module.getFirst(pos) + edge/2, edge*Module.getSecond(pos) + edge/2);
        ctx.lineTo(edge*Module.getFirst(nextPos) + edge/2, edge*Module.getSecond(nextPos) + edge/2);
        ctx.strokeStyle = '#bf0628';
        ctx.lineWidth = 2;
        ctx.stroke();
        if(Module.getFirst(nextPos) != 2 || Module.getSecond(nextPos) != 0)
            doDraw(n, nextPos, pos);
    }

    doDraw(n, Module.make_point(2, 0), Module.make_point(0, 1));
}
