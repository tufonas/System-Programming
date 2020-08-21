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
typedef struct process
{
	int pid;
	int jobid;
	int hour;
	int min;
	int sec;
	int duration;
	int status;
	int active_time;
	int suspend_hour;
	int suspend_min;
	int suspend_sec;
	int suspend_time;
}process;
int signal_term=0;
void term()
{
	signal_term=1;
	return;
}
int main(int argc,char* argv[])
{
	int fd,fd1,j,jobs=0,pid=-1;
	char message1[30],mess[30],command[30];
	process pr[10];
	pid_t result;
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigfillset (&( action . sa_mask ));
	sigaction ( SIGTERM , & action , NULL );
	int status1[10];
	for(j=0;j<10;j++)
	{
		status1[j]=-2;
	}
	if((fd=open(argv[1],O_RDWR | O_NONBLOCK))<0)
	{
		perror (" pipe open problem ");
		exit (3) ;
	}
	if((fd1=open(argv[2],O_RDWR | O_NONBLOCK))<0)
	{
		perror (" pipe open problem ");
		exit (3) ;
	}
	for(;;)
	{

		int k=0;
		while(1)
		{
			if(signal_term==1)		//EXW MIA GLOBAL METAVLHTH SIGNAL_TERM POU EINAI 0.OTAN O COORD PAREI TO MUNHMA SHUTDOWN STELNEI STO POOL SHMA SIGTERM.ETSI ME THN SUNARTHSH TERM() XEIRIZOMAI TO //
			{							//SHMA KATALLHLA KAI TERMATIZW OLA TA JOBS POU EXW KAI META TO IDIO TO POOL//
				for(k=0;k<jobs;k++)
				{
					fprintf(stdout,"stelnw sigterm sthn diergasia %d\n",pr[k].pid);
					kill(pr[k].pid,SIGTERM);
				}
				action.sa_handler = SIG_DFL;
				sigaction ( SIGTERM , & action , NULL );
				raise(SIGTERM);
			}
			if(read(fd,message1,30)<0)
			{
					for(j=0;j<jobs;j++)
					{
						int status;
						int flag=-1;
						char msg[30];
						result = waitpid(pr[j].pid, &status, WNOHANG | WUNTRACED);
						if (result == 0)		//paidi zwntano//
						{
							if(pr[j].status==2)continue;	//edw shmainei oti einai suspented opote sunexizei kanonika mexri na parei shma resume//
							pr[j].status=1;
							flag=1;
						}
						else if (result == -1)	//paidi error//
						{

							if(pr[j].status==0)continue;		//an mpei edw shmainei oti to paidi exei teleisei kai den xreiazetai na kanei kati allo//
							pr[j].status=-1;
							if(WIFEXITED(status))			//paidi finished//
							{
								flag=0;
								pr[j].status=0;
							}
						}
						else			//paidi stamathmeno//
						{
							flag=0;
							pr[j].status=0;
							if(WIFSTOPPED(status))
							{
								pr[j].status=2;
							}
						}
						if(status1[j]!=pr[j].status && status1[j]!=-2)
						{
							if(write(fd1,"2",1)==-1)
							{
									perror ( " problem in writing ");
									exit (5) ;
							}
							if(pr[j].status==2)//stamathmeno
							{
								if(write(fd1,"2",2)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
								sprintf(msg,"%d",pr[j].pid);
								if(write(fd1,msg,30)==-1)
								{
									perror ( "Problem in WRITING ");
										exit (5) ;
								}
								sprintf(msg,"%d:%d:%d:",pr[j].hour,pr[j].min,pr[j].sec);
								if(write(fd1,msg,30)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
							}
							else if(pr[j].status==-1)//error
							{
								if(write(fd1,"-1",2)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
								sprintf(msg,"%d",pr[j].pid);
								if(write(fd1,msg,30)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
								sprintf(msg,"%d:%d:%d:",pr[j].hour,pr[j].min,pr[j].sec);
								if(write(fd1,msg,30)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
							}
							else if(pr[j].status==0)//finished
							{
								if(write(fd1,"0",2)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
								sprintf(msg,"%d",pr[j].pid);
								if(write(fd1,msg,30)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
								sprintf(msg,"%d:%d:%d:",pr[j].hour,pr[j].min,pr[j].sec);
								if(write(fd1,msg,30)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
							}
							else if(pr[j].status==1)//zwntano
							{
								if(write(fd1,"1",2)==-1)
								{

										perror ( "Problem in WRITING ");
										exit (5) ;
								}
								sprintf(msg,"%d",pr[j].pid);
								if(write(fd1,msg,30)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
								sprintf(msg,"%d:%d:%d:",pr[j].hour,pr[j].min,pr[j].sec);
								if(write(fd1,msg,30)==-1)
								{
										perror ( "Problem in WRITING ");
										exit (5) ;
								}
							}
						}
						status1[j]=pr[j].status;
					}
					continue;
			}
			break;
		}
		memset(mess, '\0', sizeof(mess));
		for(j=0;j<strlen(message1);j++)
		{
			if(message1[j]==' ')
			{
				strncpy(mess,message1,j);
				break;
			}
		}
		if(!(strcmp(mess,"sumbit")))			//ENTOLH SUMBIT //
		{
			jobs++;
			char jobID[4],date[10],times[7],help[10],filename[50];
			memset(jobID, '\0', sizeof(jobID));
			int k=0;
			int p;
			memset(command, '\0', sizeof(command));
			memset(filename, '\0', sizeof(filename));
			for(p=j+1;p<strlen(message1);p++)
			{
				if(message1[p]=='|')
				{
					break;
				}
				command[k]=message1[p];
				k++;
			}
			k=0;
			while(message1[p+1]- '0' <10 && message1[p+1]- '0'>=0)
			{
				jobID[k]=message1[p+1];
				p++;
				k++;
			}
			k=0;

			if((pid=fork())==-1)				//FTIAXNW THN DIERGASIA JOB POU THA EKTELESTEI TO JOB POU HRTHE//
			{
				perror ( " fork ");
				exit (1) ;
			}
			else if(pid==0)
			{

				strcat(filename,"sdi1400266_");
				strcat(filename,jobID);
				strcat(filename,"_");

				//EDW PAIRNW THN WRA GIA NA THN VALW STO ONOMA TOU DIRECTORY POU THA DHMIOURGISW//
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				sprintf(date,"%d",tm.tm_year+1900);
				if(tm.tm_mon<10)
					sprintf(help,"0%d",tm.tm_mon+1);
				else
					sprintf(help,"%d",tm.tm_mon+1);
				strcat(date,help);
				strcpy(help,"");
				if(tm.tm_mday<10)
				{
					sprintf(help,"0%d",tm.tm_mday);
				}
				else
				{
					sprintf(help,"%d",tm.tm_mday);
				}
				strcat(date,help);
				if(tm.tm_hour<10)
					sprintf(times,"0%d",tm.tm_hour);
				else
					sprintf(times,"%d",tm.tm_hour);
				strcpy(help,"");
				if(tm.tm_min<10)
					sprintf(help,"0%d",tm.tm_min);
				else
					sprintf(help,"%d",tm.tm_min);
				strcat(times,help);
				strcpy(help,"");
				if(tm.tm_sec<10)
				{
					sprintf(help,"0%d",tm.tm_sec);
				}
				else
				{
					sprintf(help,"%d",tm.tm_sec);
				}
				strcat(times,help);
				strcpy(jobID,"");
				sprintf(jobID,"%d",getpid());
				strcat(filename,jobID);
				strcat(filename,"_");
				strcat(filename,date);
				strcat(filename,"_");
				strcat(filename,times);
				char path[50];
				memset(path, '\0', sizeof(path));
				strcpy(path,argv[3]);
				strcat(path,filename);
				if(	mkdir(path,0777)==-1)
				{
					perror("mkdir:");
				}
				int file1,file2;
				strcat(path,"/stdout_jobid.txt");
				//AFOU EXW PAREI TO PATH TWN DIRECTORIES POU DHMIOURGISA FTIAXNW TA ARXEIA STDOUT KAI STDERR POU XREIAZOMASTE//
				if((file1=open(path,O_RDWR| O_CREAT,0666))<0)
				{
						perror (" Open problem ");
						exit (3) ;
				}
				memset(path, '\0', sizeof(path));
				strcpy(path,argv[3]);
				strcat(path,filename);
				strcat(path,"/stderr_jobid.txt");
				if((file2=open(path,O_CREAT | O_RDWR ,0666))<0)
				{
						perror (" Open problem ");
						exit (3) ;
				}
				dup2(file1,1);		//XRHSIMOPOIW THN ENTOLH AUTH ETSI WSTE NA ALLAKSW TO REUMA TOU STDOUT .TO VAZW NA EKTUPWNEI MESA STO ARXEIO POU EFTIAKSA//
				dup2(file2,2);		//XRHSIMOPOIW THN ENTOLH AUTH ETSI WSTE NA ALLAKSW TO REUMA TOU STDERR .TO VAZW NA EKTUPWNEI MESA STO ARXEIO POU EFTIAKSA//
				execlp("./job","./job",command,path,NULL);			//KANW EXEC TO JOB//
				perror("ececlp:");
			}
			else
			{
				time_t t = time(NULL);					//EDW ARXIKOPOIW THN DOMH POU KRATW GIA TIS PLHROFORIES TWN JOBS POU EKTELEI TO POOL//
				struct tm tm = *localtime(&t);
				pr[jobs-1].pid=pid;
				pr[jobs-1].jobid=atoi(jobID);
				pr[jobs-1].hour=tm.tm_hour;
				pr[jobs-1].min=tm.tm_min;
				pr[jobs-1].sec=tm.tm_sec;
				pr[jobs-1].duration=0;
				pr[jobs-1].status=-1;
			}
			if(write(fd1,"1",1)==-1)				//GRAFW PISW STON COORD TO 1 POU SHMAINEI OTI EIMAI STO SUMBIT //
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			memset(message1, '\0', sizeof(message1));
			sprintf(message1,"%d",pr[jobs-1].jobid);
			if(write(fd1,message1,5)==-1)				//GRAFW STON COORD TO JOBID THS DIERGASIA POU EFTIAKSA//
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			memset(message1, '\0', sizeof(message1));
			sprintf(message1,"%d",pr[jobs-1].pid);		//GRAFW STON COORD TO PID THS DIERGASIA POU EFTIAKSA//
			if(write(fd1,message1,10)==-1)
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			memset(message1, '\0', sizeof(message1));
			sprintf(message1,"%d",getpid());			//GRAFW STON COORD TO POOL_PID //
			if(write(fd1,message1,10)==-1)
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			memset(message1, '\0', sizeof(message1));
			sprintf(message1,"%d:%d:%d:",pr[jobs-1].hour,pr[jobs-1].min,pr[jobs-1].sec);
			if(write(fd1,message1,30)==-1)				//GRAFW STON COORD TO TIME POU KSEKINHSE H  DIERGASIA POU EFTIAKSA//
			{
				perror ( "problem in writing ");
				exit (5) ;
			}
		}
		else if(!(strcmp(mess,"suspend")))				//ENOLH SUSPEND//
		{
			int status;
			while(1)								//EDW PERIMENW NA DIABASW TO JOBID POU THA MOU DWSEI TO COORD ETSI WSTE NA KSEKINHSW TO SUSPEND THS DIERGASIAS AUTHS//
			{
				if(read(fd,message1,5)==-1)
				{
					continue;
						perror ( " problem in writing ");
						exit (5) ;
				}
				break;
			}
			for(k=0;k<jobs;k++)
			{
				if(pr[k].jobid==atoi(message1))			//PSAXNW NA VRW POIO PID EINAI AUTO POU TAIRIAZEI ME TO JOBID POU STALTHIKE//
				{
					status=k;
				}
			}
			kill(pr[status].pid,SIGSTOP);				//KANW SUSPEND THN DIERGASIA STELNWNTAS SHMA SIGSTOP//
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			int diafora1,diafora2,diafora3;
			int minutes=tm.tm_min-pr[status].min;
			int hours=tm.tm_hour-pr[status].hour;
			int sec=tm.tm_sec-pr[status].sec;
			diafora3=sec;
			diafora1=hours*240;
			if(hours<0)
			{
				diafora1=23-pr[status].hour+tm.tm_hour;
				diafora1=diafora1*240;
			}
			else if(hours==1)
			{
				diafora1=0;
			}
			diafora2=(minutes)*60;
			if(minutes<0)
			{
				diafora2=59-pr[status].min+tm.tm_min;
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
				diafora3=60-pr[status].sec+tm.tm_sec;
			}
			pr[status].suspend_hour=tm.tm_hour;						//EDW PAIRNW THN WRA POU EGINE SUSPEND//
			pr[status].suspend_min=tm.tm_min;
			pr[status].suspend_sec=tm.tm_sec;
			pr[status].active_time=diafora1+diafora2+diafora3;
			if(write(fd1,"7",1)==-1)								//GRAFW TO 7 STO COORD POU SHMAINEI OTI EINAI SUSPEND//
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			char msg[10];
			memset(msg, '\0', sizeof(msg));
			sprintf(msg,"%d",pr[status].pid);						//GRAFW STON COORD TO PID THS DIERGASIAS POU EKANA SUSPEND//
			if(write(fd1,msg,10)==-1)
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			memset(msg, '\0', sizeof(msg));
			sprintf(msg,"%d",pr[status].active_time);				//GRAFW STON COORD TO ACTIVE XRONO THS DIERGASIAS POU EKANA SUSPEND//
			if(write(fd1,msg,5)==-1)
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
		}
		else if(!(strcmp(mess,"resume")))					//ENTOLH RESUME//
		{
			int status;
			while(1)
			{
				if(read(fd,message1,5)==-1)				//EDW PERIMENW NA DIABASW TO JOBID POU THA MOU DWSEI TO COORD ETSI WSTE NA KSEKINHSW TO RESUME THS DIERGASIAS AUTHS//
				{
					continue;
						perror ( " problem in writing ");
						exit (5) ;
				}
				break;
			}
			for(k=0;k<jobs;k++)
			{
				if(pr[k].jobid==atoi(message1))			//PSAXNW NA VRW POIO PID EINAI AUTO POU TAIRIAZEI ME TO JOBID POU STALTHIKE//
				{
					status=k;
				}
			}
			kill(pr[status].pid,SIGCONT);				//KANW RESUME THN DIERGASIA STELNWNTAS SHMA SIGCONT//

			//GIA TA UPOLOIPA ISXUEI OTI KAI STO SUSPEND//
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			int diafora1,diafora2,diafora3;
			int minutes=tm.tm_min-pr[status].suspend_min;
			int hours=tm.tm_hour-pr[status].suspend_hour;
			int sec=tm.tm_sec-pr[status].suspend_sec;
			diafora3=sec;
			diafora1=hours*240;
			if(hours<0)
			{
				diafora1=23-pr[status].suspend_hour+tm.tm_hour;
				diafora1=diafora1*240;
			}
			else if(hours==1)
			{
				diafora1=0;
			}
			diafora2=(minutes)*60;
			if(minutes<0)
			{
				diafora2=59-pr[status].suspend_min+tm.tm_min;
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
				diafora3=60-pr[status].suspend_sec+tm.tm_sec;
			}
			pr[status].status=1;
			pr[status].suspend_time=diafora1+diafora2+diafora3;
			if(write(fd1,"8",1)==-1)
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			char msg[10];
			memset(msg, '\0', sizeof(msg));
			sprintf(msg,"%d",pr[status].pid);
			if(write(fd1,msg,10)==-1)
			{
					perror ( " problem in writing ");
					exit (5) ;
			}
			memset(message1, '\0', sizeof(message1));
			sprintf(message1,"%d:",pr[status].suspend_time);
			if(write(fd1,message1,5)==-1)
			{
				perror ( " problem in writing ");
				exit (5) ;
			}
		}
		else if(!(strcmp(message1,"shutdown")))					//ENTOLH SHUTDOWN.EDW THA MPEI MONO OTAN ENA POOL TELEIWSEI OLES TIS JOBS TOU KAI PREPEI NA TERMATISEI//
		{
			fprintf(stdout,"EIMAI TO POOL %d kai kanw exit\n",getpid());
			action.sa_handler = SIG_DFL;					//KANW TON SIGNAL HANDLER NA EINAI DEFAULT//
			sigaction ( SIGTERM , & action , NULL );
			raise(SIGTERM);									//EDW TOU DINW SHMA SIGTERM GIA NA TERMATISEI TO POOL//
		}
	}
	exit(1);
}
