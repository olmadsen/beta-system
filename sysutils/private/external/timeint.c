#include <TextUtils.h>
#include <Memory.h>
#include <Types.h>

#define longint long

extern char *pStrcat(unsigned char* s,unsigned char *t); /* defined in betaenv_ppcbody */


void getdatestring(long time, Str255 pstr);

void getdatestring(long time, Str255 pstr)
{   Str255 secsStr;
    time=time | (1<<31);   // to make a time from modtime correct
	DateString(time,1,pstr,NULL);  // 1 is long format
	TimeString(time,true,secsStr,NULL);  // get hours, minutes, and seconds
	pStrcat(pstr,"\p ");
	pStrcat(pstr,secsStr);
}

