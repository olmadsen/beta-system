#include <Menus.h>
#include <Windows.h>
#include <Controls.h>
#include <TextEdit.h>
#include <Memory.h>
#include <Lists.h>
#include <StdIO.h>


long copyinput(long input)
{
	return input;
}

void SetMenubuttonMenu (ControlHandle control,MenuHandle menu,short menuID)
{
	PopupPrivateDataHandle data;
	data = (PopupPrivateDataHandle) (*control)->contrlData;
	InsertMenu(menu,-1);
	(*data)->mHandle = menu;
	(*data)->mID = menuID;
	SetCtlMax(control,CountMItems(menu));
	SetCtlMin(control,1);
	SetCtlValue(control,1);
}

void RemoveFromOwner (ControlHandle control)
{
	WindowPeek window;
	window = (WindowPeek) (*control)->contrlOwner;
	window->controlList = (*control)->nextControl;
}

void UpdateTextEditRecord (TEHandle teHandle,Rect *view,Rect *dest)
{
	(*teHandle)->destRect = (*dest);
	(*teHandle)->viewRect = (*view);
}

long TextEditGetLength (TEHandle teHandle)
{
	return (*teHandle)->teLength;
}

void CopyText (Handle h,Ptr buffer,Size count)
{
	BlockMove((*h),buffer,count);
}

long TextEditGetSelectionStart (TEHandle teHandle)
{
	return (*teHandle)->selStart;
}

long TextEditGetSelectionEnd (TEHandle teHandle)
{
	return (*teHandle)->selEnd;
}

void TextEditUpdateViewRect (TEHandle teHandle,Rect *view)
{
	(*teHandle)->viewRect = (*view);
}

long MAX(long a,long b)
{
	if(a > b)
		return a;
	else
		return b;
}

long MIN(long a,long b)
{
	if(a < b)
		return a;
	else
		return b;
}

void TextEditGetScrollvalues (TEHandle teHandle,long *hMax,long *h,long *vMax,long *v)
{
	long textHeight;
	long viewHeight;
	long textWidth;
	long viewWidth;
	
	viewHeight = ((*teHandle)->viewRect.bottom - (*teHandle)->viewRect.top);
	textHeight = TEGetHeight(0,32767,teHandle);
	if(((char*)*(*teHandle)->hText)[(*teHandle)->teLength-1] == 13)
	{
		textHeight += TEGetHeight((*teHandle)->nLines-1, (*teHandle)->nLines-1, teHandle);
	}
	(*vMax) = MAX(textHeight - viewHeight,0);
	
	viewWidth = ((*teHandle)->viewRect.right - (*teHandle)->viewRect.left);
	textWidth = ((*teHandle)->destRect.right - (*teHandle)->destRect.left);
	(*hMax) = MAX(textWidth - viewWidth,0);
	
	(*v) = MIN((*vMax),(*teHandle)->viewRect.top - (*teHandle)->destRect.top);
	(*h) = MIN((*hMax),(*teHandle)->viewRect.left - (*teHandle)->destRect.left);
	
}

void TextEditAdjustScroll (TEHandle teHandle,long h,long v)
{
	TEPtr		te;
	
	te = *teHandle;
	TEScroll((te->viewRect.left - te->destRect.left) - h,
			(te->viewRect.top - te->destRect.top) - v,
			teHandle);
}

void TextEditSetSelection (TEHandle teHandle,long start,long end)
{
	(*teHandle)->selStart = start;
	(*teHandle)->selEnd = end;
}

void TextEditGetSelection(TEHandle teHandle,long *start,long *end)
{
	(*start) = (*teHandle)->selStart;
	(*end) = (*teHandle)->selEnd;
}

long TextEditGetChar (TEHandle teHandle,long inx)
{
	return (long) ((char*)*(*teHandle)->hText)[inx];
}

long ScrollListGetNumberOfItems (ListHandle list)
{
	return (*list)->dataBounds.bottom;
}

void ScrollListSetItemHeight (ListHandle list,long height)
{
	Cell c;
	c.h = 2000;
	c.v = height;
	LCellSize(c,list);
}

long ScrollListGetItemHeight (ListHandle list)
{
	return (*list)->cellSize.v;
}

void ScrollListSetSingle (ListHandle list,long single)
{
	if(single == 1) {
		(*list)->selFlags = lOnlyOne;
	}
	else {
		(*list)->selFlags = 0;
	}
}

long ScrollListGetSingle (ListHandle list)
{
	if((*list)->selFlags == lOnlyOne) {
		return 1;
	}
	else {
		return 0;
	}
}

void ScrollListUpdate (ListHandle list)
{
	EraseRect(&(*list)->rView);
	LUpdate((*list)->port->visRgn,list);
}

void DrawBitMapInPort(BitMapHandle bitmap,GrafPtr port,Point from,Point to,long width,long height)
{
	Rect srcRect;
	Rect dstRect;
	
	SetRect(&srcRect,from.h,from.v,from.h + width,from.v + height);
	SetRect(&dstRect,to.h,to.v,to.h + width,to.v + height);
	CopyBits(*bitmap,&port->portBits,&srcRect,&dstRect,srcCopy,nil);
}

void EraseRectangle (short left, short top, short right, short bottom)
{
	Rect r;
	SetRect(&r, left, top, right, bottom);
	EraseRect(&r);
}
