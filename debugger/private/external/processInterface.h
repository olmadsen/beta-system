

#ifndef PROCESSINTERFACE_H
#define PROCESSINTERFACE_H

int SetBreakpoint (int address);
int ClearBreakpoint (int address, int instruction);

typedef struct groupHeader
{ long self;      /* Address of this groupHeader.            */
  long ascii;     /* Address of groupName string. dataStart. */
  long next;      /* Address of next group_header. dataEnd.  */
  long codeStart; /* Address of code segment.                */
  long code_end;  /* Address where code segment ends.        */
} groupHeader;

/* struct groupHeader* ValhallaNextGroup (struct groupHeader* current)
 * ===================================================================
 *
 * Corresponds to NextGroup in outpattern.c, but is used by valhalla
 * to locate the objectfiles within a debugged process.
 * If current is 0, the first group is returned. */

struct groupHeader* ValhallaNextGroup (struct groupHeader* current);

#endif
