#include <Quickdraw.h>
#include <TextEdit.h>
#include <Fonts.h>
#include <Dialogs.h>
#include <CursorCtl.h>
#include <Menus.h>
#include <Windows.h>
#include <SegLoad.h>
#include <StdLib.h>
#include <String.h>
#include <stdio.h>

#define GLOBAL(var) var

GLOBAL(static long gcRotateCursor)=0;
GLOBAL(static Boolean gcInbackground)=0;
GLOBAL(static long gcGiveTime)=0;

void GiveTime(void);

QDGlobals qd;
extern long StandAlone;
extern FILE *output;
extern 
#define CPromptID 7130


void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4)
{ 
  if (StandAlone){
    Str255 m1, m2, m3, m4;
    if (msg1) sprintf((char*)m1, "%c%s", strlen(msg1), msg1);
    if (msg2) sprintf((char*)m2, "%c%s", strlen(msg2), msg2);
    if (msg3) sprintf((char*)m3, "%c%s", strlen(msg3), msg3);
    if (msg4) sprintf((char*)m4, "%c%s", strlen(msg4), msg4);
    ParamText(m1, m2, m3, m4);
    Alert(CPromptID,0);
  } else {
    fprintf(output, "%s%s%s%s\n", msg1, msg2, msg3, msg4);
	fflush(output);
  }
}

void InitTheCursor(void)   
{ 
  
  if(StandAlone == 0 || gcRotateCursor) InitCursorCtl(0); 
  else {
    if (GetResource('acur', 0)) {
      InitCursorCtl(0); 
    }
  }
}

void RotateTheCursor() 
{
  if(StandAlone == 0 || gcRotateCursor) SpinCursor(32);
  if (gcGiveTime && StandAlone) {
    SpinCursor(32);
    GiveTime();
  }
}

void RotateTheCursorBack()
{ 
  if(StandAlone == 0 || gcRotateCursor) SpinCursor(-32);
  if (gcGiveTime && StandAlone) {
    SpinCursor(-32);
    GiveTime();
  }
}



void InitToolbox(void)
{
  InitGraf((Ptr) &qd.thePort);
  InitFonts();
  InitWindows();
  InitMenus();
  TEInit();
  InitDialogs(nil);
  InitCursor();
  InitTheCursor();
}


#include <ToolUtils.h>



void GiveTime(void)
{
  EventRecord   event;
  Boolean       gotEvent;
  WindowPtr     thisWindow;
  short         part;
  long          menuResult;
  short         menuID;
  short         menuItem;
  Str255        daName;
  short         daRefNum;
  
  gotEvent = WaitNextEvent(everyEvent, &event, 2, 0);
  if (gotEvent) {
    switch (event.what) {
    case mouseDown:
      part = FindWindow(event.where, &thisWindow);
      switch(part) {
      case inMenuBar:
        menuResult = MenuSelect(event.where);
        menuID = HiWord(menuResult);
        menuItem = LoWord(menuResult);
        switch(menuID) {
        case 128: /* Apple Menu */
          switch(menuItem) {
          case 1:
            break;
          default:
            GetMenuItemText(GetMenuHandle(128), menuItem, daName);
            daRefNum = OpenDeskAcc(daName);
            break;
          }
          break;
        }
        break;
      case inSysWindow:
        SystemClick(&event, thisWindow);
        break;
      case inContent:
        break;
      case inDrag:
        break;
      case inGrow:
        break;
      case inGoAway:
        break;
      case inZoomIn:
        break;
      case inZoomOut:
        break;
      }
      break;
    case mouseUp:
      break;
    case keyDown:
    case autoKey:
      break;
    case activateEvt:
      break;
    case updateEvt:
      thisWindow = (WindowPtr) event.message;
      BeginUpdate(thisWindow);
      EndUpdate(thisWindow);
      break;
    case diskEvt:
      break;
    osEvt:
      break;
    kHighLevelEvent:
      break;
    }
  }
  return;
}




void StartGiveTime(void)
{   
  gcGiveTime=1;
#if defined(Mac)
  gcInbackground = 0;
#endif
  return;
}

void StopGiveTime(void)
{  
  gcGiveTime=0;
  return;
}


