extern "C" HRESULT CreateObject(LPOLESTR pszProgID, IDispatch FAR* FAR* ppdisp);
extern "C" HRESULT 
Invoke(LPDISPATCH pdisp, 
    WORD wFlags,
    LPVARIANT pvRet,
    EXCEPINFO FAR* pexcepinfo,
    UINT FAR* pnArgErr, 
    LPOLESTR pszName,
    LPCTSTR pszFmt, 
    ...);

extern "C" void ErrorMessage2(const char*, HRESULT );
