#ifdef hpux
#define SYSV
#endif

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Vendor.h>

extern long ArgCount;
extern long ArgVector;

int getargc()
{ 
return ( (long) &ArgCount );
}

int getargv()
{ 
return ( (long) ArgVector );
}

int getCoreWidgetClass(){return ( (long) coreWidgetClass);}
int getObjectClass(){return ( (long) objectClass);}
int getRectObjClass(){return ( (long) rectObjClass);}
int getCompositeWidgetClass(){return ( (long) compositeWidgetClass);}
int getConstraintWidgetClass(){return ( (long) constraintWidgetClass);}
int getShellWidgetClass(){return ( (long) shellWidgetClass);}
int getWMShellWidgetClass(){return ( (long) wmShellWidgetClass);}
int getOverrideShellWidgetClass(){return ( (long) overrideShellWidgetClass);}
int getVendorShellWidgetClass(){return ( (long) vendorShellWidgetClass);}
int getTopLevelShellWidgetClass(){return ( (long) topLevelShellWidgetClass);}
int getTransientShellWidgetClass(){return ( (long) transientShellWidgetClass);}
int getApplicationShellWidgetClass(){return ( (long) applicationShellWidgetClass);}

