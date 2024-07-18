#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    struct _Node *prev;
    struct _Node *next;
    int val;
    int tag;
} Node;

int n, k, q;
Node *head = NULL;
Node *tail;
void push(int x);
void pop();
void programming_tanoshi();
void KuoYangTeTe();

#endif

int cnt = 0;
Node *curtag;
Node *curMed;
Node *createNode(int val, Node *prev)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->prev = prev;
    node->next = NULL;
    return node;
}
void push(int x)
{
    if (head == NULL) {
        curMed = createNode(999, NULL);
        head = createNode(x, curMed);
        curMed->next = head;
        tail = head;
        curtag = head;
    }
    else {
        tail->next = createNode(x, tail);
        tail = tail->next;
    }
    if (++cnt % 2) curMed = curMed->next;
}

void pop()
{
    Node *prev = curMed->prev, *aft = curMed->next;
    prev->next = aft;
    aft->prev = prev;
    if (cnt % 2)
        curMed = curMed->prev;

    else
        curMed = curMed->next;
    cnt--;
}

void programming_tanoshi()
{
    // !!!!!!
    Node *node = curtag;
    while (node != NULL) {
        // what if store tag and store last tag?
        if (node->tag == 0) {
            node->tag = 1;
        }
        curtag = node;
        node = node->next;
    }
}

void KuoYangTeTe()
{
    Node *node = head;
    while (node != NULL) {
        if (node->tag) node->val %= k;
        node = node->next;
    }
}