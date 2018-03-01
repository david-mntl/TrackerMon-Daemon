/**
 * trackermon.c
 * @details Simple program of the deamon
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @date 27-02-2018
 * 
 * compilation command: gcc trackermon.c -o trackermon
 * Execution: ./exec
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>

#include "./FileManagement/readConfigFile.c"
#include "./Monitoring/readStatsFile.c"

void forceError(int index){
	openlog("Logs", 0, LOG_USER);
	syslog(LOG_CRIT, "Error Force: %d", index);
	closelog();
}

int main(int argc, char const *argv[])
{
	float CPU_TRESHOLD = 0, MEM_TRESHOLD = 0, SYNNCONN_TRESHOLD = 0;
    char * logFilePath;
    readConfigFile(&CPU_TRESHOLD, &MEM_TRESHOLD, &SYNNCONN_TRESHOLD, logFilePath);
    int i = 0;
    while(1){
    	cpuStat(CPU_TRESHOLD);
		memStat(MEM_TRESHOLD);	
		getSynStat();
		//forceError(5);
		readErrors();
		readErrors();
		i++;
		sleep(4);
    }    
	
	
	return 0;
}