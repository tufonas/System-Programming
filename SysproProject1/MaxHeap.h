/*
 * MaxHeap.h
 *
 *  Created on: Feb 25, 2017
 *      Author: user
 */

#ifndef MAXHEAP_H_
#define MAXHEAP_H_
typedef struct tree_node tree_node;
struct tree_node
{
    char* kwdikos_xwras;
    long int number;
    float poso;
    tree_node* left;
    tree_node* right;
    tree_node* parent;
    char* id;
    int level;
    int flag;
};
typedef struct maxHeap
{
    int size ;
    tree_node* start ;
    float eisodhma;
} maxHeap ;
maxHeap* initMaxHeap();
tree_node* print_top_k(tree_node* node,tree_node*,int);
tree_node* new_tree_node();
long decimalToBinary(int n);
void insertNode(maxHeap *hp,float,char*,long int);
int empty_heap(maxHeap* hp);
void swap(tree_node *n1, tree_node *n2);
void buildMaxHeap(maxHeap *hp,tree_node*,int );
void heapify(tree_node**,maxHeap *);
void deleteNode(tree_node* node);
void change_flag(maxHeap*,tree_node *n,float) ;
tree_node* elenxos_stoixeiou(tree_node *n,char*,long int,float);
void top_funct(maxHeap *hp,int);
void deleteHeap(maxHeap**);

#endif /* MAXHEAP_H_ */
