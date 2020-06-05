#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/types.h>
#include <sts/wait.h>
#include <fcntl.h>
#include <unistd.h>

int pipes[2];


Make child_proc() and parent_proc()
1) parent_proc()
	-> catch the contents from pipe(by exe file)
	-> write it on pipe[1]
2) child_proc()
	-> read the contents from pipe(by parent process)

char * 
read_exec (char * exe)
{
	pid_t child_pid;
	int exit_code;

	if(pipe(pipes) != 0){
			perror("Error");
			exit(1);
	}

	execvp(exe,pipe[0],pipe[2],0x0);
	//executable file writes its contents on pipe.

	child_pid = fork();
	if(child_pid == 0){
			child_proc();
	}
	else {
			parent_proc();
	}
	wait(&exit_code);

}

int 
main (int argc, char ** argv)
{
	if (argc != 2) {
		fprintf(stderr, "Wrong number of arguments\n") ;
		exit(1) ;
	}

	char * s ;
	s = read_exec(argv[1]) ;
	printf("\"%s\"\n", s) ;
	free(s) ;
	exit(0) ;
}
