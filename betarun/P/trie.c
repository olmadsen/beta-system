#include "beta.h"
#include "trie.h"

void trie_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef sparc
#define OURINLINE __inline__
#else
#define OURINLINE
#endif

#ifdef PERSIST
/* */

Node *TInit(void)
{
  Node *new;
  
  new = (Node *)calloc(sizeof(struct Node), 1);
  new -> d = -1;
  
  return new;
}

static OURINLINE void insertDown(u_long key, void *contents, Node *current, u_long insertKey)
{
  if (current -> down == NULL) {
    current -> down = (Node *)calloc(sizeof(struct Node), 1);
    current -> down -> d = -1;
  }
  TInsert(key, contents, current -> down, insertKey);
}

static OURINLINE void insertRight(u_long key, void *contents, Node *current, u_long insertKey)
{
  if (current -> right == NULL) {
    current -> right = (Node *)calloc(sizeof(struct Node), 1);
    current -> right -> d = -1;
  }
  TInsert(key, contents, current -> right, insertKey);
}

void TInsert(u_long key, void *contents, Node *current, u_long insertKey)
{
  if (key > 10) {
    if (current -> d == -1) {
      current -> d = key % 10;
      insertDown(key / 10, contents, current, insertKey);
    } else {
      if (key % 10 == current -> d) {
	insertDown(key / 10, contents, current, insertKey);
      } else {
	insertRight(key, contents, current, insertKey);
      }
    }
  } else {
    if (current -> d == -1) {
      current -> d = key;
      current -> contents = (contentsBox *)calloc(sizeof(struct contentsBox), 1);
      current -> contents -> contents = contents;
      current -> contents -> key = insertKey;
    } else {
      if (key == current -> d) {
	if (current -> contents == NULL) {
	  current -> contents = (contentsBox *)calloc(sizeof(struct contentsBox), 1);
	} 
	current -> contents -> contents = contents;
	current -> contents -> key = insertKey;
      } else {
	insertRight(key, contents, current, insertKey);
      }
    }
  }
}

static OURINLINE void *downLookup(u_long key, Node *current)
{
  if (current -> down != NULL) {
    return TILookup(key, current -> down);
  } else {
    return NULL;
  }
}

static OURINLINE void *rightLookup(u_long key, Node *current)
{
  if (current -> right != NULL) {
    return TILookup(key, current -> right);
  } else {
    return NULL;
  }
}

void *TILookup(u_long key, Node *current)
{
  if (key > 10) {
    if (key % 10 == current -> d) {
      return downLookup(key / 10, current);
    } else {
      return rightLookup(key, current);
    }
  } else {
    if (key == current -> d) {
      if (current -> contents != NULL) {
	return current -> contents -> contents;
      } else {
	return NULL;
      }
    } else {
      return rightLookup(key, current);
    }
  }
}

void TIVisit(Node *current, void (*visitFunc)(contentsBox *))
{
  if (current -> contents != NULL) {
    visitFunc(current -> contents);
  } 
  if (current -> down != NULL) {
    TIVisit(current -> down, visitFunc);
  }
  if (current -> right != NULL) {
    TIVisit(current -> right, visitFunc);
  }
}

void TIFree(Node *current, void (*freeFunc)(void *))
{
  if (current -> contents != NULL) {
    if (freeFunc) {
      freeFunc(current -> contents -> contents);
    }
    free(current -> contents);
    current -> contents = NULL;
  } 
  if (current -> down != NULL) {
    TIFree(current -> down, freeFunc);
    current -> down = NULL;
  }
  if (current -> right != NULL) {
    TIFree(current -> right, freeFunc);
    current -> right = NULL;
  }
  free(current);
}
  
/* TESTING */

void visitFunc(contentsBox *cb)
{
  printf("visitFunc: %s\n", (char *)(cb -> contents));
}

void testTrie(void)
{
  Node *trie;
  
  trie = TInit();
  
  TInsert(10101, "10101 inserted", trie, 0);
  TInsert(0, "0 inserted", trie, 0);
  TInsert(1, "1 inserted", trie, 0);
  TInsert(1, "1 inserted", trie, 0);
  TInsert(10101, "10101 inserted again", trie, 0);
  TInsert(1010111, "1010111 inserted", trie, 0);
  
  Claim(TILookup(10101, trie) != NULL, "");
  Claim(TILookup(0, trie) != NULL, "");
  Claim(TILookup(1, trie) != NULL, "");
  Claim(TILookup(1010111, trie) != NULL, "");

  Claim(TILookup(100, trie) == NULL, "");
  Claim(TILookup(101, trie) == NULL, "");
  
  TIVisit(trie, visitFunc);
}

#endif /* PERSIST */
