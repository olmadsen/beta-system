function fixPrintButton(imagedir, basename, item)
{
  if (window.print){
    document.images.Print.src = "" + imagedir + "/print.gif";
  } else {
    document.images.Print.src = "" + imagedir + "/printg.gif";
  }
  if (navigator.appName.substring(0,9) == "Microsoft"){
    if (window.print){
      document.all.APrint.outerHTML = '<IMG onClick="javascript:if (parent &&	parent.' + basename + 'Body){printframe(parent.' + basename + 'Body)}" WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="' + imagedir + '/print.gif" ALT="Print ' + basename + ' ' + item + ' Frame" TITLE="Print ' + basename + ' ' + item + ' Interface Frame" BORDER=0>';
    } else {
      document.all.APrint.outerHTML = '<IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="' + imagedir + '/printg.gif" ALT="Print ' + basename + ' ' + item + ' Frame" TITLE="This button is disabled because printing from JavaScript is not supported by your version of Internet Explorer." BORDER=0>';
    }
  }
}
