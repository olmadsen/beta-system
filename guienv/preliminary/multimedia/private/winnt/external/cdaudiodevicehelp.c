#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>


UINT MCI_MAKE_TMSF_priv(LONG t, LONG m, LONG s, LONG f)
{
  return MCI_MAKE_TMSF(t, m, s, f);
}

UINT getInfo(UINT wDeviceID)
{
  UINT dwReturn = 0;
  MCI_INFO_PARMS info;
  char val[300];
  info.lpstrReturn = (LPSTR) &val;
  info.dwRetSize = 300;
  dwReturn = mciSendCommand(wDeviceID, MCI_INFO, 0, (DWORD) (LPMCI_INFO_PARMS) &info);

  printf("val = %s.\n", val);
  
  return dwReturn;
}
