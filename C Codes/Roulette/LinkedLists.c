#include<stdio.h>
#include<stdlib.h>

typedef struct node
	{
		int data;
		struct node *next;
		struct node *prev;
	}soldier;
    soldier* create_soldier(int x);
    soldier* create_reverse_circle(int n);
    soldier* rearrange_circle(soldier * head);
    void display(soldier * head);
    int kill(soldier * head, int n, int k);





    int main(){
        int soldier_number, i;
        int k;
        
        
        scanf("%d %d", &soldier_number, &k);
        
        soldier * head = create_reverse_circle(soldier_number);
        printf("List: ");
        display(head);
        soldier * newhead = rearrange_circle(head);
        printf("After ordering: ");
        display(newhead);
        int survivor = kill(newhead, soldier_number, k);
        printf("Survived: %d", survivor);
        
        
        
    }
    soldier* create_soldier(int x){
        soldier * newsoldier;
        newsoldier = (soldier*)malloc(sizeof(soldier));
        newsoldier->data=x;
        newsoldier->next=NULL;
        return newsoldier;
    }
    soldier * create_reverse_circle(int n){
        int i;
        soldier * newsoldier, *head, *p;
        newsoldier = (soldier*)malloc(sizeof(soldier));
        newsoldier->data=n;
        newsoldier->next=NULL;
        newsoldier->prev=NULL;
        head = newsoldier;
        p = newsoldier;
        n--;
        for(i=n;i>0;i--){
        newsoldier = create_soldier(i);
        newsoldier->prev=p;
        p->next=newsoldier;
        p = p->next;
        }
        p->next=head;
        head->prev=p;
        return head;
    }
    soldier* rearrange_circle(soldier * head){
        soldier * temp;
        soldier * temphead = head;
        int counter = 0;
        int i;
        do{
            counter++;
            temphead = temphead->next;

        }
        while(temphead!=head);
        for(i=1;i<=counter;i++){
            temp = temphead->prev;
            temphead->prev = temphead->next;
            temphead->next = temp;
            temphead = temphead->prev;
        }
            temphead = temphead->next;
        return temphead;

    }
    void display(soldier * head){
        soldier * temp = head;
        do{
            printf("%d", temp->data);
            temp = temp->next;
        }
        while(temp!=head);
        printf("\n");
    }
    int kill(soldier * head, int n, int k){
        int i;
        soldier * temp = head;
        soldier * toBeFreed, *holdnext, *holdprev;
        while(n!=1){
            for(i=1; i<k; i++){
                temp = temp->next;
            }
            toBeFreed = temp;
            holdnext = temp->next;
            holdprev = temp->prev;
            holdnext->prev = holdprev;
            holdprev->next = holdnext; 
            temp = temp->next;
            free(toBeFreed);
            n--;
        }
        return temp->data;
        
    }