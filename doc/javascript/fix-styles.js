// IE 5
function setIEStyle(sel, prop, val)
{
  for (i=0; i<document.styleSheets[0].rules.length; i++){
      if (document.styleSheets[0].rules[i].selectorText == sel){
         document.styleSheets[0].rules[i].style[prop] = val;
         return;
      }
  }
  // selector not found
  document.styleSheets[0].addRule(sel, prop + ": " + val);
}

if (document.all){	
   if (navigator.userAgent.indexOf("Mac")>-1){
      setIEStyle("PRE.beta", "marginRight", "40px");
   }
   setIEStyle("DIV.toc DL DL", "marginLeft", "-20px");
}
