typedef struct _XbToggleButtonClassPart {
  int ignore;    /* to satisfy the compiler */
} XbToggleButtonClassPart;

typedef struct _XbToggleButtonClassRec {
  CoreClassPart             core_class;
  XbButtonClassPart	    button_class;
  XbToggleButtonClassPart   toggleButton_class;
} XbToggleButtonClassRec;

extern XbToggleButtonClassRec xbToggleButtonClassRec;


typedef struct _XbToggleButtonPart {
  Boolean indicatorOn;
} XbToggleButtonPart;

typedef struct _XbToggleButtonRec {
  CorePart              core;
  XbButtonPart		button;
  XbToggleButtonPart	toggleButton;
} XbToggleButtonRec;
