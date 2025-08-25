

#include<stdio.h>
#include<stdlib.h>
#include"NoteSynth.c"

typedef struct BST_Node_Struct
{
    double key;
    double freq;
    int bar;
    double index;

    struct BST_Node_Struct *right;
    struct BST_Node_Struct *left;
  
} BST_Node;

BST_Node *newBST_Node(double freq, int bar, double index)
{

    BST_Node *new_BST_Node = NULL;
    new_BST_Node = (BST_Node *)calloc(1, sizeof(BST_Node));
    new_BST_Node->bar = bar;
    new_BST_Node->index = index;
    new_BST_Node->freq = freq;
    double key;
    key = (10.0*bar)+index;
    new_BST_Node->key = key;
    new_BST_Node->right = NULL;
    new_BST_Node->left = NULL;
    return new_BST_Node;

        
    return NULL;
}

BST_Node *BST_insert(BST_Node *root, BST_Node *new_node)
{

    if(root == new_node){
        printf("Duplicate node requested (bar:index)=%d,%lf, it was ignored\n",new_node->bar, new_node->index);
    }
    if(root == NULL){
        return new_node;
    }
    if (new_node->key <= root->key){
        root->left = BST_insert(root->left,new_node);
    }
    else{
        root->right = BST_insert(root->right,new_node);
    }
    return root;
    
    //return NULL;
}

BST_Node *BST_search(BST_Node *root, int bar, double index)
{

    double key;
    key = (10.0*bar)+index;

    if(root == NULL){
        return NULL;
    }
    if(root->key == key){
        return root;
    }
    if(key <= root->key){
        return BST_search(root->left, bar, index);
    }
    else{
        return BST_search(root->right, bar, index);
    }
    //return NULL;
}

BST_Node *find_successor(BST_Node *right_child_node)
{

    BST_Node *p = NULL;
    p = right_child_node;
    while(p->left != NULL){
        p = p->left;
    }
    return p;
    
}

BST_Node *BST_delete(BST_Node *root, int bar, double index)
{

    BST_Node *tmp;

    double key;
    key = (10.0*bar) + index;

    if(root == NULL){//target does not exist in the BST
        return NULL;
    }

    if(root->key == key){//found the to-be-deleted target
        if(root->left == NULL && root->right == NULL){//target is leaf, simply delete it
            free(root);
            return  NULL;
        }
        else if(root->right == NULL){//target only has left node
            tmp = root->left;
            free(root);
            return tmp;
        }
        else if(root->left == NULL){//target only has right node
            tmp = root->right;
            free(root);
            return tmp;
        }
        else{//target has both left&right children

            tmp = find_successor(root->right);
            root->bar = tmp->bar;
            root->freq = tmp->freq;
            root->index = tmp->index;
            root->key = tmp->key;
            root->right = BST_delete(root->right, tmp->bar,tmp->index);
            return root;
            
        }
        return root;
    }

    else if(key < root->key){//target is in the left subtree
        root->left = BST_delete(root->left, bar, index);
        return root;
    }
    else{//target is in the right subtree
        root->right = BST_delete(root->right, bar, index);
        return root;
    }
}

void BST_makePlayList(BST_Node *root)
{
    /*
     * This function does an in-order traversal of the BST to
     * generate an ordered list of notes to be played. Each
     * note is added to a linked-list and the 
     * play list is then playable using the code in NoteSynth.c
     */
    
   
    // if(root != NULL){
    //     BST_makePlayList(root->left);
    //     playlist_head=playlist_insert(playlist_head, root->freq, root->bar, root->index);
    //     BST_makePlayList(root->right);

    if (root==NULL){
        return;
    }
    BST_makePlayList(root->left);
    playlist_head=playlist_insert(playlist_head, root->freq, root->bar, root->index);
    BST_makePlayList(root->right);
    

}

void BST_inOrder(BST_Node *root, int depth)
{
    /*
     * This function performs an in-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     * 
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     * 
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */
    

    if(root != NULL){
        BST_inOrder(root->left, depth + 1);
        printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
        BST_inOrder(root->right, depth + 1);
    }
} 

void BST_preOrder(BST_Node *root, int depth)
{
    /*
     * This function performs an pre-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     * 
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement
     * 
     * The depth value is increased by 1 for each recursive call
     */
    

    if(root != NULL){
        printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
        BST_preOrder(root->left, depth + 1);
        BST_preOrder(root->right, depth + 1);
    }
}

void BST_postOrder(BST_Node *root,int depth)
{
    /*
     * This function performs an post-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     * 
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement
     * 
     * The depth value is increased by 1 for each recursive call
     */
    

    if(root != NULL){
        BST_postOrder(root->left, depth + 1);
        BST_postOrder(root->right, depth + 1);
        printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
    }
} 


void delete_BST(BST_Node *root)
{
    /*
     * This function deletes the BST and frees all memory used for
     * nodes in it. 
     */
    
    if(root != NULL){
        delete_BST(root->left);
        delete_BST(root->right);
        free(root);
        root = NULL;
    }
}

void reverse_BST(BST_Node *root){
    BST_Node *tmp;
    if(root != NULL){
        tmp = root->right;
        root->right = root->left;
        root->left = tmp;
        
        reverse_BST(root->left);
        reverse_BST(root->right);
    }
}

void data_operation(BST_Node *root, int bar){
    if(root != NULL){
        data_operation(root->left, bar);
        data_operation(root->right, bar);
        root->bar = bar - root->bar;
        root->index = 1 - root->index;
    }
}


BST_Node *reverseSong(BST_Node *root)
{
    /*
     * This function will reverse the song currently stored in our
     * tree - that means the song will play *backwards*.
     * 
     * For instance, if the song contains notes
     *   
     *  A B C D E F G     in that order
     *  
     *  after reversing it should play
     * 
     *  G F E D C B A     in that order
     */
    

    BST_Node *tmp;

    int min;
    int max;
    tmp = root;
    while(tmp->left != NULL){
        tmp = tmp->left;
    }
    min = tmp->bar;

    tmp = root;
    while(tmp->right != NULL){
        tmp = tmp->right;
    }
    max = tmp->bar;

    reverse_BST(root);
    data_operation(root, min + max);
    return root;
}

BST_Node *harmonize_insert(BST_Node *root, BST_Node *new_node){
    if(root != new_node){
        if(root == NULL){
            return new_node;
        }
        
        if (new_node->key <= root->key){
            root->left = BST_insert(root->left,new_node);
        }
        else{
            root->right = BST_insert(root->right,new_node);
        }
        return root;
    }


}

BST_Node *BST_harmonize(BST_Node *root, int semitones, double time_shift)
{
    /*
     * This function traverses the BST, and for each existing
     * note, inserts a new, modified note (i.e. it will add sounds
     * to an already existing song, based on the notes it already has)
     * 
     * The new note has the following properties:
     * - The frequency is shifted by the specified number of semitones
     *   (A semitone is the difference between one note and the
     *    immediately next one in the musical scale - ot what is the
     *    same, the difference in pitch between a white key and the
     *    black key immediately next to it in a piano)
     * - It plays in the same *bar* as the original note
     * - But its *index* is shifted by the specified time_shift
     *   (this value is between 0 and 1, but you have to check 
     *    that the final index remains between 0 and 1)
     * 
     * Both the 'semitones' and 'time_shift' parameter can be
     * positive or negative. A typical value for semitones
     * could be 4 or 7, corresponding to musical 3rds or
     * musical 5ths - this should produce some interesting
     * harmony! but you can play with this function and try
     * various things for fun.
     * 
     * For instance, suppose there exist a note in  the BST with
     * 
     * freq=440.0, at bar=10, index=.25
     * 
     * Now suppose the user specified
     * 
     * semitones=4
     * time_shift=.1
     * 
     * Then the program shall go to the note_freq[] array, find the index
     * of the entry for frequency 440.0 (let's say it's 
     * j), then go to note_freq[j+4] to find the frequency
     * of the note needs to be added.

     * Expected result: The BST will have about twice as many notes
     *   as before, and the new notes are shifted in pitch and 
     *   in time as specified by the parameters. 
     */

    if(root != NULL){
        BST_harmonize(root->left, semitones, time_shift);
        BST_harmonize(root->right, semitones, time_shift);
        BST_Node *newnode = NULL;
        double newindex;
        newindex = root->index +time_shift;
        if((newindex >=0) && (newindex < 1)){

            double newfreq;
            int freq_index;
            freq_index = -1;
            for(int i = 0; i <100; i++){
                if(note_freq[i] == root->freq){
                    freq_index = i;
                    break;
                }
            }
            
            if(freq_index == -1){
                return NULL;
            }

            if((freq_index + semitones >= 0)&&(freq_index + semitones <= 99)){
                newfreq = note_freq[freq_index + semitones];
                newnode = newBST_Node(newfreq, root->bar, newindex);
                root = harmonize_insert(root, newnode);
            }
        }
    }
    return root;
    return NULL;

}
