/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * aoa.h
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */


extern ref(Object) CopyObjectToAOA();
extern void AOAGc();

#ifdef RTDEBUG
extern void AOACheck();
extern void AOACheckObject();
extern void AOACheckReference();
extern void AOACheckObjectSpecial();

#endif
