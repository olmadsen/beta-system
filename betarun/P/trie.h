#ifndef _TRIE_H_
#define _TRIE_H_

/* */
#define INITIALTRIESIZE 8192 /* bytes */
/* #define INITIALTRIESIZE (2*8192) */ 

typedef struct trie {
  unsigned long size;
  unsigned long top;
  char buffer[INITIALTRIESIZE];
} Trie;

typedef struct contentsBox {
  unsigned long contents;
  unsigned long key;
} contentsBox;

Trie *TInit(void);
void TInsert(unsigned long key, unsigned long contents, Trie **current, unsigned long insertKey);
unsigned long TILookup(unsigned long key, Trie *current);
void TIVisit(Trie *current, void (*visitFunc)(contentsBox *));
void TIFree(Trie *current, void (*freeFunc)(unsigned long));
void TIadd(Trie **dst, Trie *src);

/* TEXT TRIES, may use the init, visit and free functions from above */
void TTInsert(char *key, unsigned long contents, Trie **trie);
unsigned long TTLookup(char *key, Trie *trie);

#endif /* _TRIE_H_ */
