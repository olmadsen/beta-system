function CheckParent(filename)
{ 
  if ((!parent) || (parent.frames["" + filename + "Body"] != self)){
     // Open frameset instead
     location.replace("" + filename + ".html" + location.hash);
  } 
}
function CheckParent2(framename,filename)
{ 
  if ((!parent) || (parent.frames["" + framename + "Body"] != self)){
     // Open frameset instead
     location.replace("" + filename + ".html" + location.hash);
  } 
}
function HashFromParent()
{ 
  if (parent && parent.location.hash){
     var oldhash = location.hash;
     var newhash = parent.location.hash;
     if (newhash != oldhash) {
	location.replace(newhash);
     }
  }
}
