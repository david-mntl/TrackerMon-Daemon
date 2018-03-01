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
#include <syslog.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "./FileManagement/readConfigFile.c"
#include "./Monitoring/readStatsFile.c"

void forceError(int index){
	openlog("Logs", 0, LOG_USER);
	syslog(LOG_CRIT, "Error Force: %d", index);
	closelog();
}

static void daemonBody()
{
	pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
  /*  signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);*/

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("firstdaemon", LOG_PID, LOG_DAEMON);
}

int main(int argc, char const *argv[])
{
  	float CPU_TRESHOLD = 0, MEM_TRESHOLD = 0, SYNNCONN_TRESHOLD = 0;
    char * logFilePath;
    readConfigFile(&CPU_TRESHOLD, &MEM_TRESHOLD, &SYNNCONN_TRESHOLD, logFilePath);
    int i = 0;

		daemonBody();
    while(1){
			//TODO: Insert daemon code here.
	        syslog (LOG_NOTICE, "First daemon started.");

    cpuStat(CPU_TRESHOLD);
		memStat(MEM_TRESHOLD);
		getSynStat();
		//forceError(5);
		readErrors();
		i++;
		sleep(2);
    }

		closelog();


	return 0;
}
