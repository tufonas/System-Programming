/*
 * main.h
 *
 *  Created on: Feb 25, 2017
 *      Author: user
 */
#include "MaxHeap.h"
#ifndef OPERATIONS_H_
#define OPERATIONS_H_

typedef struct bucket bucket;
typedef struct list list;
typedef struct number
{
	char* kwdikos_xwras;
	long int number;
}number;
typedef struct date
{
	int date;
	int month;
	int year;
}date;
typedef struct time
{
	int hour;
	int minutes;
	char* slot;
}time;
typedef struct temp_array
{
	char* number;
	int counter;
}temp_array;
typedef struct cdr
{
	char* id;
	number originator_number;
	number destination_number;
	date date;
	time time;
	int duration;
	char* type;
	int tarrif;
	int fault_condition;
}cdr;
typedef struct list
{
	cdr *rec;
	int arithmos_stoixeiwn;
	list* next;
}list;
typedef struct bucket_node
{
	number number;
	list* bucket_node_list;
	int arithmos_stoixeiwn_listwn;
	int arithmos_listwn;
	list* start;
}bucket_node;
typedef struct bucket
{
	bucket_node* bucket_node_ptr;
	bucket* next;
	int arithmos_stoixeiwn;
}bucket;
typedef struct hashtable
{
	bucket* bucket_ptr;
	int arithmos_stoixeiwn_buckets;
	int arithmos_bucket;
	bucket* start;
}hashtable;
void top(maxHeap*,int k);
void delete(hashtable** hashtable1,char* id,number num,int bucket_size,int hashtable1_size,int hashtable2_size,maxHeap*);
void topdest(number caller,hashtable**,int,int);
void bye(hashtable** hashtable1,hashtable** hashtable2,int hashtable_size1,int hashtable_size2,int bucket_size,maxHeap** hp);
void print_hashtable(hashtable* hashtable,int hashtable_size,char* name,int bucket_size,maxHeap*);
void init_date(date* year1);
void indist(hashtable** hashtable1,hashtable** hashtable2,number num1,number num2,int hashtable1_size,int,int bucket_size);
void lookup(number caller,hashtable** hashtable,int hashtable_size,int bucket_size,time time1,time time2,date year1,date year2);
void find(number caller,hashtable** hashtable,int hashtable_size,int bucket_size,time time1,time time2,date year1,date year2);
void insert(int,int ,cdr rec,cdr rec1,hashtable**,hashtable**,int,maxHeap**,float []);
number set_number(char*);
time set_time(char*);
date set_date(char*);
void init_hashtable(int hashtable_size,int bucket_size,hashtable** hashtable);
void init_time(time* time1);
void insertionSort(temp_array* arr, int n);
int hash_function(int size,int number);
int check_number(number num1,number num2);
int check_time(time time1,time time2,int hour,int min,char slot);
bucket* new_bucket();
list* new_list();
void read_find_line(FILE* fp,number* num,time* time1,date* year1,time* time2,date* year2,int );
void read_lookup_line(FILE* fp,number* num,time* time1,date* year1,time* time2,date* year2,int);
char* read_function(FILE* fp,char* function);
void read_insert_line(FILE* fp,cdr *temp,cdr*,int);
void read_top_line(FILE* fp,int* k,int);
void read_indist_line(FILE* fp,number* num1,number* num2,int);
void read_print_line(FILE* fp,char* name,int pass);
void read_topdest_line(FILE* fp,number* num,int pass);
void read_delete_line(FILE* fp,number* num,char** id,int );
#endif /* OPERATIONS_H_ */
