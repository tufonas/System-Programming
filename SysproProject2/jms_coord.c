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
#include <math.h>
typedef struct pool_pipes
{
	char* pool_in;
	char* pool_out;
}pool_pipes;
typedef struct process
{
	int pid;
	int jobid;
	int hour;
	int min;
	int sec;
	int duration;
	char status[30];
	int poolpid;
	int active_time;
	int suspend_time;
}process;
typedef struct pool
{
	int finished;
	int active;
	int total;
	int pid;
}pool;
int find_pool(char* message,int pools,int *x)
{
	int i,num,k=0;
	char mess[20];
	char number[10];
	memset(mess, '\0', sizeof(mess));
	for(i=0;i<strlen(message);i++)
	{
		if(message[i]==' ')
		{

			break;
		}
		mess[i]=message[i];
	}
	mess[i+1]='\0';
	memset(number, '\0', sizeof(number));
	if(!(strcmp(mess,"sumbit")))
	{
		return 0;
	}
	else if(!(strcmp(mess,"status")) || !(strcmp(mess,"suspend")) || !(strcmp(mess,"resume")))
	{
		while(message[i+1]-'0'>=0 && message[i+1]-'0'<10)
		{
			number[k]=message[i+1];
			k++;
			i++;
		}
		num=atoi(number);
		*x=num;
		int sum=num/pools;
		return sum;
	}
	else if ( !(strcmp(mess,"status-all")))
	{
		return -1;
	}
	else
	{
		return -3;
	}
}

int main(int argc,char* argv[])
{
	int i,j,fd,fd1,fd2,fd3,jobs_pool,jobs=0,pools=0,cnt=0,pid=-1;
	char *path;
	char *jms_in,*jms_out;
	char message1[30],message[30];
	char mess[20];
	pool_pipes *pipe=NULL;
	process processes[30];
	int fdin[10],fdout[10];
	pool pools1[30];
	for(i=0;i<argc;i++)											//DIAVAZW APO TO COMMAND LINE//
	{
		if(!strcmp(argv[i],"-l"))
		{
			path=malloc((strlen(argv[i+1])+1)*sizeof(char));
			if(path==NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(path,argv[i+1]);
		}
		if(!strcmp(argv[i],"-n"))
		{
			jobs_pool=atoi(argv[i+1]);
		}
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
	}
	if ( mkfifo ( jms_in , 0666) == -1 )				//FTIAXNW TA PIPES GIA THN EPIKOINWNIA COORD -CONSOLE//
	{
		if ( errno != EEXIST )
		{
			perror ( " receiver : mkfifo " );
			exit (6) ;
		}
	}
	if ( mkfifo ( jms_out , 0666) == -1 )
	{

		if ( errno != EEXIST )
		{
			perror ( " receiver : mkfifo " );
			exit (6) ;
		}
	}
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
	for(;;)
	{
		while(1)
		{
			if(read(fd,message1,30)<0)
			{
				for(j=0;j<pools;j++)
				{
					memset(message, '\0', sizeof(message));
					if(read(fdout[j],message,1)<0)									//DIAVAZW APO OLA TA POOLS//
					{
						continue;
					}
					if(!(strcmp(message,"1")))									//AN TO MUNHMA POU THA PARW EINAI 1 TOTE EIXA STEILEI SUMBIT//
					{
						int jobid,pid,poolpid,status1;
						while(1)
						{
							if(read(fdout[j],message,5)<0)
							{
								continue;
							}
							break;
						}
						jobid=atoi(message);
						while(1)
						{
							if(read(fdout[j],message,10)<0)
							{
								continue;
							}
							break;
						}
						pid=atoi(message);
						while(1)
						{
							if(read(fdout[j],message,10)<0)
							{
								continue;
							}
							break;
						}
						poolpid=atoi(message);
						while(1)
						{
							if(read(fdout[j],message,30)<0)
							{
								continue;
							}
							break;
						};
						char time[10];
						memset(time, '\0', sizeof(time));
						int l=0,m=0,hour,min,sec;
						while(message[l]!=':')
						{
							time[m]=message[l];
							m++;
							l++;
						}
						m=0;
						l++;
						hour=atoi(time);
						strcpy(time,"");
						memset(time, '\0', sizeof(time));
						while(message[l]!=':')
						{
							time[m]=message[l];
							m++;
							l++;
						}
						m=0;
						l++;
						min=atoi(time);
						strcpy(time,"");
						memset(time, '\0', sizeof(time));
						while(message[l]!=':')
						{
							time[m]=message[l];
							m++;
							l++;
						}
						sec=atoi(time);										//APOTHIKEUW TA STOIXEIA TWN JOBS SE ENA PINAKA//
						processes[jobid].hour=hour;
						processes[jobid].min=min;
						processes[jobid].sec=sec;
						processes[jobid].jobid=jobid;
						processes[jobid].pid=pid;
						processes[jobid].poolpid=poolpid;
						processes[jobid].active_time=0;
						processes[jobid].suspend_time=0;
						strcpy(processes[jobid].status,"ACTIVE");
						pools1[j].pid=poolpid;
						pools1[j].active++;
						pools1[j].total++;
						memset(message1, '\0', sizeof(message1));
						if(write(fd1,"1",1)==-1)
						{
								perror ( " problem in writing ");
								exit (5) ;
						}
						sprintf(message1,"%d",processes[jobid].jobid);
						if(write(fd1,message1,5)==-1)
						{
								perror ( " problem in writing ");
								exit (5) ;
						}
						memset(message1, '\0', sizeof(message1));
						sprintf(message1,"%d",processes[jobid].pid);
						if(write(fd1,message1,10)==-1)
						{
								perror ( " problem in wrinting ");
								exit (5) ;
						}
					}
					if(!(strcmp(message,"2")))									//AN TO MUNHMA POU THA PARW EINAI 2 TOTE PERIMENW NA PARW TA STATUS TWN JOBS POU EXOUN ALLAKSEI STATUS//
					{
						int pr,status;
						while(1)
						{
							if(read(fdout[j],message,2)<0)
							{
								continue;
							}
							break;
						}
						status=atoi(message);
						while(1)
						{
							if(read(fdout[j],message,30)<0)
							{
								continue;
							}
							break;
						}
						pr=atoi(message);
						while(1)
						{
							if(read(fdout[j],message,30)<0)
							{
								continue;
							}
							break;
						}
						char time[10];
						memset(time, '\0', sizeof(time));
						int l=0,m=0,hour,min,sec;
						while(message[l]!=':')
						{
							time[m]=message[l];
							m++;
							l++;
						}
						m=0;
						l++;
						hour=atoi(time);
						strcpy(time,"");
						memset(time, '\0', sizeof(time));
						while(message[l]!=':')
						{
							time[m]=message[l];
							m++;
							l++;
						}
						m=0;
						l++;
						min=atoi(time);
						strcpy(time,"");
						memset(time, '\0', sizeof(time));
						while(message[l]!=':')
						{
							time[m]=message[l];
							m++;
							l++;
						}
						sec=atoi(time);
						int y;

						for(y=j*jobs_pool;y<(j+1)*jobs_pool;y++)
						{
							if(y==jobs)break;
							if(processes[y].pid==pr)
							{
								if(status==1)			//ACTIVE//
								{
									if(!(strcmp(processes[y].status,"SUSPENTED")))
									{
										strcpy(processes[y].status,"ACTIVE");
										continue;
									}
									if(!(strcmp(processes[y].status,"ACTIVE")))
									{
										continue;
									}
									strcpy(processes[y].status,"ACTIVE");
									pools1[j].active++;
									pools1[j].finished--;
								}
								else if(status==-1)		//ERROR //
								{
									strcpy(processes[y].status,"ERROR");
								}
								else if(status==0)	//FINISHED
								{
									if(!(strcmp(processes[y].status,"FINISHED")))continue;
									strcpy(processes[y].status,"FINISHED");
									pools1[j].finished++;
									pools1[j].active--;
								}
								else if(status==2)			//SUSPENTED//
								{
									strcpy(processes[y].status,"SUSPENTED");
								}
							}
						}
						if(pools1[j].finished==jobs_pool)
						{
							if(write(fdin[j],"shutdown",30)==-1)
							{
									perror ( " problem in WRITING ");
									exit (5) ;
							}
						}
					}
					if(!(strcmp(message,"8")))							//AN TO MUNHMA POU THA PARW EINAI 8 TOTE EIXA STEILEI RESUME//
					{
						memset(message, '\0', sizeof(message));
						while(1)
						{
							if(read(fdout[j],message,10)<0)
							{
								continue;
							}
							break;
						}
						int pid=atoi(message);

						memset(message, '\0', sizeof(message));
						while(1)
						{
							if(read(fdout[j],message,5)<0)
							{
								continue;
							}
							break;
						}
						if(write(fd1,"8",1)==-1)
						{
								perror ( " problem in WRITING ");
								exit (5) ;
						}
						for(i=0;i<jobs;i++)
						{
							if(processes[i].pid==pid)
							{
								processes[i].suspend_time+=atoi(message);
								break;
							}
						}
						strcpy(processes[i].status,"ACTIVE");
						sprintf(message1,"%d",processes[i].jobid);
						if(write(fd1,message1,5)==-1)
						{
								perror ( " problem in reading ");
								exit (5) ;
						}
					}
					if(!(strcmp(message,"7")))								//AN TO MUNHMA POU THA PARW EINAI 7 TOTE EIXA STEILEI SUSPEND //
					{
						memset(message, '\0', sizeof(message));
						while(1)
						{
							if(read(fdout[j],message,10)<0)
							{
								continue;
							}
							break;
						}
						int Pid=atoi(message);
						memset(message, '\0', sizeof(message));
						while(1)
						{
							if(read(fdout[j],message,5)<0)
							{
								continue;
							}
							break;
						}
						if(write(fd1,"7",1)==-1)
						{
								perror ( " problem in reading ");
								exit (5) ;
						}
						for(i=0;i<jobs;i++)
						{
							if(processes[i].pid==Pid)
							{
								break;
							}
						}
						strcpy(processes[i].status,"SUSPENTED");
						processes[i].active_time+=atoi(message);
						sprintf(message1,"%d",processes[i].jobid);
						if(write(fd1,message1,5)==-1)
						{
								perror ( " problem in reading ");
								exit (5) ;
						}
					}
				}
				continue;
			}
			break;
		}
		memset(message, '\0', sizeof(message));
		fprintf(stdout,"command=%s\n",message1);
		memset(mess, '\0', sizeof(mess));
		for(j=0;j<strlen(message1);j++)
		{
			if(message1[j]==' ')
			{
				strncpy(mess,message1,j);
				break;
			}
		}
		int k=0;
		if(!(strcmp(mess,"sumbit")))			//an to munhma pou hrthe einai sumbit//
		{
			if(cnt==jobs_pool || pid==-1)		//ftiaxnw kainourgio pool//
			{
				cnt=0;
				if(pipe==NULL)
					pipe=malloc(sizeof(pool_pipes));
				else
					pipe=realloc(pipe,(pools+1)*sizeof(pool_pipes));
				pipe[pools].pool_in=malloc(50*sizeof(char));
				pipe[pools].pool_out=malloc(50*sizeof(char));
				strcpy(pipe[pools].pool_in,path);
				strcpy(pipe[pools].pool_out,path);
				strcat(pipe[pools].pool_in,"pool_in");
				strcat(pipe[pools].pool_out,"pool_out");
				char cpid[3];
				sprintf(cpid,"%d",pools);
				strcat(pipe[pools].pool_in,cpid);
				strcat(pipe[pools].pool_out,cpid);
				if ( mkfifo (pipe[pools].pool_in, 0666) == -1 )
				{

					if ( errno != EEXIST )
					{
						perror ( " receiver : mkfifo " );
						exit (6) ;
					}
				}

				if ( mkfifo (pipe[pools].pool_out, 0666) == -1 )
				{

					if ( errno != EEXIST )
					{
						perror ( " receiver : mkfifo " );
						exit (6) ;
					}
				}
				if((fdin[pools]=open(pipe[pools].pool_in,O_RDWR | O_NONBLOCK))<0)			//DHMIOURGW PINAKA APO PIPES GIA OLA TA POOLS POU THA XREIASTW//
				{
						perror (" POOL_IN  open problem ");
						exit (3) ;
				}
				if((fdout[pools]=open(pipe[pools].pool_out,O_RDWR | O_NONBLOCK))<0)
				{
						perror (" POOL_out open problem ");
						exit (3) ;
				}
				pools++;
				jobs++;
				cnt++;
				pools1[pools-1].total=0;
				pools1[pools-1].finished=0;
				pools1[pools-1].active=0;
				if((pid=fork())==-1)			//fork error/
				{
					perror ( " fork ");
					exit (1) ;
				}
				else if(pid==0)					//fork paidi//
				{

					strcat(message1,"|");
					char jobID[5];
					sprintf(jobID,"%d",jobs-1);
					strcat(message1,jobID);
					if(write(fdin[pools-1],message1,30)==-1)
					{
							perror ( " problem in reading ");
							exit (5) ;
					}
					char *argv1[] = { "./pool", pipe[pools-1].pool_in, pipe[pools-1].pool_out, path,NULL };
					char * cwd;
					cwd = getcwd (0, 0);
					strcat(cwd,"/pool");
					execve(cwd,argv1,NULL);
					perror("exec");
					exit(2);
				}
				else					//fork pateras//
				{
				}
			}
			else			//eimai se ena pool pou xwraei kai allo job
			{
				jobs++;
				cnt++;
				strcat(message1,"|");
				char jobID[5];
				sprintf(jobID,"%d",jobs-1);
				strcat(message1,jobID);
				if(write(fdin[pools-1],message1,30)==-1)
				{
						perror ( " problem in reading ");
						exit (5) ;
				}
			}
		}
		else if(!(strcmp(mess,"status")))			//an to munhma pou hrthe einai status//
		{

			char jobID1[10];
			memset(jobID1, '\0', sizeof(jobID1));
			k=0;
			i=0;
			while(!(message1[i]-'0' <10 && message1[i]-'0'>=0))
			{
				i++;
			}
			while(message1[i]-'0' <10 && message1[i]-'0'>=0)
			{
				jobID1[k]=message1[i];
				i++;
				k++;
			}
			k=0;
			int flag=0;
			for(k=0;k<jobs;k++)
			{
				if(processes[k].jobid==atoi(jobID1))			//AN TO JOBID EINAI AUTO POU ME ENDIAFEREI SUNEXIZW//
				{
					if(write(fd1,"2",1)==-1)
					{
							perror ( " problem in WRITING ");
							exit (5) ;
					}
					time_t t = time(NULL);						//METRAW THN WRA//
					struct tm tm = *localtime(&t);
					int diafora1,diafora2,diafora3;
					int minutes=tm.tm_min-processes[k].min;
					int hours=tm.tm_hour-processes[k].hour;
					int sec=tm.tm_sec-processes[k].sec;
					diafora3=sec;
					diafora1=hours*240;
					if(hours<0)
					{
						diafora1=23-processes[k].hour+tm.tm_hour;
						diafora1=diafora1*240;
					}
					else if(hours==1)
					{
						diafora1=0;
					}
					diafora2=(minutes)*60;
					if(minutes<0)
					{
						diafora2=59-processes[k].min+tm.tm_min;
						diafora2=diafora2*60;
					}
					else if(minutes==1)
					{
						diafora2=0;
					}
					if(sec<0)
					{
						if(diafora2>0)
						diafora2=diafora2-60;
						diafora3=60-processes[k].sec+tm.tm_sec;
					}
					sprintf(message1,"%d",processes[k].jobid);
					if(write(fd1,message1,5)==-1)					//GRAFW STO CONSOLE //
					{
							perror ( " problem in WRITING ");
							exit (5) ;
					}
					if(write(fd1,processes[k].status,30)==-1)
					{
							perror ( " problem in WRITING ");
							exit (5) ;
					}
					if(!(strcmp(processes[k].status,"ACTIVE")))
					{
						sprintf(message1,"%d",diafora1+diafora2+diafora3-processes[k].suspend_time);
						if(write(fd1,message1,5)==-1)
						{
								perror ( " problem in WRITING ");
								exit (5) ;
						}
					}
					flag=1;
				}
			}
			if(k==jobs && flag==0)
			{
				fprintf(stdout,"To Jobid den uparxei\n");
				if(write(fd1,"0",1)==-1)					//GRAFW STO CONSOLE 0 POU SHMAINEI ERROR//
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
			}
		}
		else if(!(strcmp(message1,"status-all")) || !(strcmp(mess,"status-all")))
		{
			if(write(fd1,"3",1)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			int diafora1,diafora2,diafora3;
			int minutes=tm.tm_min-processes[k].min;
			int hours=tm.tm_hour-processes[k].hour;
			int sec=tm.tm_sec-processes[k].sec;
			diafora3=sec;
			diafora1=hours*240;
			if(hours<0)
			{
				diafora1=23-processes[k].hour+tm.tm_hour;
				diafora1=diafora1*240;
			}
			else if(hours==1)
			{
				diafora1=0;
			}
			diafora2=(minutes)*60;
			if(minutes<0)
			{
				diafora2=59-processes[k].min+tm.tm_min;
				diafora2=diafora2*60;
			}
			else if(minutes==1)
			{
				diafora2=0;
			}
			if(sec<0)
			{
				if(diafora2>0)
				diafora2=diafora2-60;
				diafora3=60-processes[k].sec+tm.tm_sec;
			}
			for(i=0;i<jobs;i++)
			{
				if(!(strcmp(message1,"status-all")))				//AN H ENTOLH EINAI STATUS-ALL TOTE MPAINEI EDW//
				{
					if(write(fd1,"3.0",5)==-1)
					{
							perror ( " problem in WRITING ");
							exit (5) ;
					}
					memset(message, '\0', sizeof(message));
					sprintf(message,"%d",processes[i].jobid);
					if(write(fd1,message,5)==-1)
					{
							perror ( " problem in WRITING ");
							exit (5) ;
					}
					if(write(fd1,processes[i].status,30)==-1)
					{
							perror ( " problem in WRITING ");
							exit (5) ;
					}
					if(!(strcmp(processes[i].status,"ACTIVE")))
					{
						memset(message, '\0', sizeof(message));
						sprintf(message,"%d",diafora1+diafora2+diafora3-processes[i].suspend_time);
						if(write(fd1,message,5)==-1)
						{
								perror ( " problem in WRITING ");
								exit (5) ;
						}
					}
				}
				else if(!(strcmp(mess,"status-all")))				//AN H ENTOLH EINAI STATUS-ALL KAI ENA ORISMA META TOTE MPAINEI EDW//
				{
					char msg[10];
					int x=0,y=0;
					memset(msg, '\0', sizeof(msg));
					while(message1[x]!=' ')
					{
						x++;
					}
					x++;
					while(message1[x]-'0'<10 && message1[x]-'0'>=0)
					{
						msg[y]=message1[x];
						x++;
						y++;
					}
					if(diafora1+diafora2+diafora3<=atoi(msg))
					{
						if(write(fd1,"3.1",5)==-1)
						{
								perror ( " problem in WRITING ");
								exit (5) ;
						}
						memset(message, '\0', sizeof(message));
						sprintf(message,"%d",processes[i].jobid);
						if(write(fd1,message,5)==-1)
						{
								perror ( " problem in WRITING ");
								exit (5) ;
						}
						if(write(fd1,processes[i].status,30)==-1)
						{
								perror ( " problem in WRITING ");
								exit (5) ;
						}
						if(!(strcmp(processes[i].status,"ACTIVE")))
						{
							memset(message, '\0', sizeof(message));
							sprintf(message,"%d",diafora1+diafora2+diafora3-processes[i].suspend_time);
							if(write(fd1,message,5)==-1)
							{
									perror ( " problem in WRITING ");
									exit (5) ;
							}
						}
					}
				}
			}
			if(write(fd1,"|",5)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
		}
		else if(!(strcmp(message1,"show-active")))
		{
			if(write(fd1,"4",1)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			for(k=0;k<jobs;k++)
			{
				if(!(strcmp(processes[k].status,"ACTIVE")))
				{
					sprintf(message1,"%d",processes[k].jobid);
					if(write(fd1,message1,5)==-1)
					{
							perror ( " problem in WRITING ");
							exit (5) ;
					}
				}
			}
			if(write(fd1,"|",5)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
		}
		else if(!(strcmp(message1,"show-pools")))
		{
			if(write(fd1,"5",1)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			for(k=0;k<pools;k++)
			{
				sprintf(message1,"%d",pools1[k].pid);
				if(write(fd1,message1,10)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				sprintf(message1,"%d",pools1[k].total-pools1[k].finished);
				if(write(fd1,message1,5)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
			}
			if(write(fd1,"|",5)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
		}
		else if(!(strcmp(message1,"show-finished")))
		{
			if(write(fd1,"6",1)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			for(k=0;k<jobs;k++)
			{
				if(!(strcmp(processes[k].status,"FINISHED")))
				{
					sprintf(message1,"%d",processes[k].jobid);
					if(write(fd1,message1,5)==-1)
					{
							perror ( " problem in WRITING ");
							exit (5) ;
					}
				}
			}
			if(write(fd1,"|",5)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
		}
		else if(!(strcmp(mess,"suspend")))
		{
			int Job;
			char Jobid[5];
			memset(Jobid, '\0', sizeof(Jobid));
			int curr_pool=find_pool(message1,jobs_pool,&Job);
			if(curr_pool>=pools)
			{
				fprintf(stdout,"Den uparxei tetoio jobid\n");
				if(write(fd1,"0",1)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				continue;
			}
			if((strcmp(processes[Job].status,"SUSPENTED")) && (strcmp(processes[Job].status,"ACTIVE")) && (strcmp(processes[Job].status,"FINISHED")))
			{
				fprintf(stdout,"To Jobid auto den exei dhmiourgithei akoma\n");
				if(write(fd1,"0",1)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				continue;
			}
			if(!(strcmp(processes[Job].status,"SUSPENTED")))
			{
				fprintf(stdout,"To job einai hdh Suspented\n");
				if(write(fd1,"0",1)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				continue;
			}
			if(!(strcmp(processes[Job].status,"FINISHED")))
			{
				fprintf(stdout,"To job einai Finished\n");
				if(write(fd1,"0",1)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				continue;
			}
			if(write(fdin[curr_pool],message1,30)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			sprintf(Jobid,"%d",Job);
			if(write(fdin[curr_pool],Jobid,5)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
		}
		else if(!(strcmp(mess,"resume")))
		{
			int Job;
			int curr_pool=find_pool(message1,jobs_pool,&Job);
			char Jobid[5];
			memset(Jobid, '\0', sizeof(Jobid));
			if(curr_pool>=pools)
			{
				fprintf(stdout,"Den uparxei tetoio jobid\n");
				if(write(fd1,"0",1)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				continue;
			}
			if((strcmp(processes[Job].status,"SUSPENTED")) && (strcmp(processes[Job].status,"ACTIVE")) && (strcmp(processes[Job].status,"FINISHED")))
			{
				fprintf(stdout,"To Jobid auto den exei dhmiourgithei akoma\n");
				if(write(fd1,"0",1)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				continue;
			}
			if(!(strcmp(processes[Job].status,"ACTIVE")))
			{
				fprintf(stdout,"To job einai hdh Active\n");
				if(write(fd1,"0",1)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				continue;
			}
			if(!(strcmp(processes[Job].status,"FINISHED")))
			{
				fprintf(stdout,"To job einai Finished\n");
				if(write(fd1,"0",1)==-1)
				{
						perror ( " problem in WRITING ");
						exit (5) ;
				}
				continue;
			}

			if(write(fdin[curr_pool],message1,30)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			sprintf(Jobid,"%d",Job);
			if(write(fdin[curr_pool],Jobid,5)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
		}
		else if(!(strcmp(message1,"shutdown")))
		{
			if(write(fd1,"9",1)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			fprintf(stdout,"SHUTDOWN\n");
			int sum=0,sum1=0;
			for(k=0;k<pools;k++)
			{
				fprintf(stdout,"stelnw shma termatismou sthn diergasia %d\n",pools1[k].pid);		//STELNW SHMA TERMATISMOU SE OLA TA POOLS//
				kill(pools1[k].pid,SIGTERM);
				sum=sum+pools1[k].total-pools1[k].finished;
			}
			sprintf(message1,"%d",jobs);
			if(write(fd1,message1,5)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			sprintf(message1,"%d",sum);
			if(write(fd1,message1,5)==-1)
			{
					perror ( " problem in WRITING ");
					exit (5) ;
			}
			close(fd);
			for(k=0;k<pools;k++)			//KLEINW TA ARXEIA MOU//
			{
				close(fdin[k]);
				close(fdout[k]);
			}
			free(path);
			free(jms_in);
			free(jms_out);
			for(k=0;k<pools;k++)
			{
				free(pipe[k].pool_in);
				free(pipe[k].pool_out);
			}
			free(pipe);
			raise(SIGTERM);			//TERMATIZW TON EUATO MOU//
		}
	}



}
