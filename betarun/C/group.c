/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * group.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#if defined(MAC)
#include <String.h>
#include <Files.h>
#endif

#if 0
#define TRACE_GROUP(code) code; fflush(output) /* Trace GroupName() */
#else
#define TRACE_GROUP(code)
#endif

/************** NEXTGROUP ******************/

/* NextGroup is used by objectserver/persistent store to scan through the
 * data-segments, in order to implement InitFragment.
 * It must be non-static.
 */

#ifdef NEW_NEXTGROUP_IMPL

/********** NEW NEXTGROUP IMPLEMENTATION ***********/

/* NextGroup: (new)
 *  return the next group after the group_header given as parameter
 */
group_header* NextGroup (group_header* current)
{ group_header **ptr;
  TRACE_GROUP(fprintf (output, "NextGroup(0x%x)\n", (long)current));
  if (current) {
    /* Get ptr from current (stored by previous NextGroup) and increment */
    ptr = current->ptr+1;
  } else {
    /* Start from betaenv */
    ptr = BETA_DATA1_ADDR;
  }
  TRACE_GROUP(fprintf (output, "NextGroup: ptr=0x%x\n", (long)ptr));
  if (!ptr) {
    TRACE_GROUP(fprintf (output, "NextGroup returns 0\n"));
    return 0;
  }
  current = *ptr;
  TRACE_GROUP(fprintf (output, "NextGroup. current = 0x%x\n", (long)current));

  if (current){
    /* Save ptr in current, so that next NextGroup can continue */
    current->ptr = ptr;
  }

  return current;
}

#ifdef macppc
#define GroupCodeStart(group) (*(long*)((group)->code_start))
#define GroupCodeEnd(group)   (*(long*)((group)->code_end))
#else
#define GroupCodeStart(group) ((long)((group)->code_start))
#define GroupCodeEnd(group)   ((long)((group)->code_end))
#endif

#else 
/********** OLD NEXTGROUP IMPLEMENTATION ***********/

/* NextGroup: (old)
 *  return the next group after the group_header given as parameter
 */
group_header* NextGroup (group_header* current)
     /* Return group in executable following current. 
      * If current is NULL, first group is returned. */
{ 
  long *limit;

  TRACE_GROUP(fprintf (output, "NextGroup. current = 0x%x\n", current));
  
  if (current) {
    /* Get next data segment if any. Padding by linker 
     * may have moved it some longs down */
    current=current->data_end;

    limit = (long *) current + 10;
    if (limit > (long *) &BETA_end) limit = (long *) &BETA_end;

    for (; (long*)current<limit; current=(group_header*)((long*)current+1)) {
      if (current->data_start == current) {
	TRACE_GROUP(fprintf (output, "NextGroup returns 0x%x\n", current));
	return current;
      }
      TRACE_GROUP(fprintf (output, "NextGroup pad\n"));
    }
    /* No next group. */
    TRACE_GROUP(fprintf (output, "NextGroup returns 0\n"));
    return 0;
  } else {
    TRACE_GROUP(fprintf (output, "NextGroup returns 0x%x\n", BETA_DATA1_ADDR));
    return (struct group_header *)BETA_DATA1_ADDR;
  }
}

#ifdef mac68k
#define GroupCodeStart(group) (*(long*)((group)->code_start))
#define GroupCodeEnd(group)   (*(long*)((group)->code_end))
#else
#define GroupCodeStart(group) ((long)((group)->code_start))
#define GroupCodeEnd(group)   ((long)((group)->code_end))
#endif

/********** END NEXTGROUP ***********/

#endif /* NEW_NEXTGROUP_IMPL */

/* IsBetaPrototype (generic):
 * Run through the prototype table of a file and
 * check if the gives address is equal to one of
 * the prototype adresses.
 */
int IsBetaPrototype(group_header *gh, long data_addr) 
{ long* proto=&gh->protoTable[1];
  int i, NoOfPrototypes;
  NoOfPrototypes = gh->protoTable[0];
  TRACE_GROUP(fprintf(output, 
		      ">>>IsBetaPrototype(group=0x%x, addr=0x%x)\n",
		      gh,
		      data_addr));
  for (i=0; i<NoOfPrototypes; i++){
    TRACE_GROUP(fprintf(output,">>>IsBetaPrototype: Try 0x%x\n", *proto));
    if ((*proto)==data_addr){
      return 1;
    } else {
      proto++;
    }
  }
  return 0;
}


/* IsBetaCodeAddr (generic):
 * Scan group to see if addr is within any BETA code segment.
 */
int IsBetaCodeAddr(long addr) 
{ group_header *current = 0;
  while ((current = NextGroup (current))) {
    if ((current->code_start<=addr) && (addr<=current->code_end))
      return TRUE;
  }
  return FALSE;
}

/* GroupName: (generic)
 *  Return the name of the fragment group that the address resides in.
 *  If isCode is 0, the address is assumed to be a prototype address.
 *  Is used by DisplayBetaStack (beta.dump) and objinterface.bet.
 *  It must be non-static.
 * 
 */
char *GroupName(long address, int isCode)
{
  group_header *current;

  TRACE_GROUP(fprintf (output, 
		       "GroupName(addr: 0x%x, %s)\n",
		       (int)address,
		       isCode ? "code" : "data"));

  current = NextGroup (0);  /* first (betaenv) data segment */

  /* In general we cannot know anything about the order in which the
   * code- and data-segments of the various fragment groups are linked
   * together (because of shared code, position independent code etc).
   * So we just run through each fragment group (found via the table
   * starting at the global label BETA_DATA), and check if the address
   * is in that fragment.
   */

  while (current){
    if (isCode){
      if ((GroupCodeStart(current) <= address) &&
	  (address <= GroupCodeEnd(current))){
	TRACE_GROUP(fprintf (output, "GroupName: returns "));
	TRACE_GROUP(fprintf (output, "%s\n", NameOfGroupMacro (current)));
	return NameOfGroupMacro (current);
      }
    } else {
      /* data address; seach for Prototype */
      if (IsBetaPrototype(current,address)) {
	TRACE_GROUP(fprintf (output, "GroupName: proto: returns "));
	TRACE_GROUP(fprintf (output, "%s\n", NameOfGroupMacro (current)));
	return NameOfGroupMacro (current);
      }
    }
    TRACE_GROUP(if (isCode){
		  fprintf(output, 
			  " GroupName: cur->code: 0x%x-0x%x, name: '%s'\n", 
			  (int)current->code_start,
			  (int)current->code_end,
			  NameOfGroupMacro(current));
		} else {
		  fprintf(output, 
			  " GroupName: cur: 0x%x, name: '%s'\n", 
			  (int)current,
			  NameOfGroupMacro(current));
		});
    current = NextGroup (current);
  }

  /* GroupName failed */
  TRACE_GROUP(fprintf (output, "GroupName returns 0\n"));
  return NULL; 
}

/* NameOfGroup:
 * Declared as *function* because objectserver uses it.
 * Not used internally in RTS - here we use NameOfGroupMacro.
 */
char *NameOfGroup(struct group_header *group)
{
  return NameOfGroupMacro(group);
}



#if (defined(RTDEBUG) && (!defined(NEW_NEXTGROUP_IMPL)))
static long BETA_code_start=-1, BETA_code_end=-1;

long GetBetaCodeStart()
{
  if (BETA_code_start==-1)
    BETA_code_start=(long)((struct group_header*)BETA_DATA1_ADDR)->code_start;
  return BETA_code_start;
}
  
long GetBetaCodeEnd()
{ 
  if (BETA_code_end==-1){
    struct group_header *last, *current;
    last = current = NextGroup (0);  /* first (betaenv) data segment */
    while (current){
      last = current;
      current = NextGroup(last);
    }
    BETA_code_end=(long)last->code_end;
  }
  return BETA_code_end;
}
#endif



