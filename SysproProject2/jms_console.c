#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int main(int argc,char* argv[])
{
	char *jms_in,*jms_out,*filename;
	int i,fd,fd1;
	char* command=malloc(30*sizeof(char));
	if(command==NULL)
	{
		perror("malloc");
		exit(1);
	}
	char* function=malloc(30*sizeof(char));
	if(function==NULL)
	{
		perror("malloc");
		exit(1);
	}
	char message[25];
	char* part=malloc(20*sizeof(char));
	if(part==NULL)
	{
		perror("malloc");
		exit(1);
	}
	for(i=0;i<argc;i++)
	{
		if(!strcmp(argv[i],"-w"))
		{
			jms_in=malloc((strlen(argv[i+1]))*sizeof(char)+1);
			if(jms_in==NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(jms_in,argv[i+1]);
		}
		if(!strcmp(argv[i],"-r"))
		{
			jms_out=malloc((strlen(argv[i+1]))*sizeof(char)+1);
			if(jms_out==NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(jms_out,argv[i+1]);
		}
		if(!strcmp(argv[i],"-o"))
		{
			filename=malloc((strlen(argv[i+1]))*sizeof(char)+1);
			if(filename==NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(filename,argv[i+1]);
		}
	}
	FILE* fp;
	if((fd=open(jms_in,O_RDWR | O_NONBLOCK))<0)
	{
			perror (" jms_in open problem ");
			exit (3) ;
	}
	if((fd1=open(jms_out,O_RDWR | O_NONBLOCK))<0)
	{
			perror (" jms_out open problem ");
			exit (3) ;
	}
	if((fp=fopen(filename,"r"))==0)				//EDW THA MPEI OTAN DEN  DOTHEI ARXEIO OPERATIONS//
	while(1)
	{
		int flag=0;
		int k=0;
		i=0;
		fprintf(stdout,"Vale entolh\n");
		fscanf(stdin,"%[^\n]%*c", function);
		if(!strcmp(function,"show-pools"))
		{
			flag=1;
		}
		if(!strcmp(function,"show-active"))
		{
			flag=1;
		}
		if(!strcmp(function,"show-finished"))
		{
			flag=1;
		}
		if(!strcmp(function,"shutdown"))
		{
			flag=1;
		}
		if(!strcmp(function,"status-all"))
		{
			flag=1;
		}
		if(flag==0)
		{
			memset(command, '\0', sizeof(command));
			for(i=0;i<30;i++)
			{
				strcpy(&command[i],"\0") ;
			}
			i=0;
			while(function[k]!=' ')
			{
				command[i]=function[k];
				i++;
				k++;
			}
		}
		if(!strcmp(command,"sumbit"))
		{
			flag=1;

		}
		if(!strcmp(command,"status"))
		{
			flag=1;
		}
		if(!strcmp(command,"status-all"))
		{
			flag=1;
		}

		if(!strcmp(command,"suspend"))
		{
			flag=1;
		}
		if(!strcmp(command,"resume"))
		{
			flag=1;
		}
		if(flag==0)continue;
		if(write(fd,function,30)==-1)
		{
				perror ( " problem in writing ");
				exit (5) ;
		}
		memset(message, '\0', sizeof(message));
		while(1)
		{
			if(read(fd1,message,1)<0)
			{
				continue;
			}
			break;
		}
		if(!strcmp(message,"0"))
		{
			continue;
		}
		if(!strcmp(message,"1"))
		{

			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			int id=atoi(message);
			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,10)<0)
				{
					continue;
				}
				break;
			}
			fprintf(stdout,"JobID: %d ,PID: %d\n",id,atoi(message));
			continue;
		}
		else if(!strcmp(message,"2"))
		{
			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			int id=atoi(message);
			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,30)<0)
				{
					continue;
				}
				break;
			}
			char status[30];
			strcpy(status,message);
			if(!(strcmp(message,"ACTIVE")))
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,30)<0)
				{
					continue;
				}
				fprintf(stdout,"JobID %d Status: %s (running for %d sec)\n",id,status,atoi(message));
			}
			else
			{
				fprintf(stdout,"JobID %d Status: %s\n",id,status);
			}
		}
		else if(!strcmp(message,"3"))
		{
				while(1)
				{
					memset(message, '\0', sizeof(message));
					while(1)
					{
						if(read(fd1,message,5)<0)
						{
							continue;
						}
						break;
					}
					if(!strcmp(message,"|"))break;
					if(strcmp(message,"3.1") && strcmp(message,"3.0"))continue;
					memset(message, '\0', sizeof(message));
					while(1)
					{
						if(read(fd1,message,5)<0)
						{
								continue;
						}
						break;
					}
					if(!strcmp(message,"|"))break;
					int id=atoi(message);
					memset(message, '\0', sizeof(message));
					while(1)
					{
						if(read(fd1,message,30)<0)
						{
								continue;
						}
						break;
					}
					if(!strcmp(message,"|"))break;
					char status[30];
					strcpy(status,message);
					if(!strcmp(status,"ACTIVE"))
					{
						while(1)
						{
							if(read(fd1,message,5)<0)
							{
								continue;
							}
							break;
						}
						if(!strcmp(message,"|"))break;
						fprintf(stdout,"JobID %d Status: %s (running for %d sec)\n",id,status,atoi(message));
					}
					else
					{
						fprintf(stdout,"JobID %d Status: %s\n",id,status);
					}
				}
		}
		else if(!strcmp(message,"4"))
		{
			fprintf(stdout,"Active Jobs:\n");
			int k=1;
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				if(!strcmp(message,"|"))break;
				int id=atoi(message);
				fprintf(stdout,"%d)  JobID %d Status: ACTIVE\n",k,id);
				k++;
			}
		}
		else if(!strcmp(message,"5"))
		{
			fprintf(stdout,"Pool & NumOfJobs console\n");
			int k=1;
			while(1)
			{
				while(1)
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,10)<0)
					{
						continue;
					}
					break;
				}
				if(!strcmp(message,"|"))break;
				int pid=atoi(message);
				while(1)
				{

					memset(message, '\0', sizeof(message));
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				if(!strcmp(message,"|"))break;
				fprintf(stdout,"%d). %d %d\n",k,pid,atoi(message));
				k++;
			}
		}
		else if(!strcmp(message,"6"))
		{
			fprintf(stdout,"Finished Jobs:\n");
			int k=1;
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				if(!strcmp(message,"|"))break;
				int id=atoi(message);
				fprintf(stdout,"%d). JobID %d Status: FINISHED\n",k,id);
				k++;
			}
		}
		else if(!strcmp(message,"7"))
		{
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			fprintf(stdout,"Sent suspent signal to JobID %s\n",message);
		}
		else if(!strcmp(message,"8"))
		{
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			fprintf(stdout,"Sent resume signal to JobID %s\n",message);
		}
		else if(!strcmp(message,"9"))
		{
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			int jobs=atoi(message);
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			fprintf(stdout,"Served %d jobs,%d were still in progress\n",jobs,atoi(message));
			free(command);
			free(function);
			free(part);
			free(jms_in);
			free(jms_out);
			free(filename);
			raise(SIGTERM);
		}
	}

								//TA SXOLIA PARAKATW ISXUOUN KAI GIA THN WHILE APO PANW KAI GIA THN WHILE APO KATW APLA OI 2 ALLES WHILE AFOROUN TO STDIN KAI OXI TO ARXEIO OPERATIONS//
	while(1)					//EDW THA MPEI OTAN DWTHEI ARXEIO OPERATIONS GIA NA DIAVASEI APO ARXEIO AUTO//
	{
		char str;
		fscanf(fp,"\n%s", function);
	    if (feof(fp))
	    	break;
	    str=' ';
		strcpy(command,function);
		if(!strcmp(function,"sumbit"))
		{
			fscanf(fp," %[^\n]",part);
			strcat(command," ");
			strcat(command,part);
		}
		if(!strcmp(function,"status"))
		{
			fscanf(fp,"%s",part);
			strcat(command," ");
			strcat(command,part);
		}
		if(!strcmp(function,"status-all"))
		{
			char str=fgetc(fp);
			if(str==' ')
			{
				fscanf(fp,"%s",part);
				strcat(command," ");
				strcat(command,part);
			}
		}
		if(!strcmp(function,"suspend"))
		{
			fscanf(fp,"%s",part);
			strcat(command," ");
			strcat(command,part);
		}
		if(!strcmp(function,"resume"))
		{
			fscanf(fp,"%s",part);
			strcat(command," ");
			strcat(command,part);
		}
		if(write(fd,command,30)==-1)				//AFOU DIAVASW POIA ENTOLH EINAI ETOIMH NA EKTELESTEI  THN GRAFW STO JMS_IN//
		{
				perror ( " problem in writing ");
				exit (5) ;
		}
		memset(message, '\0', sizeof(message));
		while(1)									// EDW PERIMENW NA DIAVASW APO TO JMS_OUT ENA ARITHMO POU EINAI MESA STO PROTOKOLLO THS EPIKOINWNIAS(README)//
		{
			if(read(fd1,message,1)<0)
			{
				continue;
			}
			break;
		}
		if(!strcmp(message,"0"))						//TO MESSAGE THA PAREI ENAN ARITHMO APO 0 - 9 POU DHLWNEI ANITSTOIXA POIA SUNARTHSH KALESTHKE //
		{
			continue;
		}
		if(!strcmp(message,"1"))
		{
			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,5)<0)
				{
						continue;
				}
				break;
			}
			int id=atoi(message);
			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,10)<0)
				{
					continue;
				}
				break;
			}
			fprintf(stdout,"JobID: %d ,PID: %d\n",id,atoi(message));
			continue;
		}
		else if(!strcmp(message,"2"))
		{
			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,5)<0)
				{
						continue;
				}
				break;
			}
			int id=atoi(message);
			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,30)<0)
				{
						continue;
				}
				break;
			}
			char status[30];
			strcpy(status,message);
			if(!(strcmp(message,"ACTIVE")))
			{
				memset(message, '\0', sizeof(message));
				while(1)
				{
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				fprintf(stdout,"JobID %d Status: %s (running for %d sec)\n",id,status,atoi(message));
			}
			else
			{
				fprintf(stdout,"JobID %d Status: %s\n",id,status);
			}
		}
		else if(!strcmp(message,"3"))
		{
				while(1)
				{
					memset(message, '\0', sizeof(message));
					while(1)
					{
						if(read(fd1,message,5)<0)
						{
							continue;
						}
						break;
					}
					if(!strcmp(message,"|"))break;
					if(strcmp(message,"3.1") && strcmp(message,"3.0"))continue;
					memset(message, '\0', sizeof(message));
					while(1)
					{
						if(read(fd1,message,5)<0)
						{
							continue;
						}
						break;
					}
					if(!strcmp(message,"|"))break;
					int id=atoi(message);
					memset(message, '\0', sizeof(message));
					while(1)
					{
						if(read(fd1,message,30)<0)
						{
							continue;
						}
						break;
					}
					if(!strcmp(message,"|"))break;
					char status[30];
					strcpy(status,message);
					if(!strcmp(status,"ACTIVE"))
					{
						while(1)
						{
							if(read(fd1,message,5)<0)
							{
								continue;
							}
							break;
						}
						if(!strcmp(message,"|"))break;
						fprintf(stdout,"JobID %d Status: %s (running for %d sec)\n",id,status,atoi(message));
					}
					else
					{
						fprintf(stdout,"JobID %d Status: %s\n",id,status);
					}
				}
		}
		else if(!strcmp(message,"4"))
		{
			fprintf(stdout,"Active Jobs:\n");
			int k=1;
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				if(!strcmp(message,"|"))break;
				int id=atoi(message);
				fprintf(stdout,"%d)  JobID %d Status: ACTIVE\n",k,id);
				k++;
			}
		}
		else if(!strcmp(message,"5"))
		{
			fprintf(stdout,"Pool & NumOfJobs console\n");
			int k=1;
			while(1)
			{
				while(1)
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,10)<0)
					{
						continue;
					}
					break;
				}
				if(!strcmp(message,"|"))break;
				int pid=atoi(message);
				while(1)
				{

					memset(message, '\0', sizeof(message));
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				if(!strcmp(message,"|"))break;
				fprintf(stdout,"%d). %d %d\n",k,pid,atoi(message));
				k++;
			}
		}
		else if(!strcmp(message,"6"))
		{
			fprintf(stdout,"Finished Jobs:\n");
			int k=1;
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				if(!strcmp(message,"|"))break;
				int id=atoi(message);
				fprintf(stdout,"%d). JobID %d Status: FINISHED\n",k,id);
				k++;
			}
		}
		else if(!strcmp(message,"7"))
		{
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			fprintf(stdout,"Sent Suspent signal to JobID %s\n",message);
		}
		else if(!strcmp(message,"8"))
		{
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			fprintf(stdout,"Sent Resume signal to JobID %s\n",message);
		}
		else if(!strcmp(message,"9"))
		{
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			int jobs=atoi(message);
			while(1)
			{
				memset(message, '\0', sizeof(message));
				if(read(fd1,message,5)<0)
				{
					continue;
				}
				break;
			}
			fprintf(stdout,"Served %d jobs,%d were still in progress\n",jobs,atoi(message));
			free(command);
			free(function);
			free(part);
			free(jms_in);
			free(jms_out);
			free(filename);
			raise(SIGTERM);
		}
	}
	int flag=0;
	sleep(1);
	//EDW THA MPEI OTAN TELEIWSOUN OI ENTOLES APO TO ARXEIO OPERATIONS(INPUT)//
		while(1)
		{
			int flag=0;
			int k=0;
			i=0;
			memset(command, '\0', sizeof(command));
			memset(function, '\0', sizeof(function));
			fprintf(stdout,"Vale entolh\n");
			fscanf(stdin,"%[^\n]%*c", function);
			if(!strcmp(function,"show-pools"))
			{
				flag=1;
			}
			if(!strcmp(function,"show-active"))
			{
				flag=1;
			}
			if(!strcmp(function,"show-finished"))
			{
				flag=1;
			}
			if(!strcmp(function,"shutdown"))
			{
				flag=1;
			}
			if(!strcmp(function,"status-all"))
			{
				flag=1;
			}
			if(flag==0)
			{
				memset(command, '\0', sizeof(command));
				for(i=0;i<30;i++)
				{
					strcpy(&command[i],"\0") ;
				}
				i=0;
				while(function[k]!=' ')
				{
					command[i]=function[k];
					i++;
					k++;
				}
			}
			if(!strcmp(command,"sumbit"))
			{
				flag=1;

			}
			if(!strcmp(command,"status"))
			{
				flag=1;
			}
			if(!strcmp(command,"status-all"))
			{
				flag=1;
			}

			if(!strcmp(command,"suspend"))
			{
				flag=1;
			}
			if(!strcmp(command,"resume"))
			{
				flag=1;
			}
			if(flag==0)continue;
			if(write(fd,function,30)==-1)
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			memset(message, '\0', sizeof(message));
			while(1)
			{
				if(read(fd1,message,1)<0)
				{
					continue;
				}
				break;
			}
			if(!strcmp(message,"0"))
			{
				continue;
			}
			if(!strcmp(message,"1"))
			{

				memset(message, '\0', sizeof(message));
				while(1)
				{
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				int id=atoi(message);
				memset(message, '\0', sizeof(message));
				while(1)
				{
					if(read(fd1,message,10)<0)
					{
						continue;
					}
					break;
				}
				fprintf(stdout,"JobID: %d ,PID: %d\n",id,atoi(message));
				continue;
			}
			else if(!strcmp(message,"2"))
			{
				memset(message, '\0', sizeof(message));
				while(1)
				{
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				int id=atoi(message);
				memset(message, '\0', sizeof(message));
				while(1)
				{
					if(read(fd1,message,30)<0)
					{
						continue;
					}
					break;
				}
				char status[30];
				strcpy(status,message);
				if(!(strcmp(message,"ACTIVE")))
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,30)<0)
					{
						continue;
					}
					fprintf(stdout,"JobID %d Status: %s (running for %d sec)\n",id,status,atoi(message));
				}
				else
				{
					fprintf(stdout,"JobID %d Status: %s\n",id,status);
				}
			}
			else if(!strcmp(message,"3"))
			{
					while(1)
					{
						memset(message, '\0', sizeof(message));
						while(1)
						{
							if(read(fd1,message,5)<0)
							{
								continue;
							}
							break;
						}
						if(!strcmp(message,"|"))break;
						if(strcmp(message,"3.1") && strcmp(message,"3.0"))continue;
						memset(message, '\0', sizeof(message));
						while(1)
						{
							if(read(fd1,message,5)<0)
							{
									continue;
							}
							break;
						}
						if(!strcmp(message,"|"))break;
						int id=atoi(message);
						memset(message, '\0', sizeof(message));
						while(1)
						{
							if(read(fd1,message,30)<0)
							{
									continue;
							}
							break;
						}
						if(!strcmp(message,"|"))break;
						char status[30];
						strcpy(status,message);
						if(!strcmp(status,"ACTIVE"))
						{
							while(1)
							{
								if(read(fd1,message,5)<0)
								{
									continue;
								}
								break;
							}
							if(!strcmp(message,"|"))break;
							fprintf(stdout,"JobID %d Status: %s (running for %d sec)\n",id,status,atoi(message));
						}
						else
						{
							fprintf(stdout,"JobID %d Status: %s\n",id,status);
						}
					}
			}
			else if(!strcmp(message,"4"))
			{
				fprintf(stdout,"Active Jobs:\n");
				int k=1;
				while(1)
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					if(!strcmp(message,"|"))break;
					int id=atoi(message);
					fprintf(stdout,"%d)  JobID %d Status: ACTIVE\n",k,id);
					k++;
				}
			}
			else if(!strcmp(message,"5"))
			{
				fprintf(stdout,"Pool & NumOfJobs console\n");
				int k=1;
				while(1)
				{
					while(1)
					{
						memset(message, '\0', sizeof(message));
						if(read(fd1,message,10)<0)
						{
							continue;
						}
						break;
					}
					if(!strcmp(message,"|"))break;
					int pid=atoi(message);
					while(1)
					{

						memset(message, '\0', sizeof(message));
						if(read(fd1,message,5)<0)
						{
							continue;
						}
						break;
					}
					if(!strcmp(message,"|"))break;
					fprintf(stdout,"%d). %d %d\n",k,pid,atoi(message));
					k++;
				}
			}
			else if(!strcmp(message,"6"))
			{
				fprintf(stdout,"Finished Jobs:\n");
				int k=1;
				while(1)
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					if(!strcmp(message,"|"))break;
					int id=atoi(message);
					fprintf(stdout,"%d). JobID %d Status: FINISHED\n",k,id);
					k++;
				}
			}
			else if(!strcmp(message,"7"))
			{
				while(1)
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				fprintf(stdout,"Sent suspent signal to JobID %s\n",message);
			}
			else if(!strcmp(message,"8"))
			{
				while(1)
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				fprintf(stdout,"Sent resume signal to JobID %s\n",message);
			}
			else if(!strcmp(message,"9"))
			{
				while(1)
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				int jobs=atoi(message);
				while(1)
				{
					memset(message, '\0', sizeof(message));
					if(read(fd1,message,5)<0)
					{
						continue;
					}
					break;
				}
				fprintf(stdout,"Served %d jobs,%d were still in progress\n",jobs,atoi(message));
				free(command);
				free(function);
				free(part);
				free(jms_in);
				free(jms_out);
				free(filename);
				raise(SIGTERM);
			}
		}
		free(command);
		free(function);
		free(part);
		free(jms_in);
		free(jms_out);
		free(filename);
}
