#include <windows.h>

void getDrives (LPSTR theDrives) 
{

   DWORD  dwNumBytesForDriveStrings;
   HANDLE hHeap;
   LPTSTR lp;
   TCHAR  szLogDrive[100];
   int    nNumDrives = 0, nDriveNum;


   // Get the number of bytes needed to hold all
   // the logical drive strings.
   dwNumBytesForDriveStrings =
      GetLogicalDriveStrings(0, NULL) * sizeof(TCHAR);

   // Allocate memory from the heap for the drive
   // string names.
   hHeap = GetProcessHeap();
   lp = (LPTSTR) HeapAlloc(hHeap, HEAP_ZERO_MEMORY,
      dwNumBytesForDriveStrings);

   // Get the drives string names in our buffer.
   GetLogicalDriveStrings(HeapSize(hHeap, 0, lp), lp);

   // Parse the memory block, and fill the combo box.
   while (*lp != 0) {

      ComboBox_AddString(hwndCtl, lp);
      nNumDrives++;
      lp = _tcschr(lp, 0) + 1;   // Point to next string.
    }

   HeapFree(hHeap, 0, lp);
 }
