#ifndef _TRIE_H_
#define _TRIE_H_
#include "beta.h"

/* */
typedef struct contentsBox {
  void *contents;
  u_long key;
} contentsBox;

typedef struct Node Node;

struct Node {
  char d; /* digit [0-9] */
  contentsBox *contents;
  Node *right;
  Node *down;
};

Node *TInit(void);
void TInsert(u_long key, void *contents, Node *current, u_long insertKey);
void *TILookup(u_long key, Node *current);
void TIVisit(Node *current, void (*visitFunc)(contentsBox *));
void TIFree(Node *current, void (*freeFunc)(void *));

#endif /* _TRIE_H_ */
