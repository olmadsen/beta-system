/* */
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>

int ConfigDataSource (HWND hwndParent, WORD fRequest, LPCSTR lpszDriver, LPCSTR lpszAttributes) {
  BOOL res;
  res = SQLConfigDataSource(hwndParent, fRequest, lpszDriver, lpszAttributes);
  return res;
}
