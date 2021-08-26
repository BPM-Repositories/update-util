#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

int main() {
	system("git clone https://github.com/BizzyPythonBear/BSC-BPM $HOME/BSC-BPM");
	system("cd $HOME/BSC-BPM");
	system("sudo make install");
	return 1;
}