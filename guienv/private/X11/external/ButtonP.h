#include <Xm/Xm.h>

typedef struct _XbButtonClassPart {
  int ignore;    /* to satisfy the compiler */
} XbButtonClassPart;

typedef struct _XbButtonClassRec {
  CoreClassPart      core_class;
  XbButtonClassPart  button_class;
} XbButtonClassRec;

extern XbButtonClassRec xbButtonClassRec;


typedef struct _XbButtonPart {
  XmFontList fontList;
  XmString labelString;
} XbButtonPart;

typedef struct _XbButtonRec {
  CorePart     core;
  XbButtonPart   button;
} XbButtonRec;
