#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct node *next;
}Node;
int dummy[5005];
int Array[5005] = {};
int find_min(int n);
void delete_value(Node **ptr, int value);
void add_Node(Node **ptr,int n);
// not Node *add_Node(Node **ptr,int n);
Node *Create_Linked_list(int n);

int main(){
    int n;
    int value,value2;
    scanf("%d", &n);
    Node **ptr = (Node**)calloc(n+5,sizeof(Node));

    for(int i =1; i<n; i++){
        scanf("%d %d", &value, &value2);
        add_Node(&ptr[value],value2);
        add_Node(&ptr[value2],value);
        dummy[value]++, dummy[value2]++;
        Array[value2] = Array[value] = 1;
    }
    //for(int i=1; i<n-2; i++)
    for (int i = 1; i <=n-2; i++) {
        int absolute = find_min(n);
        // delete_value(absolute,*ptr);
        delete_value(ptr, absolute);
        Array[absolute] = 0;
    }
    printf("\n");
    return 0;
}

Node *Create_Linked_list(int n){
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = n;
    node->next = NULL;
    return node;
}

//Node *add_Node(Node **ptr,int n)
void add_Node(Node **ptr,int n){
    if(*ptr == NULL){
        *ptr = Create_Linked_list(n);
        //not yet return
        return;
    }
    Node* node= Create_Linked_list(n);
    node->next = *ptr;
    *ptr = node;
    //not yet return;
    return;
}

int find_min(int n){
    int min = 5005;
    for(int i = 1; i<=n; i++){
        if(dummy[i] == 1){
            if(i < min){
                min = i;
            }
        }
    }
    dummy[min] = 0;
    return min;
}

void delete_value(Node **ptr, int min){
    Node *leaf = ptr[min];
    dummy[leaf->data]--;

    while(1){
        if(Array[leaf->data] == 1){
            printf("%d ", leaf->data);
            break;
        }
        //not leaf = leaf->data;
        leaf = leaf->next;
    }
    //not yet return
    return;
}