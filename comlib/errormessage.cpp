#include <stdlib.h>
#include <iostream.h>
#include <assert.h>
#include <objbase.h>

//
// Print out the COM/OLE error string for an HRESULT.
//
extern "C" void ComErrorMessage(const char* str, HRESULT hr);

void ComErrorMessage(const char* str, HRESULT hr)

{
	void* pMsgBuf ;
 
	::FormatMessage( 
		 FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		 NULL,
		 hr,
		 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		 (LPTSTR) &pMsgBuf,
		 0,
		 NULL 
	) ;

	// Display the string.
	cout << str << "\r\n" ;
	cout << "Error (" << hex << hr << "):  " 
	     << (char*)pMsgBuf << endl ;

	// Free the buffer.
	LocalFree( pMsgBuf ) ;

}
