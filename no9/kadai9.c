#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHYSCHECK_VISION  1
#define PHYSCHECK_HEIGHT  2
#define PHYSCHECK_NAME    4

typedef struct{
    double vision;
    int height;
}Body;

typedef struct{
    char *name;
    Body body;
}PhysCheck;

typedef struct __node{
    PhysCheck data;
    struct __node *prev;
    struct __node *next;
} Node;

typedef struct {
    Node *head;
    Node *crnt;
} List;

int PhysHeightCmp(const PhysCheck *x, const PhysCheck *y){
    return x->body.height < y->body.height ? -1 : x->body.height > y->body.height; 
}

int PhysVisionCmp(const PhysCheck *x, const PhysCheck *y){
    return x->body.vision < y->body.vision ? -1 : x->body.vision > y->body.vision ? 1 : 0;
}

int PhysNameCmp(const PhysCheck *x,const PhysCheck *y){
    return strcmp(x->name,y->name);
}

void PrintMember(const PhysCheck *x){
    printf("%d %lf %s",x->body.height,x->body.vision,x->name);
}

void PrintLnMember(const PhysCheck *x){
    printf("%d %lf %s\n",x->body.height,x->body.vision,x->name);
}

PhysCheck ScanMember(const char *message,int sw){
    PhysCheck temp;
    char name[82];

    printf("%sするデータを入力してください。\n",message);

    if(sw & PHYSCHECK_HEIGHT) { printf("身長："); scanf("%d",&temp.body.height); }
    if(sw & PHYSCHECK_VISION) { printf("視力："); scanf("%lf",&temp.body.vision); }
    if(sw & PHYSCHECK_NAME) { printf("氏名："); scanf("%s",name); }
    temp.name = calloc(strlen(name)+1,sizeof(char));
    strcpy(temp.name,name);

    return temp;
}

static Node *AllocNode(void){
    return calloc(1,sizeof(Node));
}




static void SetNode(Node *n,const PhysCheck *x,Node *prev, Node *next){
    n->data = *x;
    if ((n->data.name = calloc(strlen(x->name)+1, sizeof(char))) == NULL) {
        return ;
    }
    strcpy(n->data.name,x->name);
    n->prev = (Node *) prev;
    n->next = (Node *) next;
}

void Initialize(List *list){
    Node *dummyNode = AllocNode(); 
    list->head = list->crnt = dummyNode;
    dummyNode->prev = dummyNode->next = dummyNode;
}

Node *Search(List *list,const PhysCheck *x,int compare(const PhysCheck *x, const PhysCheck *y)){
    Node *ptr = list->head;

    while(ptr != NULL){
        if(compare(&ptr->data,x)==0){
            list->crnt = ptr;
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void InsertAfter(List *list, Node *p, const PhysCheck *x){
    Node *ptr = AllocNode();
    Node *nxt = p->next;
    p->next = p->next->prev = ptr;
    SetNode(ptr, x, p, nxt);
    list->crnt = ptr; 
}

void InsertFront(List *list,const PhysCheck *x){
    InsertAfter(list, list->head, x);
}

void InsertRear(List *list,const PhysCheck *x){
    InsertAfter(list, list->head->prev, x);
}

void Remove(List *list, Node *p){
    p->prev->next = p->next;
    p->next->prev = p->prev;
    list->crnt = p->prev; 
    free(p->data.name);
    free(p);
    if (list->crnt == list->head)
        list->crnt = list->head->next;

}

static int IsEmpty(const List *list){
    return list->head->next == list->head;
}

void RemoveFront(List *list){
   if (!IsEmpty(list))
     Remove(list, list->head->next);
}

void RemoveRear(List *list){
    if (!IsEmpty(list))
        Remove(list, list->head->prev);
}

void RemoveCurrent(List *list){
    if (list->crnt != list->head)
        Remove(list, list->crnt);
}

void Clear(List *list){
    while(list->head!=NULL)
        RemoveFront(list);
}

void PrintCurrent(const List *list){
    if (IsEmpty(list))
        printf("着目要素はありません。");
    else
        PrintMember(&list->crnt->data);
}

void PrintLnCurrent(const List *list){
    PrintCurrent(list);
    putchar('\n');
}


void  Terminate(List *list){
    Clear(list);
    free(list->head);
}

void Print(const List *list){
    if(IsEmpty(list))
        puts("ノードがありません。");
    else{
        Node *ptr = list->head->next;

        puts("【一覧表】");

        while(ptr!=NULL){
            PrintLnMember(&ptr->data);
            ptr = ptr->next;
        }
    }
}

typedef enum {
    TERMINATE, INS_FRONT, INS_REAR, RMV_FRONT, RMV_REAR, PRINT_CRNT,
    RMV_CRNT, SRCH_HEIGHT, SRCH_VISION, SRCH_NAME, PRINT_ALL, CLEAR
}Menu;

Menu SelectMenu(void){
    int i, ch;
    char *mstring[] = {
        "先頭にノードを挿入","末尾にノードを挿入","先頭のノードを削除",
        "末尾のノードを削除","着目ノードを表示","着目ノードを削除",
        "身長で探索","視力で探索","名前で検索","全ノードを表示","全ノードを削除"
    };

    do{
        for(i = TERMINATE; i<CLEAR;i++){
            printf("(%2d) %s",i+1,mstring[i]);
            if((i%3)==2)
                putchar('\n');
        }
        printf("( 0)終了：");
        scanf("%d",&ch);
    }while(ch<TERMINATE||ch>CLEAR);

    return (Menu)ch;
}

int main(void){
    Menu menu;
    List list;
    PhysCheck x;

    Initialize(&list);

    do{
        switch(menu = SelectMenu()){
            case INS_FRONT:
                x = ScanMember("先頭に挿入",PHYSCHECK_HEIGHT | PHYSCHECK_VISION | PHYSCHECK_NAME);
                InsertFront(&list,&x);
                break;
            case INS_REAR:
                x = ScanMember("末尾に挿入",PHYSCHECK_HEIGHT | PHYSCHECK_VISION | PHYSCHECK_NAME);
                InsertRear(&list,&x);
                break;
            case RMV_FRONT:
                RemoveFront(&list);
                break;
            case RMV_REAR:
                RemoveRear(&list);
                break;
            case PRINT_CRNT:
                PrintLnCurrent(&list);
                break;
            case RMV_CRNT:
                RemoveCurrent(&list);
                break;

            case SRCH_HEIGHT:
                x = ScanMember("探索",PHYSCHECK_HEIGHT);
                if(Search(&list,&x,PhysHeightCmp)!=NULL)
                    PrintLnCurrent(&list);
                else
                    puts("その身長のデータはありません。");
                break;
            case SRCH_VISION:
                x = ScanMember("探索",PHYSCHECK_VISION);
                if(Search(&list,&x,PhysVisionCmp)!=NULL)
                    PrintLnCurrent(&list);
                else
                    puts("その視力のデータはありません。");
                break;
            case SRCH_NAME:
                x = ScanMember("探索",PHYSCHECK_NAME);
                if(Search(&list,&x,PhysNameCmp)!=NULL)
                    PrintLnCurrent(&list);
                else
                    puts("その名前のデータはありません。");
                break;

            case PRINT_ALL:
                Print(&list);
                break;
            case CLEAR:
                Clear(&list);
                break;
            case TERMINATE:
                break;

        }
    }while(menu!=TERMINATE);
    Terminate(&list);
    return 0;

}