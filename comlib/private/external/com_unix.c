/* Dummy functions allowing linking of COM programs on
 * UNIX. Most of the functions should NOT be called!
 */

#include <stdio.h>
#include "com_unix.h"

HRESULT Unimplemented (char *name)
{
  fprintf(stdout, 
	  "Warning: you have called \"%s\" which is unimplemented on %s\n",
	  name,
	  machine_type());
  return E_FAIL;
}

void ComErrorMessage(const char* str, HRESULT hr)
{
  fprintf(stdout, "COM error: %s; HRESULT is 0x%08x\n", str, hr);
}

HRESULT CoInitialize(void *LPVoid)
{
  return Unimplemented("CoInitialize");
}

void CoUninitialize(void)
{
  Unimplemented("CoUninitialize");
}

HRESULT CLSIDFromProgID(BSTR *progid, CLSID **clsid) 
{
  *clsid=NULL;
  return Unimplemented("CLSIDFromProgID");
}

HRESULT CoCreateInstance(CLSID *rclsid, 
			 void *pUnkOuter,
			 unsigned long dwClsContext, 
			 IID *riid,
			 void **ppv)
{
  *ppv=NULL;
  return Unimplemented("CoCreateInstance");
}


HRESULT RegisterActiveObject(void *pUnk, CLSID *rclsid, long flags, unsigned reg) 
{
  return Unimplemented("RegisterActiveObject");
}

