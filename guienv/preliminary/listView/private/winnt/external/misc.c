#include <windows.h>
#include <shlwapi.h>

#if (_WIN32_IE >= 0x0400)
#define ie 10
#else
#define ie 20
#endif

HRESULT GetComCtlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor)
{
HINSTANCE   hComCtl;

printf("ie = %d \n", ie);

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

