function HashFromParent()
{ 
  if (parent && parent.location.search){
     var oldhash = location.hash;
     var newhash = "#" + parent.location.search.substring(1);
     if (newhash != oldhash) {
	location.replace(newhash);
     }
  }
}
