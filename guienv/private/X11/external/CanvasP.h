typedef struct _XbCanvasClassPart {
  int empty;
} XbCanvasClassPart;

typedef struct _XbCanvasClassRec {
  CoreClassPart core_class;
  CompositeClassPart composite_class;
  ConstraintClassPart constraint_class;
  XmManagerClassPart manager_class;
  XmDrawingAreaClassPart drawing_area_class;
  XbCanvasClassPart canvas_class;
} XbCanvasClassRec;

extern XbCanvasClassRec xbCanvasClassRec;

typedef struct _XbCanvasPart {
  int empty;
} XbCanvasPart;

typedef struct _XbCanvasRec {
  CorePart core;
  CompositePart composite;
  ConstraintPart constraint;
  XmManagerPart manager;
  XmDrawingAreaPart drawing_area;
  XbCanvasPart canvas;
} XbCanvasRec;
