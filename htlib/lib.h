//
// $Id: lib.h,v 1.6 1999/03/02 03:47:22 ghutchis Exp $
//
//
#ifndef _lib_h
#define _lib_h

#include <string.h>
#include "htconfig.h"
#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

//
// Other defines used throughout the library
//
#define	OK		0
#define	NOTOK		(-1)

//
// To get rid of inconsistencies between different machines we will ALWAYS
// use our own version of the following routines
//
int mystrcasecmp(char *, const char *);
int mystrncasecmp(char *, const char *, int);

//
// strdup is a really handy function except that the standard version
// relies on malloc and free.  Since it is sometimes hard to keep track
// of when strdup is used and when new is used, we will solve the problem
// be using our own version of strdup which uses new to allocate memory.
//
char *strdup(char *);

//
// The standard strstr() function is limited in that it does case-sensitive
// searches.  This version will ignore case.
//
char *mystrcasestr(char *s, char *pattern);

//
// Too many problems with system strptime() functions...  Just use our own
// version of it.
//
extern "C" char *Htstrptime(char *buf, char *fmt, struct tm *tm);

//
// timegm() is quite rare, so provide our own.
//
extern "C" time_t Httimegm(struct tm *tm);

#endif
