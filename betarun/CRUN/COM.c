/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamOriginProto(Item *,AlloCOM)
/* = Item * AlloCOM(Object *origin, ProtoType *proto) */
{
    DeclReference1(Item *, item); /*= Item * item; */
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
      Protect(item, CallBetaEntry(proto->GenPart,item));
    }
    /* origin cannot be Ck'ed since it is not protected during call above */
    Ck(item);

    MCHECK();

    SPARC_CODE(return_in_i1(item));
    RETURN(item);
}

#endif /* MT */
