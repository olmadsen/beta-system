var StartVisible = 0;

function AdjustSideBar() {
  if (document.layers) { 
     document.layers.SideBar.top = top.pageYOffset+15; 
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
     leftboundary=-67
  }
  setInterval("AdjustSideBar()", 200);
  if (StartVisible) hdraw=setTimeout("draw()",2000);
}

function pull(){
  if (window.hdraw)
    clearInterval(hdraw);
  hpull=setInterval("pullstep()",30)
}

function draw(){
  if (window.hpull)
    clearInterval(hpull)
  hdraw=setInterval("drawstep()",30)
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

