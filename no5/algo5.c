#include <stdio.h>
#include <string.h>
#define MAX 10

typedef struct{
  char name[20];
  int height;
  double vision;
  
} PhysCheckStack;

typedef struct{
  int max;
  int ptr;
  PhysCheckStack stk[MAX];
} Stack;

int Initialize(Stack *s,int max){
  s->ptr = 0;
  s->max = max;
  return 0;
}

int Push(Stack *s,char *n,int h,double v){
  if(s->ptr >= s->max) return -1;
  strcpy(s->stk[s->ptr].name, n);
  //s->stk[s->ptr].name = n;
  s->stk[s->ptr].height = h;
  s->stk[s->ptr].vision = v;
  s->ptr++;
  return 0;
}

int Pop(Stack *s,char *n,int *h,double *v){
  if(s->ptr <= 0)return -1;
  s->ptr--;
  strcpy(n,s->stk[s->ptr].name);
  //n = s->stk[s->ptr -1].name;
  *h = s->stk[s->ptr].height;
  *v = s->stk[s->ptr].vision;
  return (0);
}

int Peek(Stack *s,char *n,int *h,double *v){
  if(s->ptr <= 0)return -1;
  n = s->stk[s->ptr -1].name;
  *h = s->stk[s->ptr -1].height;
  *v = s->stk[s->ptr -1].vision;
  return 0;
}

int Capacity(const Stack *s){
  return s->max;
}

int Size(const Stack *s){
  return s->ptr;
}

void Print(const Stack *s){
  int i;
  for(i = 0;i< s->ptr;i++)
    printf("%s %d %lf\n",s->stk[i].name,s->stk[i].height,s->stk[i].vision);
  putchar('\n');
}

int main(void){
  Stack s;
  Initialize(&s,MAX);

  while(1){
    int menu;
    char n[20];
    int h;
    double v;
    printf("現在のデータ数:%d/%d\n",Size(&s),Capacity(&s));
    printf("(1)プッシュ (2)ポップ (3)ピーク (4)表示 (0)終了:");
    scanf("%d",&menu);
    
    if(menu==0) break;

    switch(menu){
      case 1:
       printf("Name:");
       scanf("%s",n);
       printf("Height:");
       scanf("%d",&h);
       printf("Vision:");
       scanf("%lf",&v);
       if(Push(&s,n,h,v)==-1)
         puts("¥aエラー:プッシュに失敗しました。");
       break;
      case 2:
       if(Pop(&s,n,&h,&v)==-1)
         puts("\aエラー:ポップに失敗しました。");
       else
         printf("ポップしたデータは%s,%d,%lfです。\n",n,h,v);
       break;
      case 3:
       if(Peek(&s,n,&h,&v)==-1)
         puts("\aエラー:ピークに失敗しました。");
       else
         printf("ピークしたデータは%s,%d,%lfです。\n",n,h,v);
       break;
      case 4:
       Print(&s);
       break;
    }
  }
  return 0;
}

