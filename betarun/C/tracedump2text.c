/*
 * tracedump2text.c
 * (c) Copyright 2001 Erik Corry
 *
 * Takes a dump file on stdin and outputs a text rendition of it
 */

#include <stdio.h>

#ifdef DEBUG
#define DEBUG_PRINT(a) fprintf a
#else
#define DEBUG_PRINT(a)
#endif

/* #define PARANOID */

#include "trace-types.h"
#include "beta.h"

objecthash bighash;
pc_t ioastart = 0;
pc_t ioaend = 0;
pc_t tospacestart = 0;
pc_t tospaceend = 0;

long
hashtheaddr(long addr)
{
    addr >>= 3;  /* Objects are on 8-byte boundary */
    addr += (addr >> 13); /* bits 3-16 and 17-30 on top of each other */
    addr &= 0x1fff;       /* Use 13 bit index */
    return addr;
}

theobject
new_object(long addr)
{
    theobject o = (theobject)calloc(sizeof(*o), 1);
    o->address = addr;
    return o;
}

/*
 * Given a new object, put it in the hash
 */

void
enter_object(theobject o)
{
    long addr = o->address;
    int size = o->size;
    long hash = hashtheaddr(addr);
    theobject *t;
#   ifdef PARANOID
    for (t = &bighash.objects[hash]; *t; t = &((*t)->next)) {
	long taddress = (*t)->address;
	long tsize = (*t)->size;
	if ((taddress >= addr && taddress < addr + size) ||
	    (addr >= taddress && addr < taddress + tsize)) {
	    fprintf(stderr, "*** WARNING: new object from %08x and %d bytes "
		    "overlaps existing object from %08x and %d bytes\n", addr, size, taddress, tsize);
	}
    }
#   endif
    o->next = bighash.objects[hash];
    bighash.objects[hash] = o;
}

/*
 * Given an address, get the corresponding object out of the hash and
 * return it
 */

theobject
remove_object(long addr)
{
    long hash = hashtheaddr(addr);
    theobject *t;
    for (t = &bighash.objects[hash]; *t; t = &((*t)->next)) {
	if ((*t)->address == addr) {
	    theobject answer = *t;
	    *t = (*t)->next;
	    answer->next = 0;
	    return answer;
	}
    }
    fprintf(stderr, "*** Warning: no object found at %08x\n", addr);
    return 0;
}

/*
 * Given an address, find the corresponding object
 */

theobject
find_object(long addr)
{
    long hash = hashtheaddr(addr);
    theobject *t;
    for (t = &bighash.objects[hash]; *t; t = &((*t)->next)) {
	if ((*t)->address == addr) {
	    return *t;
	}
    }
    return 0;
}

theobject
move_object(long addr, long newaddr) {
    theobject o = remove_object(addr);
    if (!o) return 0;
    o->address = newaddr;
    enter_object(o);
    o->moves++;
    return o;
}

typedef struct 
{
    pc_t addr;
    char *name;
} label_t;

label_t *labels = 0;
int label_count = 0;
int labels_free = 0;

char *
find_label(pc_t addr){
    int i;
    label_t *top = labels + label_count - labels_free;
    label_t *bottom = labels;
    if (addr == 0) {
	char *t = (char *)malloc(3);
	sprintf(t, "0");
	return t;
    }
    if (addr >= ioastart && addr < ioaend) {
	char *t = (char *)malloc(30);
	sprintf(t, "IOA1 + %05x", addr - ioastart);
	return t;
    }
    if (addr >= tospacestart && addr < tospaceend) {
	char *t = (char *)malloc(30);
	sprintf(t, "IOA2 + %05x", addr - tospacestart);
	return t;
    }
    if (addr < bottom->addr) {
	char *t = (char *)malloc(30);
	sprintf(t, "(below symbols)");
	return t;
    }
    if (addr > top[-1].addr) {
	char *t = (char *)malloc(30);
	sprintf(t, "(above symbols)");
	return t;
    }
    do {
	label_t *middle;
	if (top - bottom <= 1) {
	    char *answer = (char *)malloc(strlen(bottom->name) + 10);
	    if (addr == bottom->addr) {
		sprintf(answer, "%s", bottom->name);
	    } else {
		sprintf(answer, "%04x+%s", addr - bottom->addr, bottom->name);
	    }
	    return answer;
        }
	middle = bottom + (top - bottom)/2;
	if (middle->addr <= addr) {
	    bottom = middle;
	} else {
	    top = middle;
	}
    } while (1);
}

char *label_area;
int label_area_space = 0;


void
addLabel(pc_t addr, char *label) {
    int len = strlen(label);
    if (!addr) return;
    /*printf("Add label '%s'\n", label);*/
    if (label_area_space < len + 1) {
	label_area = (char *)malloc(len+1+10000);
        label_area_space = len + 1 + 10000;
    }
    strcpy(label_area, label);
    label = label_area;
    label_area += len + 1;
    label_area_space -= len + 1;
    if (!labels_free) {
	int new_label_count = label_count * 4 + 4;
	label_t *new_labels = (label_t *)malloc(sizeof(label_t) * new_label_count);
	int i;
	labels_free = new_label_count - label_count;
	for (i = 0; i < label_count; i++) {
	    new_labels[i] = labels[i];
	}
	free(labels);
	labels = new_labels;
	label_count = new_label_count;
    }
    labels[label_count - labels_free].addr = addr;
    labels[label_count - labels_free].name = label;
    labels_free--;
}

char *
alloc_place(int i)
{
    switch(i) {
	case 1:
	    return "AlloI";
	case 2:
	    return "AlloC";
	case 3:
	    return "AlloDO";
	case 4:
	    return "AlloH";
	case 5:
	    return "AlloVRI";
	case 6:
	    return "AlloRR";
	case 7:
	    return "AlloSO";
	case 8:
	    return "AlloVR1";
	case 9:
	    return "AlloVR2";
	case 10:
	    return "AlloVR4";
	case 11:
	    return "AlloVR8";
	case 12:
	    return "CopyCT_W";
	case 13:
	    return "CopyCT";
	case 14:
	    return "CopyRR";
	case 15:
	    return "CopySRR";
	case 16:
	    return "CopySVR1";
	case 17:
	    return "CopySVR2";
	case 18:
	    return "CopySVR4";
	case 19:
	    return "CopySVR8";
	case 20:
	    return "CopySVRI";
	case 21:
	    return "CopySVRC";
	case 22:
	    return "CopyT";
	case 23:
	    return "CopyT_W";
	case 24:
	    return "CopyVR1";
	case 25:
	    return "CopyVR2";
	case 26:
	    return "CopyVR4";
	case 27:
	    return "CopyVR8";
	case 28:
	    return "CopyVRI";
	case 29:
	    return "CopyVRC";
	case 30:
	    return "ExtRR";
	case 31:
	    return "ExtVR1";
	case 32:
	    return "ExtVR2";
	case 33:
	    return "ExtVR4";
	case 34:
	    return "ExtVR8";
	case 35:
	    return "ExtVRI";
	case 36:
	    return "ExtVRC";
	case 38:
	    return "AlloS";
	case 39:
	    return "VAlloS";
	case 40:
	    return "AlloVRC";
	/* AOA allocators */
	case 41:
	    return "LVRAAlloc";
	case 42:
	    return "LVRACAlloc";
	case 43:
	    return "LVRAXAlloc";
	default:
	    return "Unknown";
    }
}

main(int argc, char **argv)
{
    int c;
    int i, j, k, l, m;
    char *a;
    char *b;
    char *d;
    int s;
    int stackframe = 0;
    while ((s = fread(&c, 1, 4, stdin)) == 4) {
	switch(c) {
	    case TRACE_EXE_FILENAME:
		{
		    char filename[1024];
		    int max = 254;
		    int *f = (int *)(&filename);
		    labeltable *lnt;
		    do {
			fread(&i, 1, 4, stdin);
			*f = i;
			f++; max--;
		    } while(i && max);
		    printf("Exe file name: '%s'\n", filename);
		    fflush(stdout);
                    lnt = initReadNameTable(filename,1 );
		    if (!lnt)
		        fprintf(stderr, "Couldn't open '%s'\n", filename);
		    else {
		        char *theLabel;
		        pc_t labelAddress;
			while ((labelAddress = nextAddress(lnt)) != (pc_t)-1) {
			    theLabel = nextLabel(lnt);
			    addLabel(labelAddress, theLabel);
			    /*printf("%08x: %s\n", labelAddress, theLabel);*/
			}
		    }
		}
		break;
	    case TRACE_STACK_POSN:
		stackframe++;
		fread(&i, 1, 4, stdin);
		printf("Entering stack frame SFRM%d at %08x\n", stackframe, i);
		break;
	    case TRACE_STACK_RETURN:
		printf("Exiting stack frame SFRM%d\n", stackframe);
		stackframe--;
		break;
	    case TRACE_GC_CALLED:
		fread(&i, 1, 4, stdin);
		printf("IOA GC %d called\n", i);
		break;
	    case TRACE_GC_OVER:
		printf("IOA GC over\n", i);
		break;
	    case TRACE_AOA_GC_CALLED:
		fread(&i, 1, 4, stdin);
		printf("AOA GC %d called\n", i);
		break;
	    case TRACE_AOA_GC_OVER:
		printf("AOA GC over\n");
		break;
	    case TRACE_ALLOC_OBJECT:
		fread(&m, 1, 4, stdin);
		fread(&i, 1, 4, stdin);
		fread(&j, 1, 4, stdin);
		fread(&k, 1, 4, stdin);
		fread(&l, 1, 4, stdin);
		a = find_label((pc_t)l);
		b = find_label((pc_t)k);
		d = alloc_place(m);
		printf("Alloc (%s) at %08x (%d bytes) %s from %s\n", d, j, i, a, b);
		free(a); free(b); a = b = 0;
		{
		    theobject o = new_object(j);
		    o->size = i;
		    o->stack_frame = stackframe;
		    enter_object(o);
		    if (c == TRACE_ALLOC_VARSIZE_OBJECT) o->privatepart = 1;
		    if (c == TRACE_ALLOC_VIRTUAL_OBJECT) o->virtualpart = 1;
		}
		break;
	    case TRACE_MOVE_OBJECT_IN_IOA:
	    case TRACE_MOVE_OBJECT_TO_AOA:
		fread(&i, 1, 4, stdin);
		fread(&j, 1, 4, stdin);
		a = find_label((pc_t)i);
		b = find_label((pc_t)j);
		move_object(i, j);
		printf("Moved object from %08x (%s) to %08x (%s)\n", i, a, j, b);
		break;
	    case TRACE_OBJECT_DEAD:
		fread(&i, 1, 4, stdin);
		a = find_label((pc_t)i);
		printf("Object died at %08x (%s)\n", i, a);
		remove_object(i);
		break;
	    case TRACE_WRITE_POINTER:
		fread(&i, 1, 4, stdin);
		fread(&j, 1, 4, stdin);
		break;
	    case TRACE_INIT_IOA:
		if (!ioastart) {
		    fread(&ioastart, 1, 4, stdin);
		    fread(&ioaend, 1, 4, stdin);
		    printf("IOA1 from %08x to %08x\n", ioastart, ioaend);
		} else {
		    fread(&tospacestart, 1, 4, stdin);
		    fread(&tospaceend, 1, 4, stdin);
		    printf("IOA2 from %08x to %08x\n", tospacestart, tospaceend);
		}
		break;
	    case TRACE_1WORD:
	    case TRACE_2WORDS:
	    case TRACE_3WORDS:
	    case TRACE_4WORDS:
	    case TRACE_5WORDS:
	    case TRACE_6WORDS:
	    case TRACE_7WORDS:
	    case TRACE_8WORDS:
	    case TRACE_9WORDS:
		printf("Debugging words:\n");
		do {
		    char *a;
		    fread(&i, 1, 4, stdin);
		    a = find_label((pc_t)i);
		    printf("    %08x - %s\n", i, a);
		    c--;
		} while(c >= TRACE_1WORD);
		break;
	    default:
		printf("Unknown code %08x\n", c);
		break;
	}
    }
}



/*
 * vim:sw=4:
 */
