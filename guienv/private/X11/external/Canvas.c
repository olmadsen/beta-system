#include <stdio.h>
#include <X11/IntrinsicP.h>
#include <X11/Intrinsic.h>
#include <X11/CompositeP.h>
#include <X11/Composite.h>
#include "CanvasP.h"
#include "Canvas.h"


static void Initialize();
static XtGeometryResult GeometryManager();

XbCanvasClassRec xbCanvasClassRec = {
  {
    /* core class members */
    (WidgetClass) &compositeClassRec, /* superclass */
    "Canvas",                         /* class_name */
    sizeof(XbCanvasRec),              /* widget_size */
    NULL,                             /* class_initialize */
    NULL,                             /* class_part_init */
    FALSE,                            /* class_inited */
    Initialize,                       /* initialize */
    NULL,                             /* initialize_hook */
    XtInheritRealize,                 /* realize */
    NULL,                             /* actions */
    0,                                /* num_actions */
    NULL,                             /* resources */
    0,                                /* num_resources */
    NULLQUARK,                        /* xrm_class */
    TRUE,                             /* compress_motion */
    TRUE,                             /* compress_exposure */
    TRUE,                             /* compress_enterleave */
    FALSE,                            /* visible_interest */
    NULL,                             /* destroy */
    XtInheritResize,                  /* resize */
    NULL,                             /* expose */
    NULL,			      /* set_values */
    NULL,			      /* set_values_hook */
    XtInheritSetValuesAlmost,	      /* set_values_almost */
    NULL,			      /* get_values_hook */
    NULL,			      /* accept_focus */
    XtVersion,			      /* version */
    NULL,			      /* callback_private */
    NULL,			      /* extension */
  },
  {
    /* composite_class members */
    GeometryManager,                  /* geometry_manager */
    XtInheritChangeManaged,	      /* changed_managed */
    XtInheritInsertChild,	      /* insert_child */
    XtInheritDeleteChild,	      /* delete_child */
    NULL,			      /* extension */
  },
  {
    /* canvas_class members */
    0,                                /* empty */
  }
};

WidgetClass xbCanvasWidgetClass = (WidgetClass) &xbCanvasClassRec;


static void Initialize(XbCanvasWidget request,XbCanvasWidget new) {
  if (request->core.width <= 0)
    new->core.width = 5;
  if (request->core.height <= 0)
    new->core.height = 5;
}

static XtGeometryResult GeometryManager(Widget w,
					XtWidgetGeometry *request,
					XtWidgetGeometry *reply) 
{
  
    if(request->request_mode & CWX)
      w->core.x = request->x;
    if(request->request_mode & CWY)
      w->core.y = request->y;
    if(request->request_mode & CWWidth)
      w->core.width = request->width;
    if(request->request_mode & CWHeight)
      w->core.height = request->height;
    if(request->request_mode & CWBorderWidth)
      w->core.border_width = request->border_width;
    return (XtGeometryYes);
}

long getXbCanvasWidgetClass(){return ( (long) xbCanvasWidgetClass);}
