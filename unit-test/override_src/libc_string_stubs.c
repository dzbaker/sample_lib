/*
** File: libc_string_stubs.c
**
** Purpose:
** Demonstrates the concept of compile-time replacement
** for C library calls.
**
** This provides the implementation of the "OCS_strncpy"
** function, which is the stub for the C library strncpy call.
**
** Notes:
** For most Unit tests this is _NOT_ necessary.  Whenever
** possible, FSW code should only call CFE/OSAL/PSP code for
** which there are already stubs available and the
** replacements can be made transparently at link time.
*/

/*
 * Note - these are the _real_ system headers here
 * as the "overrides" dir is _not_ part of the include path here
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utstubs.h"

/*
 * This is for the prototype of the "OCS_strncpy()" function
 */
#include "OCS_string.h"

/* **********************************
 * Implementation of OCS_strncpy stub
 * **********************************/
char *OCS_strncpy(char *dst, const char *src, unsigned long size)
{
    int32  Status;
    uint32 CopySize;

    Status = UT_DEFAULT_IMPL(OCS_strncpy);

    if (Status != 0)
    {
        /*
         * a "failure" response -
         * the real C library would never do this.
         */
        return (char *)0;
    }
    /*
     * Demonstrate use of a test-provided local data buffer
     * this provides the "real" data that is written to the output
     */
    CopySize = UT_Stub_CopyToLocal(UT_KEY(OCS_strncpy), dst, size);
    if (CopySize < size)
    {
        /* clear the remained, as strncpy would */
        memset(&dst[CopySize], 0, size - CopySize);
    }

    /* normal response is to return a pointer to the source */
    return dst;
}
