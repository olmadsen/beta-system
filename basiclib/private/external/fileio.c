#if defined(sun4s) || defined(hpux9pa) || defined(linux) || defined(sgi)
#define UNIX
#endif

#include <stdio.h>
#ifdef UNIX
#include <errno.h>
#include <sys/time.h>
#endif

int EOFvalue(void)
{
  return EOF;
}


int EOFfunction(FILE *F)
{
  return feof(F);
}

/* Functions supporting File.GetLine and File.GetAtom */

#define INITBUFFERSIZE  500   /* Initial size of Buffer. */
#define isEOF(ch) (((signed char)ch)==EOF)

static char *Buffer;          /* Buffer space allocate here. */
static int   BufferSize=0;    /* Current size of Buffer. */
static int   streamError;

static void OutOfMemError(char *type)
{
  fprintf(stderr, "Warning: Out of memory during File.Get%s\n", type);
  streamError=1;
}

static void InitBuffer(char *type)
{
  BufferSize=INITBUFFERSIZE;
  Buffer=(char *)malloc(BufferSize);
  if(!Buffer) OutOfMemError(type);
}


/* EnlargeBuffer:
 * Double the size of Buffer or allocate an initial Buffer. 
 */
static void EnlargeBuffer(char *type)
{
  BufferSize*=2;
  Buffer=(char*)realloc(Buffer,BufferSize);
  if(!Buffer) OutOfMemError(type);
}

/* EofInGetStringFromFile:
 * Return whether or not last call to GetStringFromFile met an EOF. 
 */
int EofInGetStringFromFile(void)
{
  return(streamError);
}

/* GetStringFromFile:
 * Read a string from the file. If toEOL is true then read to end of line,
 * else read to first space. Skip the character (eol or space) that causes
 * reading to stop.
 * Call StreamError afterwards to see if operation succeeded.
 */
char *GetStringFromFile(FILE *S, int toEOL)
{
  FILE *F;
  char *ptr;
  int  i, oldSize;
  unsigned char ch;
  
  if(!BufferSize) {
    /* The first time, initialize Buffer. */
    InitBuffer((toEOL)? "Line" : "Atom");
  }
  F=S;
  streamError=0;
  oldSize=0 /* This much of Buffer currently used. */;                 
  if(!toEOL) {
    /* GetAtom: Skip to first non-blank. */
    while((ch=getc(F))<=' ' && !isEOF(ch)) 
      /* SKIP */ ;
    if(isEOF(ch) || ungetc(ch,F)==EOF) {
      /* Only blanks on line */
      streamError=1;
      return("");
    }
  }
  while(1) {
    ptr=Buffer+oldSize; /* Insert from this place in Buffer. */
    i=BufferSize-oldSize;
    while(i--) {
      /* More room in Buffer. */
      ch=getc(F);
      if ((toEOL && ch=='\n') || (!toEOL && ch<=' ') ){
	streamError=0;
	*ptr++ = 0; /* NULL terminate */
	return(Buffer);
      }
      if (isEOF(ch)) {
	streamError=1;
	*ptr++ = 0; /* NULL terminate */
	return(Buffer);
      }
      *ptr++ = ch;
    }
    oldSize=BufferSize;
    EnlargeBuffer((toEOL)? "Line" : "Atom");
  }
}
