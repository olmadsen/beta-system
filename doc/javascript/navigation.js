var StartVisible = 0;
var DrawDelay    = 500;
var PullStepTime = 15;
var DrawStepTime = 30;
var rightboundary = -20;
var leftboundary = -100;

function on_load() {
  window.status='Type ? for Help';
  return true;
}

function AdjustSideBar() {
  if (document.layers) { 
     document.layers.SideBar.top = window.pageYOffset+37; 
  } else if (document.all) { 
     document.all.SideBar2.style.pixelTop=document.body.scrollTop+15; 
  }
  return true;
}

function SetupSideBar() {
  var is_mac = (navigator.userAgent.indexOf("Mac")>-1);
  if (document.layers) { 
     rightboundary=94
     leftboundary=36
  } else if (document.all) { 
     if (is_mac){
       rightboundary=-0
       leftboundary=-87
       document.all.SideBar2.style.pixelLeft = leftboundary;
     } else {
       rightboundary=0
       leftboundary=-77
     }
  }
  AdjustSideBar();
  setInterval("AdjustSideBar()", 200);
  if (StartVisible) {
     pull(); 
     hdraw=setTimeout("delayeddraw()",DrawDelay);
  }
}

function pull(){
  if (window.hdraw)
    clearInterval(hdraw);
  hpull=setInterval("pullstep()",PullStepTime)
}

function draw(){
  if (window.hpull)
    clearInterval(hpull)
  hdraw=setTimeout("delayeddraw()",DrawDelay);
}

function delayeddraw(){
  if (window.hpull)
    clearInterval(hpull)
  hdraw=setInterval("drawstep()",DrawStepTime)
}

function pullstep(){
  if (document.all&&document.all.SideBar2.style.pixelLeft<rightboundary)
     document.all.SideBar2.style.pixelLeft+=5
  else if(document.layers&&document.layers.SideBar.left<rightboundary)
     document.layers.SideBar.left+=4
  else if (window.hpull)
     clearInterval(hpull)
}

function drawstep(){
  if (document.all&&document.all.SideBar2.style.pixelLeft>leftboundary)
     document.all.SideBar2.style.pixelLeft-=5
  else if(document.layers&&document.layers.SideBar.left>leftboundary)
     document.layers.SideBar.left-=4
  else if (window.hdraw)
    clearInterval(hdraw)
}

function out(){
  if (document.all)
     document.all.SideBar2.style.pixelLeft=leftboundary
  else if(document.layers)
     document.layers.SideBar.left=leftboundary
  else if (window.hdraw)
    clearInterval(hdraw)
}

function go_to(lnk,ttl){
  if (lnk != ""){
    window.location = lnk;
  } else {
    window.status = ttl;
    setTimeout("window.status='Type ? for Help';", 5000);
  }
}

function show()
{
  if (document.layers){
     document.layers.SideBar.visibility = "visible";
  }
  if (document.all) {
     document.all.SideBar2.style.visibility = "visible";
     document.all.SideBar2.style.display = "block";
  }
}

function hide()
{
  if (document.layers){
     document.layers.SideBar.visibility = "hidden";
  }
  if (document.all){
     document.all.SideBar2.style.visibility = "hidden";
     document.all.SideBar2.style.display = "none";
  }
}

function onKey(e)
{
  var ch;
  if (document.layers)
    ch = String.fromCharCode(e.which);
  if (document.all)
    ch = String.fromCharCode(event.keyCode);
  
  if (ch=='h'){
    hide();
  }
  if (ch=='s') {
    show();
  }
  if (ch=='n') {
    go_to(lnk[0], ttl[0]);
  }
  if (ch=='p') {
    go_to(lnk[1], ttl[1]);
  }
  if (ch=='t') {
    window.location.hash = "_top";
  }
  if (ch=='c') {
    go_to(lnk[3], ttl[3]);
  }
  if (ch=='i') {
    go_to(lnk[4], ttl[4]);
  }
  if (ch=='?') {
    window.open(lnk[6],'miadochelp','scrollbars=yes');
  }
  if (ch=='m') {
    go_to(lnk[7], ttl[7]);
  }
}

if (document.layers){
   document.captureEvents(Event.KEYPRESS);
}
document.onkeypress=onKey;
