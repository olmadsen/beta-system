#include <windows.h>
#include <vfw.h>

LPSTR openAVIfile(char* szFilterIn)
	{	
    	OPENFILENAME ofn;
	char* gachFilter;
	char* resultFileName;
	char* szFile;
	UINT i, cbString;
	char cbReplace;

	szFile = malloc(MAX_PATH + 30);
	szFile[0] = 0;

        //
        // prompt user for file to open
        //
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner   = NULL;
        ofn.hInstance   = NULL;
        ofn.lpstrTitle = TEXT("Open AVI");

	gachFilter = malloc(strlen(szFilterIn) + 1);
	strcpy(gachFilter, szFilterIn);

	cbString = strlen(gachFilter);
	cbReplace = gachFilter[cbString - 1];
	
	for (i=0; gachFilter[i]; i++) {
	  if (gachFilter[i] == cbReplace)
	    gachFilter[i] = '\0';
	}

        if (gachFilter[0] == TEXT('\0'))
    	    AVIBuildFilter(gachFilter, sizeof(gachFilter)/sizeof(TCHAR), FALSE);
    	
    	ofn.lpstrFilter       = gachFilter;
        ofn.lpstrCustomFilter = NULL;
        ofn.nMaxCustFilter    = 0;
        ofn.nFilterIndex      = 0;
        ofn.lpstrFile         = szFile;
        ofn.nMaxFile          = MAX_PATH + 30;
        ofn.lpstrFileTitle    = NULL;
        ofn.nMaxFileTitle     = 0;
        ofn.lpstrInitialDir   = NULL;
        ofn.Flags             = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
        ofn.nFileOffset       = 0;
        ofn.nFileExtension    = 0;
        ofn.lpstrDefExt       = NULL;
        ofn.lCustData         = 0;
        ofn.lpfnHook          = NULL;
        ofn.lpTemplateName    = NULL;

    	/*
	 * If we've got a filename, return it
	 */
        if (GetOpenFileNamePreview(&ofn))
	  {
	    resultFileName = malloc(strlen(ofn.lpstrFile) + 1);
	    strcpy(resultFileName, ofn.lpstrFile);
	    free (szFile);
	    free (gachFilter);
	    return resultFileName;
	  }
        else
	  {
	    free (szFile);
	    free (gachFilter);
	    return (LPSTR) 0;
	  }
}


BOOL myMCIWndRegisterClass(HINSTANCE hInstance)
{
  return MCIWndRegisterClass(hInstance);
}

LONG myMCIWndOpen(HWND hwnd, LPSTR szFile, UINT wFlags)
{
  return MCIWndOpen(hwnd, szFile, wFlags);
}

LONG myMCIWndPlay(HWND hWnd)
{
  return MCIWndPlay(hWnd);
}

LONG myMCIWndStop(HWND hwnd)
{
  return MCIWndStop(hwnd);
}

DWORD myMCIWndClose(HWND hwnd)
{
  UINT uDevice = MCIWndGetDeviceID(hwnd);
  
  SendMessage(hwnd, MCI_CLOSE, MCI_WAIT, 0);
  if (uDevice>0) 
    {
      /* SendMessage(MCI_CLOSE) doesn't seem to close the device */
      DWORD dwErr = mciSendCommand(uDevice, MCI_CLOSE, MCI_WAIT, 0);
      return dwErr;
    }
  return 0;
}

LONG myMCIWndChangeStyles(HWND hwnd, UINT mask, LONG value)
{
  return MCIWndChangeStyles(hwnd, mask, value);
}

LONG myMCIWndGetDevice(HWND hwnd, LPSTR lp, UINT len)
{
  return MCIWndGetDevice(hwnd, lp, len);
}

UINT myMCIWndGetDeviceID(HWND hwnd)
{
  return MCIWndGetDeviceID(hwnd);
}


LONG myMCIWndGetFileName(HWND hwnd, LPSTR lp, UINT len)
{
  return MCIWndGetFileName(hwnd, lp, len);
}

LONG myMCIWndSetOwner(HWND hwnd, HWND hwndP)
{
  return MCIWndSetOwner(hwnd, hwndP);
}

VOID myMCIWndDestroy(HWND hwnd)
{
  MCIWndDestroy(hwnd);
}

LONG myMCIWndGetPosition(HWND hwnd)
{
  return MCIWndGetPosition(hwnd);
}

LONG myMCIWndPlayFromTo(HWND hwnd, LONG lStart, LONG lEnd)
{ /* Returns zero if successful or an error otherwise. */
  return MCIWndPlayFromTo(hwnd, lStart, lEnd);
}

LONG myMCIWndPlayFrom(HWND hwnd, LONG lPos)
{ /* Returns zero if successful or an error otherwise. */
return MCIWndPlayFrom(hwnd, lPos);
}

LONG myMCIWndPlayTo(HWND hwnd, LONG lPos)
{ /* Returns zero if successful or an error otherwise. */
  return MCIWndPlayTo(hwnd, lPos);
}


LONG myMCIWndGetLength(HWND hwnd)
{ /* Returns the length. The units for the length depend on the current time format. */
  return MCIWndGetLength(hwnd);
}

LONG myMCIWndSeek(HWND hwnd, long lPos) 
{ /* Returns zero if successful or an error otherwise. */
  return MCIWndSeek(hwnd, lPos);
}

LONG myMCIWndHome(HWND hwnd)
{
  return MCIWndHome(hwnd);
};

LONG myMCIWndEnd(HWND hwnd)
{
  return MCIWndEnd(hwnd);
};

LONG myMCIWndUseTime(HWND hwnd)
{ /* Returns zero if successful or an error otherwise. */
  return MCIWndUseTime(hwnd);
}

