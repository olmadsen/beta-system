#ifndef _LINIARIZE_H_
#define _LINIARIZE_H_
#include <sys/time.h>

/* GLOBAL TYPE DEFINITIONS */

typedef struct indirTableEntry {
    long byteOffset; /* Byte offset to object in liniarization */
} indirTableEntry;

typedef struct originRefIndicator {
    long byteOffset;
    long indirRef;
} originRefIndicator;

typedef struct liniarization {
    long nextId;                 /* next available local id                    */
    
    long indirTableLength;       /* number of entries (used
                                    and unsused)                               */
    indirTableEntry *indirTable; /* the indirection table                      */

    long liniarizationTop;       /* first unused byte in liniarization         */
    long liniarizationLength;    /* number of bytes available in liniarization 
                                    (used and unused)                          */
    char *liniarization;         /* the liniarization itself                   */
    long noObjects;              /* number of objects moved to this liniarization */

    /* */
    long originTableTop;
    long originTableLength;
    struct originRefIndicator *originTable;
    
    struct timeval startOfLastLiniarize;
    struct timeval endOfLastLiniarize;
    
    struct timeval startOfLastLoad;
    struct timeval endOfLastLoad;
    
    struct timeval startOfLastSave;
    struct timeval endOfLastSave;

} liniarization;

/* GLOBAL VARIABLES */

extern struct liniarization *l;

#endif /* _LINIARIZE_H_ */
