#ifdef hpux
#define SYSV
#endif

#include "Xm/Xm.h"

#ifdef sparc
/* Check for Motif 1.2 */
#if (XmVERSION !=1) || (XmREVISION !=2)
#error You MUST use Motif 1.2 header files for Solaris
#endif
#endif

#include "Xm/ArrowB.h"
#include "Xm/ArrowBG.h"
#include "Xm/AtomMgr.h"
#include "Xm/BulletinB.h"
#include "Xm/CascadeB.h"
#include "Xm/CascadeBG.h"
#include "Xm/Command.h"
#include "Xm/CutPaste.h"
#include "Xm/DialogS.h"
#include "Xm/DrawingA.h"
#include "Xm/DrawnB.h"
#include "Xm/FileSB.h"
#include "Xm/Form.h"
#include "Xm/Frame.h"
#include "Xm/Label.h"
#include "Xm/LabelG.h"
#include "Xm/List.h"
#include "Xm/MainW.h"
#include "Xm/MenuShell.h"
#include "Xm/MessageB.h"
#include "Xm/PanedW.h"
#include "Xm/PushB.h"
#include "Xm/PushBG.h" 
#include "Xm/RowColumn.h" 
#include "Xm/Scale.h" 
#include "Xm/ScrollBar.h" 
#include "Xm/ScrolledW.h" 
#include "Xm/SelectioB.h" 
#include "Xm/SeparatoG.h" 
#include "Xm/Separator.h" 
#include "Xm/Text.h" 
#include "Xm/TextF.h" 
#include "Xm/ToggleB.h" 
#include "Xm/ToggleBG.h"

int getXmPrimitiveWidgetClass(){return ( (long) xmPrimitiveWidgetClass);}
int getXmGadgetClass(){return ( (long) xmGadgetClass);}
int getXmArrowButtonWidgetClass(){return ( (long) xmArrowButtonWidgetClass);}
int getXmArrowButtonGadgetClass(){return ( (long) xmArrowButtonGadgetClass);} 
int getXmLabelWidgetClass(){return ( (long) xmLabelWidgetClass);}
int getXmLabelGadgetClass(){return ( (long) xmLabelGadgetClass);}
int getXmCascadeButtonWidgetClass(){return ( (long) xmCascadeButtonWidgetClass);}
int getXmCascadeButtonGadgetClass(){return ( (long) xmCascadeButtonGadgetClass);}
int getXmDrawnButtonWidgetClass(){return ( (long) xmDrawnButtonWidgetClass);}
int getXmPushButtonWidgetClass(){return ( (long) xmPushButtonWidgetClass);}
int getXmPushButtonGadgetClass(){return ( (long) xmPushButtonGadgetClass);}
int getXmToggleButtonWidgetClass(){return ( (long) xmToggleButtonWidgetClass);}
int getXmToggleButtonGadgetClass(){return ( (long) xmToggleButtonGadgetClass);}
int getXmListWidgetClass(){return ( (long) xmListWidgetClass);}
int getXmScrollBarWidgetClass(){return ( (long) xmScrollBarWidgetClass);}
int getXmSeparatorWidgetClass(){return ( (long) xmSeparatorWidgetClass);}
int getXmSeparatorGadgetClass(){return ( (long) xmSeparatorGadgetClass);}
int getXmTextWidgetClass(){return ( (long) xmTextWidgetClass);}
int getXmTextFieldWidgetClass(){return ( (long) xmTextFieldWidgetClass);}
int getXmMenuShellWidgetClass(){return ( (long) xmMenuShellWidgetClass);}
int getXmDialogShellWidgetClass(){return ( (long) xmDialogShellWidgetClass);}
int getXmManagerWidgetClass(){return ( (long) xmManagerWidgetClass);}
int getXmBulletinBoardWidgetClass(){return ( (long) xmBulletinBoardWidgetClass);}
int getXmFormWidgetClass(){return ( (long) xmFormWidgetClass);}
int getXmMessageBoxWidgetClass(){return ( (long) xmMessageBoxWidgetClass);}
int getXmSelectionBoxWidgetClass(){return ( (long) xmSelectionBoxWidgetClass);}
int getXmCommandWidgetClass(){return ( (long) xmCommandWidgetClass);}
int getXmFileSelectionBoxWidgetClass(){return ( (long) xmFileSelectionBoxWidgetClass);}
int getXmDrawingAreaWidgetClass(){return ( (long) xmDrawingAreaWidgetClass);}
int getXmFrameWidgetClass(){return ( (long) xmFrameWidgetClass);}
int getXmRowColumnWidgetClass(){return ( (long) xmRowColumnWidgetClass);}
int getXmScrolledWindowWidgetClass(){return ( (long) xmScrolledWindowWidgetClass);}
int getXmMainWindowWidgetClass(){return ( (long) xmMainWindowWidgetClass);}
int getXmScaleWidgetClass(){return ( (long) xmScaleWidgetClass);}
int getXmPanedWindowWidgetClass(){return ( (long) xmPanedWindowWidgetClass);}

int getXmSTRING_DEFAULT_CHARSET(){ return (long) XmSTRING_DEFAULT_CHARSET; }
int getXmSTRING_ISO8859_1(){ return (long) XmSTRING_ISO8859_1; }
int getXmSTRING_OS_CHARSET(){ return (long) XmSTRING_OS_CHARSET; }
int getXmFALLBACK_CHARSET(){ return (long) XmFALLBACK_CHARSET; }
