/*
 * MaxHeap.c
 *
 *  Created on: Feb 25, 2017
 *      Author: user
 */
#include <stdio.h>
#include <stdlib.h>
#include "MaxHeap.h"
#include <string.h>
#include <math.h>

maxHeap* initMaxHeap()
{
    maxHeap* hp=malloc(sizeof(maxHeap)) ;
    hp->size = 0 ;
    hp->start=malloc(sizeof(tree_node));
    hp->eisodhma=0;
    return hp ;
}
tree_node* new_tree_node(int size,tree_node* parent)
{
	tree_node* x;
	x=malloc(sizeof(tree_node));
	x->id=malloc(size*sizeof(char));
	x->kwdikos_xwras=malloc(3*sizeof(char));
	x->left=NULL;
	x->parent=parent;
	x->right=NULL;
	return x;
}
long decimalToBinary(int n)
{
    int remainder;
    long binary = 0, i = 1;
    while(n != 0)
    {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}
void change_flag(maxHeap* hp,tree_node* n,float eisodhma) // ALLAZW TO FLAG OLWN TWN KOMVWN SE 0//
{
     if(n==0) return;
     n->flag=0;
     change_flag(hp,n->left, hp->eisodhma);
     change_flag(hp,n->right, hp->eisodhma);
}
tree_node* elenxos_stoixeiou(tree_node *n,char* kwdikos_xwras,long int num,float poso) /*elenxw an to kainourgio stoixeio uparxei hdh mesa sto heap*/
{
	tree_node* temp=NULL;
	if(strcmp(n->kwdikos_xwras,kwdikos_xwras)==0 & n->number==num)
    {
		n->poso=n->poso+poso;
		return n;
    }
	if(n->left==NULL && n->right==NULL)
	{
		return NULL;
	}
	if(n->left==NULL)
	{
		return NULL;
	}
	temp=elenxos_stoixeiou(n->left,kwdikos_xwras,num,poso);
    if(temp!=NULL)return temp;
    if(n->right==NULL)
    {
    	 return NULL;
    }
    temp=elenxos_stoixeiou(n->right,kwdikos_xwras,num,poso);
    if( temp!=NULL)return temp;
    return NULL;
}
void insertNode(maxHeap *hp, float poso,char* kwdikos_xwras,long int num)
{
	tree_node *temp,*temp1;
	char str[100];
	temp=hp->start;
	long int thesh,i=1;
	if(hp->size==0)
	{
		hp->start->id=malloc(sizeof(char));
		hp->start->kwdikos_xwras=malloc(3*sizeof(char));
		strcpy(hp->start->id,"1");
		hp->start->kwdikos_xwras=kwdikos_xwras;
		hp->start->level=0;
		hp->start->left=NULL;
		hp->start->number=num;
		hp->start->parent=NULL;
		hp->start->poso=poso;
		hp->start->right=NULL;
		hp->size++;
		hp->start->flag=0;
		hp->eisodhma=hp->eisodhma+poso;
	}
	else
	{
		thesh=decimalToBinary(hp->size+1);
		sprintf(str,"%ld",thesh);
		hp->eisodhma=hp->eisodhma+poso;
		temp=elenxos_stoixeiou(hp->start,kwdikos_xwras,num,poso);
		if(temp!=NULL)
		{
			heapify(&temp,hp);
			return;
		}
		temp=hp->start;
		while(strcmp(str,temp->id)!=0)
		{
			if(str[i]=='0')
			{
				if(temp->left!=NULL)temp=temp->left;
				else
				{
					temp->left=new_tree_node(i+1,temp);
					temp1=temp;
					temp=temp->left;
					temp->poso=poso;
					temp->parent=temp1;
					strcpy(temp->kwdikos_xwras,kwdikos_xwras);
					temp->number=num;
					temp->flag=0;
					strcpy(temp->id,str);
					temp->level=strlen(temp->id)-1;
					break;
				}
			}
			else
			{
				if(temp->right!=NULL)temp=temp->right;
				else
				{
					temp1=temp;
					temp->right=new_tree_node(i+1,temp);
					temp=temp->right;
					temp->parent=temp1;
					temp->poso=poso;
					strcpy(temp->kwdikos_xwras,kwdikos_xwras);
					temp->number=num;
					temp->flag=0;
					strcpy(temp->id,str);
					temp->level=strlen(temp->id)-1;
					break;
				}
			}
			i++;
		}
		hp->size++;
		heapify(&temp,hp);
	}
}
void swap(tree_node *n1, tree_node *n2)
{
	tree_node temp1;
	temp1.kwdikos_xwras = (char*)malloc(3*sizeof(char));
	temp1.id = (char*)malloc(64*sizeof(char));
	strcpy(temp1.kwdikos_xwras,n1->kwdikos_xwras);
	temp1.left=n1->left;
	temp1.parent=n1->parent;
	temp1.poso=n1->poso;
	temp1.right=n1->parent;
	temp1.number=n1->number;
	temp1.flag=n1->flag;
    (*n1).number= (*n2).number ;
    strcpy((*n1).kwdikos_xwras,(*n2).kwdikos_xwras);
    (*n1).poso=(*n2).poso;
    strcpy((*n2).kwdikos_xwras,temp1.kwdikos_xwras);
    (*n2).poso=temp1.poso;
    (*n2).flag=temp1.flag;
    (*n2).number=temp1.number;
    free(temp1.kwdikos_xwras);
    free(temp1.id);
}
void heapify(tree_node** temp,maxHeap* hp)///stelnw ton komvo pou molis exei mpei kai thelw na ton valw sthn swsth theesh///
{
	tree_node* tmp;
	if((*temp)->number==hp->start->number && strcmp((*temp)->kwdikos_xwras,hp->start->kwdikos_xwras)==0)
	{
		return;
	}
	if((*temp)->parent->poso > (*temp)->poso) ///an o pateras megalutero apo to paidi telos///
	{
		return;
	}
	else
	{
		swap((*temp)->parent,(*temp));
		heapify(&(*temp)->parent,hp);
	}
}
tree_node* print_top_k(tree_node* node,tree_node* max,int lvl)
{
	if(node==NULL)return max;
	if(node->level<lvl)
	{
		max=print_top_k(node->left,max,lvl);
	}
	if(node->level<lvl)
	{
		max=print_top_k(node->right,max,lvl);
	}
	if(max->poso<=node->poso && node->flag==0 && max->flag==0)
	{
		max=node;
		return max;
	}
	else if(node->flag==0 && max->flag==0)
	{
		return max;
	}
	if(node->flag!=0 )return max;
	if(max->flag!=0) return node;
	return max;
}
void top_funct(maxHeap *hp,int k)
{
	float x=k;
	float pososto=(x/100);
	float search=(pososto*hp->eisodhma);
	int lvl=1,lvl1=1;
	tree_node* temp,*temp1;
	if(k==0)
	{
		printf("No calls found\n");
		return;
	}
	if(hp->start==NULL)
	{
		printf("No calls found\n");
	}
	printf("eisodhma=%0.2f\n",hp->eisodhma);
	printf("pososto=%0.2f\n",pososto);
	printf("Sunoliko poso=%0.2f\n",search);
	printf("Oi sundromhtes pou apartizoun to %d%% tou eisodhmatos ths etaireias einai:\n",k);
	printf("telephone %s-%ld %f%% of-revenue-for-company generated\n",hp->start->kwdikos_xwras,hp->start->number,hp->start->poso/hp->eisodhma);
	search=search-hp->start->poso;
	while(search>0)
	{
		if(hp->start->left!=NULL) temp=print_top_k(hp->start->left,hp->start->left,lvl);
		if(hp->start->right!=NULL) temp1=print_top_k(hp->start->right,hp->start->right,lvl1);
		if(hp->start->left==NULL && hp->start->right==NULL) break;
		else if(hp->start->left!=NULL && hp->start->right==NULL) temp1=temp;
		else if(hp->start->left==NULL && hp->start->right!=NULL) temp=temp1;
		if(lvl>1 && temp->level==1)temp=temp1;
		if(lvl1>1 && temp1->level==1)temp1=temp;
		if(lvl>1 && temp->level==1 && lvl1>1 && temp1->level==1)break;
		if(temp->poso >= temp1->poso && temp!=NULL)
		{
			printf("telephone %s-%ld  %f%% of-revenue-for-company generated\n",temp->kwdikos_xwras,temp->number,temp->poso/hp->eisodhma);
			temp->flag=1;
			search=search-temp->poso;
			lvl++;
		}
		else if(temp->poso < temp1->poso && temp1!=NULL)
		{
			printf("telephone %s-%ld %f%% of-revenue-for-company generated\n",temp1->kwdikos_xwras,temp1->number,temp1->poso/hp->eisodhma);
			temp1->flag=1;
			search=search-temp1->poso;
			lvl1++;
		}
	}
	change_flag(hp,hp->start,hp->eisodhma);
}
void deleteHeap(maxHeap** hp)
{
	deleteNode((*hp)->start);
}
void deleteNode(tree_node* node)
{
    if (node == NULL) return;
    deleteNode(node->left);
    deleteNode(node->right);
    free(node->kwdikos_xwras);
    node->kwdikos_xwras=NULL;
    node->left=NULL;
    node->right=NULL;
    free(node);
    node=NULL;
}

