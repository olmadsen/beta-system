#include <windows.h>
#include <stdio.h>


// Konverterer GlobalMemory-handle til Pointer
LPSTR Handle2Pointer(HANDLE hglobal)
{ LPSTR          cPtr;

  cPtr = GlobalLock(hglobal);
  GlobalUnlock(hglobal);
  return cPtr;
}

// Denne implementation ligner den originale (guienv...), og 
// den virker.
LPSTR DRAGDROPTextFromClipboard(HANDLE hTextMem)
{ LPSTR          lpText;
  LPSTR          TextStr;
  LPSTR          lpMyText;

  OpenClipboard( NULL );      
  // hTextMem = GetClipboardData( CF_TEXT );
  lpText = GlobalLock( hTextMem );
  lpMyText = malloc( GlobalSize (hTextMem) );
  lstrcpy( lpMyText, lpText );
  GlobalUnlock( hTextMem );
  CloseClipboard();
  return lpMyText;
}

//BOOL DRAGDROPTransferToClipBD( HANDLE hMemBlock, UINT FormatCB )
//{
//   if( OpenClipboard( NULL ) )
//   {
//      EmptyClipboard();
//      SetClipboardData( FormatCB, hMemBlock );
//      CloseClipboard();
//      return( TRUE );
//   }
//   return( FALSE );
//}

//BOOL DRAGDROPTextToClipboard( LPSTR Txt )
//{
//   int           i, wLen;     
//   GLOBALHANDLE  hGMem;
//   LPSTR         lpGMem;
//
//   wLen = strlen( Txt );
//   hGMem = GlobalAlloc( GHND, (DWORD) wLen + 1 );
//   lpGMem = GlobalLock( hGMem );
//   for( i=0; i<wLen; i++ ) *lpGMem++ = *Txt++;
//   GlobalUnlock( hGMem );
//   if( !TransferToClipBD( hGMem, CF_TEXT ) )
//      return( FALSE );
//   return( TRUE );
//}
