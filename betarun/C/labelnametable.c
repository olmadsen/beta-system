/* labelnametable.c
 *
 * Provides support for reading code labels from the nametable of an 
 * executable file.
 *
 * Sets up a fp to nm output and reads the nametable from this file pointer.
 * 
 * This file is used by
 *   - debugger 
 *   - dynamic linker.
 *   - betarun debug labels
 * The debugger needs only the text (code) labels, whereas the dynamic
 * linker and betarun needs most symbols.
 */


#ifdef nti_gnu
#  include "winntdef.h"

void unlink(const char *name);

#endif /* nti_gnu */

#include "beta.h"

#ifdef sgi
#define FULL_NMCOMMAND  "/bin/nm -Bhvp %s"
#define TERSE_NMCOMMAND "/bin/nm -Bhvp %s"
#define Decimal
#endif

#ifdef sparc
#define FULL_NMCOMMAND  "/usr/ccs/bin/nm -hvp %s"
#define TERSE_NMCOMMAND "/usr/ccs/bin/nm -hvp %s"
#define Decimal
#endif

#ifdef hppa
#define FULL_NMCOMMAND  "/bin/nm -hp %s | sort"
#define TERSE_NMCOMMAND "/bin/nm -hp %s | grep ' T ' | sort"
#define Decimal
#endif

#ifdef linux
#define FULL_NMCOMMAND  "nm -Bv -td %s | grep -v ' U '"
#define TERSE_NMCOMMAND "nm -Bv -td %s | grep -v ' U '"
#define Decimal
#endif

#ifdef ppcmac
#define FULL_NMCOMMAND  "not yet implemented"
#define TERSE_NMCOMMAND "not yet implemented"
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
#undef pclose
#define pclose(fp) fclose(fp); /* unlink(NMOUTFILE) / * ; fprintf(output,"Close & deleting %s\n",NMOUTFILE)*/
static void DumpFile(labeltable *table, LPSTR filename);
#endif /* nti */

void findNextLabel (labeltable *table)
{ 
  int type;
  int ch;
  int inx,val;

#ifdef ppcmac
  return;
#endif

  while (1) {
    table->NextAddress=0;
    while ((ch=fgetc (table->fp))!=' ') {
      if (ch==EOF) {
	table->NextAddress = -1; /* datpete 14/3/96: changed from 0 */
	pclose (table->fp);
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

    while ((ch=fgetc (table->fp))==' ') {
      ;
    }

    type = ch;

    if (!table->full){
      if ((type != 'N') && (type != 'T')) {
	while (fgetc (table->fp) != '\n') {
	  continue;
	}
	continue;
      }
    }
    
    fgetc (table->fp);
    
    inx=0;
    while ((ch = fgetc(table->fp))!='\n') {
      if (ch == ' ') {
	/* Skipping blanks */
	;
      } else if (ch == EOF)  {
	/* Error */
	table->NextAddress = -1; 
	pclose (table->fp);
	return;
      } else {
	if (inx < MAXLABLELENGTH - 1) {
	  table->NextLabel[inx++]=ch;
	} else {
	  break;
	}
      }
    }
    table->NextLabel[inx] = 0;
    return;
  }
}

labeltable *initReadNameTable (char* execFileName, int full)
{ 
#ifndef nti
  char command[100];
#endif /* nti */

  labeltable *table = (labeltable*)MALLOC(sizeof(labeltable));

#ifdef ppcmac
  return 0;
  
#else

  if (!table){
    fprintf(output,"couldn't malloc label table for file %s\n", execFileName); 
    return 0;
  }
  table->full = full;

#ifndef nti 
  /* ! nti */
  if (full){
    sprintf (command,FULL_NMCOMMAND,execFileName);
  } else {
    sprintf (command,TERSE_NMCOMMAND,execFileName);
  }
  table->fp = popen(command, "r");
#else /* nti */
  table->main_logical=0;
  table->textSectionNumber=0;
  table->PCOFFSymbolTable=0;
  table->COFFSymbolCount=0;
  table->name_buffer = NULL;
  table->name_space = 0;
  table->name_count = 0;
  table->names = NULL;

  /*fprintf(output,"Opening %s\n",NMOUTFILE);*/
  if ((table->fp = fopen(NMOUTFILE,"w+"))==NULL) {
    fprintf(output,"couldn't open file %s\n",NMOUTFILE); 
    FREE(table);
    return 0;
  }
  /* run nm */
  DumpFile(table, execFileName );
  fclose (table->fp);
  if ((table->fp = fopen(NMOUTFILE,"r"))==NULL) {
    fprintf(output,"couldn't open file %s\n",NMOUTFILE); 
    FREE(table);
    return 0;
  }
#endif /* nti */

  return table;
#endif /* ppcmac */
}

void freeNameTable(labeltable *handle)
{
  if (handle) FREE(handle);
}

#ifdef nti
long getProcessOffset(labeltable *table, long main_physical)
{
  if (table && table->main_logical) {
    return main_physical - table->main_logical;
  } else {
    return -1;
  }
}
#endif /* nti */

long getMainPhysical(void)
{
  extern void main(void);
  return (long)&main;
}

int nextAddress(labeltable *table) 
{ 

#ifdef ppcmac
  return -1;
#endif

  findNextLabel(table);
  /*fprintf(output, "nextAddress: 0x%x\n", table->NextAddress); fflush(output);*/
  return table->NextAddress;
}

char* nextLabel(labeltable *table) 
{ 
#ifdef ppcmac
  return 0;
#endif

  /*fprintf(output, "nextLabel: %s\n", table->NextLabel); fflush(output);*/
  return table->NextLabel;
}

#ifdef nti
/* Implements 'nm' like behaviour for nti */
static PSTR GetSZStorageClass(BYTE storageClass);
static void DumpSymbolTable(labeltable *table,
			    PIMAGE_SYMBOL pSymbolTable, 
			    unsigned cSymbols);
static void DumpSectionTable(labeltable *table,
			     PIMAGE_SECTION_HEADER section,
			     unsigned cSections);
static int indirectstrcmp(const char **s1, const char **s2);

typedef struct
{
    DWORD   flag;
    PSTR    name;
} DWORD_FLAG_DESCRIPTIONS;

#define DEFAULTTEXTSECTIONNUMBER 1
#define TEXTSECTIONNAME ".text"

#define IMAGE_DBG_SIGNATURE     0x00004944
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (DWORD)(addValue))

/* The names of the first group of possible symbol table storage classes */
static PSTR SzStorageClass1[] = {
  "NULL","AUTOMATIC","EXTERNAL","STATIC","REGISTER","EXTERNAL_DEF","LABEL",
  "UNDEFINED_LABEL","MEMBER_OF_STRUCT","ARGUMENT","STRUCT_TAG",
  "MEMBER_OF_UNION","UNION_TAG","TYPE_DEFINITION","UNDEFINED_STATIC",
  "ENUM_TAG","MEMBER_OF_ENUM","REGISTER_PARAM","BIT_FIELD"
};

/* The names of the second group of possible symbol table storage classes */
static char * SzStorageClass2[] = {
  "BLOCK","FUNCTION","END_OF_STRUCT","FILE","SECTION","WEAK_EXTERNAL"
};

static void DumpSectionTable(labeltable *table,
			     PIMAGE_SECTION_HEADER section,
			     unsigned cSections)
{
    unsigned i;
    table->textSectionNumber = (DWORD)-1;

    for ( i=1; i <= cSections; i++, section++ )
    {
      if (strcmp((const char *)section->Name,TEXTSECTIONNAME)==0) {
	table->textSectionNumber = (DWORD)i;
	break;
      }
    }
    if (table->textSectionNumber==(DWORD)-1) {
      fprintf(output,"Warning! nm(DumpSectionTable): Couldn't find section number of %s\n",TEXTSECTIONNAME);
      table->textSectionNumber = (DWORD)DEFAULTTEXTSECTIONNUMBER;
    }
}

static void DumpExeFile(labeltable *table, PIMAGE_DOS_HEADER dosHeader) {
  PIMAGE_NT_HEADERS pNTHeader;
  DWORD base = (DWORD)dosHeader;
  int i;
  
  pNTHeader = MakePtr( PIMAGE_NT_HEADERS, dosHeader,
		       dosHeader->e_lfanew );

  
  /* First, verify that the e_lfanew field gave us a reasonable */
  /* pointer, then verify the PE signature. */
#ifndef nti_gnu
  __try
    {
      if ( pNTHeader->Signature != IMAGE_NT_SIGNATURE )
        {
	  fprintf(output,"Not a Portable Executable (PE) EXE\n");
	  return;
        }
    }
  __except( TRUE )    /* Should only get here if pNTHeader (above) is bogus */
    {
      fprintf(output,"invalid .EXE\n");
      return;
    }
#else
      if ( pNTHeader->Signature != IMAGE_NT_SIGNATURE )
        {
	  fprintf(output,"Not a Portable Executable (PE) EXE\n");
	  return;
        }

#endif /* nt_gnu */  

  DumpSectionTable( table,
		    IMAGE_FIRST_SECTION(pNTHeader), 
		    pNTHeader->FileHeader.NumberOfSections);

  /*
   * Initialize these vars here since we'll need them in DumpLineNumbers
   */
  
  table->PCOFFSymbolTable = 
    MakePtr(PIMAGE_SYMBOL, base, pNTHeader->FileHeader.PointerToSymbolTable);
  table->COFFSymbolCount = pNTHeader->FileHeader.NumberOfSymbols;
  
  if ( pNTHeader->FileHeader.NumberOfSymbols 
       && pNTHeader->FileHeader.PointerToSymbolTable) {
    DumpSymbolTable(table,table->PCOFFSymbolTable, table->COFFSymbolCount);
  }

  qsort(table->names, table->name_count, sizeof(char *),
        (int (*)(const void *, const void *))indirectstrcmp);
  for (i = 0; i < table->name_count; i++)
    fprintf(table->fp, "%s\n", table->names[i]);
}

static void DumpFile(labeltable *table, LPSTR filename) {
  HANDLE hFile;
  HANDLE hFileMapping;
  LPVOID lpFileBase;
  PIMAGE_DOS_HEADER dosHeader;
  
  hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		     OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  
  if ( hFile == INVALID_HANDLE_VALUE ) {
    fprintf(output,"Couldn't open file with CreateFile(): %s\n", filename);
    return;
  }

  hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
  if ( hFileMapping == 0 ) {
    CloseHandle(hFile);
    fprintf(output,"Couldn't open file mapping with CreateFileMapping()\n");
    return;
  }

  lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
  if ( lpFileBase == 0 ) {
    CloseHandle(hFileMapping);
    CloseHandle(hFile);
    fprintf(output,"Couldn't map view of file with MapViewOfFile()\n");
    return;
  }

  dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
  if ( dosHeader->e_magic == IMAGE_DOS_SIGNATURE ) {
    DumpExeFile(table, dosHeader );
  } else {
    fprintf(output,"lDumpFile: can only dump EXE files\n");
  }

  UnmapViewOfFile(lpFileBase);
  CloseHandle(hFileMapping);
  CloseHandle(hFile);
}

#define SECTION_CONDITION \
 ((!table->full) && (DWORD)pSymbolTable->SectionNumber == table->textSectionNumber) \
 || 1

static void DumpSymbolTable(labeltable *table, 
			    PIMAGE_SYMBOL pSymbolTable,
			    unsigned cSymbols) {
  unsigned i;
  PSTR stringTable;
  
  /* The string table apparently starts right after the symbol table */
  /* Due to packing problems on gcc (18 byte long struct) we don't do this the simple way  -EC */
  /* stringTable = (PSTR)&pSymbolTable[cSymbols]; */
  stringTable = ((PSTR)pSymbolTable) + IMAGE_SIZEOF_SYMBOL * cSymbols;
  
  for (i=0; i < cSymbols; i++) {
    if (SECTION_CONDITION) {
      if (SzStorageClass1[2]==GetSZStorageClass(pSymbolTable->StorageClass)) {
	long space_needed = 0;
	if (table->name_count >= table->name_space) {
	  int new_size = table->name_space;
	  int old;
          PSTR *new_names;

	  new_names = MALLOC((table->name_space * 4 + 15) * sizeof(char *));
	  for (old = 0; old < new_size; old++)
	    new_names[old] = table->names[old];
	  for ( ; new_size < table->name_space * 4 + 15; new_size++)
	    new_names[new_size] = 0;
          table->names = new_names;
	  table->name_space = new_size;
	}

	if (!pSymbolTable)
	  fprintf(output,"DumpSymbolTable (i=%d) pSymbolTable is NULL\n", pSymbolTable->Value);

        /* Strings in C really suck rocks through a straw!  I need 8 for
	 * the address, 3 for the " N ", 1 for the null, 2 for luck.  If you
	 * change this don't forget both +11's a few lines down.
	 */
	space_needed = 14 + (pSymbolTable->N.Name.Short ?  8 :
	                     strlen(stringTable + pSymbolTable->N.Name.Long));

	if (space_needed > table->name_buffer_space) {
	  table->name_buffer = MALLOC(20000);
	  table->name_buffer_space = 20000;
	}

	/* this symbol passed */
	sprintf(table->name_buffer,"%08X N ", pSymbolTable->Value);
	if ( pSymbolTable->N.Name.Short != 0 ){
	  memcpy(table->name_buffer+11,
                 (const char *)&(pSymbolTable->N.ShortName), 8);
	  table->name_buffer[19] = 0;
	  if (!table->main_logical){
	    if (strncmp((const char *)pSymbolTable->N.ShortName, "_main", 8)==0){
	      table->main_logical = pSymbolTable->Value;
	    }
	  }
	} else {
	  sprintf(table->name_buffer+11, "%s%c",
	          stringTable + pSymbolTable->N.Name.Long, 0);
	  if (!table->main_logical){
	    if (strcmp(stringTable + pSymbolTable->N.Name.Long, "_main")==0){
	      table->main_logical = pSymbolTable->Value;
	    }
	  }
	}
	table->names[table->name_count++] = table->name_buffer;
	table->name_buffer_space -= space_needed;
	table->name_buffer += space_needed;
      }
    }
    /* Take into account any aux symbols */
    i += pSymbolTable->NumberOfAuxSymbols;
    /* Due to packing problems on gcc (18 byte long struct) we don't do this the simple way  -EC */
    /* pSymbolTable += pSymbolTable->NumberOfAuxSymbols + 1; */
    pSymbolTable = (PIMAGE_SYMBOL)((char *)pSymbolTable + IMAGE_SIZEOF_SYMBOL * (pSymbolTable->NumberOfAuxSymbols + 1));
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

static int indirectstrcmp(const char **s1, const char **s2)
{
  return strcmp(*s1, *s2);
}

#endif /* nti */
