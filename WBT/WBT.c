#include "WBT.h"


int get_height(Node* node){//如果node为null，那么返还0；否则返还node->height
	if(node == NULL){
        return 0;
    }
    else{
        return node->height;
    }
}

int maxNum(int a, int b){
    if (a >= b){
        return a;
    }
    else{
        return b;
    }
}

void update_height(Node* node){
    if (node != NULL) {
        node->height = maxNum(get_height(node->left), get_height(node->right)) + 1;
    }
}

int get_size(Node *node){
	if(node == NULL){
		return 0;
	}
	else{
		return node->size;
	}
}

int get_weight(Node *node){
	return get_size(node) + 1;
}

void update_size(Node* node){
	if(node != NULL){
		node->size = get_size(node->left) + get_size(node->right) + 1;
	}
}



//失衡节点调整

/*情况1：首个失衡结点v满足：
1.v的左子树高于右子树: weight(v->left) > 3*weight(v->right)
2.v的左子树x = v->left满足: weight(x->left)*2 > weight(x->right),x的左子树高于x的右子树
对v进行右旋single clockwise rotation*/
Node* left_left(Node* v){
	/*
	         v
	      /     \
         x     [v->R]
	   /   \
   [x->L]   [x->R]
	 /
	n
	
------------↓--------------

			 x
		   /   \
	 [x->L]      v
      /      /     \
     n	  [x->R]    [v->R]	  


	*/
	Node* x = v->left;//保存v的左孩子，x将是最终的父节点
	v->left = x->right;//将x的右孩子接到v的左子树
	x->right = v;//v作为x的右子树
 
	//update height&size
	update_height(v);
	update_size(v);

	update_height(x);
	update_size(x);
	return x;//return最终的父节点x
}
 
/*情况2：首个失衡结点v满足：
1.v的右子树高于左子树: weight(v->right) > 3*weight(v->left)
2.v的右子树x满足: get_weight(x->right)*2 > get_weight(x->left)，x的右子树高于左子树
对v进行左旋single counter-clockwise rotation*/
Node* right_right(Node* v){
	/*
	         v
	      /     \
      [v->L]       x
			     /   \
			[x->L]   [x->R]
				       \
				 		n
	
------------↓--------------

			  x
		 /         \
	    v          [x->R]
      /   \			 \
  [v->L] [x->L] 	  n


	*/

	Node* x = v->right;//保存v的右孩子，x作为最终父节点
	v->right = x->left;//x的左孩子接到v的右子树
	x->left = v;//v作为x的右子树
 
	//update height&size
	update_height(v);
	update_size(v);

	update_height(x);
	update_size(x);
	return x;
}
 
/*情况3：首个失衡结点v满足：
1.V的左子树高于右子树: weight(v->left) > 3*wiehgt(v->right)
2.v的左子树x满足: weight(x->right) >= 2*weight(x->left)，v的左节点的右子树高于左子树
对v先左旋，再右旋，double rotation: counter-clockwise rotation + clockwise rotation*/
Node* left_right(Node* v){
	/*
	          v
	      /      \
          x      [v->R]
	   /    \
   [x->L]     y
		   /     \
	   [y->L]    [y->R]  
	
	counter-clockwise x node, right_right(x)
------------↓--------------

	         v
	      /     \
         y     [v->R]
	   /   \
      x    [y->R]
	/   \  
[x->L]  [y->L]

 	clockwise v node
------------↓--------------
	            y
	      /            \
        x               v
	  /    \          /    \
 [x->L]    [y->L] [y->R]   [v->R]



	*/
	v->left = right_right(v->left);
	v = left_left(v);
	return v;
}
 
/*情况3：首个失衡结点v满足：
1.V的右子树高于左子树: weight(v->right) > 3*weight(v->left)
2.v的左子树x满足: weight(x->left) >= 2*weight(x->right)，v的右节点的左子树高于右子树
对v先左旋，再右旋，double rotation: counter-clockwise rotation + clockwise rotation*/
Node* right_left(Node* v){
	/*
	           v
	      /        \
        [v->L]       x
	   			  /     \
				 y       [x->R]
		      /     \
		 [y->L]     [y->R]
	
	clockwise x node, left_left(x)
------------↓--------------

	           v
	      /         \
        [v->L]        y
	   			  /      \
				[y->L]    x
				        /    \
				   [y->R]   [x->R]

 	counter-clockwise v node
------------↓--------------
	            y
	      /            \
        v               x
	  /    \          /    \
 [v->L]    [y->L] [y->R]   [x->R]



	*/
	v->right = left_left(v->right);
	v = right_right(v);
	return v;
}
 
Node* rebalance(Node* node){
    if (node == NULL) return node;

    // 检查左子树是否过高
    if (get_weight(node->left) > 3*get_weight(node->right)){
        if (get_weight(node->left->left)*2 > get_weight(node->left->right)) {
            node = left_left(node);
        } else {
            node = left_right(node);
        }
    }
    // 检查右子树是否过高
    else if (get_weight(node->right) > 3*get_weight(node->left)){
        if (get_weight(node->right->right)*2 > get_weight(node->right->left)) {
            node = right_right(node); 
        } else {
            node = right_left(node);
        }
    }
	update_height(node);
	update_size(node);
    return node;
}


/*创建一棵树，根结点为node*/
Node* create(int key){
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->height = 1;
	node->size = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}
 
/*往根节点为node的树中插入一个值key*/
//插入位置同BST的逻辑，大于向右找位置，小于向左找位置
Node* Insert(Node* node, int key){
	//如果为空，就创建并return一个有key值的node
	if (node == NULL){
		Node* node = create(key);
		return node;
	}
	//如果key值小于当前node的值，向node的左子树插入
	else if (key < node->key){
		//递归寻找插入位置
		node->left = Insert(node->left, key);
		node = rebalance(node);
	}
	//如果key值大于当前node的值，向右子树插入
	else if (key > node->key){
		node->right = Insert(node->right, key);
		node = rebalance(node);
	}
	else{//如果key值已经在树内，则不执行插入操作
		printf("cannot insert value that is already in Weight Balance tree.\n");
	}
	return node;
}
 
/*查找有key值的结点*/
Node* search(Node* node, int key){
	if (node == NULL || node->key == key){
		return node;
	}
	else if (key < node->key){
		search(node->left, key);
	}
	else{
		search(node->right, key);
	}
}

/*找到替换结点-右子树的最左边*/
Node* successor(Node* node){
	if (node == NULL){
		return NULL;
	}
	while (node->left){
		node = node->left;
	}
	return node;
}

/*删除结点*/
Node* del(Node* node, int key){
	//定位到要删除结点
	Node* target = search(node, key);
	if (target == NULL){//删除目标不在AVL树内||AVL树不存在
		printf("\ndelete failed, either the tree is empty or the target not founde within the tree\n");
		return node;
	}
	//删除结点在左子树
	if (key < node->key){
		//递归找到要删除结点
		node->left = del(node->left, key);
		node = rebalance(node);
	}
	//删除结点在右子树
	else if (key > node->key){
		node->right = del(node->right, key);
		node = rebalance(node);
	}
	//此时就是要删除结点
	else if (node->left != NULL && node->right != NULL){//既有左子树又有右子树，寻找大于node的最小值successor删除
		Node* succ_node = successor(node->right);//Node* succ_node = successor(node->left); 小于node的最大值successor删除
		node->key = succ_node->key;
		node->right = del(node->right, succ_node->key);//node->left = del(node->left, succ_node->key);小于node的最大值successor删除
		// free(succ_node);
		node = rebalance(node);
	}
	//只有一个孩子
	else{
		if(node->left != NULL){
			Node* temp = node;
            node = node->left;
			free(temp);
        }
        else if(node->right != NULL){
			Node* temp = node;
            node=node->right;
			free(temp);
        }
		else{//没有左也没有右孩子
			free(node);
			return NULL;
		}
	}       
	node = rebalance(node);
	return node;
}
 

int get_rank(Node* node, int key) {
  if(node == NULL){
    return NOTIN;
  }
  //key < current node, find rank in its left subtree
  if(key < node->key){
    return get_rank(node->left, key);
  }
  //key > current node, find rank in its right subtree
  else if(key > node->key){/*
         x
	   /   \
	  a     b

	  b-rank = a size + 1
  */
    int right_rank = get_rank(node->right, key);
    if (right_rank == NOTIN) {
        return NOTIN;
    }
	return 1 + get_size(node->left) + right_rank;
  }
  else{//find the key
  	return 1 + get_size(node->left);
  }

  return NOTIN;
}

Node* findRank(Node* node, int rank){
	if (node == NULL) {
        return NULL; // 如果节点为空，表示未找到
    }

    // 计算左子树的大小
    int leftSize = get_size(node->left);
    
    // 如果排名等于左子树大小加 1，说明当前节点就是我们要找的
    if (rank == leftSize + 1) {
        return node;
    } 
    // 如果排名小于等于左子树大小，递归地在左子树中查找
    else if (rank <= leftSize) {
        return findRank(node->left, rank);
    } 
    // 如果排名大于左子树大小加 1，递归地在右子树中查找
    else {
        return findRank(node->right, rank - leftSize - 1);
    }
}



void pre_order(Node* node)
{
	if (node){
		printf("[ %d ]  height:%d  size:%d\n", node->key, node->height,node->size);
		pre_order(node->left);
		pre_order(node->right);
	}
	
}

void in_order(Node* node)
{
	if (node){
		in_order(node->left);
		printf("[ %d ]  height:%d  size:%d\n", node->key, node->height,node->size);
		in_order(node->right);
	}
}

void post_order(Node* node)
{
	if (node){
		post_order(node->left);
        post_order(node->right);
        printf("[ %d ]  height:%d  size:%d\n", node->key, node->height,node->size);
	}
}


void delete_WBT(Node* node){
    if(node != NULL){
        delete_WBT(node->left);
        delete_WBT(node->right);
        free(node);
    }
}


Node* join(Node* L, int key, Node* R) {
    int L_weight = get_weight(L);
	int R_weight = get_weight(R);

	if(L_weight > 3*R_weight){
		L->right = join(L->right, key, R);
		L->right = rebalance(L->right);
		L = rebalance(L);
		return L;
		
	}
	else if(R_weight > 3*L_weight){
		R->left = join(L, key, R->left);
		R->left = rebalance(R->left);
		R = rebalance(R);
		return R;
	}

	else{
		Node* nodeK = create(key);
		nodeK->left = L;
		nodeK->right = R;
		nodeK = rebalance(nodeK);
		return nodeK;
	}
}


SplitResult split(Node* T, int k){
    SplitResult result;
	result.left = NULL;
	result.right = NULL;
    if (T == NULL) {
        return result;
    }
    if (k == T->key) {
        result.left = T->left;
        result.right = T->right;
		return result;
    } 
	else if (k < T->key) {
       result = split(T->left, k);
	   Node* new_right = join(result.right, T->key, T->right);
	   result.right = new_right;


    } 
	else if (k > T->key) {
		result = split(T->right, k);

		Node* new_left = join(T->left, T->key, result.left);
		result.left = new_left;


    }
	return result;
}

Node* tree_union(Node* T1, Node* T2){
    if (T1 == NULL) return T2;
    if (T2 == NULL) return T1;
    
    SplitResult splitResult = split(T1, T2->key);
    Node* leftUnion = tree_union(splitResult.left, T2->left);
    Node* rightUnion = tree_union(splitResult.right, T2->right);
    
    return join(leftUnion, T2->key, rightUnion);
}

