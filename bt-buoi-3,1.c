#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
char stack[MAX];
int top =-1;
void push(char item){
    if(top>=MAX-1){
        printf("stack overflow\n");
        
    }else{
        stack[++top]=item;
        
    }
}
char pop(){
    if (top<0){
        printf("stack underflow\n");
        return -1;
    }
    else{
        return stack[top--];
    }
}
int precedence(char symbol){
    switch(symbol){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
			return 2;
        case '^':
			return 3;
        default:
            return 0;
    }
}
int isoperator(char symbol){
    return (symbol =='+'||symbol=='-'||symbol=='*'||symbol=='/'||symbol=='^');
}
void infixtopostfix(char infix[], char postfix[]){
    int i=0, j=0;
    char item;
    char x;
    push('(');
    strcat(infix, ")");
    item=infix[i];
    while (item!='\0'){
        if (item=='('){
            push(item);
            
        }else if (isdigit(item)||isalpha(item)){
            postfix[j++]=item;
        }else if (isoperator(item)){
            x=pop();
            while (isoperator(x)&&precedence(x)>=precedence(item)){
                postfix[j++]=x;
                x=pop();
            }
            push(x);
            push(item);
        }else if (item==')'){
            x=pop();
            while (x!='('){
                postfix[j++]=x;
                x=pop();
            }
        }else{
            printf("biểu thức infix không hợp lệ");
            return;
        }
        i++;
        item = infix[i];
    }
    postfix[j]='\0';
}
int main() {
    //Tiếp tục hoàn thiện mã nguồn
    char infix[MAX], postfix[MAX];
    gets(infix);
    infixtopostfix(infix,postfix);
    printf("%s\n",postfix);
    return 0;
}