typedef struct _XbPlaneClassPart {
  int empty;
} XbPlaneClassPart;

typedef struct _XbPlaneClassRec {
  CoreClassPart core_class;
  CompositeClassPart composite_class;
  ConstraintClassPart constraint_class;
  XmManagerClassPart manager_class;
  XbPlaneClassPart plane_class;
} XbPlaneClassRec;

extern XbPlaneClassRec xbPlaneClassRec;

typedef struct _XbPlanePart {
  int empty;
} XbPlanePart;

typedef struct _XbPlaneRec {
  CorePart core;
  CompositePart composite;
  ConstraintPart constraint;
  XmManagerPart manager;
  XbPlanePart plane;
} XbPlaneRec;
