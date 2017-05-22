#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define String_Max 80

typedef struct{
    int max;
    int ptr;
    char **stk;
}StringStack;

int Initialize(StringStack *s,int max){
    s->ptr = 0;
    if((s->stk =calloc(max,sizeof(char *)))==NULL){
        s->max=0;
        return -1;
    }
    s->max = max;
    return 0;
}

void Terminate(StringStack *s){
    if(s->stk != NULL){
        while(--s->ptr >=0)
         free(s->stk[s->ptr]);
        free(s->stk);
    }
    s->max = s->ptr = 0;
}

int Push(StringStack *s,char *x){
    if(s->ptr >= s->max) return -1;
    if((s->stk[s->ptr]=calloc(strlen(x)+1,sizeof(char)))==NULL)
     return -1;
    strcpy(s->stk[s->ptr],x);
    s->ptr++;
    return 0;
}

int Pop(StringStack *s,char *x){
    if(s->ptr <= 0) return -1;
    s->ptr--;
    strcpy(x,s->stk[s->ptr]);
    free(s->stk[s->ptr]);
    return 0;
}

int Peek(StringStack *s,char *x){
    if(s->ptr <=0) return -1;
    strcpy(x,s->stk[s->ptr -1]);
    return 0;
}

int Capacity(const StringStack *s){
    return s->max;
}

int Size(const StringStack *s){
    return s->ptr;
}

void Print(const StringStack *s){
    int i;
    for(i = 0;i< s->ptr;i++){
        printf("%s\n",s->stk[i]);
    }
}

int main(void){
    StringStack s;
    int max;

    printf("スタックの大きさを入力してください。");
    scanf("%d",&max);

    if(Initialize(&s,max)==-1){
        puts("スタックの生成に失敗しました。\n");
        return 1;
    }

    while(1){
        int menu;
        char x[String_Max];

        printf("現在のデータ数:%d/%d\n",Size(&s),Capacity(&s));
        printf("(1)プッシュ (2)ポップ (3)ピーク (4)表示 (0)終了");
        scanf("%d",&menu);

        if(menu==0) break;

        switch(menu){
            case 1:
             printf("プッシュする文字列:");
             scanf("%s",x);
             if(Push(&s,x)==-1)
               puts("\aエラー:ポップに失敗しました。\n");
             break;
            case 2:
             if(Pop(&s,x)==-1)
              puts("\aエラー:ポップに失敗しました。\n");
             else{
                printf("ポップに失敗した文字列は%s",x);
             }
             break;
            case 3:
             if(Peek(&s,x)==-1)
              puts("\aエラー:ピークに失敗しました。\n");
             else{
                 printf("ピークに失敗しました。");
             }
             break;
            case 4:
             Print(&s);
             break;
        }
    }
    Terminate(&s);
    return 0;
}
