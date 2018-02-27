/**
 * readConfigFile.c
 * @details Simple program to read file into a config struct
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @date 25-02-2018
 * 
 * reference: https://www.pacificsimplicity.ca/blog/simple-read-configuration-file-struct-example = link that helps to resolve the problem
 * 
 * compilation command: gcc readConfigFile.c -o reader
 * Execution: ./reader
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/**
 * @brief setting global variables
 */
#define CONFIG_FILE_NAME "config.conf"

/**
 * @brief method that read a config file
 * @details this method read a config file and save it values into a struct
 * 
 * @param pfilename name of the config file to read
 */
void readConfigFile(int *pCPU, int * pMEM, int * pSYNN, char * plogFilePath){
    FILE * fp;    

    fp = fopen(CONFIG_FILE_NAME, "r");
    if (fp == NULL){
        fclose(fp); 
        exit(EXIT_FAILURE);
    }
    else{
        char key[256], value[256];
        int iVal;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1) {
            if(line[0] == '#' || line[0] == '\n')
                continue;
            else{
                sscanf(line, "%s = %s", key, value);
                if(strcmp(key, "LOGFILE") == 0){       //Identify the LOGFILE path
                    strncpy(plogFilePath,value, 255);
                } else if(strcmp(key, "CPUthreshold") == 0){  //Read the CPUthreshold
                    sscanf(value, "%d", &(*pCPU));
                } else if(strcmp(key, "MEMthreshold") == 0){  //Read the Memthreshold
                    sscanf(value, "%d", &(*pMEM));
                } else if(strcmp(key, "SYNthreshold") == 0){  //Read the SYNthreshold
                    sscanf(value, "%d", &(*pSYNN));
                }
            }
        }
        fclose(fp);    
    }
    
}

/**
 * @brief Example of how to run it
 */
int main(int argc, char **argv)
{    
    int CPU_TRESHOLD = 0, MEM_TRESHOLD = 0, SYNNCONN_TRESHOLD = 0;
    char * logFilePath;
    readConfigFile(&CPU_TRESHOLD, &MEM_TRESHOLD, &SYNNCONN_TRESHOLD, logFilePath); 
    printf("%s\n", logFilePath);      
    printf("%d\n", CPU_TRESHOLD);
    printf("%d\n", MEM_TRESHOLD);
    printf("%d\n", SYNNCONN_TRESHOLD);           
    return 0;
}
