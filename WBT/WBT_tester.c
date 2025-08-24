#include <stdlib.h>
#include <string.h>

#include "WBT.h"

//compile: gcc -o WBT_tester WBT.c WBT_tester.c

int main() {
    Node* root = NULL;
    int choice, number;

    while (1) {
        printf("\n=== Weight Balanced Tree Tester ===\n");
        printf("0 - Insert a node\n");
        printf("1 - Search a node\n");
        printf("2 - Delete a node\n");
        printf("3 - Print in-order\n");
        printf("4 - Print pre-order\n");
        printf("5 - Print post-order\n");
        printf("6 - Get rank of a key\n");
        printf("7 - Find node by rank\n");
        printf("8 - Delete tree & Exit\n");
        printf("9 - Split a tree by key\n");
        printf("10 - Union of two example trees\n");
        printf("11 - Join example L, key, R\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 0) {  // Insert
            printf("Enter value to insert: ");
            scanf("%d", &number);
            root = Insert(root, number);
            printf("Inserted %d\n", number);
        } else if (choice == 1) {  // Search
            printf("Enter value to search: ");
            scanf("%d", &number);
            Node* t = search(root, number);
            if (t) printf("Found key=%d, size=%d, height=%d\n", t->key, t->size, t->height);
            else printf("Key not found.\n");
        } else if (choice == 2) {  // Delete
            printf("Enter value to delete: ");
            scanf("%d", &number);
            root = del(root, number);
            printf("Deleted %d if it existed\n", number);
        } else if (choice == 3) {  // In-order
            printf("In-order traversal:\n");
            in_order(root);
        } else if (choice == 4) {  // Pre-order
            printf("Pre-order traversal:\n");
            pre_order(root);
        } else if (choice == 5) {  // Post-order
            printf("Post-order traversal:\n");
            post_order(root);
        } else if (choice == 6) {  // Get rank
            printf("Enter key: ");
            scanf("%d", &number);
            int r = get_rank(root, number);
            if (r == NOTIN) printf("Key %d not in tree.\n", number);
            else printf("Rank of key %d is %d\n", number, r);
        } else if (choice == 7) {  // Find by rank
            printf("Enter rank: ");
            scanf("%d", &number);
            Node* t = findRank(root, number);
            if (t) printf("Node at rank %d: key=%d\n", number, t->key);
            else printf("Invalid rank.\n");
        } else if (choice == 8) {  // Delete tree and exit
            delete_WBT(root);
            printf("Tree deleted. Exit.\n");
            break;
        } else if (choice == 9) {  // Split
            printf("Enter split key: ");
            scanf("%d", &number);
            SplitResult res = split(root, number);
            printf("Left tree (in-order):\n");
            in_order(res.left);
            printf("Right tree (in-order):\n");
            in_order(res.right);
            delete_WBT(res.left);
            delete_WBT(res.right);
        } else if (choice == 10) {  // Union
            int a[5] = {10,20,30,40,50};
            int b[5] = {15,25,35,45,55};
            Node* t1 = NULL;
            Node* t2 = NULL;
            for (int i=0; i<5; i++) {
                t1 = Insert(t1, a[i]);
                t2 = Insert(t2, b[i]);
            }
            Node* tu = tree_union(t1, t2);
            printf("Union tree (in-order):\n");
            in_order(tu);
            delete_WBT(t1);
            delete_WBT(t2);
            delete_WBT(tu);
        } else if (choice == 11) {  // Join
            Node* L = NULL;
            Node* R = NULL;
            for (int i=1; i<=3; i++) L = Insert(L, i);
            for (int i=7; i<=9; i++) R = Insert(R, i);
            Node* joined = join(L, 5, R);
            printf("Joined tree (in-order):\n");
            in_order(joined);
            delete_WBT(joined); // L和R也包含其中，直接释放joined即可
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
