async function waitAndDo(ms,f){
  await new Promise((resolve)=>{
    setTimeout(resolve,ms);
  });
  f();
}
function draw(n)  /* 棋盘 size */
{
  var c=document.getElementById('canvas');
  var ctx=c.getContext('2d');
  ctx.clearRect(0,0,c.width,c.height);

  ctx.lineWidth=1;

  var x,y;
  var len=500;
  var edge=len/n;

  /* Draw board */

  x=y=0;
  for(var i=0;i<=n;i++)
  {
    ctx.moveTo(x,y);
    ctx.lineTo(len,y);
    ctx.stroke();
    y+=edge;
  }
  x=y=0;
  for(var i=0;i<=n;i++)
  {
    ctx.moveTo(x,y);
    ctx.lineTo(x,len);
    ctx.stroke();
    x+=edge;
  }

  function doDraw(n,pos,lastPos){
    var nextPos=Module.nextPoint(n,pos,lastPos);
    if(nextPos!=Module.make_point(2,0)){
      waitAndDo(100,function(){

        ctx.beginPath();
        ctx.moveTo(edge*Module.getFirst(pos)+edge/2,edge*Module.getSecond(pos)+edge/2);
        ctx.lineTo(edge*Module.getFirst(nextPos)+edge/2,edge*Module.getSecond(nextPos)+edge/2);
        ctx.strokeStyle="#bf0628";
        ctx.lineWidth=2;
        ctx.stroke();
      
        doDraw(n,nextPos,pos);
      });
    }
  }
  
  doDraw(n,Module.make_point(2,0),Module.make_point(0,1));
}
