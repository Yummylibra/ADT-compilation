#ifndef AVL_H
#define AVL_H

#define NOTIN -1

typedef struct AVLNode {
    int key;
    int height;
    int size;
    struct AVLNode* left;
    struct AVLNode* right;
} Node;

typedef struct SplitResult {
    Node* left;
    Node* right;
} SplitResult;


Node* create(int key);
Node* Insert(Node* node, int key);
Node* search(Node* node, int key);
Node* del(Node* node, int key);

int get_rank(Node* node, int key);
Node* findRank(Node* node, int rank);

void pre_order(Node* node);
void in_order(Node* node);
void post_order(Node* node);

SplitResult split(Node* T, int k);
Node* join(Node* L, int key, Node* R);
Node* tree_union(Node* T1, Node* T2);

void delete_AVL(Node* node);

#endif
