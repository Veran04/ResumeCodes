#include <stdio.h>
#include <stdlib.h>

int main(){
    char incomeString[50];
    int income;
    int tempval;
    int tempval2;
    int tempval3;
    int tempval4;
    int tempval5;
    int tempval6;
    int sum = 0; 

    printf("Income this month? Currently two biweekly work checks and L.I adding to 4430");
    scanf(" %s", incomeString);
    income = atoi(incomeString);

    

    //the Great Lakes username is Veran99 and the password is my phoenix defense password


    printf("\nDo not include transactions that occurred today on the 15th, but DO include transactions from the 15th of the previous month. Press 0 to Confirm.");

    while(tempval3 != 0){
        scanf(" %s", incomeString);
        tempval3 = atoi(incomeString);
    }


    printf("\nOnce my salary reaches six figures, or once the year reaches 2025, opt into my company's 401k if there is still a company match. Look into pre-tax vs. post-tax. Press 0 to confirm.");


    while(tempval4 != 0){
        scanf(" %s", incomeString);
        tempval4 = atoi(incomeString);
    }


    printf("\nUpdate benefits plan & prices once I have a domestic partner. Make her a beneficiary too? Press 0 to confirm.");


    while(tempval5 != 0){
        scanf(" %s", incomeString);
        tempval5 = atoi(incomeString);
    }

    printf("\nIf savings account reaches 8 thousand & checking account has at least 4  thousand, dump savings into my loans. 0 to confirm");


    while(tempval6 != 0){
        scanf(" %s", incomeString);
        tempval6 = atoi(incomeString);
    }

    

    tempval2 = income * 0.1;
    printf("\nSubtract 10 percent towards student loans (stocks after masters degree with Mitchell)");
    tempval = income * 0.1;
    income -= tempval;
    printf("\nThen, I will subtract 10 percent towards my savings account");
    income -= tempval2;
    printf("\nNext is rent, which is currently $861");
    income -= 861;
    printf("\nNext is car insurance, currently $180");
    income -= 180;

    printf("\n1FB annual card fee. Press 1 If it is October To Remove $25 for the fee");
    scanf(" %s", incomeString);
    tempval3 = atoi(incomeString);
    if(tempval3 == 1){
        income -= 25;
    }


    printf("\nBegin entering remaining charges");

    while(tempval != 0){
        scanf(" %s", incomeString);
        tempval = atoi(incomeString);
        sum += tempval;
    }
    income -= sum;
    sum = 0;
    tempval = 5000000;


    printf("\n\nYour remaining money to invest into student loans and later savings is: %d", income);

}

