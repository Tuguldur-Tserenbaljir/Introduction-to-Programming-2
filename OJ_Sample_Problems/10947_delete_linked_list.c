#include <stdlib.h>
#include <stdio.h>

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

void deleteNode(Node ** nd, int data);
Node* createList();

void printList(Node *head){
    Node *temp;
    for(temp = head; temp!=NULL; temp=temp->next) {
        printf("%d ", temp->data);
    }
}

void freeList(Node *head){
    Node *temp;
    for(temp=head; temp!=NULL; temp=head){
        head = head->next;
        free(temp);
    }
}

void deleteNode(Node **nd, int data){
    Node *now = *nd, *last = NULL;
    while(now && --data) last = now, now = now->next;
    if(data==0 && now){
        if(last) last->next = now->next;                        
        else *nd = (*nd)->next;                                 
        free(now);
    }
}

Node* createList(){
    Node *head = NULL, *now;
    int a;
    while(scanf("%d",&a) && a!=-1){
        if(head) now = now->next = (Node*)malloc(sizeof(Node));	
        else now = head = (Node*)malloc(sizeof(Node));           
        now->data = a, now->next = NULL;
    }
    return head;
}

int main()
{
    Node *head;
    int data;

    head = createList();

    while(1){
        scanf("%d", &data);
        if(data>-1){
            deleteNode(&head,data);
        }else break;

    }

    printList(head);
    freeList(head);
    return 0;
}