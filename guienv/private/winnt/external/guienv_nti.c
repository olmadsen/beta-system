#include <windows.h>
#include <stdio.h>

#ifdef nti_gnu /* These are missing from the GNU include-files currently! */
  typedef MINMAXINFO FAR *LPMINMAXINFO;
  typedef HANDLE GLOBALHANDLE;
#endif

UINT getOsVersionId()
{
  OSVERSIONINFO osverinf;
  osverinf.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  if (GetVersionEx(&osverinf))
    return osverinf.dwPlatformId;
  return 0;
}

UINT getOsMajorVersionId()
{
  OSVERSIONINFO osverinf;
  osverinf.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  if (GetVersionEx(&osverinf))
    return osverinf.dwMajorVersion;
  return 0;
}

LRESULT CallWindProc(FARPROC theProc,HWND w,UINT m,WPARAM wParam,LPARAM lParam)
{
  return CallWindowProc(theProc,w,m,wParam,lParam);
}

void SetMinMaxInfo (LPMINMAXINFO info,LONG minX,LONG minY,LONG maxX, LONG maxY)
{
  if(minX != 0 || minY != 0) {
    info->ptMinTrackSize.x = minX;
    info->ptMinTrackSize.y = minY;
  }
  if(maxX != 0 || maxY != 0) {
    info->ptMaxTrackSize.x = maxX;
    info->ptMaxTrackSize.y = maxY;
  }
}

HACCEL updateAccelTable(HACCEL hAccel, LONG fVirt, char key, LONG cmd)
{
  HACCEL hAccelOld;
  LPACCEL lpAccelNew;
  ACCEL newAccel;
  int cAccelerators;
  BOOL found;
  UINT i;
  LONG tmpcmd;

  /* printf("fVirt, key, cmd:  %d %c %d\n",fVirt, key, cmd); */

  hAccelOld = hAccel;
  found = FALSE;

  if(!hAccel)
    {
      lpAccelNew = (LPACCEL) LocalAlloc(LPTR,sizeof(ACCEL));
      lpAccelNew[0].cmd = (WORD) cmd;
      lpAccelNew[0].fVirt = (BYTE) fVirt|FVIRTKEY; 
      /* lpAccelNew[0].fVirt = (BYTE) FCONTROL|FVIRTKEY; */
      lpAccelNew[0].key = (WORD) key;
      
      hAccel = CreateAcceleratorTable(lpAccelNew,1);
      LocalFree((HLOCAL)lpAccelNew);
    }
  else
   {
     cAccelerators = CopyAcceleratorTable(hAccelOld,NULL,0);
     lpAccelNew = (LPACCEL) LocalAlloc(LPTR,(cAccelerators+1) * sizeof(ACCEL));
     if (lpAccelNew != NULL)
        CopyAcceleratorTable(hAccel, lpAccelNew, cAccelerators);
     i = 0;
     while ( i < (UINT) cAccelerators )
       {
	 if (lpAccelNew[i].cmd == (WORD) cmd)
	   {
	     lpAccelNew[i].fVirt = (BYTE) fVirt|FVIRTKEY;
	     /* lpAccelNew[i].fVirt = FCONTROL|FVIRTKEY; */
	     lpAccelNew[i].key   = (WORD) key;
	     found = TRUE;
	     break;
	   }
	 i++;
       }

     if (!found)
       {
          lpAccelNew[cAccelerators].cmd = (WORD) cmd;
          lpAccelNew[cAccelerators].fVirt = (BYTE) fVirt|FVIRTKEY;
	  /* lpAccelNew[cAccelerators].fVirt = FCONTROL|FVIRTKEY; */
          lpAccelNew[cAccelerators].key = (WORD) key;
       }/* !found*/
     if (hAccelOld)
       if (!DestroyAcceleratorTable(hAccelOld))
	 printf("DestroyAcceleratorTable failed in updateAccelTable.");
     
     if (found)
       if (cAccelerators>0)
	 hAccel = CreateAcceleratorTable(lpAccelNew,cAccelerators);
       else
	 hAccel = NULL;
     else
       hAccel = CreateAcceleratorTable(lpAccelNew,cAccelerators+1);
     
     LocalFree((HLOCAL)lpAccelNew);
   }

  /* printf("hAccel: %d\n", hAccel);
     printf("hAccelOld: %d\n", hAccelOld); */

  return hAccel;
}

HACCEL deleteAccel(HACCEL hAccel, LONG cmd)
{
  HACCEL hAccelOld;
  LPACCEL lpAccelNew, lpAccelOld;
  ACCEL newAccel;
  int cAccelerators;
  BOOL found;
  UINT i,j;
  LONG tmpcmd;

  hAccelOld = hAccel;
  found = FALSE;
  if(hAccel)
    {
      cAccelerators = CopyAcceleratorTable(hAccelOld,NULL,0);

      lpAccelNew = (LPACCEL) LocalAlloc(LPTR,(cAccelerators) * sizeof(ACCEL));
      lpAccelOld = (LPACCEL) LocalAlloc(LPTR,(cAccelerators) * sizeof(ACCEL));

      if (lpAccelOld != NULL)
        CopyAcceleratorTable(hAccel, lpAccelOld, cAccelerators);
      i = 0;
      j = 0;
      while ( j < (UINT) cAccelerators )
	{
	  if (lpAccelOld[j].cmd == (WORD) cmd)
	    {
	      found = TRUE;
	    }
	  else
	    {
	      lpAccelNew[i].fVirt = lpAccelOld[j].fVirt;
	      lpAccelNew[i].key   = lpAccelOld[j].key;
	      lpAccelNew[i].cmd   = lpAccelOld[j].cmd;
	      i++;
	    }
	  j++;
	}

      if (hAccelOld)
	if (!DestroyAcceleratorTable(hAccelOld))
	  printf("DestroyAcceleratorTable failed in updateAccelTable. hAccelOld= %d\n", hAccelOld);

      if (found)
	if (cAccelerators>1)
	  hAccel = CreateAcceleratorTable(lpAccelNew,cAccelerators-1);
	else
	  hAccel = NULL;
      else
	if (cAccelerators>0)
	  hAccel = CreateAcceleratorTable(lpAccelNew,cAccelerators);
	else
	  hAccel = NULL;
      
      LocalFree((HLOCAL)lpAccelNew);
      LocalFree((HLOCAL)lpAccelOld);
    }

  /* printf("deleteAccell: hAccel: %d\n", hAccel);
     printf("deleteAccell: hAccelOld: %d\n", hAccelOld); */

  return hAccel;
}

BOOL isButtonDown(int button)
{
  return (GetKeyState(button) < 0 );
}

BOOL isVKeyToggled(int vkey)
{
  return (GetKeyState(vkey) & 1) ? 1 : 0;
}

BOOL hasVScroll(int style)
{
return (style & WS_VSCROLL) ? 1 : 0;
}

BOOL hasHScroll (int style)
{
return (style & WS_HSCROLL) ? 1 : 0;
}

BOOL TransferToClipBD( HANDLE hMemBlock, UINT FormatCB )
{
   if( OpenClipboard( NULL ) )
   {
      EmptyClipboard();
      SetClipboardData( FormatCB, hMemBlock );
      CloseClipboard();
      return( TRUE );
   }
   return( FALSE );
}

BOOL TextToClipboard( LPSTR Txt )
{
   int           i, wLen;     
   GLOBALHANDLE  hGMem;
   LPSTR         lpGMem;

   wLen = strlen( Txt );
   hGMem = GlobalAlloc( GHND, (DWORD) wLen + 1 );
   lpGMem = GlobalLock( hGMem );
   for( i=0; i<wLen; i++ ) *lpGMem++ = *Txt++;
   GlobalUnlock( hGMem );
   if( !TransferToClipBD( hGMem, CF_TEXT ) )
      return( FALSE );
   return( TRUE );
}

LPSTR TextFromClipboard()
{ LPSTR          lpText;
  HANDLE         hTextMem;
  LPSTR          TextStr;
  LPSTR          lpMyText;

  OpenClipboard( NULL );      
  hTextMem = GetClipboardData( CF_TEXT );
  lpText = GlobalLock( hTextMem );
  lpMyText = malloc( GlobalSize (hTextMem) );
  lstrcpy( lpMyText, lpText );
  GlobalUnlock( hTextMem );
  CloseClipboard();
  return lpMyText;
}

void setEditRect(LONG left, LONG top, LONG right, LONG bottom, HWND hWnd)
{
  RECT theRect;

  theRect.left = left;
  theRect.top  = top;
  theRect.bottom = bottom;
  theRect.right  = right;
  SendMessage(hWnd,EM_SETRECT,0,(LPARAM) &theRect);
}

int getWndProcAddr(HWND hWnd)
{ int addr;
  addr = GetWindowLong(hWnd,GWL_WNDPROC);
  return addr;
}
