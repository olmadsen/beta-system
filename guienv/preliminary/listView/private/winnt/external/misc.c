#include <windows.h>
#include <COMMCTRL.H>
/* #include <shlwapi.h> */
/* From shlwapi.h which is a new header file included with INetSDK. */

//
//====== DllGetVersion  =======================================================
//

typedef struct _DllVersionInfo
{
        DWORD cbSize;
        DWORD dwMajorVersion;                   // Major version
        DWORD dwMinorVersion;                   // Minor version
        DWORD dwBuildNumber;                    // Build number
        DWORD dwPlatformID;                     // DLLVER_PLATFORM_*
} DLLVERSIONINFO;

// Platform IDs for DLLVERSIONINFO
#define DLLVER_PLATFORM_WINDOWS         0x00000001      // Windows 95
#define DLLVER_PLATFORM_NT              0x00000002      // Windows NT

//
// The caller should always GetProcAddress("DllGetVersion"), not
// implicitly link to it.
//

typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO *);

/************** End of stuff from INetSDK **********************/

HRESULT GetComCtlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor)
{
HINSTANCE   hComCtl;

if(   IsBadWritePtr(pdwMajor, sizeof(DWORD)) || 
      IsBadWritePtr(pdwMinor, sizeof(DWORD)))
   return E_INVALIDARG;

//load the DLL
hComCtl = LoadLibrary(TEXT("comctl32.dll"));

if(hComCtl)
   {
   HRESULT           hr = S_OK;
   DLLGETVERSIONPROC pDllGetVersion;
   
   /*
   You must get this function explicitly because earlier versions of the DLL 
   don't implement this function. That makes the lack of implementation of the 
   function a version marker in itself.
   */
   pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hComCtl, TEXT("DllGetVersion"));
   
   if(pDllGetVersion)
      {
      DLLVERSIONINFO    dvi;
      
      ZeroMemory(&dvi, sizeof(dvi));
      dvi.cbSize = sizeof(dvi);
   
      hr = (*pDllGetVersion)(&dvi);
      
      if(SUCCEEDED(hr))
         {
         *pdwMajor = dvi.dwMajorVersion;
         *pdwMinor = dvi.dwMinorVersion;
         }
      else
         {
         hr = E_FAIL;
         }   
      }
   else
      {
      /*
      If GetProcAddress failed, then the DLL is a version previous to the one 
      shipped with IE 3.x.
      */
      *pdwMajor = 4;
      *pdwMinor = 0;
      }
   
   FreeLibrary(hComCtl);

   return hr;
   }

return E_FAIL;
}

BOOL isFullDragSet( HWND hWndListCtrl )
{
  BOOL bIsSet;
  if( SystemParametersInfo( SPI_GETDRAGFULLWINDOWS, 0, &bIsSet, 0 ) )
    {
      return bIsSet;
    }
  return FALSE;
} 
