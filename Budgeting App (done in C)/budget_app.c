#include <stdio.h>
#include <stdlib.h>

int main(){
    char incomeString[50];
    int income;
    int tempval;
    int sum = 0; 

    printf("What is your income this month?");
    scanf(" %s", incomeString);
    income = atoi(incomeString);
    printf("\nFirst, I will subtract 10 percent towards student loans");
    tempval = income * 0.1;
    income -= tempval;
    printf("\nNext is rent, which is currently $861");
    income -= 861;
    printf("\nNext is car insurance, currently $170");
    income -= 170;
    printf("\nNext is gas, $60");
    income -= 60;
    printf("\nBegin entering values for the first variable category, for me, food. Enter 0 when done entering values.");

    while(tempval != 0){
        scanf(" %s", incomeString);
        tempval = atoi(incomeString);
        sum += tempval;
    }
    income -= sum;
    sum = 0;
    tempval = 5000000;

    printf("\nBegin entering values for the second variable category, for me, entertainment.");

    while(tempval != 0){
        scanf(" %s", incomeString);
        tempval = atoi(incomeString);
        sum += tempval;
    }
    income -= sum;
    sum = 0;
    tempval = 5000000;

    printf("\nBegin entering values for the last variable category, for me, misc. goods");

    while(tempval != 0){
        scanf(" %s", incomeString);
        tempval = atoi(incomeString);
        sum += tempval;
    }
    income -= sum;
    sum = 0;
    tempval = 5000000;

    printf("\n\nYour remaining money to invest how you see fit is: %d", income);

}

