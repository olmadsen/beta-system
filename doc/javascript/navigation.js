var StartVisible = 0;
var DrawDelay    = 500;
var PullStepTime = 15;
var DrawStepTime = 30;
var rightboundary = -20;
var leftboundary = -100;
var SideBar = 0;
var hdraw = 0;
var hpull = 0;

function on_load() {
  window.status='Type ? for Help';
  return true;
}

function AdjustSideBar() {
  if (document.layers) { 
     SideBar.top = window.pageYOffset+37; 
  } else if (document.all) { 
     SideBar.pixelTop=document.body.scrollTop+15; 
  } else if (document.getElementById){
     SideBar.top=parseInt(document.getElementsByTagName("body")[0].scrollTop)+15 + "px"; 
  }
  return true;
}

function SetupSideBar() {
  var is_mac = (navigator.userAgent.indexOf("Mac")>-1);
  if (document.layers) { 
     SideBar = document.layers.SideBar;
     rightboundary=94
     leftboundary=36
  } else if (document.all) { 
     SideBar = document.all.SideBar2.style;
     if (is_mac){
       rightboundary=-0
       leftboundary=-87
       SideBar.pixelLeft = leftboundary;
     } else {
       rightboundary=0
       leftboundary=-77
     }
  } else if (document.getElementById){
     SideBar = document.getElementById("SideBar2").style;
     rightboundary=-2
     leftboundary=-87
     SideBar.left = leftboundary + "px";
     SideBar.top  = 8 + "px";
  }
  AdjustSideBar();
  setInterval("AdjustSideBar()", 200);
  if (StartVisible) {
     pull(); 
     hdraw=setTimeout("delayeddraw()",DrawDelay);
  }
}

function SetLeft(left){
  if (document.layers){
     SideBar.left = left;
  } else {
     SideBar.left = left + "px";
  }
} 

function pull(){
  //alert("pull");
  if (hdraw){
     clearInterval(hdraw);
     hdraw=0;
  }
  hpull=setInterval("pullstep()",PullStepTime)
}

function draw(){
  //alert("draw");
  if (hpull){
    clearInterval(hpull);
    hpull=0;
  }
  hdraw=setTimeout("delayeddraw()",DrawDelay);
}

function delayeddraw(){
  if (hpull){
    clearInterval(hpull);
    hpull=0;
  }
  hdraw=setInterval("drawstep()",DrawStepTime)
}

function pullstep(){
  var left = parseInt(SideBar.left);
  if (left<rightboundary){
     SetLeft(left+5);     
  } else if (hpull) {
     clearInterval(hpull);
     hpull=0;
  }
}

function drawstep(){
  var left = parseInt(SideBar.left);
  if (left>leftboundary){
     SetLeft(left-5);
  } else if (hdraw) {
     clearInterval(hdraw);
     hdraw=0;
  }
}

function out()
{
  SetLeft(leftboundary);
  if (hdraw){
    clearInterval(hdraw);
    hdraw=0;
  }
}

function warn(msg)
{
  //if ((navigator.javaEnabled) && (navigator.javaEnabled())){
  //  java.awt.Toolkit.getDefaultToolkit().beep();
  //  java.awt.Toolkit.getDefaultToolkit().beep();
  //  java.awt.Toolkit.getDefaultToolkit().beep();
  //}
  window.status = msg;
  setTimeout("window.status='Type ? for Help';", 5000);
}

function go_to(lnk,ttl){
  if (lnk != ""){
    window.location = lnk;
  } else {
    warn(ttl);
  }
}

function show()
{
  if (document.layers){
     document.layers.SideBar.visibility = "visible";
  } else {
     document.all.SideBar2.style.visibility = "visible";
     document.all.SideBar2.style.display = "block";
  }
}

function hide()
{
  if (document.layers){
     document.layers.SideBar.visibility = "hidden";
  } else {
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
