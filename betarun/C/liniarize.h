#ifndef _LINIARIZE_H_
#define _LINIARIZE_H_

#ifdef LIN

/* GLOBAL TYPE DEFINITIONS */

typedef struct infoTableEntry {

    /* These entries will be collected in an array. The index will be
       the id of the object in the linearization. The GC-attributes of
       the objects are used for various purposes, and below are slots
       for saving the original value of the GC-attribute and a pointer
       to the original object corrosponding to this index.  */
    
    long oldGC;      /* The original value of the GC-attribute */
    long *original;  /* A pointer to the original Object */
    long byteOffset; /* holds the offset of the object in the linearization */
} infoTableEntry;

typedef struct originRefIndicator {
    long byteOffset;
    long indirRef;
} originRefIndicator;

typedef struct liniarization {
    long fd;                    /* file descriptor associated with this
                                   liniarization */
    char *name;                 /* the name of the store in which this
                                   linearization is stored */
    long liniarizationTop;      /* first unused byte in liniarization         */
    long liniarizationLength;   /* number of bytes available in liniarization 
                                   (used and unused)                          */
    char *liniarization;        /* the liniarization itself                   */
    long noObjects;             /* number of objects moved to this liniarization */
    
    /* */
    long originTableTop;
    long originTableLength;
    struct originRefIndicator *originTable;
} liniarization;

/* GLOBAL VARIABLES */

extern struct liniarization *l;

/* GLOBAL FUNCTIONS */
void redirectPointersInAOA(void);

#endif /* LIN */
#endif /* _LINIARIZE_H_ */
