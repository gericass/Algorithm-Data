#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  String_Max 82

typedef struct {
    int max;
    int ptr;
    char **stk;
} Stack;

int Initialize(Stack *s, int max) {
    s->ptr = 0;
    if ((s->stk = calloc(max, sizeof(char *))) == NULL) {
        s->max = 0;
        return -1;
    }
    s->max = max;
    return 0;
}


int Push(Stack *s, char *x) {
    if (s->ptr >= s->max) return -1;
    s->stk[s->ptr] = calloc(strlen(x)+1, sizeof(char));
    strcpy(s->stk[s->ptr], x);
    s->ptr++;
    return 0;
}


int Pop(Stack *s, char *x) {
    if (s->ptr <= 0) return -1;
    strcpy(x, s->stk[--s->ptr]);
    return 0;
}

int IsEmpty(const Stack *s) {
    return s->ptr <= 0;
}

void recur3(char *st) {
    Stack stk;
    char *temp;

    Initialize(&stk, 100);
    temp = calloc(strlen(st)+1,sizeof(char));


    while(1){
        if( (strlen(st)) > 0 ){
        printf("%c",*st);
        Push(&stk, st);
        if (strlen(st)>1) st += 2;
        else st++;
        }
        else if( !IsEmpty(&stk) ){
            st = temp;
            Pop(&stk, st);
            printf("%c",*st);
            st++;
        }else{
            break;
        }

    }
    free(temp);
}


int main(void) {
    char x[String_Max];
    scanf("%s",x);
    recur3(x);
    printf("\n");
    
        
    return 0;
}