/**
 * writeLogFile.c
 * @details Simple program to write in log file
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @date 26-02-2018
 * 
 * 
 * reference: 
 * 
 * * compilation command: gcc writeLogFile.c -o writeLog
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define LOG_FILE_NAME "trackermon.log"
#define CPU_ALERT 0
#define MEM_ALERT 1
#define NET_ALERT 2
#define SYS_ERROR_ALERT 3

/**
 * @brief Write message into trackermon.log file
 * @details A specific message would be writing depending of the type of alert your insert
 *          The message is construct with the entries
 * 
 * @param pAlertUsage Message that says the read stat from the computer (CPU usgae, memory usage, # syn conncections, )
 * @param pThreshold The treshold specified on the config.conf file
 * @param indicate the type of the alert
 * @return return 1 if the message has been write, if not return -1
 */
void writeLog(char * pAlertUsage, char* pThreshold, int pType){

	FILE* fp = fopen(LOG_FILE_NAME,"a"); //open file

	if(fp == NULL){ //if the file can not be open
		fclose(fp); 
        exit(EXIT_FAILURE);
	}
	//file open
	else{	
		switch(pType){
			case(CPU_ALERT):
				fprintf(fp, "[CRITICAL] CPU usage is currently: %s which is over %s\n", pAlertUsage, pThreshold);			
				break;
			case(MEM_ALERT):
				fprintf(fp, "[CRITICAL] Memory usage is currently: %s which is over %s\n", pAlertUsage, pThreshold);
				break;
			case(NET_ALERT):
				fprintf(fp, "[CRITICAL] SYN flood connections detected. Currently there are %s active SYN_RECV connections, which is over: %s\n", pAlertUsage, pThreshold);
				break;
			case(SYS_ERROR_ALERT):
				fprintf(fp, "[CRITICAL] System critical error has been detected: %s\n", pAlertUsage);
				break;
		}	
	}
}

int main(int argc, char const *argv[])
{
	writeLog("6,5", "6", 0);
	return 0;
}
