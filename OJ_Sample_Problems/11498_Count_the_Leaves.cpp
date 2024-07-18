#include<iostream>

#include <iostream>
#include <string>
#include<cctype>
#include<string>
#include<sstream>
/*
struct node{
    int data;
    struct node* left;
    struct node*right;

};
struct node* newNode(int data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}
void printTree(struct node *node){
    if(node == NULL)return;
    cout<<node;
    if(node->left != nullptr)cout<<node->left;
    if(node->left != nullptr)cout<<node->right;
    cout<<node->data;

}*/

using namespace std;
int main(){
    int N;
    while(cin>>N){
    if(N == 0)return 0;
    int a,b,root;
    int count = 0;
    int parent[1005]= {0};
    int leaf[1005] = {0};

    while(N--){
        cin>>a>>b; //(1,2)
        parent[a] = 1;
        leaf[b] = 1;
        /*struct node *root = newNode(a);
        if(root->left == nullptr)root->left = newNode(b);
        if(root->right == nullptr)root->right = newNode(b);
        printTree(root);*/
    }
    cin>>root;//for last dummy, root giver
    parent[root]=1;
    for(int i =0;i<1005;i++){
        if(leaf[i]==1 && parent[i]==0){
            count++;
        }
    }
    cout<<count<<endl;
    }

}