#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    char data;
    struct node* right;
    struct node* left;
}Node;
int array[5];

Node* createNode(char c);
Node* expression();
int solve(Node *root);


Node* createNode(char c){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = c;
    node->right = NULL;
    node->left = NULL;
    return node;
}
int solve(Node *root){
    int num;
    if (root->data == '&')num = solve(root->left) *solve(root->right);
    else if(root->data == '|')num = solve(root->left) + solve(root->right);
    else num = array[(root->data) - 'A'];
    if(num>1) num =1;
    return num;
}
Node* expression(){
    char c;
    scanf("%c", &c);
    Node* node = createNode(c);
    if(node->left == NULL && (node->data == '&' || node->data == '|'))node->left = expression();
    if(node->right == NULL && (node->data == '&' || node->data == '|'))node->right = expression();
    return node;
}
int main(){
    Node* root;
    root = expression();
    for(int i = 1;i<16;i++){
        int num = solve(root);
        printf("%d %d %d %d %d\n",array[0],array[1],array[2],array[3], num);
        array[3]++;
        if(array[3]>1){
            array[3] = 0;
            array[2]++;
        }
        if(array[2]>1){
            array[2] = 0;
            array[1]++;
        }
        if(array[1]>1){
            array[1] = 0;
            array[0]++;
        }
    }
    int num = solve(root);
    printf("%d %d %d %d %d\n",array[0],array[1],array[2],array[3], num);
    return 0;
}