#include <X11/Intrinsic.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/CoreP.h>
#include "ButtonP.h"
#include "Button.h"
#include "ToggleButtonP.h"
#include "ToggleButton.h"

static XtResource resources[] = {
  {XmNindicatorOn,XmCIndicatorOn,XmRBoolean,sizeof(Boolean),
     XtOffset(XbToggleButtonWidget,toggleButton.indicatorOn),XmRString,"False"},
};


XbToggleButtonClassRec xbToggleButtonClassRec = {
    /* CoreClassPart */
  {
    (WidgetClass) &xbButtonClassRec,       /* superclass               */
    "ToggleButton",			 /* class_name		     */
    sizeof(XbToggleButtonRec),		 /* widget_size		     */
    NULL,				 /* class_initialize	     */
    NULL,				 /* class_part_initialize    */
    FALSE,				 /* class_inited	     */
    NULL,				 /* initialize		     */
    NULL,				 /* initialize_hook	     */
    XtInheritRealize,			 /* realize		     */
    NULL,				 /* actions		     */
    0,					 /* num_actions		     */
    resources,				 /* resources		     */
    1,					 /* num_resources	     */
    NULLQUARK,				 /* xrm_class		     */
    TRUE,				 /* compress_motion	     */
    TRUE,				 /* compress_exposure	     */
    TRUE,				 /* compress_enterleave	     */
    FALSE,				 /* visible_interest	     */
    NULL,				 /* destroy		     */
    XtInheritResize,			 /* resize		     */
    NULL,				 /* expose		     */
    NULL,				 /* set_values		     */
    NULL,				 /* set_values_hook	     */
    XtInheritSetValuesAlmost,		 /* set_values_almost	     */
    NULL,				 /* get_values_hook	     */
    NULL,				 /* accept_focus	     */
    XtVersion,				 /* version		     */
    NULL,				 /* callback_private	     */
    NULL,				 /* extension		     */
  },
    /* ButtonClassPart */
  {
    0,					/* ignore		     */
  },
    /* ToggleButtonClassPart */
  {
    0,					/* ignore 		     */
  }
};

WidgetClass xbToggleButtonWidgetClass = (WidgetClass) &xbToggleButtonClassRec;

long getXbToggleButtonWidgetClass(){return ( (long) xbToggleButtonWidgetClass);}
