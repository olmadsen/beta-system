#ifndef _SEQUENCETABLE_H_
#define _SEQUENCETABLE_H_

typedef struct sequenceTable {
  unsigned long elemSize;        /* size of elements in byts */
  int (*isFree)(void *);         /* determines if an entry is free */
  void (*Free)(void *);          /* function to free entry */
  unsigned long maxIndex;        /* number of entries allocated for this table */
  unsigned long nextFree;        /* Index of the next free entry */
  void *body[1];
} sequenceTable;

sequenceTable *STInit(unsigned long NoElems, 
		      int (*isFree)(void *), 
		      void (*Free)(void *), 
		      unsigned long elemSize);
unsigned long STSize(sequenceTable *currentTable);
unsigned long STInsert(sequenceTable **tableSite, void *elm);
void *STLookup(sequenceTable *currentTable, unsigned long inx);
void STFree(sequenceTable **currentTable);
unsigned long STtop(sequenceTable *currentTable);

#endif /* _SEQUENCETABLE_H_ */
