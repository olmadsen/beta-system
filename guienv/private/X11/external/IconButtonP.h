typedef struct _XbIconButtonClassPart {
  int ignore;    /* to satisfy the compiler */
} XbIconButtonClassPart;

typedef struct _XbIconButtonClassRec {
  CoreClassPart             core_class;
  XbButtonClassPart	    button_class;
  XbIconButtonClassPart	    iconButton_class;
} XbIconButtonClassRec;

extern XbIconButtonClassRec xbIconButtonClassRec;


typedef struct _XbIconButtonPart {
  Boolean    showLabel;
} XbIconButtonPart;

typedef struct _XbIconButtonRec {
  CorePart              core;
  XbButtonPart		button;
  XbIconButtonPart	iconButton;
} XbIconButtonRec;
