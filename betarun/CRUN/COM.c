/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamOriginProto(struct Item *,AlloCOM)
/* = struct Item * AlloCOM(struct Object *origin, struct ProtoType *proto) */
{
    DeclReference1(struct Item *, item); /*= struct Item * item; */
    GCable_Entry();
    MCHECK();
    FetchOriginProto();

    DEBUG_CODE(NumAlloCOM++);

    Ck(origin);

#if (defined(hppa) && defined(RTDEBUG))
    if((unsigned)/*getRefSP()*/RefSP > (unsigned)ReferenceStack + 990*4) {
      Notify("ReferenceStack overflow!!!");
    }
#endif

    DEBUG_CODE( Claim(proto->Size > 0, "AlloCOM: proto->Size > 0") );

    Protect(origin, item = (struct Item *) AOAcalloc(ItemSize(proto)));

    /* The new Object is now allocated, but not initialized yet! */

    setup_item(item, proto, origin); 

    /* COM objects have their prototype point AFTER the static part of 
     * the proto type struct 
     */
    /* item->Proto++; does not work - adds 28 */
    item->Proto = (struct ProtoType *)((long)item->Proto+sizeof(ProtoType)-4);

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
