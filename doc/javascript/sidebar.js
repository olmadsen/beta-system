var StartVisible = 0;
var DrawDelay    = 500;
var PullStepTime = 15;
var DrawStepTime = 30;

function AdjustSideBar() {
  if (document.layers) { 
     document.layers.SideBar.top = window.pageYOffset+37; 
  } else if (document.all) { 
     document.all.SideBar2.style.top=document.body.scrollTop+15; 
  }
  return true;
}

function SetupSideBar() {
  if (document.layers) { 
     rightboundary=94
     leftboundary=36
  } else if (document.all) { 
     rightboundary=0
     leftboundary=-77
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

function onKey(e)
{
   if (document.layers){
     if (e.which==104) {
        // 'h'
	document.layers.SideBar.visibility = "hidden";
     }
     if (e.which==115) {
        // 's'
	document.layers.SideBar.visibility = "visible";
     }
     if (e.which==110) {
        // 'n'
	if (window.next) window.location = next;
     }
     if (e.which==112) {
        // 'p'
	if (window.prev) window.location = prev;
     }
     if (e.which==116) {
        // 't'
	window.location.hash = "_top";
     }
     if (e.which==99) {
        // 'c'
	if (window.content) window.location = content;
     }
     if (e.which==105) {
        // 'i'
	if (window.inx) window.location = inx;
     }
     if (e.which==109) {
        // 'm'
	if (manuals) window.location = manuals;
     }
     if (e.which==63) {
        // '?'
	if (window.help) window.open(help,'miadochelp','scrollbars=yes');
     }
   } else if (document.all){
     if (event.keyCode==104) {
        // 'h'
        //document.all.SideBar2.style.visibility = "hidden";
	document.all.SideBar2.style.display = "none";
     }
     if (event.keyCode==115) {
	// 's'
        //document.all.SideBar2.style.visibility = "visible"; // IE4: "show"?
	document.all.SideBar2.style.display = "block";
     }
     if (event.keyCode==110) {
        // 'n'
	if (window.next) window.location = next;
     }
     if (event.keyCode==112) {
        // 'p'
	if (window.prev) window.location = prev;
     }
     if (event.keyCode==116) {
        // 't'
	window.location.hash = "_top";
     }
     if (event.keyCode==105) {
        // 'i'
	if (window.inx) window.location = inx;
     }
     if (event.keyCode==99) {
        // 'c'
	if (window.content) window.location = content;
     }
     if (event.keyCode==109) {
        // 'm'
	if (window.manuals) window.location = manuals;
     }
     if (event.keyCode==63) {
        // '?'
	if (window.help) window.open(help,'miadochelp','scrollbars=yes');
     }
   }
}

if (document.layers){
   document.captureEvents(Event.KEYPRESS);
}
document.onkeypress=onKey;
