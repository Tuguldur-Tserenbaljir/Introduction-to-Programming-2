#include <stdio.h>
#include <stdlib.h>

typedef struct node_
{
    int data;                        //Data of the node
    struct node_ *nextptr;           //Address of the next node
} node;
node* Find_Node(int indx, node* head);
node* Create_Linked_list(int n);
node* Create_Node(int n);
void CUT_NODE(int a, int b, node **head);
void ADD_NODE(int a, int b,node **head);
void Print_List(node *head);

int main(){
    int n,m;
    scanf("%d %d", &n, &m);
    node* head = Create_Linked_list(n);
    int a,b;
    char s[5];
    for(int i = 0; i<m;i++){
        scanf("%s %d %d ", s, &a , &b );
        if( s[0] == 'A'){
            ADD_NODE(a,b, &head);
        } else if (s[0] == 'C'){
            CUT_NODE(a,b,&head);
        }
    }
    Print_List(head);
    return 0;
}
node* Create_Node(int val){
    node *temp = (node*)malloc(sizeof(node));
    temp->data = val;
    temp->nextptr = NULL;
    return temp;
}
node* Create_Linked_list(int n){
    node *head = NULL;
    node *tail;
    int data;
    for(int i = 0; i<n; i++){
        scanf("%d", &data);
        if(head == NULL){
            head = Create_Node(data);
            tail = head;
        } else{
            tail->nextptr = Create_Node(data);
            tail = tail->nextptr;
        }
    }
    return head;
}

void ADD_NODE(int a, int b, node **head){
    int indx = a;
    node *Tuudo = *head;
    node *temp = Create_Node(b);
    if (indx == 0){
        temp->nextptr = *head;
        *head = temp;
    } else{
        for(int i =0; i<indx-1; i++){
            Tuudo = Tuudo->nextptr;
        }
        node* node = Tuudo->nextptr;
        Tuudo->nextptr = temp;
        temp->nextptr = node;
    }
    return;
}
void CUT_NODE(int a, int b, node **head){
    if(a==0) return;
    node* old_head = *head;
    node* prev_a = Find_Node(a-1, *head);
    node* node_a = prev_a->nextptr;
    node* node_b = Find_Node(a+b-1, *head);
    node* after_b = node_b->nextptr;

    *head = node_a;
    prev_a->nextptr = after_b;
    node_b->nextptr = old_head;
    return;
}
node* Find_Node(int indx, node* head){
    node* temp = head;
    for(int i =0; i<indx; i++){
        temp = temp->nextptr;
    }
    return temp;
}

void Print_List(node *head){
    for(; head!=NULL; head = head->nextptr){
        printf("%d\n", head->data);
    }
    return;
}