#include "beta.h"
#include "trie.h"

#ifdef sparc
#define OURINLINE __inline__
#else
#define OURINLINE
#endif

/* Local types */
#define INITIALOFFSET 4
#define NODE(offset) (Node *)(&(trie -> buffer[0]) + (unsigned long)offset)
#define CONTENTSBOX(offset) ((contentsBox *)(&(trie -> buffer[0]) + (unsigned long)offset))
#define HEAD(trie) ((Node *)(&(trie -> buffer[0]) + INITIALOFFSET))
typedef struct Node Node;

struct Node {
  char d; /* digit [0-9] */
  unsigned long contents;
  unsigned long right;
  unsigned long down;
};

/* LOCAL FUNCTION DECLARATIONS */
static void TRealloc(Trie **trie);
static unsigned long allocNode(Trie *trie);
static unsigned long allocContentsBox(Trie *trie);
static OURINLINE void insertDown(unsigned long key, 
				 void *contents, 
				 Node *current, 
				 Trie *trie,
				 unsigned long insertKey);
static OURINLINE void insertRight(unsigned long key, 
				  void *contents, 
				  Node *current, 
				  Trie *trie,
				  unsigned long insertKey);
static void _TInsert(unsigned long key, 
		     void *contents, 
		     Node *current, 
		     Trie *trie,
		     unsigned long insertKey);
static OURINLINE void *downLookup(unsigned long key, Node *current, Trie *trie);
static OURINLINE void *rightLookup(unsigned long key, Node *current, Trie *trie);
static void *_TILookup(unsigned long key, Node *current, Trie *trie);
static void _TIVisit(Node *current, Trie *trie, void (*visitFunc)(contentsBox *));
static void _TIFree(Node *current, Trie *trie, void (*freeFunc)(void *));

/* LOCAL VARIABLES */
static Node *new;

/* IMPLEMENTATION */
Trie *TInit(void)
{
  Trie *new;

  new = (Trie *)calloc(1, sizeof(struct trie));
  new -> size = INITIALTRIESIZE;
  new -> top = INITIALOFFSET;
  /* allocate root node */
  ((Node *)(&(new -> buffer[0]) + (unsigned long)INITIALOFFSET)) -> d = -1;
  new -> top += sizeof(struct Node);
  return new;
}

void TInitp(Trie *new)
{
  new -> size = INITIALTRIESIZE;
  new -> top = INITIALOFFSET;
  /* allocate root node */
  ((Node *)(&(new -> buffer[0]) + (unsigned long)INITIALOFFSET)) -> d = -1;
  new -> top += sizeof(struct Node);
}

static void TRealloc(Trie **trie)
{
  Trie *new;
  
  new = (Trie *)calloc(1, 2 * sizeof(unsigned long) + 2 * (*trie) -> size);
  memcpy(&(new -> buffer[0]), (*trie) -> buffer, (*trie) -> top);
  new -> size = (*trie) -> size * 2;
  new -> top = (*trie) -> top;
  
  free(*trie);
  *trie = new;
}

static unsigned long allocNode(Trie *trie)
{
  if (trie -> top + sizeof(struct Node) < trie -> size) {
    trie -> top += sizeof(struct Node);
    return trie -> top - sizeof(struct Node);
  } else {
    Claim(FALSE, "allocNode: Unexpected reallocation");
    return 0;
  }
}

static unsigned long allocContentsBox(Trie *trie)
{
  if (trie -> top + sizeof(struct contentsBox) < trie -> size) {
    trie -> top += sizeof(struct contentsBox);
    return trie -> top - sizeof(struct contentsBox);
  } else {
    Claim(FALSE, "allocContentsBox: Unexpected reallocation");
    return 0;
  }
}

static OURINLINE void insertDown(unsigned long key, 
				 void *contents, 
				 Node *current, 
				 Trie *trie,
				 unsigned long insertKey)
{
  if (current -> down == 0) {
    current -> down = allocNode(trie);
    new = NODE(current -> down);
    new -> d = -1;
    new -> contents = 0;
    new -> right = 0;
    new -> down = 0;
  }
  _TInsert(key, contents, NODE(current -> down), trie, insertKey);
}

static OURINLINE void insertRight(unsigned long key, 
				  void *contents, 
				  Node *current, 
				  Trie *trie,
				  unsigned long insertKey)
{
  if (current -> right == 0) {
    current -> right = allocNode(trie);
    new = NODE(current -> right);
    new -> d = -1;
    new -> contents = 0;
    new -> right = 0;
    new -> down = 0;
  }
  _TInsert(key, contents, NODE(current -> right), trie, insertKey);
}

void TInsert(unsigned long key, 
	     void *contents, 
	     Trie **trie, 
	     unsigned long insertKey)
{
  /* Make sure that there is enough room to hold the new value */
  /* A max of log10(key) new nodes + one contentsbox might be generated */
  
  if ((*trie) -> top + 
      (sizeof(struct Node) * 20) + 
      sizeof(struct contentsBox) < (*trie) -> size) {
    _TInsert(key, contents, HEAD((*trie)), *trie, insertKey);
  } else {
    TRealloc(trie);
    TInsert(key, contents, trie, insertKey);
  }
}

static void _TInsert(unsigned long key, 
		     void *contents, 
		     Node *current, 
		     Trie *trie,
		     unsigned long insertKey)
{
  if (key > 10) {
    if (current -> d == -1) {
      current -> d = key % 10;
      insertDown(key / 10, contents, current, trie, insertKey);
    } else {
      if (key % 10 == current -> d) {
	insertDown(key / 10, contents, current, trie, insertKey);
      } else {
	insertRight(key, contents, current, trie, insertKey);
      }
    }
  } else {
    if (current -> d == -1) {
      current -> d = key;
      current -> contents = allocContentsBox(trie);
      CONTENTSBOX(current -> contents) -> contents = contents;
      CONTENTSBOX(current -> contents) -> key = insertKey;
    } else {
      if (key == current -> d) {
	if (current -> contents == 0) {
	  current -> contents = allocContentsBox(trie);
	} 
	CONTENTSBOX(current -> contents) -> contents = contents;
	CONTENTSBOX(current -> contents) -> key = insertKey;
      } else {
	insertRight(key, contents, current, trie, insertKey);
      }
    }
  }
}

static OURINLINE void *downLookup(unsigned long key, Node *current, Trie *trie)
{
  if (current -> down != 0) {
    return _TILookup(key, NODE(current -> down), trie);
  } else {
    return NULL;
  }
}

static OURINLINE void *rightLookup(unsigned long key, Node *current, Trie *trie)
{
  if (current -> right != 0) {
    return _TILookup(key, NODE(current -> right), trie);
  } else {
    return NULL;
  }
}

void *TILookup(unsigned long key, Trie *trie)
{
  return _TILookup(key, HEAD(trie), trie);
}

static void *_TILookup(unsigned long key, Node *current, Trie *trie)
{
  if (key > 10) {
    if (key % 10 == current -> d) {
      return downLookup(key / 10, current, trie);
    } else {
      return rightLookup(key, current, trie);
    }
  } else {
    if (key == current -> d) {
      if (current -> contents != 0) {
	return CONTENTSBOX(current -> contents) -> contents;
      } else {
	return NULL;
      }
    } else {
      return rightLookup(key, current, trie);
    }
  }
}

void TIVisit(Trie *trie, void (*visitFunc)(contentsBox *))
{
  _TIVisit(HEAD(trie), trie, visitFunc);
}

static void _TIVisit(Node *current, Trie *trie, void (*visitFunc)(contentsBox *))
{
  if (current -> contents != 0) {
    visitFunc(CONTENTSBOX(current -> contents));
  } 
  if (current -> down != 0) {
    _TIVisit(NODE(current -> down), trie, visitFunc);
  }
  if (current -> right != 0) {
    _TIVisit(NODE(current -> right), trie, visitFunc);
  }
}

void TIFree(Trie *trie, void (*freeFunc)(void *))
{
  if (freeFunc) {
    _TIFree(HEAD(trie), trie, freeFunc);
  }
  free(trie);
}

static void _TIFree(Node *current, Trie *trie, void (*freeFunc)(void *))
{
  if (current -> contents != 0) {
    freeFunc(CONTENTSBOX(current -> contents) -> contents);
  } 
  if (current -> down != 0) {
    _TIFree(NODE(current -> down), trie, freeFunc);
  }
  if (current -> right != 0) {
    _TIFree(NODE(current -> right), trie, freeFunc);
  }
}
  
/* TESTING */
#ifdef RTDEBUG
void visitFunc(contentsBox *cb)
{
  printf("visitFunc: %s\n", (char *)(cb -> contents));
}

void testTrie(void)
{
  Trie *trie;
  
  trie = TInit();

#define TINSERT(x,y,z,v) \
  fprintf(output, "TInsert(%s)\n", (char*)y); fflush(output); \
  TInsert(x,y,z,v)
  
  TINSERT(10101, "10101 inserted", &trie, 0);
  TINSERT(0, "0 inserted", &trie, 0);
  TINSERT(1, "1 inserted", &trie, 0);
  TINSERT(1, "1 inserted", &trie, 0);
  TINSERT(10101, "10101 inserted again", &trie, 0);
  TINSERT(1010111, "1010111 inserted", &trie, 0);
  
  Claim(TILookup(10101, trie) != NULL, "");
  Claim(TILookup(0, trie) != NULL, "");
  Claim(TILookup(1, trie) != NULL, "");
  Claim(TILookup(1010111, trie) != NULL, "");

  Claim(TILookup(100, trie) == NULL, "");
  Claim(TILookup(101, trie) == NULL, "");
  
  TIVisit(trie, visitFunc);
}

#endif /* RTDEBUG */
