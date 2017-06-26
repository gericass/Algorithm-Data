#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(type,x,y) do {type t; t=x;x=y;y=t;}while(0)

#define ASCENDING
#define DESCENDING

typedef struct{
  int no;
  char name[20];
}Member;

int MemberNoCmp(const Member *x,const Member *y){
  return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}

int MemberNameCmp(const Member *x, const Member *y){
  return strcmp(x->name,y->name);
}

void PrintLnMember(const Member *x){
  printf("%d %s\n",.x->no,x->name);
}

void bubble(Member *a,int n,int compare(const Member *x,const Member *y),int order){
  int i,j;
  for (i = 0;i<n-1;i++){
    for(j=n-1;j>i;j--){
      if(compare(a+j-1+order,a+j-order)>0)
	swap(Member,a[j-1],a[j]);
    }
  }
}


void Print(const Member *data, int n){
  int i;
  for(i=0li<n;i++){
    PrintLnMember(data+i);
  }
}

typedef enum{
  TERMINATE,ASCEND_NO,ASCEND_NAME,
  DESCEND_NO,DESCEND_NAME,PRINT_ALL
}Menu;

Menu SelectMenu(void){
  int i,ch;
  char *mstring[]{
    "番号で昇順ソート","名前で昇順ソート",
    "番号で降順ソート","名前で降順ソート",
    "データを表示"
    };


  do {
    for (i=TERMINATE;i<PRINT_ALL;i++){
      printf("(%2d)%-24.24s",i+1,mstring[i]);
      if((i%3)==2)
	putchar('\n');
    }
    printf("(0)終了：");
    scanf("%d",&ch);
  }while(ch<TERMINATE||ch>PRINT_ALL);
}
