#include <X11/Intrinsic.h>
#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/CoreP.h>
#include "ButtonP.h"
#include "Button.h"
#include "DescentButtonP.h"
#include "DescentButton.h"


XbDescentButtonClassRec xbDescentButtonClassRec = {
    /* CoreClassPart */
  {
    (WidgetClass) &widgetClassRec,       /* superclass               */
    "DescentButton",			 /* class_name		     */
    sizeof(XbDescentButtonRec),		 /* widget_size		     */
    NULL,				 /* class_initialize	     */
    NULL,				 /* class_part_initialize    */
    FALSE,				 /* class_inited	     */
    NULL,				 /* initialize		     */
    NULL,				 /* initialize_hook	     */
    XtInheritRealize,			 /* realize		     */
    NULL,				 /* actions		     */
    0,					 /* num_actions		     */
    NULL,				 /* resources		     */
    0,					 /* num_resources	     */
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
    /* DescentButtonClassPart */
  {
    0,					/* ignore 		     */
  }
};

WidgetClass xbDescentButtonWidgetClass = (WidgetClass) &xbDescentButtonClassRec;

long getXbDescentButtonWidgetClass(){return ( (long) xbDescentButtonWidgetClass);}
