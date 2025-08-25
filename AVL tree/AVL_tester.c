#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

static int read_int(const char *prompt) {
    int x;
    int rc;
    for (;;) {
        if (prompt) printf("%s", prompt);
        rc = scanf("%d", &x);
        if (rc == 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            return x;
        }
        printf("Invalid input. Please enter an integer.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
}

static void pause_enter(void) {
    printf("\nPress Enter to continue...");
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);

    Node *root = NULL;

    for (;;) {
        printf("\nPlease select from the following options:\n");
        printf("0 - Insert a new node\n");
        printf("1 - Search for a node\n");
        printf("2 - Delete a node\n");
        printf("3 - Print nodes in in-order\n");
        printf("4 - Print nodes in pre-order\n");
        printf("5 - Print nodes in post-order\n");
        printf("6 - Show the rank of a given node\n");
        printf("7 - Show the node of a given rank\n");
        printf("8 - delete AVL and exit\n");
        printf("9 - split an avl tree (demo)\n");
        printf("10 - union 2 avl trees (demo)\n");
        printf("11 - join L tree, k node and R tree (demo)\n");

        int choice = read_int("Your choice: ");

        switch (choice) {
            case 0: {
                int number = read_int("enter the number: ");
                root = Insert(root, number);
                pause_enter();
                break;
            }
            case 1: {
                int number = read_int("enter the search-targeted number: ");
                Node *t = search(root, number);
                if (t) {
                    printf("Node found, address:%p\n", (void*)t);
                }
                else {
                    printf("Target not found\n");
                }
                pause_enter();
                break;
            }
            case 2: {
                int number = read_int("enter the delete-targeted number: ");
                root = del(root, number);
                pause_enter();
                break;
            }
            case 3:
                printf("in-order printing...\n");
                in_order(root);
                pause_enter();
                break;
            case 4:
                printf("pre-order printing...\n");
                pre_order(root);
                pause_enter();
                break;
            case 5:
                printf("post-order printing...\n");
                post_order(root);
                pause_enter();
                break;
            case 6: {
                int number = read_int("enter the target value: ");
                int rank = get_rank(root, number);
                if (rank == NOTIN) {
                    printf("This value is not in the tree!\n");
                }
                else {
                    printf("the rank of the value is: %d\n", rank);   
                }
                pause_enter();
                break;
            }
            case 7: {
                int number = read_int("enter the target rank: ");
                Node* t = findRank(root, number);
                if (!t) {
                    printf("Invalid rank, node not found\n");
                }
                else {
                    printf("Node found, address:%p, key:%d, height:%d\n", (void*)t, t->key, t->height);
                }
                pause_enter();
                break;
            }
            case 8:
                delete_AVL(root);
                printf("System terminated.\n");
                return 0;

            case 9: { // split demo
                int array[12] = {60,20,80,10,30,70,115,35,65,75,100,120};
                int x = 78;
                Node* Tsplit = NULL;
                for (int i = 0; i < 12; i++) Tsplit = Insert(Tsplit, array[i]);
                printf("The tree to be split at key = %d in pre_order is:\n", x);
                pre_order(Tsplit);

                SplitResult r = split(Tsplit, x);
                printf("\nResult tree 1:\n"); pre_order(r.left);
                printf("\nResult tree 2:\n"); pre_order(r.right);

                delete_AVL(r.left);
                delete_AVL(r.right);
                delete_AVL(Tsplit);
                pause_enter();
                break;
            }
            case 10: { // union demo
                int treeA[6] = {11,10,25,9,20,28};
                int treeB[6] = {18,14,22,13,16,31};
                Node *t1 = NULL, *t2 = NULL;
                for (int i = 0; i < 6; i++) {
                    t1 = Insert(t1, treeA[i]);
                    t2 = Insert(t2, treeB[i]);
                }
                printf("\nTree1 in pre_order is:\n"); pre_order(t1);
                printf("\nTree2 in pre_order is:\n"); pre_order(t2);

                Node* tu = tree_union(t1, t2);
                printf("\nUnion tree in pre_order is:\n"); pre_order(tu);

                delete_AVL(t1);
                delete_AVL(t2);
                delete_AVL(tu);
                pause_enter();
                break;
            }
            case 11: { // join demo
                int treeL[8] = {2,0,4,1,3,6,5,7};
                int treeR[2] = {10,9};
                Node *L = NULL, *R = NULL;
                for (int i = 0; i < 8; i++) {
                    L = Insert(L, treeL[i]);
                }
                for (int i = 0; i < 2; i++) {
                    R = Insert(R, treeR[i]);
                }

                printf("\nTree L (pre):\n"); pre_order(L);
                printf("\nThe k is: %d\n", 8);
                printf("\nTree R (pre):\n"); pre_order(R);

                Node* J = join(L, 8, R);
                printf("\nJoined (pre):\n"); pre_order(J);

                delete_AVL(J);
                delete_AVL(L);
                delete_AVL(R);
                pause_enter();
                break;
            }
            default:
                printf("Please enter a valid selection number.\n");
                pause_enter();
                break;
        }
    }
}
