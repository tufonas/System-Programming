# include <stdio.h>
# include <sys/types.h> /* sockets */
# include <sys/socket.h> /* sockets */
# include <netinet/in.h> /* internet sockets */
# include <unistd.h> /* read , write , close */
# include <netdb.h> /* ge th os tb ya dd r */
# include <stdlib.h> /* exit */
# include <string.h> /* strlen */
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
}cont_server;
int main ( int argc , char * argv [])
{
	int port , sock , i,y=0,j=0;
	char contentserver[500];
	cont_server cservers[20];
	for(j=0;j<20;j++)
	{
		cservers[j].delay=-1;
		cservers[j].port=-1;
	}
	struct sockaddr_in server ;
	struct sockaddr * serverptr =( struct sockaddr *)&server ;
	struct hostent * rem ;
	for(i=0;i<argc;i++)
	{
		if(!strcmp(argv[i],"-n"))
		{
			if (( rem = gethostbyname ( argv [i+1]) ) == NULL )
			{
				herror ( " gethostbyname "); exit (1) ;
			}
		}
		if(!strcmp(argv[i],"-p"))
		{
			port = atoi ( argv [i+1]) ; /* Convert port number to integer */
		}
		if(!strcmp(argv[i],"-s"))
		{
			strcpy(contentserver,argv[i+1]);
			char *token;
			while(1)
			{
				if(y==0)
					strcpy(cservers[y].adress,strtok(contentserver,":"));
				else
				{
					if((token=strtok(NULL,":"))==NULL)
					{
						break;
					}
					strcpy(cservers[y].adress,token);
				}
				cservers[y].port=atoi(strtok(NULL,":"));
				strcpy(cservers[y].dirorfile,strtok(NULL,":"));
				cservers[y].delay=atoi(strtok(NULL,","));
				y++;
			}
		}

	}
	/* Create socket */
	if (( sock = socket ( AF_INET , SOCK_STREAM , 0) ) < 0)
		perror_exit (" socket ");
	server . sin_family = AF_INET ; /* Internet domain */
	memcpy (&server.sin_addr ,rem->h_addr ,rem->h_length );
	server.sin_port = htons ( port ); /* Server port */
	/* Initiate connection */
	if ( connect ( sock , serverptr , sizeof ( server )) < 0)
		perror_exit (" connect ");
	char array[256];
	do
	{
		for(j=0;j<y;j++)
		{
			if ( write ( sock , cservers[j].adress , 255) < 0)
				perror_exit (" write " );
			memset(array, '\0', sizeof(array));
			sprintf(array,"%d",cservers[j].port);
			if ( write ( sock , array, 255) < 0)
				perror_exit (" write " );
			if ( write ( sock ,  cservers[j].dirorfile  , 255) < 0)
				perror_exit (" write " );
			strcpy(array," ");
			memset(array, '\0', sizeof(array));
			sprintf(array,"%d",cservers[j].delay);
			if ( write ( sock ,  array , 255) < 0)
				perror_exit (" write " );

		}
		y=0;
		if ( write ( sock ,  "END" , 255) < 0)
			perror_exit (" write " );
		bzero(array,255);
		if ( read ( sock ,  array , 255) < 0)
			perror_exit (" write " );
	}
	while ( y!= 0) ; /* Finish on " end " */
	char  *sxetikh_diaspora,*mesos_oros,*bytes,*files;
	strtok(array," ");
	files=(strtok(NULL," "));
	mesos_oros=(strtok(NULL," "));
	sxetikh_diaspora=(strtok(NULL," "));
	fprintf(stdout,"Bytes Transferred=%0.3f\nFiles Transferred=%s\nMesos Oros=%0.3f\nSxetikh Diaspora=%0.3f\n",atof(array),(files),atof(mesos_oros),atof(sxetikh_diaspora));
	close ( sock ); /* Close socket and exit */
}
