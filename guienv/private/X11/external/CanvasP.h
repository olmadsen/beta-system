typedef struct _XbCanvasClassPart {
  int empty;
} XbCanvasClassPart;

typedef struct _XbCanvasClassRec {
  CoreClassPart core_class;
  CompositeClassPart composite_class;
  XbCanvasClassPart canvas_class;
} XbCanvasClassRec;

extern XbCanvasClassRec xbCanvasClassRec;

typedef struct _XbCanvasPart {
  int empty;
} XbCanvasPart;

typedef struct _XbCanvasRec {
  CorePart core;
  CompositePart composite;
  XbCanvasPart canvas;
} XbCanvasRec;
