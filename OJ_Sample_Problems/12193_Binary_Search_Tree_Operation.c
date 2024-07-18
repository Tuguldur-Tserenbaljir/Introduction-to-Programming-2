#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    int data;
    int depth;
    struct node* right;
    struct node* left;
}Node;
typedef struct list{
    int sum_level;
    int num_level;
} Level;


Node* createNode(int data); //donze


void makeTree(int num,int depth); //donze
void printInOrder(Node* head); //donze
void freeTree(Node* head); //donze
void addChild(Node* move, Node* num, int depth); //donze
void update_level(int depth, int num); //donze

Node* head;
Level* levels;
int maxLevel;

int main()
{
    int n, num;
    scanf("%d", &n);
    levels = (Level*)calloc(n+2, sizeof(Level));
    maxLevel = 0;

    while(n--){
        scanf("%d", &num);
        makeTree(num, 1);
    }

    int q;
    char op[25];
    scanf("%d", &q);
    while(q--){
        scanf("%s", op);
        if(op[0]=='A'){
            int lvl;
            scanf("%d", &lvl);
            if(lvl > maxLevel || lvl<=0) printf("0\n");
            else printf("%.3f\n", ((double)levels[lvl].sum_level)/((double)levels[lvl].num_level));
        }
        else if(op[0]=='S'){
            int lvl;
            scanf("%d", &lvl);
            if(lvl > maxLevel || lvl<=0) printf("0\n");
            else printf("%d\n", levels[lvl].sum_level);
        }
        else if(op[0]=='G'){
            printf("%d\n", maxLevel);
        }
        else if(op[0]=='P'){
            if(head!=NULL) printInOrder(head);
            else printf("NULL");
            printf("\n");
        }
    }

    return 0;
}

void update_level(int depth, int num){
    Level check = levels[depth];
    if(maxLevel < depth) maxLevel = depth;
    levels[depth].sum_level += num;
    levels[depth].num_level += 1;
    return;
}


void addChild(Node* move, Node* num, int depth){
    if(move->data > num->data){
        if(move->left == NULL){
            move->left = num;
            update_level(depth+1,num->data);
            move->left->depth = depth;
            return;
    } else{
            addChild(move->left,num,depth+1);
        }

    }
    else if (move->data < num->data){
        if(move->right == NULL){
            move->right = num;
            update_level(depth+1, num->data);
            move->right->depth = depth;
            return;
        } else{
            addChild(move->right,num,depth+1);
        }
    }

}


Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->right = NULL;
    node->left = NULL;
    return node;
}


void makeTree(int num,int depth){
    Node *move = head;
    Node *node = createNode(num);

    if(head == NULL){
        head = node;
        node->depth = 1;
        levels[1].num_level+=1;
        levels[1].sum_level+=num;
        update_level(depth, node->data);
        return;
    } else{
        addChild(move,node,depth);
    }
}


void printInOrder(Node* head){
    if(head == NULL)return;
    printInOrder(head->left);
    printf("%d ", head->data);
    printInOrder(head->right);
}


void freeTree(Node* head){
    if (head != NULL){
        freeTree(head->right);
        freeTree(head->left);
        free(head);
    }
}