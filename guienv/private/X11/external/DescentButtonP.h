typedef struct _XbDescentButtonClassPart {
  int ignore;    /* to satisfy the compiler */
} XbDescentButtonClassPart;

typedef struct _XbDescentButtonClassRec {
  CoreClassPart             core_class;
  XbButtonClassPart	    button_class;
  XbDescentButtonClassPart  descentButton_class;
} XbDescentButtonClassRec;

extern XbDescentButtonClassRec xbDescentButtonClassRec;


typedef struct _XbDescentButtonPart {
  int ignore;    /* to satisfy the compiler */
} XbDescentButtonPart;

typedef struct _XbDescentButtonRec {
  CorePart              core;
  XbButtonPart		button;
  XbDescentButtonPart   descentButton;
} XbDescentButtonRec;
