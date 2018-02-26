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
int writeLog(char * pAlertUsage, char* pThreshold, int pType){

	FILE* fp = fopen(LOG_FILE_NAME,"a"); //open file

	if(fp == NULL){ //if the file can not be open
		printf("Error, no file open");
		return -1;
	}
	//file open
	else{		
		if (pType == CPU_ALERT){
			char * CPU1 = "CPU usage is currently  ";
			char* CPU2 =" which is over ";
			char * CPU3 = (char *) malloc(1 + strlen(CPU1)+ strlen(pAlertUsage)+ strlen(CPU2) +strlen(pThreshold));
			strcpy(CPU3, CPU1);
			strcat(CPU3,pAlertUsage);
			strcat(CPU3,CPU2);
			strcat(CPU3,pThreshold);
			fprintf(fp, "%s\n", CPU3);
			return 1;			
		} else if (pType == MEM_ALERT) {
			char * MEM1 = "Memory usage is currently: ";
			char * MEM2 =" which is over: ";
			char * MEM3 = (char *) malloc(1 + strlen(MEM1)+ strlen(pAlertUsage)+ strlen(MEM2) +strlen(pThreshold));
			strcpy(MEM3, MEM1);
			strcat(MEM3,pAlertUsage);
			strcat(MEM3,MEM2);
			strcat(MEM3,pThreshold);
			fprintf(fp, "%s\n", MEM3);
			return 1;
		} else if (pType == NET_ALERT) {
			char * NET1 = "SYN flood connections detected. Currently there are ";
			char * NET2 =" active SYN_RECV connections, which is over: ";
			char * NET3 = (char *) malloc(1 + strlen(NET1)+ strlen(pAlertUsage)+ strlen(NET2) +strlen(pThreshold));
			strcpy(NET3, NET1);
			strcat(NET3,pAlertUsage);
			strcat(NET3,NET2);
			strcat(NET3,pThreshold);
			fprintf(fp, "%s\n", NET3);
			return 1;
		} else if (pType == SYS_ERROR_ALERT){
			char * sys1 = "System critical error has been detected: ";
			char * sys2 =  (char *) malloc(1 + strlen(sys1)+ strlen(pAlertUsage));
			strcpy(sys2, sys1);
			strcat(sys2,pAlertUsage);
			fprintf(fp, "%s\n", sys2);
			return 1;
		} else {
			printf("Type spicifier is not valid");
			return -1;
		}
	}
}

int main(int argc, char const *argv[])
{
	writeLog("6,5", "6", 0);
	return 0;
}
