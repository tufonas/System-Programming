/*
 * main.c
 *
 *  Created on: Feb 25, 2017
 *      Author: user
 */
#include <stdio.h>
#include <stdlib.h>
#include "Operations.h"
#include "MaxHeap.h"
#include <string.h>


int main(int argc,char *argv[])
{
	FILE *fp,*fp1;
	cdr rec,rec1;
	hashtable *hashtable1,*hashtable2;
	maxHeap *hp;
	char* function=malloc(10*sizeof(char));
	char* id=malloc(10*sizeof(char));
	char* hashtable_name=malloc(9*sizeof(char));
	char epilogh[100];
	int i,j=0;
	int hashtable1_size=atoi(argv[4]),hashtable2_size=atoi(argv[6]),bucket_size=atoi(argv[8])/sizeof(bucket_node);
	init_hashtable(hashtable1_size,bucket_size,&hashtable1);
	init_hashtable(hashtable2_size,bucket_size,&hashtable2);
	hp = initMaxHeap();
	fp=fopen(argv[2],"r");
	fp1=fopen(argv[10],"r");
	char ch=fgetc(fp1);
	while(ch!='\n')
	{
		ch=fgetc(fp1);
	}
	int x;
	float xrewsh[5];
	fscanf(fp1,"%d;%d;%f\n",&x,&x,&xrewsh[0]);
	fscanf(fp1,"%d;%d;%f\n",&x,&x,&xrewsh[1]);
	fscanf(fp1,"%d;%d;%f\n",&x,&x,&xrewsh[2]);
	fscanf(fp1,"%d;%d;%f\n",&x,&x,&xrewsh[3]);
	fscanf(fp1,"%d;%d;%f\n",&x,&x,&xrewsh[4]);
	printf("xrewsh=%f\n",xrewsh[0]);
	printf("xrewsh1=%f\n",xrewsh[1]);
	printf("xrewsh2=%f\n",xrewsh[2]);
	printf("xrewsh3=%f\n",xrewsh[3]);
	printf("xrewsh4=%f\n",xrewsh[4]);
	number num,num1;
	time time1,time2;
	date year1,year2;
	while(!feof(fp))
	{
		function=read_function(fp,function);
		printf("\n%d)function=%s\n",j,function);
		if(strcmp(function,"insert")==0)
		{
			read_insert_line(fp,&rec,&rec1,0);
			if(rec.destination_number.number==0)break;
			printf("rec=%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",rec.id,
							rec.originator_number.kwdikos_xwras,rec.originator_number.number,
						rec.destination_number.kwdikos_xwras,rec.destination_number.number,
							rec.date.date,rec.date.month,rec.date.year,rec.time.hour,rec.time.minutes,rec.time.slot,rec.duration,rec.type,rec.tarrif,rec.fault_condition);
			insert(hashtable1_size,hashtable2_size,rec,rec1,&hashtable1,&hashtable2,bucket_size,&hp,xrewsh);
		}
		else if(strcmp(function,"delete")==0)
		{
			read_delete_line(fp,&num,&id,0);
			printf("caller=%s-%ld   id=%s\n",num.kwdikos_xwras,num.number,id);
			delete(&hashtable1,id,num,bucket_size,hashtable1_size,hashtable2_size,hp);
		}
		else if(strcmp(function,"find")==0)
		{
			init_time(&time1);
			init_time(&time2);
			init_date(&year1);
			init_date(&year2);
			read_find_line(fp,&num,&time1,&year1,&time2,&year2,0);
			find(num,&hashtable1,hashtable1_size,bucket_size,time1,time2,year1,year2);
		}
		else if(strcmp(function,"lookup")==0)
		{
			init_time(&time1);
			init_time(&time2);
			init_date(&year1);
			init_date(&year2);
			read_lookup_line(fp,&num,&time1,&year1,&time2,&year2,0);
			lookup(num,&hashtable2,hashtable2_size,bucket_size,time1,time2,year1,year2);
		}
		else if(strcmp(function,"topdest")==0)
		{
			read_topdest_line(fp,&num,0);
			printf("number=%s-%ld \n",num.kwdikos_xwras,num.number);
			topdest(num,&hashtable1,hashtable1_size,bucket_size);
		}
		else if(strncmp(function,"bye",3)==0)
		{
			bye(&hashtable1,&hashtable2,hashtable1_size,hashtable2_size,bucket_size,&hp);
			if(hashtable1==NULL)printf("hashtable1 deleted\n");
			if(hashtable2==NULL)printf("hashtable2 deleted\n");
			if(hp==NULL)printf("maxheap deleted\n");
		}
		else if(strcmp(function,"indist")==0)
		{
			read_indist_line(fp,&num,&num1,0);
			printf("number1=%s-%ld \n",num.kwdikos_xwras,num.number);
			printf("nummber2=%s-%ld \n",num1.kwdikos_xwras,num1.number);
			indist(&hashtable1,&hashtable2,num,num1,hashtable1_size,hashtable2_size,bucket_size);
		}
		else if(strcmp(function,"top")==0)
		{
			int k;
			read_top_line(fp,&k,0);
			top(hp,k);
		}
		else if(strcmp(function,"print")==0)
		{
			read_print_line(fp,hashtable_name,0);
			if(strcmp(hashtable_name,"hashtable1")==0)
			{
				print_hashtable(hashtable1,hashtable1_size,hashtable_name,bucket_size,hp);
			}
			else
			{
				print_hashtable(hashtable2,hashtable2_size,hashtable_name,bucket_size,hp);
			}
		}
		j++;
	}
	fclose(fp1);
	fp1=fopen(argv[10],"r");
	printf("################################TELOS ARXEIOU################################\n\n\n");

	while(1)
	{
		printf("\n################################ENTOLES PROMPT################################\n");
		printf("Vale Entolh     (Gia termatismo 0)\n");
		scanf("%s",epilogh);
		printf("epilogh=%s\n",epilogh);
		if(strcmp(epilogh,"0")==0)
		{
			printf("Thelete sigoura na termatisete thn diadikasia ?");
			printf("\t NO=0 ,YES=any other key\n");
			scanf("%s",epilogh);
			if(strcmp(epilogh,"0")==0)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if(strcmp(epilogh,"insert")==0)
		{
			if(rec.destination_number.number==0)break;

			read_insert_line(fp,&rec,&rec1,1);
			printf("temp=%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",rec.id,
							rec.originator_number.kwdikos_xwras,rec.originator_number.number,
							rec.destination_number.kwdikos_xwras,rec.destination_number.number,
							rec.date.date,rec.date.month,rec.date.year,rec.time.hour,rec.time.minutes,rec.time.slot,rec.duration,rec.type,rec.tarrif,rec.fault_condition);
			insert(hashtable1_size,hashtable2_size,rec,rec1,&hashtable1,&hashtable2,bucket_size,&hp,xrewsh);
		}
		else if(strcmp(epilogh,"delete")==0)
		{
			read_delete_line(fp,&num,&id,1);
			printf("caller=%s-%ld   id=%s\n",num.kwdikos_xwras,num.number,id);
			delete(&hashtable1,id,num,bucket_size,hashtable1_size,hashtable2_size,hp);
		}
		else if(strcmp(epilogh,"find")==0)
		{
			init_time(&time1);
			init_time(&time2);
			init_date(&year1);
			init_date(&year2);
			read_find_line(fp,&num,&time1,&year1,&time2,&year2,1);
			printf("num=%s-%ld time1=%d:%d%s time2=%d:%d%s year1=%d/%d/%d year2=%d/%d/%d\n",num.kwdikos_xwras,num.number,
					time1.hour,time1.minutes,time1.slot,
					time2.hour,time2.minutes,time2.slot,
					year1.date,year1.month,year1.year,
					year2.date,year2.month,year2.year);
			find(num,&hashtable1,hashtable1_size,bucket_size,time1,time2,year1,year2);
		}
		else if(strcmp(epilogh,"lookup")==0)
		{
			init_time(&time1);
			init_time(&time2);
			init_date(&year1);
			init_date(&year2);
			read_lookup_line(fp,&num,&time1,&year1,&time2,&year2,1);
			printf("num=%s-%ld time1=%d:%d%s time2=%d:%d%s year1=%d/%d/%d year2=%d/%d/%d\n",num.kwdikos_xwras,num.number,
					time1.hour,time1.minutes,time1.slot,
					time2.hour,time2.minutes,time2.slot,
					year1.date,year1.month,year1.year,
					year2.date,year2.month,year2.year);
			lookup(num,&hashtable2,hashtable2_size,bucket_size,time1,time2,year1,year2);
		}
		else if(strcmp(epilogh,"topdest")==0)
		{
			read_topdest_line(fp,&num,1);
			printf("num=%s-%ld \n",num.kwdikos_xwras,num.number);
			topdest(num,&hashtable1,hashtable1_size,bucket_size);
		}
		else if(strncmp(epilogh,"bye",3)==0)
		{
			bye(&hashtable1,&hashtable2,hashtable1_size,hashtable2_size,bucket_size,&hp);
			if(hashtable1==NULL)printf("hashtable1 deleted\n");
			if(hashtable2==NULL)printf("hashtable2 deleted\n");
		}
		else if(strcmp(epilogh,"indist")==0)
		{
			read_indist_line(fp,&num,&num1,1);
			printf("number1=%s-%ld \n",num.kwdikos_xwras,num.number);
			printf("number2=%s-%ld \n",num1.kwdikos_xwras,num1.number);
			indist(&hashtable1,&hashtable2,num,num1,hashtable1_size,hashtable2_size,bucket_size);
		}
		else if(strcmp(epilogh,"top")==0)
		{
			int k;
			read_top_line(fp,&k,1);
			top(hp,k);
		}
		else if(strcmp(epilogh,"print")==0)
		{
			read_print_line(fp,hashtable_name,1);
			if(strcmp(hashtable_name,"hashtable1")==0)
			{
				print_hashtable(hashtable1,hashtable1_size,hashtable_name,bucket_size,hp);
			}
			else
			{
				print_hashtable(hashtable2,hashtable2_size,hashtable_name,bucket_size,hp);
			}
		}
	}
	fclose(fp);
	free(hashtable_name);
	free(id);
	free(function);
}


