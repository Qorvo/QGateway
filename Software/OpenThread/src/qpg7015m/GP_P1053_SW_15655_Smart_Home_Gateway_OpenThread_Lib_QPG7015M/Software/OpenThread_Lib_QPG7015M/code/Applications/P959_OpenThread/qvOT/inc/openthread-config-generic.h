#ifndef _OPENTHREAD_CONFIG_GENERIC_H_
#define _OPENTHREAD_CONFIG_GENERIC_H_
/*
 * Qorvo created file:
 *
 * This file is required to jailbreak the OpenThread build process
 * So we don't need to be build OpenThread twice just to have the
 * the file of the same name. The relevant content of that file
 * is added below.
 * The actual file used by openthread is automatically generated
 * and located in  in '<openthread_repo>/build/'
 */

// This is used by `uart_xxx.c`
/* Define to 1 if stdbool.h conforms to C99. */
#define HAVE_STDBOOL_H 1
/* Define to 1 if the system has the type `_Bool'. */
#define HAVE__BOOL 1

#endif // _OPENTHREAD_CONFIG_GENERIC_H_
