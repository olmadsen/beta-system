function fixPrintButton()
{
  if (window.print){
    document.images.Print.src = "../../images/print.gif";
  } else {
    document.images.Print.src = "../../images/printg.gif";
  }
  if (navigator.appName.substring(0,9) == "Microsoft"){
    if (window.print){
      //if (printIsNativeSupport()){
	document.all.APrint.outerHTML = '<IMG onClick="javascript:if (parent && parent.basicsystemenvBody){printframe(parent.basicsystemenvBody)}" WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="../../images/print.gif" ALT="Print Basicsystemenv Interface Frame" TITLE="Print Basicsystemenv Interface Frame" BORDER=0>';
      //}
    } else {
      document.all.APrint.outerHTML = '<IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="../../images/printg.gif" ALT="Print Basicsystemenv Interface Frame" TITLE="This button is disabled because printing from JavaScript is not supported by your version of Internet Explorer." BORDER=0>';
    }
  }
}
