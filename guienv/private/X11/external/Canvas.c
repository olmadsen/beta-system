#ifdef sun4
#define MOTIF12
#endif

#ifdef sun4s
#define MOTIF12
#endif

#ifdef hpux9pa
#define MOTIF12
#endif

#ifdef linux
#define MOTIF12
#endif

#include <stdio.h>
#include <X11/IntrinsicP.h>
#include <X11/Intrinsic.h>
#include <X11/CompositeP.h>
#include <X11/Composite.h>
#include <Xm/Xm.h>
#include <Xm/XmP.h>
#ifdef MOTIF12
#include <Xm/ManagerP.h>
#endif
#include "CanvasP.h"
#include "Canvas.h"

Bool answer = False;

void SetAnswer(Bool value)
{
  answer = value;
}

static void Initialize();
static XtGeometryResult GeometryManager();
static void DrawCanvas();

XbCanvasClassRec xbCanvasClassRec = {
  {
    /* core class members */
    (WidgetClass) &xmManagerClassRec, /* superclass */
    "Canvas",                          /* class_name */
    sizeof(XbCanvasRec),               /* widget_size */
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
    XtInheritExpose,                  /* expose */
    NULL,			      /* set_values */
    NULL,			      /* set_values_hook */
    XtInheritSetValuesAlmost,	      /* set_values_almost */
    NULL,			      /* get_values_hook */
    NULL,			      /* accept_focus */
    XtVersion,			      /* version */
    NULL,			      /* callback_private */
    XtInheritTranslations,            /* tm_table              */
    NULL,                             /* query_geometry        */
    NULL,                             /* display_accelerator   */
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
    /* constraint_class members */
    NULL,                             /* subresources */
    0,                                /* subresources_count */
    sizeof(XmManagerConstraintRec),   /* constraint_size */
    NULL,                             /* initialize constraints */
    NULL,                             /* destroy */
    NULL,                             /* set_values */
    NULL,                             /* extension */
  },
  {
    /* manager_class members */
    XtInheritTranslations,		     	      /* translations */
    NULL,
    0,
    NULL,
    0,
    XmInheritParentProcess,
    NULL,
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
  if (answer) {
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
  else {
    return (XtGeometryNo);
  }
}

static void DrawCanvas(XbCanvasWidget canvas,XEvent *event,Region region)
{
}

long getXbCanvasWidgetClass(){return ( (long) xbCanvasWidgetClass);}
