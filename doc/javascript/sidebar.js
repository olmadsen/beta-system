var StartVisible = 0;
var DrawDelay    = 1000;
var PullStepTime = 15;
var DrawStepTime = 30;

function AdjustSideBar() {
  if (document.layers) { 
     document.layers.SideBar.top = top.pageYOffset+37; 
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

