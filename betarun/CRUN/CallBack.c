/* File: CallBack.c
 * $Id: CallBack.c,v 1.1 1992-06-06 03:36:37 beta Exp $
 */

#include "beta.h"
#include "crun.h"

extern void CopyCProcPar() asm("CopyCProcPar");

void CopyCProcPar(ref(Object)theObj)
{
    /* I'm trying to see if is possible to make a struct */
    struct CallBackStruct {
	long savedSP;
    };
	
    ref(CallBackFrame) theCBStruct = cast(CallBackFrame)CBFATop;

    /* Find a free entry in the Call Back Functions Area.		*/
    /* This area is defined by [ CBFA <= CBFATop <= CBFALimit ].	*/

    if (theCBStruct+1 > cast(CallBackFrame)CBFALimit)
      BetaError(-11, theObj);

    (cast(CallBackFrame)CBFATop)++;
    

  
}

extern void HandleCallBack() asm("HandleCallBack");

void HandleCallBack()
{
    fprintf(stderr, "HandleCallBack is still not implemented\n");
}
