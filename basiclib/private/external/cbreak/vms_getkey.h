/*
 *  file: vms_getkey.h
 *  purpose: header file for vms_getkey.c
 *
 * author: Anthony C. McCracken
 * modification: R. Vankemmel 28/10/1994
 *               Split his original ode into a header and a source file.
 *               Reason: see description in the vms_getkey.c file.
 *               Added proper flags preventing multiple includes.
 *
 * His original comments:
 *================================================================
 *
    TERMIO.H fixes a few anomolies of the VAX C runtime library.

    Version 1.6 10-APR-92      Anthony C. McCracken

    getkey() returns the next keystroke without echo or a carriage
             return.

    putchar(char) works like the UNIX putchar, buffering the characters
                  until the buffer fills up (512 chars) or a newline
                  character is putchared.

    To use these routines, just include this header file after all the
    other #include statements.

 *================================================================
 *
 */
#ifndef _VMS_GETKEY_H_SEEN_
#define _VMS_GETKEY_H_SEEN_

#include <stdio.h>
#include <ssdef.h>
#include <iodef.h>

typedef struct {
           short int status;              /* I/O completion status */
           short int bcount;              /* byte transfer count   */
           int dev_dep_data;              /* device dependant data */
        } iosb;                  /* This is a QIO I/O Status Block */

typedef struct {
           short int length;              /* Length of string      */
           char      dtype;               /* Type 14 is a string   */
           char      class;               /* Class 1 is fixed length */
           char      *ptr;                /* Pointer to the string */
        } descr;                 /* once initialized, this is a fixed */
                                 /* length string descriptor */
/* function prototyping */
extern char getkey();

#endif
