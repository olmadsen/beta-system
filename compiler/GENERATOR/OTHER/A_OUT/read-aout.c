#include <stdio.h>
#include <a.out.h>
#include <stab.h>

extern char *sparc_disass(unsigned int instr);

struct exec header;
FILE 	*fd;
char *strings=0;
int stringsize=0;

int show_data=0, show_text=0;

void print_header()
{ if ( fread(&header, sizeof(struct exec), 1, fd)==0 ){
    fprintf(stderr, "Failed to read a.out header\n");
    exit(1);
  }

  printf("a_dynamic:     0x%x\n", header.a_dynamic);     
  printf("a_toolversion: 0x%x\n", header.a_toolversion);
  printf("a_machtype:    0x%x ", header.a_machtype);     /* machine type */
  switch(header.a_machtype){
    case 0: printf("(Pre 3.0)\n"); break;
    case M_68010: printf("(M_68010)\n"); break;
    case M_68020: printf("(M_68020)\n"); break;
    case M_SPARC: printf("(M_SPARC)\n"); break;
    default: printf("(unknown)\n"); break;
  }
  printf("a_magic:       0x%x ", header.a_magic);        /* magic number */
  switch(header.a_magic){
  case OMAGIC: printf("(OMAGIC)\n"); break;
  case NMAGIC: printf("(NMAGIC)\n"); break;
  case ZMAGIC: printf("(ZMAGIC)\n"); break;
  default: printf("(unknown)\n"); break;
  }
  printf("a_text:        0x%x\n", header.a_text);        /* size of text segment */
  printf("a_data:        0x%x\n", header.a_data);        /* size of initialized data */
  printf("a_bss:         0x%x\n", header.a_bss);         /* size of uninitialized data */
  printf("a_syms:        0x%x\n", header.a_syms);        /* size of symbol table */
  printf("a_entry:       0x%x\n", header.a_entry);       /* entry point */
  printf("a_trsize:      0x%x\n", header.a_trsize);      /* size of text relocation */
  printf("a_drsize:      0x%x\n", header.a_drsize);      /* size of data relocation */ 
}

void print_text()
{ int i;
  char *nm;
  unsigned long instr;
  for (i=0; i<header.a_text; i+=4){
    if ( fread(&instr, sizeof(unsigned long), 1, fd)==0 ){
      fprintf(stderr, "Failed to read instruction\n");
      exit(1);
    }
    printf("0x%08x: 0x%08x", i, instr);
    nm = sparc_disass(instr);
    printf("\t%s\n", nm);
  }
}

void print_char(unsigned char ch)
{
  if ((' ' <= ch) && (ch <= '~')){
    putc(ch, stdout);
  } else {
    putc(' ', stdout);
  }
}

void print_data()
{ int i;
  union {
    unsigned long raw;
    unsigned char bytes[4];
  } word;
  for (i=0; i<header.a_data; i+=4){
    if ( fread(&word.raw, sizeof(unsigned long), 1, fd)==0 ){
      fprintf(stderr, "Failed to read data word\n");
      exit(1);
    }
    printf("0x%08x: 0x%08x\t\"", i, word.raw);
    print_char(word.bytes[0]);
    print_char(word.bytes[1]);
    print_char(word.bytes[2]);
    print_char(word.bytes[3]);
    printf("\"\n");
  }
  printf("\n");
}
void print_nlists()
{
  struct nlist nlist;
  int i;

  for (i=0; i < (header.a_syms/sizeof(struct nlist)); i++){
    
    if ( fread(&nlist, sizeof(struct nlist), 1, fd)==0 ){
      fprintf(stderr, "Failed to read nlist entry\n");
      exit(1);
    }

    printf("\n[%d]", i);
    printf("\tn_strx:  0x%x", nlist.n_un.n_strx);
    printf(" (%s)\n", &strings[nlist.n_un.n_strx-4]);
    printf("\tn_type:  0x%x ", nlist.n_type);
    switch(nlist.n_type & N_TYPE){
    case N_UNDF: printf("(N_UNDF)"); break;
    case N_ABS: printf("(N_ABS)"); break;
    case N_TEXT: printf("(N_TEXT)"); break;
    case N_DATA: printf("(N_DATA)"); break;
    case N_BSS: printf("(N_BSS)"); break;
    case N_COMM: printf("(N_COMM)"); break;
    case N_FN: printf("(N_FN)"); break;
    default: printf("(unknown)"); break;
    }
    if (nlist.n_type & N_EXT) printf(" (external)");
    printf("\n");

    printf("\tn_other: 0x%x\n", nlist.n_other);
    printf("\tn_desc:  0x%x\n", nlist.n_desc);
    printf("\tn_value: 0x%x\n", nlist.n_value);

  }
}

void print_reloc(int num)
{
  struct reloc_info_sparc reloc;
  int i;

  for (i=0; i < num; i++){
    if ( fread(&reloc, sizeof(struct reloc_info_sparc), 1, fd)==0 ){
      fprintf(stderr, "Failed to read relocation entry\n");
      exit(1);
    }

    printf("\n[%d]", i);
    printf("\tr_address:  0x%x\n", reloc.r_address);
    printf("\tr_index:    0x%x\n", reloc.r_index);
    printf("\tr_extern:   0x%x\n", reloc.r_extern);
    printf("\tr_type:     0x%x ", reloc.r_type);
    switch(reloc.r_type){
    case RELOC_DISP8: printf("(RELOC_DISP8)"); break;
    case RELOC_DISP16: printf("(RELOC_DISP8)"); break;
    case RELOC_DISP32: printf("(RELOC_DISP32)"); break;
    case RELOC_WDISP30: printf("(RELOC_WDISP30)"); break;
    case RELOC_WDISP22: printf("(RELOC_WDISP22)"); break;
    case RELOC_HI22: printf("(RELOC_HI22)"); break;
    case RELOC_22: printf("(RELOC_22)"); break;
    case RELOC_13: printf("(RELOC_13)"); break;
    case RELOC_LO10: printf("(RELOC_LO10)"); break;
    case RELOC_SFA_BASE: printf("(RELOC_SFA_BASE)"); break;
    case RELOC_SFA_OFF13: printf("(RELOC_SFA_OFF13)"); break;
    case RELOC_BASE10: printf("(RELOC_BASE10)"); break;
    case RELOC_BASE13: printf("(RELOC_BASE13)"); break;
    case RELOC_BASE22: printf("(RELOC_BASE22)"); break;
    case RELOC_PC10: printf("(RELOC_PC10)"); break;
    case RELOC_PC22: printf("(RELOC_PC22)"); break;
    case RELOC_JMP_TBL: printf("(RELOC_JMP_TBL)"); break;
    case RELOC_SEGOFF16: printf("(RELOC_SEGOFF16)"); break;
    case RELOC_GLOB_DAT: printf("(RELOC_GLOB_DAT)"); break;
    case RELOC_JMP_SLOT: printf("(RELOC_JMP_SLOT)"); break;
    case RELOC_RELATIVE: printf("(RELOC_RELATIVE)"); break;
    default: printf("(unknown)"); break;
    }
    printf("\n");
    printf("\tr_addend:   0x%x\n", reloc.r_addend);
  }
}


void read_strings()
{ 
  fseek(fd, N_STROFF(header), 0);
  if ( fread(&stringsize, 4, 1, fd)==0 ){
    fprintf(stderr, "Failed to read size of string table\n");
    exit(1);
  }
  stringsize-=4;
  if (stringsize>0){
    strings=(char *)malloc(stringsize);
    if ( fread(strings, 1, stringsize, fd)==0 ){
      fprintf(stderr, "Failed to read string table\n");
      exit(1);
    }
  }
}

void usage(char * progname)
{
  fprintf(stderr, "Usage: %s [ -d ] [ -t ] aout-file\n", progname);
  fprintf(stderr, "   -d: include data segment printout\n");
  fprintf(stderr, "   -t: include text segment printout\n");
  exit(1);
}


void print_strings()
{
  int i, new=1;
  if (stringsize>0){
    for (i=0; i<stringsize; i++){
      if (new) { new=0; printf("\n0x%x:\t", i+4); }
      if (strings[i]!=NULL){
	putc(strings[i], stdout);
      } else {
	new=1;
      }
    }
    printf("\n\n");
  }
}

void main(argc,argv)
     int	argc;
     char	*argv[];
{

  char c, *prog = argv[0];

  /* Process command-line arguments */
  while (--argc > 0 && (*++argv)[0] == '-') /* walk through arguments */
    while (c = *++(argv[0])) /* walk through current option */
      switch (c) {
      case 't':
        show_text=1;
        break;
      case 'd':
        show_data=1;
        break;
      default:
        fprintf(stderr, "%s: illegal option %c\n", prog, c);
        argc = 0;
        break;
      }
  if (argc != 1) usage(prog);

  fd = fopen(*argv, "r");
  if (fd == 0) {
    fprintf(stderr, "Failed to open %s\n", *argv);
    exit(1);
  }

  printf("\n    ***** Header (struct exec) *****\n\n");
  print_header();

  read_strings();

  if (show_text) {
    printf("\n    ***** Text segment *****\n\n");
    fseek(fd, N_TXTOFF(header), 0);
    print_text();
  }

  if (show_data){
    printf("\n    ***** Data segment *****\n\n");
    fseek(fd, N_DATOFF(header), 0);
    print_data();
  }

  printf("\n    ***** Text relocation entries *****\n\n");
  fseek(fd, N_TRELOFF(header), 0);
  print_reloc(header.a_trsize/sizeof(struct reloc_info_sparc));
  
  printf("\n    ***** Data relocation entries *****\n\n");
  fseek(fd, N_DRELOFF(header), 0);
  print_reloc(header.a_drsize/sizeof(struct reloc_info_sparc));

  printf("\n    ***** Symbol table *****\n\n");
  fseek(fd, N_SYMOFF(header), 0);
  print_nlists();

  printf("\n    ***** String table *****\n\n");
  print_strings();

}
