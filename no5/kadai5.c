#include <stdio.h>
#include <string.h>
#define MAX 10

typedef struct{
  char name[20];
  int height;
  double vision;
} Data;

typedef struct{
  int max;
  int ptr;
  Data stk[MAX];
} PhysCheckStack;

typedef struct{
  char name[20];
}PhysCheck;




int Initialize(PhysCheckStack *s,int max){
  s->ptr = 0;
  s->max = max;
  return 0;
}

int Push(PhysCheckStack *s,char *n,int h,double v){
  if(s->ptr >= s->max) return -1;
  strcpy(s->stk[s->ptr].name, n);
  //s->stk[s->ptr].name = n;
  s->stk[s->ptr].height = h;
  s->stk[s->ptr].vision = v;
  s->ptr++;
  return 0;
}

int Pop(PhysCheckStack *s,char *n,int *h,double *v){
  if(s->ptr <= 0)return -1;
  s->ptr--;
  strcpy(n,s->stk[s->ptr].name);
  //n = s->stk[s->ptr -1].name;
  *h = s->stk[s->ptr].height;
  *v = s->stk[s->ptr].vision;
  return (0);
}

int Peek(PhysCheckStack *s,char *n,int *h,double *v){
  if(s->ptr <= 0)return -1;
  n = s->stk[s->ptr -1].name;
  *h = s->stk[s->ptr -1].height;
  *v = s->stk[s->ptr -1].vision;
  return 0;
}

int Capacity(const PhysCheckStack *s){
  return s->max;
}

int Size(const PhysCheckStack *s){
  return s->ptr;
}

void Print(const PhysCheckStack *s){
  int i;
  for(i = 0;i< s->ptr;i++)
    printf("%s %d %lf\n",s->stk[i].name,s->stk[i].height,s->stk[i].vision);
  putchar('\n');
}

int Search(PhysCheckStack *s, PhysCheck *x){
  int i;
  int count=0;
  for(i = 0;i< s->ptr; i++){
    if(strcmp(s->stk[i].name,x->name)==0){
      count++;
      printf("%s %d %lf\n",s->stk[i].name,s->stk[i].height,s->stk[i].vision);
    }
  }
  return count;
}


int main(void){
  PhysCheckStack s;
  PhysCheck p;
  int mx;
  printf("スタックの大きさを入力してください。");
  scanf("%d",&mx);

  Initialize(&s,mx);

  while(1){
    int menu;
    char n[20];
    int h;
    double v;
    printf("現在のデータ数:%d/%d\n",Size(&s),Capacity(&s));
    printf("(1)プッシュ (2)ポップ (3)ピーク (4)表示 (5)探索 (0)終了:");
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
      case 5:
	scanf("%s",p.name);
        int res =  Search(&s,&p);
        if(res==0)
	  printf("パターンは存在しません。\n");
        break;
    }
  }
  return 0;
}

