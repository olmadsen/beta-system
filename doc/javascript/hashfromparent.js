function HashFromParent()
{ 
  if (parent.location.search){
     location.hash = parent.location.search.substring(1);
  }
}
