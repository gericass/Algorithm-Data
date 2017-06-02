#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int max;
  int num;
  int front;
  int rear;
  char **que;
}StringQueue;

int Initialize(StringQueue *q,int max){
  q->num = q->front = q->rear = 0;
  if((q->que=calloc(max,sizeof(char *)))==NULL){
    q->max=0;
    return -1;
  }
  q->max = max;
  return 0;
}

void Terminate(StringQueue *q){
  if(q->que!=NULL){
    free(q->que);
    q->max = q->num = q->front = q->rear = 0;
  }
}


int Count(StringQueue *q, char *x){
  int count = 0;
for(int i = 0;i<q->num;i++){
  int key = strcmp(x,q->que[(i+q->front)%q->max+1]);
  if(key==0){
    count++;
  }
}
return count;
}


int Enque(StringQueue *q,char *x){
  if(q->num >=q->max){
   q->que = realloc(q->que,(q->max+7)*sizeof(char *));
   q->max = q->max + 7;
   
  }
  
  q->num++;
  q->rear++;
  q->que[q->rear]=calloc(strlen(x)+1,sizeof(char));
  strcpy(q->que[q->rear],x);
  //if(q->rear == q->max)q->rear = 0;
  return 0;
  
}

int Deque(StringQueue *q,char *x){
  if(q->num <=0)
    return -1;
  else{
    q->num--;
    q->front++;
    x = calloc(strlen(x)+1,sizeof(char));
    strcpy(x,q->que[q->front]);
    if(q->max-q->num >= 15){
      q->que = realloc(q->que,(q->max-5)*sizeof(char *));
      q->max = q->max - 5;
    }
    //if(q->front == q->max)q->front = 0;
    return 0;
  } 
}

int Peek(const StringQueue *q,char *x){
  if(q->num <= 0)
    return -1;
  //q->que[q->front] = calloc(strlen(x)+1,sizeof(char));
  strcpy(x,q->que[q->front]);
  return 0;
}

int Capacity(const StringQueue *q){
  return (q->max);
}

int Size(const StringQueue *q){
  return(q->num);
}

void Print(const StringQueue *q){
  int i;

  for(i = 0;i<q->num;i++)
    printf("%s",q->que[(i+q->front)%q->max+1]);
  putchar('\n');
}

int main(void){
  StringQueue que;

   if(Initialize(&que,10)==-1){
       puts("キューの生成に失敗しました。\n");
       return 1;
   }

    while(1){
      int m;
      char x[82];
      char y[82];
       

        printf("現在のデータ数:%d/%d\n",Size(&que),Capacity(&que));
        printf("(1)エンキュー(2)デキュー(3)ピーク(4)表示(5)パターンの計数(0)終了:");
        scanf("%d",&m);

        if(m==0) break;

        switch(m){
            case 1:
             printf("データ:");
             scanf("%s",x);
             if(Enque(&que,x)==-1)
               puts("\aエラー:データのエンキューに失敗しました。\n");
             break;
            case 2:
             if(Deque(&que,x)==-1)
              puts("\aエラー:デキューに失敗しました。\n");
             else
              printf("デキューしたデータは%sです。\n",x);
             
             break;
            case 3:
             if(Peek(&que,x)==-1)
              puts("\aエラー:ピークに失敗しました。\n");
             else
              printf("ピークしたデータは%sです。\n",x);
             break;
            case 4:
             Print(&que);
             break;
            case 5:
             scanf("%s",y);
             int c = Count(&que,y);
             if(c==0){
               printf("パターンは存在しません。\n");
             }else{
               printf("パターンの数:%d\n",c);
             }
             break;
        }
    }
    Terminate(&que);
    return 0;
}
