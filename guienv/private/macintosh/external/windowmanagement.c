#include <Windows.h>
#include <Types.h>
#include <LowMem.h>		// dkj replaced SysEqu.h
#include <OsUtils.h>


#define DialogKind 2
#define kApplicationFloaterKind 7
#define NormalKind 8

void SetWindowMaxSize (WindowPeek theWindow, long width, long height);

void ActivateWindow (WindowPtr theWindow);
void DeactivateWindow (WindowPtr theWindow);
WindowPtr GetNextVisibleWindow (WindowPtr theWindow);
void SetTheWindowKind (WindowPtr WindowPtrerence, short kind);
RgnHandle GetContentRegion(WindowPtr WindowPtrerence);
WindowPtr GetWindowList(void);
void SetWindowList(WindowPtr WindowPtrerence);
Boolean GetWindowHilite(WindowPtr WindowPtrerence);
pascal void SetWindowHilite(WindowPtr WindowPtrerence, Boolean windowHilite);
Boolean WindowIsModal(WindowPtr WindowPtrerence);
void SetWindowBackground (WindowPtr theWindow, short red, short green, short blue);
WindowPtr FrontNonFloatingWindow(void);
WindowPtr  LastFloatingWindow(void);
WindowPtr SelectTheWindow (WindowPtr theWindow);
void DragTheWindow (WindowPtr windowToDrag, Point startPoint, const Rect *draggingBounds);
void HideTheWindow (WindowPtr windowToHide);
void ShowTheWindow(WindowPtr windowToShow);



void SetWindowMaxSize (WindowPeek theWindow, long width, long height)
{
	WStateDataHandle state;
	Rect zoomRect;
	
	state = (WStateDataHandle) theWindow->dataHandle;
	if (state != nil) {
		if ((width > 0) && (height > 0)) {
			zoomRect = qd.screenBits.bounds;
			zoomRect.left = zoomRect.left + 4;
			zoomRect.top = zoomRect.top + 40;

			if (zoomRect.bottom - zoomRect.top > height)
				zoomRect.bottom = zoomRect.top + height;
			if(zoomRect.right - zoomRect.left > width)
				zoomRect.right = zoomRect.left + width;
			(*state)->stdState = zoomRect;
		}
	}
	return;
}


void ActivateWindow (WindowPtr theWindow)
{
	HiliteWindow(theWindow, true);
	LMSetCurActivate(theWindow);
}

void DeactivateWindow (WindowPtr theWindow)
{	
	HiliteWindow(theWindow, false);
	LMSetCurDeactive(theWindow);
}


WindowPtr GetNextVisibleWindow (WindowPtr theWindow)
{
	do {
		theWindow = GetNextWindow(theWindow);
	} while ((theWindow != nil) && (IsWindowVisible(theWindow) == false));
	
}


void SetTheWindowKind (WindowPtr WindowPtrerence, short kind)
{
	SetWindowKind(WindowPtrerence, kind);
}

RgnHandle GetContentRegion(WindowPtr WindowPtrerence)
{
	return (((WindowPeek) WindowPtrerence)->contRgn);
}


WindowPtr GetWindowList(void)
{
	return (LMGetWindowList());
}

// SetWindowList — Set the first window in this process’ window list.

void SetWindowList(WindowPtr WindowPtrerence)
{
	LMSetWindowList(WindowPtrerence);
}

// Get/SetWindowHilite — get and set the hilited field of a window

Boolean GetWindowHilite(WindowPtr WindowPtrerence)
{
	return (((WindowPeek) WindowPtrerence)->hilited);
}

pascal void SetWindowHilite(WindowPtr WindowPtrerence, Boolean windowHilite)
{
	((WindowPeek) WindowPtrerence)->hilited = windowHilite;
}



Boolean WindowIsModal(WindowPtr WindowPtrerence)
{
	short	windowVariant;
	
	windowVariant = GetWVariant((WindowPtr) WindowPtrerence);
	if ((GetWindowKind(WindowPtrerence) == DialogKind) &&
		((windowVariant == dBoxProc) ||
		(windowVariant == movableDBoxProc)))
		return true;
	else
		return false;
}


void SetWindowBackground (WindowPtr theWindow, short red, short green, short blue)
{
	WCTabHandle ctab;
	
	ctab = (WCTabHandle) NewHandleClear(sizeof(WinCTab));
	
	(**ctab).ctSize = 0;
	(**ctab).ctTable[0].value = wContentColor;
	(**ctab).ctTable[0].rgb.red = red;
	(**ctab).ctTable[0].rgb.green = green;
	(**ctab).ctTable[0].rgb.blue = blue;
	
	SetWinColor(theWindow, ctab);
}

WindowPtr FrontNonFloatingWindow(void)
{
	WindowPtr	theWindow;
	
	// Get the first visible window in the window list.
	
	theWindow = FrontWindow();
	
	// Keep searching until a visible window whose windowKind is not
	// kApplicationkApplicationFloaterKind is found, or the end of the window list is reached.
	
	while ((theWindow != nil) && (GetWindowKind(theWindow) == kApplicationFloaterKind)) {
		do {
			theWindow = GetNextWindow(theWindow);
		} while ((theWindow != nil) && (IsWindowVisible(theWindow) == false));
	}

	return theWindow;
}

WindowPtr  LastFloatingWindow(void)
{
	WindowPtr	theWindow;
	WindowPtr	lastFloatingWindow;
	
	theWindow = GetWindowList();
	lastFloatingWindow = nil;
	
	// We have to search the entire window list because we don’t know what the windowKind
	// of other windows in the list might be, and we have account for the fact that a modal
	// dialog is up.
	
	while (theWindow != nil) {
		if (GetWindowKind(theWindow) == kApplicationFloaterKind)
			lastFloatingWindow = theWindow;
		theWindow = GetNextWindow(theWindow);
	}
	
	return lastFloatingWindow;
}

WindowPtr SelectTheWindow (WindowPtr theWindow)
{
	short kind = 0;
	WindowPtr currentFrontWindow = nil;
	WindowPtr lastFloatingWindow = nil;
	
	kind = GetWindowKind(theWindow);
	switch (kind) {
		case DialogKind:
			break;
		case kApplicationFloaterKind:
			BringToFront(theWindow);
			break;
		case NormalKind:
			currentFrontWindow = FrontNonFloatingWindow();
			if(theWindow != currentFrontWindow) {
				DeactivateWindow(currentFrontWindow);
				lastFloatingWindow = LastFloatingWindow();
				if (lastFloatingWindow == nil) {
					BringToFront(theWindow);
				} else {
					SendBehind(theWindow, lastFloatingWindow);
				}
				ActivateWindow(theWindow);
			}
			break;
	}
	
	return currentFrontWindow;
}

void DragTheWindow (WindowPtr windowToDrag, Point startPoint, const Rect *draggingBounds)
{
	Rect		dragRect;
	KeyMap		keyMap;
	GrafPtr		savePort;
	GrafPtr		windowManagerPort;
	RgnHandle	dragRegion;
	RgnHandle	windowContentRegion;
	long		dragResult;
	short		topLimit;
	short		newHorizontalWindowPosition;
	short		newVerticalWindowPosition;
	short		horizontalOffset;
	short		verticalOffset;
	Boolean		commandKeyDown = false;
	
	if (WaitMouseUp()) {
	
	// Adjust the top of the dragging rectangle so that it’s below the menu bar
	
		topLimit = GetMBarHeight() + 4;
		dragRect = *draggingBounds;
		if (dragRect.top < topLimit)
			dragRect.top = topLimit;
	
	// Set up the Window Manager port.
	
		GetPort(&savePort);
		GetWMgrPort(&windowManagerPort);
		SetPort(windowManagerPort);
		SetClip(GetGrayRgn());
		
	// Check to see if the command key is down.  If it is, don’t bring the window to the
	// front after the move.  Trying to do Pascal stuff in C is so much fun.  GetKeys()
	// is a total pain to try to use properly from C, so I’m going to hard code where the
	// command key is in the KeyMap array.
	
		GetKeys(keyMap);
		if (keyMap[1] & 0x8000)
			commandKeyDown = true;
	
		if ((commandKeyDown == true) ||
			(GetWindowKind(windowToDrag) != kApplicationFloaterKind)) {
			
			if (commandKeyDown == false)
	
	// If there are floating windows, clip the dragging outline to draw behind the floaters.
	
				ClipAbove(FrontNonFloatingWindow());
			else
			
	// If the command key was down, clip the outline to draw behind any windows above
	// the window being dragged.
	
				ClipAbove(windowToDrag);
		}
			
	// Create a region to drag
	
		dragRegion = NewRgn();
		GetWindowStructureRgn(windowToDrag, dragRegion);
		
	// Drag the window around
	
		dragResult = DragGrayRgn(dragRegion, startPoint, &dragRect, &dragRect, noConstraint, nil);
	
	// Restore the port for coordinate conversion.
	
		SetPort(savePort);

		if (dragResult != 0) {
			horizontalOffset = dragResult & 0xFFFF;
			verticalOffset = dragResult >> 16;
	
	// Only move it if it stayed inside the dragging box.
	
			if (verticalOffset != -32768) {
				windowContentRegion = GetContentRegion(windowToDrag);
				newHorizontalWindowPosition = (**windowContentRegion).rgnBBox.left + horizontalOffset;
				newVerticalWindowPosition = (**windowContentRegion).rgnBBox.top + verticalOffset;
				
				MoveWindow((WindowPtr) windowToDrag, newHorizontalWindowPosition, newVerticalWindowPosition, false);
				
			}
		}
	
	// Bring the window forward if the command key wasn’t down
	
		if (commandKeyDown == false)
			SelectTheWindow(windowToDrag);
	
	// Get rid of the dragging region
	
		DisposeRgn(dragRegion);
	}
}

void HideTheWindow (WindowPtr windowToHide)
{
	WindowPtr			frontNonFloater;
	WindowPtr			lastFloater;
	WindowPtr			windowBehind;
	
	// Don’t do anything if the window is already invisible.
	
	if (IsWindowVisible(windowToHide) == false)
		return;
				
	// Get the first visible document window, if any.
	
	frontNonFloater = FrontNonFloatingWindow();
	
	// Hide the Window
	
	ShowHide(windowToHide, false);
	
	// Send it behind all other windows
	
	
	
	
	if (windowToHide == frontNonFloater) {
		windowBehind = GetNextVisibleWindow(windowToHide);
		if (windowBehind != nil) {
			ActivateWindow(windowBehind);
		}
	}
	
	SendBehind(windowToHide, nil);
}


void ShowTheWindow(WindowPtr windowToShow)
{
	WindowPtr			windowBehind;
	WindowPtr			frontNonFloatingWindow;
	WindowPtr			lastFloatingWindow;
	short				windowClass;
	Boolean				windowIsInFront = false;
	
	if (IsWindowVisible(windowToShow) != false)
		return;
		
	windowClass = GetWindowKind(windowToShow);
	
	// Bring the window to the front before showing it
	
	switch (windowClass) {
		case kApplicationFloaterKind:
			BringToFront(windowToShow);
			break;
		case NormalKind:
		case DialogKind:

			lastFloatingWindow = LastFloatingWindow();
			
			if (lastFloatingWindow != nil) {
				SendBehind(windowToShow, lastFloatingWindow);
			} else {
				BringToFront(windowToShow);
			}
			break;
	}
	
	// If the window behind the window to show is currently the frontmost document window,
	// unhighlight it, and highlight the new front window.
	
	if (windowClass != kApplicationFloaterKind) {
		windowBehind = GetNextVisibleWindow(windowToShow);
		
		if (windowBehind == FrontNonFloatingWindow()) {
			if (windowBehind != nil)
				DeactivateWindow(windowBehind);

	// Set the highlight state so the window appears highlighted from the start.
	
			SetWindowHilite(windowToShow, true);
			windowIsInFront = true;
		}
	}
	else {
	
	// A floating window is about to be shown. Make sure the windows in the window list
	// are all in the right place.
	
    // ValidateWindowList();
		
	// Check to see if a modal window is up before trying to highlight it.
	
		SetWindowHilite(windowToShow, false);
		windowIsInFront = true;	
	
		frontNonFloatingWindow = FrontNonFloatingWindow();
		if ((frontNonFloatingWindow != nil) &&
			(frontNonFloatingWindow == (WindowPtr) FrontWindow()) &&
			(WindowIsModal(frontNonFloatingWindow)))
			SetWindowHilite(windowToShow, false);
		else {
			SetWindowHilite(windowToShow, false);
			windowIsInFront = true;
		}
	}
	
	// Show the window
	
	ShowHide((WindowPtr) windowToShow, true);
	
	if (windowIsInFront) {
		LMSetCurActivate(windowToShow);
	}
}