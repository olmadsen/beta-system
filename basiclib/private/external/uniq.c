#include <sys/ioctl.h>  

int getImRead(thefile)
int thefile;
{
  long noOfBytes;
  int result;

  result=ioctl(thefile,FIONREAD,&noOfBytes);
  if (result==0) { return noOfBytes;} else { return -1;};
}
