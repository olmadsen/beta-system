/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamOriginProto(Item *,AlloCOM)
/* = Item * AlloCOM(Object *origin, ProtoType *proto) */
{
    DeclReference1(Item *, item); /*= Item * item; */
    GCable_Entry();
    MCHECK();
    FetchOriginProto();

    DEBUG_CODE(NumAlloCOM++);

    Ck(origin);

#ifndef COM
  fprintf(output, "\n\n***WARNING: Using AlloCOM with COM symbol undefined. GC may fail!\n\n");
#endif

#if (defined(hppa) && defined(RTDEBUG))
    if((unsigned)/*getRefSP()*/RefSP > (unsigned)ReferenceStack + 990*4) {
      Notify("ReferenceStack overflow!!!");
    }
#endif

    Claim((long)proto->Size>0, "proto->Size>0");

    Protect(origin, item = (Item *) AOAcalloc(ItemSize(proto)));

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, origin); 

#ifndef COM
    item->Proto = (ProtoType *)((long)(item->Proto)+DISP_OFF);
#endif /* COM */

    if (proto->GenPart){
#ifdef RTDEBUG
      Protect2(origin, item, CallBetaEntry(proto->GenPart,item));
#else
      Protect(item, CallBetaEntry(proto->GenPart,item));
#endif
    }

    Ck(origin); Ck(item);

    MCHECK();

    GCable_Exit(1);    
#ifdef sparc
    return_in_i1(item);
#else
    RETURN(item);
#endif
}

#endif /* MT */
