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
 * * compilation command: gcc -Wall readStatsFile.c -o statsReader
 * 
 */
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>

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
double getCPUStat(){
	char str[100];
	const char d[2] = " ";
	char* token;
	int i = 0;
	double sum = 0, idle = 0;

	FILE* fp = fopen(CPU_STAT_FILE_NAME,"r"); //open file

	if(fp == NULL){ //if the file can not be open
		printf("Error, no file open");
		return -1;
	}
	//file open
	else{
		i = 0;
		fgets(str,100,fp);
		fclose(fp);
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
		printf("%f\n", 100 - 100*(idle/sum));
		return (1.0 - (idle)*1.0/(sum))*100;	
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
double memStat()
{
	FILE *file = fopen (MEM_STAT_FILE_NAME, "r");   //open the file, read stat
	double memTotal, memFree;
	const char d[2] = " ";
	//if the file exists or open
    if (file != NULL){    	

    	char line[MAXBUF]; //reading line for the config file
    	int i = 0, j = 0; //to know which parameter is readed
    	char* token;
    	// while there are lines to read
    	while(fgets(line, sizeof(line), file) != NULL){
    	 	
    	 	token = strtok(line,d);
    	 	while(token!=NULL){              //while to separeta MemTotal:        5991156 kB
				token = strtok(NULL,d);
				if (j == 0){
					memTotal = atof(token); //get the memory total value
				}
				if (j == 3){
					memFree = atof(token);  //get the memory free value
					break;
				}
				j++;	
			}

    	 	if (i == 1){
    	 		break;    	 		
    	 	}

            i++;
    	} //END WHILE

    	//closing the file
    	fclose(file);	
    	return 100*(memTotal- memFree)/memTotal;;
    }// IF END

    else{ //if the file couldnt be open
    	//syslog(LOG_ERR, "Can not open config file: %s, error: %s",
		//	conf_file_name, strerror(errno));
		printf("Error, no file open");
    	fclose(file);	
    	return -1;
    }
	
	
}
 
int main(int argC,char* argV[])
{
	getCPUStat();
	//memStat();
	return 0;
}