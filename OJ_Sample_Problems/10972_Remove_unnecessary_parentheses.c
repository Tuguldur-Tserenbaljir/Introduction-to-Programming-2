#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    char data;
    struct node* right;
    struct node* left;
}Node;
char infx[300];
int pos;

Node* expression();
Node* factor();
Node* createNode(char c);
void printInfix(Node *root);
void freeTree(Node *root);
int main(){
    scanf("%s", infx);
    int len = strlen(infx);
    pos = len - 1;
    Node *root = expression();
    printInfix(root);
    freeTree(root);
}
void printInfix(Node *root){
    if(root == NULL)return;
    printInfix(root->left);
    printf("%c", root->data);
    if(root->right != NULL){
         if(root->right->data == '&' || root->right->data == '|'){
             printf("(");
             printInfix(root->right);
             printf(")");
    }
    else printInfix(root->right);
    }
}
Node* expression(){
    Node *right = factor();
    if(pos == -1 || infx[pos] == '(')return right;
    Node *head = createNode(infx[pos]);
    pos--;
    head->right = right;
    head->left = expression();
    return head;
}
Node* factor(){
    char now = infx[pos];
    pos--;
    Node *in_bracket;
    if(now == ')'){
        in_bracket = expression();
        pos--;
        return in_bracket;
    } else return createNode(now);

}
Node* createNode(char c){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}
void freeTree(Node *root){
    if(root !=NULL){
        freeTree(root->right);
        freeTree(root->left);
        free(root);
    }
}