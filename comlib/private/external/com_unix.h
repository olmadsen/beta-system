/* Dummy functions allowing linking of COM programs on
 * UNIX. Most of the functions should NOT be called!
 */

extern char *machine_type(void);

#define E_FAIL 0x80004005

typedef unsigned long HRESULT;

typedef struct _GUID
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;

typedef GUID IID;
typedef GUID CLSID;

typedef unsigned short *BSTR;

extern HRESULT Unimplemented (char *name);
extern void ComErrorMessage(const char* str, HRESULT hr);
extern HRESULT CoInitialize(void *LPVoid);
extern void CoUninitialize(void);
extern HRESULT CLSIDFromProgID(BSTR *progid, CLSID **clsid); 
extern HRESULT CoCreateInstance(CLSID *rclsid, 
			 void *pUnkOuter,
			 unsigned long dwClsContext, 
			 IID *riid,
			 void **ppv);
extern HRESULT RegisterActiveObject(void *pUnk, CLSID *rclsid, long flags, unsigned reg); 
