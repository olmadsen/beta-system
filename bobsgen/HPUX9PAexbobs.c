/* Output from p2c, the Pascal-to-C translator */
/* From input file "exbobs.p" */


/*****************************************************************************
 *  B O B S - SYSTEM
 *  PARSER GENERATOR
 *
 * UNIVERSITY OF AARHUS, DENMARK
 *
 * AUTHORS:
 *   SQREN HENRIK ERIKSEN
 *   BENT BAEK JENSEN
 *   BENT BRUUN KRISTENSEN
 *   OLE LEHRMANN MADSEN
 *
 * VERSION: January 1985
 * This version has been heavily modified. It is not compatible with
 * previous versions of BOBS. Contact Ole Lehrmann Madsen for further
 * documentation. In most cases the "standard" manual may still be used:
 *      "THE B O B S - SYSTEM"
 *       DAIMI PB-71. Third printing
 *       DEPT. OF COMPUTER SCIENCE, UNIVERSITY OF AARHUS,
 *       NY MUNKEGADE, DK8000 AARHUS C, DENMARK.
 *
 * THIS PROGRAM WAS ORIGINALLY IMPLEMENTED IN THE FIRST VERSION OF
 * PASCAL RELEASED FROM N.WIRTH. THIS IMPLEMENTATION WAS FULFILLED IN
 * MARCH 1972. SINCE THEN, THE SYSTEM HAS BEEN CHANGED IN SEVERAL WAYS.
 * AMONG OTHERS, IT HAS BEEN CONVERTED INTO STANDARD PASCAL.
 * THE SYSTEM IS INTENDED TO BE PORTABLE, HOWEVER THERE IS NO GUARANTEE
 * FOR THIS. YOU SHOULD BE AWARE OF (AT LEAST) THE FOLLOWING THINGS:
 *  - THE TYPE CHAR, - THE TYPE ALFA, - THE MAXIMUM SIZE OF SETS.
 *  SEE THE CONSTANTS: MINCH,MAXCH,SETMAX,ALFALENGTH IN THE PROGRAM.
 *  THESE CONSTANTS SHOULD EASE MOVING THE SYSTEM. NOTE, IF YOU CHANGE
 *  THE CONSTANT ALFALENGTH, YOU MAY HAVE PROBLEMS WITH STRINGS.
 *
 * DUE TO THE MANY CHANGES IN THE SYSTEM, THE PROGRAMMING IS NOT SO
 * NICE AS WE WOULD LIKE IT TO BE. YOU SHOULD NOT TRY TO MAKE CHANGES
 * YOURSELF. IF YOU FIND ERRORS OR 'OTHERS' YOU MAY WISH TO CHANGE,
 * PLEASE WRITE TO US. WRITE IN ANY CASE AND TELL US WHAT PROBLEMS
 * YOU HAD IN GETTING THE SYSTEM TO RUN.
 * NOTE: WE CANNOT GUARANTEE ANY SUPPORT OF THE SYSTEM .
 *
 * Changes: March-May 1993:
 * - to adapt to p2c program, which translates pascal into C /JLK
 * - fix of error when 'duplicate terminals'. All duplicates were
 *   assigned a new internal number. This gave an error when name, etc.
 *   were dublicated. /OLM
 * - reserved terminals like NAME, KONST, STRING, ERROR, EMPTY have
 *   changed into _NAME_, _KONST_, _STRING_, _ERROR_, _EMPTY_.
 *   This has been done in order to allow, NAME, etc. as legal
 *   terminal symbols in the grammar. /OLM
 * Changes: March 1994:
 * - removed 'packed' from all data structures, since the gcc (GNU C)
 *   compiler generate wrong code on SUN Solaris (SPARC). /JLK
 * Changes September 1994:
 * - removed dependency on sequential allocation of dynamic structures
 *   in the heap from the operation stateno.  It did not work on Linux
 *   machines.  Instead, a global variable, seqIndex is introduced.
 *   Each time a 'pointer' is allocated (in the allocp operation), the
 *   seqIndex is incremented, and the new value is assigned to the new
 *   field, seq, in the record.  In stateno, this field is now used in
 *   the binary search, instead of the actual pointer addresses. /JLK
 * Changes August 1994, v1.3/OLM:
 *  - In procedure lookahead:trans an error was corrected; see comment
 *  - minor error in write stmt corrected in niceparser
 * Changes August 1994, v1.4/OLM:
 *  - All terminals muts now be enclosed by metasymbol 5, default is ";
 *    This is the case for the initial list of terminals as well as
 *    terminal symbols in productions; version meta/v1.4/gen has been adapted
 *    to this version of bobs
 *  - Changes in tables format to be used by tabc.bet. A dot (.) has been
 *    inserted between label and production numnber; does not affect bobs,
 *    but only meta-gen and tabc.
 */
/*$b0*/
/* to turn off output buffering insert  $b0  */


#include <p2c/p2c.h>


/* removed by JLK to please p2c: ,parsin,parsout,tables*/

#define const1          2400
#define const2          900
#define const3          720

#define const4          80000L   /* JLK: 17/6-95 was 40000 */

#define const5          63
#define const6          6000
#define const7          20000
#define const8          480   /* JLK: 17/6-95 was 240 */
#define const9          10000   /* ESS: 30/6-95 was 2000 */
#define const10         7200
#define const11         130
#define const12         840
#define const13         5
#define const14         15
#define const16         10000
/*NOTICE: CONST16>CONST2*/
/* JLK: 17/6-95 was 5000 */
#define const18         75
#define const19         12000   /*MAX SIZE OF ARRAY LABELBUF/ SUM OF LENGTH */
/* OF ALL PRODUCTION LABELS (OPTIONS[34])   */
#define const20         1200   /*max length of a production label */

#define minch           ' '
#define maxch           '~'   /*THE FIRST/LAST CHAR IN TYPE CHAR*/

#define setmax          63   /*MAX. VALUE OF INTEGERS IN A SET */
#define alfalength      10   /* NO. OF CHARS IN TYPE ALFA */
#define alfal20         20
    /* NB! this is a quick change ; length of type alfa20*/
#define alf3            31   /*MUST BE 3*ALFALENGTH+1 */

#define rhsnil          0   /*THE EMPTY REFERENCE OF CHAINS IN RHS*/

#define blank           "          "
#define blank20         "                    "


/*packed*/
typedef Char alfa_[alfalength];
typedef short symbol;

typedef long rtypeset[setmax / 32 + 2];

typedef struct rtype {
  rtypeset r[const13 + 1];
} rtype;

typedef struct nontelm {
  alfa_ word1, word2, word3;
  struct nontelm *rlink, *llink;
  short nontermvaerdi;
} nontelm;   /*packed*/

typedef long pointer2;

typedef struct termelm {
  struct termelm *niveaup, *higherp;
  short intern;
  Char tegn;
  boolean ok;
} termelm;   /*packed*/

typedef struct prodtype {
  short leftside;
  pointer2 start;
  struct konfigt *lookbackp;
  char laengde;
} prodtype;   /*packed*/

typedef struct entrytyp {
  termelm *dummyyp, *termp;
  short intern1;
  Char tegn1;
  boolean ok1;
} entrytyp;   /*packed*/

typedef rtype bitmatrix[const2 + 1];
typedef char modetype;

typedef struct konfigt {
  /*packed*/
  struct konfigt *derivp, *nextp;
  modetype dot;   /* DOT-PLACERING TIL BRUG I ADEQUAD */
  boolean ifbasis;
  /* added by jlk to solve Linux problem */
  long seq;
  modetype mode;
  union {
    struct {
      short inf;
      short prodnr;
    } U1;
    struct konfigt *lookbp;
  } UU;
} konfigt;

typedef enum {
  firsttim, finish
} erastype;
/*packed*/
typedef Char dayfilemsg[40];
/*packed*/
typedef Char alfa20[alfal20];


typedef struct _REC_rhs {
  /*packed*/
  short symbol_;
  konfigt *parserp;
  pointer2 link;
  char basisl;
  boolean basis;
  short first;
  short length;
  /*ADDRESS OF PRODUCTION LABEL IN LABELBUF (OPTIONS[34])*/
  long seqno;   /* input seqNo of this production */
} _REC_rhs;

typedef struct _REC_help {
  /*packed*/
  boolean afledt, overgang;
  short prodindex;
  pointer2 rightp;
  erastype status;
  boolean term;
} _REC_help;

typedef struct _REC_tilstand {
  /*packed*/
  short errorno;
  konfigt *oldstart;
  short newstart;
} _REC_tilstand;

typedef struct _REC_husknonterm {
  /*packed*/
  nontelm *nontermp;
  boolean leftboo, rightboo;
} _REC_husknonterm;

typedef struct _REC_fcq {
  /*packed*/
  konfigt *udgang;
  short frekvens;
} _REC_fcq;

typedef struct _REC_prodspl {
  /*packed*/
  unsigned short splstart, spllen;
} _REC_prodspl;

typedef struct _REC_symbspl {
  /*packed*/
  unsigned short splstart, spllen;
} _REC_symbspl;


/* line added by jlk to solve Linux problem */
Static long seqIndex;
Static entrytyp entry_[256];
Static _REC_rhs rhs[const4 + 1];
Static pointer2 lefthelp[const2 + 1];
Static prodtype prod[const1 + 1];
Static _REC_help help[const2 + 1];
Static _REC_tilstand tilstand[const10 + 1];
Static alfa20 internrep[const2 + 2];
Static long husk[const2];
Static _REC_husknonterm husknonterm[const2 + 1];

Static long prodcount, emptyvalue, errorval, nameval, cstval, stringval;
Static Char stringch;

Static nontelm *last, *first, *dynp, *statp;
Static pointer2 point, huskp, helpp, top;
Static termelm *termtop, *gl, *gn, *gc, *gs, *go;

Static Char ch, s;

Static short internv;
Static long antalprod, antaltilst, tilstnr, lbbegin, lbend, trmax, nontslut,
	    nontstart, mstime, k, j, i, tal, count, goalhusk, empty,
	    termantal, termrep, symb, termg, optno, dummy;
Static boolean error, nontermboo, goaltest, emptyboo, goalboo, errorboo,
	       venstreboo, first37, nboo1, nboo2, noword, firstboo, error1,
	       error2, error3;

Static konfigt *rodp, *begintilst, *lqbep, *classtop, *gemp, *oldp, *freeptr;

Static FILE *blst, *parsin, *parsout, *tables;

Static _REC_fcq fcq[const3];
Static long fcqi;
/* FCQ AND FCQI ARE USED IN PROCEDURE
   REMEMBER AND OPTIMIZE, */
Static boolean options[const18];


Static long combegin, comlength;
/*packed*/
Static Char comend[alfalength];

/*VARIABLES TO STORE AND READ PRODUCTION LABELS (OPTIONS[33,34])*/
/*packed*/
Static Char labelbuf[const19 + 1];
Static short linx;
Static long prodseqno;
Static long nolook[const1 + 1];
Static long nolooki;   /* INIT=0 */
Static boolean allnolook;   /* IS ALL PRODUCTIONS TO BE ATTEMPTED? */
/* used by procedure initempty and lookahead procedures  */
/* emptya[symb]=true if symb may produce the empty string*/
Static boolean emptya[const2 + 1];

/* variables used in order to parse sentential forms */
Static long nontl, nontr;
/* lookBackEntry: array[0..const2] of pointer; */

Static long cstmax[20];

/*$L-*/
/***************** grammar to ROSE    *********************************/

Static _REC_prodspl prodspl[const1 + 1];
Static _REC_symbspl symbspl[const2 + 1];
Static long splstart, spllen;
Static FILE *spltab, *f1, *f2, *f3, *f4, *f5;


Static void initspl(void)
{
  if (spltab != NULL)
    spltab = freopen("spltab   ", "w", spltab);
  else
    spltab = fopen("spltab   ", "w");
  if (spltab == NULL)
    _EscIO(FileNotFound);
  splstart = 1;
  spllen = 0;
}


Static void splch(Char ch)
{
  spllen++;
  putc(ch, spltab);
}


Static void syspl(long sy)
{
  symbspl[sy].splstart = splstart;
  symbspl[sy].spllen = spllen;
  splstart += spllen;
  spllen = 0;
}


Static void prspl(long p)
{
  prodspl[p].splstart = splstart;
  prodspl[p].spllen = spllen;
  splstart += spllen;
  spllen = 0;
}


Static void spl(Char *a)
{
  long i;

  for (i = 0; i < alfalength; i++) {
    if (a[i] != ' ')
      splch(a[i]);
  }
}


Static void spl20(Char *a)
{
  long i;

  for (i = 0; i < alfal20; i++) {
    if (a[i] != ' ')
      splch(a[i]);
  }
}


Static void tv(nontelm *p)
{
  if (p == NULL)
    return;
  tv(p->llink);
  tv(p->rlink);
  spl(p->word1);
  spl(p->word2);
  spl(p->word3);
  syspl(p->nontermvaerdi);
}


Static void rosegram(void)
{
  long l, p, i, c, abrhslen, corhslen, rhsinx, FORLIM;
  _REC_rhs *WITH;
  long FORLIM1;
  prodtype *WITH1;
  _REC_prodspl *WITH2;
  _REC_symbspl *WITH3;

  /* spelling tables */
  initspl();
  FORLIM = termg;
  /*terminal symbols*/
  for (c = 0; c <= FORLIM; c++) {
    spl20(internrep[c + 1]);
    syspl(c);
  }
  /* nonterminal symbols*/
  tv(first);
  FORLIM = antalprod;
  /* production labels*/
  for (p = 0; p <= FORLIM; p++) {
    WITH = &rhs[prod[p].start];
    FORLIM1 = WITH->first + WITH->length;
    for (i = WITH->first; i < FORLIM1; i++)
      splch(labelbuf[i]);
    prspl(p);
  }

  abrhslen = 0;
  corhslen = 0;
  FORLIM = antalprod;
  for (p = 0; p <= FORLIM; p++) {
    WITH1 = &prod[p];
    FORLIM1 = WITH1->start + WITH1->laengde;
    for (i = WITH1->start + 1; i <= FORLIM1; i++) {
      corhslen++;
      if (rhs[i].symbol_ > termg)
	abrhslen++;
    }
  }

  if (f1 != NULL)
    f1 = freopen("f1       ", "w", f1);
  else
    f1 = fopen("f1       ", "w");
  if (f1 == NULL)
    _EscIO(FileNotFound);
  if (f2 != NULL)
    f2 = freopen("f2       ", "w", f2);
  else
    f2 = fopen("f2       ", "w");
  if (f2 == NULL)
    _EscIO(FileNotFound);
  if (f3 != NULL)
    f3 = freopen("f3       ", "w", f3);
  else
    f3 = fopen("f3       ", "w");
  if (f3 == NULL)
    _EscIO(FileNotFound);
  if (f4 != NULL)
    f4 = freopen("f4       ", "w", f4);
  else
    f4 = fopen("f4       ", "w");
  if (f4 == NULL)
    _EscIO(FileNotFound);
  if (f5 != NULL)
    f5 = freopen("f5       ", "w", f5);
  else
    f5 = fopen("f5       ", "w");
  if (f5 == NULL)
    _EscIO(FileNotFound);
  fprintf(f1, "%12ld", antalprod);
  fprintf(f2, "%12ld", nontslut - nontstart + 1);
  fprintf(f3, "%12ld", abrhslen);
  fprintf(f4, "%12ld", antalprod);
  fprintf(f5, "%12ld", corhslen);

  l = 1;
  rhsinx = 1;
  FORLIM = antalprod;
  for (p = 0; p <= FORLIM; p++) {
    WITH1 = &prod[p];
    WITH2 = &prodspl[p];
    fprintf(f4, "%12d%12ld%12d%12u%12u",
	    WITH1->leftside, rhsinx, WITH1->laengde, WITH2->splstart,
	    WITH2->spllen);
    c = 0;
    FORLIM1 = WITH1->start + WITH1->laengde;
    for (i = WITH1->start + 1; i <= FORLIM1; i++) {
      rhsinx++;
      /***********************************************
                with SymbSpl[rhs[i].symbol] do
                 if rhs[i].symbol <= termg then
                    write(f5,0,SplStart,SplLen)
                 else begin c:=c+1;
                   write(f5,1,c);
                   write(f3,rhs[i].symbol)
                 end;
***************************************************/
    }
    fprintf(f1, "%12d%12ld%12ld", WITH1->leftside, l, c);
    l += c;
  }

  FORLIM = nontslut;
  for (i = nontstart; i <= FORLIM; i++) {
    WITH3 = &symbspl[i];
    fprintf(f2, "%12u%12u", WITH3->splstart, WITH3->spllen);
  }

}


/******************** end ROSE *************************************/
/*$L-*/

Static void initmax(void)
{
  long i;

  for (i = 0; i <= 19; i++)
    cstmax[i] = 0;
}


Static void updatemax(long cst, long val)
{
  if (cstmax[cst - 1] < val)
    cstmax[cst - 1] = val;
}


Static void printmax(void)
{
  long i;

  fprintf(blst, "\n statistics :\n");
  for (i = 1; i <= 20; i++) {
    fprintf(blst, " const%ld used %12ld of ", i, cstmax[i - 1]);
    switch (i) {

    case 1:
      fprintf(blst, "%ld\n", (long)const1);
      break;

    case 2:
      fprintf(blst, "%ld\n", (long)const2);
      break;

    case 3:
      fprintf(blst, "%ld\n", (long)const3);
      break;

    case 4:
      fprintf(blst, "%ld\n", const4);
      break;

    case 5:
      fprintf(blst, "%ld\n", (long)const5);
      break;

    case 6:
      fprintf(blst, "%ld\n", (long)const6);
      break;

    case 7:
      fprintf(blst, "%ld\n", (long)const7);
      break;

    case 8:
      fprintf(blst, "%ld\n", (long)const8);
      break;

    case 9:
      fprintf(blst, "%ld\n", (long)const9);
      break;

    case 10:
      fprintf(blst, "%ld\n", (long)const10);
      break;

    case 11:
      fprintf(blst, "%ld\n", (long)const11);
      break;

    case 12:
      fprintf(blst, "%ld\n", (long)const12);
      break;

    case 13:
      fprintf(blst, "%ld\n", (long)const13);
      break;

    case 14:
      fprintf(blst, "%ld\n", (long)const14);
      break;

    case 15:
      fprintf(blst, " not used \n");
      break;

    case 16:
      fprintf(blst, "%ld\n", (long)const16);
      break;

    case 17:
      fprintf(blst, " not used \n");
      break;

    case 18:
      fprintf(blst, "%ld\n", (long)const18);
      break;

    case 19:
      fprintf(blst, "%ld\n", (long)const19);
      break;

    case 20:
      fprintf(blst, " not used \n");
      break;
    }
  }
}


Static long clock(void)
{
  return 0;
}


Static void msg(Char *m)
{
  /* WRITES A MESSAGE IN THE KRONOS DAYFILE */
  /* THIS PROCEDURE MAY BEE REMOVED         */
  fprintf(blst, "%.40s\n", m);
}


Static void writech(Char ch, long no)
{
  long i;

  for (i = 1; i <= no; i++)
    putc(ch, blst);
}


Static Char lf(void)
{
  putc('\n', blst);
  return ' ';
}  /*LF*/


Static void allocate(pointer2 *p);


Static void outalf(Char *a, long *t)
{
  long i;
  Char STR1[256];

  sprintf(STR1, "%.*s", alfalength, a);
  if (!strcmp(STR1, blank))
    return;
  i = alfalength;
  while (a[i - 1] == ' ')
    i--;
/* p2c: exbobs.p, line 418: Note:
 * Format for packed-array-of-char will work only if width < length [321] */
  fprintf(blst, "%.*s", (int)i, a);
  *t += i;
}


Static void outalf20(Char *a, long *t)
{
  long i;
  Char STR1[256];

  sprintf(STR1, "%.*s", alfal20, a);
  if (!strcmp(STR1, blank20))
    return;
  i = alfal20;
  while (a[i - 1] == ' ')
    i--;
/* p2c: exbobs.p, line 428: Note:
 * Format for packed-array-of-char will work only if width < length [321] */
  fprintf(blst, "%.*s", (int)i, a);
  *t += i;
}


Static void nontwrit(long i, long *t)
{
  nontelm *WITH;

  putc('<', blst);
  (*t)++;
  if (i == 0)
    outalf("BOBSGO    ", t);
  else {
    if (const2 < i)
      fprintf(blst, "index error in nontwrit\n");
    else {
      if (husknonterm[i].nontermp == NULL) {
	if (i == nontstart)
	  fprintf(blst, "GoalSymbol");
	else
	  fprintf(blst, "NIL pointer in nontwrit");
      } else {
	WITH = husknonterm[i].nontermp;
	outalf(WITH->word1, t);
	outalf(WITH->word2, t);
	outalf(WITH->word3, t);
      }
    }
  }
  putc('>', blst);
  (*t)++;
}


Static void symbwrite(long i, long *t)
{
  if (i <= termg)
    outalf20(internrep[i + 1], t);
  else
    nontwrit(i, t);
}


#define pagew           85
#define labelpos        70


/* Local variables for outgrammar: */
struct LOC_outgrammar {
  long altpos;
} ;

Local void lfcheck(long i, long *pos, long max, long indpos,
		   struct LOC_outgrammar *LINK)
{
  long j;

  if (i + *pos <= max) {
    *pos += i;
    return;
  }
  putc('\n', blst);
  for (j = 1; j <= indpos; j++)
    putc(' ', blst);
  *pos = i + indpos;
}

Local void writenont(long n, long *pos, struct LOC_outgrammar *LINK)
{
  long i, j;
  /*packed*/
  Char c[alf3];
  nontelm *WITH;

  if (n == 0) {
    fprintf(blst, "BOBS-GO");
    *pos += 7;
    return;
  }
  if (n == nontstart) {
    fprintf(blst, "GoalSymbol");
    *pos += 10;
    return;
  }
  WITH = husknonterm[n].nontermp;
  for (i = 0; i < alfalength; i++)
    c[i] = WITH->word1[i];
  for (i = 1; i <= alfalength; i++)
    c[i + 9] = WITH->word2[i - 1];
  for (i = 1; i <= alfalength; i++)
    c[i + 19] = WITH->word3[i - 1];
  i = alfalength * 3;
  while (c[i - 1] == ' ')
    i--;
  lfcheck(i + 2, pos, labelpos, LINK->altpos + 3, LINK);
  putc('<', blst);
  for (j = 0; j < i; j++)
    putc(c[j], blst);
  putc('>', blst);
}

Local void writeterm(Char *t, long *pos, struct LOC_outgrammar *LINK)
{
  long i, j;

  i = alfal20;
  while (t[i - 1] == ' ')
    i--;
  lfcheck(i, pos, labelpos, LINK->altpos + 3, LINK);
  for (j = 0; j < i; j++)
    putc(t[j], blst);
}

Local void nextprod(long *lhs, pointer2 *rhsp, long *bobsno, long *seqno,
		    struct LOC_outgrammar *LINK)
{
  long lhsi, k, FORLIM, FORLIM1;

  *bobsno = 0;
  while (true) {
    FORLIM = nontslut;
    for (lhsi = nontstart + 1; lhsi <= FORLIM; lhsi++) {
      *lhs = lhsi;
      *rhsp = help[*lhs].rightp;
      if (*rhsp != rhsnil) {
	do {
	  (*bobsno)++;
	  if (rhs[*rhsp].seqno == *seqno)
	    goto _L10;
	  FORLIM1 = rhs[*rhsp].basisl;
	  for (k = 1; k <= FORLIM1; k++)
	    allocate(rhsp);
	  *rhsp = rhs[*rhsp].link;
	} while (*rhsp != rhsnil);
      }
    }
    (*seqno)++;
  }
_L10: ;
}


/**********/

Static void outgrammar(void)
{
  struct LOC_outgrammar V;
  long lhs, bobsno, oldlhs, pos, symb, p, seqno, k, i;
  pointer2 rhsp, rhsp1;
  long FORLIM, FORLIM1;
  _REC_rhs *WITH;

  fprintf(blst, "\n\f");
  for (k = 1; k <= 45; k++)
    putc('*', blst);
  fprintf(blst, "  The Grammar  ");
  for (k += 15; k <= pagew; k++)
    putc('*', blst);
  fprintf(blst, "\n     BOBS\n");
  oldlhs = 0;
  seqno = 0;
  FORLIM = antalprod;
  for (p = 1; p <= FORLIM; p++) {
    seqno++;
    nextprod(&lhs, &rhsp, &bobsno, &seqno, &V);
    if (lhs != oldlhs)
      putc('\n', blst);
    fprintf(blst, "%4ld%4ld   ", seqno, bobsno);
    pos = 11;
    if (lhs != oldlhs) {
      writenont(lhs, &pos, &V);
      fprintf(blst, " ::= ");
      V.altpos = pos + 2;
      pos += 5;
      oldlhs = lhs;
    } else {
      pos = V.altpos + 3;
      FORLIM1 = V.altpos - 11;
      /* altPos is no.of chars before | */
      for (i = 1; i <= FORLIM1; i++)
	putc(' ', blst);
      fprintf(blst, "|  ");
    }
    rhsp1 = rhsp;
    FORLIM1 = rhs[rhsp].basisl;
    for (k = 1; k <= FORLIM1; k++) {
      allocate(&rhsp1);
      symb = rhs[rhsp1].symbol_;
      if (symb <= termg)
	writeterm(internrep[symb + 1], &pos, &V);
      else
	writenont(symb, &pos, &V);
      putc(' ', blst);
      pos++;
    }
    if (options[32] || options[33]) {
      WITH = &rhs[rhsp];
      for (; pos <= labelpos; pos++)
	putc(' ', blst);
      putc(':', blst);
      FORLIM1 = WITH->first + WITH->length;
      for (k = WITH->first; k < FORLIM1; k++) {
	pos++;
	lfcheck(1, &pos, pagew, labelpos + 2, &V);
	putc(labelbuf[k], blst);
      }
    }
    putc('\n', blst);
  }
  putc('\n', blst);
  for (k = 1; k <= pagew; k++)
    putc('*', blst);
  putc('\n', blst);
}

#undef pagew
#undef labelpos


Static jmp_buf _JL999;



Static void stop(long n)
{
  /* ALL ABNORMAL TERMINATION IS THROUGH THIS PROCEDURE*/
  putc('\n', blst);
  printf("!!!!! ABNORMAL TERMINATION OF BOBS!\n");
  switch (n) {

  case 0:   /*MISCELLANEOUS*/
    break;

  case 1:   /*CONSTERROR*/
    break;

  case 2:
    printf("!!!!! ERROR(S) IN INPUT! See lst-file for details\n");
    break;

  case 3:   /*ERROR(S) IN GRAMMAR*/
    outgrammar();
    fprintf(blst, "***** ERROR(S) IN GRAMMAR \n");
    printf("!!!!! ERROR(S) IN GRAMMAR! See lst-file for details\n");
    break;

  case 4:   /*NOT SLR/LALR(1) */
    break;

  case 5:   /*ERRONEOUS PARSIN FILE*/
    break;

  case 6:
    fprintf(blst, "INFINITE STACK-GROWTH POSSIBLE IN LALRK\n");
    printf("INFINITE STACK-GROWTH POSSIBLE IN LALRK\n");
    break;

  case 7:
    fprintf(blst, "CIRCULARITY IN LALRK\n");
    printf("CIRCULARITY IN LALRK\n");
    break;
  }
  longjmp(_JL999, 1);
}  /*STOP*/


Static void constval(long c, Char *r)
{
  Char gem[21];
  long a, b, i, j;

  if (c >= 1000000L) {
    memcpy(r, "(********)", sizeof(alfa_));
    return;
  }
  a = c;
  gem[11] = ')';
  for (j = 12; j <= 20; j++)
    gem[j] = ' ';
  j = 10;
  do {
    b = a % 10;
/* p2c: exbobs.p, line 598:
 * Note: Using % for possibly-negative arguments [317] */
    a /= 10;
    gem[j] = (Char)(b + '0');
    j--;
  } while (a != 0);
  gem[j] = '(';
  for (i = 0; i < alfalength; i++)
    r[i] = gem[j + i];
}


Static void consterror(Char *s1, Char *s2, long cc)
{
  printf("!!!!! ERROR IN %.*s: %.*sTO SMALL (%ld)\n",
	 alfalength, s1, alfalength, s2, cc);
  fprintf(blst, "\n\n***** ERROR IN %.*s: %.*sTO SMALL (%ld)",
	  alfalength, s1, alfalength, s2, cc);
  /*     constval(cc,aa);
       m[1]:=s2; m[3]:=aa;
       m[2]:=' TO SMALL '; m[4]:='          ';
       for i:=1 to 4 do
       for j:=1 to 10 do ms[(i-1)*10+j]:=m[i,j];
        writeln(ms); writeln(blst,ms);
   */
  stop(0);
}


Static void allocate(pointer2 *p)
{
  /* VAR P:POINTER2 */
  if (*p >= const4)
    consterror("ALLOCATE  ", "CONST4    ", const4);
  (*p)++;
}  /*ALLOCATE*/


Static void initprod(void)
{
  pointer2 p;
  long k, i, l, FORLIM;
  prodtype *WITH;
  long FORLIM1;

  k = -1;
  FORLIM = nontslut;
  for (i = nontstart; i <= FORLIM; i++) {
    p = help[i].rightp;
    while (p != rhsnil) {
      k++;
      if (k > const1)
	consterror("INITPROD  ", "CONST1    ", const1);
      WITH = &prod[k];
      WITH->leftside = i;
      WITH->start = p;
      WITH->laengde = rhs[p].basisl;
      FORLIM1 = WITH->laengde;
      for (l = 1; l <= FORLIM1; l++)
	allocate(&p);
      if (WITH->laengde == 1 && rhs[WITH->start + 1].symbol_ == emptyvalue) {
	/*EMPTY RIGHT HAN
D SIDE*/
	WITH->laengde = 0;
      }
      p = rhs[p].link;
    }
  }
  prod[k + 1].leftside = 0;
  antalprod = k;
}


Static void dump1(void)
{
  long i;
  boolean sorted;
  long seq1, FORLIM;
  _REC_tilstand *WITH;

  fprintf(blst, "%c%c%c TILSTAND", lf(), lf(), lf());
  seq1 = -1;
  sorted = true;
  FORLIM = antaltilst;
  for (i = 0; i <= FORLIM; i++) {
    WITH = &tilstand[i];
    fprintf(blst, "%c%5ld%12ld%12ld%12d%12d",
	    lf(), i, (long)WITH->oldstart, WITH->oldstart->seq,
	    WITH->newstart, WITH->newstart);
    if (seq1 > WITH->oldstart->seq) {
      sorted = false;
      fprintf(blst, "<<< this state NOT sorted");
    }
    seq1 = WITH->oldstart->seq;
  }
  if (sorted)
    fprintf(blst, "%ctilstand sorted\n", lf());
  else
    fprintf(blst, "%cERROR: tilstand not sorted\n", lf());
}


Static void dump2(void)
{
  pointer2 lqb;
  _REC_rhs *WITH;

  lqb = top;
  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, " RIGTHSIDE ");
  fputc(lf(), blst);
  fprintf(blst, "              SYMBOL     LINK     BASISL   PARSERP");
  do {
    fputc(lf(), blst);
    WITH = &rhs[lqb];
    fprintf(blst, "%12ld%12d%12ld%12d%12ld",
	    lqb, WITH->symbol_, WITH->link, WITH->basisl,
	    (long)WITH->parserp);
    allocate(&lqb);
  } while (lqb != point);
}


Static void dump3(void)
{
  long i, FORLIM;
  _REC_husknonterm *WITH;

  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, " HUSKNONTERM ");
  fputc(lf(), blst);
  fprintf(blst, "  NONTERMP  LEFTBOO  RIGHTBOO");
  FORLIM = nontslut;
  for (i = nontstart; i <= FORLIM; i++) {
    WITH = &husknonterm[i];
    fprintf(blst, "%c%12ld%12d%12d",
	    lf(), (long)WITH->nontermp, WITH->leftboo, WITH->rightboo);
  }
}


Static void dump4(void)
{
  long i, FORLIM;

  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, " HELP");
  fputc(lf(), blst);
  FORLIM = nontslut;
  for (i = nontstart; i <= FORLIM; i++)
    fprintf(blst, " %12ld%c", help[i].rightp, lf());
}


Static void dump5(void)
{
  /* OPTION 16 */
  long i, t, FORLIM;
  prodtype *WITH;

  fprintf(blst, "\f");
  fprintf(blst, "A DUMP OF THE PROD-ARRAY");
  fputc(lf(), blst);
  fprintf(blst, "  START      LOOKBACKP   LAENGDE    LEFTSIDE");
  fputc(lf(), blst);
  FORLIM = antalprod;
  for (i = 0; i <= FORLIM; i++) {
    WITH = &prod[i];
    fprintf(blst, "%6ld", WITH->start);
    if (WITH->lookbackp == NULL)
      fprintf(blst, "%14s", "NIL");
    else
      fprintf(blst, "%14ld", (long)WITH->lookbackp);
    fprintf(blst, "%8d", WITH->laengde);
    fprintf(blst, "        ");
    if (i != 0)
      nontwrit(WITH->leftside, &t);
    fputc(lf(), blst);
  }
  fprintf(blst, "%c%c", lf(), lf());
}


Static void outterminal(void)
{
  /* OUTPUT THE INTERN VALUES OF TERMINALS */
  long i, FORLIM;

  fprintf(blst, "%c%c%c", lf(), lf(), lf());
  fprintf(blst, " TERMINAL        INTERN VAERDI");
  fprintf(blst, "%c%c", lf(), lf());
  FORLIM = termantal;
  for (i = 0; i <= FORLIM; i++)
    fprintf(blst, " %.*s%s%12ld%c", alfal20, internrep[i + 1], blank, i, lf());
  fprintf(blst, "%c%c ", lf(), lf());
}  /*OUTTERMINAL*/


Static void newelm(pointer2 *top, Char *rname)
{
  if (*top >= const4)
    consterror(rname, "CONST4    ", const4);
  (*top)++;
}  /*NEWELM*/


Static void matrixout(rtype *s)
{
  long i, j, FORLIM, FORLIM1;

  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, " BITMATRIX");
  FORLIM = nontslut;
  for (i = 0; i <= FORLIM; i++) {
    fprintf(blst, "%c ", lf());
    FORLIM1 = nontslut;
    for (j = 0; j <= FORLIM1; j++) {
      if (P_inset(j % (setmax + 1), s[i].r[j / (setmax + 1)]))
	putc('1', blst);
      else
	putc('0', blst);
/* p2c: exbobs.p, line 763:
 * Note: Using % for possibly-negative arguments [317] */
    }
  }
  fprintf(blst, "%c%c", lf(), lf());
}


Static void inithelp(void)
{
  long i, symb;

  i = 0;
  while (i <= antalprod) {
    symb = prod[i].leftside;
    help[symb].prodindex = i;
    do {
      i++;
    } while (symb == prod[i].leftside);
  }
}


Static void skrivparser(konfigt *p)
{
  /*  PROCEDURE TIL TEST AF GENERERET PARSER   */
  long t, i;
  konfigt *lqbep;
  long dummy;
  konfigt *WITH;

  fprintf(blst, "\f");
  fprintf(blst, "%c%c PARSER%c%c", lf(), lf(), lf(), lf());
  fprintf(blst, " BASIS TILSTADR   MODE   DERIVP   NEXTP  PRODNO  INF");
  fprintf(blst, "%c%c", lf(), lf());
  if (antaltilst == 0)
    t = tilstnr;
  else
    t = antaltilst;
  for (i = 0; i <= t; i++) {
    lqbep = tilstand[i].oldstart;
    do {
      WITH = lqbep;
      if (WITH->ifbasis)
	fprintf(blst, " *");
      else
	fprintf(blst, "  ");
      fprintf(blst, "%13ld%6d", (long)lqbep, WITH->mode);
      if (WITH->derivp == NULL)
	fprintf(blst, "       NIL");
      else
	fprintf(blst, "%10ld", (long)WITH->derivp);
      if (WITH->nextp == NULL)
	fprintf(blst, "     NIL");
      else
	fprintf(blst, "%8ld", (long)WITH->nextp);
      if (lbbegin <= i && i <= lbend) {
	fprintf(blst, " LOOKBACK: ");
	if (WITH->UU.lookbp == NULL)
	  fprintf(blst, "       NIL");
	else
	  fprintf(blst, "%10ld", (long)WITH->UU.lookbp);
      } else {
	fprintf(blst, "%6d", WITH->UU.U1.prodnr);
	fprintf(blst, "    ");
	if (WITH->mode != 0) {
	  if (WITH->UU.U1.inf <= termg) {
	    putc(' ', blst);
	    outalf20(internrep[WITH->UU.U1.inf + 1], &dummy);
	  } else
	    nontwrit(WITH->UU.U1.inf, &dummy);
	}
      }
      fputc(lf(), blst);
      lqbep = WITH->derivp;
    } while (lqbep != NULL);
    fputc(lf(), blst);
  }
}  /*SKRIVPARSER*/


Static void allocp(konfigt **p, long m, Char *a)
{
  if (freeptr != NULL) {
    *p = freeptr;
    freeptr = freeptr->derivp;
  } else {
    switch (m) {

    case 1:   /* changed by JLK to please p2c: new(p,1); */
      *p = Malloc(sizeof(konfigt));
      break;

    case 5:   /* changed by JLK to please p2c: new(p,5); */
      *p = Malloc(sizeof(konfigt));
      break;
    }
    if (*p == NULL)
      consterror(a, "CONST6    ", const6);
    seqIndex++;
    (*p)->seq = seqIndex;   /* line added by jlk to solve Linux problem */
  }
  (*p)->derivp = NULL;
}  /*ALLOCP*/


Static void initempty(void)
{
  long pn, rhsinx, j;
  boolean empty, changes;
  long FORLIM, FORLIM1;

  FORLIM = nontslut;
  for (pn = 0; pn <= FORLIM; pn++)
    emptya[pn] = false;
  do {
    changes = false;
    FORLIM = antalprod;
    for (pn = 0; pn <= FORLIM; pn++) {
      if (!emptya[prod[pn].leftside]) {
	empty = true;
	rhsinx = prod[pn].start;
	FORLIM1 = prod[pn].laengde;
	for (j = 1; j <= FORLIM1; j++)   /*possibly zero*/
	  empty = (empty && emptya[rhs[rhsinx + j].symbol_]);
	if (empty) {
	  emptya[prod[pn].leftside] = true;
	  changes = true;
	}
      }
    }
  } while (changes != false);
  if (!options[35])
    return;
  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, "The following nonterminals may produce the empty string:\n");
  FORLIM = nontslut;
  for (pn = nontstart; pn <= FORLIM; pn++) {
    if (emptya[pn]) {
      fprintf(blst, "  ");
      j = 0;
      nontwrit(pn, &j);
      putc('\n', blst);
    }
  }
  fprintf(blst, "%c%c", lf(), lf());
}  /* INITEMPTY */



Static void remember(konfigt *p)
{
  /* REMEMBER IS USED TO COUNT THE
     FREQUENCY OF HOW OFTEN
     THE DIFFERENT VALUES OF NEXTP
     IN A LOOKBACKSTATE ARE USED */
  long i, FORLIM;

  /* REMEMBER */
  FORLIM = fcqi;
  for (i = 0; i < FORLIM; i++) {
    if (fcq[i].udgang == p) {
      fcq[i].frekvens++;
      goto _L5;
    }
  }
  fcqi++;
  if (fcqi > const3)
    consterror(" REMEMBER ", "CONST3    ", const3);
  fcq[fcqi - 1].udgang = p;
  fcq[fcqi - 1].frekvens = 1;
_L5: ;
}


Static void optimize(konfigt **maxnextp, long *md)
{
  /* OPTIMIZE FINDS THE NEXTP,WHICH IS MOST OFTEN USED IN
     THE STATE,AND DELETES THE STATEELEMENTS WHERE IT OCCURS*/
  konfigt *p;
  long max, i, husk, FORLIM;
  _REC_fcq *WITH;

  /* END OPTIMIZE */
  if (options[20]) {
    fprintf(blst, "%c FCQ%c%c    UDGANG  FREKVENS%c", lf(), lf(), lf(), lf());
    FORLIM = fcqi;
    for (i = 0; i < FORLIM; i++) {
      WITH = &fcq[i];
      fprintf(blst, "%12ld%12d%c", (long)WITH->udgang, WITH->frekvens, lf());
    }
    fprintf(blst, "%c%c", lf(), lf());
  }
  *maxnextp = fcq[0].udgang;
  max = fcq[0].frekvens;
  FORLIM = fcqi;
  for (i = 1; i < FORLIM; i++) {
    WITH = &fcq[i];
    if (WITH->frekvens > max) {
      max = WITH->frekvens;
      *maxnextp = WITH->udgang;
    }
  }

  if (*md == 4) {
    p = begintilst;
    while (p->nextp != *maxnextp)
      p = p->derivp;
    husk = p->UU.U1.prodnr;
    /* THE LOOKAHEAD-SET OF PROD. <>HUSK' WILL BE DELETED */
  }


  while (begintilst->nextp == *maxnextp && begintilst->mode == *md)
    begintilst = begintilst->derivp;

  p = begintilst;
  do {
    oldp = p;
    do {
      p = p->derivp;
      if (p == NULL)
	goto _L10;
    } while (p->nextp == *maxnextp && p->mode == *md);
_L10:
    oldp->derivp = p;
  } while (p != NULL);
  if (*md == 4)
    *md = husk;

}


Static void timecheck(Char *a)
{
  dayfilemsg m;
  long i;
  alfa_ b;
  long time;

  time = clock() - mstime;
  mstime = clock();
  memcpy(m, "                      USED            MS", sizeof(dayfilemsg));
  constval(time, b);
  for (i = 1; i <= 10; i++)
    m[i + 26] = b[i - 1];
  for (i = 1; i <= 20; i++)
    m[i] = a[i - 1];
  msg(m);
}  /* TIMECHECK */


Local long heap(void)
{
  return 777;
}


Static void heapcheck(Char *a)
{
  dayfilemsg m;
  long i;
  alfa_ b;

  /* ASSEMBLY LANGUAGE ROUTINE TO RETURN */
  /* ACTUAL SIZE OF HEAP .               */
  memcpy(m, " HEAP                                   ", sizeof(dayfilemsg));
  constval(heap(), b);
  for (i = 1; i <= 10; i++)
    m[i + 29] = b[i - 1];
  for (i = 1; i <= 20; i++)
    m[i + 5] = a[i - 1];
  msg(m);
}  /* HEAPCHECK */


Static void constcheck(Char *a, long c1, long c2)
{
  dayfilemsg m;
  alfa_ b1, b2;
  long i;

  memcpy(m, "                                        ", sizeof(dayfilemsg));
  constval(c1, b1);
  constval(c2, b2);
  for (i = 1; i <= 10; i++)
    m[i] = a[i - 1];
  for (i = 1; i <= 10; i++)
    m[i + 11] = b1[i - 1];
  for (i = 1; i <= 10; i++)
    m[i + 24] = b2[i - 1];
  msg(m);
}  /* CONSTCHECK */


Static void writem(long pnr, long dot)
{
  long t, i, FORLIM;

  fflush(blst);
  P_ioresult = 0;
  t = 0;
  nontwrit(prod[pnr].leftside, &t);
  fprintf(blst, " ::= ");
  t += 5;
  FORLIM = prod[pnr].laengde;
  for (i = 1; i <= FORLIM; i++) {
    if (i == dot) {
      fprintf(blst, " .  ");
      t += 4;
    }
    if (rhs[i + prod[pnr].start].symbol_ <= termg)
      outalf20(internrep[rhs[i + prod[pnr].start].symbol_ + 1], &t);
    else
      nontwrit(rhs[i + prod[pnr].start].symbol_, &t);
    putc(' ', blst);
  }
  if (dot == 0 || dot == prod[pnr].laengde + 1)
    fprintf(blst, " .");
  fflush(blst);
  P_ioresult = 0;
}  /* WRITEM */


#define maxopt          13


typedef enum {
  alfanum, special, sep
} chtype;
/*packed*/
typedef Char labelarr[100];
typedef Char buftype[alf3];


typedef struct _REC_mnemo {
  alfa_ opt;
  long num;
} _REC_mnemo;

/* Local variables for ingrammar: */
struct LOC_ingrammar {
  jmp_buf _JL7777;
  buftype buffer;
  Char metasymbol[5];
  _REC_mnemo mnemo[maxopt];
  alfa_ m[6];
  alfa_ alfav, metavar;
  boolean eofflag;
  chtype chgroup[256];
  long i;
} ;

Local void gramerror(long a, struct LOC_ingrammar *LINK);
Local void inch(struct LOC_ingrammar *LINK);
Local void space(struct LOC_ingrammar *LINK);
Local void nterminal(Char *meta, struct LOC_ingrammar *LINK);

Local boolean testch(Char ch1, Char ch2, struct LOC_ingrammar *LINK)
{
  /* USED BY TERMINPUT AND TERMINAL */
  return ((LINK->chgroup[ch1] == LINK->chgroup[ch2] &&
	   LINK->chgroup[ch2] != sep) ||
	  options[4] && LINK->chgroup[ch1] != sep && LINK->chgroup[ch2] != sep);
  /*TRUE- IF CH1 AND CH2<>SEP AND IN SAME GROUP OF CHARS */
  /*TRUE- IF OPTIONS[5] AND CH1,CH2<>SEP */
}  /*TESTCH*/

Local void pack(Char *b, long inx, Char *a, struct LOC_ingrammar *LINK)
{
  long i;

  for (i = 1; i <= alfalength; i++)
    a[i - 1] = b[inx + i - 2];
}

/* Local variables for terminput: */
struct LOC_terminput {
  struct LOC_ingrammar *LINK;
  boolean stoperror;

  /************** OLM: 11.4.93 ********/
  boolean noNewTerm;   /* see below */
} ;


Local void inputerror(long nr, struct LOC_terminput *LINK)
{
  /* ERROR-PROCEDURE LOCAL FOR TERMINPUT*/
  if (nr & 1)
    putc('\n', blst);
  switch (nr) {

  case 1:
    fprintf(blst, "*****  END OF FILE ENTCOUNTERED.");
    break;

  case 2:
    fprintf(blst, "\n  ***  TERMINAL DUPLICATED.");
    break;

  case 3:
    consterror("TERMINPUT ", "CONST12   ", const12);
    break;

  case 6:
    LINK->stoperror = true;
    do {
      inch(LINK->LINK);
    } while (ch != ' ');
    fprintf(blst, "\n  ***  TERMINAL MORE THAN %2ld CHARACTERS.\n",
	    (long)alfal20);
    break;

  case 7:
    consterror("TERMINPUT ", "CONST2    ", const2);
    break;

  case 4:
    LINK->stoperror = true;
    do {
      inch(LINK->LINK);
    } while (ch != ' ');
    fprintf(blst, "\n  ***  ILLEGAL CONCATENATION.");
    break;

  case 8:
    LINK->stoperror = true;
    fprintf(blst, "\n*** Illegal m5 in terminput\n");
    break;

  case 9:
    LINK->stoperror = true;
    fprintf(blst, "\n*** Illegal character combination in terminal\n");
    break;

  case 10:
    LINK->stoperror = true;
    fprintf(blst, "\n*** Empty terminal symbol\n");
    break;
  }
  /*  VED ULIGE NR. HELT UD- ELLERS HUSK FEJLEN    */
  fprintf(blst, "%c          ", lf());
  if (nr & 1)
    stop(0);
}

Local void fresh(struct LOC_terminput *LINK)
{
  /* NY CELLE I TERMTREE ALLOCERES OG INITIALISERES   */
  termelm *WITH;

  termtop = Malloc(sizeof(termelm));
  if (termtop == NULL)
    inputerror(3, LINK);
  WITH = termtop;
  WITH->ok = false;
  WITH->tegn = ch;
  WITH->intern = -1;
  WITH->niveaup = NULL;
  WITH->higherp = NULL;
  trmax++;   /*USED IN PROCEDURE FINALPARSER*/
}

Local long newTermNo(struct LOC_terminput *LINK)
{
  /* allocate new terminal number */
  if (!LINK->noNewTerm) {   /* skip */
    if (termantal < const2)
      termantal++;
    else
      inputerror(7, LINK);
  }
  LINK->noNewTerm = false;
  return termantal;
}

Local void terminput(struct LOC_ingrammar *LINK)
{
  struct LOC_terminput V;
  /*INDLAESNING AF TERMINALER ADSKILT MED SPACE EL. EOL
    OG AFSLUTTET MED METASYMBOL 4 */
  long i, j;
  Char c[alfal20];
  termelm *runp, *gemp;
  alfa20 alfac, emptyalfa, namealfa, cstalfa, stringalfa, erroralfa;
  Char chh;
  entrytyp *WITH;
  termelm *WITH1;

  /******** end OLM 11.4.93 **********/
  V.LINK = LINK;
  /*   INITIALISERING   */
  V.noNewTerm = false;   /* OLM: 11.4.93 */
  trmax = 0;   /*SEE PROCEDURE FRESH*/
  for (chh = minch; chh <= maxch; chh++) {
    WITH = &entry_[chh];
    WITH->termp = NULL;
    WITH->ok1 = false;
    WITH->intern1 = -1;
  }
  errorval = -1;
  /* NB: 0 is -BOBS-EOI- which is the last terminal on input */
  memcpy(erroralfa, "_ERROR_             ", sizeof(alfa20));
  emptyvalue = -1;
  memcpy(emptyalfa, "_EMPTY_             ", sizeof(alfa20));
  nameval = -1;
  memcpy(namealfa, "_NAME_              ", sizeof(alfa20));
  cstval = -1;
  memcpy(cstalfa, "_KONST_             ", sizeof(alfa20));
  stringval = -1;
  memcpy(stringalfa, "_STRING_            ", sizeof(alfa20));
  stringch = ' ';
  gl = NULL;
  gn = NULL;
  gc = NULL;
  gs = NULL;
  go = NULL;
  termantal = 1;
  V.stoperror = false;
  /* LQKKE SAALAENGE FLERE TERMINALER   */
  ch = s;
  while (ch == ' ')
    inch(LINK);
  while (ch != LINK->metasymbol[3]) {
    if (ch != LINK->metasymbol[4])
      inputerror(8, &V);
    inch(LINK);
    i = 0;
    /*   LQKKE -SAALAENGE NAESTE CHAR-VAERDI GODKENDT   */
    do {
      if (ch == LINK->metasymbol[4]) {
	inch(LINK);
	if (ch != LINK->metasymbol[4])
	  goto _L100;
      }
      if ((i > 0) & (!testch(c[i - 1], ch, LINK)))
	inputerror(9, &V);
      if (i == alfal20 && !options[3])
	inputerror(6, &V);
      if (i < alfal20) {
	i++;
	c[i - 1] = ch;
      }
      /*  NAESTE CHAR-V. SQGES I ALLEREDE OPBYGGET TRAE   */
      if (i > 1) {
	if (i == 2) {
	  WITH = &entry_[c[0]];
	  if (WITH->termp == NULL) {
	    fresh(&V);
	    WITH->termp = termtop;
	    gemp = termtop;
	    goto _L10;
	  }
	  runp = WITH->termp;
	} else {
	  WITH1 = gemp;
	  if (WITH1->higherp == NULL) {
	    fresh(&V);
	    WITH1->higherp = termtop;
	    gemp = termtop;
	    goto _L10;
	  }
	  runp = WITH1->higherp;
	}
	while (runp->tegn != ch) {
	  WITH1 = runp;
	  if (WITH1->niveaup == NULL)
	    goto _L11;
	  runp = WITH1->niveaup;
	}
	gemp = runp;
	goto _L10;   /* this code was written by BBK */
_L11:   /*  CHAR NOT FOUND - NY CELLE OPRETTES   */
	fresh(&V);
	runp->niveaup = termtop;
	gemp = termtop;
      }
_L10:
      inch(LINK);
    } while (true);
_L100:
    if (i == 0)
      inputerror(10, &V);
    /* ch = ' ' or m[4] */
    if (ch == ' ' || ch == LINK->metasymbol[3]) {
      if (options[2] && ch == ' ') {
	inch(LINK);
	if (ch == LINK->metasymbol[0]) {
	  inch(LINK);
	  V.noNewTerm = true;   /*OLM 11.4.93:??*/
	  goto _L12;
	}
      }
      /* NY TERMINAL REGISTRERES - TEST FOR GENGANGERI   */
      /* OLM: 11.4.93
       *if termantal<const2 then termantal:=termantal+1 else inputerror(7);
       */
_L12:   /*GOTO 12 LIG NY TERMINAL IKKE NYT NUMMER*/
      if (i == 1) {
	WITH = &entry_[c[0]];
	if (WITH->ok1) {
	  inputerror(2, &V);
	  goto _L14;
	}
	WITH->intern1 = newTermNo(&V);
	/*writeln(blst,intern1);*/
	WITH->ok1 = true;
      } else {
	if (gemp->ok) {
	  inputerror(2, &V);
	  goto _L14;
	}
	gemp->intern = newTermNo(&V);
	/*writeln(blst,intern);*/
	gemp->ok = true;
      }
      /* OLM 11.4.93:
       * before this correction, each occurence of a terminal symbol
       * gave rise to a new terminal number. In addition dublicate
       * occurrences of NAME, KONST, etc., implied that gn, gc, etc
       * was set to refer to the last allocated cell (via termtop).
       * In case of dublicate NAME, etc. termtop did not refer to
       * to the last char of e.g. NAME. The last char in NAME is referred
       * by gemp.
       * The correction avoids a new terminal number for dublicate
       * terminals. In addition a dublicate terminal is not tested
       * for being NAME, etc.
       */
      /* TERMINAL PAKKES OG GEMMES- TEST FOR EVT. EMPTY-TERMINAL  */
      for (j = 0; j < i; j++)
	alfac[j] = c[j];
      for (; i < alfal20; i++)
	alfac[i] = ' ';
      if (!strncmp(erroralfa, alfac, sizeof(alfa20))) {
	errorval = termantal;
	go = termtop;
      } else if (!strncmp(emptyalfa, alfac, sizeof(alfa20))) {
	emptyvalue = termantal;
	gl = termtop;
      } else if (!strncmp(namealfa, alfac, sizeof(alfa20))) {
	nameval = termantal;
	gn = termtop;
      } else if (!strncmp(cstalfa, alfac, sizeof(alfa20))) {
	cstval = termantal;
	gc = termtop;
      } else if (!strncmp(stringalfa, alfac, sizeof(alfa20))) {
	stringval = termantal;
	gs = termtop;
      }
      memcpy(internrep[termantal + 1], alfac, sizeof(alfa20));
_L14: ;   /* OLM 11.4.93 */
    } else
      inputerror(4, &V);
_L22:
    while (ch == ' ')
      inch(LINK);
  }
  inch(LINK);
  memcpy(internrep[1], "BOBS-GO             ", sizeof(alfa20));
  memcpy(internrep[2], "-EOF-               ", sizeof(alfa20));
  if (options[0])
    outterminal();
  if (V.stoperror)
    stop(2);
}

/* Local variables for terminal: */
struct LOC_terminal {
  struct LOC_ingrammar *LINK;
} ;

Local void inputerror_(long nr, struct LOC_terminal *LINK)
{
  /*  ERROR-PROC. LOCAL FOR TERMINAL    */
  errorboo = true;
  error2 = true;
  error = true;
  termrep = 0;
  putc('\n', blst);
  switch (nr) {

  case 1:
    fprintf(blst, "*** Empty terminal symbol\n\n");
    gramerror(23, LINK->LINK);
    break;

  case 2:
    fprintf(blst, "*** Fatal system error: illegal call of terminal\n\n");
    gramerror(23, LINK->LINK);
    break;

  case 3:
    fprintf(blst, "***  Illegal terminal symbol\n\n");
    gramerror(23, LINK->LINK);   /*GOTO88;*/
    break;
  }
}

Local boolean metach(Char ch, struct LOC_terminal *LINK)
{
  boolean b;
  long j;

  b = false;
  for (j = 0; j <= 3; j++)
    b = (b || ch == LINK->LINK->metasymbol[j]);
  return b;
}  /*METACH*/


/*----------------------------------------------------------*/
Local void terminal(struct LOC_ingrammar *LINK)
{
  /* KALDES MED CHAR-VALUE I CH; LEVERER I TERMREP DEN INTERNE
     REPRAESENTATION AF NAESTE TERMINAL PAA INPUT-
     HVIS EN FINDES- ELLERS -1 */
  struct LOC_terminal V;
  Char buf[alf3];
  termelm *gemp, *runp;
  entrytyp *WITH;
  termelm *WITH1;

  V.LINK = LINK;
  /* IN DEC 10 PASCAL, JUMPS OUT OF A PROCEDURE ARE NOT ALLOWED */
  /* INPUTERROR(6) SHOULD TERMINATE BY GOTO 88; THIS IS INSTEAD */
  /* SIMULATED BY LABEL 77 AND GOTO 77 */
  while (ch == ' ')
    inch(LINK);
  if (ch != LINK->metasymbol[4])
    inputerror_(2, &V);
  inch(LINK);
  LINK->i = 0;
  do {
    if (ch == LINK->metasymbol[4]) {
      inch(LINK);
      if (ch != LINK->metasymbol[4])
	goto _L66;
    }
    if (LINK->i < alf3 - 1) {
      LINK->i++;
      buf[LINK->i - 1] = ch;
    }
    if (LINK->i != 1) {
      if (LINK->i == 2) {
	WITH = &entry_[buf[0]];
	if (WITH->termp == NULL)
	  goto _L77;
	runp = WITH->termp;
      } else {
	if (gemp->higherp == NULL)
	  goto _L77;
	runp = gemp->higherp;
      }
      while (runp->tegn != ch) {
	WITH1 = runp;
	if (WITH1->niveaup == NULL)
	  goto _L77;
	runp = WITH1->niveaup;
      }
      gemp = runp;
    }
    inch(LINK);
  } while (true);
_L66:

  /* OPSAMLET ALFA-VAERDI TESTES SOM TERMINAL      */
  /* writeln(blst); write(blst,'Terminal: "');
   * for j:=1 to i do write(blst,buf[j]); write(blst,'"=');
   */
  if (LINK->i == 0)
    inputerror_(1, &V);
  if (LINK->i == 1) {
    WITH = &entry_[buf[0]];
    if (!WITH->ok1)
      goto _L77;
    termrep = WITH->intern1;
  } else {
    if (!gemp->ok)
      goto _L77;
    termrep = gemp->intern;
  }
  goto _L88;
_L77:
  inputerror_(3, &V);
_L88: ;   /*writeln(blst,termrep)*/
}

Local void fejl(long i, struct LOC_ingrammar *LINK)
{
  fputc(lf(), blst);
  if ((unsigned long)i >= 32 || ((1L << i) & 0x3300) == 0)
    fputc(lf(), blst);
  fprintf(blst, "  ***  ");
  switch (i) {

  case 1:
    fprintf(blst, " EOF ENCOUNTERED IN READING THE GRAMMAR");
    break;

  case 2:
    fprintf(blst, " = EXPECTED IN GOALSYMBOLCARD");
    break;

  case 3:
    fprintf(blst, " GOALSYMBOLCARD EXPECTED");
    break;

  case 4:
    fprintf(blst, " EMPTY IS NOT THE ONLY SYMBOL IN RIGHTSIDE");
    break;

  case 5:
    fprintf(blst, " ERROR(S) IN METASYMBOLS");
    break;

  case 6:
    fprintf(blst, " METASYMBOLCARD EXPECTED");
    break;

  case 7:
    consterror("INGRAMMAR ", "CONST2    ", const2);
    break;

  case 8:
    fprintf(blst, " AN ALTERNATIVE ON A RIGHTSIDE HAS NO SYMBOLS");
    break;

  case 9:
    fprintf(blst,
	    " THE STRING-ESCAPE CHAR MUST APPEAR IN THE LIST OF TERMINALS");
    break;

  case 10:
    fprintf(blst, " TWO OR MORE METASYMBOLS ARE ALIKE");
    break;

  case 17:
    fprintf(blst, " ERROR(S) IN STRINGCARD ");
    break;

  case 18:
    fprintf(blst, " TOO LONG NONTERMINAL ");
    break;

  case 19:
    fprintf(blst, " TOO LONG RIGHTSIDE (MAX 15) ");
    break;

  case 11:
    fprintf(blst, " INPUT FILE EMPTY ");
    break;

  case 12:
    fprintf(blst, " METASYMBOL 3 APPEARS IN WRONG CONTEXT");
    break;

  case 13:
    fprintf(blst, " METASYMBOL 1 WAS EXPECTED");
    break;

  case 14:
    consterror("INGRAMMAR ", "CONST11   ", const11);
    break;

  case 15:
    fprintf(blst, " ILLEGAL CHARACTER IN OPTION LIST");
    break;

  case 16:
    fprintf(blst, " OPTION NUMBER IS NOT DEFINED");
    break;

  case 20:
    fprintf(blst, " METASYMBOL 4 WAS EXPECTED IN COMMENT-DEFINITION");
    break;

  case 21:
    fprintf(blst, " METASYMBOL 4 WAS EXPEXTED AFTER COMMENT-DEFINITION");
    break;

  case 22:
    fprintf(blst, " COMMENT =  WAS EXPECTED ");
    break;

  case 23:
    fprintf(blst, " NONTERMINAL = ... M4 ... M4  was expected");
    break;

  case 24:
    fprintf(blst,
      " SYMBOLS in COMMENTS DEFINITION MUST BE ENCLOSED BY METASYMBOL 5 (\") AS IN COMMENT=\"...\";\"...\"");

    break;
  }
  if ((unsigned long)i < 32 && ((1L << i) & 0xc6e) != 0)
    printf("!!!!! ERROR(S) IN INPUT                      \n");
  putc('\n', blst);
  errorboo = true;
  if (i == 4)
    nboo2 = true;
  else {
    if ((unsigned long)i >= 32 || ((1L << i) & 0xdb300L) == 0)
      stop(0);
  }
  options[7] = false;
}


Local void gramerror(long a, struct LOC_ingrammar *LINK)
{
  if (a < 23)   /*NOT CALLED FROM TERMINAL*/
    fejl(a, LINK);
  while (LINK->metasymbol[3] != s)
    space(LINK);
  space(LINK);
}


Local void goalsymb(struct LOC_ingrammar *LINK)
{
  /* PROCEDUREN LAESER GOALSYMBOLKORTET*/
  long i;

  for (i = 0; i < alfalength; i++) {
    LINK->buffer[i] = s;
    space(LINK);
  }
  pack(LINK->buffer, 1, LINK->alfav, LINK);
  if (!strncmp(LINK->alfav, "GOALSYMBOL", sizeof(alfa_))) {
    if (s == '=') {
      nterminal(&LINK->metasymbol[3], LINK);
      goalhusk = count;
    } else
      fejl(2, LINK);
  } else
    fejl(3, LINK);
  goaltest = true;
  nboo1 = false;
  space(LINK);
}


Local void goalprod(struct LOC_ingrammar *LINK)
{
  /* INDSAETTELSE AF GOALPRODUKTIONEN*/
  long i;
  _REC_rhs *WITH;

  /* INDSAETTELSE AF HQJRESIDE*/
  huskp = point;
  rhs[point].basisl = 3;

  newelm(&point, "GOALPROD  ");
  rhs[point].symbol_ = 0;

  newelm(&point, "GOALPROD  ");
  WITH = &rhs[point];
  if (goaltest)
    WITH->symbol_ = goalhusk;
  else
    WITH->symbol_ = count;
  newelm(&point, "GOALPROD  ");
  rhs[point].symbol_ = 1;
  for (i = 1; i <= 4; i++) {
    WITH = &rhs[huskp];
    allocate(&huskp);
    WITH->link = rhsnil;
    WITH->parserp = NULL;
  }
  goalboo = false;
  point = huskp;
}

Local void nontmeta(struct LOC_ingrammar *LINK)
{
  /* read the terminal symbols used to delimit nonterminals*/
  /* when parsing sentential forms */
  /*packed*/
  Char buf[12];
  long i;

  for (i = 0; i <= 11; i++) {
    buf[i] = s;
    space(LINK);
  }
  if (strncmp(buf, "NONTERMINAL=", 12)) {
    gramerror(23, LINK);
    return;
  }
  ch = s;
  terminal(LINK);
  nontl = termrep;
  if (ch != ' ')
    s = ch;
  else
    space(LINK);
  if (ch != LINK->metasymbol[3]) {
    gramerror(23, LINK);
    return;
  }
  space(LINK);
  ch = s;
  terminal(LINK);
  nontr = termrep;
  if (ch != ' ')
    s = ch;
  else
    space(LINK);
  if (s != LINK->metasymbol[3])
    gramerror(23, LINK);
  else
    space(LINK);
}

Local void comment(struct LOC_ingrammar *LINK)
{
  /* THE PROCEDURE READS THE COMMENT CARD IF ANY */
  /*packed*/
  Char buf[8];
  long i;

  for (i = 0; i <= 7; i++) {
    buf[i] = s;
    space(LINK);
  }
  if (strncmp(buf, "COMMENT=", 8)) {
    gramerror(22, LINK);
    return;
  }
  ch = s;
  terminal(LINK);
  combegin = termrep;
  if (ch != ' ')
    s = ch;
  else
    space(LINK);
  if (s != LINK->metasymbol[3]) {
    gramerror(20, LINK);
    return;
  }
  i = 1;
  space(LINK);
  if (s != LINK->metasymbol[4])
    fejl(24, LINK);
  space(LINK);
  while (s != LINK->metasymbol[4] && i <= alfalength) {
    comend[i - 1] = s;
    space(LINK);
    i++;
  }
  comlength = i - 1;
  space(LINK);
  if (s != LINK->metasymbol[3])
    gramerror(21, LINK);
  else
    space(LINK);
}


Local void dumpnonterminternrep(struct LOC_ingrammar *LINK)
{
  if (!options[5])
    return;
  fprintf(blst, "%c%c%c", lf(), lf(), lf());
  fprintf(blst, " A LIST OF NONTERMINALS WITH INTERNAL REPRESENTATION ");
  fprintf(blst, "%c%c", lf(), lf());
  noword = false;
  nterminal(&LINK->metasymbol[2], LINK);
}

Local void inch(struct LOC_ingrammar *LINK)
{
  if (P_eof(stdin)) {
    ch = ' ';
    if (LINK->eofflag)
      fejl(1, LINK);
    else
      longjmp(LINK->_JL7777, 1);
    return;
  }
  if (P_eoln(stdin)) {
    if (options[7] == false)
      fprintf(blst, "\n     ");
    scanf("%*[^\n]");
    getchar();
    ch = ' ';
    return;
  }
  ch = getchar();
  if (ch == '\n')
    ch = ' ';
  if (options[7] == false)
    putc(ch, blst);
}  /*INCH*/

Local void space(struct LOC_ingrammar *LINK)
{
  do {
    inch(LINK);
  } while (ch == ' ');
  s = ch;
}


Local void laes(long *a, struct LOC_ingrammar *LINK)
{
  long i;

  i = 1;
  while (i <= *a) {
    LINK->buffer[i - 1] = s;
    i++;
    space(LINK);
  }
  if (i < 12) {
    for (i--; i <= 11; i++)
      LINK->buffer[i] = ' ';
  }
}


Local void stringdef(struct LOC_ingrammar *LINK)
{
  /*packed*/
  Char buf[9];
  long i;

  for (i = 0; i <= 8; i++) {
    buf[i] = s;
    space(LINK);
  }
  if (!strncmp(buf, "STRINGCH=", 9))
    stringch = s;
  else
    fejl(17, LINK);
  if (entry_[stringch].ok1 == false)
    fejl(9, LINK);
  space(LINK);
  if (s == LINK->metasymbol[3])
    space(LINK);
}  /*SLUT PAA STRING */

/* Local variables for nterminal: */
struct LOC_nterminal {
  struct LOC_ingrammar *LINK;
  Char *meta;
  alfa_ alfa1, alfa2, alfa3;
  boolean boo;
  long i;
} ;

Local void nextword(struct LOC_nterminal *LINK)
{
  long i;

  space(LINK->LINK);
  if (s == LINK->LINK->metasymbol[2]) {
    gramerror(12, LINK->LINK);
    error1 = true;
    goto _L26;
  }
  i = 1;
  while (s != *LINK->meta) {
    if (i <= 30)
      LINK->LINK->buffer[i - 1] = s;
    space(LINK->LINK);
    i++;
  }
  for (i--; i <= 29; i++)
    LINK->LINK->buffer[i] = ' ';
  pack(LINK->LINK->buffer, 1, LINK->alfa1, LINK->LINK);
  pack(LINK->LINK->buffer, 11, LINK->alfa2, LINK->LINK);
  pack(LINK->LINK->buffer, 21, LINK->alfa3, LINK->LINK);
_L26: ;
  /*END NEXTWORD*/
}

Local void visitnode(nontelm *p)
{
  fprintf(blst, " %.*s%.*s%.*s",
	  alfalength, p->word1, alfalength, p->word2, alfalength, p->word3);
  fprintf(blst, " INTERNAL VALUE");
  fprintf(blst, " %12d%c", p->nontermvaerdi, lf());
}



Local void udord(nontelm *p, struct LOC_nterminal *LINK)
{
  if (p == NULL)
    return;
  udord(p->llink, LINK);
  visitnode(p);
  udord(p->rlink, LINK);
}


Local void indord(struct LOC_nterminal *LINK)
{
  nontelm *WITH;

  LINK->boo = true;
  dynp = first;
  while (dynp != NULL && LINK->boo) {
    WITH = dynp;
    if (!strncmp(LINK->alfa1, WITH->word1, sizeof(alfa_)) &&
	!strncmp(LINK->alfa2, WITH->word2, sizeof(alfa_)) &&
	!strncmp(LINK->alfa3, WITH->word3, sizeof(alfa_)))
    {  /*ORDET VAERET FQR*/
      LINK->boo = false;
      count = WITH->nontermvaerdi;
      if (!venstreboo)
	continue;
      LINK->i = 1;   /*UNDERSQGE OM VSIDE VAERET FQR*/
      while (LINK->i < k && husk[LINK->i - 1] != count)
	LINK->i++;
      if (LINK->i < k)
	rhs[lefthelp[count]].link = point;
      /*HVIS VAERET FQR DA I<K POINTER SAETTES*/
      continue;
    }
    last = dynp;
    if (strncmp(LINK->alfa1, WITH->word1, sizeof(alfa_)) < 0) {
      dynp = WITH->llink;
      continue;
    }
    if (!strncmp(LINK->alfa1, WITH->word1, sizeof(alfa_)) &&
	strncmp(LINK->alfa2, WITH->word2, sizeof(alfa_)) < 0)
      dynp = WITH->llink;
    else {
      if (!strncmp(LINK->alfa1, WITH->word1, sizeof(alfa_)) &&
	  !strncmp(LINK->alfa2, WITH->word2, sizeof(alfa_)) &&
	  strncmp(LINK->alfa3, WITH->word3, sizeof(alfa_)) < 0)
	dynp = WITH->llink;
      else
	dynp = WITH->rlink;
    }
  }
  if (!LINK->boo)
    return;
  statp = Malloc(sizeof(nontelm));
  if (statp == NULL)
    fejl(14, LINK->LINK);
  WITH = statp;
  memcpy(WITH->word1, LINK->alfa1, sizeof(alfa_));
  memcpy(WITH->word2, LINK->alfa2, sizeof(alfa_));
  memcpy(WITH->word3, LINK->alfa3, sizeof(alfa_));
  WITH->llink = NULL;
  WITH->rlink = NULL;
  WITH->nontermvaerdi = internv;
  count = internv;
  if (internv >= const2)
    fejl(7, LINK->LINK);
  internv++;
  husknonterm[count].nontermp = statp;
  WITH = last;
  if (strncmp(WITH->word1, LINK->alfa1, sizeof(alfa_)) > 0) {
    WITH->llink = statp;
    return;
  }
  if (!strncmp(WITH->word1, LINK->alfa1, sizeof(alfa_)) &&
      strncmp(WITH->word2, LINK->alfa2, sizeof(alfa_)) > 0) {
    WITH->llink = statp;
    return;
  }
  if (!strncmp(WITH->word1, LINK->alfa1, sizeof(alfa_)) &&
      !strncmp(WITH->word2, LINK->alfa2, sizeof(alfa_)) &&
      strncmp(WITH->word3, LINK->alfa3, sizeof(alfa_)) > 0)
    WITH->llink = statp;
  else
    WITH->rlink = statp;
}






Local void nterminal(Char *meta_, struct LOC_ingrammar *LINK)
{
  struct LOC_nterminal V;
  nontelm *WITH;

  V.LINK = LINK;
  V.meta = meta_;
  if (!noword) {
    udord(first, &V);
    return;
  }
  if (nontermboo) {
    nextword(&V);
    first = Malloc(sizeof(nontelm));
    WITH = first;
    memcpy(WITH->word1, V.alfa1, sizeof(alfa_));
    memcpy(WITH->word2, V.alfa2, sizeof(alfa_));
    memcpy(WITH->word3, V.alfa3, sizeof(alfa_));
    WITH->llink = NULL;
    WITH->rlink = NULL;
    count = internv;
    husknonterm[count].nontermp = first;
    nontermboo = false;
    WITH->nontermvaerdi = internv;
    internv++;
    return;
  }
  nextword(&V);
  if (errorboo == false)
    indord(&V);
}


Local void metasymb(struct LOC_ingrammar *LINK)
{
  /* METASYMB LAESER ET KORT MED FQLGENDE UDSEENDE : */
  /*  METAVARIABLE M1=   M2=  M3=  M4=  M5= */
  count = 11;
  laes(&count, LINK);
  pack(LINK->buffer, 1, LINK->alfav, LINK);
  if (strncmp(LINK->alfav, LINK->metavar, sizeof(alfa_)))
  {  /*METAVARIABLE GENKENDT*/
    fejl(6, LINK);
    return;
  }
  j = 1;
  while (j <= 5) {
    count = 3;
    laes(&count, LINK);
    pack(LINK->buffer, 1, LINK->alfav, LINK);
    if (!strncmp(LINK->m[j], LINK->alfav, sizeof(alfa_))) {
      LINK->metasymbol[j - 1] = s;
      LINK->i = j;
      if (LINK->i > 1) {
	while (LINK->i > 1) {
	  LINK->i--;
	  if (s == LINK->metasymbol[LINK->i - 1])
	    fejl(10, LINK);
	}
      }
      j++;
    } else
      fejl(5, LINK);
    if (j <= 5)
      space(LINK);
  }
}


Local void init(struct LOC_ingrammar *LINK)
{
  Char c;
  long i;

  memcpy(LINK->mnemo[0].opt, "NYLALR    ", sizeof(alfa_));
  LINK->mnemo[0].num = 27;
  memcpy(LINK->mnemo[1].opt, "PROD      ", sizeof(alfa_));
  LINK->mnemo[1].num = 16;
  memcpy(LINK->mnemo[2].opt, "TILSTAND  ", sizeof(alfa_));
  LINK->mnemo[2].num = 17;
  memcpy(LINK->mnemo[3].opt, "VHRECURS  ", sizeof(alfa_));
  LINK->mnemo[3].num = 25;
  memcpy(LINK->mnemo[4].opt, "TIMECHECK ", sizeof(alfa_));
  LINK->mnemo[4].num = 47;
  memcpy(LINK->mnemo[5].opt, "LOOKBACK  ", sizeof(alfa_));
  LINK->mnemo[5].num = 21;
  memcpy(LINK->mnemo[6].opt, "LALR1     ", sizeof(alfa_));
  LINK->mnemo[6].num = 51;
  memcpy(LINK->mnemo[7].opt, "LALR2     ", sizeof(alfa_));
  LINK->mnemo[7].num = 52;
  memcpy(LINK->mnemo[8].opt, "LALR3     ", sizeof(alfa_));
  LINK->mnemo[8].num = 53;
  memcpy(LINK->mnemo[9].opt, "PARSER    ", sizeof(alfa_));
  LINK->mnemo[9].num = 15;
  memcpy(LINK->mnemo[10].opt, "HEAPCHECK ", sizeof(alfa_));
  LINK->mnemo[10].num = 46;
  memcpy(LINK->mnemo[11].opt, "EMPTY     ", sizeof(alfa_));
  LINK->mnemo[11].num = 36;
  memcpy(LINK->mnemo[12].opt, "LRCOND    ", sizeof(alfa_));
  LINK->mnemo[12].num = 35;
  LINK->eofflag = true;
  for (c = minch; c <= maxch; c++)
    LINK->chgroup[c] = special;
  for (c = 'A'; c <= 'Z'; c++)
    LINK->chgroup[c] = alfanum;
  for (c = 'a'; c <= 'z'; c++)
    LINK->chgroup[c] = alfanum;
  for (c = '0'; c <= '9'; c++)
    LINK->chgroup[c] = alfanum;
  LINK->chgroup['_'] = alfanum;
  LINK->chgroup[' '] = sep;
  error = false;
  /* the following is done in the main-program
     FOR i:=1 TO const18 DO options[i]:=false;  */

  combegin = 0;
  comlength = 1;
  for (i = 0; i < alfalength; i++)
    comend[i] = ' ';
  linx = 0;
  prodseqno = 0;
  nolooki = 0;   /* INDEX TO NOLOOK */
  nontl = -1;
  nontr = -1;
}  /*INIT*/

Local void enter(long no)
{
  long i;

  nolook[nolooki] = no;
  i = 0;
  while (nolook[i] != no)
    i++;
  if (i == nolooki)
    nolooki++;
}

Local long findlabel(Char *lab, long labellength, struct LOC_ingrammar *LINK)
{
  long Result, i, j, k, no;
  pointer2 p;
  boolean boo;
  long FORLIM;

  boo = false;
  no = 0;
  FORLIM = internv;
  for (i = nontstart + 1; i < FORLIM; i++) {
    p = help[i].rightp;
    while (p != rhsnil) {
      if (rhs[p].length == labellength || options[32]) {
	boo = true;
	k = rhs[p].first;
	if (options[32]) {
	  while (labelbuf[k] != ' ')
	    k++;
	  k++;
	}
	if (rhs[p].length - k + rhs[p].first == labellength) {
	  for (j = 0; j < labellength; j++)
	    boo = (labelbuf[k + j] == lab[j] && boo);
	  if (boo) {
	    Result = rhs[p].first;
	    enter(rhs[p].first);
	    no++;
	  }
	}
      }
      p = rhs[rhs[p].basisl + p].link;
    }
  }
  if (no == 0) {
    fprintf(blst, "%cLABEL NOT FOUND: %.*s%c",
	    lf(), (int)labellength, lab, lf());
    Result = -1;
  }
/* p2c: exbobs.p, line 1817: Note:
 * Format for packed-array-of-char will work only if width < length [321] */
  if (no > 1) {
    fprintf(blst, "%cLABEL DECLARED MORE THAN ONCE: %.*s%c",
	    lf(), (int)labellength, lab, lf());
    return -1;
  }
/* p2c: exbobs.p, line 1822: Note:
 * Format for packed-array-of-char will work only if width < length [321] */
  return Result;
}

Local void readlabel(long pt, struct LOC_ingrammar *LINK)
{
  long lo, i;
  alfa_ sa;

  prodseqno++;
  rhs[pt].seqno = prodseqno;
  if (!(options[32] || options[33]))
    return;
  lo = linx;
  rhs[pt].first = lo;
  if (options[32]) {
    /* use the input seqNo as the first part of the label */
    if (linx + 15 > const19)
      consterror("READLABEL ", "CONST19   ", const19);
    constval(prodseqno, sa);
    i = 2;
    while (sa[i - 1] != ')') {
      labelbuf[linx] = sa[i - 1];
      i++;
      linx++;
    }
    labelbuf[linx] = ' ';
    linx++;
  }
  if (options[33]) {
    /* READ THE LABEL GIVEN, AND STOP ON THE FIRST OCURRENCE OF
       METASYMBOL 1 */
    space(LINK);
    while (s != LINK->metasymbol[0]) {
      labelbuf[linx] = s;
      linx++;
      inch(LINK);
      s = ch;
      if (linx + 1 >= const19)
	consterror("READLABEL ", "CONST19   ", const19);
    }
  }
  if (linx - lo > const20) {
    lo = linx;
    fprintf(blst, " *** A PRODUCTION LABEL MUST NOT EXCEED%4ld CHARS\n",
	    (long)const20);
  }
  rhs[pt].length = linx - lo;
}  /*READLABEL*/

/* Local variables for readspecialpurposeinput: */
struct LOC_readspecialpurposeinput {
  struct LOC_ingrammar *LINK;
} ;

Local void readalfa(Char *a, struct LOC_readspecialpurposeinput *LINK)
{
  long i;

  i = 1;
  space(LINK->LINK);
  memcpy(a, "          ", sizeof(alfa_));
  while (isupper(s) || isdigit(s)) {
    if (i <= 10) {
      a[i - 1] = s;
      i++;
    }
    inch(LINK->LINK);
    s = ch;
  }  /* WHILE */
}  /* READALFA */

Local boolean valid(Char ch)
{
  /* valid */
  return (ch == '*' || ch == '_' || ch == '/' || ch == '-' || isalnum(ch));
  /* OR
           ((ch >= chr(ord('A')+40B)) AND (ch <= chr(ord('Z')+40B))); */
}

Local void readlabel_(Char *lab, long *l,
		      struct LOC_readspecialpurposeinput *LINK)
{
  long i;

  i = 1;
  space(LINK->LINK);
  ch = s;
  while (valid(ch)) {
    lab[i - 1] = ch;
    i++;
    inch(LINK->LINK);
  }
  *l = i - 1;
}

Local void readspecialpurposeinput(struct LOC_ingrammar *LINK)
{
  struct LOC_readspecialpurposeinput V;
  labelarr lab;
  alfa_ a;
  long fl, length;

  V.LINK = LINK;
  LINK->eofflag = false;
  readalfa(a, &V);
  LINK->eofflag = true;
  allnolook = false;
  if (strncmp(a, "NOLOOKAHEA", sizeof(alfa_)))
    return;
  ch = ',';
  while (ch != '.') {
    readlabel_(lab, &length, &V);
    if (lab[0] == '*' && length == 1)
      allnolook = true;
    else
      fl = findlabel(lab, length, LINK);
    while (ch == ' ')
      inch(LINK);
    if (ch != ',' && ch != '.') {
      fprintf(blst, ",OR. EXPECTED\n");
      s = '.';
    }
  }
}  /* READ-SPECIAL-PURPOSE-INPUT */



/* SLUT PROCEDURE TERMINAL     */
/*----------------------------------------------------------*/


/*----------------------------------------------------------*/




Static void ingrammar(void)
{
  struct LOC_ingrammar V;
  alfa_ buf;

  if (setjmp(V._JL7777))
    goto _L7777;
  init(&V);
  fprintf(blst,
    "************ A LIST OF INPUT WITH POSSIBLE ERRORMESSAGES  ************");
  fprintf(blst, "%c%c    ", lf(), lf());
  space(&V);   /* READ FIRST NON-BLANK CHARACTER ON INPUT*/
  if (s == 'O') {
    /* OPTIONS INDLAESES */
    do {
      if (s == 'M') {
	fejl(15, &V);
	goto _L111;
      }
      space(&V);
    } while (s != '(');
    space(&V);
    do {
      while (s == ',')
	space(&V);
      if (isdigit(s)) {
	optno = 0;
	do {
	  optno = optno * 10 + s - '0';
	  space(&V);
	} while (s >= '0' && s <= '9');
	if (optno > const18)
	  fejl(16, &V);
	else
	  options[optno - 1] = !options[optno - 1];
      } else {
	if (s != ')') {
	  for (V.i = 1; V.i <= 10; V.i++) {
	    if (isupper(s) || isdigit(s)) {
	      buf[V.i - 1] = s;
	      space(&V);
	    } else
	      buf[V.i - 1] = ' ';
	  }
	  if (!strncmp(buf, "          ", sizeof(alfa_))) {
	    do {
	      if (s == 'M')
		goto _L111;
	      space(&V);
	    } while (s != ')');
	  } else {
	    for (V.i = 1; V.i <= maxopt; V.i++) {
	      if (!strncmp(V.mnemo[V.i - 1].opt, buf, sizeof(alfa_))) {
		options[V.mnemo[V.i - 1].num - 1] =
		  !options[V.mnemo[V.i - 1].num - 1];
		goto _L555;
	      }
	    }
	    fprintf(blst, "%c UNKNOWN MNEMONIC %.*s - IGNORED%c",
		    lf(), alfalength, buf, lf());
_L555: ;
	  }
	}
      }
    } while (s != ')');
    space(&V);
_L111: ;
  }
  /* SLUT PAA INDLAESNING AF OPTIONS */

  memcpy(V.metavar, "METASYMBOL", sizeof(alfa_));
  memcpy(V.m[1], "M1=       ", sizeof(alfa_));
  memcpy(V.m[2], "M2=       ", sizeof(alfa_));
  memcpy(V.m[3], "M3=       ", sizeof(alfa_));
  memcpy(V.m[4], "M4=       ", sizeof(alfa_));
  memcpy(V.m[5], "M5=       ", sizeof(alfa_));
  for (V.i = 0; V.i <= const2; V.i++) {
    /* INITIALISERING AF NONTERMHUSK*/
    husknonterm[V.i].rightboo = false;
    husknonterm[V.i].leftboo = false;
  }
  for (V.i = 0; V.i <= const2; V.i++)
    help[V.i].rightp = rhsnil;
  emptyboo = false;
  error1 = false;
  errorboo = false;
  error2 = false;
  if (s == 'M') {
    metasymb(&V);
    space(&V);
  } else {  /*DEFAULT VAERDIER FOR METASYMBOLER */
    V.metasymbol[0] = '=';
    V.metasymbol[1] = '|';
    V.metasymbol[2] = '<';
    V.metasymbol[3] = ';';
    V.metasymbol[4] = '"';
    fputc(lf(), blst);
    fprintf(blst,
	    " NO METASYMBOLS HAVE BEEN CHOSEN THE FOLLOWING ARE USED \n");
    fprintf(blst, " M1== M2=| M3=< M4=; M5=\"\n");
    fprintf(blst, "%c %c", lf(), s);
  }

  terminput(&V);   /*READ TERMINAL SYMBOLS */

  k = 1;
  top = 1;
  termg = termantal;
  venstreboo = false;
  termantal++;
  nontstart = termantal;
  help[nontstart].rightp = top;
  termantal++;
  if (termantal >= const2)
    consterror("INGRAMMAR ", "CONST2    ", const2);
  internv = termantal;
  goalhusk = termantal;
      /*this should be the goalsymb if no GOALCARD is def*/
  nontermboo = true;
  empty = 127;
  error3 = false;
  noword = true;
  space(&V);
  point = top;
  goaltest = false;
  nboo1 = true;
  nboo2 = false;
  while (s == 'N' || s == 'C' || s == 'S' || s == 'G') {
    switch (s) {

    case 'G':
      goalsymb(&V);
      break;

    case 'S':
      stringdef(&V);
      break;

    case 'C':
      comment(&V);
      break;

    case 'N':
      nontmeta(&V);
      break;
    }
  }
  goalboo = true;
_L13:
  while (s != V.metasymbol[3]) {
    firstboo = true;
    tal = 0;
    if (s == 'M')  /* METASKIFT*/
      metasymb(&V);
    else {
      if (s != V.metasymbol[2]) {
	gramerror(12, &V);
	goto _L13;
      }
      /* NY VENSTRE SIDE*/
      venstreboo = true;
      nterminal(&V.metasymbol[2], &V);
      if (error1) {
	error1 = false;
	goto _L13;
      }
      husk[k - 1] = count;
      k++;
      if (goalboo)
	goalprod(&V);
      husknonterm[count].leftboo = true;
      if (help[count].rightp == rhsnil)
	help[count].rightp = point;
      rhs[point].parserp = NULL;
      rhs[point].link = rhsnil;
      helpp = point;
      huskp = point;
      newelm(&point, "INGRAMMAR ");
      space(&V);
      venstreboo = false;
      if (s != V.metasymbol[0]) {
	gramerror(13, &V);
	goto _L13;
      }
      readlabel(helpp, &V);
      space(&V);
_L10:
      if (s == V.metasymbol[1]) {  /*END OF ALTERNATIVE/BEGINNING OF NEXT*/
	if (tal == 0) {
	  gramerror(8, &V);
	  goto _L13;
	}
	if (emptyboo && tal > 1)
	  fejl(4, &V);
	emptyboo = false;
	rhs[helpp].basisl = tal;
	tal = 0;
	helpp = point;
	rhs[huskp].link = point;
	rhs[point].link = rhsnil;
	rhs[point].parserp = NULL;
	newelm(&point, "INGRAMMAR ");
	readlabel(helpp, &V);
	space(&V);
	goto _L10;
      }
      if (s == V.metasymbol[2]) {  /*READ NONTERMINAL*/
	nterminal(&V.metasymbol[2], &V);
	if (error1) {
	  error1 = false;
	  goto _L13;
	}
	tal++;
	if (tal > 15) {
	  gramerror(19, &V);
	  goto _L13;
	}
	husknonterm[count].rightboo = true;
	rhs[point].parserp = NULL;
	rhs[point].link = rhsnil;
	rhs[point].symbol_ = count;
	huskp = point;
	newelm(&point, "INGRAMMAR ");
	firstboo = false;
	space(&V);
	goto _L10;
      }
      if (s != V.metasymbol[3]) {   /*READ TERMINAL*/
	ch = s;
	terminal(&V);
	if (error2) {
	  error2 = false;
	  goto _L13;
	}
	if (emptyvalue == termrep)
	  emptyboo = true;
	rhs[point].parserp = NULL;
	rhs[point].link = rhsnil;
	tal++;
	if (tal > 15) {
	  gramerror(19, &V);
	  goto _L13;
	}
	rhs[point].symbol_ = termrep;
	huskp = point;
	newelm(&point, "INGRAMMAR ");
	firstboo = false;
	if (ch != ' ')
	  s = ch;
	else
	  space(&V);
	goto _L10;
      }
      if (tal == 0) {
	gramerror(8, &V);
	goto _L13;
      }
      if (emptyboo && tal > 1)
	fejl(4, &V);
      emptyboo = false;
      rhs[helpp].basisl = tal;
      lefthelp[husk[k - 2]] = huskp;
    }
    space(&V);
    emptyboo = false;
  }
  readspecialpurposeinput(&V);
  fprintf(blst,
    "\n\n*********************************  END OF LIST ****************************\n\n\n");
  if (errorboo)
    stop(2);

  if (options[5])
    dumpnonterminternrep(&V);
_L7777: ;

  /*ENDOF ALTERNATIVE/NO MORE FOR THIS LHS*/
}

#undef maxopt


Static void unused(void)
{
  long i, FORLIM;
  _REC_husknonterm *WITH;
  nontelm *WITH1;

  fprintf(blst, "\f");
  fprintf(blst,
    "*******************************  GRAMMARCHECKS  **************************\n");
  /* TEST AF OM DER EX NONTERMINALER ,DER KUN BRUGES PAA ENTEN HQJRE ELLER*/
  /* VENSTRE SIDE,HELE GRAMMATIKKEN CHECKES PAANAER GOALPROD. DENNE OVER - */

  /*OVERSPRINGES,FINDES DER FEJL STANDSER PROGRAMMET */
  if (nboo1)
    goalhusk = husk[0];
  FORLIM = internv;
  for (i = termantal; i < FORLIM; i++) {
    WITH = &husknonterm[i];
    if (!(WITH->leftboo && WITH->rightboo)) {
      WITH1 = WITH->nontermp;
      if (WITH1->nontermvaerdi != goalhusk) {
	fprintf(blst, " %.*s%.*s%.*s",
		alfalength, WITH1->word1, alfalength, WITH1->word2,
		alfalength, WITH1->word3);
	if (WITH->leftboo)
	  fprintf(blst, " APPEARS ONLY IN LEFTSIDE ");
	else
	  fprintf(blst, " APPEARS ONLY IN RIGHTSIDE");
	fputc(lf(), blst);
	nboo2 = true;
      }
      /* VITESTER KUN HVIS DET IKKE ER GOALSYMBOLET*/
    }
  }
  nontslut = internv - 1;
  if (nboo2) {
    stop(3);
    return;
  }
  fprintf(blst, "\nIT HAS BEEN CHECKED THAT ALL NONTERMINALS\n");
  fprintf(blst, "EXCEPT THE GOALSYMBOL APPEAR IN BOTH\n");
  fprintf(blst, "LEFT AND RIGHTSIDE OF A PRODUCTION\n\n");
}  /* UNUSED */


Static void erasure(void)
{
  long lambda, m, ll, kk, k, i, j, l;
  pointer2 pq, oldp, p, pp, ppp;
  boolean boo, ok, slut;
  long FORLIM, FORLIM1;

  if (!options[30])   /* OBS. ERASURE IS NOT PERFORMED*/
    goto _L100;
  boo = false;
  lambda = emptyvalue;
  if (lambda == 0) {
    fprintf(blst, "\nIT HAS BEEN CHECKED THAT NO NONTERMINAL\n");
    fprintf(blst, "CAN PRODUCE THE EMPTY STRING \n\n");
    goto _L100;
  }
  ok = false;
  FORLIM = nontslut;
  for (i = nontstart; i <= FORLIM; i++)
    help[i].status = firsttim;
_L10:
  FORLIM = nontslut;
  for (i = nontstart; i <= FORLIM; i++) {
    /* I GENNEMLQBER ALLE VENSTRESIDER */
    p = help[i].rightp;
    while (p != rhsnil) {
      pp = p;
      ll = rhs[p].basisl;
      allocate(&p);
      if (ll == 1) {
	if (rhs[p].symbol_ == lambda) {
	  /* EN HQJRESIDE ER GENKENDT SOM DEN TOMME STRENG */
	  ok = true;   /* OK ER TRUE HVIS EMPTY FINDES PAA EN HQJRE SIDE */
	  /*  PROD. A..LAMBDA FJERNES */
	  if (pp == help[i].rightp)
	    help[i].rightp = rhs[p].link;
	  else
	    rhs[oldp].link = rhs[p].link;
	  if (help[i].status == firsttim) {
	    help[i].status = finish;
	    FORLIM1 = nontslut;
	    for (j = nontstart + 1; j <= FORLIM1; j++) {
	      p = help[j].rightp;
	      while (p != rhsnil) {
		k = rhs[p].basisl;
		l = p + k;
		pp = p;
		for (m = 1; m <= k; m++) {
		  allocate(&pp);
		  symb = rhs[pp].symbol_;
		  if (symb == i) {
		    pq = p;
		    newelm(&point, "ERASURE   ");
		    /* ppp:=point; rhs[point].p !! truncation */
		    if (k == 1) {
		      rhs[point].basisl = 1;
		      newelm(&point, "ERASURE   ");
		      rhs[point].symbol_ = lambda;
		      rhs[point].parserp = NULL;
		      allocate(&pq);
		    } else {
		      rhs[point].basisl = k - 1;
		      while (pq < l) {
			allocate(&pq);
			if (pq != pp) {
			  newelm(&point, "ERASURE   ");
			  rhs[point].parserp = NULL;   /*TRUNC*/
			  rhs[point].symbol_ = rhs[pq].symbol_;
			}
		      }
		    }
		    rhs[point].link = rhs[pq].link;
		    rhs[pq].link = ppp;
		  }
		}
		oldp = pp;
		p = rhs[pp].link;
	      }
	    }
	    goto _L10;   /* DER STARTES NU FORFRA MED GRAMMATIKKEN */
	  }
	}
      }
      for (kk = 2; kk <= ll; kk++)
	allocate(&p);
      oldp = p;
      p = rhs[p].link;
    }
  }
  do {
    slut = true;
    FORLIM = nontslut;
    for (i = nontstart; i <= FORLIM; i++) {
      p = help[i].rightp;
      while (p != rhsnil) {
	pp = p;
	ll = rhs[p].basisl;
	boo = false;
	for (kk = 1; kk <= ll; kk++) {
	  allocate(&pp);
	  symb = rhs[pp].symbol_;
	  if (symb > termg)
	    boo = (boo || help[symb].rightp == rhsnil);
	}
	if (boo) {
	  if (p == help[i].rightp) {
	    pq = rhs[pp].link;
	    help[i].rightp = pq;
	    if (pq == rhsnil)
	      slut = false;
	  } else
	    rhs[oldp].link = rhs[pp].link;
	} else
	  oldp = pp;
	p = rhs[pp].link;
      }
    }
  } while (!slut);
  fprintf(blst, "%c%c", lf(), lf());
  if (ok) {
    fprintf(blst, " THE GRAMMAR IS MODIFIED FOR ERASURE \n");
    fprintf(blst, " I. E. NO NONTERMINAL CAN NOW PRODUCE THE EMPTY STRING\n");
  } else {
    fprintf(blst, " EMPTY HAS BEEN SPECIFIED AS A TERMINAL SYMBOL,\n");
    fprintf(blst, " BUT IT HAS NOT BEEN USED \n");
  }
  putc('\n', blst);
_L100: ;
}


/****************************************************************************/
/* ELIMINATED, since pascal compiler complains about too many local variables?
(* NOTE: internal comments herein have been substituted with "( *" eand "* )"
 procedure vhrecurs;
   label 10;
   var
     sn: record  case b: boolean of
               true: (p: integer ( * pointer2 * ) );
               false: (pvaerdi: integer);
            end;
     p2: pointer2;
     ( * OBS! In the original version of BOBS, sn.p is a pointer2 * )
     ( * This might not work in all Pascal implementations.       * )
     ( * P2 is used to coerse p * )

     boo: boolean;
     ii,ll,i,j,l: integer;
     start: integer;
     pt1s,ph1s: bitmatrix ;

     procedure writeheadsandtails;
     label 10,20;
     var
       nomoretails,nomoreheads: boolean;
       headsymb,tailsymb,symb,tael,i :integer;
     begin
       page(blst);
       write(blst,'A LIST OF PRODUCED 1-HEADS AND 1-TAILS FOR ALL NONTERMINALS');
       for i:=1 to 34 do write(blst,' '); write(blst,'I');
       for i:=1 to 45 do write(blst,' '); write(blst,'I',lf);
       write(blst,'              SYMBOL              I     TERMINAL TAILS');
       write(blst,lf);
       for i:=1 to 34 do write(blst,' '); write(blst,'I');
       for i:=1 to 45 do write(blst,' '); write(blst,'I');
       for symb:=nontstart+1 to nontslut do
       begin
         tael:=1; nomoreheads:=false; nomoretails:=false;
         headsymb:=0; tailsymb:=0;
         write(blst,lf,' ');
         for i:=1 to 33 do write(blst,'-'); write(blst,'I');
         for i:= 1 to 45 do write(blst,'-'); write(blst,'I');
         for i:=1 to 45 do write(blst,'-');
         write(blst,lf,' ');
         nontwrit(symb,tael);
         repeat
           if headsymb<>0 then write(blst,lf); ( * NO LINESHIFT FIRST TIME IN LOOP * )
           for tael:=tael+1 to 34 do write(blst,' ');      write(blst,'I');
           for i:=1 to 4 do ( * PRINT 4 HEADS IF THEY EXIST ELSE SPACES * )
           begin
             headsymb:=headsymb+1;
             while headsymb<nontstart do
             if(headsymb mod (setmax+1))in ph1s[symb].r[headsymb div (setmax+1)
] then goto 10
             else headsymb:=headsymb+1;
             nomoreheads:=true;
             10:
                if nomoreheads then write(blst,' ','    ')
                else write(blst,' ',internrep[headsymb]);
           end;
           write(blst,' ','I');
           for i:=1 to 4 do ( * PRINT 4 TAILS IF THEY EXIST ELSE SPACES * )
           begin
             tailsymb:=tailsymb+1;
             while tailsymb<nontstart do
             if(tailsymb mod (setmax+1))in pt1s[symb].r[tailsymb div (setmax+1)
] then goto 20
             else tailsymb:=tailsymb+1;
             nomoretails:=true;
             20:
                if nomoretails then write(blst,' ','    ')
                else write(blst,' ',internrep[tailsymb]);
           end;
           tael:=0;
         until nomoretails and nomoreheads;
       end;
       write(blst,lf,' ');
     end;


     procedure iterer(var matrix: bitmatrix);
     var
       n,up1,up2,nn,m,k,kk,l,i,j: integer;
       slut:boolean;
       gem,boo: rtypeset;
       trans: bitmatrix;
       fresh: rtype;
     begin
       n:=nontslut div (setmax+1);
       nn:=nontslut-n*(setmax+1);
       if options[19] then write(blst,lf,' NONTSLUT',nontslut,'        N',n); ( * trunc * )


       repeat up1:=setmax;  slut:=true;
         ( * MATRIXEN MATRIX TRANSPONERES  OVER I MATRIXEN TRANS * )
         k:=-1;
         for m:=0 to n do
         begin
           if m=n then up1:=nn;
           for kk:=0 to up1 do
           begin
             k:=k+1;
             j:=-1; up2:=setmax;
             for l:=0 to n do
             begin
               boo:=[]; if l=n then up2:=nn;
               for i:=0 to up2 do
               begin
                 j:=j+1;
                 if(kk in matrix[j].r[m]) then boo:=boo + [i];
               end;
               trans[k].r[l]:=boo;
             end;
           end;
         end;

         for i:=0 to const13 do fresh.r[i]:=[];
         ( * HER STARTES SELVE ITERERINGEN * )
         for k:=nontstart to nontslut do
         with matrix[k] do
         begin
           i:=-1;  up2:=setmax;
           for l:=0 to n do
           begin
             gem:=[]; if l=n then up2:=nn;
             for m:=0 to up2 do
             begin
               i:=i+1; boo:=[];
               for j:=0 to n do
               boo:=boo + (r[j] * trans[i].r[j]);
                if boo<>[] then gem:=gem + [m];
             end;
             fresh.r[l]:=gem;
           end;
           for j:=0  to n do
           begin
             gem:=r[j] + fresh.r[j];
             if gem<>r[j] then
              begin  r[j]:=gem;
                slut:=false;
              end;
           end;
         end;
       until slut;
     end;
   begin
     if options[25] then goto 10;
     i:=nontslut div (setmax+1);
     if i>const13 then
      begin
        write(blst,lf,lf,' CONST13',' MUST BE',i,lf);
        consterror('VHRECURS  ','CONST13   ',const13);
      end;
     for i:=0 to const2 do
     for j:=0 to const13 do
     begin
       ph1s[i].r[j]:=[];
       pt1s[i].r[j]:=[];
     end;
     with sn do
     for i:=nontstart to nontslut do
     begin
       p:=help[i].rightp;
       while p<>rhsnil do
       begin
         l:=rhs[p].basisl;
         p2:=p;
         allocate(p2);
         ll:=rhs[p].symbol;
         ii:=ll div (setmax+1);
         ph1s[i].r[ii]:=ph1s[i].r[ii] + [ll mod (setmax+1)];
         pvaerdi:=pvaerdi+l-1;
         ll:=rhs[p].symbol;
         ii:=ll div (setmax+1);
         pt1s[i].r[ii]:=pt1s[i].r[ii] + [ll mod (setmax+1)];
         p:=rhs[p].link;
       end;
     end;
     if options[20]  then
      begin
        matrixout(ph1s);
        matrixout(pt1s);
      end;
     iterer(ph1s);
     iterer(pt1s);
     if options[20]  then
      begin
        matrixout(ph1s);
        matrixout(pt1s);
      end;
     if options[18] then writeheadsandtails;
     boo:=false; l:=1;
     start:=nontstart+1;
     for ii:=start to nontslut do
     begin i:=ii div (setmax+1);
       if( ph1s[ii].r[i] * pt1s[ii].r[i] * [ii mod (setmax+1)])<>[] then
        begin
          boo:=true;
          write(blst,lf,' '); nontwrit(ii,l);
        end;
     end;
     if boo then
      begin
        writeln(blst);
        write(blst,' THE ABOVE STANDING NONTERMINALS ');write(blst,lf);
        write(blst,' ARE BOTH LEFT AND RIGHT RECURSIVE ');write(blst,lf);
        write(blst,' THE PROGRAM TERMINATES ');
        stop(3);
      end;
      writeln(blst);
      writeln(blst,'IT HAS BEEN CHECKED THAT NO NONTERMINAL');
      writeln(blst,'IS BOTH LEFT AND RIGHT RECURSIVE');
      writeln(blst);
     10:
   end;
*/
/********************* vhrecurs***************************/

Static void termination(void)
{
  pointer2 p;
  boolean nonew, termboo;
  long i, j, k, FORLIM;
  _REC_rhs *WITH;

  FORLIM = nontslut;
  for (i = nontstart; i <= FORLIM; i++)
    help[i].term = false;
  do {
    nonew = true;
    FORLIM = nontslut;
    for (i = nontstart; i <= FORLIM; i++) {
      if (!help[i].term) {
	p = help[i].rightp;
	while (p != rhsnil) {
	  k = rhs[p].basisl;
	  termboo = true;
	  for (j = 1; j <= k; j++) {
	    allocate(&p);
	    WITH = &rhs[p];
	    if (WITH->symbol_ > termg)
	      termboo = (termboo && help[WITH->symbol_].term);
	  }
	  if (termboo) {
	    nonew = false;
	    help[i].term = true;
	    p = rhsnil;
	  } else
	    p = rhs[p].link;
	}
      }
    }
  } while (!nonew);
  termboo = false;
  k = 0;
  FORLIM = nontslut;
  for (i = nontstart + 1; i <= FORLIM; i++) {
    if (help[i].rightp != rhsnil && !help[i].term) {
      fprintf(blst, "%c%c ", lf(), lf());
      nontwrit(i, &k);
      termboo = true;
    }
  }
  if (!termboo) {
    fprintf(blst, "\nIT HAS BEEN CHECKED THAT ALL NONTERMINALS CAN\n");
    fprintf(blst, "PRODUCE A STRING OF ONLY TERMINAL SYMBOLS\n\n");
    return;
  }
  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, " THE ABOVE STANDING NONTERMINALS CANNOT PRODUCE");
  fputc(lf(), blst);
  fprintf(blst, " A STRING OF ONLY TERMINAL SYMBOLS ");
  stop(3);
}


/* Local variables for idogfjern: */
struct LOC_idogfjern {
  boolean fjboo;
} ;

/* Local variables for fjernkaede: */
struct LOC_fjernkaede {
  struct LOC_idogfjern *LINK;
  long fjern, indsat;
} ;

Local void fjskriv(struct LOC_fjernkaede *LINK)
{
  long z;

  z = 1;
  putc(' ', blst);
  nontwrit(LINK->fjern, &z);
  fprintf(blst, "  HAS BEEN SUBSTITUTED BY  ");
  nontwrit(LINK->indsat, &z);
  fputc(lf(), blst);
}

Local boolean fjernkaede(boolean *t, struct LOC_idogfjern *LINK)
{
  struct LOC_fjernkaede V;
  boolean Result;
  long i, k, l, m, n, s;
  pointer2 j;

  V.LINK = LINK;
  Result = false;
  k = nontslut;
  i = nontstart - 1;
  do {
    i++;
    j = help[i].rightp;
    if (j != rhsnil) {
      if (rhs[j].basisl == 1) {
	allocate(&j);
	if (rhs[j].link == rhsnil && rhs[j].symbol_ > termg) {
	  V.indsat = rhs[j].symbol_;
	  V.fjern = i;
	  help[i].rightp = rhsnil;
	  Result = true;
	  LINK->fjboo = true;
	  if (*t)
	    fjskriv(&V);
	  s = nontstart - 1;
	  do {
	    s++;
	    j = help[s].rightp;
	    if (j != rhsnil) {
	      l = rhs[j].basisl;
	      m = 0;
	      do {
		for (n = 1; n <= l; n++) {
		  allocate(&j);
		  if (rhs[j].symbol_ == V.fjern)
		    rhs[j].symbol_ = V.indsat;
		}
		if (rhs[j].link != rhsnil) {
		  j = rhs[j].link;
		  l = rhs[j].basisl;
		} else
		  m = 1;
	      } while (m != 1);
	    }
	  } while (s != k);
	}
      }
    }
  } while (i != k);
  return Result;
}

/* Local variables for identprod: */
struct LOC_identprod {
  struct LOC_idogfjern *LINK;
  long laengde2, j;
  pointer2 startp2;
} ;

Local void skriv(long *x, struct LOC_identprod *LINK)
{
  long l, jj, ll;
  pointer2 stepp3;
  long FORLIM;

  /*UDSKRIVNING OM AENDRING I GRAMMATIKKEN */
  stepp3 = LINK->startp2;
  if (*x == 1) {
    fprintf(blst, "%c%c", lf(), lf());
    fprintf(blst, " IDENTICALS PRODUCTIONS EXIST   ");
    fputc(lf(), blst);
    fprintf(blst, " AND THE GRAMMAR IS MODIFIED  ");
    fputc(lf(), blst);
    fprintf(blst, " THE FOLLOWING PRODUCTION(S) EXIST MORE THAN ONCE ");
    fputc(lf(), blst);
  }
  putc(' ', blst);
  jj = 1;
  nontwrit(LINK->j, &jj);
  fprintf(blst, " ::= ");
  FORLIM = LINK->laengde2;
  for (l = 1; l <= FORLIM; l++) {
    allocate(&stepp3);
    ll = rhs[stepp3].symbol_;
    if (ll <= termg) {
      /* HQJRE SIDE ER ET TERMINAL SYMBOL */
      outalf20(internrep[ll + 1], &jj);
    } else {
      /*HQJRE SIDE ER ET NONTERMINAL SYMBOL */
      nontwrit(ll, &jj);
    }
    putc(' ', blst);
  }
  fputc(lf(), blst);
}


Local boolean identprod(boolean *t, struct LOC_idogfjern *LINK)
{
  struct LOC_identprod V;
  long laengde1, i, kk;
  boolean ens, idboo;
  pointer2 startp1, stepp1, stepp2, lastok;
  long FORLIM, FORLIM1;


  V.LINK = LINK;
  kk = 0;
  idboo = false;

  FORLIM = nontslut;
  for (V.j = nontstart; V.j <= FORLIM; V.j++) {
    startp1 = help[V.j].rightp;
    if (startp1 != rhsnil) {
      do {
	laengde1 = rhs[startp1].basisl;
	V.startp2 = startp1;
	for (i = 1; i <= laengde1; i++)
	  allocate(&V.startp2);
	lastok = V.startp2;
	V.startp2 = rhs[V.startp2].link;
	if (V.startp2 != rhsnil) {
	  do {
	    ens = false;
	    stepp1 = startp1;
	    stepp2 = V.startp2;
	    V.laengde2 = rhs[stepp2].basisl;
	    if (laengde1 == V.laengde2) {
	      ens = true;
	      for (i = 1; i <= laengde1; i++) {
		allocate(&stepp1);
		allocate(&stepp2);
		if (rhs[stepp1].symbol_ != rhs[stepp2].symbol_)
		  ens = false;
	      }
	      if (ens) {
		kk++;
		if (*t)
		  skriv(&kk, &V);
		idboo = true;
		rhs[lastok].link = rhs[stepp2].link;
	      }
	    } else {
	      FORLIM1 = V.laengde2;
	      for (i = 1; i <= FORLIM1; i++)
		allocate(&stepp2);
	    }
	    if (!ens)
	      lastok = stepp2;
	    stepp2 = rhs[stepp2].link;
	    if (stepp2 != rhsnil)
	      V.startp2 = stepp2;
	  } while (stepp2 != rhsnil);
	  for (i = 1; i <= laengde1; i++)
	    allocate(&startp1);
	  startp1 = rhs[startp1].link;
	  if (startp1 == rhsnil)
	    startp1 = V.startp2;
	} else
	  V.startp2 = startp1;
      } while (startp1 != V.startp2);
    }
  }
  if (idboo == false && *t) {
    fprintf(blst, "\nIT HAS BEEN CHECKED  THAT THERE \n");
    fprintf(blst, "EXISTS NO IDENTICAL PRODUCTIONS \n\n");
  }
  return idboo;
}




Static void idogfjern(boolean b)
{
  struct LOC_idogfjern V;
  boolean boo1, boo2, boo3, boo4;

  if (b && options[22]) {
    fputc(lf(), blst);
    fprintf(blst, " DUMP BEFOR IDOGFJERN ");
    fprintf(blst, "%c%c", lf(), lf());
    dump5();
    fprintf(blst, "%c%c", lf(), lf());
    dump2();
    fprintf(blst, "%c%c", lf(), lf());
  }
  V.fjboo = false;
  boo1 = b;
  boo2 = b;
  boo3 = true;
  while (boo3) {
    boo4 = identprod(&boo1, &V);
    if (options[27])
      boo3 = false;
    else
      boo3 = fjernkaede(&boo2, &V);
    boo3 = (boo3 || boo4);
    boo1 = false;
  }
  if (options[27] == false) {
    if (V.fjboo && b) {
      fprintf(blst, " THE GRAMMER HAS BEEN MODIFIED FOR SIMPLE CHAINS ");
      fputc(lf(), blst);
      fprintf(blst, " USING THE ABOVE STANDING SUBSTITUTIONS ");
      fputc(lf(), blst);
    }
    if (b && V.fjboo == false) {
      fprintf(blst, " THE GRAMMER HAS BEEN CHECKED FOR ");
      fputc(lf(), blst);
      fprintf(blst, " SIMPLE CHAINS ");
      fputc(lf(), blst);
    }
  }
  if (!(b && options[23]))
    return;
  fputc(lf(), blst);
  fprintf(blst, " DUMP AFTER IDOGFJERN ");
  fprintf(blst, "%c%c", lf(), lf());
  dump5();
  fprintf(blst, "%c%c", lf(), lf());
  dump2();
  fprintf(blst, "%c%c", lf(), lf());
}


Static void freelist(konfigt *pt)
{
  konfigt *p;

  p = pt;
  while (p->derivp != NULL)
    p = p->derivp;
  p->derivp = freeptr;
  freeptr = pt;
}  /*FREELIST*/


typedef struct _REC_stack {
  /*packed*/
  short symbovg;
  konfigt *tilstp;
} _REC_stack;

/* Local variables for lr0: */
struct LOC_lr0 {
  /******   PROC. LR(0) KRAEVER :                                 */
  /* GOALPRODUKTIONSNUMMER I 'GOALPROD'                    */
  /* FQRSTE FRIE CELLE I RIGHTSIDE I 'TOP'                 */
  /* 'LEFTSIDE' I PROD-ARRAY FQRSTE TOMME CELLE NULSTILLET    */
  _REC_stack stack[const9];
  pointer2 lqbep2;
  long baslae, stacktop, stacktael;
} ;

/* Local variables for niceparser: */
struct LOC_niceparser {
  struct LOC_lr0 *LINK;
  long i, pnr, l, count, nbcount, nextcount, suc, statenr, nr;
  pointer2 rightp;
} ;

Local long sqg(konfigt *p, struct LOC_niceparser *LINK)
{
  long i;

  /*SQG*/
  i = 0;
  while (p != tilstand[i].oldstart)
    i++;
  return i;
}

Local void linemark(struct LOC_niceparser *LINK)
{
  long i, FORLIM;

  /*LINEMARK*/
  fputc(lf(), blst);
  FORLIM = LINK->nextcount;
  for (i = 1; i <= FORLIM; i++)
    putc(' ', blst);
  putc('^', blst);
  fputc(lf(), blst);
}

Local void udskriv(struct LOC_niceparser *LINK)
{
  long k, j;
  prodtype *WITH;
  long FORLIM;
  _REC_rhs *WITH1;
  long FORLIM1;

  /*UDSKRIV */
  WITH = &prod[LINK->pnr];
  k = WITH->leftside;
  LINK->rightp = WITH->start;
  LINK->l = WITH->laengde;
  if (LINK->statenr > 0)
    fprintf(blst, " %s", blank);
  else
    fprintf(blst, " %10ld", LINK->i);
  if (LINK->suc >= 0)
    fprintf(blst, "%10ld ", LINK->suc);
  else {
    if (LINK->nr == 0)
      fprintf(blst, "    REDUCE ");
    else
      fprintf(blst, "%s ", blank);
  }
  fprintf(blst, "    ");
  LINK->count = 26;
  if (k == nontstart) {
    fprintf(blst, "<GOALSYMBOL>");
    LINK->count += 12;
  } else
    nontwrit(k, &LINK->count);
  fprintf(blst, " ::= ");
  LINK->count += 5;
  LINK->nbcount = LINK->count;
  LINK->nextcount = -1;
  FORLIM = LINK->l;
  for (k = 1; k <= FORLIM; k++) {
    if (k == LINK->nr)
      LINK->nextcount = LINK->count;
    allocate(&LINK->rightp);
    WITH1 = &rhs[LINK->rightp];
    if (WITH1->symbol_ >= nontstart)
      nontwrit(WITH1->symbol_, &LINK->count);
    else
      outalf20(internrep[WITH1->symbol_ + 1], &LINK->count);
    putc(' ', blst);
    LINK->count++;
    if (LINK->count >= 110) {
      if (LINK->nextcount >= 0)
	linemark(LINK);
      else
	fputc(lf(), blst);
      FORLIM1 = LINK->nbcount;
      for (j = 1; j <= FORLIM1; j++)
	putc(' ', blst);
      LINK->nextcount = -1;
      LINK->count = LINK->nbcount;
    }
  }
  if (LINK->nextcount >= 0)
    linemark(LINK);
  else
    fputc(lf(), blst);
}

Local void niceparser(struct LOC_lr0 *LINK)
{
  struct LOC_niceparser V;
  konfigt *p;
  long FORLIM;
  konfigt *WITH;

  V.LINK = LINK;
  /*NICEPARSER*/
  fprintf(blst, "\f");
  fprintf(blst, "*************************");
  fprintf(blst, "  THE LR(0)-MACHINE  ");
  fprintf(blst, "**************************");
  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, " STATE NUMBER SUCCESSOR   CONFIGURATION SETS");
  fputc(lf(), blst);
  FORLIM = tilstnr;
  for (V.i = 0; V.i <= FORLIM; V.i++) {
    p = tilstand[V.i].oldstart;
    V.statenr = 0;
    do {
      WITH = p;
      V.pnr = WITH->UU.U1.prodnr;
      V.nr = WITH->mode;
      if (WITH->nextp != NULL)
	V.suc = sqg(WITH->nextp, &V);
      else
	V.suc = -1;
      p = WITH->derivp;
      udskriv(&V);
      V.statenr++;
    } while (p != NULL);
    fputc(lf(), blst);
  }
  fputc(lf(), blst);
}

Local void juster(konfigt *startp, boolean boo, struct LOC_lr0 *LINK)
{
  /******   FOR NY TILSTAND NOTERES FOREKOMST AF  */
  /* (PROD. NR., SYMBOL NR.) FOR DENNE   */
  /* uses global variables top, baslae, inf and begintilst (=startp??) */
  long i;
  konfigt *WITH;
  _REC_rhs *WITH1;

  lqbep = startp;
  while (lqbep != NULL) {
    WITH = lqbep;
    LINK->lqbep2 = prod[WITH->UU.U1.prodnr].start;
    for (i = WITH->mode; i >= 1; i--)
      allocate(&LINK->lqbep2);
    if (rhs[LINK->lqbep2].parserp != NULL) {
      while (rhs[LINK->lqbep2].link != rhsnil)
	LINK->lqbep2 = rhs[LINK->lqbep2].link;
      rhs[LINK->lqbep2].link = top;
      LINK->lqbep2 = top;
      newelm(&top, "LR0       ");
    }
    WITH1 = &rhs[LINK->lqbep2];
    WITH1->basis = boo;
    if (boo)
      WITH1->basisl = LINK->baslae;
    WITH1->parserp = begintilst;
    WITH1->link = rhsnil;
    lqbep = WITH->derivp;
  }
}

Local void stackellerej(struct LOC_lr0 *LINK)
{
  /******   CHECKER HVORVIDT  (TILSTAND, OVERGANGSSYMBOL)
    ER STAKKET ELLER SKAL STAKKES      */
  konfigt *WITH;
  _REC_help *WITH1;
  _REC_stack *WITH2;

  WITH = classtop;
  WITH1 = &help[WITH->UU.U1.inf];
  if (WITH1->overgang)
    return;
  LINK->stacktael++;
  if (LINK->stacktop == const9)
    consterror("LR0       ", "CONST9    ", const9);

  LINK->stacktop++;
  WITH1->overgang = true;
  WITH2 = &LINK->stack[LINK->stacktop - 1];
  WITH2->symbovg = WITH->UU.U1.inf;
  WITH2->tilstp = begintilst;
}

/* Local variables for geninititems: */
struct LOC_geninititems {
  struct LOC_lr0 *LINK;
} ;

Local long makegoalprod(long sy, struct LOC_geninititems *LINK)
{
  long Result;
  pointer2 ptr;
  long i;
  _REC_rhs *WITH;

  prodcount++;
  Result = prodcount;

  ptr = top;
  prod[prodcount].start = top;
  prod[prodcount].leftside = nontstart;
  prod[prodcount].laengde = 3;
  prod[prodcount].lookbackp = NULL;
  rhs[top].basisl = 3;
  newelm(&top, "GOALPROD  ");
  rhs[top].symbol_ = 0;
  newelm(&top, "GOALPROD  ");
  rhs[top].symbol_ = sy;
  newelm(&top, "GOALPROD  ");
  rhs[top].symbol_ = 1;
  newelm(&top, "GOALPROD  ");   /* note it is assumed that top is unused*/
  for (i = 1; i <= 4; i++) {
    WITH = &rhs[ptr];
    WITH->link = rhsnil;
    WITH->parserp = NULL;
    allocate(&ptr);
  }
  /*      top:=ptr;*/
  return Result;
}

Local konfigt *goalitem(long sy, struct LOC_geninititems *LINK)
{
  konfigt *Result;
  pointer2 ptr;
  konfigt *WITH;

  allocp(&classtop, 1, "LR0       ");
  Result = classtop;
  WITH = classtop;
  WITH->ifbasis = true;
  WITH->UU.U1.prodnr = makegoalprod(sy, LINK);
  WITH->mode = 1;
  ptr = prod[WITH->UU.U1.prodnr].start;
  allocate(&ptr);
  WITH->UU.U1.inf = rhs[ptr].symbol_;
  WITH->derivp = NULL;
  LINK->LINK->stacktop++;
  LINK->LINK->stack[LINK->LINK->stacktop - 1].tilstp = classtop;
  LINK->LINK->stack[LINK->LINK->stacktop - 1].symbovg = classtop->UU.U1.inf;
  begintilst = classtop;
  juster(classtop, true, LINK->LINK);
  return Result;
}

Local void geninititems(struct LOC_lr0 *LINK)
{
  /* This procedure extends the BOBS system  such that any  nonterminal
     can be  the startsymbol (goal symbol) of the parser.
     For each nonterminal A in [nontStart+1, nontSlut], a production
        G ::=  bobs-go A  -eof-
     is added.
     These productions  are stored in prod[antalProd+1] ... prod[antalprod+M]
     where M=(nontSlut - nontStart)
     Note nontStart is the goal-symbol generated by BOBS. Not the goalsymbol
     specified by the user.

     For each A in [nontStart+1,nontSlut] the following LR(0)-items are generated
        [G ::= bobs-go . A -eof-]
     where G is the goalsymbol generated by BOBS.

    tilstand[0] will denote the start state of the goalsymbol.
    tilstand[A-nontStart] will denote the start state of nonterm A.
    If A is the goalsymbol specified by the user
    then tilstand[0]=tilstand[A-nontstart];

    In procedure compress, a change has also been made. In all reduce states
    for goalproductions mode must be 0. mode=0 terminates the parsing.
    */
  struct LOC_geninititems V;
  long sy, FORLIM;

  V.LINK = LINK;
  LINK->stacktop = 0;
  prodcount = antalprod;
  LINK->baslae = 1;   /*used by procedure juster */
  tilstnr = 0;
  tilstand[tilstnr].oldstart = goalitem(goalhusk, &V);
  FORLIM = nontslut;
  for (sy = nontstart + 1; sy <= FORLIM; sy++) {
    tilstnr++;
    if (sy != goalhusk)
      tilstand[tilstnr].oldstart = goalitem(sy, &V);
    else
      tilstand[tilstnr].oldstart = tilstand[0].oldstart;
  }
}


/*$L+*/
Static void lr0(void)
{
  struct LOC_lr0 V;
  konfigt *helpp, *closp, *oldp;
  long modeh, i, symb, prodno;
  boolean kopi;
  long goalprod;
  _REC_stack *WITH;
  _REC_help *WITH1;
  konfigt *WITH2;
  _REC_rhs *WITH3;
  prodtype *WITH4;
  konfigt *WITH5;


  /******    INITIALISERING   */
  goalprod = 0;
  top = point;
  newelm(&top, "LR0       ");
  freeptr = NULL;
  antaltilst = 0;
  lbbegin = 0;
  lbend = -1;

  geninititems(&V);

  /* This comment encloses the code allocating the 'old' initial item *
     allocp(rodp,1,'LR0       ');
     classtop:= rodp;
     WITH rodp^ DO
     BEGIN
       ifbasis:=true;
       prodnr:= goalprod;
       mode:= 1;
       lqbep2:= prod[goalprod].start;
       allocate(lqbep2);
       inf:= rhs[lqbep2].symbol;
       derivp:= nil;
     END;
     baslae:=1;
     stacktop:= 1;
     WITH stack[1] DO
     BEGIN
       tilstp:= rodp;
       symbovg:= rodp^.inf
     END;
     tilstnr:= 0;
     tilstand[tilstnr].oldstart:= rodp;
     juster(rodp,true);
   end of old initial item generation  */

  allocp(&classtop, 1, "LR0       ");
  begintilst = classtop;
  while (V.stacktop > 0) {
    WITH = &V.stack[V.stacktop - 1];
    /******    TILSTAND,OVERGANGSSYMBOL AFSTAKKES.   */
    oldp = WITH->tilstp;
    symb = WITH->symbovg;
    lqbep = oldp;
    V.stacktael = 0;
    V.baslae = 0;
    V.stacktop--;
    for (i = 0; i <= const2; i++) {
      WITH1 = &help[i];
      WITH1->afledt = false;
      WITH1->overgang = false;
    }
    /******    NYT BASIS-SET GENERERES  */
    while (lqbep->UU.U1.inf != symb)
      lqbep = lqbep->derivp;
    closp = lqbep;
    while (true) {
      if (V.baslae == const5)
	consterror("LR0       ", "CONST5    ", const5);
      V.baslae++;
      WITH2 = classtop;
      WITH2->ifbasis = true;
      WITH2->nextp = NULL;
      WITH2->UU.U1.prodnr = lqbep->UU.U1.prodnr;
      modeh = lqbep->mode + 1;
      if (prod[WITH2->UU.U1.prodnr].laengde < modeh) {
	WITH2->mode = 0;
	WITH2->UU.U1.inf = 0;
      } else {
	WITH2->mode = modeh;
	V.lqbep2 = prod[WITH2->UU.U1.prodnr].start;
	for (i = WITH2->mode; i >= 1; i--)
	  allocate(&V.lqbep2);
	WITH2->UU.U1.inf = rhs[V.lqbep2].symbol_;
	stackellerej(&V);
      }
      do {
	lqbep = lqbep->derivp;
	if (lqbep == NULL)
	  goto _L20;
      } while (lqbep->UU.U1.inf != symb);
      helpp = classtop;
      allocp(&classtop, 1, "LR0       ");
      helpp->derivp = classtop;
    }
_L20:
    classtop->derivp = NULL;
    /******   TEST OM BASIS-SET ER GENGANGER  */
    kopi = false;
    V.lqbep2 = prod[begintilst->UU.U1.prodnr].start;
    for (i = begintilst->mode; i >= 1; i--)
      allocate(&V.lqbep2);
    if (rhs[V.lqbep2].parserp != NULL) {
      while (V.lqbep2 != rhsnil && !kopi) {
	WITH3 = &rhs[V.lqbep2];
	if (WITH3->basis) {
	  if (V.baslae == WITH3->basisl) {
	    kopi = true;
	    lqbep = begintilst;
	    while (lqbep != NULL && kopi) {
	      WITH2 = lqbep;
	      kopi = false;
	      helpp = WITH3->parserp;
	      while (helpp != NULL) {
		kopi = ((WITH2->UU.U1.prodnr == helpp->UU.U1.prodnr &&
			 WITH2->mode == helpp->mode) || kopi);

		helpp = helpp->derivp;
	      }
	      lqbep = WITH2->derivp;
	    }
	  }
	}
	if (!kopi)
	  V.lqbep2 = WITH3->link;
      }
    }
    if (kopi) {
      /******   BASIS-SET GENKENDT  */
      closp->nextp = rhs[V.lqbep2].parserp;
      V.stacktop -= V.stacktael;
      freelist(begintilst);
      allocp(&classtop, 1, "LR0       ");
      begintilst = classtop;
      continue;
    }
    /******    BASIS-SET ACCEPTERET SOM NYT  */
    closp->nextp = begintilst;
    if (tilstnr == const10)
      consterror("LR0       ", "CONST10   ", const10);
    tilstnr++;
    tilstand[tilstnr].oldstart = begintilst;
    juster(begintilst, true, &V);
    /******     TILHQRENDE CLOSURE-SET GENERERES.    */
    closp = classtop;
    lqbep = begintilst;
    while (lqbep != NULL) {
      WITH2 = lqbep;
      WITH1 = &help[WITH2->UU.U1.inf];
      if (WITH2->mode > 0) {
	if (WITH2->UU.U1.inf > termg) {
	  if (!WITH1->afledt) {
	    WITH1->afledt = true;
	    prodno = WITH1->prodindex;
	    while (prod[prodno].leftside == WITH2->UU.U1.inf) {
	      WITH4 = &prod[prodno];
	      helpp = classtop;
	      allocp(&classtop, 1, "LR0       ");
	      helpp->derivp = classtop;
	      WITH5 = classtop;
	      WITH5->ifbasis = false;
	      V.lqbep2 = WITH4->start;
	      allocate(&V.lqbep2);
	      WITH5->UU.U1.inf = rhs[V.lqbep2].symbol_;
	      if (prod[prodno].laengde == 0)   /*EMPTY RIGHTHAND SIDE*/
		WITH5->mode = 0;   /*TRUNC!!*/
	      else
		WITH5->mode = 1;
	      WITH5->UU.U1.prodnr = prodno;
	      WITH5->derivp = NULL;
	      WITH5->nextp = NULL;
	      if (classtop->mode > 0)
		stackellerej(&V);
	      prodno++;
	    }
	  }
	}
      }
      lqbep = WITH2->derivp;
    }
    if (closp->derivp != NULL)
      juster(closp->derivp, false, &V);
    allocp(&classtop, 1, "LR0       ");
    begintilst = classtop;
  }
  gemp = classtop;
  if (options[1])
    skrivparser(classtop);
  if (options[29])
    niceparser(&V);
  /*   dump1;  point:=top;  top:=1; dump2; top:=point; */
}


/******  END OF PROCEDURE  LR0      */

/*$L-*/
Static void lookb(void)
{
  /* LOOKB GENERATES THE LOOKBACKSTATES */
  long prodnr, symb, md, r1;
  pointer2 point;
  konfigt *tilstp;
  prodtype *WITH;
  konfigt *WITH1;

  /* END LOOKB */
  prod[0].lookbackp = NULL;
  antaltilst = tilstnr;
  lbbegin = tilstnr + 1;
  freeptr = NULL;

  prodnr = 1;
  while (prodnr <= antalprod) {   /*FOR prodnr:=1 TO antalprod DO*/
    WITH = &prod[prodnr];
    fcqi = 0;
    allocp(&classtop, 5, "LOOKBP    ");
    begintilst = classtop;
    symb = WITH->leftside;
    point = WITH->start;
    if (WITH->laengde > 0)   /*RHS NOT EMPTY*/
      allocate(&point);
    while (point != rhsnil) {
      WITH1 = classtop;
      WITH1->mode = 5;
      tilstp = rhs[point].parserp;
      if (tilstp == NULL) {
	fprintf(blst, " THE STARTSYMBOL CANNOT PRODUCE A STRING CONTAINING ");
	fprintf(blst, "%c ", lf());
	r1 = 1;
	nontwrit(WITH->leftside, &r1);
	fprintf(blst, "%c%c", lf(), lf());
	stop(3);
      }
      WITH1->UU.lookbp = tilstp;
      while (tilstp->UU.U1.inf != symb)
	tilstp = tilstp->derivp;
      tilstp = tilstp->nextp;
      remember(tilstp);
      WITH1->nextp = tilstp;
      oldp = classtop;
      allocp(&classtop, 5, "LOOKB     ");
      oldp->derivp = classtop;
      point = rhs[point].link;
    }
    oldp->derivp = NULL;
    if (fcqi == 1) {
      WITH->lookbackp = begintilst->nextp;
      freelist(begintilst);
    } else {
      md = 5;
      optimize(&tilstp, &md);
      oldp->derivp = classtop;
      WITH1 = classtop;

      WITH1->derivp = NULL;
      WITH1->nextp = tilstp;
      WITH1->UU.lookbp = NULL;
      WITH1->mode = 5;
      antaltilst++;
      if (antaltilst > const10)
	consterror("LOOKB     ", "CONST10   ", const10);
      tilstand[antaltilst].oldstart = begintilst;
      WITH->lookbackp = begintilst;
    }

    /* lookBackEntry[symb]:=lookbackp; */

    while (prod[prodnr + 1].leftside == symb) {
      prodnr++;
      prod[prodnr].lookbackp = WITH->lookbackp;
    }
    prodnr++;
  }
  lbend = antaltilst;
  freeptr = NULL;

  if (options[14]) {
    skrivparser(gemp);
    /*
      writeln(blst,'nontL=',nontL:1,' nontR=',nontR:1);
      writeln(blst); writeln(blst,'LookBackEntry:');
      FOR i:=nontStart to nontSlut DO  writeln(blst,i:3,ord(lookBackEntry[i]));
      writeln(blst);*/
  }
  if (options[15])   /* PROD ARRAY*/
    dump5();
  if (options[16])   /* TILSTANDS ARRAY */
    dump1();
}


typedef struct item {
  /*packed*/
  short p, d;
  boolean nobot;
} item;

/*packed*/
typedef boolean laset[const2 + 1];
typedef enum {
  nyindgang, nyvej, udenom
} tilstcheck;


typedef struct _REC_lookant {
  /*packed*/
  short ant;
  konfigt *point;
} _REC_lookant;

typedef struct _REC_stack_ {
  /*packed*/
  short symb;
  short pnr;
  modetype token;
} _REC_stack_;

typedef struct _REC_done {
  /* CONST16 > MAX NUMBER OF PRODUCTIONS */
  /*packed*/
  long dotno;
  boolean mrk;
  short lnk;   /* INTERNAL Done-LINK */
  konfigt *hidep;
} _REC_done;

typedef struct _REC_ll {
  /*packed*/
  boolean mrk, lamrk;
  short lnk;
  konfigt *hidep;
} _REC_ll;

typedef struct _REC_tm {
  /*packed*/
  konfigt *s;
  short lnk;
} _REC_tm;

typedef struct _REC_done_ {
  /* CONST16 > MAX NO OF PROD */
  /*packed*/
  konfigt *rf;
  item ita, itb;
  boolean mrk;
  short lnk;   /* INTERNAL DONE-link */
} _REC_done_;

/* Local variables for adequad: */
struct LOC_adequad {
  item it1, it2;

  /* used by function entertm   */
  konfigt *tm[const10 + 1];
  long tmtop;

  long prodant, termant, lalaengde;
  boolean lrok, headwrite;
  konfigt *helpp, *lastok;
  _REC_lookant lookant[const14];
  _REC_stack_ stack[const2];
  laset la1;
  long la[const2 + 1];
  long pr1, pr2;   /*prod.no. of conflicting productions.*/
} ;

/* used in testconflicts and lrcond   */


/****************************************************************/
/*                                                                */
/*                   SMALL PROCEDURES                             */
/*                                                                */
/******************************************************************/

Local long symbmax(struct LOC_adequad *LINK)
{
  if (options[58])
    return nontslut;
  else
    return (nontstart - 1);
}

Local boolean itemeq(item it1, item it2, struct LOC_adequad *LINK)
{
  return (it1.p == it2.p && it1.d == it2.d && it1.nobot == it2.nobot);
}

Local void cr(long n, struct LOC_adequad *LINK)
{
  putc('\n', blst);
  for (; n >= 1; n--)
    putc(' ', blst);
}

Local void empty_(boolean *m, struct LOC_adequad *LINK)
{
  long i, FORLIM;

  FORLIM = symbmax(LINK);
  for (i = 0; i <= FORLIM; i++)
    m[i] = false;
}

Local void inter(boolean *m, boolean *n, struct LOC_adequad *LINK)
{
  long i, FORLIM;

  FORLIM = symbmax(LINK);
  for (i = 0; i <= FORLIM; i++)
    m[i] = (m[i] && n[i]);
}

Local void union_(boolean *m, boolean *n, struct LOC_adequad *LINK)
{
  long i, FORLIM;

  FORLIM = symbmax(LINK);
  for (i = 0; i <= FORLIM; i++)
    m[i] = (m[i] || n[i]);
}

Local boolean isempty(boolean *m, struct LOC_adequad *LINK)
{
  boolean b;
  long i, FORLIM;

  b = false;
  FORLIM = symbmax(LINK);
  for (i = 0; i <= FORLIM; i++)
    b = (b || m[i]);
  return (!b);
}


Local boolean terminal_(long symb, struct LOC_adequad *LINK)
{
  return (symb <= termg || options[58]);
}


Local boolean emptys(long pn, long l, struct LOC_adequad *LINK)
{
  long i;
  boolean emptyboo;
  long FORLIM;

  if (prod[pn].laengde + 1 != l) {
    emptyboo = true;   /* OPTIMIST */
    FORLIM = prod[pn].laengde;
    for (i = l; i <= FORLIM; i++) {
      emptyboo = (emptyboo && emptya[rhs[prod[pn].start + i].symbol_]);
      if (!emptyboo)
	goto _L33;
    }
  } else
    emptyboo = true;
_L33:
  return emptyboo;
}  /* EMPTYS */

Local konfigt *gotox(konfigt *r, long symb, struct LOC_adequad *LINK)
{
  while (r->UU.U1.inf != symb)
    r = r->derivp;
  return (r->nextp);
}  /* GOTOX */

Local konfigt *gotos(konfigt *r, long p, long l, struct LOC_adequad *LINK)
{
  long i, sy;

  for (i = 1; i <= l; i++) {
    sy = rhs[prod[p].start + i].symbol_;
    while (r->UU.U1.inf != sy)
      r = r->derivp;
    r = r->nextp;
  }
  return r;
}

Local void pred(long p, long l, konfigt *t, long *rl, konfigt **s,
		struct LOC_adequad *LINK)
{
  if (*rl == -1) {  /* INITIAL CALL */
    *rl = prod[p].start;
    if (prod[p].laengde > 0)
      (*rl)++;
  }
  while (*rl != rhsnil) {
    *s = rhs[*rl].parserp;
    *rl = rhs[*rl].link;
    if (gotos(*s, p, l - 1, LINK) == t)
      goto _L10;
  }
  *s = NULL;
_L10: ;
}  /* PRED */


/*****************************************************/
/*                                                   */
/*           AUXILLARY PROCEDURES                    */
/*                                                   */
/*****************************************************/

Local void optimalisering(tilstcheck x, struct LOC_adequad *LINK)
{
  long seq;

  switch (x) {

  case nyindgang:
    seq = LINK->lastok->seq;
    *LINK->lastok = *LINK->helpp;
    LINK->lastok->seq = seq;
    break;

  case nyvej:
    LINK->lastok->derivp = LINK->helpp;
    LINK->lastok = LINK->helpp;
    break;

  case udenom:
    LINK->lastok->derivp = LINK->helpp;
    break;
  }
}



Local void lalrtext(long x, struct LOC_adequad *LINK)
{
  long i;

  fprintf(blst, "\f");
  for (i = 1; i <= 71; i++)
    putc('*', blst);
  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, "         ");
  switch (x) {

  case 1:
    printf("******** The grammar is LALR(1)\n");
    fprintf(blst, "The grammar is LALR(1) \n\n");
    for (i = 1; i <= 71; i++)
      putc('*', blst);
    putc('\n', blst);
    break;

  case 2:
    printf("!!!!!!!! The grammar is NOT LALR(1)!!! \n\n");
    printf("A parser for the grammar has however been constructed.\n");
    printf("THIS PARSER MAY NOT WORK PROPERLY!!!\n");
    printf("When a parse conflict occurs, \n");
    printf("the parser selects one of the possibilities.\n");
    printf("If the parse conflict is due to an ambiguity,\n");
    printf("one of the possible right parses is produced.\n");
    printf("If the grammar is unambiguous and NON LALR(1),\n");
    printf("a parse error may appear on a syntactic correct string!\n\n");

    fprintf(blst, "The grammar is NOT LALR(1) \n\n");
    for (i = 1; i <= 71; i++)
      putc('*', blst);
    fprintf(blst,
	    "\n\nA parser for the grammar has however been constructed.\n");
    fprintf(blst, "THIS PARSER MAY NOT WORK PROPERLY!!!\n");
    fprintf(blst, "When a parse conflict occurs, \n");
    fprintf(blst, "the parser selects one of the possibilities.\n");
    fprintf(blst, "If the parse conflict is due to an ambiguity,\n");
    fprintf(blst, "one of the possible right parses is produced.\n");
    fprintf(blst, "If the grammar is unambiguous and NON LALR(1),\n");
    fprintf(blst,
	    "a parse error may appear on a syntactic correct string!\n\n\n");

    break;
  }
}


Local void adeqwrite(long x, struct LOC_adequad *LINK)
{
  switch (x) {

  case 5:
    fprintf(blst, "\f");
    fprintf(blst, " *********************");
    fprintf(blst, "  A list of LR(1) conflicts  ");
    fprintf(blst, "*********************");
    cr(0, LINK);
    cr(0, LINK);
    break;

  /*OVERSKRIFT TIL LOOKAHEAD-MAENGDERNE LALR1 */
  case 6:
    /*UDSKRIFT AF AFSLUTNING PAA LOOKAHEAD-MAENGDERNE LALR1 */
    cr(0, LINK);
    cr(0, LINK);
    fprintf(blst, " *********************");
    fprintf(blst, " End of LR(1) conflicts  ");
    fprintf(blst, "*************************");
    cr(0, LINK);
    cr(0, LINK);
    break;

  case 3:
  case 4:
    fprintf(blst, " adequad udskrift er fjernet \n");
    break;
  }
}

Local konfigt *findreduce(long pnr, struct LOC_adequad *LINK)
{
  pointer2 p1, p2;
  konfigt *pt;
  prodtype *WITH;

  WITH = &prod[pnr];
  if (WITH->laengde == 0)
    return (WITH->lookbackp);
  else {
    p1 = WITH->start;
    while (rhs[p1].parserp->derivp != NULL) {
      p2 = p1;
      p1 = rhs[p1].link;
      if (p1 != rhsnil)
	continue;
      allocp(&pt, 1, "FINDREDUCE");
      pt->mode = 3;
      pt->UU.U1.inf = WITH->laengde - 1;
      pt->UU.U1.prodnr = pnr;
      pt->nextp = WITH->lookbackp;
      pt->derivp = NULL;   /*TRUNC*/
      antaltilst++;
      updatemax(10, antaltilst);
      if (antaltilst > const10)
	consterror("FINDREDUCE", "CONST10   ", const10);
      tilstand[antaltilst].oldstart = pt;
      newelm(&top, "FINDREDUCE");
      p1 = top;
      rhs[p1].parserp = pt;
      rhs[p1].link = rhsnil;
      rhs[p2].link = p1;
    }
    return (rhs[p1].parserp);
  }
}  /* FINDREDUCE */


Local void initdot(struct LOC_adequad *LINK)
{
  long i;
  konfigt *p;
  long FORLIM;

  FORLIM = antaltilst;
  for (i = 0; i <= FORLIM; i++) {
    p = tilstand[i].oldstart;
    while (p != NULL) {
      p->dot = p->mode;
      p = p->derivp;
    }
  }
}  /* INITDOT */

/* Local variables for lookahead: */
struct LOC_lookahead {
  struct LOC_adequad *LINK;
  boolean *look;
  long reclevel;   /* MISCELANEOUS */

  _REC_done done[const16 + 1];

  long donetop;   /* MARKS UN-USED PART OF Done */
} ;

/* POINTS TO LAST ITEM USED */



Local boolean enterdone(konfigt *r, long symb, struct LOC_lookahead *LINK)
{
  /* IF r IN done[symb] OR r=nil THEN enterdone=false */
  /* IF r NOTIN done[symb]       THEN enterdone=true  */
  /*                  AND r is inserted in done[symb] */
  boolean Result;
  long i, oldi;   /* LOOP-POINTER TO Done */
  _REC_done *WITH;

  Result = false;
  i = symb;
  while (LINK->done[i].mrk) {
    WITH = &LINK->done[i];
    if (WITH->hidep == r)
      goto _L2;
    oldi = i;
    i = WITH->lnk;
  }
  if (i == 0) {   /*not found*/
    LINK->donetop++;
    updatemax(16, LINK->donetop);
    if (LINK->donetop > const16)
      consterror("EnterDone ", "const16   ", const16);
    LINK->done[oldi].lnk = LINK->donetop;
    i = LINK->donetop;
  }
  WITH = &LINK->done[i];
  WITH->hidep = r;
  WITH->mrk = true;
  WITH->lnk = 0;
  Result = true;
_L2:
  return Result;
}  /* EnterDone */

Local boolean entertm(konfigt *r, struct LOC_lookahead *LINK)
{
  /* IF r IN    tm THEN entertm=false */
  /* IF r NOTIN tm THEN entertm=true  */
  /*          AND r is inserted in tm */
  long i;

  LINK->LINK->tm[0] = NULL;
  i = 0;
  while (LINK->LINK->tm[i] != r && i < LINK->LINK->tmtop)
    i++;
  if (LINK->LINK->tm[i] == r)
    return false;
  else {
    LINK->LINK->tmtop++;
    LINK->LINK->tm[LINK->LINK->tmtop] = r;
    return true;
  }
}  /* entertm*/

Local void trans(konfigt *r, struct LOC_lookahead *LINK)
{
  if (!entertm(r, LINK))
    return;
  while (r != NULL) {
    if (r->dot != 0) {
      /* OLM: 16.8.95; the following stmt used to be
       *  if terminal(...) then ... else if emptya[...] then ...;
       *  This does NOT work with option 59, since terminal(x)
       *  returns true for terminal as well as nonterminals with
       *  this option. The reason is that 59 includes nonterminals
       *  in the lookahead sets.
       */
      if (terminal_(r->UU.U1.inf, LINK->LINK))
	LINK->look[r->UU.U1.inf] = true;
      if (emptya[r->UU.U1.inf])
	trans(r->nextp, LINK);
    }
    r = r->derivp;
  }
}  /* TRANS */


Local void lalr1(konfigt *t, long pn, long dn, struct LOC_lookahead *LINK)
{
  long lhs, rlink;
  konfigt *s, *r;

  if (options[38])
    fprintf(blst, "%12ld%12ld%12ld%12ld\n", (long)s, pn, dn, LINK->reclevel);
  LINK->reclevel++;
  lhs = prod[pn].leftside;
  /* FOR s IN pred(T,...)        */
  rlink = -1;
  pred(pn, dn, t, &rlink, &s, LINK->LINK);
  while (s != NULL) {
    if (enterdone(s, lhs, LINK)) {
      trans(gotox(s, lhs, LINK->LINK), LINK);
      r = s;
      while (r != NULL) {
	if (r->dot != 0 && r->UU.U1.inf == lhs) {
	  if (emptys(r->UU.U1.prodnr, r->dot + 1, LINK->LINK))
	    lalr1(s, r->UU.U1.prodnr, r->dot, LINK);
	}

	r = r->derivp;
      }
    }
    pred(pn, dn, t, &rlink, &s, LINK->LINK);
  }
  LINK->reclevel--;
}  /* LALR1 */

/*****************************************************************/
/*                                                                */
/*                    NEW LOOKAHED                                */
/*                                                                */
/******************************************************************/



Local void lookahead(konfigt *pointp, long prodno, long dotno, boolean *look_,
		     struct LOC_adequad *LINK)
{
  struct LOC_lookahead V;
  long j, FORLIM;

  V.LINK = LINK;
  V.look = look_;
  if (options[38]) {
    fprintf(blst, "     ");
    writech('-', 60);
    fprintf(blst, "%c%c     STATE    PRODNO     DOTNO     LEVEL%c",
	    lf(), lf(), lf());
  }
  V.donetop = nontslut;
  LINK->tmtop = 0;
  FORLIM = V.donetop;
  for (j = 0; j <= FORLIM; j++)
    V.done[j].mrk = false;
  empty_(V.look, LINK);
  V.reclevel = 0;

  if (dotno == 0)
    lalr1(pointp, prodno, prod[prodno].laengde + 1, &V);
  else
    lalr1(pointp, prodno, dotno, &V);

  LINK->lalaengde = 0;
  FORLIM = symbmax(LINK);
  for (j = 0; j <= FORLIM; j++) {
    if (V.look[j]) {
      LINK->la[LINK->lalaengde] = j;
      updatemax(8, LINK->lalaengde);
      if (LINK->lalaengde < const8)
	LINK->lalaengde++;
      else
	consterror("LOOKAHEAD ", "CONST8    ", const8);
    }
  }
}  /* LOOKAHEAD */

/* Local variables for lalrlookahead: */
struct LOC_lalrlookahead {
  struct LOC_adequad *LINK;
  long l, info;
  _REC_ll ll[const16 + 1];
  long lltop;

  _REC_tm tm[const16];
  long tmtop;
} ;

/* Local variables for lalr1_: */
struct LOC_lalr1_ {
  struct LOC_lalrlookahead *LINK;
  konfigt *lalrpt;
} ;

Local void trans_(konfigt *t, long stacktop, struct LOC_lalr1_ *LINK)
{
  long inx, lhs, i;
  konfigt *r;

  for (i = LINK->LINK->tmtop - 1; i >= stacktop; i--) {
    if (LINK->LINK->tm[i].s == t && LINK->LINK->tm[i].lnk == stacktop)
      goto _L10;
  }
  inx = stacktop;
  while (inx > 0) {
    if (LINK->LINK->tm[inx - 1].s == t)
      goto _L10;
    inx = LINK->LINK->tm[inx - 1].lnk;
  }
  /* push t */
  LINK->LINK->tmtop++;
  if (LINK->LINK->tmtop > const16)
    consterror("trans     ", "const16   ", const16);
  updatemax(16, LINK->LINK->tmtop);
  LINK->LINK->tm[LINK->LINK->tmtop - 1].s = t;
  LINK->LINK->tm[LINK->LINK->tmtop - 1].lnk = stacktop;
  stacktop = LINK->LINK->tmtop;
  /* parse */
  while (t != NULL) {
    if (t->mode != 0)
      LINK->LINK->ll[t->UU.U1.inf].lamrk = true;
    else {  /* reduce */
      inx = stacktop;
      i = prod[t->UU.U1.prodnr].laengde;
      while (inx > 0 && i > 0) {
	inx = LINK->LINK->tm[inx - 1].lnk;
	i--;
      }
      if (inx == 0) {
	allocp(&r, 1, "trans     ");
	r->UU.U1.prodnr = t->UU.U1.prodnr;
	r->mode = i;
	r->derivp = LINK->lalrpt;
	/* lalrpt TRUNC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      } else {
	r = LINK->LINK->tm[inx - 1].s;
	lhs = prod[t->UU.U1.prodnr].leftside;
	while (r->UU.U1.inf != lhs)
	  r = r->derivp;
	trans_(r->nextp, inx, LINK);
      }
    }
    t = t->derivp;
  }
_L10: ;
}  /* trans */


Local void lalr1_(konfigt *statep, long prodno, long dotno,
		  struct LOC_lalrlookahead *LINK)
{
  struct LOC_lalr1_ V;
  long leftinf, hinx;
  pointer2 rightp, prodp, syinx;
  konfigt *runp, *transp, *loopp;
  prodtype *WITH;
  _REC_ll *WITH1;
  konfigt *WITH2;

  V.LINK = LINK;
  WITH = &prod[prodno];
  leftinf = WITH->leftside;
  rightp = WITH->start;
  /*RHS NOT EMPTY TRUNC !!!!!!!!!!!!!!!!*/
  prodp = rightp;
  while (prodp != rhsnil) {
    runp = rhs[prodp].parserp;
    loopp = runp;
    syinx = rightp;
    for (hinx = 1; hinx <= dotno; hinx++) {
      LINK->info = rhs[syinx].symbol_;
      while (loopp->UU.U1.inf != LINK->info)
	loopp = loopp->derivp;
      loopp = loopp->nextp;
      allocate(&syinx);
    }
    if (loopp == statep) {
      if (LINK->ll[leftinf].mrk) {
	hinx = leftinf;
	do {
	  WITH1 = &LINK->ll[hinx];
	  if (runp == WITH1->hidep)
	    goto _L2;
	  LINK->l = hinx;
	  hinx = WITH1->lnk;
	} while (hinx != 0);
	LINK->lltop++;
	if (LINK->lltop > const16)
	  consterror("LALRLOOKAH", "const16   ", const16);
	updatemax(16, LINK->lltop);
	hinx = LINK->lltop;
	LINK->ll[LINK->l].lnk = hinx;
      } else
	hinx = leftinf;
      WITH1 = &LINK->ll[hinx];
      WITH1->mrk = true;
      WITH1->hidep = runp;
      WITH1->lnk = 0;
      transp = runp;
      while (transp->UU.U1.inf != leftinf)
	transp = transp->derivp;
      transp = transp->nextp;
      LINK->tmtop = 0;
      V.lalrpt = NULL;
      trans_(transp, 0, &V);
      loopp = V.lalrpt;
      while (loopp != NULL) {
	WITH2 = loopp;
	lalr1_(runp, WITH2->UU.U1.prodnr, WITH2->mode, LINK);
	loopp = WITH2->derivp;
      }
      if (V.lalrpt != NULL)
	freelist(V.lalrpt);
    }
_L2:   /*TRY NEXT */
    prodp = rhs[prodp].link;
  }
}  /*LALR1*/


/****************************************************************/
/*                                                                */
/*                   OLD LOOKAHEAD                                */
/*                                                                */
/******************************************************************/


Local void lalrlookahead(konfigt *pointp, long prodno,
			 struct LOC_adequad *LINK)
{
  struct LOC_lalrlookahead V;
  long j, FORLIM;
  _REC_ll *WITH;


  V.LINK = LINK;
  V.lltop = const2;
  for (j = 0; j <= const2; j++) {
    WITH = &V.ll[j];
    WITH->mrk = false;
    WITH->lamrk = false;
  }
  lalr1_(pointp, prodno, prod[prodno].laengde, &V);
  LINK->lalaengde = 0;
  FORLIM = symbmax(LINK);
  for (j = 0; j <= FORLIM; j++) {
    if (V.ll[j].lamrk) {
      LINK->la[LINK->lalaengde] = j;
      updatemax(8, LINK->lalaengde);
      if (LINK->lalaengde < const8)
	LINK->lalaengde++;
      else
	consterror("LalrLookah", "const8    ", const8);
    }
  }
}  /* LALRLOOKAHEAD */

/* Local variables for lrcond: */
struct LOC_lrcond {
  struct LOC_adequad *LINK;
  _REC_done_ done[const16 + 1];
  long donetop;
  laset global, locallr, locallalr, la1, la2;
  konfigt *tm[const10 + 1];
  long tmtop;
} ;

/* Local variables for dotrans: */
struct LOC_dotrans {
  struct LOC_lrcond *LINK;
  boolean *transla;
} ;

Local boolean entertm_(konfigt *r, struct LOC_dotrans *LINK)
{
  long i;   /* LOOP-POINTER TO TM */

  /* RETURNS FALSE IN  R  ALREADY REGISTERED (OR NIL), */
  /* OTHERWISE TRUE, PLUS THAT  R  IS INSERTED  */

  LINK->LINK->tm[0] = NULL;
  i = 0;
  while (LINK->LINK->tm[i] != r && i < LINK->LINK->tmtop)
    i++;
  if (LINK->LINK->tm[i] == r)
    return false;
  else {
    LINK->LINK->tmtop++;
    LINK->LINK->tm[LINK->LINK->tmtop] = r;
    return true;
  }
}  /* ENTERTM */

Local void trans__(konfigt *r, struct LOC_dotrans *LINK)
{
  /*       */
  if (!entertm_(r, LINK))
    return;
  while (r != NULL) {
    if (r->dot != 0) {
      if (terminal_(r->UU.U1.inf, LINK->LINK->LINK))
	LINK->transla[r->UU.U1.inf] = true;
      else if (emptya[r->UU.U1.inf])
	trans__(r->nextp, LINK);
    }
    r = r->derivp;
  }  /* WHILE */
}  /* TRANS */


Local void dotrans(konfigt *r, boolean *transla_, struct LOC_lrcond *LINK)
{
  struct LOC_dotrans V;

  V.LINK = LINK;
  V.transla = transla_;
  empty_(V.transla, LINK->LINK);
  LINK->tmtop = 0;
  trans__(r, &V);
}  /* DOTRANS */

Local void sort(item *it1, item *it2, boolean *swap, struct LOC_lrcond *LINK)
{
  item it;

  if (it1->d >= it2->d && (it1->d != it2->d || it2->p >= it1->p) &&
      (it1->p != it2->p || it1->d != it2->d || it2->nobot >= it1->nobot))
	/* Swap */
	  return;
  it = *it1;
  *it1 = *it2;
  *it2 = it;
  *swap = !*swap;
}

/* Local variables for enterdone_: */
struct LOC_enterdone_ {
  struct LOC_lrcond *LINK;
  boolean swap;
} ;

Local boolean enterdone_(konfigt *r, item it1, item it2, boolean swap_,
			 struct LOC_lrcond *LINK)
{
  /* RETURNS FALSE IF  (IT1,IT2,R) in Done or R=NIL */
  /* OTHERWISE TRUE, and inserts (IT1,IT2,R) in Done*/
  /* DONETOP MUST BE INITIALIZED TO   ANTALPROD     */
  struct LOC_enterdone_ V;
  boolean Result;
  long i, oldi;   /* LOOP-POINTER TO DONE */
  _REC_done_ *WITH;

  V.LINK = LINK;
  V.swap = swap_;
/* p2c: exbobs.p, line 3952:
 * Note: Taking & of possibly promoted param swap [324] */
  sort(&it1, &it2, &V.swap, LINK);
  Result = false;
  if (r != NULL && it1.p > 0) {
    i = it1.p;
    while (LINK->done[i].mrk) {   /*done[0] is never used; done[i].mrk=false*/
      WITH = &LINK->done[i];
      if ((WITH->rf == r) & itemeq(WITH->ita, it1, LINK->LINK) &
	  itemeq(WITH->itb, it2, LINK->LINK)) {
	Result = false;
	goto _L10;
      }
      oldi = i;
      i = WITH->lnk;
    }
    if (i == 0) {   /*not found*/
      LINK->donetop++;
      updatemax(16, LINK->donetop);
      if (LINK->donetop > const16)
	consterror("lr-cond   ", "const16   ", const16);
      LINK->done[oldi].lnk = LINK->donetop;
      i = LINK->donetop;
    }
    WITH = &LINK->done[i];
    WITH->rf = r;
    WITH->ita = it1;
    WITH->itb = it2;
    WITH->mrk = true;
    WITH->lnk = 0;
    Result = true;
  }
_L10:
  return Result;
}  /* ENTERDONE */

Local void pritem(item it, struct LOC_lrcond *LINK)
{
  if (it.nobot)
    fprintf(blst, "    ");
  else
    fprintf(blst, " // ");
  writem(it.p, it.d);
  cr(16, LINK->LINK);
}

/* Local variables for cond: */
struct LOC_cond {
  struct LOC_lrcond *LINK;
  item ir, jr;
  laset lr;
  long level;
  boolean conflict, swap;
  long inf;
  konfigt *s;
  boolean contrib, loopp, moreconflict;
  item is, js;
} ;

Local boolean bottom(struct LOC_cond *LINK)
{
  return (!(LINK->is.nobot || LINK->js.nobot));
}

Local void trace(struct LOC_cond *LINK)
{
  long a1, a2, a3;

  if (options[37])
    fprintf(blst, "%12d%12d%s%12d%12d%s%12ld%12d\n",
	    LINK->is.p, LINK->is.d, LINK->is.nobot ? " TRUE" : "FALSE",
	    LINK->js.p, LINK->js.d, LINK->js.nobot ? " TRUE" : "FALSE",
	    (long)LINK->s, rhs[prod[LINK->js.p].start + LINK->js.d].symbol_);
  LINK->contrib = false;
  LINK->moreconflict = false;
  /* find possible conflicts*/
  if (!LINK->jr.nobot)
    return;
  a1 = LINK->js.p;
  a2 = prod[a1].start;
  a3 = rhs[a2 + LINK->js.d].symbol_;
  if (options[37])   /*rhs[prod[Js.P].start+Js.D].symbol*/
    fprintf(blst, "%12ld%12ld%12ld\n", a1, a2, a3);
  /* LocalLALR:= Global INTER (FIRST(..)- e ) */
  dotrans(gotox(LINK->s, a3, LINK->LINK->LINK), LINK->LINK->locallalr,
	  LINK->LINK);
  inter(LINK->LINK->locallalr, LINK->LINK->global, LINK->LINK->LINK);

  /* LocalLR:=LocalLALR INTER LALR1(Is,S) */
  if (LINK->ir.nobot)   /* result in LA1 */
    lookahead(LINK->s, LINK->is.p, LINK->is.d, LINK->LINK->la1,
	      LINK->LINK->LINK);
  else
    empty_(LINK->LINK->la1, LINK->LINK->LINK);
  memcpy(LINK->LINK->locallr, LINK->LINK->la1, sizeof(laset));
  inter(LINK->LINK->locallr, LINK->LINK->locallalr, LINK->LINK->LINK);

  /* LR:=LR UNION LocalLR */
  union_(LINK->lr, LINK->LINK->locallr, LINK->LINK->LINK);

  LINK->contrib = !isempty(LINK->LINK->locallalr, LINK->LINK->LINK);
  LINK->conflict = (LINK->conflict || LINK->contrib);

  if (LINK->conflict)
    return;
  lookahead(LINK->s, LINK->js.p, LINK->js.d, LINK->LINK->la2,
	    LINK->LINK->LINK);
  inter(LINK->LINK->la1, LINK->LINK->la2, LINK->LINK->LINK);
  LINK->moreconflict = !isempty(LINK->LINK->la1, LINK->LINK->LINK);
  /* MoreConflict= (LALR1(Is,S) INTER LALR1(Js,S)) <> EMPTY */
}  /*Trace*/

Local void print(struct LOC_cond *LINK)
{
  long i, FORLIM;

  fprintf(blst, "(%4ld)---------------------------------------------",
	  LINK->level);
  cr(16, LINK->LINK->LINK);

  if (!LINK->swap)
    pritem(LINK->is, LINK->LINK);
  pritem(LINK->js, LINK->LINK);
  if (LINK->contrib) {
    fprintf(blst, "%20c", ' ');
    fprintf(blst, "which generates: ");
    cr(41, LINK->LINK->LINK);
    FORLIM = termg;
    for (i = 0; i <= FORLIM; i++) {
      if (LINK->LINK->locallalr[i]) {
	outalf20(internrep[LINK->inf + 1], &dummy);
	if (LINK->lr[i])
	  putc(' ', blst);
	else
	  fprintf(blst, " ! no LR-conflict ");
      }
    }
  }
  cr(16, LINK->LINK->LINK);
  if (LINK->swap)
    pritem(LINK->is, LINK->LINK);
  if (bottom(LINK)) {
    fprintf(blst, "(***  path terminated by bottom  ***)");
    cr(16, LINK->LINK->LINK);
    return;
  }

  if (LINK->loopp) {
    fprintf(blst, "(***  path terminated by loop    ***)");
    cr(16, LINK->LINK->LINK);
  }
}  /*Print*/

Local void cond(item ir_, item jr_, konfigt *t, boolean *lr_, long level_,
		boolean conflict_, boolean swap_, struct LOC_lrcond *LINK)
{
  struct LOC_cond V;
  long lhs, rlink;
  konfigt *r;


  V.LINK = LINK;
  V.ir = ir_;
  V.jr = jr_;
  memcpy(V.lr, lr_, sizeof(laset));
  V.level = level_;
  V.conflict = conflict_;
  V.swap = swap_;
/* p2c: exbobs.p, line 4056:
 * Note: Taking & of possibly promoted param swap [324] */
  sort(&V.ir, &V.jr, &V.swap, LINK);
  V.is = V.ir;
  V.is.d += 1 - V.jr.d;
  lhs = prod[V.jr.p].leftside;
  if (options[37])
    fprintf(blst, " COND:%12d%12d%12d%12d%12ld\n",
	    V.ir.p, V.ir.d, V.jr.p, V.jr.d, (long)t);
  rlink = -1;
  pred(V.jr.p, V.jr.d, t, &rlink, &V.s, LINK->LINK);
  while (V.s != NULL) {
    r = V.s;
    while (r != NULL) {
      if (r->dot != 0 && r->UU.U1.inf == lhs) {
	V.js.p = r->UU.U1.prodnr;
	V.js.d = r->dot;
	V.js.nobot = V.jr.nobot & emptys(V.js.p, V.js.d + 1, LINK->LINK);
	if (options[37])
	  fprintf(blst, " cond-inner%12d%12d%s%12d%12d%s%12ld\n",
		  V.is.p, V.is.d, V.is.nobot ? " TRUE" : "FALSE", V.js.p,
		  V.js.d, V.js.nobot ? " TRUE" : "FALSE", (long)V.s);
	V.loopp = !enterdone_(V.s, V.is, V.js, V.swap, LINK);
	trace(&V);
	if (V.conflict | (!bottom(&V) && V.moreconflict)) {
	  print(&V);
	  if (!(V.loopp | bottom(&V)))
	    cond(V.is, V.js, V.s, V.lr, V.level + 1, V.conflict, V.swap, LINK);
	}
      }
      r = r->derivp;
    }
    pred(V.jr.p, V.jr.d, t, &rlink, &V.s, LINK->LINK);
  }
}  /* COND */


/*************************************************************/
/*                                                                */
/*                       LR-COND                                  */
/*                                                                */
/******************************************************************/


Local boolean lrcond(item it1, item it2, konfigt *t, boolean *c1, boolean *c2,
		     struct LOC_adequad *LINK)
{
  /* STATE  */
  struct LOC_lrcond V;
  boolean check;
  laset lr;
  long i;

  V.LINK = LINK;
  check = true;
  V.donetop = antalprod;
  for (i = 0; i <= const16; i++)
    V.done[i].mrk = false;
  empty_(lr, LINK);
  memcpy(V.global, c1, sizeof(laset));
  inter(V.global, c2, LINK);
  cond(it1, it2, t, lr, 0, false, false, &V);
  return check;
}  /* LRCOND */

/* Local variables for testconflicts: */
struct LOC_testconflicts {
  struct LOC_adequad *LINK;
  konfigt *confstate;
  laset c1, c2;
} ;

/**/
Local void mark_(boolean *c, long index, struct LOC_testconflicts *LINK)
{
  long i;
  konfigt *p;
  long FORLIM;

  empty_(c, LINK->LINK);
  p = LINK->LINK->lookant[index - 1].point;
  FORLIM = LINK->LINK->lookant[index - 1].ant;
  for (i = 1; i <= FORLIM; i++) {
    c[p->UU.U1.inf] = true;
    p = p->derivp;
  }
}  /* MARK */

/**/
Local boolean check(struct LOC_testconflicts *LINK)
{
  long i;
  boolean b;
  long FORLIM;

  b = false;
  FORLIM = nontstart;
  for (i = 0; i < FORLIM; i++)   /* CHECK TERMINALS ONLY */
    b = (b || LINK->c1[i] && LINK->c2[i]);
  if (!(b && LINK->LINK->headwrite))
    return b;
  LINK->LINK->headwrite = false;
  LINK->LINK->lrok = false;
  adeqwrite(5, LINK->LINK);
  return b;
}  /* CHECK */

/**/
Local void ShiftReduceConflict(long prodindex, struct LOC_testconflicts *LINK)
{
  long i;
  symbol inf;
  konfigt *p;
  long FORLIM;

  cr(2, LINK->LINK);
  for (i = 1; i <= 61; i++)
    putc('-', blst);
  cr(2, LINK->LINK);
  fprintf(blst, "LALR(1) conflict of type SHIFT/REDUCE");
  cr(0, LINK->LINK);
  cr(4, LINK->LINK);
  fprintf(blst, "Conflicting item(s):");
  FORLIM = LINK->LINK->termant;
  for (i = 0; i < FORLIM; i++) {
    inf = LINK->LINK->stack[i].symb;
    if (LINK->c1[inf] && LINK->c2[inf]) {   /* CONFLICT ON INF */
      cr(6, LINK->LINK);
      writem(LINK->LINK->stack[i].pnr, LINK->LINK->stack[i].token);
      LINK->LINK->it1.p = LINK->LINK->stack[i].pnr;
      LINK->LINK->it1.d = LINK->LINK->stack[i].token;
      LINK->LINK->it1.nobot = false;   /*trunc*/
    }
  }
  cr(4, LINK->LINK);
  fprintf(blst, "In conflict with production:");
  cr(6, LINK->LINK);
  p = LINK->LINK->lookant[prodindex - 1].point;
  fprintf(blst, "%3d: ", p->UU.U1.prodnr);
  writem(p->UU.U1.prodnr, 0);
  LINK->LINK->it2.p = p->UU.U1.prodnr;
  LINK->LINK->it2.d = prod[LINK->LINK->it2.p].laengde + 1;
  LINK->LINK->it2.nobot = true;
  cr(6, LINK->LINK);
  fprintf(blst, "Lookaheadset:");
  cr(6, LINK->LINK);
  FORLIM = termg;
  for (i = 0; i <= FORLIM; i++) {
    if (LINK->c2[i]) {
      outalf20(internrep[i + 1], &dummy);
      putc(' ', blst);
    }
  }
  cr(4, LINK->LINK);
  fprintf(blst, "Conflict on symbol(s):");
  cr(6, LINK->LINK);
  FORLIM = termg;
  for (i = 0; i <= FORLIM; i++) {
    if (LINK->c1[i] && LINK->c2[i]) {   /* CONFLICT */
      outalf20(internrep[i + 1], &dummy);
      putc(' ', blst);
    }
  }
  cr(4, LINK->LINK);
  fprintf(blst, "Other shift item(s) in that state:");
  FORLIM = LINK->LINK->termant;
  for (i = 0; i < FORLIM; i++) {
    inf = LINK->LINK->stack[i].symb;
    if (!(LINK->c1[inf] && LINK->c2[inf])) {
      cr(6, LINK->LINK);
      writem(LINK->LINK->stack[i].pnr, LINK->LINK->stack[i].token);
    }
  }
  cr(0, LINK->LINK);
  if (!options[34])
    return;
  fprintf(blst, "Backwards trace:");
  cr(4, LINK->LINK);
  lrcond(LINK->LINK->it1, LINK->LINK->it2, LINK->confstate, LINK->c1,
	 LINK->c2, LINK->LINK);
}

/**/
Local void ReduceReduceConflict(long index1, long index2,
				struct LOC_testconflicts *LINK)
{
  long i;
  konfigt *p;
  long FORLIM;

  LINK->LINK->pr1 = LINK->LINK->lookant[index1 - 1].point->UU.U1.prodnr;
  LINK->LINK->pr2 = LINK->LINK->lookant[index2 - 1].point->UU.U1.prodnr;
  cr(2, LINK->LINK);
  for (i = 1; i <= 61; i++)
    putc('-', blst);
  cr(2, LINK->LINK);
  fprintf(blst, "LALR(1) conflict of type: REDUCE/REDUCE");
  cr(4, LINK->LINK);
  fprintf(blst, "first conflicting production:");
  cr(6, LINK->LINK);
  p = LINK->LINK->lookant[index1 - 1].point;
  fprintf(blst, "%3ld: ", LINK->LINK->pr1);
  writem(p->UU.U1.prodnr, 0);
  cr(6, LINK->LINK);
  fprintf(blst, "Lookahead set:");
  cr(5, LINK->LINK);
  FORLIM = termg;
  for (i = 0; i <= FORLIM; i++) {
    if (LINK->c1[i]) {
      outalf20(internrep[i + 1], &dummy);
      putc(' ', blst);
    }
  }
  cr(4, LINK->LINK);
  fprintf(blst, "second conflicting production:");
  cr(5, LINK->LINK);
  p = LINK->LINK->lookant[index2 - 1].point;
  fprintf(blst, "%3ld: ", LINK->LINK->pr2);
  writem(p->UU.U1.prodnr, 0);
  cr(6, LINK->LINK);
  fprintf(blst, "lookahead set:");
  cr(5, LINK->LINK);
  FORLIM = termg;
  for (i = 0; i <= FORLIM; i++) {
    if (LINK->c2[i]) {
      outalf20(internrep[i + 1], &dummy);
      putc(' ', blst);
    }
  }
  cr(4, LINK->LINK);
  fprintf(blst, "Conflict on symbol(s)");
  cr(5, LINK->LINK);
  FORLIM = termg;
  for (i = 0; i <= FORLIM; i++) {
    if (LINK->c1[i] && LINK->c2[i])
      outalf20(internrep[i + 1], &dummy);
  }
  cr(4, LINK->LINK);

  if (!options[34])
    return;
  fprintf(blst, "Backwards trace:");
  cr(4, LINK->LINK);
  LINK->LINK->it1.p = LINK->LINK->pr1;
  LINK->LINK->it1.d = prod[LINK->LINK->it1.p].laengde + 1;
  LINK->LINK->it1.nobot = true;
  LINK->LINK->it2.p = LINK->LINK->pr2;
  LINK->LINK->it2.d = prod[LINK->LINK->it2.p].laengde + 1;
  LINK->LINK->it2.nobot = true;
  lrcond(LINK->LINK->it1, LINK->LINK->it2, LINK->confstate, LINK->c1,
	 LINK->c2, LINK->LINK);
}  /* REDUCE/REDUCE-CONFLICT */


Local void testconflicts(konfigt *confstate_, struct LOC_adequad *LINK)
{
  /**************************************************************/
  /* USING GLOBAL VARIABLES:                                    */
  /*  STACK: ARRAY CONTAINING SHIFT-INFORMATION                 */
  /*  LOOKANT: ARRAY CONTAINING REDUCE-INFORMATION              */
  /*  TERMANT: INTEGER (MAXIMUM ENTRY IN STACK)                 */
  /*  PRODANT: INTEGER (MAXIMUM ENTRY IN LOOKANT)               */
  /**************************************************************/
  struct LOC_testconflicts V;
  long i, j;
  boolean conflict;
  long FORLIM, FORLIM1;

  V.LINK = LINK;
  V.confstate = confstate_;
  empty_(V.c1, LINK);
  FORLIM = LINK->termant;
  for (i = 0; i < FORLIM; i++)
    V.c1[LINK->stack[i].symb] = true;
  FORLIM = LINK->prodant;
  for (i = 1; i <= FORLIM; i++) {
    mark_(V.c2, i, &V);
    /* IF C1 AND C2 ARE DISJOINT THERE IS NO SHIFT/REDUCE CONFLICT */
    conflict = check(&V);
    if (conflict)
      ShiftReduceConflict(i, &V);
  }
  FORLIM = LINK->prodant;
  /* CHECK IF LOOKANT[I]=/=LOOKANT[J], I=/=J */
  for (i = 1; i < FORLIM; i++) {
    mark_(V.c1, i, &V);
    FORLIM1 = LINK->prodant;
    for (j = i + 1; j <= FORLIM1; j++) {
      mark_(V.c2, j, &V);
      /* IF C1 AND C2 ARE DISJOINT THERE IS NO REDUCE/REDUCE CONFLICT */
      conflict = check(&V);
      if (conflict)
	ReduceReduceConflict(i, j, &V);
    }
  }
}  /* TESTCONFLICTS */



/******************************************************************/
/*                                                                */
/*                  TEST - PROCEDURES                             */
/*                                                                */
/******************************************************************/

Local void predtest(struct LOC_adequad *LINK)
{
  long rlink, i;   /* INDEX TO PROD */
  long oldprodno, oldstate;
  konfigt *s;   /* LINK-POINTER IN RHS */
  pointer2 t;   /* DVS. DENNE */
  long FORLIM;

  if (!options[37])   /* PRED-TEST */
    return;
  if (!options[14])   /* SKRIVPARSER(GEMP) ALREADY CALLED */
    skrivparser(gemp);
  fprintf(blst, "\f");
  fputc(lf(), blst);
  writech('*', 20);
  fprintf(blst, " PRED-TEST (OPTION 38) ");
  writech('*', 20);
  fprintf(blst, "%c%c", lf(), lf());
  fprintf(blst, "PRODNO     STATE      PRED%c%c", lf(), lf());
  oldprodno = -1;
  oldstate = -1;
  FORLIM = antalprod;
  for (i = 1; i <= FORLIM; i++) {
    t = prod[i].start;
    while (t != rhsnil) {
      rlink = -1;
      pred(i, prod[i].laengde + 1, rhs[t].parserp, &rlink, &s, LINK);
      while (s != NULL) {
	if (oldprodno == i)
	  fprintf(blst, "         ");
	else
	  fprintf(blst, "%7ld  ", i);
	oldprodno = i;
	if (oldstate == (long)rhs[t].parserp)
	  fprintf(blst, "          ");
	else
	  fprintf(blst, "%7ld   ", (long)rhs[t].parserp);
	oldstate = (long)rhs[t].parserp;
	fprintf(blst, "%12ld%c", (long)s, lf());
	pred(i, prod[i].laengde + 1, rhs[t].parserp, &rlink, &s, LINK);
      }
      t = rhs[t].link;
    }
  }
}  /* PREDTEST */

Local void looktestud(konfigt *start, long pnr, struct LOC_adequad *LINK)
{  /* UDSKRIV LOOKAHEADMAENGDERNE */
  long w, t, FORLIM;

  fprintf(blst, "%12ld%12ld", (long)start, pnr);
  t = 25;
  FORLIM = LINK->lalaengde;
  for (w = 0; w < FORLIM; w++) {
    outalf20(internrep[LINK->la[w] + 1], &dummy);
    t += 11;
    if (t > 60) {
      fprintf(blst, "%c%20c", lf(), ' ');
      t = 25;
    }
  }
  fprintf(blst, "%c%c", lf(), lf());
}  /* OPTION 37 */

Local void testlrcond(struct LOC_adequad *LINK)
{
  long p[10], d[10];
  long j, i;
  konfigt *r, *t;
  long FORLIM;

  FORLIM = tilstnr;
  for (j = 1; j <= FORLIM; j++) {
    t = tilstand[j].oldstart;
    r = t;
    i = 0;
    while (r != NULL) {
      if (r->mode == 0) {
	i++;
	p[i - 1] = r->UU.U1.prodnr;
	d[i - 1] = prod[p[i - 1]].laengde + 1;
      }
      r = r->derivp;
    }
    if (i > 1) {
      fprintf(blst, "%12ld%12ld%12ld%12ld%12ld",
	      p[0], d[0], p[1], d[1], (long)t);
      /*     IF LRCOND( P[1], D[1], P[2], D[2], T )
             THEN WRITE(BLST,' NO LR(1)-CONFLICT',LF)
             ELSE WRITE(BLST,' IS NOT LR(1)',LF);*/
    }
  }
}  /* TESTLR */


Local void lookaheadtest(struct LOC_adequad *LINK)
{
  long i, t, FORLIM;

  if (!options[39])
    return;
  fprintf(blst, "\f");
  fputc(lf(), blst);
  writech('*', 25);
  fprintf(blst, " LOOKAHEAD-TEST ");
  writech('*', 25);
  fputc(lf(), blst);
  writech(' ', 25);
  if (options[26])
    fprintf(blst, " OLD LOOKAHEAD%c", lf());
  else
    fprintf(blst, " NEW LOOKAHEAD%c", lf());
  FORLIM = antalprod;
  for (i = 1; i <= FORLIM; i++) {
    t = prod[i].start;
    while (t != rhsnil) {
      if (options[26])
	lalrlookahead(rhs[t].parserp, i, LINK);
      else
	lookahead(rhs[t].parserp, i, 0, LINK->la1, LINK);
      looktestud(rhs[t].parserp, i, LINK);
      t = rhs[t].link;
    }
  }
  options[38] = false;
}  /* LOOKAHEADTEST */


/**************************************************************/
/*                                                            */
/*                      ADEQUAD                               */
/*                                                            */
/**************************************************************/


Static void adequad(void)
{
  struct LOC_adequad V;
  long pnr, lsymb, i, j, k, l;
  boolean boo;
  konfigt *start, *lqbep1, *lqbep2, *lqbep3, *stopp;
  long FORLIM;
  konfigt *WITH;
  prodtype *WITH1;



  /******************************************************************/
  /*                                                                */
  /*                 ADEQUAD- BODY                                  */
  /*                                                                */
  /******************************************************************/




  initdot(&V);
  /* file lalrk.pas must be inserted
     stack1:=nil; stack2:=nil;
     IF options[51] THEN lalrklookahead(1);
     IF options[52] THEN lalrklookahead(2);
     IF options[53] THEN lalrklookahead(3);
     IF options[54] THEN lalrklookahead(4);
     IF options[55] THEN lalrklookahead(5);
  */

  if (options[37])
    predtest(&V);
  if (options[39])
    lookaheadtest(&V);
  if (options[6])
    msg("- OPTION 7 IGNORED                      ");
  if (options[41])
    testlrcond(&V);
  V.lrok = true;
  V.headwrite = true;
  boo = true;
  FORLIM = tilstnr;
  for (i = 1; i <= FORLIM; i++) {   /* the grammar is LALR(1) */
    start = tilstand[i].oldstart;
    V.prodant = 0;
    V.termant = 0;
    V.helpp = start;
    do {
      k = V.helpp->mode;
      if (k == 0)
	V.prodant++;
      else {
	if (V.helpp->UU.U1.inf <= symbmax(&V) && V.helpp->nextp != NULL)
	  V.termant++;
      }
      V.helpp = V.helpp->derivp;
    } while (V.helpp != NULL);
    if (V.prodant > const14)
      consterror("ADEQUAD   ", "CONST6    ", const6);
    updatemax(6, V.prodant);

    /* test if the state is inadequate or adequate       */
    if (V.prodant > 1 || V.prodant == 1 && V.termant > 0)
    {  /* inadequate state */
      /* compute lookahead and add to items */
      V.prodant = 0;
      V.termant = 0;
      V.helpp = start;
      do {
	k = V.helpp->mode;
	if (k == 0) {
	  pnr = V.helpp->UU.U1.prodnr;
	  lsymb = prod[pnr].leftside;

	  /**********************************************/
	  if (options[26])   /* Old LookAhead */
	    lalrlookahead(start, pnr, &V);
	  else  /* New LookAhead  */
	    lookahead(start, pnr, 0, V.la1, &V);
	  /**********************************************/

	  l = V.lalaengde - 1;
	  allocp(&lqbep1, 1, "ADEQUAD   ");
	  V.helpp->nextp = lqbep1;
	  V.prodant++;
	  V.lookant[V.prodant - 1].ant = V.lalaengde;
	  V.lookant[V.prodant - 1].point = lqbep1;
	  lqbep3 = findreduce(pnr, &V);
	  for (j = 0; j <= l; j++) {
	    lqbep2 = lqbep1;
	    lqbep2->nextp = lqbep3;
	    lqbep2->UU.U1.inf = V.la[j];
	    lqbep2->UU.U1.prodnr = pnr;
	    lqbep2->mode = 4;
	    if (j == l)
	      lqbep2->derivp = V.helpp->derivp;
	    else {
	      allocp(&lqbep1, 1, "ADEQUAD   ");
	      lqbep2->derivp = lqbep1;
	    }
	  }
	} else {
	  WITH = V.helpp;
	  if (WITH->UU.U1.inf <= symbmax(&V) && WITH->nextp != NULL) {
	    V.termant++;
	    if (V.termant > const2)
	      consterror("ADEQUAD   ", "CONST2    ", const2);
	    else {
	      V.stack[V.termant - 1].symb = WITH->UU.U1.inf;
	      V.stack[V.termant - 1].pnr = WITH->UU.U1.prodnr;
	      V.stack[V.termant - 1].token = WITH->mode;
	    }
	  }
	  WITH->mode = 2;
	}
	V.helpp = V.helpp->derivp;
      } while (V.helpp != NULL);


      /**************************************/
      /* test for conflicts in state: start */

      testconflicts(start, &V);
      /***************************************/

    } else {
      if (V.prodant == 0) {  /* adequate state of type shift */
	V.helpp = start;
	while (V.helpp != NULL) {
	  V.helpp->mode = 1;
	  V.helpp = V.helpp->derivp;
	}
      }
    }
    /*NU ER DENNE TILSTAND FAERDIG,HVIS LOOKAHEAD
      VAR NQDVENDIG ER DEN SAT IND
      DER MANGLER NU KUN AT BLIVE JUSTERET POINTERE.
      DER SKER UNDER OPTIMALISERING.OPTIMALISE-
      RING VIL KUN SKE HVIS GRAMMATIKKEN ER SLR1 */
  }

  /**************** experimental change ******************************/
  /* A parser will be constructed even if the grammar is NON LALR(1) */
  /*    if (lrok) then
        begin*********/
  FORLIM = tilstnr;
  /*******************************************************************/
  /* Optimization is performed by removing superfluous entries */
  for (i = 1; i <= FORLIM; i++) {
    start = tilstand[i].oldstart;
    V.lastok = start;
    V.prodant = 0;
    V.termant = 0;
    count = 0;
    lqbep1 = start;
    do {
      V.helpp = lqbep1;
      count++;
      stopp = lqbep1->derivp;
      if (lqbep1->mode == 0 && lqbep1->nextp != NULL) {
	/*NU ER DET EN REDUKTION
	  PRODANT,TERMANT,COUNT SIGER OM DER SKAL
	  VAERE NY INDGANG */
	if (V.prodant == 0 && V.termant == 0) {
	  V.helpp = lqbep1->nextp;
	  optimalisering(nyindgang, &V);
	} else {
	  V.helpp = lqbep1->nextp;
	  optimalisering(nyvej, &V);
	}
	V.prodant++;
	/*LASTOK SKAL VAERE DET SIDSTE
	  AF LOOKAHEADELEMENTERNE */
	do {
	  lqbep3 = V.lastok->derivp;
	  if (lqbep3 != stopp)
	    V.lastok = lqbep3;
	} while (lqbep3 != stopp);
      } else {
	if (lqbep1->mode == 0) {
	  WITH1 = &prod[lqbep1->UU.U1.prodnr];
	  /*IN THIS STATE: ONLY ONE REDUCTION       */
	  /*IF ITS AN EMPTY REDUCTION, THEN         */
	  /*SOME NONTERMINAL TRANSITIONS MAY APPEAR */
	  lqbep1->mode = 3;
	  lqbep1->nextp = WITH1->lookbackp;
	  V.prodant++;
	  if (WITH1->laengde == 0)
	    lqbep1->UU.U1.inf = 0;
	  else
	    lqbep1->UU.U1.inf = WITH1->laengde - 1;
	  if (count > 1)
	    optimalisering(nyindgang, &V);
	} else {
	  if (lqbep1->UU.U1.inf <= symbmax(&V)) {
	    /*NU ER DET ET TERMINAL SYMBOL */
	    if (count > 1) {
	      if (lqbep1->nextp != NULL) {
		V.helpp = lqbep1;
		if (V.prodant == 0 && V.termant == 0)
		  optimalisering(nyindgang, &V);
		else
		  optimalisering(nyvej, &V);
	      } else {
		V.helpp = stopp;
		optimalisering(udenom, &V);
		V.termant--;
	      }
	    }
	    V.termant++;
	  } else {  /*NONTERMINAL TRANSITION */
	    V.helpp = lqbep1->derivp;
	    if (V.termant == 0 && V.prodant == 0)
	      optimalisering(nyindgang, &V);
	    else {
	      V.helpp = stopp;
	      optimalisering(udenom, &V);
	    }
	  }
	}
      }
      lqbep1 = stopp;
    } while (lqbep1 != NULL);
  }

  /*******************************/
  if (options[11])
    adeqwrite(6, &V);
  if (V.lrok)   /* IF NOT LROK */
    lalrtext(1, &V);
  /********************************* experimental change ********/
  /*    end********/
  /* IF LROK THEN */
  /*   else
        begin******/
  if (V.lrok == false) {
    adeqwrite(6, &V);
    lalrtext(2, &V);
    /****  stop(0) ;*********/
  }
  /*******************************/

}  /* ADEQUAD */


typedef short symbol_;

typedef short errorno;
   /* changed from errno to avoid linking problem on Linux/jlk */
typedef char rslength;

typedef short prodno;

typedef short lrinx;

typedef struct lrelm {
  /*packed*/
  lrinx chain;   /*NEXT ITEM IN THIS STATE*/
  lrinx next;   /*NEXT STATE*/
  /*TYPE OF STATE*/
  rslength kind;
  union {
    struct {
      symbol_ symb;
      errorno err;
    } U1;
    struct {
      rslength rs;
      prodno prodn;
    } U0;
    lrinx lb;
  } UU;
} lrelm;   /*RECORD*/


typedef short lxinx;
   /* NOTE! CHAR MAY NOT CONTAIN MORE THAN 256 CHARS*/

typedef struct lxelm {
  /*packed*/
  short np, hp;
  symbol_ tv;
  Char ch;
} lxelm;


/* Local variables for finalparser: */
struct LOC_finalparser {
  lrelm lr[const7 + 1];
  long smax, errorcount;   /* set by errorTables */
  long firstt;
  /* ,incr - used by stateNo - now obsolite */
  long last;
} ;


Local void copy_(Char *ch, boolean skip, struct LOC_finalparser *LINK)
{
  if (P_eof(parsin)) {
    fputc(lf(), blst);
    fprintf(blst, " FILE PARSIN IS NOT A CORRECT PARSER ");
    msg("=ERROR(S) IN FILE   PARSIN              ");
    stop(0);
    return;
  }
  /* changed by JLK to please p2c:
   * begin ch:=parsin^;
   *   if not skip then
   *    if eoln(parsin) then writeln(parsout)
   *    else write(blst,parsout,ch);
   * end;
   * get(parsin);*/
  if (!skip) {
    if (P_eoln(parsin)) {
      *ch = getc(parsin);
      if (*ch == '\n')
	*ch = ' ';
      putc('\n', parsout);
      return;
    }
    *ch = getc(parsin);
    if (*ch == '\n')
      *ch = ' ';
    putc(*ch, parsout);
    return;
  }
  *ch = getc(parsin);
  if (*ch == '\n')
    *ch = ' ';
}  /*COPY*/


Local void search(boolean skip, struct LOC_finalparser *LINK)
{
  Char a[5];
  long i;
  boolean found;
  Char ch;

  found = false;
  a[0] = 'B';
  a[1] = 'O';
  a[2] = 'B';
  a[3] = 'S';
  a[4] = ' ';
  do {
    copy_(&ch, skip, LINK);
    if (ch == '*') {
      do {
	copy_(&ch, skip, LINK);
      } while (ch == '*');
      i = 1;
      while (a[i - 1] == ch && i < 5) {
	copy_(&ch, skip, LINK);
	i++;
      }
      found = (i > 4);
    }
  } while (!found);
  while (!P_eoln(parsin))
    copy_(&ch, skip, LINK);
  copy_(&ch, skip, LINK);
}  /*SEARCH*/

Local long stateno(konfigt *pt, struct LOC_finalparser *LINK)
{
  long k, l, u, sno, ptSeq;

  if (pt == NULL) {
    sno = 0;
    ptSeq = 0;
    return sno;
  }
  l = LINK->firstt;
  u = LINK->last;
  ptSeq = pt->seq;
  do {
    k = (l + u) / 2;
    /* changed from:
     *  if ord(tilstand[k].oldstart) <= ord(pt) then l:=k+incr;
     *    if ord(tilstand[k].oldstart) >= ord(pt) then u:=k-incr;
     * by jlk to solve Linux problem
     */
    if (tilstand[k].oldstart->seq <= ptSeq)
      l = k + 1;
    if (tilstand[k].oldstart->seq >= ptSeq)
      u = k - 1;
    /* changed from:
     *    until (l*incr) > (u*incr);
     * by jlk to solve Linux problem
     */
  } while (l <= u);
  sno = tilstand[k].newstart;
  if (options[73])
    fprintf(blst, "stateno:%12ld%4ld%12ld%4ld%4ld%4d\n",
	    (long)tilstand[k].oldstart, tilstand[k].oldstart->seq, (long)pt,
	    pt->seq, k, tilstand[k].newstart);
  return sno;

  /*BINARY SEARCH*/
}  /*STATENO*/

Local void emitconstants(struct LOC_finalparser *LINK)
{
  long m;

  if (!options[31]) {   /*USE STANDARD SKELETON COMPILER */
    if (parsin != NULL)
      parsin = freopen("parsin", "r", parsin);
    else
      parsin = fopen("parsin", "r");
    if (parsin == NULL)
      _EscIO(FileNotFound);
    if (parsout != NULL) {
      /*ON FILE PARSIN, AND DELIVER IT */
      parsout = freopen("parsout", "w", parsout);
    } else
      parsout = fopen("parsout", "w");
    if (parsout == NULL)
      _EscIO(FileNotFound);
    /*ON FILE PARSOUT WITH INITIALISED CONSTANTS*/
    search(false, LINK);
    fprintf(parsout, " goalSymbol=%ld;\n", goalhusk);
    fprintf(parsout, " nontStart=%ld;\n", nontstart);
    fprintf(parsout, " SYMBMAX=%ld;\n", nontslut);
    if (LINK->errorcount < prodcount)
      m = prodcount;
    else
      m = LINK->errorcount;
    fprintf(parsout, " PRODMAX=%ld;\n", antalprod);
    fprintf(parsout, " prodFMax=%ld;\n", m);
    fprintf(parsout, " LRMAX=%ld;\n", LINK->smax);
    fprintf(parsout, " LXMAX=%ld;\n", trmax);
    fprintf(parsout, " ERRORVAL=%ld;\n", errorval);
    fprintf(parsout, " NAMEVAL=%ld;\n", nameval);
    fprintf(parsout, " CONSTVAL=%ld;\n", cstval);
    fprintf(parsout, " STRINGVAL=%ld;\n", stringval);
    fprintf(parsout, " STRINGCH=\n");
    if (stringch == '\'')
      fprintf(parsout, "'''';\n");
    else
      fprintf(parsout, "'%c';\n", stringch);
    fprintf(parsout, " COMBEGIN=%ld;\n", combegin);
    fprintf(parsout, " COMLENGTH=%ld;\n", comlength);
    if (options[56] || options[58]) {
      fprintf(parsout, " nontL=%ld;\n", nontl);
      fprintf(parsout, " nontR=%ld;\n", nontr);
    }
    search(true, LINK);
    fprintf(parsout, " (*BOBS*) \n");
    search(false, LINK);
  }
  fprintf(tables, "%12ld\n", goalhusk);
  fprintf(tables, "%12ld\n", nontstart);
  fprintf(tables, "%12ld\n", nontslut);
  fprintf(tables, "%12ld\n", antalprod);
  fprintf(tables, "%12ld\n", m);
  fprintf(tables, "%12ld\n", LINK->smax);
  fprintf(tables, "%12ld\n", trmax);
  fprintf(tables, "%12ld\n", errorval);
  fprintf(tables, "%12ld\n", nameval);
  fprintf(tables, "%12ld\n", cstval);
  fprintf(tables, "%12ld\n", stringval);
  if (options[56])
    fprintf(tables, "%12d\n", stringch);
  else
    fprintf(tables, " %c\n", stringch);
  fprintf(tables, "%12ld\n", combegin);
  fprintf(tables, "%12ld\n", comlength);
  if (options[56] || options[58]) {
    fprintf(tables, "%ld\n", nontl);
    fprintf(tables, "%ld\n", nontr);
  }
}  /*EMITCONSTANTS*/

/* Local variables for emitlex: */
struct LOC_emitlex {
  struct LOC_finalparser *LINK;
  lxelm lx[const12 + 257];
  long tinx;
} ;

/* Local variables for convertlex: */
struct LOC_convertlex {
  struct LOC_emitlex *LINK;
} ;

Local void incrtinx(struct LOC_convertlex *LINK)
{
  if (LINK->LINK->tinx < const12)
    LINK->LINK->tinx++;
  else
    consterror("CONVERTLEX", " CONST12  ", const12);
  updatemax(12, LINK->LINK->tinx);
}

Local void visit(termelm *p, struct LOC_convertlex *LINK)
{
  lxelm *WITH1;

  WITH1 = &LINK->LINK->lx[LINK->LINK->tinx + 256];
  WITH1->tv = p->intern;
  WITH1->ch = p->tegn;
  if (p->niveaup != NULL) {
    incrtinx(LINK);
    WITH1->np = LINK->LINK->tinx;
    visit(p->niveaup, LINK);
  } else
    WITH1->np = 0;
  if (p->higherp == NULL) {
    WITH1->hp = 0;
    return;
  }
  incrtinx(LINK);
  WITH1->hp = LINK->LINK->tinx;
  visit(p->higherp, LINK);
}  /*VISIT*/

Local void convertlex(struct LOC_emitlex *LINK)
{
  struct LOC_convertlex V;
  Char c;
  lxelm *WITH;
  entrytyp *WITH1;

  V.LINK = LINK;
  /*TRANSFORM CLASS TERMTREE INTO ARRAY LX*/
  LINK->tinx = 0;
  LINK->lx[256].ch = ' ';
  LINK->lx[256].hp = 0;
  LINK->lx[256].np = 0;
  LINK->lx[256].tv = 0;
  /* LX[0] IS NOT USED */
  for (c = minch; c <= maxch; c++) {
    WITH = &LINK->lx[c - maxch + 255];
    WITH1 = &entry_[c];
    WITH->tv = WITH1->intern1;
    WITH->ch = c;
    WITH->np = 0;
    if (WITH1->termp != NULL) {
      incrtinx(&V);
      WITH->hp = LINK->tinx;
      visit(WITH1->termp, &V);
    } else
      WITH->hp = 0;
  }
}  /*CONVERTLEX*/

Local void emitlex(struct LOC_finalparser *LINK)
{
  struct LOC_emitlex V;
  long t;
  /* added by JLK to make p2c happy - see next p2c modification */
  long x, FORLIM;
  lxelm *WITH;

  V.LINK = LINK;
  convertlex(&V);
  FORLIM = V.tinx + 256;
  for (t = minch - maxch + 255; t <= FORLIM; t++) {
    WITH = &V.lx[t];
    if (options[56])
      fprintf(tables, "%d ", WITH->ch);
    else
      fprintf(tables, " %c", WITH->ch);
    fprintf(tables, "%d %d ", WITH->np, WITH->hp);
    x = WITH->tv;
    if (x < 0)
      fprintf(tables, "%d\n", 0);
    else
      fprintf(tables, "%ld\n", x);
    /* modified by JLK to please p2c:
     * Old: if tv<0 then writeln(tables,0:1) else writeln(tables,tv:1);
     */
  }
}  /*EMITLEX*/

Local boolean nolookahead(long p)
{
  long i;

  if (allnolook)
    return true;
  else {
    nolook[nolooki] = p;
    i = 0;
    while (nolook[i] != p)
      i++;
    return (i != nolooki);
  }
}

Local void emitpars(struct LOC_finalparser *LINK)
{
  lrinx si, FORLIM;
  lrelm *WITH;


  fprintf(blst, "\n\n ");
  FORLIM = LINK->smax;
  for (si = 0; si <= FORLIM; si++) {
    WITH = &LINK->lr[si];
    if (WITH->kind == 3) {
      if (nolookahead(rhs[prod[WITH->UU.U0.prodn].start].first))
	WITH->kind = 7;
    }
    if (WITH->kind == 7)
      fprintf(blst, "NOLOOKAHEAD ON %d%c", WITH->UU.U0.prodn, lf());
    fprintf(tables, "%d %d %d ", WITH->chain, WITH->next, WITH->kind);
    switch (WITH->kind) {

    case 1:
    case 2:
    case 4:
    case 6:
      fprintf(tables, "%d %d\n", WITH->UU.U1.symb, WITH->UU.U1.err);
      break;

    case 0:
    case 3:
    case 7:
      fprintf(tables, "%d %d\n", WITH->UU.U0.rs, WITH->UU.U0.prodn);
      break;

    case 5:
      fprintf(tables, "%d\n", WITH->UU.lb);
      break;
    }
  }
}  /*EMITPARS*/

/* Local variables for compress: */
struct LOC_compress {
  struct LOC_finalparser *LINK;
  lrinx si, sstart;
} ;

Local void lapres(konfigt **start, struct LOC_compress *LINK)
{
  konfigt *sp;
  long m;
  konfigt *WITH;

  sp = *start;
  begintilst = sp;
  fcqi = 0;   /*BEGINTILST AND FCQI ARE USED IN OPTIMIZE*/
  while (sp != NULL) {
    WITH = sp;
    if (WITH->mode == 4)
      remember(WITH->nextp);
    sp = WITH->derivp;
  }
  m = 4;
  optimize(&sp, &m);
  allocp(&classtop, 1, "LAPRES    ");
  oldp->derivp = classtop;   /*OLDP IS SET IN OPTIMIZE*/
  WITH = classtop;
  WITH->UU.U1.inf = 0;
  WITH->UU.U1.prodnr = m;
  WITH->mode = 4;
  WITH->nextp = sp;
  WITH->derivp = NULL;
  *start = begintilst;
}  /*LAPRES*/

Local void deletetail(long s, struct LOC_compress *LINK)
{
  long t;
  lrinx sinx, tinx, sx, tx, oldsinx, smatch;
  konfigt *sptr, *tptr, *sp, *tp;
  boolean maxmatch;
  lrelm *WITH;
  konfigt *WITH1;

  t = 1;
  smatch = const7;
  maxmatch = false;
  while (t < s && !maxmatch) {
    sinx = LINK->LINK->lr[LINK->sstart].chain;
    oldsinx = LINK->sstart;
    sptr = tilstand[s].oldstart->derivp;
    while (sinx > 0 && sinx < smatch) {
      tinx = tilstand[t].newstart;
      tptr = tilstand[t].oldstart;
      while (tinx > 0) {
	if (LINK->LINK->lr[sinx].UU.U1.symb == LINK->LINK->lr[tinx].UU.U1.symb) {
	  sx = sinx;
	  tx = tinx;
	  sp = sptr;
	  tp = tptr;
	  while (sx > 0 && tx > 0) {
	    WITH = &LINK->LINK->lr[sx];
	    WITH1 = sp;
	    if (WITH->UU.U1.symb != LINK->LINK->lr[tx].UU.U1.symb ||
		WITH->kind != LINK->LINK->lr[tx].kind ||
		WITH1->nextp != tp->nextp)
	      goto _L10;
	    sx = WITH->chain;
	    sp = WITH1->derivp;
	    tx = LINK->LINK->lr[tx].chain;
	    tp = tp->derivp;
	  }
	  if (sx == tx)   /*SX=TX=0*/
	  {  /*SUCCESSFUL MATCH*/
	    maxmatch = (oldsinx == LINK->sstart);
	    smatch = oldsinx;
	    LINK->si = smatch + 1;
	    LINK->LINK->lr[smatch].chain = tinx;
	    goto _L20;
	  }
	}
_L10:
	tinx = LINK->LINK->lr[tinx].chain;
	tptr = tptr->derivp;
      }  /*WHILE TINX>0 DO*/
      oldsinx = sinx;
      sinx = LINK->LINK->lr[sinx].chain;
      sptr = sptr->derivp;
    }  /*WHILE SINX>0....*/
_L20:
    t++;
  }
}  /*DELETETAIL*/

/*     PROCEDURE emitLookBackEntry;
     VAR I: integer;
     BEGIN writeln(tables);
       FOR I:=nontStart to nontSlut do
         writeln(tables,stateNo(lookBackEntry[I]));
     END; */

Local void compress(struct LOC_finalparser *LINK)
{
  /* THE CLASS PARSER IS COMPRESSED INTO THE ARRAY LR*/
  struct LOC_compress V;
  long state_;
  boolean laoptim, tailoptim;
  konfigt *statep;
  long seq;   /* added by jlk to avoid Linux problem */
  long FORLIM;
  lrelm *WITH;
  konfigt *WITH1;


  V.LINK = LINK;
  laoptim = !options[21];
  tailoptim = !options[28];
  V.si = 0;

  FORLIM = antaltilst;
  /*COPY PARSER TO LR AND MERGE IDENTICAL TAILS OF STATES*/
  for (state_ = 0; state_ <= FORLIM; state_++) {
    statep = tilstand[state_].oldstart;
    V.sstart = V.si;
    tilstand[state_].newstart = V.sstart;
    if (laoptim && ((1L << statep->mode) & 0x14) != 0) {
      lapres(&statep, &V);
      seq = tilstand[state_].oldstart->seq;
	  /* added by jlk to avoid Linux problem */
      *tilstand[state_].oldstart = *statep;
      tilstand[state_].oldstart->seq = seq;
	  /* added by jlk to avoid Linux problem */
    }
    while (statep != NULL) {
      WITH = &LINK->lr[V.si];
      WITH1 = statep;
      if (WITH1->derivp == NULL)
	WITH->chain = 0;
      else
	WITH->chain = V.si + 1;
      if (((1L << WITH1->mode) & 0x18) != 0) {   /*PRODNR IS UNDEF IF MODE=5*/
	if (prod[WITH1->UU.U1.prodnr].laengde == 0)
	  WITH1->mode = 6;
      }
      WITH->kind = WITH1->mode;
      switch (WITH1->mode) {

      case 1:
      case 2:
      case 4:
      case 6:
	WITH->UU.U1.symb = WITH1->UU.U1.inf;
	WITH->UU.U1.err = WITH1->UU.U1.prodnr;
	if (WITH1->mode <= 2)
	  WITH->UU.U1.err = 0;
	break;

      case 3:
	WITH->UU.U0.rs = WITH1->UU.U1.inf;
	WITH->UU.U0.prodn = WITH1->UU.U1.prodnr;
	if (WITH->UU.U0.prodn == 0 || WITH->UU.U0.prodn > antalprod)
	{   /*see proc handleProd in LR0 */
	  WITH->kind = 0;
	  WITH->UU.U0.prodn = 0;
	}
	break;

      case 5:
	/* blank case */
	break;
      }/*CASE*/
      statep = WITH1->derivp;
      if (V.si >= const7 - 1)
	consterror("COMPRESS  ", "CONST7    ", const7);
      V.si++;
    }
    if (tailoptim && ((1L << LINK->lr[V.sstart].kind) & 0x16) != 0)
      deletetail(state_, &V);
  }

  LINK->smax = V.si - 1;   /*INDEX OF LAST ELEMENT USED IN LR*/

  /*ADJUST NEXT AND LB IN LR BY MEANS OF ARRAY TILSTAND*/

  LINK->firstt = 0;
  LINK->last = antaltilst;   /* line added by jlk to solve Linux problem */
  /*INITIALIZATIONS FOR THE FUNCTION STATENO
   *  - obsolite due to new binary search method
   *  - see changes, sept. 1994
   * if ord(tilstand[0].oldstart) < ord(tilstand[antaltilst].oldstart) then
   * begin incr:=1;
   *  firstt:=0; last:=antaltilst;
   * end
   * else
   * begin incr:=-1;
   *   firstt:=antaltilst; last:=0;
   * end;
   */
  if (options[16])
    dump1();
  FORLIM = antaltilst;
  for (state_ = 0; state_ <= FORLIM; state_++) {
    V.sstart = tilstand[state_].newstart;
    statep = tilstand[state_].oldstart;
    V.si = V.sstart;
    while (statep != NULL) {
      WITH = &LINK->lr[V.si];
      WITH1 = statep;
      WITH->next = stateno(WITH1->nextp, LINK);
      if (WITH1->mode == 5)
	WITH->UU.lb = stateno(WITH1->UU.lookbp, LINK);
      V.si = WITH->chain;
      if (V.si < V.sstart)
	statep = NULL;   /*REST OF THE STATE IS A TAIL*/
      else
	statep = WITH1->derivp;
    }
  }  /*FOR*/
}  /*COMPRESS*/

Local void errortable(struct LOC_finalparser *LINK)
{
  long i, i5, no, j, StateIcount, StateJcount;
  lrinx lqbep, testp, gemp;
  long FORLIM;
  _REC_tilstand *WITH;
  lrelm *WITH1;
  long FORLIM1;
  _REC_tilstand *WITH2;

  fprintf(blst, "\f");
  no = 0;
  fprintf(blst,
	  "***********************  COMPILER ERROR MESSAGES  ***********");
  fprintf(blst, "%c%c%c ", lf(), lf(), lf());
  fprintf(blst, "  ERRORNO : 0      ** ILLEGAL TERMINAL SYMBOL **");
  fprintf(blst, "%c%c%c ", lf(), lf(), lf());
  fprintf(blst, "  ERRORNO :        EXPECTED SYMBOL:");
  FORLIM = antaltilst;
  for (i = 1; i <= FORLIM; i++)
    tilstand[i].errorno = 0;
  FORLIM = antaltilst;
  for (i = 1; i <= FORLIM; i++) {
    WITH = &tilstand[i];
    if (LINK->lr[WITH->newstart].kind == 1 && WITH->errorno == 0) {
      if (no < const1)
	no++;
      else
	consterror("ERRORTABLE", "CONST1    ", const1);
      updatemax(1, no);
      WITH->errorno = no;
      i5 = 0;
      LINK->lr[WITH->newstart].UU.U1.err = no;
      lqbep = WITH->newstart;
      fprintf(blst, "%c%c%12ld :        ", lf(), lf(), no);
      StateIcount = 0;
      while (lqbep != 0) {
	WITH1 = &LINK->lr[lqbep];
	StateIcount++;
	if (i5 > 50) {
	  fprintf(blst, "%c%s%s", lf(), blank, blank);
	  i5 = 0;
	}
	symbwrite(WITH1->UU.U1.symb, &i5);
	putc(' ', blst);
	lqbep = WITH1->chain;
	i5++;
      }
      FORLIM1 = antaltilst;
      for (j = i + 1; j <= FORLIM1; j++) {
	if (LINK->lr[tilstand[j].newstart].kind == 1 &&
	    tilstand[j].errorno == 0) {
	  lqbep = WITH->newstart;
	  gemp = tilstand[j].newstart;
	  /* count no. of elements in 'gemp' */
	  StateJcount = 0;
	  testp = gemp;
	  while (testp != 0) {
	    StateJcount++;
	    testp = LINK->lr[testp].chain;
	  }

	  /* match StateI and StateJ */
	  while (lqbep != 0) {
	    WITH1 = &LINK->lr[lqbep];
	    testp = gemp;
	    while (WITH1->UU.U1.symb != LINK->lr[testp].UU.U1.symb) {
	      testp = LINK->lr[testp].chain;
	      if (testp == 0)
		goto _L33;
	    }
	    lqbep = WITH1->chain;
	  }
	  if (StateIcount == StateJcount) {
	    WITH2 = &tilstand[j];
	    WITH2->errorno = no;
	    LINK->lr[WITH2->newstart].UU.U1.err = no;
	  }
_L33: ;   /* NOT IDENTICAL      */
	}
      }
    }
  }
  fprintf(blst,
    "\n\n\n*********************************************************************");
  LINK->errorcount = no;
}

Local void spl_(Char *a)
{
  long i;

  for (i = 0; i < alfalength; i++) {
    if (a[i] != ' ')
      putc(a[i], tables);
  }
}

Local void spl20_(Char *a)
{
  long i;

  for (i = 0; i < alfal20; i++) {
    if (a[i] != ' ')
      putc(a[i], tables);
  }
}

Local void tv_(nontelm *p)
{
  if (p == NULL)
    return;
  tv_(p->llink);
  tv_(p->rlink);
  fprintf(tables, " %d ", p->nontermvaerdi);
  spl_(p->word1);
  spl_(p->word2);
  spl_(p->word3);
  putc('\n', tables);
}

Local void emitlabels(struct LOC_finalparser *LINK)
{
  long pn, i, FORLIM;
  prodtype *WITH;
  long FORLIM1;
  _REC_rhs *WITH1;

  putc('\n', tables);
  FORLIM = antalprod;
  for (pn = 1; pn <= FORLIM; pn++) {
    fprintf(tables, "%5ld ", pn);
    if (options[55]) {
      WITH = &prod[pn];
      fprintf(tables, "%d %d ", WITH->laengde, WITH->leftside);
      FORLIM1 = WITH->start + WITH->laengde;
      for (i = WITH->start + 1; i <= FORLIM1; i++)
	fprintf(tables, "%d ", rhs[i].symbol_);
    }
    WITH1 = &rhs[prod[pn].start];
    FORLIM1 = WITH1->first + WITH1->length;
    for (i = WITH1->first; i < FORLIM1; i++)
      putc(labelbuf[i], tables);
    putc('\n', tables);
  }
  if (!options[55])
    return;
  fprintf(tables, "%ld StartSymbol\n", nontstart);
  FORLIM = nontstart;
  for (i = 1; i < FORLIM; i++) {
    fprintf(tables, "%ld ", i);
    spl20_(internrep[i + 1]);
    putc('\n', tables);
  }
  tv_(first);   /* nonterminals*/
}  /*EMITLABELS*/


Static void finalparser(void)
{
  struct LOC_finalparser V;
  long i;
  termelm *WITH;
  long FORLIM;

  /*DELETE 'ERROR','NAME','KONST','STRING' AND 'EMPTY' FROM TERMTREE*/
  if (go != NULL) {
    WITH = go;
    WITH->intern = 0;
    WITH->ok = false;
  }
  if (gs != NULL) {
    WITH = gs;
    WITH->intern = 0;
    WITH->ok = false;
  }
  if (gl != NULL) {
    WITH = gl;
    WITH->intern = 0;
    WITH->ok = false;
  }
  if (gn != NULL) {
    WITH = gn;
    WITH->intern = 0;
    WITH->ok = false;
  }
  if (gc != NULL) {
    WITH = gc;
    WITH->intern = 0;
    WITH->ok = false;
  }

  if (tables != NULL)
    tables = freopen("tables", "w", tables);
  else
    tables = fopen("tables", "w");
  if (tables == NULL)
    _EscIO(FileNotFound);

  compress(&V);
  errortable(&V);
  emitconstants(&V);
  if (options[56]) {
    FORLIM = comlength;
    for (i = 0; i < FORLIM; i++)
      fprintf(tables, "%d\n", comend[i]);
  } else
    fprintf(tables, "%.*s\n", (int)comlength, comend);
  emitlex(&V);
  if (options[16])   /* TILSTANDS ARRAY */
    dump1();
  emitpars(&V);
  /*     IF options[57] then emitLookBackEntry;*/
  if (options[32] || options[33])
    emitlabels(&V);
  updatemax(7, V.smax + 1);

/* p2c: exbobs.p, line 5141: Note:
 * Format for packed-array-of-char will work only if width < length [321] */
}  /*FINALPARSER*/


/******************************************************/
/*                                                    */
/*            M-A-I-N     PROGRAM                     */
/*                                                    */
/******************************************************/

main(int argc, Char *argv[])
{
  PASCAL_MAIN(argc, argv);
  if (setjmp(_JL999))
    goto _L999;
  f5 = NULL;
  f4 = NULL;
  f3 = NULL;
  f2 = NULL;
  f1 = NULL;
  spltab = NULL;
  tables = NULL;
  parsout = NULL;
  parsin = NULL;
  blst = NULL;
  if (blst != NULL)
    blst = freopen("bobslist", "w", blst);
  else
    blst = fopen("bobslist", "w");
  if (blst == NULL)
    _EscIO(FileNotFound);
  printf("******** BOBS SYSTEM  - LALR(1) Parser Generator - Version 1.4\n");
  fprintf(blst,
    "******** BOBS SYSTEM  - LALR(1) Parser Generator - Version 1.4 ********\n");
  fprintf(blst, "******** DER ER BQF I BOBS!\n");


  /***** setting of default options              ***************/
  for (i = 1; i <= const18; i++)
    options[i - 1] = false;
  options[27] = true;   /* don't remove single productions  */
  /* removed by JLK - is already done by generator:
   * options[32]:= true;    PARSIN and PARSOUT are ignored
   */
  options[55] = true;   /* write(blst,ord(ch)) not ch on tables  */
  options[56] = true;   /* the grammar is written to tables */

  fprintf(blst, "\f");
  fprintf(blst, "Default options:");
  for (i = 1; i <= const18; i++) {
    if (options[i - 1])
      fprintf(blst, "%ld ", i);
  }
  putc('\n', blst);
  /**************************************************************/

  seqIndex = 0;

  initmax();


  mstime = clock();
  /* HEAPCHECK('AT PROGRAM-START         '); */
  ingrammar();
  if (!options[27]) {
    options[27] = true;
    fprintf(blst,
	    "Option 28 is ignored; single productions are not removed\n");
  }
  if (options[46])
    timecheck("INGRAMMAR           ");
  if (options[45])
    heapcheck("AFTER INGRAMMAR     ");
  unused();
  idogfjern(true);
  termination();
  erasure();
  idogfjern(false);
  /*vhrecurs;*/
  if (options[46])
    timecheck("GRAMMAR-CHECKS      ");
  if (options[45])
    heapcheck("AFTER GRAMMAR-CHECKS");
  initprod();
  inithelp();
  initempty();
  /*   RoseGram; */
  outgrammar();
  updatemax(1, antalprod);
  updatemax(2, nontslut);
  if (options[46])
    timecheck("OUT-GRAMMAR         ");
  if (options[45])
    heapcheck("AFTER OUT-GRAMMAR   ");
  if (options[50])
    goto _L999;

  lr0();
  lookb();
  updatemax(10, antaltilst);
  updatemax(4, top);
  if (options[46])
    timecheck("LR0 & LOOKB         ");
  if (options[45])
    heapcheck("AFTER LR0 & LOOKB   ");
  /*msg(' *** adequad                            ');*/
  adequad();
  if (options[46])
    timecheck("ADEQUAD             ");
  if (options[45])
    heapcheck("AFTER ADEQUAD       ");
  if (options[49])   /* KUN RES. FRA ADEQUAD AF INTERESSE */
    goto _L999;
  finalparser();
  if (options[46])
    timecheck("FINALPARSER         ");
  if (options[45])
    heapcheck("AT END OF PROGRAM   ");
_L999:
  printmax();
  if (blst != NULL)
    fclose(blst);
  if (parsin != NULL)
    fclose(parsin);
  if (parsout != NULL)
    fclose(parsout);
  if (tables != NULL)
    fclose(tables);
  if (spltab != NULL)
    fclose(spltab);
  if (f1 != NULL)
    fclose(f1);
  if (f2 != NULL)
    fclose(f2);
  if (f3 != NULL)
    fclose(f3);
  if (f4 != NULL)
    fclose(f4);
  if (f5 != NULL)
    fclose(f5);
  exit(EXIT_SUCCESS);
}








/* End. */
