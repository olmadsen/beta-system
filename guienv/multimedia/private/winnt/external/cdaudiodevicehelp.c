#include <windows.h>
#ifndef nti_gnu
#include <mmsystem.h>
#endif
#include <stdio.h>

#ifdef nti_gnu
DWORD WINAPI mciSendCommandA(UINT mciId, UINT uMsg, DWORD dwParam1, DWORD dwParam2);

typedef struct tagMCI_INFO_PARMS {
  DWORD dwCallback;
  LPSTR lpstrReturn;
  DWORD dwRetSize;
} MCI_INFO_PARMS, * LPMCI_INFO_PARMS;

#define MCI_INFO                        0x080A

/* MCI time format conversion macros */
#define MCI_MSF_MINUTE(msf)             ((BYTE)(msf))
#define MCI_MSF_SECOND(msf)             ((BYTE)(((WORD)(msf)) >> 8))
#define MCI_MSF_FRAME(msf)              ((BYTE)((msf)>>16))

#define MCI_MAKE_MSF(m, s, f)           ((DWORD)(((BYTE)(m) | \
						  ((WORD)(s)<<8)) | \
						 (((DWORD)(BYTE)(f))<<16)))

#define MCI_TMSF_TRACK(tmsf)            ((BYTE)(tmsf))
#define MCI_TMSF_MINUTE(tmsf)           ((BYTE)(((WORD)(tmsf)) >> 8))
#define MCI_TMSF_SECOND(tmsf)           ((BYTE)((tmsf)>>16))
#define MCI_TMSF_FRAME(tmsf)            ((BYTE)((tmsf)>>24))

#define MCI_MAKE_TMSF(t, m, s, f)       ((DWORD)(((BYTE)(t) | \
						  ((WORD)(m)<<8)) | \
						 (((DWORD)(BYTE)(s) | \
						   ((WORD)(f)<<8))<<16)))

#define MCI_HMS_HOUR(hms)               ((BYTE)(hms))
#define MCI_HMS_MINUTE(hms)             ((BYTE)(((WORD)(hms)) >> 8))
#define MCI_HMS_SECOND(hms)             ((BYTE)((hms)>>16))

#define MCI_MAKE_HMS(h, m, s)           ((DWORD)(((BYTE)(h) | \
						  ((WORD)(m)<<8)) | \
						 (((DWORD)(BYTE)(s))<<16)))

#endif

UINT MCI_MAKE_TMSF_priv(LONG t, LONG m, LONG s, LONG f)
{
  return MCI_MAKE_TMSF(t, m, s, f);
}

UINT MCI_TMSF_TRACKS_priv(UINT tmsf)
{
  return MCI_TMSF_TRACK(tmsf);
}

UINT myMCI_TMSF_MILLI(UINT tmsf)
{
  return ((MCI_TMSF_MINUTE(tmsf))*60+MCI_TMSF_SECOND(tmsf))*1000+(MCI_TMSF_FRAME(tmsf)*1000)/75;
}

UINT getInfo(UINT wDeviceID)
{
  UINT dwReturn = 0;
  MCI_INFO_PARMS info;
  char val[300];
  info.lpstrReturn = (LPSTR) &val;
  info.dwRetSize = 300;
  dwReturn = mciSendCommandA(wDeviceID, MCI_INFO, 0, (DWORD) (LPMCI_INFO_PARMS) &info);

  printf("val = %s.\n", val);
  
  return dwReturn;
}
