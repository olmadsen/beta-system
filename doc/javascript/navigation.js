var StartVisible = 0;
var DrawDelay    = 500;
var PullStepTime = 15;
var DrawStepTime = 30;
var rightboundary = 0;
var leftboundary = 0;
var topOffset = 0;
var SideBar = 0;
var SideBarWidth = 0;
var SideBarHeight = 0
var tid = 0;
var hdraw = 0;
var hpull = 0;
var helpmsg = "Type ? for help";
var Opera = window.opera ? true : false;
var Mac = (navigator.userAgent.indexOf("Mac")>-1);
var UpdateDelay = 25;

function on_load() {
  window.status=helpmsg;
  SetupSideBar();
  return true;
}

function AdjustSideBar () {
  if (document.layers) {
    SideBar.top = window.pageYOffset + topOffset;
  }
  else if (document.all && !Opera) {
    SideBar.style.pixelTop = // document.body.scrollTop + topOffset;
                             // document.body.scrollTop disabled when
			     // using DOCTYPE in IE6, see e.g.
			     // http://www.evolt.org/article/document_body_doctype_switching_and_more/17/30655
			     // http://www.quirksmode.org/js/doctypes.html
			     // http://www.quirksmode.org/js/fixedmenu.html
			     // http://forums.devshed.com/archive/t-26334
                             document.documentElement.scrollTop + topOffset;
  }
  else if (document.getElementById && !Opera) {
    if (SideBarWidth == 0)  // workaround for bug of NN6 to compute width
      SideBarWidth = SideBar.offsetWidth;
    SideBar.style.top = (window.pageYOffset+topOffset) + 'px';
  }
  else if (Opera) {
    SideBar.style.pixelTop = window.pageYOffset + topOffset;
  }
}

function SetupSideBar() {
  if (document.layers) {
    SideBar = document['SideBarLayer'];
    SideBarWidth = SideBar.document.width;
    SideBarHeight = SideBar.document.height;
    rightboundary=90
    leftboundary=36
    topOffset = 45;
  }
  else if (document.all && !Opera) {
    SideBar = document.all['SideBar'];
    SideBarWidth = SideBar.offsetWidth;
    SideBarHeight = SideBar.offsetHeight;
    if (Mac){
      rightboundary=0
      leftboundary=-90
      topOffset = 15;
    } else {
      rightboundary=2
      leftboundary=-87
      topOffset = 26;
    }
    SideBar.style.pixelLeft = leftboundary;
  }
  else if (document.getElementById && !Opera) {
    SideBar = document.getElementById('SideBar');
    SideBarWidth = SideBar.offsetWidth;
    SideBarHeight = SideBar.offsetHeight;
    rightboundary=2
    leftboundary=-87
    topOffset = 13;
    SideBar.style.left = leftboundary + "px";
    SideBar.style.top  = 8 + "px";
    PullStepTime = 5;
    DrawStepTime = 10;
  }
  else if (Opera) {
    SideBar = document.getElementById('SideBar');
    SideBarWidth = SideBar.style.pixelWidth;
    SideBarHeight = SideBar.style.pixelHeight;
    rightboundary=2
    leftboundary=-87
    topOffset = 15;
  }
  AdjustSideBar();
  if (document.layers) {
    SideBar.visibility = 'show';
  } else {
    SideBar.style.visibility = 'visible';
  }
  if (document.all && !Opera) {
    window.onscroll = AdjustSideBar;
    //document.onhelp = openhelp;
  } else {
    tid = setInterval('AdjustSideBar()', UpdateDelay);
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
     SideBar.style.left = left + "px";
  }
} 
function GetLeft(){
  if (document.all){
     return SideBar.style.pixelLeft;
  } else if (document.layers){
     return parseInt(SideBar.left);
  } else {
     return parseInt(SideBar.style.left);
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
  var left = GetLeft();
  if (left<rightboundary){
     SetLeft(left+5);     
  } else if (hpull) {
     clearInterval(hpull);
     hpull=0;
  }
}

function drawstep(){
  var left = GetLeft();
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
     SideBar.style.visibility = "visible";
     SideBar.style.display = "block";
  }
}

function hide()
{
  if (document.layers){
     SideBar.visibility = "hidden";
  } else {
     SideBar.style.visibility = "hidden";
     SideBar.style.display = "none";
  }
}

function openhelp()
{
   window.open(lnk[6],'miadochelp','scrollbars=yes');
   return false;
}

function onKey(e)
{
  var c;
  var ch;
  if (document.layers){
    c  = e.which;
    ch = String.fromCharCode(e.which);
  } else if (document.all){
    c  = event.keyCode;
    ch = String.fromCharCode(event.keyCode);
  } else if (document.getElementById){
    c  = e.charCode;
    ch = String.fromCharCode(e.charCode);
  } else {
    c  = 1;
    ch = '*';
  }
  //window.status = 'Pressed ' + c + ' "' + ch + '"';
  if (ch=='?') {
    // Fails in Netscape 6 (c==0)
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
   document.captureEvents(Event.KEYPRESS);
}

document.onkeypress=onKey;
window.onload=on_load;
