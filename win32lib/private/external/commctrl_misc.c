#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

/* Microsoft Development Library.  
// SetView - sets a list view's window style to change the view. 
// hwndLV - handle of the list view control 
// dwView - value specifying a view style */
 
void SetView(HWND hWndListView, DWORD dwView) 
{ DWORD dwStyle;
  dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
  
  if ((dwStyle & LVS_TYPEMASK) != dwView) 
    SetWindowLong(hWndListView, GWL_STYLE,
		  (dwStyle & ~LVS_TYPEMASK) | dwView); 
} 

void getDispInfo(LPARAM lParam, LV_DISPINFO * pLvdi)
{
  pLvdi = (LV_DISPINFO *)lParam;

}

int sizeOf_TBBUTTON()
{
  return sizeof(TBBUTTON);
}
