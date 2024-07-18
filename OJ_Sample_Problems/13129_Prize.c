#include <stdio.h>
#include <stdlib.h>
typedef struct _Node{
    int number;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node* head;
Node* createList(int n);
void solveJosephus(int n, int k);

Node* createList(int n){
    Node *temp = (Node*)malloc(sizeof(Node));
    Node *insert;
    head = temp;
    temp->next = NULL;
    temp->prev = NULL;
    temp->number = 1;
    for(int i=0;i<n-1;i++){
        insert=(Node*)malloc(sizeof(Node));
        temp->next= insert;
        insert->prev= temp;
        insert->number = i+2;
        temp = insert;
    }
    head->prev = insert;
    insert->next= head;
    return head;
}
void solveJosephus(int n, int k){
    int lucky_number,people;
    people = n;
    Node *store;
    for(int i =0;i<k;i++){
        scanf("%d", &lucky_number);
       
        if (i == 0 && lucky_number%2 ==0){
            head = head->next;
        }
        if(lucky_number%2==0){
            if (lucky_number >people) {
                lucky_number = lucky_number%people;
                if(lucky_number == 0){
                    lucky_number = people;
                }
            }
            for (int i =0; i<lucky_number;i++){
                head = head->prev;
            }
            head->prev->next = head->next;
            head->next->prev = head->prev;
            store = head->next;
            printf("%d\n", head->number);
            free(head);
            people--;
            head = store;
        } else{
            if (lucky_number >people) {
                lucky_number = lucky_number%people;
                if(lucky_number == 0){
                    lucky_number = people;
                }
            }
            for(int i =1;i<lucky_number;i++){
                head= head->next;
            }
            head->prev->next = head->next;
            head->next->prev = head->prev;
            store = head->next;
            printf("%d\n", head->number);
            free(head);
            people--;
            head = store;
        }
    }
}