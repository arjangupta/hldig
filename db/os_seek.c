/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 1997, 1998, 1999
 *	Sleepycat Software.  All rights reserved.
 */

#include "db_config.h"

#ifndef lint
static const char sccsid[] = "@(#)os_seek.c	11.3 (Sleepycat) 10/29/99";
#endif /* not lint */

#ifndef NO_SYSTEM_INCLUDES
#include <sys/types.h>

#include <errno.h>
#include <stdlib.h>

#ifdef _MSC_VER //_WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#endif

#include "db_int.h"
#include "os_jump.h"

/*
 * CDB___os_seek --
 *	Seek to a page/byte offset in the file.
 *
 * PUBLIC: int CDB___os_seek
 * PUBLIC:     __P((DB_FH *, size_t, db_pgno_t, u_int32_t, int, DB_OS_SEEK));
 */
int
CDB___os_seek(fhp, pgsize, pageno, relative, isrewind, db_whence)
	DB_FH *fhp;
	size_t pgsize;
	db_pgno_t pageno;
	u_int32_t relative;
	int isrewind;
	DB_OS_SEEK db_whence;
{
	off_t offset;
	int whence;

	switch (db_whence) {
	case DB_OS_SEEK_CUR:
		whence = SEEK_CUR;
		break;
	case DB_OS_SEEK_END:
		whence = SEEK_END;
		break;
	case DB_OS_SEEK_SET:
		whence = SEEK_SET;
		break;
	default:
		return (EINVAL);
	}

	if (CDB___db_jump.j_seek != NULL)
		return (CDB___db_jump.j_seek(fhp->fd, pgsize, pageno,
		    relative, isrewind, whence) == -1 ? CDB___os_get_errno() : 0);

	offset = (off_t)pgsize * pageno + relative;
	if (isrewind)
		offset = -offset;
	return (lseek(fhp->fd, offset, whence) == -1 ? CDB___os_get_errno() : 0);
}
