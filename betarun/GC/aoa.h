/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $Id: aoa.h,v 1.4 1992-09-03 12:57:07 beta Exp $
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
