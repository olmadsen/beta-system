#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#ifdef nti_ms
# include <ole2.h>
# include <richedit.h>
# include <richole.h>
#else
# include <commctrl.h>
#endif

#ifdef nti_bor
# define SF_TEXT 1
# define SF_RTF  2
#endif

#define cchRTFSig 5
static const TCHAR szRTFSig[] = TEXT("{\\rtf");

int sizeof_TCHAR()
{
  return sizeof(TCHAR);
}

int sizeOfCharFormat()
{
#ifdef nti_ms
  return sizeof(CHARFORMAT);
#else
  return 60;
#endif
}

int sizeOfChooseFont()
{
  return sizeof(CHOOSEFONT);
}

int sizeOfLogFont()
{
  return sizeof(LOGFONT);
}

int sizeOfPrintDlg()
{
  return sizeof(PRINTDLG);
}

int sizeOfDocInfo()
{
  return sizeof(DOCINFO);
}



DWORD calFormat(HFILE hf)
{
  DWORD dwFormat;
  TCHAR szType[cchRTFSig + 1];
  UINT cb = cchRTFSig * sizeof(TCHAR);
  
  cb = _lread(hf, szType, cb);
  szType[cb / sizeof(TCHAR)] = TEXT('\0');
  if(cb == cchRTFSig * sizeof(TCHAR))
    dwFormat = lstrcmpi(szRTFSig, szType) ? SF_TEXT : SF_RTF;
  else
    dwFormat = SF_TEXT;		/* not big enough to be RTF, assume text */
  
  /* move back to the beginning of the file */
  _llseek(hf, 0, 0);

  return dwFormat;
}


