
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

typedef struct list List; //define o tipo list
typedef struct node Node; // define o tipo no

struct list
{
    Node* head;
};

struct node
{
    int info;
    Node* next; 
};

List* create_list();
void add_top_list(List* l, int v);
void add_bottom_list(List* l, int v);
void add_middle_list(List* l, int v);
int size_list(List* l);
int free_list(List* l);
void print_list(List* l);
void delete_element_list(List* l, int v);
void delete_end_list(List* l);


List* create_list(){
    List* list = (List*) malloc(sizeof(List));
    list->head = NULL;
    return list;
}


int free_list(List* l){
    Node* node = l->head;
    while (node->next != l->head)
    {
        Node* aux = node->next;
        free(node);
        node = aux;
    }

    free(l);
}

void print_list(List* l){
    Node* node = l->head;
    if(node != NULL){
    do{
        printf("%d\n", node->info);
        node = node->next;
    }while (node != l->head);

    }
}

void add_node(List* l, int v){
    if(l->head!=NULL){
         Node* node = l->head;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = v;
    while (node->next != l->head)
    {
        node = node->next;
    }
    node->next = newNode;
    newNode->next = l->head;
    }else{
        Node* newNode = (Node*)malloc(sizeof(Node));
        l->head = newNode;
        newNode->info = v;
        newNode->next = l->head;
    }
   
    
}

int size_list(List* l){
    int count = 0;
    Node* node = l->head;
    while (node != NULL)
    {
        count++;
        node = node->next;
    }
    return count;
}

void delete_element_list(List* l, int v){
    Node* before = NULL;
    Node* node = l->head;

    while (node!=NULL && node->info!=v)
    {
        before = node;
        node = node->next;
    }
    if(node != NULL){
        if(before == NULL){
            l->head = node->next;
        }else{
            before->next = node->next;
        }
        free(node);
    }
     
}
