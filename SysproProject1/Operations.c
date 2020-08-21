/*
 * Operations.c
 *
 *  Created on: Feb 25, 2017
 *      Author: user
 */

#include <stdio.h>
#include "Operations.h"
#include <math.h>
#include <stdlib.h>
#include "MaxHeap.h"
#include <string.h>
#define SECONDARY_LIST_SIZE 10

int hash_function(int size, int number)
{
	double A = (sqrt(5) - 1) / 2;
	double temp = (A * number);
	temp = temp - floor(temp);
	int hash = floor(temp * size);
	return hash;
}
list* new_list()
{
	list* temp;
	int i=0;
	temp = malloc(sizeof(list));
	temp->next = NULL;
	temp->rec = malloc(sizeof(cdr));
	temp->arithmos_stoixeiwn=0;
	temp->rec[i].id = malloc(10 * sizeof(char));
	temp->rec[i].id = NULL;
	temp->rec[i].originator_number.kwdikos_xwras=malloc(3*sizeof(char));
	temp->rec[i].destination_number.kwdikos_xwras=malloc(3*sizeof(char));
	temp->rec[i].originator_number.kwdikos_xwras = NULL;
	temp->rec[i].originator_number.number = -1;
	temp->rec[i].destination_number.kwdikos_xwras = NULL;
	temp->rec[i].destination_number.number = -1;
	temp->rec[i].date.date = -1;
	temp->rec[i].date.month = -1;
	temp->rec[i].date.year = -1;
	temp->rec[i].duration = -1;
	temp->rec[i].fault_condition = -1;
	temp->rec[i].tarrif = -1;
	temp->rec[i].time.slot = malloc(2 * sizeof(char));
	temp->rec[i].time.slot = NULL;
	temp->rec[i].time.hour = -1;
	temp->rec[i].time.minutes = -1;
	temp->rec[i].type = malloc(10 * sizeof(char));
	temp->rec[i].type = NULL;
	return temp;
}
bucket* new_bucket()
{
	bucket* temp;
	int i=0;
	temp = malloc(sizeof(bucket));
	temp->bucket_node_ptr = malloc(sizeof(bucket_node));
	temp->next = NULL;
	temp->bucket_node_ptr->bucket_node_list = new_list();
	temp->bucket_node_ptr->number.kwdikos_xwras=malloc(3*sizeof(char));
	temp->bucket_node_ptr->number.kwdikos_xwras = NULL;
	temp->bucket_node_ptr->number.number = -1;
	temp->bucket_node_ptr->start = temp->bucket_node_ptr[i].bucket_node_list;
	temp->bucket_node_ptr->arithmos_stoixeiwn_listwn=0;
	temp->bucket_node_ptr->arithmos_listwn=1;
	temp->arithmos_stoixeiwn=0;
	return temp;
}
void insert(int hashtable1_size, int hashtable2_size, cdr rec,cdr rec1,hashtable** hashtable1, hashtable** hashtable2, int bucket_size, maxHeap** hp,float xrewsh[])
{
	int hash1, hash2, i = 0, j = 0, flag = 0, k = 0, l = 0,bucket_node1=-1,bucket_node2=-1;
	hash1 = hash_function(hashtable1_size, rec.originator_number.number);
	hash2 = hash_function(hashtable2_size, rec.destination_number.number);
	bucket* temp,*temp1;
	if(*hashtable1==NULL && *hashtable2==NULL)			//an exei perasei apo bye tote to hashtable kai to heap tha einai NULL giauto prepei na ta arxikopoihsw ksana otan erthei kainourgia eggrafh//
	{
		init_hashtable(hashtable1_size,bucket_size,hashtable1);
		init_hashtable(hashtable2_size,bucket_size,hashtable2);
		*hp = initMaxHeap();
	}
	while(1)		//psaxnw na vrw an to kainourgio stoixeio uparxei hdh sto hashtable1//
	{
		for (i = 0; i < (*hashtable1)[hash1].bucket_ptr->arithmos_stoixeiwn; i++)
		{
			if(check_number((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[i].number,rec.originator_number))
			{
				flag=1;
				bucket_node1 = i;
				break;
			}
		}
		if(flag==1)break;
		if ((*hashtable1)[hash1].bucket_ptr->next == NULL)
		{
			break;
		}
		else
		{
			(*hashtable1)[hash1].bucket_ptr = (*hashtable1)[hash1].bucket_ptr->next;
		}
	}
	temp=(*hashtable1)[hash1].bucket_ptr;
	(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].start;
	flag=0;
	while(1)			//psaxnw na vrw an to kainourgio stoixeio uparxei hdh sto hashtable2//
	{
		for (i = 0; i < (*hashtable2)[hash2].bucket_ptr->arithmos_stoixeiwn; i++)
		{
			if(check_number((*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[i].number,rec.destination_number))
			{
				flag=1;
				bucket_node2 = i;
				break;
			}
		}
		if(flag==1)break;
		if ((*hashtable2)[hash2].bucket_ptr->next == NULL)
		{
			break;
		}
		else
		{
			(*hashtable2)[hash2].bucket_ptr = (*hashtable2)[hash2].bucket_ptr->next;
		}
	}
	if(bucket_node1==-1)//auto shmainei oti h kainourgia eggrafh den uparxei mesa sto hashtable1//
	{
		while(1)
		{
			if(temp->arithmos_stoixeiwn==0)//auto shmainei oti exei ginei malloc kai perimenei na gemisei xwris realloc///
			{
					temp->arithmos_stoixeiwn++;
					(*hashtable1)[hash1].arithmos_stoixeiwn_buckets++;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].arithmos_stoixeiwn_listwn++;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].number.number=rec.originator_number.number;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].number.kwdikos_xwras=malloc(3*sizeof(char));
					strcpy(temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].number.kwdikos_xwras,rec.originator_number.kwdikos_xwras);
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn++;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->rec[temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1]=rec;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->rec[temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1].originator_number.kwdikos_xwras=NULL;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->rec[temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1].originator_number.number=-1;
					break;
			}
			else if(temp->arithmos_stoixeiwn<bucket_size)	//realloc//
			{
					temp->bucket_node_ptr=realloc(temp->bucket_node_ptr,((temp->arithmos_stoixeiwn)+1)*sizeof(bucket_node));
					temp->arithmos_stoixeiwn++;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list=new_list();
					(*hashtable1)[hash1].arithmos_stoixeiwn_buckets++;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->next=NULL;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].arithmos_listwn=1;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn++;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].arithmos_stoixeiwn_listwn=1;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].number.kwdikos_xwras=malloc(3*sizeof(char));
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].number.number=rec.originator_number.number;
					strcpy(temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].number.kwdikos_xwras,rec.originator_number.kwdikos_xwras);
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].start=temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->rec[temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1]=rec;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->rec[temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1].originator_number.number=-1;
					temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->rec[temp->bucket_node_ptr[temp->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1].originator_number.kwdikos_xwras=NULL;
					flag=1;
					break;
			}
			else
			{
				if(temp->next==NULL)		//an einai null shmainei oti den exei allo bucket meta kai giauto ftiaxnei ena kainourgio//
				{
					temp->next=new_bucket();
					temp=temp->next;
				}
				else						//alliws phgainei sto epomeno//
				{
					temp=temp->next;
				}
			}
		}
	}
	else	//h eggrafh uparxei mesa sto hashtable1 sthn thesh hash1 kai bucket->bucket_node1///
	{
		while(1)
		{
			if(temp->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn<SECONDARY_LIST_SIZE)
			{
				temp->bucket_node_ptr[bucket_node1].bucket_node_list->rec=
					realloc(temp->bucket_node_ptr[bucket_node1].bucket_node_list->rec,(temp->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn+1)*sizeof(cdr));
				temp->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn++;
				temp->bucket_node_ptr[bucket_node1].bucket_node_list->rec[temp->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn-1]=rec;
				temp->bucket_node_ptr[bucket_node1].bucket_node_list->rec[temp->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn-1].originator_number.kwdikos_xwras=NULL;
				temp->bucket_node_ptr[bucket_node1].bucket_node_list->rec[temp->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn-1].originator_number.number=-1;
				temp->bucket_node_ptr[bucket_node1].arithmos_stoixeiwn_listwn++;
				temp->bucket_node_ptr[bucket_node1].bucket_node_list = temp->bucket_node_ptr[bucket_node1].start;
				temp = (*hashtable1)[hash1].start;
				flag=1;
				break;
			}
			else
			{
				if(temp->bucket_node_ptr[bucket_node1].bucket_node_list->next!=NULL)
				{
					temp->bucket_node_ptr[bucket_node1].bucket_node_list=temp->bucket_node_ptr[bucket_node1].bucket_node_list->next;
				}
				else if(temp->bucket_node_ptr[bucket_node1].bucket_node_list->next==NULL)
				{
					temp->bucket_node_ptr[bucket_node1].bucket_node_list->next=new_list();
					temp->bucket_node_ptr[bucket_node1].bucket_node_list=temp->bucket_node_ptr[bucket_node1].bucket_node_list->next;
					temp->bucket_node_ptr[bucket_node1].arithmos_listwn++;
				}
			}
		}
	}
	flag=0;
	temp1=(*hashtable2)[hash2].bucket_ptr;
	(*hashtable2)[hash2].bucket_ptr=(*hashtable2)[hash2].start;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(bucket_node2==-1)//auto shmainei oti h kainourgia eggrafh den uparxei mesa sto hashtable2//
	{
		while(1)
		{
			if(temp1->arithmos_stoixeiwn==0)//auto shmainei oti exei ginei malloc kai perimenei na gemisei xwris realloc///
			{
					temp1->arithmos_stoixeiwn++;
					(*hashtable2)[hash2].arithmos_stoixeiwn_buckets++;
					//(*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[(*hashtable2)[hash2].bucket_ptr->arithmos_stoixeiwn-1].arithmos_listwn=1;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].arithmos_stoixeiwn_listwn++;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].number.number=rec1.destination_number.number;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].number.kwdikos_xwras=malloc(3*sizeof(char));
					strcpy(temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].number.kwdikos_xwras,rec1.destination_number.kwdikos_xwras);
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn++;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->rec[temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1]=rec1;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->rec[temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1].destination_number.kwdikos_xwras=NULL;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->rec[temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1].destination_number.number=-1;
					break;
			}
			else if(temp1->arithmos_stoixeiwn<bucket_size)	//realloc//
			{
					temp1->bucket_node_ptr=realloc(temp1->bucket_node_ptr,((temp1->arithmos_stoixeiwn)+1)*sizeof(bucket_node));
					temp1->arithmos_stoixeiwn++;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list=new_list();
					(*hashtable2)[hash2].arithmos_stoixeiwn_buckets++;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->next=NULL;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].arithmos_listwn=1;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn++;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].arithmos_stoixeiwn_listwn=1;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].number.kwdikos_xwras=malloc(10*sizeof(char));
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].number.number=rec1.destination_number.number;
					strcpy(temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].number.kwdikos_xwras,rec1.destination_number.kwdikos_xwras);
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].start=temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->
							rec[temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1]=rec1;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->rec[temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1].destination_number.number=-1;
					temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->rec[temp1->bucket_node_ptr[temp1->arithmos_stoixeiwn-1].bucket_node_list->arithmos_stoixeiwn-1].destination_number.kwdikos_xwras=NULL;
					flag=1;
					break;
			}
			else
			{
				if(temp1->next==NULL)	//an einai null shmainei oti den exei allo bucket meta kai giauto ftiaxnei ena kainourgio//
				{
					temp1->next=new_bucket();
					temp1=temp1->next;
				}
				else
				{
					temp1=temp1->next;
				}
			}
		}
	}
	else	//h eggrafh uparxei mesa sto hashtable1 sthn thesh hash1 kai bucket->bucket_node2///
	{
		while(1)
		{
			if(temp1->bucket_node_ptr[bucket_node2].bucket_node_list->arithmos_stoixeiwn<SECONDARY_LIST_SIZE)
			{
				temp1->bucket_node_ptr[bucket_node2].bucket_node_list->rec=
						realloc(temp1->bucket_node_ptr[bucket_node2].bucket_node_list->rec,(temp1->bucket_node_ptr[bucket_node2].bucket_node_list->arithmos_stoixeiwn+1)*sizeof(cdr));
				temp1->bucket_node_ptr[bucket_node2].bucket_node_list->arithmos_stoixeiwn++;
				temp1->bucket_node_ptr[bucket_node2].bucket_node_list->rec[temp1->bucket_node_ptr[bucket_node2].bucket_node_list->arithmos_stoixeiwn-1]=rec1;
				temp1->bucket_node_ptr[bucket_node2].bucket_node_list->rec[temp1->bucket_node_ptr[bucket_node2].bucket_node_list->arithmos_stoixeiwn-1].destination_number.kwdikos_xwras=NULL;
				temp1->bucket_node_ptr[bucket_node2].bucket_node_list->rec[temp1->bucket_node_ptr[bucket_node2].bucket_node_list->arithmos_stoixeiwn-1].destination_number.number=-1;
				temp1->bucket_node_ptr[bucket_node2].arithmos_stoixeiwn_listwn++;
				temp1->bucket_node_ptr[bucket_node2].bucket_node_list = temp1->bucket_node_ptr[bucket_node2].start;
				temp1 = (*hashtable2)[hash2].start;
				flag=1;
				break;
			}
			else
			{
				if(temp1->bucket_node_ptr[bucket_node2].bucket_node_list->next!=NULL)
				{
					temp1->bucket_node_ptr[bucket_node2].bucket_node_list=temp1->bucket_node_ptr[bucket_node2].bucket_node_list->next;
				}
				else if(temp1->bucket_node_ptr[bucket_node2].bucket_node_list->next==NULL)
				{
					temp1->bucket_node_ptr[bucket_node2].bucket_node_list->next=new_list();
					temp1->bucket_node_ptr[bucket_node2].bucket_node_list=temp1->bucket_node_ptr[bucket_node2].bucket_node_list->next;
					temp1->bucket_node_ptr[bucket_node2].arithmos_listwn++;
				}
			}
		}
	}
	float poso;
	//STO SHMEIO AUTO ELENXW TIS XREWSEIS APO TO CONFIG FILE ME TA STOIXEIA THS EGGRAFHS GIA NA VGALW THN SWSTH XREWSH//
	if(strcmp(rec.type,"0")==0 && rec.tarrif==0)
	{
		poso=xrewsh[0];
	}
	else if(strcmp(rec.type,"1")==0 && rec.tarrif==1)
	{
		poso=rec.duration*xrewsh[1];
	}
	else if(strcmp(rec.type,"1")==0 && rec.tarrif==2)
	{
		poso=rec.duration*xrewsh[2];
	}
	else if(strcmp(rec.type,"2")==0 && rec.tarrif==1)
	{
		poso=rec.duration*xrewsh[3];
	}
	else if(strcmp(rec.type,"2")==0 && rec.tarrif==2)
	{
		poso=rec.duration*xrewsh[4];
	}
	if(rec.fault_condition/100==2)
	{
		insertNode(*hp,poso,rec.originator_number.kwdikos_xwras,rec.originator_number.number);				//SYNARTHSH POU KANEI INSERT THN KAINOURGIA EGGRAFH STON MAX HEAP//
		printf("OK\n");
	}
	else
	{
		printf("IError\n");
	}
}
void delete(hashtable** hashtable1,char* id,number num,int bucket_size,int hashtable1_size,int hashtable2_size,maxHeap* hp)
{
	int hash1,hash2,i,j,bucket_node1=-1,bucket_node2=-1,list_node1=-1,list_node2=-1,flag=0;
	hash1=hash_function(hashtable1_size,num.number);
	cdr temp;
	if(*hashtable1==NULL)
	{
		printf("Den uparxei domh hashtable kai maxheap\n");
		return;
	}
	while(1)
	{
		for(i=0;i<(*hashtable1)[hash1].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num1 sto bucket hashtable1//
		{
			if(check_number((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[i].number,num))
			{
				bucket_node1=i;
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if((*hashtable1)[hash1].bucket_ptr->next!=NULL)
		{
			(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].bucket_ptr->next;
		}
		else
		{
			printf("DError\n");
			(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].start;
			return;
		}
	}
	flag=1;
	if(bucket_node1==-1)
	{
		printf("DError\n");
		(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].start;
		return;
	}
	while(1)
	{
		for(i=0;i<(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn;i++)//psaxnw na vrw thn thesh tou num1 MESA STHN LISTA//
		{
			if(bucket_node1==-1)
			{
				printf("DError\n");
				(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].start;
				return;
			}
			if(strcmp((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i].id,id)==0)
			{
				list_node1=i;
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->next!=NULL)
		{
			(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->next;
		}
		else break;
	}
	if(list_node1==-1)
	{
		printf("DError\n");
		(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].start;
		return;
	}
	// DIAGRAFW THN EGGRAFH KAI TA PAW OLA MIA THESH PANW//
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].date.date=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].date.month=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].date.year=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].destination_number.number=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].destination_number.kwdikos_xwras=NULL;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].originator_number.kwdikos_xwras=NULL;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].originator_number.number=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].duration=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].fault_condition=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].id=NULL;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].tarrif=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].time.hour=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].time.minutes=-1;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].time.slot=NULL;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].type=NULL;
	temp=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1];
	if(list_node1<SECONDARY_LIST_SIZE-1)
	{
		for(i=list_node1;i<(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn-1;i++)
		{
			memcpy(&(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i],&(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i+1],sizeof(cdr));
			memcpy(&(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i+1],&temp,sizeof(cdr));
		}
	}
	list_node1=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn-1;
	free((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].destination_number.kwdikos_xwras);
	free((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].originator_number.kwdikos_xwras);
	free((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].id);
	free((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].time.slot);
	free((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[list_node1].type);
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn--;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].arithmos_stoixeiwn_listwn--;
	(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].start;
	(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].start;
	printf("Deleted cdr-id\n");
}
int check_time(time time1, time time2, int hour, int min, char slot)	//ELENXW AN O XRONOS POU EGINE H EGGRAFH EINAI ANAMESA STA XRONIKA ORIA POU MOU DINONTAI //
{
	int flag = 0, flag1 = 0;
	if((strcmp(time1.slot,"a.m")==0 && strcmp(time2.slot,"a.m")==0 && slot=='a') || (strcmp(time1.slot,"p.m")==0 && strcmp(time2.slot,"p.m")==0 && slot=='p'))
	{
		if(hour>time1.hour)
		{
			flag=1;
		}
		else if(hour==time1.hour)
		{
			if (min >= time1.minutes)
			{
				flag = 1;
			}
		}
		if(hour<time2.hour)
		{
			flag1=1;
		}
		else if (hour == time2.hour)
		{
			if (min <= time2.minutes)
			{
				flag1 = 1;
			}
		}
		if (flag1 == 1 && flag == 1)
			return 1;
		else
			return 0;
	}
	else if(strcmp(time1.slot,"a.m")==0 && strcmp(time2.slot,"p.m")==0 && slot=='a')
	{
		if(hour>time1.hour)
		{
			flag=1;
		}
		else if(hour==time1.hour)
		{
			if (min >= time1.minutes)
			{
				flag = 1;
			}
		}
		if(flag==1)return 1;
		else return 0;
	}
	else if(strcmp(time1.slot,"a.m")==0 && strcmp(time2.slot,"p.m")==0 && slot=='p')
	{
		if(hour<time2.hour)
		{
			flag1=1;
		}
		else if (hour == time2.hour)
		{
			if (min <= time2.minutes)
			{
				flag1 = 1;
			}
		}
		if(flag1==1)return 1;
		else return 0;
	}
	else if(strcmp(time1.slot,"p.m")==0 && strcmp(time2.slot,"a.m")==0 && slot=='a')
	{
		if(hour<time2.hour)
		{
			flag1=1;
		}
		else if (hour == time2.hour)
		{
			if (min <= time2.minutes)
			{
				flag1= 1;
			}
		}
		if(flag1==1)return 1;
		else return 0;
	}
	else if(strcmp(time1.slot,"p.m")==0 && strcmp(time2.slot,"a.m")==0 && slot=='p')
	{
		if(hour>time1.hour)
		{
			flag=1;
		}
		else if(hour==time1.hour)
		{
			if (min >= time1.minutes)
			{
				flag = 1;
			}
		}
		if(flag==1)return 1;
		else return 0;
	}
	else return 0;
}
void find(number caller, hashtable** hashtable, int hashtable_size,int bucket_size, time time1, time time2, date year1, date year2)
{
	if(*hashtable==NULL)
	{
		printf("Den uparxei domh hashtable kai maxheap\n");
		return;
	}
	int thesh = hash_function(hashtable_size, caller.number),i,bucket_position,flag=0;
	while(1)			//VRISKW THN THESH THS EGGRAFHS STO BUCKET//
	{
		for (i = 0; i < (*hashtable)[thesh].bucket_ptr->arithmos_stoixeiwn; i++)
		{
			if (check_number((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[i].number,caller))
			{
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if ((*hashtable)[thesh].bucket_ptr->next == NULL)
		{
			printf("No CDRs found\n");
			(*hashtable)[thesh].bucket_ptr=(*hashtable)[thesh].start;
			return;
		}
		else
		{
			(*hashtable)[thesh].bucket_ptr = (*hashtable)[thesh].bucket_ptr->next;
		}
	}
	bucket_position = i;
	flag=0;
	int hour, minutes, date, month, year;
	char slot;
	printf("Euresh eggrafwn gia ton arithmo %s-%ld \n",caller.kwdikos_xwras, caller.number);
	if(year1.date!=-1 && year2.date!=-1)
	{
		printf("(%d/%d/%d) mexri (%d/%d/%d) \n", year1.date, year1.month,year1.year, year2.date, year2.month, year2.year);
	}
	if(time1.hour!=-1 && time2.hour!=-1)
	{
		printf("(%d:%d%s) mexri tis (%d:%d%s)\n",time1.hour,time1.minutes, time1.slot, time2.hour, time2.minutes, time2.slot);
	}
	while(1)	//ANALOGA TIS PERIPTWSEIS POU MOU DINONTAI MPAINEI KAI STHN KATALLHLH IF//
	{
		for (i = 0; i < (*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->arithmos_stoixeiwn; i++)
		{
			if (time1.hour != -1 && time2.hour != -1 && year1.date != -1 && year2.date != -1)
			{
				if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour== -1)break;
				hour=(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour;
				minutes=(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes;
				slot =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot[0];
				date =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date;
				month =	(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month;
				year =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year;
				if (date >= year1.date && month >= year1.month && year >= year1.year && date <= year2.date && month <= year2.month && year <= year2.year)
				{
					if (check_time(time1, time2, hour, minutes, slot))
					{
						flag=1;
						printf("%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].id,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.kwdikos_xwras,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.number,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.number,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].duration,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].type,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].tarrif,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].fault_condition);
					}
				}
			}
			else if (time1.hour != -1 && time2.hour != -1 && year1.date == -1 && year2.date == -1)
			{
				if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour== -1)break;
				hour =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour;
				minutes =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes;
				slot =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot[0];
				if (check_time(time1, time2, hour, minutes, slot))
				{
					flag=1;
					printf("%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].id,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.kwdikos_xwras,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.number,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.number,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].duration,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].type,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].tarrif,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].fault_condition);
				}
			}
			else if (time1.hour == -1 && time2.hour == -1 && year1.date != -1 && year2.date != -1)
			{
				if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour
						== -1)
					break;
				date =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date;
				month =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month;
				year =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year;
				if (date >= year1.date && month >= year1.month && year >= year1.year && date <= year2.date && month <= year2.month && year <= year2.year)
				{
					flag=1;
					printf("%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].id,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.kwdikos_xwras,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.number,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.number,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].duration,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].type,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].tarrif,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].fault_condition);
				}
			}
			else if (time1.hour == -1 && time2.hour == -1 && year1.date == -1	&& year2.date == -1)
			{

				if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour== -1)break;
				flag=1;
				printf("%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].id,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.kwdikos_xwras,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.number,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.number,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].duration,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].type,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].tarrif,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].fault_condition);
			}
			else
			{
				printf("Sumplirwse swsta ta stoixeia\nAn valeis time1 prepei na valeis kai time2\nAn valeis year1 prepei na valeis kai year2\n");
				return;
			}
		}
		if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->next!=NULL)
		{
			(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->next;
		}
		else if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->next==NULL)
		{
			break;
		}
	}
	if(flag==0)
		printf("No CDRs found\n");
	(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].start;
	(*hashtable)[thesh].bucket_ptr=(*hashtable)[thesh].start;
}
void lookup(number caller, hashtable** hashtable, int hashtable_size,int bucket_size, time time1, time time2, date year1, date year2)//ISXUEI TO IDIO ME THN FIND ALLA GIA TO HASHTABLE2//
{

	if(*hashtable==NULL)
	{
		printf("Den uparxei domh hashtable kai maxheap\n");
		return;
	}
	int thesh = hash_function(hashtable_size, caller.number), i,flag=0,bucket_position;
	while(1)
	{
		for (i = 0; i < (*hashtable)[thesh].bucket_ptr->arithmos_stoixeiwn; i++)
		{
			if (check_number((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[i].number,caller))
			{
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if ((*hashtable)[thesh].bucket_ptr->next == NULL)
		{
			printf("O arithmos %s-%ld den uparxei sthn lista\n",caller.kwdikos_xwras, caller.number);
			(*hashtable)[thesh].bucket_ptr=(*hashtable)[thesh].start;
			return;
		}
		else
		{
			(*hashtable)[thesh].bucket_ptr = (*hashtable)[thesh].bucket_ptr->next;
		}
	}
	bucket_position = i;
	int hour, minutes, date, month, year;
	flag=0;
	char slot;
	printf("Euresh eggrafwn gia ton arithmo %s-%ld \n",caller.kwdikos_xwras, caller.number);
	if(year1.date!=-1 && year2.date!=-1)
	{
		printf("(%d/%d/%d) mexri (%d/%d/%d) \n", year1.date, year1.month,year1.year, year2.date, year2.month, year2.year);
	}
	if(time1.hour!=-1 && time2.hour!=-1)
	{
		printf("(%d:%d%s) mexri tis (%d:%d%s)\n",time1.hour,time1.minutes, time1.slot, time2.hour, time2.minutes, time2.slot);
	}
	while(1)
	{
		for (i = 0; i < (*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->arithmos_stoixeiwn; i++)
		{
			if (time1.hour != -1 && time2.hour != -1 && year1.date != -1&& year2.date != -1)
			{
				if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour==-1)break;
				hour =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour;
				minutes =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes;
				slot =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot[0];
				date =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date;
				month =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month;
				year =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year;
				if (date >= year1.date && month >= year1.month && year >= year1.year && date <= year2.date && month <= year2.month && year <= year2.year)
				{
					if (check_time(time1, time2, hour, minutes, slot))
					{
							flag=1;
							printf("%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].id,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.kwdikos_xwras,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.number,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.number,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].duration,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].type,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].tarrif,
								(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].fault_condition);
					}
				}
			}
			else if (time1.hour != -1 && time2.hour != -1 && year1.date == -1&& year2.date == -1)
			{
				if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour== -1)break;
				hour =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour;
				minutes =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes;
				slot =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot[0];
				if (check_time(time1, time2, hour, minutes, slot))
				{
					flag=1;
					printf("%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].id,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.kwdikos_xwras,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.number,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.number,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].duration,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].type,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].tarrif,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].fault_condition);
				}
			}
			else if (time1.hour == -1 && time2.hour == -1 && year1.date != -1 && year2.date != -1)
			{
				if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour	== -1)break;
				date =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date;
				month =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month;
				year =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year;
				if (date >= year1.date && month >= year1.month && year >= year1.year && date <= year2.date && month <= year2.month && year <= year2.year)
				{
					flag=1;
					printf("%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].id,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.kwdikos_xwras,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.number,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.number,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].duration,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].type,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].tarrif,
							(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].fault_condition);
				}
			}
			else if (time1.hour == -1 && time2.hour == -1 && year1.date == -1 && year2.date == -1)
			{
				if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour== -1)break;
				flag=1;
				printf("%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].id,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.kwdikos_xwras,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].originator_number.number,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.number,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.date,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.month,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].date.year,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.hour,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.minutes,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].time.slot,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].duration,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].type,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].tarrif,
						(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].fault_condition);
			}
			else
			{
				printf("Sumplirwse swsta ta stoixeia\nAn valeis time1 prepei na valeis kai time2\nAn valeis year1 prepei na valeis kai year2\n");
				return;
			}
		}
		if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->next!=NULL)
		{
			(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->next;
		}
		else if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->next==NULL)
		{
			break;
		}
	}
	if(flag==0)
		printf("No CDRs found\n");
	(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].start;
	(*hashtable)[thesh].bucket_ptr=(*hashtable)[thesh].start;
}
void indist(hashtable** hashtable1, hashtable** hashtable2, number num1, number num2,int hashtable1_size,int hashtable2_size ,int bucket_size)
{
	int i, j, k, flag = 0, flag1 = 0,l=0, caller1_length= 0,caller2_length=0, m, thesh, bucket_node1=-1,bucket_node2=-1, flg = 0,hash1,hash2,hash1_1,hash2_2,metrhths=0,metrhths1=0;
	number* caller1 = NULL;
	number* caller2=NULL;
	number* epikoinwnia=NULL;
	list* x,*y;
	int* temp1;
	int* temp2;
	if(*hashtable1==NULL && *hashtable2==NULL)
	{
		printf("Den uparxei domh hashtable kai maxheap\n");
		return;
	}
	hash1=hash_function(hashtable1_size,num1.number);
	hash1_1=hash_function(hashtable1_size,num2.number);
	hash2=hash_function(hashtable2_size,num2.number);
	hash2_2=hash_function(hashtable2_size,num1.number);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while(1)
	{
		for(i=0;i<(*hashtable1)[hash1].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num1 sto bucket hashtable1//
		{
			if(check_number((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[i].number,num1))
			{
				bucket_node1=i;
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if((*hashtable1)[hash1].bucket_ptr->next!=NULL)
		{
			(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].bucket_ptr->next;
		}
		else
		{
			printf("To stoixeio %s-%ld den uparxei sthn lista tou hashtable1\n",num1.kwdikos_xwras,num1.number);
			printf("No indist found\n");
			break;
		}
	}
	x=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list;
	(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].start;
	flag=0;
	while(1)
	{
		for(i=0;i<(*hashtable1)[hash1_1].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num2 sto bucket hashable1//
		{
			if(check_number((*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[i].number,num2))
			{
				bucket_node2=i;
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if((*hashtable1)[hash1_1].bucket_ptr->next!=NULL)
		{
			(*hashtable1)[hash1_1].bucket_ptr=(*hashtable1)[hash1_1].bucket_ptr->next;
		}
		else
		{
			printf("To stoixeio %s-%ld den uparxei sthn lista tou hashtable1\n",num2.kwdikos_xwras,num2.number);
			printf("No indist found\n");
			break;
		}
	}
	y=(*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list;
	(*hashtable1)[hash1_1].bucket_ptr=(*hashtable1)[hash1_1].start;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while(1)				//vazw se ena pinaka caller1 se poion phre thlefwno o caller1//
	{
		if(bucket_node1==-1)
		{
			metrhths++;
			break;
		}
		for(i=0;i<x->arithmos_stoixeiwn;i++)
		{
			if(caller1==NULL)
			{
				caller1=malloc(sizeof(number));
				caller1->kwdikos_xwras=malloc(3*sizeof(char));
			}
			else
			{
				caller1=realloc(caller1,(caller1_length+1)*sizeof(number));
				caller1[caller1_length].kwdikos_xwras=malloc(3*sizeof(char));
			}
			caller1[caller1_length].number=x->rec[i].destination_number.number;
			strcpy(caller1[caller1_length].kwdikos_xwras,x->rec[i].destination_number.kwdikos_xwras);
			caller1_length++;
		}
		if(x->next!=NULL)
		{
			x=x->next;
		}
		else break;
	}
	while(1)									//vazw se ena pinaka caller2 se poion phre thlefwno o caller2//
	{
		if(bucket_node2==-1)
		{
			metrhths1++;
			break;
		}
		for(i=0;i<y->arithmos_stoixeiwn;i++)
		{
			if(caller2==NULL)
			{
				caller2=malloc(sizeof(number));
				caller2->kwdikos_xwras=malloc(3*sizeof(char));
			}
			else
			{
				caller2=realloc(caller2,(caller2_length+1)*sizeof(number));
				caller2[caller2_length].kwdikos_xwras=malloc(3*sizeof(char));
			}
			caller2[caller2_length].number=y->rec[i].destination_number.number;
			strcpy(caller2[caller2_length].kwdikos_xwras,y->rec[i].destination_number.kwdikos_xwras);
			caller2_length++;
		}
		if(y->next!=NULL)
		{
			y=y->next;
		}
		else break;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	flag=0;
	bucket_node1=-1;
	bucket_node2=-1;
	while(1)
	{
		for(i=0;i<(*hashtable2)[hash2_2].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num1 sto bucket hashtable2//
		{
			if(check_number((*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[i].number,num1))
			{
				bucket_node1=i;
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if((*hashtable2)[hash2_2].bucket_ptr->next!=NULL)
		{
			(*hashtable2)[hash2_2].bucket_ptr=(*hashtable2)[hash2_2].bucket_ptr->next;
		}
		else break;
	}
	x=(*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list;
	(*hashtable2)[hash2_2].bucket_ptr=(*hashtable2)[hash2_2].start;
	flag=0;
	while(1)
	{
		for(i=0;i<(*hashtable2)[hash2].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num2 sto bucket hashable2//
		{
			if((*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[i].number.number==num2.number && strcmp((*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[i].number.kwdikos_xwras,num2.kwdikos_xwras)==0)
			{
				bucket_node2=i;
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if((*hashtable2)[hash2].bucket_ptr->next!=NULL)
		{
			(*hashtable2)[hash2].bucket_ptr=(*hashtable2)[hash2].bucket_ptr->next;
		}
		else break;
	}
	y=(*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list;
	(*hashtable2)[hash2].bucket_ptr=(*hashtable2)[hash2].start;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	flag=0;
	while(1)
	{
		if(bucket_node1==-1)
		{
			metrhths++;
			break;
		}
		for(i=0;i<x->arithmos_stoixeiwn;i++)//vazw ston  pinaka caller1 poioi thlefwnhsan ston caller1//
		{
			flag=0;
			for(j=0;j<caller1_length;j++)
			{
				if(check_number(caller1[j],x->rec[i].originator_number))
				{
					flag=1;
					break;
				}
			}
			if(flag==1)continue;
			if(caller1==NULL)
			{
				caller1=malloc(sizeof(number));
				caller1->kwdikos_xwras=malloc(3*sizeof(char));
			}
			else
			{
				caller1=realloc(caller1,(caller1_length+1)*sizeof(number));
				caller1[caller1_length].kwdikos_xwras=malloc(3*sizeof(char));
			}
			caller1[caller1_length].number=x->rec[i].originator_number.number;
			strcpy(caller1[caller1_length].kwdikos_xwras,x->rec[i].originator_number.kwdikos_xwras);
			caller1_length++;
		}

		if(x->next!=NULL)
		{
			x=x->next;
		}
		else break;
	}
	flag=0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while(1)
	{
		if(bucket_node2==-1)
		{
			metrhths1++;
			break;
		}
		for(i=0;i<y->arithmos_stoixeiwn;i++)//vazw ston  pinaka caller2 poioi thlefwnhsan ston caller2//
		{
			flag=0;
			for(j=0;j<caller2_length;j++)
			{
				if(check_number(caller2[j],y->rec[i].originator_number))
				{
					flag=1;
					break;
				}
			}
			if(flag==1)continue;
			if(caller2==NULL)
			{
				caller2=malloc(sizeof(number));
				caller2->kwdikos_xwras=malloc(3*sizeof(char));
			}
			else
			{
				caller2=realloc(caller2,(caller2_length+1)*sizeof(number));
				caller2[caller2_length].kwdikos_xwras=malloc(3*sizeof(char));
			}
			caller2[caller2_length].number=y->rec[i].originator_number.number;
			strcpy(caller2[caller2_length].kwdikos_xwras,y->rec[i].originator_number.kwdikos_xwras);
			caller2_length++;
		}

		if(y->next!=NULL)
		{
			y=y->next;
		}
		else break;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(metrhths==2 && metrhths1==2)
	{
		printf("No indist found\n");
		return;
	}
	if(metrhths==2)
	{
		printf("No indist found\n");
		return;
	}
	if(metrhths1==2)
	{
		printf("No indist found\n");
		return;
	}
	for(i=0;i<caller1_length;i++)
	{
		for(j=0;j<caller2_length;j++)
		{
			if(check_number(caller1[i],caller2[j]))			//EDW SUGKRINW TOUS DUO PINAKES CALLER1 KAI CALLER2 GIA NA DW POIOI EINAI OI KOINOI.OI KOINOI THA MPOUN SE ENAN ALLO PINAKA GIA NA //
			{												//EPANALIFTHEI I IDIA DIADIKASIA ME THN PARAPANW GIA TOUS KOINOUS//
				if(epikoinwnia==NULL)
				{
					epikoinwnia=malloc(sizeof(number));
					epikoinwnia->kwdikos_xwras=malloc(3*sizeof(char));
				}
				else
				{
					epikoinwnia=realloc(epikoinwnia,(l+1)*sizeof(number));
					epikoinwnia[l].kwdikos_xwras=malloc(3*sizeof(char));
				}
				epikoinwnia[l].number=caller1[i].number;
				strcpy(epikoinwnia[l].kwdikos_xwras,caller1[i].kwdikos_xwras);
				l++;
			}
		}
	}
	for(j=0;j<l;j++)
	{
		if(l==1)break;
		if(check_number(epikoinwnia[j],num1) || check_number(epikoinwnia[j],num2))	//VAZW ME -1 TA STOIXEIA TOU PINAKA POU TAAUTIZONTAI ME TO NUM1 KAI NUM2//
		{
			epikoinwnia[j].number=-1;
		}
	}
	//////////////////PSAKSIMO STON PINAKA EPIKOINWNIA//////////////////////////////////////////////////////////////////////
	for(k=0;k<l;k++)	//EPANALAMVANETAI H IDIA DIADIKASIA ME PARAPANW GIA TOUS KOINOUS POU VRHKAME GIA NA DOUME AN MILANE METAKSU TOUS//
	{
		flg=0;
		metrhths=0;
		metrhths1=0;
		if(k==l-1)break;
		if(epikoinwnia[k].number==-1)continue;
		for(m=k+1;m<l;m++)
		{
			if(epikoinwnia[m].number==-1)continue;
			hash1=hash_function(hashtable1_size,num1.number);
			hash1_1=hash_function(hashtable1_size,num2.number);
			hash2=hash_function(hashtable2_size,num2.number);
			hash2_2=hash_function(hashtable2_size,num1.number);

			hash1=hash_function(hashtable1_size,epikoinwnia[k].number);
			hash1_1=hash_function(hashtable1_size,epikoinwnia[m].number);
			hash2=hash_function(hashtable2_size,epikoinwnia[m].number);
			hash2_2=hash_function(hashtable2_size,epikoinwnia[k].number);
			for(j=0;j<caller1_length;j++)
			{
				free(caller1[j].kwdikos_xwras);
				caller1[j].kwdikos_xwras=NULL;
				caller1[j].number=-1;
			}
			caller1_length=0;
			for(j=0;j<caller2_length;j++)
			{
				free(caller2[j].kwdikos_xwras);
				caller2[j].kwdikos_xwras=NULL;
				caller2[j].number=-1;
			}
			caller2_length=0;
			bucket_node1=-1;
			bucket_node2=-1;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			flag=0;
			while(1)
			{
				for(i=0;i<(*hashtable1)[hash1].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num1 sto bucket hashtable1//
				{
					if(check_number((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[i].number,epikoinwnia[k]))
					{
						bucket_node1=i;
						flag=1;
						break;
					}
				}
				if(flag==1)break;
				if((*hashtable1)[hash1].bucket_ptr->next!=NULL)
				{
					(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].bucket_ptr->next;
				}
				else break;
			}
			(*hashtable1)[hash1].bucket_ptr=(*hashtable1)[hash1].start;

			//psaxnw na vrw thn thesh tou num2 sto bucket hashable1//
			while(1)
			{
				for(i=0;i<(*hashtable1)[hash1_1].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num2 sto bucket hashtable1//
				{
					if(check_number((*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[i].number,epikoinwnia[m]))
					{
						bucket_node2=i;
						flag=1;
						break;
					}
				}
				if(flag==1)break;
				if((*hashtable1)[hash1_1].bucket_ptr->next!=NULL)
				{
					(*hashtable1)[hash1_1].bucket_ptr=(*hashtable1)[hash1_1].bucket_ptr->next;
				}
				else break;
			}
			(*hashtable1)[hash1_1].bucket_ptr=(*hashtable1)[hash1_1].start;
			flag=0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			while(1)
			{
				if(bucket_node1==-1)
				{
					metrhths++;
					break;
				}
				for(i=0;i<(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn;i++) //vazw se ena pinaka caller1 se poion phre thlefwno o caller1//
				{
					if(bucket_node1==-1)break;
					if(caller1==NULL)
					{
						caller1=malloc(sizeof(number));
						caller1->kwdikos_xwras=malloc(3*sizeof(char));
					}
					else
					{
						caller1=realloc(caller1,(caller1_length+1)*sizeof(number));
						caller1[caller1_length].kwdikos_xwras=malloc(3*sizeof(char));
					}
					caller1[caller1_length].number=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i].destination_number.number;
					strcpy(caller1[caller1_length].kwdikos_xwras,(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i].destination_number.kwdikos_xwras);
					caller1_length++;
				}
				if((*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->next!=NULL)
				{
					(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->next;
				}
				else break;
			}
			(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list=(*hashtable1)[hash1].bucket_ptr->bucket_node_ptr[bucket_node1].start;
			flag=0;
			//vazw se ena pinaka caller2 se poion phre thlefwno o caller2//
			while(1)
			{
				if(bucket_node2==-1)
				{
					metrhths1++;
					break;
				}
				for(i=0;i<(*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->arithmos_stoixeiwn;i++) //vazw se ena pinaka caller2 se poion phre thlefwno o caller2//
				{
					if(bucket_node2==-1)break;
					if(caller2==NULL)
					{
						caller2=malloc(sizeof(number));
						caller2->kwdikos_xwras=malloc(3*sizeof(char));
					}
					else
					{
						caller2=realloc(caller2,(caller2_length+1)*sizeof(number));
						caller2[caller2_length].kwdikos_xwras=malloc(3*sizeof(char));
					}
					caller2[caller2_length].number=(*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->rec[i].destination_number.number;
					strcpy(caller2[caller2_length].kwdikos_xwras,(*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->rec[i].destination_number.kwdikos_xwras);
					caller2_length++;
				}
				if((*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->next!=NULL)
				{
					(*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list=(*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->next;
				}
				else break;
			}
			(*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list=(*hashtable1)[hash1_1].bucket_ptr->bucket_node_ptr[bucket_node2].start;
			flag=0;
			bucket_node1=-1;
			bucket_node2=-1;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			while(1)
			{
				for(i=0;i<(*hashtable2)[hash2_2].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num1 sto bucket hashtable2//
				{
					if(check_number((*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[i].number,epikoinwnia[k]))
					{
						bucket_node1=i;
						flag=1;
						break;
					}
				}
				if(flag==1)break;
				if((*hashtable2)[hash2_2].bucket_ptr->next!=NULL)
				{
					(*hashtable2)[hash2_2].bucket_ptr=(*hashtable2)[hash2_2].bucket_ptr->next;
				}
				else break;
			}
			(*hashtable2)[hash2_2].bucket_ptr=(*hashtable2)[hash2_2].start;


			while(1)
			{
				for(i=0;i<(*hashtable2)[hash2].bucket_ptr->arithmos_stoixeiwn;i++)		//psaxnw na vrw thn thesh tou num2 sto bucket hashtable2//
				{
					if(check_number((*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[i].number,epikoinwnia[m]))
					{
						bucket_node2=i;
						flag=1;
						break;
					}
				}
				if(flag==1)break;
				if((*hashtable2)[hash2].bucket_ptr->next!=NULL)
				{
					(*hashtable2)[hash2].bucket_ptr=(*hashtable2)[hash2].bucket_ptr->next;
				}
				else break;
			}
			(*hashtable2)[hash2].bucket_ptr=(*hashtable2)[hash2].start;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			flag=0;
			while(1)
			{
				if(bucket_node1==-1)
				{
					metrhths++;
					break;
				}
				for(i=0;i<(*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->arithmos_stoixeiwn;i++)//vazw ston  pinaka caller1 poioi thlefwnhsan ston caller1//
				{
					flag=0;
					for(j=0;j<caller1_length;j++)
					{
						if(check_number(caller1[j],(*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i].originator_number))
						{
							flag=1;
							break;
						}
					}
					if(flag==1)continue;
					if(caller1==NULL)
					{
						caller1=malloc(sizeof(number));
						caller1->kwdikos_xwras=malloc(3*sizeof(char));
					}
					else
					{
						caller1=realloc(caller1,(caller1_length+1)*sizeof(number));
						caller1[caller1_length].kwdikos_xwras=malloc(3*sizeof(char));
					}
					caller1[caller1_length].number=(*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i].originator_number.number;
					strcpy(caller1[caller1_length].kwdikos_xwras,(*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->rec[i].originator_number.kwdikos_xwras);
					caller1_length++;
				}

				if((*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->next!=NULL)
				{
					(*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list=(*hashtable2)[hash2_2].bucket_ptr->bucket_node_ptr[bucket_node1].bucket_node_list->next;
				}
				else break;
			}
			flag=0;
			while(1)
			{
				if(bucket_node2==-1)
				{
					metrhths1++;
					break;
				}
				for(i=0;i<(*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->arithmos_stoixeiwn;i++)//vazw ston  pinaka caller2 poioi thlefwnhsan ston caller2//
				{
					flag=0;
					for(j=0;j<caller2_length;j++)
					{
						if(check_number(caller2[j],(*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->rec[i].originator_number))
						{
							flag=1;
							break;
						}
					}
					if(flag==1)continue;
					if(caller2==NULL)
					{
						caller2=malloc(sizeof(number));
						caller2->kwdikos_xwras=malloc(3*sizeof(char));
					}
					else
					{
						caller2=realloc(caller2,(caller2_length+1)*sizeof(number));
						caller2[caller2_length].kwdikos_xwras=malloc(3*sizeof(char));
					}
					caller2[caller2_length].number=(*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->rec[i].originator_number.number;
					strcpy(caller2[caller2_length].kwdikos_xwras,(*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->rec[i].originator_number.kwdikos_xwras);
					caller2_length++;
				}

				if((*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->next!=NULL)
				{
					(*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list=(*hashtable2)[hash2].bucket_ptr->bucket_node_ptr[bucket_node2].bucket_node_list->next;
				}
				else break;
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(metrhths==2 && metrhths1==2)
			{
				continue;
			}
			if(metrhths==2)
			{
				continue;
			}
			if(metrhths1==2)
			{
				continue;
			}
			for(i=0;i<caller1_length;i++)
			{
				if(check_number(caller1[i],epikoinwnia[m]))
				{
					flg=1;
					break;
				}
				for(j=0;j<caller2_length;j++)
				{
					if(check_number(caller2[j],epikoinwnia[k]))
					{
						flg=1;
						break;
					}
				}
				if(flg==1)break;
			}
			if(flg==1)break;
		}
	}
	if(l==0)
	{
		printf("No indist found\n");		return;
	}
	if(flg==0)
	{
		printf("Sundromites pou epikoinwnhsan me ton arithmo %s-%ld kai ton arithmo %s-%ld \nkai den exoun milhsei me tous ypoloipous pou milhsan me autous tous duo callers einai :\n",num1.kwdikos_xwras,num1.number,num2.kwdikos_xwras,num2.number);
		for(i=0;i<l;i++)
		{
			if(epikoinwnia[i].number!=-1)
			printf("%s-%ld\n",epikoinwnia[i].kwdikos_xwras,epikoinwnia[i].number);
		}
	}
}
int check_number(number num1,number num2)
{
	if(num1.number==num2.number && strcmp(num1.kwdikos_xwras,num2.kwdikos_xwras)==0)return 1;
	else return 0;
}
void read_top_line(FILE* fp,int *k,int pass)
{
	if(pass==0)
		fscanf(fp, "\n %3d",k);
	else
		fscanf(stdin, "\n %3d",k);
}
time set_time(char* y)
{
	time x;
	int i, j = 0;
	int hour, minutes;
	x.slot = malloc(2 * sizeof(char));
	char* temp = malloc(2 * sizeof(char));
	char* temp1 = malloc(2 * sizeof(char));
	for (i = 0; i < strlen(y); i++)
	{
		if (i < 2)
		{
			temp[i] = y[i];
		}
		else if (i > 2)
		{
			temp1[j] = y[i];
			j++;
		}
	}
	hour = atoi(temp);
	minutes = atoi(temp1);
	if (minutes >= 60)
	{
		printf("Lathos morfh wras,Ta lepta prepei na einai katw apo 60");
	}
	if (hour > 24)
	{
		printf("Lathos morfh wras,H wra prepei na einai katw apo 24");
	}
	if (hour > 12)
	{
		x.hour = hour - 12;
		x.minutes = minutes;
		strcpy((x.slot), "p.m");
	}
	else
	{
		x.hour = hour;
		x.minutes = minutes;
		strcpy((x.slot), "a.m");
	}
	free(temp);
	temp=NULL;
	free(temp1);
	temp1=NULL;
	return x;
}
date set_date(char* y)
{
	int i, j = 0, l = 0;;
	int day, month, year;
	char* temp = malloc(2 * sizeof(char));
	char* temp1 = malloc(2 * sizeof(char));
	char* temp2 = malloc(4 * sizeof(char));
	for (i = 0; i < strlen(y); i++)
	{
		if (i < 2)
		{
			temp[i] = y[i];
		}
		else if (i >= 2 && i < 4)
		{
			temp1[j] = y[i];
			j++;
		}
		else
		{
			temp2[l] = y[i];
			l++;
		}
	}
	day = atoi(temp);
	month = atoi(temp1);
	year = atoi(temp2);
	if (day > 31)
	{
		printf("H mera prepei na einai katw apo 32");
	}
	if (month > 12) {
		printf("O mhnas prepei na einai katw apo 13");
	}
	date x;
	x.date = day;
	x.month = month;
	x.year = year;
	free(temp);
	free(temp1);
	free(temp2);
	temp=NULL;
	temp1=NULL;
	temp2=NULL;
	return x;
}
void topdest(number caller, hashtable** hashtable, int hashtable_size,int bucket_size)
{
	int thesh, i=-1, j = 0, bucket_position, array_length, k, kwdikos, times,flag=0;
	if(*hashtable==NULL)
	{
		printf("Den uparxei domh hashtable kai maxheap\n");
		return;
	}
	thesh = hash_function(hashtable_size, caller.number);
	while(1)
	{
		for (i = 0; i < (*hashtable)[thesh].bucket_ptr->arithmos_stoixeiwn; i++)
		{
			if (check_number((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[i].number,caller))
			{
				flag=1;
				break;
			}
		}
		if(flag==1)break;
		if ((*hashtable)[thesh].bucket_ptr->next == NULL)
		{
			printf("No calls found\n");
			(*hashtable)[thesh].bucket_ptr= (*hashtable)[thesh].start;
			return;
		}
		else
		{
			(*hashtable)[thesh].bucket_ptr = (*hashtable)[thesh].bucket_ptr->next;
		}
	}
	if((*hashtable)[thesh].bucket_ptr->bucket_node_ptr->arithmos_stoixeiwn_listwn==0)
	{
		printf("No calls found\n");
		return;
	}

	bucket_position = i;
	int x=(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].arithmos_stoixeiwn_listwn;
	temp_array* array = malloc(x* sizeof(temp_array));
	(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list=(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].start;
	for (i = 0; i < (*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].arithmos_stoixeiwn_listwn; i++)
	{
		array[i].number = malloc(3 * sizeof(char));
		array[i].counter=0;
	}
	array_length=0;
	while(1)
	{
		for (i = 0; i < (*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->arithmos_stoixeiwn; i++)
		{
			flag = 0;
			for (k = 0; k < array_length; k++)
			{
				if (strcmp(array[k].number,(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras)==0)
				{
					array[k].counter++;
					flag = 1;
					break;
				}
			}
			if(flag==0)
			{
				strcpy(array[array_length].number ,(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->rec[i].destination_number.kwdikos_xwras);
				(array[array_length].counter)++;
				array_length++;
			}
		}
		if ((*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->next== NULL)
		{
			break;
		}
		else
		{
			(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list->next;
		}

	}
	j = array_length;
	(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].bucket_node_list =(*hashtable)[thesh].bucket_ptr->bucket_node_ptr[bucket_position].start;
	(*hashtable)[thesh].bucket_ptr= (*hashtable)[thesh].start;
	insertionSort(array, j);
	while (array[j - 1].counter == array[j - 2].counter)		//AN UPARXOUN PARAPANW APO ENA ME TON IDIO MEGISTO ARITHMO KLHSEWN SE MIA XWRA THA MPEI MESA STHN WHILE KAI THA TOUS EKTUPWSEI OLOUS//
	{
		printf("Country code:%s ,Calls made: %d\n", array[j - 1].number,array[j - 1].counter);
		j--;
		if (j < 2)
		{
			printf("Country code:%s ,Calls made: %d\n", array[j - 1].number,array[j - 1].counter);
			return;
		}
	}
	printf("Country code:%s ,Calls made: %d\n", array[array_length - 1].number,array[array_length - 1].counter);
	for (i = 0; i < array_length; i++)
	{
		free(array[i].number);
		array[i].number=NULL;
	}
	free(array);
	array=NULL;
}
void insertionSort(temp_array* arr, int n)
{
	int i, j;
	temp_array key;
	for (i = 1; i < n; i++)
	{
		key.counter = arr[i].counter;
		key.number = arr[i].number;
		j = i - 1;
		while (j >= 0 && arr[j].counter > key.counter)
		{
			arr[j + 1].counter = arr[j].counter;
			arr[j + 1].number = arr[j].number;
			j = j - 1;
		}
		arr[j + 1].counter = key.counter;
		arr[j + 1].number = key.number;
	}
}
void top(maxHeap* hp,int k)
{
	if(hp==NULL)
	{
		printf("Den uparxei maxheap\n");
		return;
	}
	top_funct(hp,k);
}
void bye(hashtable** hashtable1,hashtable** hashtable2,int hashtable_size1,int hashtable_size2,int bucket_size,maxHeap** hp)
{
	int i,j,k;
	bucket* temp=NULL;
	list* tmp=NULL;
	if(*hashtable1==NULL && *hashtable2==NULL && *hp==NULL)
	{
		printf("Den uparxei domh hashtable kai maxheap\n");
		return;
	}
	deleteHeap(hp);//FREE MAXHEAP//
	free(*hp);
	*hp=NULL;
	///////////////////////////////////////////////////////////////////////////////////////////////////////free hashtable1////////////////////////////////////////////////////////////////
	for(i=0;i<hashtable_size1;i++)
	{
		temp=(*hashtable1)[i].bucket_ptr;
		while(1)
		{
			for(j=(*hashtable1)[i].bucket_ptr->arithmos_stoixeiwn-1;j>=0;j--)
			{
				if((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].arithmos_stoixeiwn_listwn==0)
					{
					getchar();
					continue;
					}
				while(1)
				{
					if((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list==NULL)break;
					for(k=(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->arithmos_stoixeiwn-1;k>=0;k--)
					{
						if((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].id==NULL)continue;
						free((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].destination_number.kwdikos_xwras);
						(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].destination_number.kwdikos_xwras=NULL;
						free((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].originator_number.kwdikos_xwras);
						(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].originator_number.kwdikos_xwras=NULL;
						free((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].id);
						(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].id=NULL;
						free((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].type);
						(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].type=NULL;
						free((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].time.slot);
						(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].time.slot=NULL;
					}
					free((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec);
					(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec=NULL;
					if((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->next!=NULL)
					{
						tmp=(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list;
						(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list=(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->next;
						(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].start=(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->next;
						free(tmp);
						tmp=NULL;
					}
					else
					{
						break;
						getchar();
					}
				}
				free((*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list);
				(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list=NULL;
				(*hashtable1)[i].bucket_ptr->bucket_node_ptr[j].start=NULL;
			}
			free((*hashtable1)[i].bucket_ptr->bucket_node_ptr);
			(*hashtable1)[i].bucket_ptr->bucket_node_ptr=NULL;
			if((*hashtable1)[i].bucket_ptr->next!=NULL)
			{
				temp=(*hashtable1)[i].bucket_ptr->next;
				free((*hashtable1)[i].bucket_ptr);
				(*hashtable1)[i].bucket_ptr=NULL;
				(*hashtable1)[i].start=NULL;
				(*hashtable1)[i].bucket_ptr=temp;
				(*hashtable1)[i].start=temp;
			}
			else break;
		}
		(*hashtable1)[i].bucket_ptr->next=NULL;
		free((*hashtable1)[i].bucket_ptr);
		(*hashtable1)[i].bucket_ptr=NULL;
		(*hashtable1)[i].start=NULL;
	}
	free((*hashtable1));
	*hashtable1=NULL;
	///////////////////////////////////////////////////////////////////////////////////////free hashtable2//////////////////////////////////////////////////////////////////////////
	temp=NULL;
	tmp=NULL;
	for(i=0;i<hashtable_size2;i++)
	{
		temp=(*hashtable2)[i].bucket_ptr;
		while(1)
		{
			for(j=(*hashtable2)[i].bucket_ptr->arithmos_stoixeiwn-1;j>=0;j--)
			{
				if((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].arithmos_stoixeiwn_listwn==0)continue;
				while(1)
				{
					for(k=(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->arithmos_stoixeiwn-1;k>=0;k--)
					{
						if((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].id==NULL)continue;
						free((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].destination_number.kwdikos_xwras);
						(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].destination_number.kwdikos_xwras=NULL;
						free((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].originator_number.kwdikos_xwras);
						(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].originator_number.kwdikos_xwras=NULL;
						free((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].id);
						(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].id=NULL;
						free((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].type);
						(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].type=NULL;
						(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].time.slot=NULL;
					}
					free((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec);
					(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec=NULL;
					if((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->next!=NULL)
					{
						tmp=(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list;
						(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list=(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->next;
						(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].start=(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list;
						free(tmp);
						tmp=NULL;
					}
					else break;
				}
				free((*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list);
				(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list=NULL;
				(*hashtable2)[i].bucket_ptr->bucket_node_ptr[j].start=NULL;
			}
			free((*hashtable2)[i].bucket_ptr->bucket_node_ptr);
			(*hashtable2)[i].bucket_ptr->bucket_node_ptr=NULL;
			if((*hashtable2)[i].bucket_ptr->next!=NULL)
			{
				temp=(*hashtable2)[i].bucket_ptr->next;
				free((*hashtable2)[i].bucket_ptr);
				(*hashtable2)[i].bucket_ptr=NULL;
				(*hashtable2)[i].start=NULL;
				(*hashtable2)[i].bucket_ptr=temp;
				(*hashtable2)[i].start=temp;
			}
			else break;
		}
		(*hashtable2)[i].bucket_ptr->next=NULL;
		free((*hashtable2)[i].bucket_ptr);
		(*hashtable2)[i].bucket_ptr=NULL;
		(*hashtable2)[i].start=NULL;
	}
	free((*hashtable2));
	*hashtable2=NULL;
	if(hp==NULL)printf("hashtable2 deleted\n");
}
number set_number(char* x)
{
	number y;
	int i, j = 0;
	char* str = malloc(10 * sizeof(char));
	y.kwdikos_xwras = malloc(3 * sizeof(char));
	for (i = 0; i < strlen(x); i++)
	{
		if (i < 3)
		{
			y.kwdikos_xwras[i] = x[i];
		}
		else if (i > 3)
		{
			str[j] = x[i];
			j++;
		}
	}
	y.kwdikos_xwras[3]='\0';
	y.number = atol(str);
	free(str);
	str=NULL;
	return y;
}
void print_hashtable(hashtable* hashtable, int hashtable_size, char* name,int bucket_size, maxHeap* hp)
{
	int i, j = 0, k, flag = 0,flag1=0;
	if(hashtable==NULL && hp==NULL)
	{
		printf("Den uparxei domh hashtable kai maxheap\n");
		return;
	}
	printf("%s:\n", name);
	for (i = 0; i < hashtable_size; i++)
	{
		printf("\t%s[%d]:\n", name, i);
		if((hashtable)[i].arithmos_stoixeiwn_buckets==0)continue;
		printf("\tArithmos stoixeiwn buckets=%d kai sunolika buckets sundedemena=%d\n",(hashtable)[i].arithmos_stoixeiwn_buckets,(hashtable)[i].arithmos_bucket);
		printf("\tBucket %d:\n", i);
		printf("\tarithmos stoixeiwn bucket=%d\n", hashtable[i].bucket_ptr->arithmos_stoixeiwn);
		while(1)
		{
				for (j = 0; j < hashtable[i].bucket_ptr->arithmos_stoixeiwn; j++)
				{
					printf("\t\tArithmos stoixeiwn listwn=%d kai sunolikes listes sundedemenes=%d\n",(hashtable)[i].bucket_ptr->bucket_node_ptr[j].arithmos_stoixeiwn_listwn,(hashtable)[i].bucket_ptr->bucket_node_ptr[j].arithmos_listwn);
					printf("\t\tBucket_node[%d]:%s-%ld\n", j,(hashtable)[i].bucket_ptr->bucket_node_ptr[j].number.kwdikos_xwras,(hashtable)[i].bucket_ptr->bucket_node_ptr[j].number.number);
					if ((hashtable)[i].bucket_ptr->bucket_node_ptr[j].number.number ==-1 )
					{
						continue;
					}
					printf("\t\tSecondary list of number %s-%ld :\n",
							(hashtable)[i].bucket_ptr->bucket_node_ptr[j].number.kwdikos_xwras,
							(hashtable)[i].bucket_ptr->bucket_node_ptr[j].number.number);
					printf("\t\tarithmos stoixeiwn listas=%d\n", hashtable[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->arithmos_stoixeiwn);
					while(1)
					{
							for (k = 0; k < hashtable[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->arithmos_stoixeiwn; k++)
							{
								printf("\t\t\t\t\tlist[%d]:%s---%s-%ld---%s-%ld---%d/%d/%d---%d:%d%s---%d---%s---%d---%d\n",k,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].id,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].originator_number.kwdikos_xwras,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].originator_number.number,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].destination_number.kwdikos_xwras,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].destination_number.number,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].date.date,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].date.month,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].date.year,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].time.hour,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].time.minutes,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].time.slot,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].duration,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].type,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].tarrif,
										(hashtable)[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->rec[k].fault_condition);
							}
							if (hashtable[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->next!= NULL)
							{
								flag = 1;
								hashtable[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list =hashtable[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list->next;
								printf("\t\t\t\t\t\t\t\t\t||\n");
								printf("\t\t\t\t\t\t\t\t\t||\n");
								printf("\t\t\t\t\t\t\t\t\t\\/\n");
							}
							else break;
					}
					hashtable[i].bucket_ptr->bucket_node_ptr[j].bucket_node_list =hashtable[i].bucket_ptr->bucket_node_ptr[j].start;
				}
				if(hashtable[i].bucket_ptr->next!=NULL)
				{
					hashtable[i].bucket_ptr=hashtable[i].bucket_ptr->next;
					printf("\t\t\t\t||\n");
					printf("\t\t\t\t||\n");
					printf("\t\t\t\t\\/\n");
				}
				else break;
		}
		hashtable[i].bucket_ptr=hashtable[i].start;
	}
}
void init_hashtable(int hashtable_size, int bucket_size, hashtable** hashtable1)	//ARXIKOPOIW ENA HASHTABLE//
{
	int i, j,k=0,l=0;
	*hashtable1 =malloc(hashtable_size*sizeof(hashtable));
	for (i = 0; i < hashtable_size; i++)
	{
		(*hashtable1)[i].bucket_ptr =malloc(sizeof(bucket));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr = malloc(sizeof(bucket_node));
		(*hashtable1)[i].bucket_ptr->next = NULL;
		(*hashtable1)[i].arithmos_stoixeiwn_buckets=0;
		(*hashtable1)[i].arithmos_bucket=1;
		(*hashtable1)[i].bucket_ptr->arithmos_stoixeiwn=0;
		(*hashtable1)[i].start = (*hashtable1)[i].bucket_ptr;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list = malloc(sizeof(list));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr->number.kwdikos_xwras=malloc(3*sizeof(char));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].number.kwdikos_xwras = NULL;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].number.number = -1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].arithmos_stoixeiwn_listwn=0;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].arithmos_listwn=1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].start =(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec = malloc(sizeof(cdr));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->next = NULL;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->arithmos_stoixeiwn=0;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].id =malloc(10 * sizeof(char));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].id =NULL;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].originator_number.kwdikos_xwras =malloc(3 * sizeof(char));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].originator_number.kwdikos_xwras =NULL;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].originator_number.number =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].destination_number.kwdikos_xwras =malloc(3 * sizeof(char));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].destination_number.kwdikos_xwras =NULL;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].destination_number.number =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].date.date =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].date.month =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].date.year =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].duration =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].fault_condition =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].tarrif =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].time.slot =malloc(2 * sizeof(char));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].time.slot =NULL;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].time.minutes=-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].time.hour =-1;
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].type =malloc(10 * sizeof(char));
		(*hashtable1)[i].bucket_ptr->bucket_node_ptr[k].bucket_node_list->rec[l].type =NULL;
	}
}
char* read_function(FILE* fp, char* function)
{
	fscanf(fp, "\n%s \n", function);
	return function;
}
void read_insert_line(FILE* fp, cdr *temp,cdr* tmp,int pass)
{
	char* temp1 = malloc(13 * sizeof(char));
	char* temp2 = malloc(13 * sizeof(char));
	temp->id = malloc(10 * sizeof(char));
	temp->time.slot = malloc(2 * sizeof(char));
	temp->type = malloc(10 * sizeof(char));
	tmp->id = malloc(10 * sizeof(char));
	tmp->time.slot = malloc(2 * sizeof(char));
	tmp->type = malloc(10 * sizeof(char));
	if(pass==0)
	{
		fscanf(fp, "%[^;];%[^;];%[^;];%2d%2d%4d;%2d:%2d;%d;%[^;];%d;%d;\n",
				temp->id, temp1, temp2, &temp->date.date, &temp->date.month,
				&temp->date.year, &temp->time.hour, &temp->time.minutes,
				&temp->duration, temp->type, &temp->tarrif, &temp->fault_condition);
	}
	else
	{
		fscanf(stdin, "%[^;];%[^;];%[^;];%2d%2d%4d;%2d:%2d;%d;%[^;];%d;%d;",
						temp->id, temp1, temp2, &temp->date.date, &temp->date.month,
						&temp->date.year, &temp->time.hour, &temp->time.minutes,
						&temp->duration, temp->type, &temp->tarrif, &temp->fault_condition);
	}
	if (temp->time.hour > 12)
	{
		temp->time.hour = temp->time.hour - 12;
		strcpy((temp->time.slot), "p.m");
		tmp->time.hour = tmp->time.hour - 12;
		strcpy((tmp->time.slot), "p.m");
	}
	else
	{
		strcpy((temp->time.slot), "a.m");
		strcpy((tmp->time.slot), "a.m");
	}
	tmp->time.slot=temp->time.slot;
	tmp->time.hour=temp->time.hour;
	tmp->time.minutes=temp->time.minutes;
	temp->originator_number = set_number(temp1);
	temp->destination_number = set_number(temp2);
	tmp->originator_number = set_number(temp1);
	tmp->destination_number = set_number(temp2);
	strcpy(tmp->type,temp->type);
	strcpy(tmp->id,temp->id);
	tmp->date=temp->date;
	tmp->duration=temp->duration;
	tmp->fault_condition=temp->fault_condition;
	tmp->tarrif=temp->tarrif;
	free(temp1);
	free(temp2);
}
void init_date(date* year1)
{
	year1->date = -1;
	year1->month = -1;
	year1->year = -1;
}
void init_time(time* time1)
{
	time1->slot = malloc(2 * sizeof(char));
	time1->slot = NULL;
	time1->hour = -1;
	time1->minutes = -1;
}
void read_print_line(FILE* fp, char* name,int pass)
{
	if(pass==0)
	{
		fscanf(fp, "\n%[^\n]", name);
	}
	else
	{
		fscanf(stdin, "\n%[^\n]", name);
	}
}
void read_delete_line(FILE* fp, number* num, char** id,int pass)
{
	char* temp1 = malloc(13 * sizeof(char));
	if(pass==0)
		fscanf(fp, "\n%[^ ] %[^\n]", temp1, *id);
	else
		fscanf(stdin, "\n%[^ ] %[^\n]", temp1, *id);
	*num = set_number(temp1);
	free(temp1);
}
void read_lookup_line(FILE* fp, number* num, time* time1, date* year1,time* time2, date* year2,int pass)
{
	char** temp1 = malloc(5 * sizeof(char*));
	int i, j = 0;
	char ch;
	for (i = 0; i < 5; i++)
	{
		temp1[i] = malloc(13 * sizeof(char));
	}
	if(pass==0)
		fscanf(fp, "\n %14c", temp1[0]);
	else
		fscanf(stdin, "\n %14c", temp1[0]);
	if(pass==0)
		ch = getc(fp);
	else
		ch=getc(stdin);
	if (ch == '\n')
	{
		*num = set_number(temp1[0]);
		return;
	}
	else
	{
		if(pass==0)
			fscanf(fp, "%[^ ] %s", temp1[1], temp1[2]);
		else
			fscanf(stdin, "%[^ ] %s", temp1[1], temp1[2]);

	}
	if(pass==0)
		ch = getc(fp);
	else
		ch=getc(stdin);
	if (ch == '\n') {
		*num = set_number(temp1[0]);
		*time1 = set_time(temp1[1]);
		*time2 = set_time(temp1[2]);
		return;
	}
	else
	{
		if(pass==0)
			fscanf(fp, "%[^ ] %s", temp1[3], temp1[4]);
		else
			fscanf(stdin, "%[^ ] %s", temp1[3], temp1[4]);
	}
	*num = set_number(temp1[0]);
	*time1 = set_time(temp1[1]);
	*time2 = set_time(temp1[3]);
	*year1 = set_date(temp1[2]);
	*year2 = set_date(temp1[4]);
	for(i=0;i<5;i++)
	{
		free(temp1[i]);
		temp1[i]=NULL;
	}
	free(temp1);
	temp1=NULL;
}
void read_topdest_line(FILE* fp, number* num,int pass)
{
	char* temp1 = malloc(13 * sizeof(char));
	if(pass==0)
		fscanf(fp, "\n%[^\n]\n", temp1);
	else
		fscanf(stdin, "\n%[^\n]", temp1);
	*num = set_number(temp1);
}
void read_find_line(FILE* fp, number* num, time* time1, date* year1,time* time2, date* year2,int pass)
{
	char** temp1 = malloc(5 * sizeof(char*));
	int i, j = 0;
	char ch;
	for (i = 0; i < 5; i++)
	{
		temp1[i] = malloc(13 * sizeof(char));
	}
	if(pass==0)
		fscanf(fp, "\n %14c", temp1[0]);
	else
		fscanf(stdin, "\n %14c", temp1[0]);
	if(pass==0)
		ch = getc(fp);
	else
		ch=getc(stdin);
	if (ch == '\n')
	{
		*num = set_number(temp1[0]);
		return;
	}
	else
	{
		if(pass==0)
			fscanf(fp, "%[^ ] %s", temp1[1], temp1[2]);
		else
			fscanf(stdin, "%[^ ] %s", temp1[1], temp1[2]);

	}
	if(pass==0)
		ch = getc(fp);
	else
		ch=getc(stdin);
	if (ch == '\n')
	{
		*num = set_number(temp1[0]);
		*time1 = set_time(temp1[1]);
		*time2 = set_time(temp1[2]);
		return;
	}
	else
	{
		if(pass==0)
			fscanf(fp, "%[^ ] %s", temp1[3], temp1[4]);
		else
			fscanf(stdin, "%[^ ] %s", temp1[3], temp1[4]);
	}
	*num = set_number(temp1[0]);
	*time1 = set_time(temp1[1]);
	*time2 = set_time(temp1[3]);
	*year1 = set_date(temp1[2]);
	*year2 = set_date(temp1[4]);
}
void read_indist_line(FILE* fp, number* num1, number* num2,int pass)
{
	char* temp1 = malloc(13 * sizeof(char));
	char* temp2 = malloc(13 * sizeof(char));
	if(pass==0)
		fscanf(fp, "\n %[^ ] %[^\n]", temp1, temp2);
	else
		fscanf(stdin, "\n %[^ ] %[^\n]", temp1, temp2);
	*num1 = set_number(temp1);
	*num2 = set_number(temp2);
	free(temp1);
	temp1=NULL;
	free(temp2);
	temp2=NULL;
}
