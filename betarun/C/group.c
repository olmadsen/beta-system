/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-2002 Mjolner Informatics Aps.
 * group.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#if defined(MAC)
#include <String.h>
#include <Files.h>
#endif

/********* Fragment group support via BETA_DATA *******/

/*
 *  The structure is:
 *                      _______          __________ 
 *          BETA_DATA: |_______|<==---->|data_start|(group_header)
 *                     |_______|   \	|protoTable|
 *                     |  ...  |    |	| data_end |
 *                     |  ...  |    |	|code_start|
 *                     |  ...  |    |	| code_end |
 *                     |  ...  |    |	|group_name|
 *                     |  ...  |    |	|  hash    |
 *                     |  ...  |    |	| modtime  |
 *                     |  ...  |    `---|___ptr____|
 *                     |  ...  |    
 *                     |  ...  |    
 *                     |  ...  |    
 *                     |_______|    
 *                     |___0___|      _______ 
 *                     |_______|---->|_______|
 *                                   |_______|
 *                      (extra block |  ...  |
 *                       added by    |_______|
 *                       AddGroup)   |___0___|
 *                                   |___0___| (last block double NULL term)
 */

extern group_header *BETA_DATA; /* Defined in BETA */

/************** NEXTGROUP ******************/

/* NextGroup is used by objectserver/persistent store to scan through the
 * data-segments, in order to implement InitFragment.
 * It must be non-static.
 */


/* NextGroup: 
 *  return the next group after the group_header given as parameter.
 */
group_header* NextGroup (group_header* current)
{ group_header **ptr;
  TRACE_GROUP(fprintf (output, "NextGroup(0x%x)\n", (int)current));
  if (current) {
    /* Get ptr from current (stored by previous NextGroup) and increment */
    ptr = current->ptr+1;
  } else {
    /* Start from betaenv */
    ptr = &BETA_DATA;
  }
  TRACE_GROUP(fprintf (output, "NextGroup: ptr=0x%x\n", (int)ptr));
  if (!ptr) {
    TRACE_GROUP(fprintf (output, "NextGroup returns 0\n"));
    return 0;
  }
  current = *ptr;
  TRACE_GROUP(fprintf (output, "NextGroup: current = 0x%x\n", (int)current));

  if (!current){
    TRACE_GROUP(fprintf (output, "NextGroup: met 1 NULL - try next too\n"));
    ptr++;
    TRACE_GROUP(fprintf (output, "NextGroup: next ptr=0x%x\n", (int)ptr));
    current = *ptr;
    TRACE_GROUP(fprintf (output, "NextGroup: next current = 0x%x\n", (int)current));
    if (current){
      /* A non-zero field after the first NULL is a pointer to
       * another block - continue through that one.
       */
      ptr = (group_header **)current;
      TRACE_GROUP(fprintf (output, "NextGroup: new ptr=0x%x\n", (int)ptr));
      current = *ptr;
      TRACE_GROUP(fprintf (output, "NextGroup: new current = 0x%x\n", (int)current));
    }
  }
  if (current){
    /* Save ptr in current, so that next NextGroup can continue */
    current->ptr = ptr;
  }

  TRACE_GROUP(fprintf (output, "NextGroup: returns current = 0x%x\n", (int)current));
  return current;
}

#define AddGroupNumberOfElements 16

static group_header **NewGroupList(void)
{ 
  group_header **list;
  int i;
  list = (group_header **) MALLOC((AddGroupNumberOfElements+2) * sizeof(group_header*));
  for (i=0; i<AddGroupNumberOfElements+2; i++) list[i]=0;
  return list;
}

void AddGroup(group_header *new_group)
{
  static group_header **LastGroup = &BETA_DATA;
  static int LastGroupInx;
  group_header **list;

  if (LastGroup == &BETA_DATA){
    /* There is never room for more in BETA_DATA */
    /* Find last position in BETA_DATA */
    while (LastGroup[LastGroupInx]) LastGroupInx++;
    list = NewGroupList();
    LastGroup[LastGroupInx+1]=(group_header *)list;
    LastGroup=list;
    LastGroupInx=0;
  } else {
    /* Check for space in LastGroup */
    if (LastGroupInx==AddGroupNumberOfElements){
      list = NewGroupList();
      LastGroup[LastGroupInx+1]=(group_header *)list;
      LastGroup=list;
      LastGroupInx=0;
    }
  }
  /* Now there is known to be a free cell at LastGroup[LastGroupInx] */
  LastGroup[LastGroupInx] = new_group;
  LastGroupInx++;
  return;
}

#ifdef macppc
#define GroupCodeStart(group) ((pc_t)(*(unsigned long*)((group)->code_start)))
#define GroupCodeEnd(group)   ((pc_t)(*(unsigned long*)((group)->code_end)))
#else
#define GroupCodeStart(group) ((group)->code_start)
#define GroupCodeEnd(group)   ((group)->code_end)
#endif

/* IsPrototypeOfGroup:
 * Run through the prototype table of a file and
 * check if the gives address is equal to one of
 * the prototype adresses.
 */
int IsPrototypeOfGroup(group_header *gh, long data_addr) 
{ long* proto=&gh->protoTable[1];
  int i, NoOfPrototypes;

  NoOfPrototypes = gh->protoTable[0];
  TRACE_GROUP(fprintf(output, 
		      ">>>IsPrototypeOfGroup(group=0x%x, addr=0x%x)\n",
		      (int)gh,
		      (int)data_addr));
  for (i=0; i<NoOfPrototypes; i++){
    TRACE_GROUP(fprintf(output,">>>IsPrototypeOfGroup: Try 0x%x\n", (int)*proto));
    if ((*proto)==data_addr){
      return (i + 1);
    } else {
      proto++;
    }
  }
  return 0;
}

/* IsPrototypeOfProcess:
 * Return TRUE if pt is a special proto type or
 * a prototype of any pattern in the current process.
 */
int IsPrototypeOfProcess(long pt)
{ 
  group_header *gh;

  TRACE_GROUP(fprintf(output, "IsPrototypeOfProcess(0x%08x)\n", (int)pt));

  if (isSpecialProtoType(pt)) return 1;
  gh = NextGroup(0);
  while (gh){
    if (IsPrototypeOfGroup(gh, pt)) return 1;
    gh = NextGroup(gh);
  }
  return 0;
} 


/* IsBetaCodeAddrOfProcess:
 * Scan group to see if addr is within any BETA code segment.
 */
int IsBetaCodeAddrOfProcess(pc_t addr) 
{ 
#ifdef MAC
  /* can't determine if an address is in a given object file on MAC.
   * Let's assume that it is the case.
   */
  DEBUG_CODE(fprintf(output, "Warning: ppcmac: IsBetaCodeAddrOfProcess is NOT implemented!\n"));
  return TRUE;
#else
  group_header *current = 0;
  while ((current = NextGroup (current))) {
    TRACE_GROUP({
      fprintf(output, "IsBetaCodeAddrOfProcess: current=0x%08x\n", (int)current); 
      fflush(output);
    });
    if ((GroupCodeStart(current)<=addr) && (addr<=GroupCodeEnd(current)))
      return TRUE;
  }
  return FALSE;
#endif /* MAC */
}

/* IsBetaDataAddrOfProcess:
 * Scan group to see if addr is within any BETA data segment.
 */
int IsBetaDataAddrOfProcess(unsigned long addr) 
{ 
#ifdef MAC
  /* can't determine if an address is in a given object file on MAC.
   * Let's assume that it is the case.
   */
  return TRUE;
#else
  group_header *current = 0;
  while ((current = NextGroup (current))) {
    TRACE_GROUP({
      fprintf(output, "IsBetaDataAddrOfProcess: current=0x%08x\n", (int)current); 
      fflush(output);
    });
    if (((unsigned long)current->data_start<=addr) && (addr<=(unsigned long)current->data_end))
      return TRUE;
  }
  return FALSE;
#endif /* MAC */
}

/* GroupName: (generic)
 *  Return the name of the fragment group that the address resides in.
 *  If isCode is 0, the address is assumed to be a prototype address.
 *  Is used by DisplayBetaStack (beta.dump) and objinterface.bet.
 *  It must be non-static.
 * 
 */
char *GroupName(pc_t address, int isCode)
{
  group_header *current;

  TRACE_GROUP(fprintf (output, 
		       "GroupName(addr: 0x%x, %s)\n",
		       (int)address,
		       isCode ? "code" : "data"));

#ifdef MAC
  if (isCode){
    /* can't determine if an address is in a given object file on MAC */
    return "(unknown fragment group)";
  }
#endif

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
      if (IsPrototypeOfGroup(current,(long)address)) {
	TRACE_GROUP(fprintf (output, "GroupName: proto: returns "));
	TRACE_GROUP(fprintf (output, "%s\n", NameOfGroupMacro (current)));
	return NameOfGroupMacro (current);
      }
    }
    TRACE_GROUP(if (isCode){
		  fprintf(output, 
			  " GroupName: cur->code: 0x%x-0x%x, name: '%s'\n", 
			  (int)GroupCodeStart(current),
			  (int)GroupCodeEnd(current),
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
char *NameOfGroup(group_header *group)
{
  return NameOfGroupMacro(group);
}
