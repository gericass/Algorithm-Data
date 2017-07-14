#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHYSCHECK_VISION 1
#define PHYSCHECK_HEIGHT 2
#define PHYSCHECK_NAME 4

typedef struct {
    double vision;
    int height;
} Body;

typedef struct {
    char *name;
    Body body;
} PhysCheck;

typedef struct __bnode{
    PhysCheck data;
    struct __bnode *left;
    struct __bnode *right;
} BinNode;


int PhysHeightCmp(const PhysCheck *x, const PhysCheck *y){
    return x->body.height < y->body.height ? -1 : x->body.height > y->body.height ? 1 : 0; 
}

int PhysVisionCmp(const PhysCheck *x, const PhysCheck *y){
    return x->body.vision < y->body.vision ? -1 : x->body.vision > y->body.vision ? 1 : 0;
}

int PhysNameCmp(const PhysCheck *x,const PhysCheck *y){
    return strcmp(x->name,y->name);
}

void PrintLnPhys(const PhysCheck *x){
    printf("%lf %d %s\n",x->body.vision,x->body.height,x->name);
}

PhysCheck ScanMember(const char *message,int sw){
    PhysCheck temp;
    char name[82];
    printf("%sするデータを入力してください。\n",message);
    if(sw & PHYSCHECK_VISION){printf("視力："); scanf("%lf",&temp.body.vision);}
    if(sw & PHYSCHECK_HEIGHT){printf("身長："); scanf("%d",&temp.body.height);}
    if(sw & PHYSCHECK_NAME){printf("氏名："); scanf("%s",name);}
    temp.name = calloc(strlen(name)+1,sizeof(char));
    strcpy(temp.name,name);

    return temp;
}

static BinNode *AllocBinNode(void){
    return calloc(1,sizeof(BinNode));
}

/*--- ノードの各メンバに値を設定 ----*/
static void SetBinNode(BinNode *n, const PhysCheck *x,
    const BinNode *left, const BinNode *right){
    n->data = *x; /* データ */
    n->left = (BinNode *)left; /* 左子ノードへのポインタ */
    n->right = (BinNode *)right;/* 右子ノードへのポインタ */
}
/*--- 探索 ---*/
BinNode *Search(BinNode *p, const PhysCheck *x){
    int cond;
    if (p == NULL)
        return NULL; /* 探索失敗 */
    else if ((cond = PhysNameCmp(x, &p->data)) == 0)
        return p; /* 探索成功 */
    else if (cond < 0)
        return Search(p->left, x); /* 左部分木から探索 */
    else
        return Search(p->right, x); /* 右部分木から探索 */
}
/*--- ノードを挿入 ---*/
BinNode *Add(BinNode *p, const PhysCheck *x, const int type){
    int cond;
    if (p!=NULL){
        if(type==1){
            cond = PhysVisionCmp(x,&p->data);
        }else if(type==2){
            cond = PhysHeightCmp(x,&p->data);
        }else{
            cond = PhysNameCmp(x,&p->data);
        }
    }
    if (p == NULL) {
        p = AllocBinNode();
        SetBinNode(p, x, NULL, NULL);
        if(type==1){
            cond = PhysVisionCmp(x,&p->data);
        }else if(type==2){
            cond = PhysHeightCmp(x,&p->data);
        }else{
            cond = PhysNameCmp(x,&p->data);
        }
    } else if (cond == 0)
        printf("【エラー】%s は既に登録されています。\n", x->name);
    else if (cond < 0)
        p->left = Add(p->left, x,type);
    else
        p->right = Add(p->right, x,type);
    return p;
}
/*--- ノードを削除 ---*/
int Remove(BinNode **root, const PhysCheck *x){
    BinNode *next, *temp;
    BinNode **left;
    BinNode **p = root;
    while (1) {
        int cond;
        if (*p == NULL) {
            printf("【エラー】%s は登録されていません。\n", x->name);
            return -1; /* そのキーは存在しない */
        } else if ((cond = PhysNameCmp(x, &(*p)->data)) == 0)
            break; /* 探索成功 */
        else if (cond < 0)
            p = &((*p)->left); /* 左部分木から探索 */
        else
            p = &((*p)->right);/* 右部分木から探索 */
    }

    if ((*p)->left == NULL)
        next = (*p)->right;
    else {
        left = &((*p)->left);
        while ((*left)->right != NULL)
            left = &(*left)->right;
        next = *left;
        *left = (*left)->left;
        next->left = (*p)->left;
        next->right = (*p)->right;
    }
    temp = *p;
    *p = next;
    free(temp);
    return 0;
}
/*--- 全ノードのデータを表示 ---*/
void PrintTree(const BinNode *p){
    if (p != NULL) {
        PrintTree(p->left);
        PrintLnPhys(&p->data);
        PrintTree(p->right);
    }
}
/*--- 全ノードの削除 ---*/
void FreeTree(BinNode *p){
    if (p != NULL) {
        FreeTree(p->left);
        FreeTree(p->right);
        free(p);
    }
}
/*--- メニュー ---*/
typedef enum {
    TERMINATE, ADD, REMOVE, SEARCH, PRINT_ALL
} Menu;
/*--- メニュー選択 ---*/
Menu SelectMenu(void){
    int i, ch;
    char *mstring[] = {"挿入","削除","探索", "表示"};
    do {
        for (i = TERMINATE; i < PRINT_ALL; i++) {
            printf("(%2d) %-18.18s ", i + 1, mstring[i]);
            if ((i % 3) == 2)
            putchar('\n');
        }
        printf("( 0) 終了 ：");
        scanf("%d", &ch);
    } while (ch < TERMINATE || ch > PRINT_ALL);
    return (Menu)ch;
}

int main(void){
    Menu menu;
    BinNode *root = NULL; /* ２分探索木の根へのポインタ */
    int type;
    printf("(1)視力で木を作成 (2)身長で木を作成 (4)名前で木を作成\n");
    scanf("%d",&type);
    do {
        PhysCheck x;
        BinNode *temp;
        switch (menu = SelectMenu()) {
        /*--- ノードの挿入 ---*/
        case ADD :
            x = ScanMember("挿入", PHYSCHECK_VISION|PHYSCHECK_HEIGHT|PHYSCHECK_NAME);
            root = Add(root, &x,type);
            break;
        /*--- ノードの削除 ---*/
        case REMOVE :
            x = ScanMember("削除", PHYSCHECK_NAME);
            Remove(&root, &x);
            break;
        /*--- ノードの探索 ---*/
        case SEARCH :
            x = ScanMember("探索", PHYSCHECK_NAME);
            if ((temp = Search(root, &x)) != NULL)
            PrintLnPhys(&temp->data);
            break;
        /*--- 全ノードの表示 ---*/
        case PRINT_ALL :
            puts("【一覧表】");
            PrintTree(root);
            break;
        case TERMINATE :
            break;
        }
    } while (menu != TERMINATE);
    FreeTree(root);
    return 0;
}