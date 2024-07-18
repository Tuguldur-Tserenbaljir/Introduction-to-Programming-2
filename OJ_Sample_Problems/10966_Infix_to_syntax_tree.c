#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef FUNCTION_H
#define FUNCTION_H
#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;
BTNode* createNode(TokenSet c);
BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);
BTNode* EXPR(){
    BTNode* r_exp = FACTOR();
    if(pos == -1 || expr[pos] == '(') return r_exp;
    BTNode* head = makeNode(expr[pos]);
    pos--;
    head->right = r_exp;
    head->left = EXPR();
    return head;

}

BTNode* FACTOR(){
    char input = expr[pos];
    pos--;
    BTNode* in_bracket;
    if(input == ')'){
        in_bracket = EXPR();
        pos--;
        return in_bracket;
    } else return makeNode(input);
}
BTNode* createNode(TokenSet c){
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}
BTNode* makeNode(char c){
    BTNode* node;
    if(c == '|'){
        node = createNode(OP_OR);
    }
    else if(c == '&'){
        node = createNode(OP_AND);
    }
    else if(c == 'A'){
        node = createNode(ID_A);
    }
    else if(c == 'B'){
        node = createNode(ID_B);
    }
    else if(c == 'C'){
        node = createNode(ID_C);
    }
    else if(c == 'D'){
        node = createNode(ID_D);
    }
    return node;
}
#endif