#ifndef _TRIE_H_
#define _TRIE_H_
#include "../C/beta.h"

/* */
#define INITIALTRIESIZE 8192  /* bytes */

typedef struct trie {
  unsigned long size;
  unsigned long top;
  char buffer[INITIALTRIESIZE];
} Trie;

typedef struct contentsBox {
  void *contents;
  unsigned long key;
} contentsBox;

Trie *TInit(void);
void TInitp(Trie *new);
void TInsert(unsigned long key, void *contents, Trie **current, unsigned long insertKey);
void *TILookup(unsigned long key, Trie *current);
void TIVisit(Trie *current, void (*visitFunc)(contentsBox *));
void TIFree(Trie *current, void (*freeFunc)(void *));

#endif /* _TRIE_H_ */
