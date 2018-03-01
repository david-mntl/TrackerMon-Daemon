/**
 * readStatsFile.c
 * @details Simple program to read /proc/stat file
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @date 25-02-2018
 * 
 * 
 * reference: https://rosettacode.org/wiki/Linux_CPU_utilization = link that helps to resolve the problem
 * 
 * * compilation command: gcc readStatsFile.c -o statsReader
 * 
 */
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include "../FileManagement/writeLogFile.c"

#define CPU_STAT_FILE_NAME "/proc/stat"
#define MEM_STAT_FILE_NAME "/proc/meminfo"
#define MAXBUF 1024

/**
 * @brief Method that gets CPU stats
 * @details top -n 1 | grep '%Cpu(s)' on linux command line output:
 *          %Cpu(s):  6,3 us,  2,1 sy,  0,0 ni, 90,3 id,  1,3 wa,  0,0 hi,  0,0 si,  0,0 st
 *          The CPU usage = 6.3 us + 2.1 sy + 1,3 wa
 *          
 *          Read the first line of the /proc/stat file
 *          The /proc/stat output: cpu  296948 1960 101245 4266549 59385 0 848 0 0 0
 *          The CPU usage = ( 1 - (4266549 / suma(296948, 1960, 101245, 4266549, 59385, 0, 848, 0, 0, 0)) )*100
 * @return The cpu usage
 */
void cpuStat(float pCPU_TRESHOLD){	

	FILE* file = fopen(CPU_STAT_FILE_NAME,"r"); //open file

	if(file == NULL){ //if the file can not be open
		fclose(file); 
        exit(EXIT_FAILURE);
	}
	//file open
	else{
		char str[100];
		const char d[2] = " ";
		char* token;
		int i = 0;
		float sum = 0, idle = 0;
		fgets(str,100,file);
		fclose(file);
		token = strtok(str,d); //token by token

		while(token!=NULL){
			token = strtok(NULL,d);
			if(token!=NULL){
				sum += atof(token); //sum all items of CPU

				if(i==3){
					idle = atof(token); //get idle
				}
				i++;
			}
		}
		float CPU = ((1.0 - (idle)*1.0/(sum))*100);
		if(CPU > pCPU_TRESHOLD){
    		writeLog(CPU, pCPU_TRESHOLD,"",0);
		}	
	}
    
}

/**
 * @brief Method that gets memory stats
 * @details Read the first 2 lines of the /proc/meminfo file
 *          The cat /proc/meminfo output: MemTotal:        5991156 kB
										  MemFree:         1870996 kB
 *          The Memory usage = 100*(MemTotal - MemFree)/MemTotal
 * @return Return the memory usage
 */
void memStat(float pMEM_TRESHOLD)
{
	FILE *file = fopen (MEM_STAT_FILE_NAME, "r");   //open the file, read stat	
	if(file == NULL){
		fclose(file); 
        exit(EXIT_FAILURE);
	}
    else{    	
		//if the file exists or open
    	char line[MAXBUF]; //reading line for the config file
    	int i = 0, j = 0; //to know which parameter is readed
    	char* token;
    	float memTotal, memFree;
		const char d[2] = " ";	
    	// while there are lines to read
    	while( i < 2){
    	 	fgets(line, sizeof(line), file);
    	 	token = strtok(line,d);
    	 	while(token!=NULL && j < 4){              //while to separeta MemTotal:        5991156 kB
				token = strtok(NULL,d);
				if (j == 0){
					memTotal = atof(token); //get the memory total value
				}
				if (j == 3){
					memFree = atof(token);  //get the memory free value					
				}
				j++;	
			}
            i++;
    	} //END WHILE

    	//closing the file
    	fclose(file);	
    	float MEM = (100*(memTotal- memFree)/memTotal); 
    	if(MEM > pMEM_TRESHOLD){
    		writeLog(MEM, pMEM_TRESHOLD, "",1);
    	}
    }// ILSE END
}

/**
 * @brief Method that read all the critical errors, and the errors force by the user
 * @details The first time that is executed saved all the errors of the syslog file 
 *          the others time it will read only the last error
 */
int i = 0;
void readErrors(){
	char *errorM = (char*) malloc(256);
    FILE* fileE = fopen("/var/log/syslog", "r"); // should check the result
    if(fileE == NULL){
		fclose(fileE); 
        exit(EXIT_FAILURE);
	}
    char lineError[256];
    if (i == 0){
		while (fgets(lineError, sizeof(lineError), fileE)) {
			if (strstr(lineError, "CRITICAL") != NULL || strstr(lineError, "Error")){
				strncpy(errorM, lineError+55,64);
				writeLog(0.0,0.0,lineError, 3);
			}
		}
		fclose(fileE);	
		i = 1;
	}
	else{
		while (fgets(lineError, sizeof(lineError), fileE)) {
			if (strstr(lineError, "CRITICAL") != NULL || strstr(lineError, "Error"))
				strncpy(errorM, lineError+55,64);
		}
		fclose(fileE);	
		writeLog(0.0,0.0,lineError, 3);
	}
}

// return the number of SYN_RECV
/**
 * @brief Method that read synn connections
 */
void getSynStat(){
	
   	FILE *file = popen ("netstat -tuna | grep -c SYN_RECV", "r");//load  the command output with syn information

    if(file == NULL){
		fclose(file); 
        exit(EXIT_FAILURE);
	}
    else{
    	char line[100];// will load a line of tmd
    	fgets(line, sizeof(line), file);// load a line

    	fclose(file);// close file after read
    	int synRecv = atof(line);// cast line to int and assing to sysRecv
    	//printf("%d\n",synRecv);
    		
  	} 
}