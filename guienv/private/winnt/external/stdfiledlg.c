#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#ifdef nti_bor
#include <alloc.h>
#else
#include <malloc.h>
#endif

static char szDirName[MAX_PATH + 30];
static char szFile[MAX_PATH + 30];
static char* szDialogTitle;

LPSTR stdopenfiledlg( HWND owner, char* szFilter, char* szDirNameIn, char* szFileIn, char* inDialogTitle)
{
  LPSTR   lpstrFile;
  OPENFILENAME ofn;
  
  UINT i, cbString;
  char cbReplace;
  
  strcpy(szFile, szFileIn);
  strcpy(szDirName, szDirNameIn);
  szDialogTitle = malloc(strlen(inDialogTitle) + 1);
  strcpy(szDialogTitle, inDialogTitle);

  cbString = strlen(szFilter);
  cbReplace = szFilter[cbString - 1];

  for (i=0; szFilter[i] != '\0'; i++) {
      if (szFilter[i] == cbReplace)
         szFilter[i] = '\0';
  }
  memset(&ofn, 0, sizeof(OPENFILENAME));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = owner;
  ofn.lpstrFilter = szFilter;
  ofn.nFilterIndex = 1;
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = MAX_PATH + 30;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = szDirName;
  ofn.lpstrTitle = szDialogTitle;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  if (GetOpenFileName(&ofn))
    {
      /* printf("lpstrFile: %s \n", ofn.lpstrFile); */
      free (szDialogTitle);
      return ofn.lpstrFile;
    }
  else
    {
      free (szDialogTitle);
      return (LPSTR) 0;
    }
}

LPSTR stdsavefiledlg( HWND owner, char* szFilter, char* szDirNameIn, char* szFileIn, char* inDialogTitle)
{
  LPSTR   lpstrFile;
  OPENFILENAME ofn;
  UINT i, cbString;
  char cbReplace;
 
  strcpy(szFile, szFileIn);
  strcpy(szDirName, szDirNameIn);
  szDialogTitle = malloc(strlen(inDialogTitle) + 1);
  strcpy(szDialogTitle, inDialogTitle);

  cbString = strlen(szFilter);
  cbReplace = szFilter[cbString - 1];

  for (i=0; szFilter[i] != '\0'; i++) {
      if (szFilter[i] == cbReplace)
         szFilter[i] = '\0';
  }
  memset(&ofn, 0, sizeof(OPENFILENAME));
 
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = owner;
  ofn.lpstrFilter = szFilter;
  ofn.nFilterIndex = 1;
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = MAX_PATH + 30;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = szDirName;
  ofn.lpstrTitle = szDialogTitle;
  ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
  if (GetSaveFileName(&ofn))
     return ofn.lpstrFile;
  else
     return (LPSTR) 0;
}
