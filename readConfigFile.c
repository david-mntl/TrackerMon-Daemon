/**
 * readConfig.c
 * @details Simple program to read file into a config struct
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @date 25-02-2018
 * 
 * compilation command: gcc -Wall readConfig.c -o reader
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/**
 * @brief setting global variables
 */
#define CONFIG_FILE_NAME "config.conf"
#define MAXBUF 1024
#define DELIM "="

/**
 * @details struct definition... contains all the variables of the config file
 * 
 */
struct trackermonConfig {
	char CPUthreshold[MAXBUF];
	char MEMthreshold[MAXBUF];
	char SYNthreshold[MAXBUF];
};

/**
 * @brief method that read a config file
 * @details this method read a config file and save it values into a struct
 * 
 * @param pfilename name of the config file to read
 * @return a struct with config file info
 */
struct trackermonConfig readConfig(char* pfilename){

	struct trackermonConfig configStruct; //struct tu retorn
    FILE *file = fopen (pfilename, "r");   //open the file, read stat

    //if the file exists or open
    if (file != NULL){

    	char line[MAXBUF]; //reading line for the config file
    	int i = 0; //to know which parameter is readed

    	// while there are lines to read
    	while(fgets(line, sizeof(line), file) != NULL){
    		char *cfline;
    	 	cfline = strstr((char *)line,DELIM);
    	 	cfline = cfline + strlen(DELIM);

    	 	if (i == 6){
                memcpy(configStruct.CPUthreshold,cfline,strlen(cfline));
            } else if (i == 9){
                memcpy(configStruct.MEMthreshold,cfline,strlen(cfline));                    
            } else if (i == 12){
                memcpy(configStruct.SYNthreshold,cfline,strlen(cfline));                    
            }
            i++;
    	} //END WHILE

    	//closing the file
    	fclose(file);	

    	return configStruct;
    }// IF END

    else{ //if the file couldnt be open
    	//syslog(LOG_ERR, "Can not open config file: %s, error: %s",
		//	conf_file_name, strerror(errno));
		printf("Error, no file open");
    	fclose(file);	
    	return configStruct;
    }
}

/**
 * @brief Example of how to run it
 * @details [long description]
 * 
 * @param argc [description]
 * @param argv [description]
 * 
 * @return [description]
 */
int main(int argc, char **argv)
{
        struct trackermonConfig configstruct;
       
        configstruct = readConfig(CONFIG_FILE_NAME);
       
        // Struct members 
        printf("%s",configstruct.CPUthreshold);
        printf("%s",configstruct.MEMthreshold);
        //printf("%s",configstruct.SYNthreshold);
       
        // Cast port as int 
        int x;
        x = atoi(configstruct.SYNthreshold);
        printf("%d\n",x);
               
        return 0;
}
*/