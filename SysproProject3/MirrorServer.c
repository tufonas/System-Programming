# include <stdio.h>
# include <sys/types.h> /* sockets */
# include <sys/socket.h> /* sockets */
# include <netinet/in.h> /* internet sockets */
# include <unistd.h> /* read , write , close */
# include <netdb.h> /* ge th os tb ya dd r */
# include <stdlib.h> /* exit */
# include <sys/wait.h>
# include <ctype.h>
# include <string.h> /* strlen */
# include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <dirent.h>
# include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
void perror_exit ( char * message )
{
	perror ( message );
	exit ( EXIT_FAILURE );
}
typedef struct cont_server
{
	char adress[100];
	int port;
	char dirorfile[100];
	int delay;
	int files;
	int fetched;
	int done;
	int id;
	int numb;
	char path[100];
}cont_server;
typedef struct files
{
	char name[100];
	char adress[100];
	int port;
	int id;
}files;
typedef struct help
{
	char path[100];
	int id;
}help;
int cnt=0;
int numDevicesDone=0;
float bytesTransferred=0;
int filesTransferred=0;
int content_servers_number=0;
int shared_buffer_size=3;				//apo edw allazw to megethos tou pinaka tou koinou buffer//
int positions=0;
int start=0;
int end=0;
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;			/*ola ta mutex kai ta conditions pou xreiazomai*/
pthread_mutex_t *mutex;
pthread_mutex_t fetch_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t position_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t end_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t start_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t bytes_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t files_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t id_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t numDevicesDone_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  *read_cond ;
pthread_cond_t  *write_cond ;
files shared_buffer[30];
int tetragwna;
cont_server content_server[50];
int worker_mirror_manager_number=0;
int real_content_number=0;
int main ( int argc , char * argv [])
{
	int port,sock,i,newsock,j,err;
	int  clientlen ;
	struct sockaddr_in server ,client;
	int workers_num;
	char path[100];
	for(i=0;i<argc;i++)
	{
		if(!strcmp(argv[i],"-m"))
		{
			strcpy(path,argv[i+1]);
		}
		if(!strcmp(argv[i],"-p"))
		{
			port = atoi ( argv [i+1]) ;
		}
		if(!strcmp(argv[i],"-w"))
		{
			workers_num=atoi(argv[i+1]);
		}
	}
	for(i=0;i<shared_buffer_size;i++)
	{
		shared_buffer[i].port=-1;
	}
	mutex=malloc(shared_buffer_size*sizeof(pthread_mutex_t));			/*arxikopoiw tous pinakes mutex kai condition variables*/
	read_cond=malloc(shared_buffer_size*sizeof(pthread_cond_t));
	write_cond=malloc(shared_buffer_size*sizeof(pthread_cond_t));
	for(i=0;i<shared_buffer_size;i++)
	{
		pthread_mutex_init(&(mutex[i]),NULL);
		pthread_cond_init (&(read_cond[i]), NULL);
		pthread_cond_init (&(write_cond[i]), NULL);
	}
	help work_struct[workers_num];
	pthread_t *workers ;
	void *Worker( void *) ;
	if (( workers = malloc ( workers_num * sizeof ( pthread_t ))) == NULL )
	{
		perror ( " malloc ") ;
		exit (1) ;
	}
	for(i=0;i<workers_num;i++)
	{
		work_struct[i].id=i;
		strcpy(work_struct[i].path,path);
		if ((err=pthread_create( workers+i , NULL , Worker ,(void*)(work_struct+i))))		/*ftiaxnw ta threads workers*/
		{
			perror (" pthread_create " );
			exit (1) ;
		}
	}
	if (( sock = socket ( AF_INET , SOCK_STREAM , 0) ) < 0)
		perror_exit (" socket ");
	server.sin_family = AF_INET ; /* Internet domain */
	server.sin_addr.s_addr = htonl(INADDR_ANY) ;
	server.sin_port = htons(port); /* The given port */
	if ( bind ( sock , (struct sockaddr *) &server,sizeof(server)) < 0)
	{
		perror ( " bind "); exit ( -1) ;
	}
	if ( listen ( sock , 5) < 0)
	{
		perror ( " listen ") ; exit ( -1) ;
	}
	/* accept connection */
	clientlen=sizeof(client);
	if (( newsock = accept ( sock , (struct sockaddr *) &client , &clientlen ) ) < 0)			/*sundesh me ton client*/
		perror_exit ("accept ") ;
	char buf [100];
	int counter=0;
	while(read ( newsock , buf , 255) > 0)						/*edw pairnw ta stoixeia apo auta pou mou stelnei o clien*/
	{
		if(strcmp(buf,"END")==0)break;
		if(counter==0)
			strcpy(content_server[content_servers_number].adress,buf);
		else if(counter==1)
		{
			content_server[content_servers_number].port=atoi(buf);
			for(j=0;j<=content_servers_number; j++)
			{
				if(j==content_servers_number)continue;
				if(content_server[content_servers_number].port==content_server[j].port)
				{
					real_content_number--;
					break;
				}
			}
		}
		else if(counter==2)
			strcpy(content_server[content_servers_number].dirorfile,buf);
		else if(counter==3)
			content_server[content_servers_number].delay=atoi(buf);
		else
		{
			counter=0;
			content_servers_number++;
			real_content_number++;
			strcpy(content_server[content_servers_number].adress,buf);
		}
		counter++;
	}
	for(j=0;j<=content_servers_number; j++)			/*arxikopoiw ton pinaka pou kratw plhrofories gia tous content servers*/
	{
		content_server[j].numb=1;
		strcpy(content_server[j].path,path);
		content_server[j].files=-1;
		content_server[j].fetched=0;
		content_server[j].done=-1;
	}
	for(j=0;j<content_servers_number; j++)
	{
		for(i=j+1;i<=content_servers_number; i++)
		{
			if(content_server[j].port==content_server[i].port)
			{
				content_server[j].numb++;
				content_server[i].numb++;			/*kanw autes tis prostheseis gia na vrw ton pragmatiko arithmo twn servers content*/
			}										/*px mporei na zhtw 3 diaforetika arxeia apo ton idio server  pou sunepagetai 1 content kai oxi 3*/
		}
	}
	pthread_t *MirrorManagers ;
	void *MirrorManager( void *) ;
	if (( MirrorManagers = malloc ( content_servers_number+1 * sizeof ( pthread_t ))) == NULL )
	{
		perror ( " malloc ") ;
		exit (1) ;
	}
	int y;
	char buffer[256];
	char pathname[100];
	bzero(buffer,256);
	for (y =0 ; y <= content_servers_number ; y++)
	{
		memset(pathname,'\0',sizeof(pathname));
		strcpy(pathname,path);
		strcat(pathname,"/");
		strcat(pathname,content_server[y].adress);
		strcat(pathname,"_");
		char numb[20];
		sprintf(numb,"%d",content_server[y].port);
		strcat(pathname,numb);
		if(	mkdir(pathname,0777)==-1)			/*ftiaxnw ta directories katw apo ta opoia tha mpoun ta arxeia pou zhtountai apo ton client*/
		{
			//perror("mkdir:");
		}
		if ((err=pthread_create( MirrorManagers+y , NULL , MirrorManager ,(void*)(content_server+y))))			/*ftiaxnw tous mirror managers*/
		{
			perror (" pthread_create " );
			exit (1) ;
		}
	}
	for (y =0 ; y <= content_servers_number ; y++)
	{
		if ( (err = pthread_join (*( MirrorManagers + y) , NULL )))
		{
				/* Wait for thread termination */
			perror (" pthread_join " );
			exit (1) ;
		}
	}
	for (i =0 ; i <workers_num ; i++)
	{
		if ( (err = pthread_join (*( workers+i) , NULL )))
		{
			perror (" pthread_join " );
			exit (1) ;
		}
	}
	fprintf(stdout,"bytes=%f\n",bytesTransferred);
	fprintf(stdout,"files=%d\n",filesTransferred);
	fprintf(stdout,"numDevicesDone=%d\n",numDevicesDone);
	for(y=0;y<=content_servers_number;y++)
	{
		if(content_server[y].files==0)			/*an kanena apo ta arxeia pou efere o content apo to list den to theloume*/
		{
			fprintf(stdout,"O Content me port %d kai adress %s den exei to arxeio pou thelete!\n",content_server[y].port,content_server[y].adress);
		}
	}
	int n;
	float mesos_oros=((float)bytesTransferred/(float)filesTransferred);
	float diaspora;
	diaspora=((float)(tetragwna-((float)pow(bytesTransferred,2)/(float)filesTransferred))/(float)filesTransferred);
	float tupikh_apoklish=sqrt(diaspora);
	float sxetikh_diaspora=tupikh_apoklish/mesos_oros;
	sprintf(buffer,"%f %d %f %f",bytesTransferred,filesTransferred,mesos_oros,sxetikh_diaspora);	/*grafw ta statistika pisw ston client*/
	n = write(newsock,buffer,255);
	if (n < 0)
		perror("ERROR writing to socket");

	for(i=0;i<shared_buffer_size;i++)
	{
		pthread_mutex_destroy(&mutex[i]);
		pthread_cond_destroy(&read_cond[i]);
		pthread_cond_destroy(&write_cond[i]);
	}
	pthread_mutex_destroy(mutex);
	pthread_mutex_destroy(&numDevicesDone_mutex);
	pthread_mutex_destroy(&id_mutex);
	pthread_mutex_destroy(&fetch_mutex);
	pthread_mutex_destroy(&end_mutex);
	pthread_mutex_destroy(&start_mutex);
	pthread_mutex_destroy(&count_mutex);
	pthread_mutex_destroy(&position_mutex);
	pthread_mutex_destroy(&files_mutex);
	pthread_mutex_destroy(&bytes_mutex);
	free(workers);
	free(MirrorManagers);
	exit(1);
}

void *Worker(void *r)
{
	help *x=(help*)r;
    int sockfd, portno, n,j=0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    int thread_mutex_place=0;
    while(1)
    {
	    pthread_mutex_lock( &start_mutex );
	    thread_mutex_place=start;
	    start=(start+1)%shared_buffer_size;
	    pthread_mutex_unlock( &start_mutex );
    	pthread_mutex_lock( &(mutex[thread_mutex_place]));
    	int cont=0;
		if(worker_mirror_manager_number==content_servers_number+1)		/*sunthikh termatismou twn workers .an oi managers pou teleiwsan einai isoi me tis aithseis pou eginan teleiwnoun oi workers*/
		{
			for(n=0;n<shared_buffer_size;n++)
			{
				pthread_cond_broadcast(&read_cond[n]);			/*teleiwnw kai ksupnw ola ta alla .to idio sumvainei se oles tis sunthikes parakatw*/
			}
			pthread_mutex_unlock(&mutex[thread_mutex_place]);
			pthread_exit(&x->id);
		}
		while(positions==0  || shared_buffer[thread_mutex_place].port==-1)		/*an oi kalummenes theseis einai 0 kai h porta einai -1 tote prepei na perimenei to worker*/
		{
			if(worker_mirror_manager_number==content_servers_number+1)
			{
				for(n=0;n<shared_buffer_size;n++)
				{
					pthread_cond_broadcast(&read_cond[n]);
				}
				pthread_mutex_unlock(&mutex[thread_mutex_place]);
				pthread_exit(&x->id);
			}
			pthread_cond_wait( &(read_cond[thread_mutex_place]), &(mutex[thread_mutex_place]) );
		}
		if(worker_mirror_manager_number==content_servers_number+1)
		{
			for(n=0;n<shared_buffer_size;n++)
			{
				pthread_cond_broadcast(&read_cond[n]);
			}
			pthread_mutex_unlock(&mutex[thread_mutex_place]);
			pthread_exit(&x->id);
		}
		fprintf(stdout,"WORKER[%d]: %s\n",thread_mutex_place,shared_buffer[thread_mutex_place].name);
		portno = shared_buffer[thread_mutex_place].port;
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
			perror("ERROR opening socket");
		server = gethostbyname(shared_buffer[thread_mutex_place].adress);			/*sundeomai me ton content apo to nhma worker*/
		if (server == NULL)
		{
			fprintf(stderr,"ERROR, no such host\n");
			exit(0);
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr,
			 (char *)&serv_addr.sin_addr.s_addr,
			 server->h_length);
		serv_addr.sin_port = htons(portno);
		if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		{
			perror("ERROR1 connecting");
		}

		bzero(buffer,256);
		sprintf(buffer,"FETCH %s %d",shared_buffer[thread_mutex_place].name,shared_buffer[thread_mutex_place].id);
		n = write(sockfd,buffer,255);					/*stelwn thn aithsh fetch me to onoma tou arxeiou kathws kai to id tou content*/
		if (n < 0)
			perror("ERROR writing to socket");
		for(j=0;j<content_servers_number+1;j++)
		{
			if(shared_buffer[thread_mutex_place].id==content_server[j].id)
			{
				break;					/*vriskw poia thesh tou content antistoixei me to id ths theshs tou shared buffer*/
			}
		}
		bzero(buffer,255);
		n = read(sockfd,buffer,255);
		if (n < 0)
		{
			perror("ERROR reading from socket");
		}
		char new_file[100];
		if(strcmp(buffer,"FILE")==0)
		{
			bzero(buffer,255);					//porta//
			n = read(sockfd,buffer,255);
			if (n < 0)
			{
				perror("ERROR reading from socket");
				fprintf(stderr,"error=%d\n",errno);
			}
			int port=atoi(buffer);
			bzero(buffer,255);
			n = read(sockfd,buffer,255);		//adress//
			if (n < 0)
			{
				perror("ERROR reading from socket");
				fprintf(stderr,"error=%d\n",errno);
			}
			char adrr[100];
			strcpy(adrr,buffer);
			char array[10000];
			bzero(array,10000);
			n = read(sockfd,array,10000);
			if (n < 0)
			{
				perror("ERROR reading from socket");
				fprintf(stderr,"error=%d\n",errno);
			}
			sprintf(new_file,"%s/%s_%d%s",x->path,adrr,port,shared_buffer[thread_mutex_place].name);
			bzero(buffer,255);
			n = read(sockfd,buffer,100);		//file_size//
			if (n < 0)
			{
				perror("ERROR reading from socket");
				fprintf(stderr,"error=%d\n",errno);
			}
			pthread_mutex_lock( &bytes_mutex );		/*auksanw ta bytes kai ta files transfered*/
			bytesTransferred+=atoi(buffer);
			tetragwna+=pow(atoi(buffer),2);
			pthread_mutex_unlock( &bytes_mutex );
			pthread_mutex_lock( &files_mutex );
			filesTransferred++;
			pthread_mutex_unlock( &files_mutex );
			int fd;
			if((fd = open(new_file, O_RDWR | O_CREAT,0666))<0)
			{
				bzero(buffer,255);
				if(errno==2)	/*no such file or dierctory*/
				{
					char *token=strtok(new_file,"/");
					while(token!=NULL)
					{
						token = strtok(NULL,"/");
						if(token==NULL)break;
						strcpy(buffer,token);
					}
				}
				else perror("file");
				bzero(new_file,100);
				sprintf(new_file,"%s/%s_%d/%s",x->path,adrr,port,buffer);
				if((fd = open(new_file, O_RDWR | O_CREAT,0666))<0)
				{
					perror("file1");
				}
			}
			if((write(fd,array,sizeof(array)))<0)
			{
				perror("write");
			}
			close(fd);


		}
		else if (strcmp(buffer,"ERROR")==0)
		{
			fprintf(stdout,"DEN UPARXEI TETOIO ARXEIO\n");
		}
		bzero(shared_buffer[thread_mutex_place].name,100);		/*svinw to onoma kai thn dieuthinsi apo ton shared buffer*/
		bzero(shared_buffer[thread_mutex_place].adress,100);
		shared_buffer[thread_mutex_place].port=-1;
		pthread_mutex_lock( &position_mutex );
		positions--;
		pthread_mutex_unlock( &position_mutex );
		pthread_cond_signal( &(write_cond[thread_mutex_place]) );
		pthread_mutex_unlock( &(mutex[thread_mutex_place]) );
		pthread_mutex_lock( &fetch_mutex );
		content_server[j].fetched++;
		pthread_mutex_unlock( &fetch_mutex );
		bzero(buffer,256);
		for(n=0;n<=content_servers_number;n++)
		{
			if(content_server[n].files==content_server[n].fetched && content_server[n].done==-1)
			{
				pthread_mutex_lock( &numDevicesDone_mutex );
				numDevicesDone++;			/*an isxuei h parapanw sunthikh tote auksanw ton arithmo twn devices pou teleiwsan*/
				content_server[n].done=0;		/*an ginei mhden shmainei oti gia ton sugkekrimeno server content exoume parei to info oti exei teleiwsei*/
				pthread_mutex_unlock( &numDevicesDone_mutex );
			}
		}
		if(worker_mirror_manager_number==content_servers_number+1)
		{
			for(n=0;n<shared_buffer_size;n++)
			{
				pthread_cond_broadcast(&read_cond[n]);
			}
			pthread_exit(&x->id);
		}
	}
}
void *MirrorManager(void *f)
{
	cont_server *x;
	int num=0;
	x=(cont_server*)f;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int thread_mutex_place=0;
    char buffer[256];
    char buffer1[256];
    portno = x->port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("ERROR opening socket");
    server = gethostbyname(x->adress);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)		/*sundeomai me ton content*/
    {
    	perror("ERROR connecting1");
    }
    bzero(buffer,256);
    sprintf(buffer,"LIST %d %s %d %d",x->delay,x->adress,x->numb,cnt);			/*kanw list ston content kai stelwn to delay to adress to id kai to real number of content.*/
   	n = write(sockfd,buffer,255);
    if (n < 0)
    	perror("ERROR writing to socket");
    pthread_mutex_lock( &id_mutex );
    x->id=cnt;
    cnt++;
    pthread_mutex_unlock( &id_mutex );
   	char *ch,*token;
   	int flag=0;
   	int flg=0;
   	char arr[100];
   	char path1[100];
   	char diror_path[100];
   	char arr1[100];
   	char help[100];
   	char content_path[100];
    while(1)
    {
    	bzero(buffer,256);
    	n = read(sockfd,buffer,255);
    	if (n < 0)
    		perror("ERROR reading from socket");
    	bzero(buffer1,256);
		if(!(strcmp(buffer,"END")))					/*an diavasw end apo ton content auto shmainei oti den exei na mou steilei alla arxeia kai o manager teleiwnei*/
		{
			pthread_mutex_lock( &count_mutex );
			worker_mirror_manager_number++;
			pthread_mutex_unlock( &count_mutex );
			x->files=num;
			break;
		}
    	if(strcmp(buffer,"")==0)continue;
    	if(buffer[0]!='/' && strcmp(buffer,"END")!=0)continue;
    	strncpy(buffer1,buffer,strlen(buffer)-2);
    	bzero(diror_path,100);
    	strcpy(help,x->dirorfile);
    	bzero(arr1,100);
		token=strtok(help,"/");
    	strcpy(diror_path,token);
    	int br=0;
		while( token != NULL )
		{
			token = strtok(NULL,"/");
			if(token==NULL)
			{
				break;
			}
			br=1;
			strcpy(arr1,"/");
			strcat(arr1,token);
		}
		if(br==0)
		{
			strcpy(arr1,help);
		}
		bzero(diror_path,100);
		bzero(help,100);
		strcpy(help,buffer1);
		token=strtok(help,"/");
		int rt=0;
		if(strcmp(token,&arr1[1])==0)
		{
			strcpy(diror_path,token);
			rt=1;
		}
		while( token != NULL )
		{
			token = strtok(NULL,"/");
			if(token==NULL)break;
			if(rt==1)
			{
				strcat(diror_path,"/");
				strcat(diror_path,token);
			}
			if(strcmp(token,&arr1[1])==0 && rt==0)
			{
				strcpy(diror_path,arr1);
				rt=1;
			}

		}
    	if(flag==0)		//auto pou zhtaei o client einai prosvasimo//
    	{
    		bzero(path1,100);
    		strcpy(content_path,buffer1);
    		flag=1;
    	}

    	bzero(path1,100);
    	strcpy(path1,content_path);
		strcat(path1,x->dirorfile);
		flg=0;
    	if(flag==0)
    	{
    		if(!(strcmp(buffer,"END")))
			{
				break;
			}
    		continue;
    	}
    	if(flag==1)			/*pairnw diafores periptwseis gia na filtrarw ta paths */
    	{
    		if(strncmp(buffer1,path1,strlen(path1))==0)
    		{
    			if(buffer1[strlen(path1)]=='/' || buffer1[strlen(path1)]==' ')
    			{
    				strcpy(arr,&buffer1[strlen(content_path)]);
    				flg=1;
    			}
    		}
    		if(strncmp(x->dirorfile,content_path,strlen(content_path))==0)
    		{
    			if((ch=strstr(buffer1,x->dirorfile))!=NULL )
    			{
    				flg=1;
    		    	strcpy(arr,&buffer1[strlen(x->dirorfile)]);
    			}
    		}
    		if(flg==1)				/*an to flg==1 tote shmainei oti to arxeio pou hrthe to exw dextei kai prepei na mpei ston shared buffer*/
    		{
    		   	int xx=0,z=0;
    		   	char array[100];
    		    if(buffer[strlen(buffer)-2]=='~')			/*elenxw an to path pou pairnw apo ton content einai directory*/
    		    {
    		    	while(buffer1[xx]==x->path[xx])
    		    	{
    		    		array[z]=buffer[xx];
    		    		xx++;
    		    		z++;
    		    	}
    		    	strcpy(buffer,&(buffer1[strlen(array)-1]));
					sprintf(buffer1,"%s/%s_%d%s",x->path,x->adress,x->port,x->dirorfile);
					mkdir(buffer1,0777);
    		    	bzero(buffer1,256);
    				memset(buffer1, '\0', sizeof(buffer1));
    				if(strstr(arr,arr1)==NULL)
    					sprintf(buffer1,"%s/%s_%d%s%s",x->path,x->adress,x->port,arr1,arr);
    				else if(strstr(arr1,arr)!=NULL)
    					sprintf(buffer1,"%s/%s_%d%s",x->path,x->adress,x->port,arr1);
    				else
    					sprintf(buffer1,"%s/%s_%d%s",x->path,x->adress,x->port,arr);
    		    	mkdir(buffer1,0777);
    		    	continue;
    		    }
    	        pthread_mutex_lock( &end_mutex );
    	        thread_mutex_place=end;
    	        end=(end+1)%shared_buffer_size;			/*auksanw thn thesh ths ouras mou*/
    	        pthread_mutex_unlock( &end_mutex );
    	        pthread_mutex_lock( &(mutex[thread_mutex_place]) );
    		   	while(positions>=shared_buffer_size || shared_buffer[thread_mutex_place].port!=-1)
    		    {
    		    	pthread_cond_wait( &write_cond[thread_mutex_place], &(mutex[thread_mutex_place]) );
    		    }
    			strcpy(shared_buffer[thread_mutex_place].name,diror_path);/*prosthetw thn eggrafh ston shared buffer*/
    			fprintf(stdout,"MirrorManage[%d]:%s\n",thread_mutex_place,shared_buffer[thread_mutex_place].name);
    		    strcpy(shared_buffer[thread_mutex_place].adress,x->adress);
    		    shared_buffer[thread_mutex_place].port=x->port;
    		    shared_buffer[thread_mutex_place].id=buffer[strlen(buffer)-1]-'0';
    		    pthread_mutex_lock( &position_mutex );
    		    positions++;
    		    pthread_mutex_unlock( &position_mutex );
    		    num++;
    				pthread_cond_signal( &read_cond[thread_mutex_place] );
    			pthread_mutex_unlock( &(mutex[thread_mutex_place]) );		/*ksupnaw ola ta threads pou perimenoun na diavasoun*/
    		}
    	}

    }
   pthread_exit(&x->id);
}
