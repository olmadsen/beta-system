/* labelnametable.c
 *
 * Provides support for reading code labels from the nametable of an 
 * executable file.
 *
 * Sets up a fd to nm output and reads the nametable from this descriptor.
 * 
 * This file is used by both the debugger and the dynamic linker.
 * The debugger needs only the text (code) labels, whereas the dynamic
 * linker needs most symbols.
 * 
 * FIXME: In betarun/C/stack.c some of this code is replicated.
 * Probably this file should be included in betarun as "the one and only".
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#ifdef nti
#include <windows.h>
#ifdef nti_gnu
#  include "winntdef.h"
#endif /* nti_gnu */
#endif /* nti */

typedef struct _labeltable {
  FILE *fd;            /* The file descriptor from which the nameTable is read */
  int NextAddress;     /* The last address read from the fd. */
  char NextLabel[200]; /* The last label read from the fd. */
  int full;            /* Include all symbols? */
#ifdef nti
  int process_offset;  /* Offset for mapped process */
  DWORD textSectionNumber;
#endif /* nti */
} labeltable;


#ifdef ppcmac

char* nextLabel(labeltable *handle) 
{ 
  return 0;
}

int nextAddress(labeltable *handle) 
{ 
  return -1;
}

labeltable *initReadNameTable (char* execFileName) { 
  return 0;
}

void freeNameTable(labeltable *handle)
{
  return;
}

#else /* !ppcmac */

#ifdef sgi
#define FULL_NMCOMMAND  "/bin/nm -hvp %s"
#define TERSE_NMCOMMAND "/bin/nm -hvp %s"
#define Decimal
#endif

#ifdef sun4s
#define FULL_NMCOMMAND  "/usr/ccs/bin/nm -hvp %s"
#define TERSE_NMCOMMAND "/usr/ccs/bin/nm -hvp %s"
#define Decimal
#endif

#ifdef hpux9pa
#define FULL_NMCOMMAND  "/bin/nm -hp %s | sort"
#define TERSE_NMCOMMAND "/bin/nm -hp %s | grep ' T ' | sort"
#define Decimal
#endif

#ifdef linux
#define FULL_NMCOMMAND  "nm -Bv -td %s | grep -v ' U '"
#define TERSE_NMCOMMAND "nm -Bv -td %s | grep -v ' U '"
#define Decimal
#endif

#ifndef nti
#ifndef FULL_NMCOMMAND
#error FULL_NMCOMMAND should be defined
#endif 
#ifndef TERSE_NMCOMMAND
#error TERSE_NMCOMMAND should be defined
#endif 
#endif /* nti */

#ifdef nti
#define Hexadecimal
#define NMOUTFILE "temp.nmoutfile"
#define NMSORTOUTFILE "temp.nmsortoutfile"
#define pclose(fd) fclose(fd); unlink(NMSORTOUTFILE) /* ; fprintf(stderr,"Close & deleting %s\n",NMSORTOUTFILE)*/
static PSTR GetSZStorageClass(BYTE storageClass);
static void DumpSymbolTable(labeltable *table,
			    PIMAGE_SYMBOL pSymbolTable, 
			    unsigned cSymbols);
static void DumpExeFile(labeltable *table, 
			PIMAGE_DOS_HEADER dosHeader);
static void DumpFile(labeltable *table, LPSTR filename);
static void GetSectionName(WORD section,
			   PSTR buffer, 
			   unsigned cbBuffer);
static void DumpSectionTable(labeltable *table,
			     PIMAGE_SECTION_HEADER section,
			     unsigned cSections,
			     BOOL IsEXE);
static void DumpFile(labeltable *table, LPSTR filename);
#endif /* nti */

void findNextLabel (labeltable *table)
{ 
  int type;
  int ch;
  int inx,val;
  while (1) {
    table->NextAddress=0;
    while ((ch=fgetc (table->fd))!=' ') {
      if (ch==EOF) {
	table->NextAddress = -1; /* datpete 14/3/96: changed from 0 */
	pclose (table->fd);
	return;
      }
#ifdef Hexadecimal
      ch=tolower(ch);
      if (('0'<=ch) && (ch<='9')) {
	val = ch-'0';
      } else {
	val = 10+ch-'a';
      }
      table->NextAddress = (table->NextAddress*16)+val;
#else
      val = ch-'0';
      table->NextAddress = (table->NextAddress*10)+val;
#endif
    }

    while ((ch=fgetc (table->fd))==' ') 
      ;

    type = ch;

    if (!table->full){
      if ((type != 'N') && (type != 'T')) {
	while (fgetc (table->fd) != '\n') continue;
	continue;
      }
    }

    fgetc (table->fd);

    inx=0;
    while ((ch = fgetc(table->fd))!='\n') {
      if (ch==' ')
	;
      else
	table->NextLabel[inx++]=ch;
    }
    table->NextLabel[inx] = 0;
    return;
  }
}

labeltable *initReadNameTable (char* execFileName, int full)
{ 
  char command[100];
  labeltable *table = (labeltable*)malloc(sizeof(labeltable));
  if (!table){
    fprintf(stderr,"couldn't malloc label table for file %s\n", execFileName); 
    return 0;
  }
#ifndef nti 
  /* ! nti */
  if (full){
    sprintf (command,FULL_NMCOMMAND,execFileName);
  } else {
    sprintf (command,TERSE_NMCOMMAND,execFileName);
  }
  table->fd = popen(command, "r");
#else /* nti */
  table->full = full;
  table->process_offset=0;
  /*fprintf(stderr,"Opening %s\n",NMOUTFILE);*/
  if ((table->fd = fopen(NMOUTFILE,"w+"))==NULL) {
    fprintf(stderr,"couldn't open file %s\n",NMOUTFILE); 
    free(table);
    return 0;
  }
  /* run nm */
  DumpFile(table, execFileName );
  fclose (table->fd);
  sprintf(command,"sort < %s > %s",NMOUTFILE,NMSORTOUTFILE);
  system(command);
  unlink(NMOUTFILE);
  if ((table->fd = fopen(NMSORTOUTFILE,"r"))==NULL) {
    fprintf(stderr,"couldn't open file %s\n",NMSORTOUTFILE); 
    free(table);
    return 0;
  }
#endif /* nti */

  return table;
}

void freeNameTable(labeltable *handle)
{
  free(handle);
}


int nextAddress(labeltable *table) 
{ 
  findNextLabel(table);
#ifdef nti
#if 0
  fprintf(stderr, 
	  "table->NextAddress: %d (0x%x), table->NextLabel: %s\n",
	  table->NextAddress + table->process_offset,
	  table->NextAddress + table->process_offset,
	  table->NextLabel);
#endif 
  return table->NextAddress + table->process_offset;
#else
  return table->NextAddress;
#endif /* nti */
}

char* nextLabel(labeltable *table) 
{ 
  return table->NextLabel;
}

#ifdef nti
/* Implements 'nm' like behaviour for nti */


typedef struct
{
    DWORD   flag;
    PSTR    name;
} DWORD_FLAG_DESCRIPTIONS;

#define DEFAULTTEXTSECTIONNUMBER 1
#define TEXTSECTIONNAME ".text"

#define IMAGE_DBG_SIGNATURE     0x00004944
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (DWORD)(addValue))
#define NUMBER_SECTION_CHARACTERISTICS (sizeof(SectionCharacteristics) / sizeof(DWORD_FLAG_DESCRIPTIONS))

/* The names of the first group of possible symbol table storage classes */
static char * SzStorageClass1[] = {
  "NULL","AUTOMATIC","EXTERNAL","STATIC","REGISTER","EXTERNAL_DEF","LABEL",
  "UNDEFINED_LABEL","MEMBER_OF_STRUCT","ARGUMENT","STRUCT_TAG",
  "MEMBER_OF_UNION","UNION_TAG","TYPE_DEFINITION","UNDEFINED_STATIC",
  "ENUM_TAG","MEMBER_OF_ENUM","REGISTER_PARAM","BIT_FIELD"
};

/* The names of the second group of possible symbol table storage classes */
static char * SzStorageClass2[] = {
  "BLOCK","FUNCTION","END_OF_STRUCT","FILE","SECTION","WEAK_EXTERNAL"
};

/* Bitfield values and names for the IMAGE_SECTION_HEADER flags */

static DWORD_FLAG_DESCRIPTIONS SectionCharacteristics[] = 
{
  { IMAGE_SCN_CNT_CODE, "CODE" },
  { IMAGE_SCN_CNT_INITIALIZED_DATA, "INITIALIZED_DATA" },
  { IMAGE_SCN_CNT_UNINITIALIZED_DATA, "UNINITIALIZED_DATA" },
  { IMAGE_SCN_LNK_INFO, "LNK_INFO" },
  /* { IMAGE_SCN_LNK_OVERLAY, "LNK_OVERLAY" }, */
  { IMAGE_SCN_LNK_REMOVE, "LNK_REMOVE" },
  { IMAGE_SCN_LNK_COMDAT, "LNK_COMDAT" },
  { IMAGE_SCN_MEM_DISCARDABLE, "MEM_DISCARDABLE" },
  { IMAGE_SCN_MEM_NOT_CACHED, "MEM_NOT_CACHED" },
  { IMAGE_SCN_MEM_NOT_PAGED, "MEM_NOT_PAGED" },
  { IMAGE_SCN_MEM_SHARED, "MEM_SHARED" },
  { IMAGE_SCN_MEM_EXECUTE, "MEM_EXECUTE" },
  { IMAGE_SCN_MEM_READ, "MEM_READ" },
  { IMAGE_SCN_MEM_WRITE, "MEM_WRITE" },
};

static PIMAGE_SYMBOL PCOFFSymbolTable = 0;
static DWORD COFFSymbolCount = 0;
static PIMAGE_COFF_SYMBOLS_HEADER PCOFFDebugInfo = 0;

static void DumpSectionTable(labeltable *table,
			     PIMAGE_SECTION_HEADER section,
			     unsigned cSections,
			     BOOL IsEXE)
{
    unsigned i, j;
    table->textSectionNumber = -1;

    for ( i=1; i <= cSections; i++, section++ )
    {
      if (strcmp(section->Name,TEXTSECTIONNAME)==0) {
	table->textSectionNumber = i;
	break;
      }
    }
    if (table->textSectionNumber==-1) {
      fprintf(stderr,"Warning! nm(DumpSectionTable): Couldn't find section number of %s\n",TEXTSECTIONNAME);
      table->textSectionNumber = DEFAULTTEXTSECTIONNUMBER;
    }
}

static void DumpExeFile(labeltable *table, PIMAGE_DOS_HEADER dosHeader) {
  PIMAGE_NT_HEADERS pNTHeader;
  DWORD base = (DWORD)dosHeader;
  
  pNTHeader = MakePtr( PIMAGE_NT_HEADERS, dosHeader,
		       dosHeader->e_lfanew );
  
  /* First, verify that the e_lfanew field gave us a reasonable */
  /* pointer, then verify the PE signature. */
#ifndef nti_gnu
  __try
    {
      if ( pNTHeader->Signature != IMAGE_NT_SIGNATURE )
        {
	  fprintf(stderr,"Not a Portable Executable (PE) EXE\n");
	  return;
        }
    }
  __except( TRUE )    /* Should only get here if pNTHeader (above) is bogus */
    {
      fprintf(stderr,"invalid .EXE\n");
      return;
    }
#else
      if ( pNTHeader->Signature != IMAGE_NT_SIGNATURE )
        {
	  fprintf(stderr,"Not a Portable Executable (PE) EXE\n");
	  return;
        }

#endif /* nt_gnu */  

  DumpSectionTable( table,
		    IMAGE_FIRST_SECTION(pNTHeader), 
		    pNTHeader->FileHeader.NumberOfSections, TRUE);

  /*
   * Initialize these vars here since we'll need them in DumpLineNumbers
   */
  
  PCOFFSymbolTable = MakePtr(PIMAGE_SYMBOL, base,
			     pNTHeader->FileHeader.PointerToSymbolTable);
  COFFSymbolCount = pNTHeader->FileHeader.NumberOfSymbols;
  
  if ( pNTHeader->FileHeader.NumberOfSymbols 
       && pNTHeader->FileHeader.PointerToSymbolTable) {
    DumpSymbolTable(table,PCOFFSymbolTable, COFFSymbolCount);
    fprintf(table->fd,"\n");
  }
}

static void DumpFile(labeltable *table, LPSTR filename) {
  HANDLE hFile;
  HANDLE hFileMapping;
  LPVOID lpFileBase;
  PIMAGE_DOS_HEADER dosHeader;
  
  hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		     OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  
  if ( hFile == INVALID_HANDLE_VALUE ) {
    fprintf(stderr,"Couldn't open file with CreateFile()\n");
    return;
  }

  hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
  if ( hFileMapping == 0 ) {
    CloseHandle(hFile);
    fprintf(stderr,"Couldn't open file mapping with CreateFileMapping()\n");
    return;
  }

  lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
  if ( lpFileBase == 0 ) {
    CloseHandle(hFileMapping);
    CloseHandle(hFile);
    fprintf(stderr,"Couldn't map view of file with MapViewOfFile()\n");
    return;
  }

  dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
  if ( dosHeader->e_magic == IMAGE_DOS_SIGNATURE ) {
    DumpExeFile(table, dosHeader );
  }
  else if ( (dosHeader->e_magic == IMAGE_DBG_SIGNATURE) && 
	    (dosHeader->e_cblp == 0) ) {
    fprintf(stderr,"DumpFile: DumpDbgFile not implemented\n");
  } else if ( (dosHeader->e_magic == 0x014C)    /*  Does it look like a i386 */
              && (dosHeader->e_sp == 0) ) {      /*  COFF OBJ file??? */
    /*  The two tests above aren't what they look like.  They're */
    /*  really checking for IMAGE_FILE_HEADER.Machine == i386 (0x14C) */
    /*  and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0; */
    fprintf(stderr,"DumpFile: DumpObjFile not implemented\n");
  } else if ( 0 == strncmp(lpFileBase, IMAGE_ARCHIVE_START,
			   IMAGE_ARCHIVE_START_SIZE ) ) {
    fprintf(stderr,"DumpFile: DumpLibFile not implemented\n");
  } else
    fprintf(stderr,"unrecognized file format\n");
  
  UnmapViewOfFile(lpFileBase);
  CloseHandle(hFileMapping);
  CloseHandle(hFile);
}

#define SECTION_CONDITION \
 ((!table->full) && pSymbolTable->SectionNumber == table->textSectionNumber) \
 || 1

static void DumpSymbolTable(labeltable *table, 
			    PIMAGE_SYMBOL pSymbolTable,
			    unsigned cSymbols) {
  unsigned i;
  PSTR stringTable;
  char sectionName[10];
  
  /* The string table apparently starts right after the symbol table */
  stringTable = (PSTR)&pSymbolTable[cSymbols]; 
  
  for ( i=0; i < cSymbols; i++ ) {
    if (SECTION_CONDITION) {
      if (SzStorageClass1[2]==GetSZStorageClass(pSymbolTable->StorageClass)) {
	
	/* this symbol passed */
	sprintf(sectionName,"N"); /* Identification really don't matter for BETA */
	if (pSymbolTable) {
	  fprintf(table->fd,"%08X", pSymbolTable->Value);
	} else 
	  fprintf(stderr,"DumpSymbolTable (i=%d) pSymbolTable is NULL\n", pSymbolTable->Value);
	fprintf(table->fd," %s ", sectionName);
	if ( pSymbolTable->N.Name.Short != 0 )
	  fprintf(table->fd,"%-20.8s", pSymbolTable->N.ShortName);
	else
	  fprintf(table->fd,"%-20s", stringTable + pSymbolTable->N.Name.Long);
	fprintf(table->fd,"\n");
      }
    }
    /* Take into account any aux symbols */
    i += pSymbolTable->NumberOfAuxSymbols;
    pSymbolTable += pSymbolTable->NumberOfAuxSymbols;
    pSymbolTable++;
  }
}

static PSTR GetSZStorageClass(BYTE storageClass) {
  if ( storageClass <= IMAGE_SYM_CLASS_BIT_FIELD )
      return SzStorageClass1[storageClass];
  else if ( (storageClass >= IMAGE_SYM_CLASS_BLOCK)
              && (storageClass <= IMAGE_SYM_CLASS_WEAK_EXTERNAL) )
    return SzStorageClass2[storageClass-IMAGE_SYM_CLASS_BLOCK];
  else
    return "???";
}

static void GetSectionName(WORD section, PSTR buffer, unsigned cbBuffer) {
  char tempbuffer[10];
  
  switch ( (SHORT)section ) {
  case IMAGE_SYM_UNDEFINED: strcpy(tempbuffer, "U"); break;
  case IMAGE_SYM_ABSOLUTE:  strcpy(tempbuffer, "A"); break;
  case IMAGE_SYM_DEBUG:     strcpy(tempbuffer, "d"); break;
  default: sprintf(tempbuffer, "%-5X", section);
  }
  strncpy(buffer, tempbuffer, cbBuffer-1);
};

#endif /* nti */

#endif /* ppcmac */
