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

#define SCRAMBLETEMPLATE "\
Mj\277lner BETA System\r\
DEMO VERSION release 3.0\
\r\r"

#define SCRAMBLESTRING {\
0x76, 0x45, 0x23, 0x78, 0x3f, 0x83, 0x1a, 0x63, 0x4a, 0x38, \
0x95, 0xfd, 0x06, 0x7e, 0x30, 0x6c, 0x41, 0x4d, 0x49, 0x6d, \
0x52, 0x40, 0x36, 0xa2, 0xab, 0x26, 0x8c, 0x07, 0x7d, 0x5d, \
0x3b, 0x9e, 0xe7, 0xbe, 0x04, 0x91, 0x1d, 0xa5, 0xff, 0xc3, \
0x0c, 0x68, 0x6f, 0x88, 0xae, 0xcc }
#define SCRAMBLELEN 46
#define SCRAMBLECHK 3660

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
