/**
 * trackermon.c
 * @details Simple program of the deamon
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @author David Monestel Aguilar <p.david06.p@gmail.com>
 * @date 27-02-2018
 * 
 * compilation command: gcc trackermon.c -o trackermon
 * Execution: ./trackermon
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>

#include "./FileManagement/readConfigFile.c"
#include "./Monitoring/monitoring.c"

int main(int argc, char const *argv[])
{
	float CPU_TRESHOLD = 0, MEM_TRESHOLD = 0, SYNNCONN_TRESHOLD = 0;
    char * logFilePath;
    readConfigFile(&CPU_TRESHOLD, &MEM_TRESHOLD, &SYNNCONN_TRESHOLD, logFilePath); //read config.conf file
    int i = 0;
    while(1){
    	cpuStat(CPU_TRESHOLD);
		memStat(MEM_TRESHOLD);	
		synnStat(SYNNCONN_TRESHOLD);
		readError();				
		sleep(3);
    }    
	
	
	return 0;
}