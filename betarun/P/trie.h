#ifndef _TRIE_H_
#define _TRIE_H_
#include "beta.h"

/* */
typedef struct contentsBox {
  void *contents;
  unsigned long key;
} contentsBox;

typedef struct Node Node;

struct Node {
  char d; /* digit [0-9] */
  contentsBox *contents;
  Node *right;
  Node *down;
};

Node *TInit(void);
void TInsert(unsigned long key, void *contents, Node *current, unsigned long insertKey);
void *TILookup(unsigned long key, Node *current);
void TIVisit(Node *current, void (*visitFunc)(contentsBox *));
void TIFree(Node *current, void (*freeFunc)(void *));

#endif /* _TRIE_H_ */
