#ifndef _DEF_LiteClueP_h
#define _DEF_LiteClueP_h

#include <X11/ShellP.h>
/* Include public header file for this widget. */
#ifndef __VMS
# include "LiteClue.h"
#else
# include "LiteClue.h"
#endif
    
/* Doubly Linked List Processing */
struct list_thread_str
{
	struct list_thread_str * forw;	/* next pointer */
	struct list_thread_str * back;	/* prev pointer */
};
typedef struct list_thread_str  ListThread; 


typedef struct {
	int	nothing;	/* place holder */
} LiteClueClassPart;

/* Full class record declaration */
typedef struct _LiteClueClassRec {
	CoreClassPart	core_class;
	CompositeClassPart  composite_class;
	ShellClassPart  shell_class;
	OverrideShellClassPart  override_shell_class;
	LiteClueClassPart	LiteClue_class;
} LiteClueClassRec;

extern LiteClueClassRec xcgLiteClueClassRec;

/* New fields for the LiteClue widget record */
typedef struct {
	/* resources */
	Pixel foreground;

#if XtSpecificationRelease < 5
	XFontStruct *font;	/* the font for text in box */
#else
	XFontSet fontset;	/* the font for text in box */
#endif
        int  waitPeriod;	/* the delay resource - pointer must be
				   in watched widget this long before
				   help is poped - in millisecs
				*/
        int  cancelWaitPeriod;	/* after help is popped-down - normal
				   wait period is cancelled for this
				   period - in millisecs
				*/

	/* -------- private state --------- */
	ListThread widget_list; 	/* list of widgets we are liteClue-ing */
	Dimension font_width;	/* width of '1' character */
	Dimension font_height;	/* height of font, rows are spaced using this */
	Dimension font_baseline;	/* relative displacement to baseline from top */
	GC text_GC;		/* for drawing text */
	XtIntervalId interval_id;	/* New field, holds timer id */
	Boolean	HelpIsUp;	/* the help is popup is up */
	Time	HelpPopDownTime;	/* the time at which help popup was popped down */
} LiteCluePart;


/*
 * Full instance record declaration
 */
typedef struct _LiteClueRec {
	CorePart		core;
	CompositePart  composite;
	ShellPart 	shell;
	OverrideShellPart override;
	LiteCluePart	liteClue;
} LiteClueRec;


#endif /* _DEF_LiteClueP_h */

