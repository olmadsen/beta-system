#include <windows.h>
#ifndef nti_gnu
# include <vfw.h>
#endif

#ifdef nti_gnu
struct __avifile;
typedef struct __avifile __avifile;
typedef __avifile FAR* PAVIFILE;

typedef struct _AVIFILEINFO {
  DWORD dwMaxBytesPerSec;
  DWORD dwFlags;
  DWORD dwCaps;
  DWORD dwStreams;
  DWORD dwSuggestedBufferSize;
  DWORD dwWidth;
  DWORD dwHeight;
  DWORD dwScale;        
  DWORD dwRate;
  DWORD dwLength;
  DWORD dwEditCount;
  char  szFileType[64];
} AVIFILEINFO, FAR * LPAVIFILEINFO;

  #define MCI_CLOSE                       0x0804
  #define MCI_PLAY                        0x0806
  #define MCI_SEEK                        0x0807
  #define MCI_STOP                        0x0808
  #define MCI_PAUSE                       0x0809
  #define MCI_NOTIFY                      0x00000001L
  #define MCI_WAIT                        0x00000002L
  #define MCI_FROM                        0x00000004L
  #define MCI_TO                          0x00000008L
  #define MCI_TRACK                       0x00000010L
  #define MCIWndOpen(hwnd, sz, f)     (LONG)MCIWndSM(hwnd, MCIWNDM_OPEN, (WPARAM)(UINT)(f),(LPARAM)(LPVOID)(sz))
  #define MCIWndOpenDialog(hwnd)      MCIWndOpen(hwnd, -1, 0)
  #define MCIWndClose(hwnd)           (LONG)MCIWndSM(hwnd, MCI_CLOSE, 0, 0)
  #define MCIWndPlay(hwnd)            (LONG)MCIWndSM(hwnd, MCI_PLAY, 0, 0)
  #define MCIWndStop(hwnd)            (LONG)MCIWndSM(hwnd, MCI_STOP, 0, 0) 
  #define MCIWndPause(hwnd)           (LONG)MCIWndSM(hwnd, MCI_PAUSE, 0, 0)
  #define MCIWndResume(hwnd)          (LONG)MCIWndSM(hwnd, MCI_RESUME, 0, 0)
  #define MCIWndSeek(hwnd, lPos)      (LONG)MCIWndSM(hwnd, MCI_SEEK, 0, (LPARAM)(LONG)(lPos))
  #define MCIWndEject(hwnd)           (LONG)MCIWndSM(hwnd, MCIWNDM_EJECT, 0, 0)

  #define MCIWndHome(hwnd)            MCIWndSeek(hwnd, MCIWND_START)
  #define MCIWndEnd(hwnd)             MCIWndSeek(hwnd, MCIWND_END)
  #define MCIWNDM_OPEN                (WM_USER + 153)
  #define MCIWND_START                -1
  #define MCIWND_END                  -2
  #define MCIWndSM SendMessage  
  #define MCIWNDM_GETDEVICEID	(WM_USER + 100)
  #define MCIWNDM_GETDEVICE           (WM_USER + 125)
  #define MCIWNDM_GETFILENAME    (WM_USER + 124)

  WINAPI DWORD WINAPI mciSendCommandA(UINT mciId, UINT uMsg, DWORD dwParam1, DWORD dwParam2);
  #define mciSendCommand  mciSendCommandA

  WINAPI AVIFileOpenA       (PAVIFILE FAR * ppfile, LPCSTR szFile, UINT uMode, LPCLSID lpHandler);
  #define AVIFileopen AVIFileOpenA

  WINAPI AVIBuildFilterA(LPSTR lpszFilter, LONG cbFilter, BOOL fSaving);
  #define AVIBuildFilter	AVIBuildFilterA

  BOOL WINAPI GetOpenFileNamePreviewA(OPENFILENAME* lpofn);
  #define GetOpenFileNamePreview          GetOpenFileNamePreviewA


  WINAPI AVIFileInfoA (PAVIFILE pfile, AVIFILEINFO* pfi, LONG lSize);
  #define AVIFileInfo	AVIFileInfoA

  ULONG WINAPI AVIFileRelease      (PAVIFILE pfile);

  #define MCIWndGetFileName(hwnd, lp, len) (LONG)MCIWndSM(hwnd, MCIWNDM_GETFILENAME, (WPARAM)(UINT)(len), (LPARAM)(LPVOID)(lp))

  #define MCIWndGetDevice(hwnd, lp, len)   (LONG)MCIWndSM(hwnd, MCIWNDM_GETDEVICE, (WPARAM)(UINT)(len), (LPARAM)(LPVOID)(lp))

  #define MCIWndGetDeviceID(hwnd)     (UINT)MCIWndSM(hwnd, MCIWNDM_GETDEVICEID, 0, 0)

  #define MCIWNDM_CHANGESTYLES	(WM_USER + 135)
  #define MCIWndChangeStyles(hwnd, mask, value) (LONG)MCIWndSM(hwnd, MCIWNDM_CHANGESTYLES, (WPARAM)(UINT)(mask), (LPARAM)(LONG)(value))

  #define MCIWNDM_SETOWNER	(WM_USER + 152)
  #define MCIWndSetOwner(hwnd, hwndP)  (LONG)MCIWndSM(hwnd, MCIWNDM_SETOWNER, (WPARAM)(hwndP), 0)

  #define MCIWndDestroy(hwnd)         (VOID)MCIWndSM(hwnd, WM_CLOSE, 0, 0)

  #define MCIWNDM_GETPOSITION	(WM_USER + 102)
  #define MCIWndGetPosition(hwnd)     (LONG)MCIWndSM(hwnd, MCIWNDM_GETPOSITION, 0, 0)

  #define MCIWNDM_PLAYFROM	(WM_USER + 122)
  #define MCIWNDM_PLAYTO          (WM_USER + 123)

  #define MCIWndPlayFrom(hwnd, lPos)  (LONG)MCIWndSM(hwnd, MCIWNDM_PLAYFROM, 0, (LPARAM)(LONG)(lPos))
  #define MCIWndPlayTo(hwnd, lPos)    (LONG)MCIWndSM(hwnd, MCIWNDM_PLAYTO,   0, (LPARAM)(LONG)(lPos))

  #define MCIWndPlayFromTo(hwnd, lStart, lEnd) (MCIWndSeek(hwnd, lStart), MCIWndPlayTo(hwnd, lEnd))

  #define MCIWNDM_GETLENGTH	(WM_USER + 104)
  #define MCIWndGetLength(hwnd)       (LONG)MCIWndSM(hwnd, MCIWNDM_GETLENGTH, 0, 0)

  #define MCIWNDM_SETTIMEFORMAT (WM_USER + 119)
  #define MCIWndSetTimeFormat(hwnd, lp) (LONG)MCIWndSM(hwnd, MCIWNDM_SETTIMEFORMAT, 0, (LPARAM)(LPTSTR)(lp))

  #define MCIWndUseTime(hwnd)         MCIWndSetTimeFormat(hwnd, TEXT("ms"))

  #define MCIWNDM_GET_SOURCE      (WM_USER + 140)
  #define MCIWndGetSource(hwnd, prc)  (LONG)MCIWndSM(hwnd, MCIWNDM_GET_SOURCE, 0, (LPARAM)(LPRECT)(prc))


#endif

int avilength,aviwidth,aviheight;

int AVIwdh() { return aviwidth; };

int AVIlgt() { return avilength; };

int AVIhgt() { return aviheight; };
void AVIread(char* filename)
{
  PAVIFILE ppfile;
  AVIFILEINFO pfi;
  
  if (AVIFileOpenA(&ppfile,filename,OF_READ,0x0)) {
    avilength=0;aviwidth=0;aviheight=0;
    return;
  };
  
  
  if (!AVIFileInfo(ppfile,&pfi,sizeof(AVIFILEINFO))) {
    aviwidth=pfi.dwWidth;
    aviheight=pfi.dwHeight;
    avilength=pfi.dwLength/((float)pfi.dwRate/pfi.dwScale);
  };


  AVIFileRelease(ppfile);
}
  
                
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

LONG myMCIWndPause(HWND hwnd)
{
  return MCIWndPause(hwnd);
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

typedef struct
{ 
  int length, width, height; 
} infostruct;
   

void myMCIgetinfo(char* filename,HWND owner,HINSTANCE hinst,infostruct* inf)
{
  HWND hwnd;
  int length;
  RECT prc;

  hwnd = MCIWndCreate(owner,hinst,0,filename);
  length = MCIWndGetLength(hwnd);
  MCIWndGetSource(hwnd,&prc);
  MCIWndDestroy(hwnd);
  
  inf->length=length;
  inf->width=prc.right-prc.left;
  inf->height=prc.bottom-prc.top;
}
  
  
