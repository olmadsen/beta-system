#include "trie.h"
#include <stdio.h>
#include <string.h>

#ifdef sparc
#define OURINLINE __inline__
#else
#define OURINLINE
#endif

#ifdef nti
#include <memory.h>
#include <tchar.h>
#endif /* nti */

#include <stdlib.h>

#ifdef sgi
#include <string.h>
#endif /* sgi */

#if 0
extern FILE *output;
#define TRACE(msg) fprintf(output, "trie.c:%d: %s\n", __LINE__, msg); fflush(output)
#define TRACEX(msg,v) fprintf(output, "trie.c:%4d: %25s: 0x%08x\n", __LINE__, msg,(int)v); fflush(output)
#else
#define TRACE(msg)
#define TRACEX(msg,v)
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
				 unsigned long contents, 
				 Node *current, 
				 Trie *trie,
				 unsigned long insertKey);
static OURINLINE void insertRight(unsigned long key, 
				  unsigned long contents, 
				  Node *current, 
				  Trie *trie,
				  unsigned long insertKey);
static void _TInsert(unsigned long key, 
		     unsigned long contents, 
		     Node *current, 
		     Trie *trie,
		     unsigned long insertKey);
static OURINLINE unsigned long downLookup(unsigned long key, Node *current, Trie *trie);
static OURINLINE unsigned long rightLookup(unsigned long key, Node *current, Trie *trie);
static unsigned long _TILookup(unsigned long key, Node *current, Trie *trie);
static void _TIVisit(Node *current, Trie *trie, void (*visitFunc)(contentsBox *));
static void _TIFree(Node *current, Trie *trie, void (*freeFunc)(unsigned long));
/* TEXT TRIES */
static unsigned long _TTLookup(char *key, Node *current, Trie *trie);
static void _TTInsert(char *key, unsigned long contents, Node *current, Trie *trie);

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
  TRACEX("TInit: new", new);
  return new;
}

static void TRealloc(Trie **trie)
{
  Trie *new;
  
  new = (Trie *)calloc(1, 2 * sizeof(unsigned long) + 2 * (*trie) -> size);
  memcpy(&(new -> buffer[0]), (*trie) -> buffer, (*trie) -> top);
  new -> size = (*trie) -> size * 2;
  new -> top = (*trie) -> top;
  
  TRACEX("TRealloc: free", *trie);
  free(*trie);
  TRACEX("TRealloc: new", new);
  *trie = new;
}

static unsigned long allocNode(Trie *trie)
{
  TRACEX("allocNode: trie", trie);
  if (trie -> top + sizeof(struct Node) < trie -> size) {
    trie -> top += sizeof(struct Node);
    return trie -> top - sizeof(struct Node);
  } else {
    return 0;
  }
}

static unsigned long allocContentsBox(Trie *trie)
{
  TRACEX("allocContentsBox: trie", trie);
  if (trie -> top + sizeof(struct contentsBox) < trie -> size) {
    trie -> top += sizeof(struct contentsBox);
    return trie -> top - sizeof(struct contentsBox);
  } else {
    return 0;
  }
}

static OURINLINE void insertDown(unsigned long key, 
				 unsigned long contents, 
				 Node *current, 
				 Trie *trie,
				 unsigned long insertKey)
{
  TRACEX("insertDown: trie", trie);
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
				  unsigned long contents, 
				  Node *current, 
				  Trie *trie,
				  unsigned long insertKey)
{
  TRACEX("insertRight: trie", trie);
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
	     unsigned long contents, 
	     Trie **trie, 
	     unsigned long insertKey)
{
  /* Make sure that there is enough room to hold the new value */
  /* A max of log10(key) new nodes + one contentsbox might be generated */
  
  TRACEX("TInsert: trie", *trie);
  if ((*trie) -> top + 
      (sizeof(struct Node) * 20) + 
      sizeof(struct contentsBox) < (*trie) -> size) {
    _TInsert(key, contents, HEAD((*trie)), *trie, insertKey);
  } else {
    TRealloc(trie);
    TInsert(key, contents, trie, insertKey);
  }
}

#define TRIEFACTOR 8
static void _TInsert(unsigned long key, 
		     unsigned long contents, 
		     Node *current, 
		     Trie *trie,
		     unsigned long insertKey)
{
  TRACEX("_TInsert: trie", trie);
  if (key > TRIEFACTOR) {
    if (current -> d == (char)-1) {
      current -> d = (char)(key % TRIEFACTOR);
      insertDown(key / TRIEFACTOR, contents, current, trie, insertKey);
    } else {
      if ((char)(key % TRIEFACTOR) == current -> d) {
	insertDown(key / TRIEFACTOR, contents, current, trie, insertKey);
      } else {
	insertRight(key, contents, current, trie, insertKey);
      }
    }
  } else {
    if (current -> d == (char)-1) {
      current -> d = (char)key;
      current -> contents = allocContentsBox(trie);
      CONTENTSBOX(current -> contents) -> contents = contents;
      CONTENTSBOX(current -> contents) -> key = insertKey;
    } else {
      if ((char)key == current -> d) {
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

static OURINLINE unsigned long downLookup(unsigned long key, Node *current, Trie *trie)
{
  TRACEX("downLookup: trie", trie);
  if (current -> down != 0) {
    return _TILookup(key, NODE(current -> down), trie);
  } else {
    return 0;
  }
}

static OURINLINE unsigned long rightLookup(unsigned long key, Node *current, Trie *trie)
{
  TRACEX("rightLookup: trie", trie);
  if (current -> right != 0) {
    return _TILookup(key, NODE(current -> right), trie);
  } else {
    return 0;
  }
}

unsigned long TILookup(unsigned long key, Trie *trie)
{
  TRACEX("TILookup: trie", trie);
  return _TILookup(key, HEAD(trie), trie);
}

static unsigned long _TILookup(unsigned long key, Node *current, Trie *trie)
{
  TRACEX("_TILookup: trie", trie);
  if (key > TRIEFACTOR) {
    if ((char)(key % TRIEFACTOR) == current -> d) {
      return downLookup(key / TRIEFACTOR, current, trie);
    } else {
      return rightLookup(key, current, trie);
    }
  } else {
    if ((char)key == current -> d) {
      if (current -> contents != 0) {
	return CONTENTSBOX(current -> contents) -> contents;
      } else {
	return 0;
      }
    } else {
      return rightLookup(key, current, trie);
    }
  }
}

void TIVisit(Trie *trie, void (*visitFunc)(contentsBox *))
{
  TRACEX("TIVisit: trie", trie);
  _TIVisit(HEAD(trie), trie, visitFunc);
}

static void _TIVisit(Node *current, Trie *trie, void (*visitFunc)(contentsBox *))
{
  TRACEX("_TIVisit: trie", trie);
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

void TIFree(Trie *trie, void (*freeFunc)(unsigned long))
{
  TRACEX("TIFree: trie", trie);
  if (freeFunc) {
    _TIFree(HEAD(trie), trie, freeFunc);
  }
  free(trie);
}

static void _TIFree(Node *current, Trie *trie, void (*freeFunc)(unsigned long))
{
  TRACEX("_TIFree: trie", trie);
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

static Trie **_dst;

void addFunc(contentsBox *cb)
{ 
    TInsert(cb -> key, 
            cb -> contents, 
            _dst, 
            cb -> key);
}

void TIadd(Trie **dst, Trie *src)
{
  TRACEX("_TIFree: src", src);
    _dst = dst;
    TIVisit(src, addFunc);
}

/* Below we include functions very similar to the above, only the key
   used to insert objects in the trie comes in the form of character
   strings. */

/* LOOKUP */

unsigned long TTLookup(char *key, Trie *trie)
{
  TRACEX("TTLookup: trie", trie);
  if (key) {
    if (key[0] != '\0') {
      return _TTLookup(key, HEAD(trie), trie);
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

static unsigned long _TTLookup(char *key, Node *current, Trie *trie)
{
  TRACEX("_TTLookup: trie", trie);
  if (/* key > TRIEFACTOR */ key[1] != '\0') {
    if (/* key % TRIEFACTOR == current -> d */ key[0] == current -> d) {
      return downLookup(/* key / TRIEFACTOR */ (unsigned long)(key + 1), current, trie);
    } else {
      return rightLookup((unsigned long)key, current, trie);
    }
  } else {
    if (/* key == current -> d*/ key[0] == current -> d) {
      if (current -> contents != 0) {
	return CONTENTSBOX(current -> contents) -> contents;
      } else {
	return 0;
      }
    } else {
      return rightLookup((unsigned long)key, current, trie);
    }
  }
}

/* INSERT */

void TTInsert(char *key, 
	      unsigned long contents, 
	      Trie **trie)
{
  /* Make sure that there is enough room to hold the new value */
  /* A max of strlen(key) new nodes + one contentsbox might be generated */
  
  TRACEX("TTInsert: trie", *trie);
  if ((*trie) -> top + 
      (sizeof(struct Node) * strlen(key)) + 
      sizeof(struct contentsBox) < (*trie) -> size) {
    _TTInsert(key, contents, HEAD((*trie)), *trie);
  } else {
    TRealloc(trie);
    TTInsert(key, contents, trie);
  }
}

static void _TTInsert(char *key, 
		      unsigned long contents, 
		      Node *current, 
		      Trie *trie)
{
  TRACEX("_TTInsert: trie", trie);
  if (/* key > TRIEFACTOR */ key[1] != 0) {
    if (current -> d == -1) {
      current -> d = /* key % TRIEFACTOR */ key[0];
      insertDown(/* key / TRIEFACTOR */ (unsigned long)(key + 1), 
		 contents, 
		 current, 
		 trie,
		 0);
    } else {
      if (/* key % TRIEFACTOR == current -> d */ key[0] == current -> d) {
	insertDown(/* key / TRIEFACTOR */ (unsigned long)(key + 1), 
		   contents, 
		   current, 
		   trie,
		   0);
      } else {
	insertRight((unsigned long)key, contents, current, trie, 0);
      }
    }
  } else {
    if (current -> d == -1) {
      current -> d = /* key */ key[0];
      current -> contents = allocContentsBox(trie);
      CONTENTSBOX(current -> contents) -> contents = contents;
      CONTENTSBOX(current -> contents) -> key = 0;
    } else {
      if (/* key == current -> d */ key[0] == current -> d) {
	if (current -> contents == 0) {
	  current -> contents = allocContentsBox(trie);
	} 
	CONTENTSBOX(current -> contents) -> contents = contents;
	CONTENTSBOX(current -> contents) -> key = 0;
      } else {
	insertRight((unsigned long)key, contents, current, trie, 0);
      }
    }
  }
}
  
/* TESTING */
#ifdef RTDEBUG
#define Assert(cond, message) if (!(cond)) { fprintf(stderr, message); } 
void visitFunc(contentsBox *cb)
{
  printf("visitFunc: %s\n", (char *)(cb -> contents));
}

void testTrie(void)
{
  Trie *trie;
  
  trie = TInit();

  /* test integer trie */
#define TINSERT(x,y,z,v) \
  fprintf(stderr, "TInsert(%s)\n", (char*)y); fflush(stderr); \
  TInsert(x,y,z,v)
  
  TINSERT(10101, (unsigned long)"10101 inserted", &trie, 0);
  TINSERT(0, (unsigned long)"0 inserted", &trie, 0);
  TINSERT(1, (unsigned long)"1 inserted", &trie, 0);
  TINSERT(1, (unsigned long)"1 inserted", &trie, 0);
  TINSERT(10101, (unsigned long)"10101 inserted again", &trie, 0);
  TINSERT(1010111, (unsigned long)"1010111 inserted", &trie, 0);
  
  Assert(TILookup(10101, trie) != 0, "\n");
  Assert(TILookup(0, trie) != 0, "\n");
  Assert(TILookup(1, trie) != 0, "\n");
  Assert(TILookup(1010111, trie) != 0, "\n");
  Assert(TILookup(100, trie) == 0, "\n");
  Assert(TILookup(101, trie) == 0, "\n");
  
  TIVisit(trie, visitFunc);

  /* test text trie */
#define TTINSERT(x,y,z) \
  fprintf(stderr, "TTInsert(%s)\n", (char*)y); fflush(stderr); \
  TTInsert(x,y,z)

  {
    Trie *textTrie;
    
    textTrie = TInit();
    
    TTINSERT("10101", (unsigned long)"10101 inserted", &textTrie);
    TTINSERT("0", (unsigned long)"0 inserted", &textTrie);
    TTINSERT("1", (unsigned long)"1 inserted", &textTrie);
    TTINSERT("1", (unsigned long)"1 inserted", &textTrie);
    TTINSERT("10101", (unsigned long)"10101 inserted again", &textTrie);
    TTINSERT("1010111", (unsigned long)"1010111 inserted", &textTrie);
    
    Assert(TTLookup("10101", textTrie) != 0, "\n");
    Assert(TTLookup("0", textTrie) != 0, "\n");
    Assert(TTLookup("1", textTrie) != 0, "\n");
    Assert(TTLookup("1010111", textTrie) != 0, "\n");
    Assert(TTLookup("100", textTrie) == 0, "\n");
    Assert(TTLookup("101", textTrie) == 0, "\n");

    TIVisit(textTrie, visitFunc);
  }
}

#endif /* RTDEBUG */
