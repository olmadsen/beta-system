/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * scramble.c
 * by Jacob Seligmann
 */

#include <stdio.h>

/*
 * This program is used to generate scrambled strings for C/initialize.c
 * 
 * Instructions: 
 * 1) Replace SCRAMBLETEMPLATE below with string to be scrambled
 * 2) Compile and run program
 * 3) Incorporate output into SCRAMBLE{STRING,LEN,CHK} below
 * 4) Compile and run program
 * 5) Incorporate output into C/initialize.c
 * Note: Steps 3 and 4 above are not needed, but recommended as verification
 *
 * Scramble algorithm:
 * Simple. Each character is xor'ed with the value of the previous 
 * (scrambled) character, and 41 is added to the result (modulo 256).
 * [The first character is xor'ed with 0.] In addition, the sum of 
 * the unscrambled characters is maintained as a checksum.
 */

#define SCRAMBLETEMPLATE "\n\
**********\n\
SCRAMBLED!\n\
**********\n\
\n"

#define SCRAMBLESTRING {\
0x33, 0x42, 0x91, 0xe4, 0xf7, 0x06, 0x55, 0xa8, 0xab, 0xaa, \
0xa9, 0xcc, 0xc8, 0xb4, 0x0f, 0x77, 0x63, 0x4a, 0x2f, 0x93, \
0x00, 0x4a, 0x69, 0x6c, 0x6f, 0x6e, 0x6d, 0x70, 0x83, 0xd2, \
0x21, 0x34, 0x47, 0x76, 0xa5 }
#define SCRAMBLELEN 35
#define SCRAMBLECHK 1576

void encode(void)
{
  int len, chk;
  unsigned char enc, oldenc, dec;
  unsigned char c, *p;

  printf("Template:\n%s\n", SCRAMBLETEMPLATE);

  printf("Encoding:\n\n");

  printf("#define SCRAMBLESTRING {");
  len = chk = 0;
  enc = dec = 0;
  p = SCRAMBLETEMPLATE;
  while ((c=*p++) != '\0') {
    if (len % 10 == 0)
      printf("\\\n");
    len++;
    oldenc = enc;
    enc = ((c ^ oldenc) + 41);
    dec = ((enc - 41) ^ oldenc);
    if (c != dec) {
      printf("Oops, encoding error!");
      exit(1);
    }
    chk += c;
    printf("0x%02x", enc);
    if (*p != '\0')
      printf(", ");
  }
  printf(" }\n");
  printf("#define SCRAMBLELEN %d\n", len);
  printf("#define SCRAMBLECHK %d\n", chk);
}


void decode(void)
{
  int i, chk;
  unsigned char c, foo[] = SCRAMBLESTRING;
  
  printf("\nDecoding:\n");

  chk = 0;
  for (i=0; i<SCRAMBLELEN; i++) {
    c = (foo[i] - 41) ^ (i?foo[i-1]:0);
    if (c != (unsigned char)SCRAMBLETEMPLATE[i]) {
      fprintf(stderr,"Decoding FAILED: c='%c', template='%c'\n", 
	     c, SCRAMBLETEMPLATE[i]);
      exit(1);
    }
    chk += c;
    putchar(c);
  }
  if (chk != SCRAMBLECHK) {
    fprintf(stderr, "Consistency check FAILED: chk==%d, SCRAMBLECHK=%d\n", 
	    chk, SCRAMBLECHK);
    exit(1);
  }
  printf("Decoding OK!\n");
}


void main(void)
{
  encode();
  decode();
}
