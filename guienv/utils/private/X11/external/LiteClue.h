#define XgcNcancelWaitPeriod	 "cancelWaitPeriod"
#define XgcNwaitPeriod	 "waitPeriod"
/*
 * New resource classes
 */
#define XgcCCancelWaitPeriod	"cancelWaitPeriod"
#define XgcCWaitPeriod	"WaitPeriod"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" { 
#endif

extern WidgetClass xcgLiteClueWidgetClass; 
typedef struct _LiteClueClassRec *XcgLiteClueWidgetClass;
typedef struct _LiteClueRec      *XcgLiteClueWidget;
void XcgLiteClueAddWidget(Widget w, Widget watch,  char * text, int size, int option );
void XcgLiteClueDeleteWidget(Widget w, Widget watch);
void XcgLiteClueSetSensitive(Widget w, Widget watch, Boolean sensitive);
Boolean XcgLiteClueGetSensitive(Widget w, Widget watch);
Boolean XcgLiteClueDispatchEvent(Widget w, XEvent  *event);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

