var StartVisible = 0;
var DrawDelay    = 500;
var PullStepTime = 15;
var DrawStepTime = 30;
var rightboundary = -20;
var leftboundary = -100;
var SideBar = 0;
var hdraw = 0;
var hpull = 0;
var helpmsg = "Type ? for help";

function on_load() {
  window.status=helpmsg;
  return true;
}

function AdjustSideBar() {
  if (document.layers) { 
     SideBar.top = window.pageYOffset+37; 
  } else if (document.all) { 
     SideBar.pixelTop=document.body.scrollTop+15; 
  } else if (document.getElementById){
     SideBar.top=window.pageYOffset+8 + "px"; 
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
     rightboundary=2
     leftboundary=-87
     SideBar.left = leftboundary + "px";
     SideBar.top  = 8 + "px";
     PullStepTime = 5;
     DrawStepTime = 10;
  }
  AdjustSideBar();
  if (document.all){
     window.onscroll = AdjustSideBar;
     //document.onhelp = openhelp;
  } else {
    setInterval("AdjustSideBar()", 100);
  }
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

function containsNN6 (container, containee) {
  var isParent = false;
  do {
    if ((isParent = container == containee)){
      break;
    }
    containee = containee.parentNode;
  } while (containee != null);
  return isParent;
}

function pull(e){
  // Ignore events bubbling from children
  if (document.all) {
     // Fails on MacIE5 - and seems not to be needed on IE.
     // if (this.contains(e.fromElement)){
     //   return;
     //}
  } else if (document.getElementById) {
     if (containsNN6(this, e.relatedTarget))
        return;
  }
  if (hdraw){
     clearInterval(hdraw);
     hdraw=0;
  }
  hpull=setInterval("pullstep()",PullStepTime)
}

function draw(e){
  // Ignore events bubbling from children
  if (document.all) {
     // Fails on MacIE5 - and seems not to be needed on IE.
     // if (this.contains(e.toElement)){
     //   return;
     //}
  } else if (document.getElementById) {
     if (containsNN6(this, e.relatedTarget)){
        return;
     }
  }
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

function setStatusTimeout(msg1, msg2)
{
  window.status = msg1;
  setTimeout('window.status="' + msg2 + '";', 5000);
}

function warn(msg)
{
  //if ((navigator.javaEnabled) && (navigator.javaEnabled())){
  //  java.awt.Toolkit.getDefaultToolkit().beep();
  //  java.awt.Toolkit.getDefaultToolkit().beep();
  //  java.awt.Toolkit.getDefaultToolkit().beep();
  //}
  setStatusTimeout(msg, helpmsg);
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
     SideBar.visibility = "visible";
  } else {
     SideBar.visibility = "visible";
     SideBar.display = "block";
  }
}

function hide()
{
  if (document.layers){
     SideBar.visibility = "hidden";
  } else {
     SideBar.visibility = "hidden";
     SideBar.display = "none";
  }
}

function openhelp()
{
   window.open(lnk[6],'miadochelp','scrollbars=yes;');
   return false;
}

function onKey(e)
{
  var c = document.layers ? e.which : document.all ? event.keyCode : document.getElementById ? e.keyCode : 1;
  var ch = String.fromCharCode(c);
  //window.status = 'pressed ' + c + ' "' + ch + '"';
  if (ch=='?') {
    openhelp();
    return false;
  }
  ch = ch.toLowerCase();
  if (ch=='h'){
    hide();
    return;
  }
  if (ch=='s') {
    show();
    return false;
  }
  if (ch=='n') {
    go_to(lnk[0], ttl[0]);
    return false;
  }
  if (ch=='p') {
    go_to(lnk[1], ttl[1]);
    return false;
  }
  if (ch=='t') {
    window.location.hash = "_top";
    return false;
  }
  if (ch=='c') {
    go_to(lnk[3], ttl[3]);
    return false;
  }
  if (ch=='i') {
    go_to(lnk[4], ttl[4]);
    return false;
  }
  if (ch=='m') {
    go_to(lnk[7], ttl[7]);
    return false;
  }
}

if (document.layers){
   document.captureEvents(Event.KEYUP);
}
document.onkeyup=onKey;
