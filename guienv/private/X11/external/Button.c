#include <stdio.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/CoreP.h>
#include <Xm/Xm.h>
#include "ButtonP.h"
#include "Button.h"

static Boolean SetValues();
static void Initialize();
static void GetValuesHook();
static void ExposeMethod();

static XtResource resources[] = {
  {XmNfontList,XmCFontList,XmRFontList,sizeof(XmFontList),
     XtOffset(XbButtonWidget,button.fontList),XmRString,XmSTRING_DEFAULT_CHARSET},
  {XmNlabelString,XmCXmString,XmRXmString,sizeof(XmString),
     XtOffset(XbButtonWidget,button.labelString),XmRString,"Hejsan"},
};

XbButtonClassRec xbButtonClassRec = {
    /* CoreClassPart */
  {
    (WidgetClass) &widgetClassRec,       /* superclass               */
    "Button",				 /* class_name		     */
    sizeof(XbButtonRec),		 /* widget_size		     */
    NULL,				 /* class_initialize	     */
    NULL,				 /* class_part_initialize    */
    FALSE,				 /* class_inited	     */
    Initialize,				 /* initialize		     */
    NULL,				 /* initialize_hook	     */
    XtInheritRealize,			 /* realize		     */
    NULL,				 /* actions		     */
    0,					 /* num_actions		     */
    resources,				 /* resources		     */
    XtNumber(resources),		 /* num_resources	     */
    NULLQUARK,				 /* xrm_class		     */
    TRUE,				 /* compress_motion	     */
    TRUE,				 /* compress_exposure	     */
    TRUE,				 /* compress_enterleave	     */
    FALSE,				 /* visible_interest	     */
    NULL,				 /* destroy		     */
    XtInheritResize,			 /* resize		     */
    ExposeMethod,			 /* expose		     */
    SetValues,				 /* set_values		     */
    NULL,				 /* set_values_hook	     */
    XtInheritSetValuesAlmost,		 /* set_values_almost	     */
    GetValuesHook,			 /* get_values_hook	     */
    NULL,				 /* accept_focus	     */
    XtVersion,				 /* version		     */
    NULL,				 /* callback_private	     */
    NULL,				 /* extension		     */
  },
    /* ButtonClassPart */
  {
    0,					/* ignore 		     */
  }
};

WidgetClass xbButtonWidgetClass = (WidgetClass) &xbButtonClassRec;

long getXbButtonWidgetClass(){return ( (long) xbButtonWidgetClass);}

static Boolean SetValues(XbButtonWidget current,
			 XbButtonWidget request,
			 XbButtonWidget new) {
  if (current->button.labelString != new->button.labelString) {
    new->button.labelString = XmStringCopy(new->button.labelString);
  }
  return FALSE;
}

static void Initialize(XbButtonWidget request,XbButtonWidget new) {
  
}

static void GetValuesHook(XbButtonWidget w, ArgList args,Cardinal *nargs) {
  Cardinal i = 0;
  String key = "labelString";

  while (i != *nargs) {
    if(strcmp(args[i].name,key) == 0) {
      *(long*)args[i].value = (long) XmStringCopy( *(XmString*) (args[i].value));
      break;
    }
    i++;
  }
}


static void ExposeMethod(XbButtonWidget w,XExposeEvent event)
{

}
