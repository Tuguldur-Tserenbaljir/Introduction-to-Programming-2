#include <stdlib.h>
#include <stdio.h>
typedef struct _Tree_Node{
    int number;
    struct _Tree_Node* parent;
    struct _Tree_Node* left;
    struct _Tree_Node* right;
}Tree_Node;

Tree_Node* tree_head;


void add_node(int n);
void showtree(Tree_Node* treenow);
Tree_Node *get_tree_leafs(int data);
void add_child(Tree_Node *temp, Tree_Node *something);
void add_node(int n){
    if(tree_head ==NULL) {
        tree_head = get_tree_leafs(n);
        return;
    }
    else{
        Tree_Node *temp = get_tree_leafs(n);
        Tree_Node *something = tree_head;
        add_child(temp,something);
    }
    
}
void showtree(Tree_Node* treenow){
    if(treenow == NULL)return;
    showtree(treenow->left);
    printf("%d ", treenow->number);
    showtree(treenow->right);
}
Tree_Node *get_tree_leafs(int data){
    Tree_Node *temp = (Tree_Node*)malloc(sizeof(Tree_Node));
    temp->number = data;
    temp->left= NULL;
    temp->right = NULL;
    return temp;
}

void add_child(Tree_Node *temp, Tree_Node *something){
    if(something->number <temp->number){
        if(something->right == NULL){
            something->right = temp;
        }else{
            add_child(temp,something->right);
        }
    } else if(temp->number < something->number){
        if(something->left == NULL){
            something->left = temp;
            return;
        } else{
            add_child(temp,something->left);
        }
    }
}