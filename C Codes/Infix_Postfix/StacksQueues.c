
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 50


struct stack {
    char items[SIZE];
    int top;
};
struct intstack {
    int items[SIZE];
    int top;
};
int push(struct stack*stackPTR, char x);
int intpush(struct intstack*intstackPTR, int x);
int full(struct stack*stackPTR);
int intfull(struct intstack*intstackPTR);
int empty(struct stack*stackPTR);
int intempty(struct intstack*intstackPTR);
char pop(struct stack*stackPTR);
int intpop(struct intstack*intstackPTR);
int power(int base, int exponent);


char *menu();
int isBalancedParentheses(char * infix);
char * convertToPostfix(char * infix);
int isOperator(char c);
int getOperatorPriority(char c);
int convertToInt(char c);
int calculate(int a, int b, char op);
void evaluateix(char * postfix);






int main(){
char *str;
char *postfix;


while(strcmp((str=menu()), "exit")!=0){
if (isBalancedParentheses(str)){
printf("parentheses: balanced\n");
postfix = convertToPostfix(str);
printf("postfix: %s\n", postfix);
evaluateix(postfix);

}
else{
    printf("parentheses: unbalanced\n");
    printf("postfix: n/a\n");
    printf("output: n/a\n");
}
}
free(str);
free(postfix);
return 0;
}

char *menu(){
    char r;
    char * infixarray;
    
    
    scanf(" %c", &r);
    getchar();
    if(r=='e'){
         infixarray  = malloc(SIZE*sizeof(char));
         
        scanf("%[^\n]", infixarray);
       
        printf("infix: %s\n", infixarray);
    }
    else if (r=='x'){
         infixarray = malloc(5*sizeof(char));
        char array[5] = "exit\0";
        strcpy(infixarray, array);
    }
    return infixarray;
}
int isBalancedParentheses(char * infix){
struct stack expression;
int i, ret, retval;
int valid = 1;
char ch;
expression.top=-1;
for( i = 0; infix[i]!='\0'; i++){
  if((infix[i])==' ') {
      i++;
  } 
ch = infix[i];
if(ch=='('){
    ret = push(&expression, ch);
    if(ret==0){
        printf("The stack is full.\n");
        
    }
   
}
if(ch==')'){
    retval = pop(&expression);
    if(retval=='#'){
        valid=0;
        
    }
    
}
}
if(!empty(&expression)){
    valid=0;
}
if(valid==1){
    return 1;
}
else{
    return 0;
}
}

char * convertToPostfix(char * infix){

struct stack expression;
expression.top=-1;
int i;
int prio[50];
int j = 0;
int k = 0;
char * postfix;
postfix = (char*)malloc(SIZE*sizeof(char));
for(i=0;i<strlen(infix);i++){
    
   if(infix[i]==')'){
       while(expression.items[expression.top]!='('){
           j--;
           postfix[k] = pop(&expression);
           
           
           k++;
            
           postfix[k] = ' ';
           k++;
       }
       pop(&expression);
       j--;
       
     
      
   }
   char ch = infix[i];
   if(isOperator(ch)){
       
       prio[j]=getOperatorPriority(ch);
       
       if(j>0){
            if(prio[j]<=prio[j-1]){
                while(expression.items[expression.top]!='('){
                    if(empty(&expression)){
                        break;
                    }
                    
                     postfix[k]=pop(&expression);
                    
                      
                    k++;
                     
                    postfix[k]=' ';
                    k++;
           }
           
       }
       }
      if((infix[i-1]!=')' && infix[i-1]!=' ') || j==0){
          j++;
      }
            
      
       
       push(&expression, ch);
       
   }
   else if ( ch!=')' ){
       postfix[k]=ch;
        
       k++;
        
       char testvalue = infix[i+1];
       if(isOperator(testvalue) || testvalue==')'){
            postfix[k]=' ';
           k++;
            
       }
   }
   
   
   
}
while(!empty(&expression)){
    
    if(!isOperator(postfix[k-2])){
        postfix[k]=' ';
        k++;
    }
  
    postfix[k]=pop(&expression);
    
    k++;
    postfix[k]=' ';
    k++;
}
int nullTerminator = strlen(postfix);
postfix[nullTerminator-1]='\0';

 return postfix;
}







int push(struct stack*stackPTR, char x){
if(full(stackPTR)){
    
    return 0;
}
stackPTR->items[stackPTR->top+1]=x;
(stackPTR->top)++;
return 1;
}

char pop(struct stack*stackPTR){
    char retval;
    if(empty(stackPTR)){
        return '#';
    }
    retval = stackPTR->items[stackPTR->top];
    (stackPTR->top)--;
    return retval;
}


int full(struct stack*stackPTR){
    return (stackPTR->top == SIZE-1);
}
int intfull(struct intstack*intstackPTR){
    return (intstackPTR->top == SIZE-1);
}

int empty(struct stack*stackPTR){
    
    return (stackPTR->top == -1);
}
int intempty(struct intstack*intstackPTR){
    return (intstackPTR->top == -1);
}

int isOperator(char c){
    if((c=='+' || c=='-' || c=='/' || c=='*' || c=='^' || c =='%' || c=='(')&& c!=')'){
        return 1;
    }
     else {
        return 0;
    }
}


int getOperatorPriority(char c){
if(c=='('){
    return 4;
}
if(c=='^'){
    return 3;
}
if(c=='%' || c=='*' || c=='/'){
    return 2;
}
if(c=='+' || c=='-'){
    return 1;
}
}
void evaluateix(char * postfix){

struct intstack expression;
expression.top=-1;
int x[SIZE];
int k;
int i;
int multidigit;
int singledigit;
for(i=0;i<strlen(postfix);i++){
    
    
    
    if(!isOperator(postfix[i])){
        
        int j = 0;
        while(postfix[i]!=' '){
            
            x[j] = convertToInt(postfix[i]);
            
            i++;
            j++;
            
        }
        if(j>1){
            for(k=0;k<j;k++){
                if(k==0){
                    multidigit = (0*10)+ x[k];
                    k++;
                }
                multidigit = (multidigit * 10) + x[k];
            }
        intpush(&expression, multidigit);
        }
        else if ( j==1){
            singledigit = x[0];
            intpush(&expression, singledigit);
        }
    }
    else if (isOperator(postfix[i])){
        
        int operandB = intpop(&expression);
        int operandA = intpop(&expression);
        char op = postfix[i];
       
        int temp = calculate(operandA, operandB, op);
       
        intpush(&expression, temp);
        
        i++;
    }
}

int result = intpop(&expression);
printf("value: %d\n", result);
}
int convertToInt(char c){
int x = c-'0';
return x;
}
int calculate(int a, int b, char op){
    int calculation;
    if(op=='+'){
        calculation = a+b;
    }
    if(op=='-'){
        calculation = a-b;
    }
    if(op=='/'){
        calculation = a/b;
    }
    if(op=='*'){
        calculation = a*b;
    }
    if(op=='^'){
        calculation = power(a, b);
    }
    if(op=='%'){
        calculation = a%b;
    }
    return calculation;
}
int power(int base, int exponent){
    int result=1;
    for(exponent; exponent>0; exponent--){
        result*=base;
    }
    return result;
}
int intpush(struct intstack*intstackPTR, int x){
    if(intfull(intstackPTR)){
    
    return 0;
}
intstackPTR->items[intstackPTR->top+1]=x;
(intstackPTR->top)++;
return 1;
}
int intpop(struct intstack*intstackPTR){
    int retval;
    if(intempty(intstackPTR)){
        return '#';
    }
    retval = intstackPTR->items[intstackPTR->top];
    (intstackPTR->top)--;
    return retval;
}