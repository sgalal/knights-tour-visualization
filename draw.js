/// @param n board size
/// @param ns sleep time after drawing a line, in nanosecond
function draw(n, ns)
{
    var c = document.getElementById('canvas');
    var ctx = c.getContext('2d');

    ctx.lineWidth = 1;
    var x, y;
    var len = 500;
    var edge = len/n;

    async function doDraw(n, pos, lastPos)
    {
        var nextPos = Module.nextPoint(n, pos, lastPos);
        await new Promise((resolve) =>
        {
            setTimeout(resolve, ns);
        });

        var beginX = edge*Module.getFirst(pos) + edge/2;
        var beginY = edge*Module.getSecond(pos) + edge/2;
        var endX = edge*Module.getFirst(nextPos) + edge/2;
        var endY = edge*Module.getSecond(nextPos) + edge/2;

        ctx.beginPath();
        ctx.moveTo(beginX, beginY);
        ctx.lineTo(endX, endY);
        ctx.strokeStyle = 'red';
        ctx.lineWidth = 1;
        ctx.stroke();
        if(Module.getFirst(nextPos) != 2 || Module.getSecond(nextPos) != 0)
            doDraw(n, nextPos, pos);
        ctx.closePath();

        ctx.beginPath();
        ctx.arc(endX, endY, 2, 0, 360, false);
        ctx.fillStyle = 'blue';
        ctx.fill();
        ctx.closePath();
    }

    doDraw(n, Module.make_point(2, 0), Module.make_point(0, 1));
}
