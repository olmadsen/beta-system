function printframe()
{
  if (navigator.appName.substring(0,9) == "Microsoft"){
     if (navigator.userAgent.indexOf("IE 5")  > -1){
       window.print();
     } else {
       alert("Sorry, your version of Explorer does not support printing from JavaScript.\nUse your browser's print button instead.");
     }
  } else {
     self.print();
  }
}
