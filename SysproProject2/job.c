/*
 * job.c
 *
 *  Created on: Apr 11, 2017
 *      Author: user
 */
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
int main(int argc,char* argv[])
{
	if(argv[1][0]=='.')
	{
		execv(argv[1],argv);
		perror("execv");
		exit(1);
	}
	system(argv[1]);
	exit(1);
}

