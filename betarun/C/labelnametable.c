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

#undef TRACE
#if 0
#define TRACE(msg) fprintf(stdout, "%s\n", msg); fflush(stdout);
#define TRACEX(msg,x) fprintf(stdout, "%s: 0x%x\n", msg, (int)x); fflush(stdout);
#define TRACES(msg,s) fprintf(stdout, "%s: %s\n", msg, s); fflush(stdout);
#define STATIC
#else
#define TRACE(msg)
#define TRACEX(msg,x)
#define TRACES(msg,s)
#define STATIC static
#endif

#ifdef nti_gnu

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
#define pclose(fp) fclose(fp); unlink(NMOUTFILE) /* ; fprintf(output,"Close & deleting %s\n",NMOUTFILE)*/
STATIC void DumpFile(labeltable *table, LPSTR filename);
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
	TRACE("pclose");
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
  labeltable *table;

  TRACES("initReadNameTable", execFileName);

#ifdef ppcmac
  return 0;
  
#else

  table = (labeltable*)MALLOC(sizeof(labeltable));
  if (!table){
    fprintf(output,"couldn't malloc label table for file %s\n", execFileName); 
    return 0;
  }
  /* clear whole table struct */
  memset (table, 0, sizeof(labeltable));
  table->full = full;

#ifndef nti 
  /* ! nti */
  if (full){
    TRACES(FULL_NMCOMMAND, execFileName);
    sprintf (command,FULL_NMCOMMAND,execFileName);
  } else {
    TRACES(TERSE_NMCOMMAND, execFileName);
    sprintf (command,TERSE_NMCOMMAND,execFileName);
  }
  TRACE("popen");
  table->fp = popen(command, "r");
#else /* nti */

  TRACES("Opening", NMOUTFILE);
  if ((table->fp = fopen(NMOUTFILE,"w+"))==NULL) {
    fprintf(output,"couldn't open file %s\n",NMOUTFILE); 
    FREE(table);
    return 0;
  }
  /* run "nm" */
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
STATIC PSTR GetSZStorageClass(BYTE storageClass);
STATIC void DumpSymbolTable(labeltable *table,
			    PIMAGE_SYMBOL pSymbolTable, 
			    unsigned cSymbols);
STATIC void DumpSectionTable(labeltable *table,
			     PIMAGE_SECTION_HEADER section,
			     unsigned cSections);
STATIC int indirectstrcmp(const char **s1, const char **s2);

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
STATIC PSTR SzStorageClass1[] = {
  "NULL","AUTOMATIC","EXTERNAL","STATIC","REGISTER","EXTERNAL_DEF","LABEL",
  "UNDEFINED_LABEL","MEMBER_OF_STRUCT","ARGUMENT","STRUCT_TAG",
  "MEMBER_OF_UNION","UNION_TAG","TYPE_DEFINITION","UNDEFINED_STATIC",
  "ENUM_TAG","MEMBER_OF_ENUM","REGISTER_PARAM","BIT_FIELD"
};

/* The names of the second group of possible symbol table storage classes */
STATIC char * SzStorageClass2[] = {
  "BLOCK","FUNCTION","END_OF_STRUCT","FILE","SECTION","WEAK_EXTERNAL"
};

STATIC void DumpSectionTable(labeltable *table,
			     PIMAGE_SECTION_HEADER section,
			     unsigned cSections)
{
    unsigned i;

    TRACE("DumpSectionTable");

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

STATIC void DumpExeFile(labeltable *table, PIMAGE_DOS_HEADER dosHeader) {
  PIMAGE_NT_HEADERS pNTHeader;
  DWORD base = (DWORD)dosHeader;
  int i;
  
  TRACE("DumpExeFile");

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
  for (i = 0; i < table->name_count; i++){
    /*fprintf(output, "Writing to NMOUTFILE: %s\n", table->names[i]);*/
    fprintf(table->fp, "%s\n", table->names[i]);
  }
}

STATIC void DumpFile(labeltable *table, LPSTR filename) {
  HANDLE hFile;
  HANDLE hFileMapping;
  LPVOID lpFileBase;
  PIMAGE_DOS_HEADER dosHeader;

  TRACE("DumpFile");
  
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

#if 0 
#define SECTION_CONDITION \
 ((!table->full) && (DWORD)pSymbolTable->SectionNumber == table->textSectionNumber)
#else
/* We need to consider all sections for dynamic link */
#define SECTION_CONDITION 1
#endif

STATIC void DumpSymbolTable(labeltable *table, 
			    PIMAGE_SYMBOL pSymbolTable,
			    unsigned cSymbols) {
  unsigned i;
  PSTR stringTable;
  
  TRACEX("DumpSymbolTable", pSymbolTable);

#ifdef nti_gnu
  /* The string table apparently starts right after the symbol table */
  /* Due to packing problems on gcc (18 byte long struct) we don't do this the simple way  -EC */
  stringTable = ((PSTR)pSymbolTable) + IMAGE_SIZEOF_SYMBOL * cSymbols;
#else
  stringTable = (PSTR)&pSymbolTable[cSymbols];
#endif
  
  for (i=0; i < cSymbols; i++) {
    TRACEX("Symbol#", i);
    if (SECTION_CONDITION) {
      TRACE("  condition OK");
      TRACEX("  Outside: pSymbolTable now", pSymbolTable);
      if (SzStorageClass1[2]==GetSZStorageClass(pSymbolTable->StorageClass)) {
	long space_needed = 0;
	TRACEX("  Inside: pSymbolTable now", pSymbolTable);
	if (table->name_count >= table->name_space) {
	  int old_size = table->name_space; 
	  int new_size = (old_size==0) ? 1024 : old_size*2;
	  int old, new;
          PSTR *new_names;

	  TRACEX("Allocation of table->names. Old size", old_size);
	  TRACEX("Allocation of table->names. New size", new_size);
	  new_names = MALLOC(new_size * sizeof(char *));
	  for (old = 0; old < old_size; old++){
	    new_names[old] = table->names[old];
	  }
	  for (new = old_size ; new < new_size; new++){
	    new_names[new] = NULL;
	  }
	  if (table->names){
	    TRACE("Free old table->names");
	    FREE(table->names);
	  }
          table->names = new_names;
	  table->name_space = new_size;
	}

	if (!pSymbolTable){
	  TRACE("pSymbolTable is NULL");
	  fprintf(output,"DumpSymbolTable (i=%ld) pSymbolTable is NULL\n", pSymbolTable->Value);
	  break;
	}
        /* Strings in C really suck rocks through a straw!  I need 8 for
	 * the address, 3 for the " N ", 1 for the null, 2 for luck.  If you
	 * change this don't forget both +11's a few lines down.
	 */
	space_needed = 14 + (pSymbolTable->N.Name.Short ?  8 :
	                     strlen(stringTable + pSymbolTable->N.Name.Long));
	TRACEX("space_needed", space_needed);
	TRACEX("table->name_buffer_space", table->name_buffer_space);

	if (space_needed > table->name_buffer_space) {
	  int new_size = (space_needed > 20000) ? space_needed : 20000;
	  TRACEX("Allocation of table->name_buffer", new_size);
#if 0
	  /* Dont free! There are pointers into the old block(s) */
	  /* Yes I know it's a leak... */
	  if (table->name_buffer){
	    TRACE("Free old table->name_buffer");
	    FREE(table->name_buffer);
	  }
#endif
	  table->name_buffer = MALLOC(new_size);
	  if (!table->name_buffer) {
	    fprintf(output, "Malloc of name_buffer failed\n");
	    TRACE("Malloc of name_buffer failed");
	    break;
	  }
	  table->name_buffer_space = new_size;
	}

	/* this symbol passed */
	TRACE("  Symbol passed");
	TRACEX("  pSymbolTable now", pSymbolTable);
	TRACEX("  value", pSymbolTable->Value);
	TRACEX("  value->name_buffer", table->name_buffer);
	sprintf(table->name_buffer,"%08lX N ", pSymbolTable->Value);
	if ( pSymbolTable->N.Name.Short != 0 ){
	  TRACE("Short name");
	  memcpy(table->name_buffer+11,
                 (const char *)&(pSymbolTable->N.ShortName), 8);
	  table->name_buffer[19] = 0;
	  TRACES("  name (short)", table->name_buffer+11);
	  if (!table->main_logical){
	    if (strncmp((const char *)pSymbolTable->N.ShortName, "_main", 8)==0){
	      TRACEX("MAIN found (short)", pSymbolTable->Value);
	      table->main_logical = pSymbolTable->Value;
	    }
	  }
	} else {
	  /* Not a short name */
	  TRACE("Long name");
	  sprintf(table->name_buffer+11, "%s%c",
	          stringTable + pSymbolTable->N.Name.Long, 0);
	  TRACES("  name (long)", table->name_buffer+11);
	  if (!table->main_logical){
	    if (strcmp(stringTable + pSymbolTable->N.Name.Long, "_main")==0){
	      TRACEX("MAIN found (long)", pSymbolTable->Value);
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
    if (pSymbolTable->NumberOfAuxSymbols>0){
      TRACEX("Skip aux", pSymbolTable->NumberOfAuxSymbols);
      i += pSymbolTable->NumberOfAuxSymbols;
    }
#ifdef nti_gnu
    /* Due to packing problems on gcc (18 byte long struct) we don't do this the simple way  -EC */
    pSymbolTable = (PIMAGE_SYMBOL)((char *)pSymbolTable + IMAGE_SIZEOF_SYMBOL * (pSymbolTable->NumberOfAuxSymbols + 1));
#else
    pSymbolTable += pSymbolTable->NumberOfAuxSymbols + 1;
#endif
  }

  TRACE("DumpSymbolTable end");

}

STATIC PSTR GetSZStorageClass(BYTE storageClass) {
  if ( storageClass <= IMAGE_SYM_CLASS_BIT_FIELD )
      return SzStorageClass1[storageClass];
  else if ( (storageClass >= IMAGE_SYM_CLASS_BLOCK)
              && (storageClass <= IMAGE_SYM_CLASS_WEAK_EXTERNAL) )
    return SzStorageClass2[storageClass-IMAGE_SYM_CLASS_BLOCK];
  else
    return "???";
}

STATIC int indirectstrcmp(const char **s1, const char **s2)
{
  return strcmp(*s1, *s2);
}

#endif /* nti */
