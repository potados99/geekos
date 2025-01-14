/*
 * Copyright (c) 2001,2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * Copyright (c) 2003,2013,2014 Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 *
 * All rights reserved.
 *
 * This code may not be resdistributed without the permission of the copyright holders.
 * Any student solutions using any of this code base constitute derviced work and may
 * not be redistributed in any form.  This includes (but is not limited to) posting on
 * public forums or web sites, providing copies to (past, present, or future) students
 * enrolled in similar operating systems courses the University of Maryland's CMSC412 course.
 */

#include <conio.h>
#include <process.h>


int main(int argc __attribute__ ((unused)), char **argv
         __attribute__ ((unused))) {

	
// format string for one process line should be "%3d %4d %4d %2c%2c %3c %4d %s\n"
	struct Process_Info pInfo[30];
	PS(pInfo, 10);
	char stat;
	int i;
	Print("PID PPID PRIO STAT AFF TIME COMMAND\n");
	for(i = 0; i < 10; ++i) {
		if(pInfo[i].pid <= 0) continue;
		
		// core
		pInfo[i].currCore = ' ';
		if(pInfo[i].status == STATUS_RUNNABLE) pInfo[i].currCore = '0';

		// status
		if(pInfo[i].status == STATUS_RUNNABLE) stat = 'R';
		else if(pInfo[i].status == STATUS_BLOCKED) stat = 'B';
		else stat = 'Z';		
		
		// AFF
		char aff = '0' + pInfo[i].affinity;
		if(aff < '0') aff = 'A';

		Print("%3d %4d %4d %2c%2c %3c %4d %s\n", pInfo[i].pid, pInfo[i].parent_pid, pInfo[i].priority, pInfo[i].currCore, stat, aff, pInfo[i].totalTime, pInfo[i].name);
	}
	
	Exit(0);

    return 1;
}
