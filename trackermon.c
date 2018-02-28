/**
 * trackermon.c
 * @details Simple program of the deamon
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @date 27-02-2018
 * 
 * compilation command: gcc trackermon.c -o exec
 * Execution: ./exec
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./FileManagement/readConfigFile.c"
#include "./Monitoring/readStatsFile.c"
#include "./FileManagement/writeLogFile.c"


/**
 * @brief Read the last error of the system
 * @details [long description]
 * 
 * @param plineError [description]
 */
int readErrors(char * plineError){
	char *errorM = (char*) malloc(256);
	//char const* const fileError = "/var/log/messages.log"; //should check that argc > 1
    FILE* fileE = fopen("/var/log/syslog", "r"); // should check the result
    char lineError[256];
	while (fgets(lineError, sizeof(lineError), fileE)) {
      if (strstr(lineError, "CRITICAL") != NULL)
		strncpy(errorM, lineError+55,64);
	}	
	//verify if the error is not already readed
	if(strcmp(lineError, plineError) != 0){
		strncpy(plineError,lineError, 255); 	
		return 1;
	}
	return -1;
	
}

int main(int argc, char const *argv[])
{/**
	float CPU_TRESHOLD = 0, MEM_TRESHOLD = 0, SYNNCONN_TRESHOLD = 0;
	float CPU_STAT = 0, MEM_STAT = 0, SYNN_STAT = 0;
    char * logFilePath;
    char errorLine[256];

    readConfigFile(&CPU_TRESHOLD, &MEM_TRESHOLD, &SYNNCONN_TRESHOLD, logFilePath);
	while(1){
		
		cpuStat(&CPU_STAT);
		memStat(&MEM_STAT);		
		
		if(CPU_STAT > CPU_TRESHOLD){
			printf("Se paso el CPU");
			//writeLog((char *)(pCpuStat), (char *)(pCpuT), 0);
		}

		if(MEM_STAT > MEM_TRESHOLD){
			printf("Se paso la mem");
			//writeLog((char *)(pMemStat), (char *)(pMemT), 1);
		}

		if(readErrors(errorLine)){
			printf("new error\n");
			//writeLog(errorLine, "", 3);	
		}
		
		

		sleep(2);
	}*/
	float CPU_TRESHOLD = 0, MEM_TRESHOLD = 0, SYNNCONN_TRESHOLD = 0;
	float CPU_STAT = 0, MEM_STAT = 0, SYNN_STAT = 0;
    char * logFilePath;
    readConfigFile(&CPU_TRESHOLD, &MEM_TRESHOLD, &SYNNCONN_TRESHOLD, logFilePath);
    cpuStat(&CPU_STAT);
	memStat(&MEM_STAT);	
	char line[256];
	readErrors(line);
	return 0;
}