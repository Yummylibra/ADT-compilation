/*
   AVL tree implementation.

   Author: A. Tafliovich
   Based heavily on materials developed by F. Estrada.
*/

#include "AVL_tree.h"

/*************************************************************************
 ** Suggested helper functions
 *************************************************************************/

/* Returns the height (number of nodes on the longest root-to-leaf path) of
 * the tree rooted at node 'node'. Returns 0 if 'node' is NULL.
 */
int height(AVL_Node* node){
  if(node == NULL){
    return 0;
  }
  else{
    return node->height;
  }
};

/* Updates the height of the tree rooted at node 'node' based on the heights
 * of its children. Note: this should be an O(1) operation.
 */
void update_height(AVL_Node* node){
  int left = node->left->height;
  int right = node->right->height;
  if(left > right){
    node->height = left + 1;
    return;
  }
  else{
    node->height = right + 1;
    return;
  }
};

/* Returns the balance factor (height of left subtree - height of right
 * subtree) of node 'node'. Returns 0 of node is NULL.
 */
int balance_factor(AVL_Node* node){
  if(node == NULL){
    return 0;
  }
  else{
    return node->left->height - node->right->height;
  }
};

/* Returns the result of performing the corresponding rotation in the AVL
 * tree rooted at 'node'.
 */
// single rotations: right/clockwise
AVL_Node* right_rotation(AVL_Node* node){
  AVL_Node* k = node->left;//preserve left child of node. k is the ultimate fater node.
  node->left = k->right;//get the right child of k to the left of node.
  k->right = node;//node is the right child of k.
  // update_height(k);
  // update_height(node);
  k->height = maxNum(height(k->left), height(k->right)) + 1;
  node->height = maxNum(height(node->left), height(node->right)) + 1;
  return k;

}
// single rotations: left/counter-clockwise
AVL_Node* left_rotation(AVL_Node* node){
  AVL_Node *k = node->right;
  node->right = k->left;
  k->left = node;
  // update_height(k);
  // update_height(node);
  k->height = maxNum(height(k->left), height(k->right)) + 1;
  node->height = maxNum(height(node->left), height(node->right)) + 1;
  return k;
}
// double rotation: right/clockwise then left/counter-clockwise
AVL_Node* right_left_rotation(AVL_Node* node){
  node->right = right_rotation(node->right);
	node = left_rotation(node);
	return node;
}
// double rotation: left/counter-clockwise then right/clockwise
AVL_Node* left_right_rotation(AVL_Node* node){
  node->left = left_rotation(node->right);
	node = right_rotation(node);
	return node;
}

/* Returns the successor node of 'node'. */
AVL_Node* successor(AVL_Node* node){
  if(node == NULL){
    return NULL;
  }
  while(node->left != NULL){
    node = node->left;
  }
  return node;
}

/* Creates and returns an AVL tree node with key 'key', value 'value', height
 * of 1, and left and right subtrees NULL.
 */
AVL_Node* create_node(int key, void* value){
  AVL_Node *newNode = (AVL_Node*)malloc(sizeof(AVL_Node));
  newNode->key = key;
  newNode->value = value;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 0;
  return newNode;
}

/*************************************************************************
 ** Provided functions
 *************************************************************************/
void print_tree_inorder_(AVL_Node* node, int offset) {
  if (node == NULL) return;
  print_tree_inorder_(node->right, offset + 1);
  printf("%*s %d [%d]\n", offset, "", node->key, node->height);
  print_tree_inorder_(node->left, offset + 1);
}

void print_tree_inorder(AVL_Node* node) {
  print_tree_inorder_(node, 0);
}

void delete_tree(AVL_Node* node) {
  if (node == NULL) return;
  delete_tree(node->left);
  delete_tree(node->right);
  free(node);
}

/*************************************************************************
 ** Required functions
 ** Must run in O(log n) where n is the number of nodes in a tree rooted
 **  at 'node'.
 *************************************************************************/

AVL_Node* search(AVL_Node* node, int key) {
  if(node == NULL){//return null if the AVL tree is empty
    return NULL;
  }
  if(node->key == key){//if we find the node with corresponding key, return it.
    return node;
  }
  if(key < node->key){//if the wnated key is smaller than the current key, go to node's left subtree to find it.
    search(node->left,key);
  }
  else{
    search(node->right, key);//else, go to node's right subtree to find it.
  }
  //return node;
}

int maxNum(int a, int b){
    if (a >= b){
        return a;
    }
    else{
        return b;
    }
}

AVL_Node* insert(AVL_Node* node, int key, void* value) {
  if(node == NULL){//create a new AVL tree if the tree is empty
    AVL_Node *new = create_node(key, value);
    node = new;
  }
  if(search(node, key) == NULL){//only insert if the value is new

    if(key < node->key){//insert on left subtree if key< node.key
      
      node->left = insert(node->left, key, value);

      if(height(node->left) - height(node->right) == 2){//rebalance left subtree
        if(key < node->left->key){
          node = right_rotation(node);
        }
        else{
          node = left_right_rotation(node);
        }
      }

    }

    else if(key > node->key){//insert on right subtree if key > node.key

      node->right = insert(node->right, key,value);

      if(height(node->right) - height(node->left) == 2){//rebalance right subtree
        if(key > node->right->key){
          node = left_rotation(node);
        }
        else{
          node = right_left_rotation(node);
        }
      }
    }

    
  }
  // update_height(node);
  node->height = maxNum(height(node->left), height(node->right)) + 1;
  return node;
}

AVL_Node* delete(AVL_Node* node, int key) {
  AVL_Node *target = search(node,key);
  if(target == NULL || node == NULL){
    return NULL;
  }
  if(key < node->key){
    node->left = delete(node->left, key);
    if(height(node->right) - height(node->left) == 2){
      if(key < node->right->key){
        node = right_left_rotation(node);
      }
      else{
        node = left_rotation(node);
      }
    }
  }

  else if(key > node->key){
    node->right = delete(node->right, key);
    if(height(node->left) - height(node->right) == 2){
      if(key < node->left->key){
        node = right_rotation(node);
      }
      else{
        node = left_right_rotation(node);
      }
    }
  }
  //below this line, we preform the delete of 3 different type
  else if(node->left != NULL && node->right != NULL){//node has 2 children
    AVL_Node *scr = successor(node->right);
    node->key = scr->key;
    node->value = scr->value;
    node->right = delete(node->right, scr->key);
  }
  else{
    if(node->left != NULL){
      node = node->left;
    }
    else{
      node = node->right;
    }
  }
  if(node != NULL){
    // update_height(node);
    node->height = maxNum(height(node->left), height(node->right)) + 1;
  }
  return node;

}
