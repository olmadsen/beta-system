#include <windows.h>
#include <mmsystem.h>


void playsong(char* name)
{ char* str[512];
  sprintf(str,"open %s type sequencer alias canyon",name);
  mciSendString(str,0,0,0);
  mciSendString("play canyon wait", 0, 0, 0);
  mciSendString("close canyon", 0, 0, 0);
};

