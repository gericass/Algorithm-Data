#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_NO    1
#define MEMBER_NAME  2

typedef struct {
    int no;
    char name[20];
} Member;

typedef struct __node{
    Member data;
    struct __node *text;
} Node;

typedef struct {
    Node *head;
    Node *crnt;
} List;

int MemberNoCmp(const Member *x, const Member *y){
    return x->no < y->no ? -1 : x->no ? 1 : 0;
}

int MemberNameCmp(const Member *x,const Member *y){
    return strcmp(x->name,y->name);
}

void PrintMember(const Member *x){
    printf("%d %s",x->no,x->name);
}

void PrintLnMember(const Member *x){
    printf("%d %s\n",x->no,x->name);
}

Member ScanMember(const char *message,int sw){
    Member temp;

    printf("%sするデータを入力してください。\n",message);

    if(sw & MEMBER_NO) { printf("番号："); scanf("%d",&temp.no); }
    if(sw & MEMBER_NAME) { printf("氏名："); scanf("%s",temp.name); }
    return temp;
}

static Node *AllocNode(void){
    return calloc(1,sizeof(Node));
}

static void SetNode(Node *n,const Member *x,const Node *next){
    n->data = *x;
    n->next = next;
}

void Initialize(List *list){
    list->head = NULL;
    list->crnt = NULL;
}

Node *Search(List *list,const Member,
            int compare(const Member *x, const Member *y)){
    Node *ptr = list->head;

    while(ptr != NULL){
        if(compare(&ptr->data,x)==0){
            list->crnt = ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void InsertFront(List *list,const Member *x){
    Node *ptr = list->head;
    list->head = list->crnt = AllocNode();
    SetNode(list->head,x,ptr);
}