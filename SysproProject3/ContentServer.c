#include <stdio.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <sys/stat.h>
#include <netinet/in.h> /* internet sockets */
#include <unistd.h> /* read , write , close */
#include <netdb.h> /* ge th os tb ya dd r */
#include <stdlib.h> /* exit */
#include <sys/wait.h>
#include <ctype.h>
#include <string.h> /* strlen */
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
void error(char *msg)
{
    perror(msg);
    exit(1);
}
typedef struct server
{
	int id;
	int port;
	int delay;
	char adress[100];
	int files;
	int numb;
}server;
int fetched_files[20];
int i_am_in=0;
void write_directories(char* pathname,int newsockfd,int id);
void search(char *pathname,char *dirorfilename,int portno,char *adress,int newsockfd,int i);
int main(int argc, char *argv[])
{
	int i;
	int sockfd, newsockfd, portno, clilen;
	char* pathname;
	server servers[20];
	int server_place=0;
	int id,delay,number_of_servers;//real one//
	char adress[100];
	for(i=0;i<argc;i++)
	{
		if(!strcmp(argv[i],"-d"))
		{
			pathname=malloc((strlen(argv[i+1]))*sizeof(char));
			strcpy(pathname,argv[i+1]);
		}
		if(!strcmp(argv[i],"-p"))
		{
			portno = atoi ( argv [i+1]) ;
		}
	}
	for(i=0;i<20;i++)
	{
		servers[i].files=-1;
	}
     char buffer[256];
     char *dirorfilename=malloc(256*sizeof(char));
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr =htonl( INADDR_ANY);
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
              error("ERROR on binding");
 	if ( listen ( sockfd , 5) < 0)
 	{
 		perror ( " listen ") ; exit ( -1) ;
 	}
 	for(i=0;i<20;i++)
 	{
 		fetched_files[i]=0;
 	}
 	while(1)					/*h while auth trexei sunexws kai pernei aithseis LIST kai FETCH*/
 	{
		clilen = sizeof(cli_addr);
		fprintf(stdout,"I am waiting for connection\n");
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);		/*sundesh me MirrorManager*/
		if (newsockfd < 0)
			  error("ERROR on accept");
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);							/*diavazei ENTOLH FETCH H LIST*/
		if (n < 0)
			error("ERROR reading from socket");
		strtok(buffer," ");

		if(strcmp(buffer,"LIST")==0)						/*AN EINAI LIST*/
		{
			delay=atoi(strtok(NULL," "));
			strcpy(adress,strtok(NULL," "));
			number_of_servers=atoi(strtok(NULL," "));
			id=atoi(strtok(NULL," "));
			fprintf(stdout,"Here is the message: delay=%d\n",delay);
			servers[server_place].delay=delay;
			fprintf(stdout,"Here is the message: adress=%s\n",adress);
			strcpy(servers[server_place].adress,adress);
			fprintf(stdout,"Here is the message: number=%d\n",number_of_servers);
			servers[server_place].numb=number_of_servers;
			servers[server_place].id=id;
			fprintf(stdout,"Here is the message: ID=%d\n",id);
			bzero(buffer,256);
			sprintf(buffer,"%s_%d",pathname,servers[server_place].id);
			n = write(newsockfd,buffer,255);					/*Grafw stous MirrorManagers to pathname pou upakouei o Content kai to id tou*/
			if (n < 0)
				perror("ERROR writing to socket");
			write_directories(pathname,newsockfd,servers[server_place].id);    		/*stelnei anadromika stous MirrorManagers thn lista me ta arxeia pou kanei share*/
			server_place++;
			n = write(newsockfd,"END",255);						/*molis teleiwsei thn olh diadikasia stelnei to END pou shmainei oti h entolh LIST teleiwse*/
			if (n < 0)
				 error("ERROR writing to socket");
			printf("esteila to end\n");
		}
		else if(strcmp(buffer,"FETCH")==0)			/*AN EINAI FETCH*/
		{
			bzero(dirorfilename,256);
			strcpy(dirorfilename,strtok(NULL," "));
			id=atoi(strtok(NULL," "));
			bzero(buffer,256);
			int i;
			for(i=0;i<server_place;i++)
			{
				if(servers[i].id==id)
				{
					break;
				}
			}
			FILE *sock_fp ;
			fprintf(stdout,"i am sleeping...for %d sec\n",servers[i].delay);
			sleep(servers[i].delay);
			fprintf(stdout,"i woke up\n");
			int fd;
			if((fd = open(&dirorfilename[1], O_RDWR))>=0)
			{
				n = write(newsockfd,"FILE",255);
				if (n < 0)
					 error("ERROR writing to socket");
				char array[10000];
				bzero(array,10000);
				int ct=0;
				sock_fp=fdopen(fd,"r");
				while(!feof(sock_fp))		/*grafw se ena pinaka to periexomeno tou arxeiou pou diavasa*/
				{
					char buf;
					buf=fgetc(sock_fp);
					if(feof(sock_fp))
					{
						break;
					}
					array[ct]=buf;
					ct++;
				}
				fclose(sock_fp);
				bzero(buffer,255);
				sprintf(buffer,"%d",portno);
				n = write(newsockfd,buffer,255);
				if (n < 0)
					error("ERROR writing to socket");
				n = write(newsockfd,servers[i].adress,255);
				if (n < 0)
					error("ERROR writing to socket");
				n = write(newsockfd,array,10000);
				if (n < 0)
					 error("ERROR writing to socket");
				int fd = open(&dirorfilename[1], O_RDONLY);
				struct stat file_stat;
				if (fstat(fd, &file_stat) < 0)
			    {
					fprintf(stderr, "Error fstat --> %s", strerror(errno));
			        exit(EXIT_FAILURE);
			    }
			    close(fd);
			    char file_size[100];
			    sprintf(file_size, "%ld", file_stat.st_size);
				n = write(newsockfd,file_size,100);
				if (n < 0)
					 error("ERROR writing to socket");
				fetched_files[i]++;
			}
			else
			{
				search(pathname,dirorfilename,portno,servers[i].adress,newsockfd,i); /*h sunarthsh auth einai san thn write directories kai einai gia otan zhtountai sketa arxeia xwris directories*/
			}
		}
 	}
    return 0;
}
void write_directories(char* pathname,int newsockfd,int id)			/*anadromikh sunarthsh pou stelnei ta directories kai ta files stous mirror managers*/
{
	 DIR *dir,*dir1;
	 char buffer[256];
	 char buffer1[256];
	 int n;
	 struct dirent *ent;
	 if((dir=opendir(pathname))!=NULL)
	 {
	 	while((ent=readdir(dir))!=NULL)				//trexw oti uparxei mesa sto arxiko directory//
	 	{
	 		bzero(buffer1,256);
	 		strcpy(buffer1,pathname);
	 		strcat(buffer1,"/");
	 		strcat(buffer1,ent->d_name);
	 		if((dir1=opendir(buffer1))!=NULL)		//an auto pou diavasa einai directory//
	 		{

	 			bzero(buffer,256);
	 			strcpy(buffer,ent->d_name);
	 			if(!(strcmp(buffer,".")))continue;
	 			if(!(strcmp(buffer,"..")))continue;
	 			bzero(buffer,256);
	 			realpath(ent->d_name,buffer);
	 			bzero(buffer,256);
				sprintf(buffer,"%s~%d",buffer1,id);			/*~ shmainei directory*/
	 			n = write(newsockfd,buffer,255);
	 			if (n < 0)
	 				perror("ERROR writing to socket");
	 			write_directories(buffer1,newsockfd,id);
	 		}
	 		else						//an auto pou diavasa einai file//
	 		{
	 			bzero(buffer,256);
	 			bzero(buffer1,256);
	 			strcpy(buffer1,pathname);
	 			strcat(buffer1,"/");
	 			strcat(buffer1,ent->d_name);
	 			realpath(buffer1,buffer);
	 			bzero(buffer1,256);
				sprintf(buffer1,"%s@%d",buffer,id);			/*@ shmainei arxeio*/
	 			n = write(newsockfd,buffer1,255);
	 			if (n < 0)
	 				perror("ERROR writing to socket");
	 		}
	 	}
	 	closedir(dir);
	 	closedir(dir1);
	 	return;
	 }
	 else
	 {
		bzero(buffer,256);
		bzero(buffer1,256);
		strcpy(buffer1,pathname);
		strcat(buffer1,"/");
		strcat(buffer1,ent->d_name);
		realpath(buffer1,buffer);
		bzero(buffer1,256);
		sprintf(buffer1,"%s_%d",buffer,id);
		n = write(newsockfd,buffer1,255);
		if (n < 0)
			perror("ERROR writing to socket");
	 }
}
void search(char *pathname,char *dirorfilename,int portno,char *adress,int newsockfd,int i)
{
	 DIR *dir,*dir1;
	 char buffer[256];
	 char buffer1[256];
	 int n;
	 FILE *sock_fp;
	 struct dirent *ent;
	 if((dir=opendir(pathname))!=NULL)
	 {
	 	while((ent=readdir(dir))!=NULL)				//trexw oti uparxei mesa sto arxiko directory//
	 	{
	 		bzero(buffer1,256);
	 		strcpy(buffer1,pathname);
	 		strcat(buffer1,"/");
	 		strcat(buffer1,ent->d_name);
	 		if((dir1=opendir(buffer1))!=NULL)		//an auto pou diavasa einai directory//
	 		{
	 			bzero(buffer,256);
	 			strcpy(buffer,ent->d_name);
	 			if(!(strcmp(buffer,".")))continue;
	 			if(!(strcmp(buffer,"..")))continue;
	 			bzero(buffer,256);
	 			realpath(ent->d_name,buffer);
	 			search(buffer1,dirorfilename,portno,adress,newsockfd,i);
	 		}
	 		else						//an auto pou diavasa einai file//
	 		{
	 			if(strcmp(ent->d_name,&dirorfilename[strlen(dirorfilename)-strlen(ent->d_name)])==0)
	 			{
	 				if(strcmp(&buffer1[strlen(buffer1)-strlen(dirorfilename)],dirorfilename)!=0)
	 				{
	 					continue;
	 				}
	 				sock_fp=fopen(buffer1,"r");
					n = write(newsockfd,"FILE",255);
					if (n < 0)
						 error("ERROR writing to socket");
					char array[10000];
					bzero(array,10000);
					int ct=0;
					while(!feof(sock_fp))
					{
						char buf;
						buf=fgetc(sock_fp);
						if(feof(sock_fp))
						{
							break;
						}
						array[ct]=buf;
						ct++;
					}
					fclose(sock_fp);
					bzero(buffer,255);
					sprintf(buffer,"%d",portno);
					n = write(newsockfd,buffer,255);
					if (n < 0)
						error("ERROR writing to socket");
					n = write(newsockfd,adress,255);
					if (n < 0)
						error("ERROR writing to socket");
					n = write(newsockfd,array,10000);
					if (n < 0)
						 error("ERROR writing to socket");
					int fd = open(buffer1, O_RDONLY);
					struct stat file_stat;
					if (fstat(fd, &file_stat) < 0)
				    {
						fprintf(stderr, "Error fstat --> %s", strerror(errno));
				        exit(EXIT_FAILURE);
				    }
				    close(fd);
				    char file_size[100];
				    sprintf(file_size, "%ld", file_stat.st_size);
					n = write(newsockfd,file_size,100);
					if (n < 0)
						 error("ERROR writing to socket");
					fetched_files[i]++;
	 			}
	 		}
	 	}
	 }
}
