#ifndef _SEQUENCETABLE_H_
#define _SEQUENCETABLE_H_
#include "beta.h"

typedef struct sequenceTable {
  u_long elemSize;        /* size of elements in byts */
  int (*isFree)(void *);  /* determines if an entry is free */
  void (*Free)(void *);    /* function to free entry */
  u_long maxIndex;        /* number of indices allocated for this table */
  u_long nextFree;        /* Index of the next free entry */
  void *body[1];
} sequenceTable;

sequenceTable *STInit(u_long NoElems, 
		      int (*isFree)(void *), 
		      void (*Free)(void *), 
		      u_long elemSize);
u_long STSize(sequenceTable *currentTable);
u_long STInsert(sequenceTable **tableSite, void *elm);
void *STLookup(sequenceTable *currentTable, u_long inx);
void STFree(sequenceTable **currentTable);

#endif /* _SEQUENCETABLE_H_ */
