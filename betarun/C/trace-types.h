/*
 * trace-types.h
 * (c) Copyright 2001 Erik Corry
 *
 * Constants used to put messages in the allocation trace file
 * enabled with flag 102.
 */

#ifndef TRACE_TYPES_H
#define TRACE_TYPES_H 1

extern pc_t AllocCallPoint;

/*
 * TRACE_STACK_POSN number addr
 * A call has allocated a new stack frame which starts here (addr just for
 * debugging)
 */
#define TRACE_STACK_POSN 0

/*
 * TRACE_STACK_RETURN (number addr)
 * A call has returned
 */
#define TRACE_STACK_RETURN 1

/*
 * TRACE_ALLOC_OBJECT size address call-point prototype
 * An object has been allocated, size is in bytes, address is the handle
 */
#define TRACE_ALLOC_OBJECT 2

/*
 * TRACE_ALLOC_VARSIZE_OBJECT size address call-point
 * As above, but the object was a private part-object (hidden by the fragment
 * system) so we didn't know its
 * size when allocating the stack frame size.
 */
#define TRACE_ALLOC_VARSIZE_OBJECT 3

/*
 * TRACE_ALLOC_VIRTUAL_OBJECT size address call-point
 * As above but the object was a virtual part object (hidden by potential
 * specialisation) so we didn't know the size
 */
#define TRACE_ALLOC_VIRTUAL_OBJECT 4

/*
 * TRACE_MOVE_OBJECT_IN_IOA addr addr
 * An object has been moved from addr to addr
 */
#define TRACE_MOVE_OBJECT_IN_IOA 5

/*
 * TRACE_MOVE_OBJECT_TO_AOA addr addr
 * An object has been moved from addr to addr
 */
#define TRACE_MOVE_OBJECT_TO_AOA 6

/*
 * TRACE_OBJECT_DEAD addr
 * An object has been found to be dead by the GC
 */
#define TRACE_OBJECT_DEAD 7

/*
 * TRACE_GC_CALLED number
 * TRACE_GC_OVER
 * (IOA) GC called
 */
#define TRACE_GC_CALLED 8
#define TRACE_GC_OVER 9

/*
 * TRACE_AOA_GC_CALLED number
 * TRACE_AOA_GC_OVER
 * Adult object area garbage collection started
 */
#define TRACE_AOA_GC_CALLED 10
#define TRACE_AOA_GC_OVER 11

/*
 * TRACE_WRITE_POINTER address address
 * A pointer has been written in the first object pointing to the second object
 */
#define TRACE_WRITE_POINTER 12

/*
 * TRACE_WRITE_ORIGIN_POINTER address address
 * As above, but the pointer write was to set up an origin
 */
#define TRACE_WRITE_ORIGIN_POINTER 13

/*
 * TRACE_WRITE_ORIGIN_POINTER address address
 * As above, but the pointer write was during an eviction
 */
#define TRACE_WRITE_EVICTION_POINTER 14

/*
 * TRACE_INIT_IOA address address
 * The IOA lies between these addresses
 */
#define TRACE_INIT_IOA 20

/*
 * TRACE_NEW_AOA address address
 * A new AOA area has been allocated between these addresses (there can be many)
 */
#define TRACE_NEW_AOA 21

/*
 * TRACE_DELETE_AOA
 * An AOA area between these addresses has been freed (it was empty)
 */
#define TRACE_DELETE_AOA 22

/*
 * TRACE_EXE_FILENAME
 * Followed by zero-terminated list of longs which define filename
 * Endian-dependent!
 */
#define TRACE_EXE_FILENAME 23

/*
 * TRACE_1WORD address/word
 * TRACE_2WORDS address/word address/word
 * TRACE_3WORDS address/word address/word address/word
 * TRACE_4WORDS address/word address/word address/word address/word
 * For debugging
 */
#define TRACE_1WORD 30
#define TRACE_2WORDS 31
#define TRACE_3WORDS 32
#define TRACE_4WORDS 33
#define TRACE_5WORDS 34
#define TRACE_6WORDS 35
#define TRACE_7WORDS 36
#define TRACE_8WORDS 37
#define TRACE_9WORDS 38

typedef struct _theobject {
    struct _theobject *next;
    long address;
    long alloc_point;
    int size;
    int stack_frame; /* -1 = IOA, -2 = AOA */
    int false_alarms;
    int moves;
    char privatepart;
    char virtualpart;
} *theobject;

typedef struct {
    int entries;
    theobject objects[8192];
} objecthash;

#endif /* def TRACE_TYPES_H */
