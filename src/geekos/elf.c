/*
 * ELF executable loading
 * Copyright (c) 2003, Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 * Copyright (c) 2003, David H. Hovemeyer <daveho@cs.umd.edu>
 *
 * All rights reserved.
 *
 * This code may not be resdistributed without the permission of the copyright holders.
 * Any student solutions using any of this code base constitute derviced work and may
 * not be redistributed in any form.  This includes (but is not limited to) posting on
 * public forums or web sites, providing copies to (past, present, or future) students
 * enrolled in similar operating systems courses the University of Maryland's CMSC412 course.
 *
 * $Revision: 1.31 $
 *
 */

#include <geekos/errno.h>
#include <geekos/kassert.h>
#include <geekos/ktypes.h>
#include <geekos/screen.h>      /* for debug Print() statements */
#include <geekos/pfat.h>
#include <geekos/malloc.h>
#include <geekos/string.h>
#include <geekos/user.h>
#include <geekos/fileio.h>
#include <geekos/elf.h>

#include <geekos/paging.h>

int elfDebug = 0;

/**
 * From the data of an ELF executable, determine how its segments
 * need to be loaded into memory.
 * @param exeFileData buffer containing the executable file
 * @param exeFileLength length of the executable file in bytes
 * @param exeFormat structure describing the executable's segments
 *   and entry address; to be filled in
 * @return 0 if successful, < 0 on error
 */
int Parse_ELF_Executable(char *exeFileData, ulong_t exeFileLength,
                         struct Exe_Format *exeFormat) {
	elfHeader* pElfHeader = (elfHeader*)exeFileData;
	programHeader* pProgHeader = (programHeader*)(exeFileData + pElfHeader->phoff);
	struct Exe_Segment* pSegment = exeFormat->segmentList;
	
	if(exeFileData == 0) {
		return 0;
	}

	for(int i = 0; i < pElfHeader->phnum; ++i) {
		pSegment->offsetInFile = pProgHeader->offset;
		pSegment->lengthInFile = pProgHeader->fileSize;
		pSegment->startAddress = pProgHeader->vaddr;
		pSegment->sizeInMemory = pProgHeader->memSize;
		pSegment->protFlags = pProgHeader->flags;
		++pSegment;
		++pProgHeader;
	}
	
	exeFormat->numSegments = pElfHeader->phnum;
	exeFormat->entryAddr = pElfHeader->entry;

	return 0;
}
