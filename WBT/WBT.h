#ifndef __WBT_header
#define __WBT_header

#include <stdio.h>
#include <stdlib.h>

#define NOTIN -1

typedef struct WBTNode {
    int key;
    int size;
    int height;
    struct WBTNode* left;
    struct WBTNode* right;
} Node;

typedef struct {
    Node* left;
    Node* right;
} SplitResult;


Node* create(int key);
Node* Insert(Node* node, int key);
Node* search(Node* node, int key);
Node* del(Node* node, int key);


int get_rank(Node* node, int key);
Node* findRank(Node* node, int rank);


Node* join(Node* L, int key, Node* R);
SplitResult split(Node* T, int k);
Node* tree_union(Node* T1, Node* T2);

void pre_order(Node* node);
void in_order(Node* node);
void post_order(Node* node);

void delete_WBT(Node* node);

#endif
