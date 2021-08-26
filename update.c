#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

void getIntoDir(char* directory) {
	char* args[] = {"cd", directory, NULL};
	pid_t pid;
	if ((pid = fork()) < 0) {     /* fork a child process           */
		printf("[E]: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) {          /* for the child process:         */
		if (execvp("cd", args) < 0) {     /* execute the command  */
			printf("[E]: exec failed\n");
			exit(1);
		}
	}
	else {                                  /* for the parent:      */
		wait(&pid);
		return;
	}
}

void installUpdates() {
	char* args[] = {"sudo", "make", "install", NULL};
	pid_t pid;
	if ((pid = fork()) < 0) {     /* fork a child process           */
		printf("[E]: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) {          /* for the child process:         */
		if (execvp("sudo", args) < 0) {     /* execute the command  */
			printf("[E]: exec failed\n");
			exit(1);
		}
	}
	else {                                  /* for the parent:      */
		wait(&pid);
		return;
	}		
}

int checkExist(char* directory) {
	DIR* directory = opendir(directory);
	if (directory) {
		closedir(directory);
		return 1;
	} else if (ENOENT == errno) {
		printf("The directory: %s was not found!", directory);
		return 0;
	} else {
		printf("[E]: OpenDir() Failed");
		return 0;
	}
}

void removeDir(char* directory) {
	char* args[] = {"rm", "-r", directory, NULL};
	pid_t pid;
	if ((pid = fork()) < 0) {     /* fork a child process           */
		printf("[E]: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) {          /* for the child process:         */
		if (execvp("rm", args) < 0) {     /* execute the command  */
			printf("[E]: exec failed\n");
			exit(1);
		}
	}
	else {                                  /* for the parent:      */
		wait(&pid);
		return;
	}	
}

void updateRepo(char* progName) {
	char* args[] = {"git", "clone", "https://github.com/BizzyPythonBear/BSC-BPM", progName, NULL};
	pid_t pid;
	if ((pid = fork()) < 0) {     /* fork a child process           */
		printf("[E]: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) {          /* for the child process:         */
		if (execvp("git", args) < 0) {     /* execute the command  */
			printf("[E]: exec failed\n");
			exit(1);
		}
	}
	else {                                  /* for the parent:      */
		wait(&pid);
		return;
	}
	return;
}

int main() {
	getIntoDir("../");
	updateRepo("BSC-BPM");
	getIntoDir("BSC-BPM");
	installUpdates();
}