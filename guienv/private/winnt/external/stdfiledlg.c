#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#ifdef nti_bor
#include <alloc.h>
#else
#include <malloc.h>
#endif

LPSTR stdopenfiledlg( HWND owner, char* szFilterIn, char* szDirNameIn, char* szFileIn, char* inDialogTitle)
{
  char* szDirName;
  char* szFile;
  char* szDialogTitle;
  char* szFilter;
  char* resultFileName;

  OPENFILENAME ofn;
  
  UINT i, cbString;
  char cbReplace;
  
  if (strlen(szFileIn) > MAX_PATH + 30)
    szFile = malloc(strlen(szFileIn) + 1);
  else
    szFile = malloc(MAX_PATH + 30);
  strcpy(szFile, szFileIn);

  szDirName = malloc(strlen(szDirNameIn) + 1);
  strcpy(szDirName, szDirNameIn);

  szDialogTitle = malloc(strlen(inDialogTitle) + 1);
  strcpy(szDialogTitle, inDialogTitle);

  szFilter = malloc(strlen(szFilterIn) + 1);
  strcpy(szFilter, szFilterIn);

  cbString = strlen(szFilter);
  cbReplace = szFilter[cbString - 1];

  for (i=0; szFilter[i]; i++) {
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
      resultFileName = malloc(strlen(ofn.lpstrFile) + 1);
      strcpy(resultFileName, ofn.lpstrFile);
      free (szFile);
      free (szDirName);
      free (szFilter);
      free (szDialogTitle);
      return resultFileName;
    }
  else
    {
      free (szFile);
      free (szDirName);
      free (szFilter);
      free (szDialogTitle);
      return (LPSTR) 0;
    }
}

LPSTR stdsavefiledlg( HWND owner, char* szFilterIn, char* szDirNameIn, char* szFileIn, char* inDialogTitle)
{
  char* szDirName;
  char* szFile;
  char* szDialogTitle;
  char* szFilter;
  char* resultFileName;
  OPENFILENAME ofn;
  UINT i, cbString;
  char cbReplace;
 
  if (strlen(szFileIn) > MAX_PATH + 30)
    szFile = malloc(strlen(szFileIn) + 1);
  else
    szFile = malloc(MAX_PATH + 30);
  strcpy(szFile, szFileIn);

  szDirName = malloc(strlen(szDirNameIn) + 1);
  strcpy(szDirName, szDirNameIn);

  szDialogTitle = malloc(strlen(inDialogTitle) + 1);
  strcpy(szDialogTitle, inDialogTitle);

  szFilter = malloc(strlen(szFilterIn) + 1);
  strcpy(szFilter, szFilterIn);

  cbString = strlen(szFilter);
  cbReplace = szFilter[cbString - 1];

  for (i=0; szFilter[i]; i++) {
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
    {
      resultFileName = malloc(strlen(ofn.lpstrFile) + 1);
      strcpy(resultFileName, ofn.lpstrFile);
      free (szFile);
      free (szDirName);
      free (szFilter);
      free (szDialogTitle);
      return resultFileName;
    }
  else
    {
      free (szFile);
      free (szDirName);
      free (szFilter);
      free (szDialogTitle);
      return (LPSTR) 0;
    }
}
