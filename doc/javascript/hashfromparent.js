function HashFromParent(filename)
{ 
  if ((!parent) || (parent.frames["" + filename + "Body"] != self)){
     // Open frameset instead
     location.replace("" + filename + ".html" + location.hash);
  } else {
    if (parent.location.hash){
       var oldhash = location.hash;
       var newhash = parent.location.hash;
       if (newhash != oldhash) {
	  location.replace(newhash);
       }
    }
  }
}
