function HashFromParent()
{ 
  if (parent.location.search){
     location.replace("#" + parent.location.search.substring(1));
  }
}
