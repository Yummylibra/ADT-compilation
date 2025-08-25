
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 1024
#ifndef __testing
#define MAT_SIZE 10	// Use the small graph
//#define MAT_SIZE 400	// Use full-size graph
#endif


double AdjMat[MAT_SIZE][MAT_SIZE];
char ingredients[MAT_SIZE][MAX_STR_LEN];


typedef struct intNode_struct
{
    int  x;
    struct intNode_struct *next;
} intNode;

intNode *insertInt(intNode *h, int x)
{
  // Inserts the int 'x' into the linked list 
  // whose head is at the address in 'h'
  
  intNode *newNode;
  
  newNode=(intNode *)calloc(1,sizeof(intNode));
  newNode->x=x;
  newNode->next=NULL;
  
  if (h!=NULL)
    newNode->next=h;
  
  return newNode;
}

int searchInt(intNode *h, int x)
{
  // Search the linked list for the value 'x', if
  // found, it returns 1, else it returns 0
  while (h!=NULL)
  {
    if (h->x==x) return 1;
    h=h->next;
  }
  return 0;
}

intNode *deleteList(intNode *h)
{
  // Delete list and free memory
  intNode *q;
  if (h==NULL) return NULL;
  
  while (h!=NULL)
  {
     q=h->next;
     free(h);
     h=q;
  }
  
  return NULL;
}

// Read the adjacency matrix from file, and read the ingredient
// names
void load_ingredients(void)
{
  // Loads the adjacency matrix and ingredients list from file,
  // N must be either 10 (small graph), or 400 (full-size).
  
  FILE *f;
  int n=MAT_SIZE;
  
  if (n==10) f=fopen("AdjMat_small.dat","rb");
  else f=fopen("AdjMat_full.dat","rb");
  if (f==NULL)
  {
    printf("Can not open file with adjacency matrix. Please make sure it's in this directory\n");
    return;
  }
  fread(&AdjMat[0][0],n*n*sizeof(double),1,f);
  fclose(f);
  
  if (n==10) f=fopen("Ingredient_names_small.txt","r");
  else f=fopen("Ingredient_names_full.txt","r");
  if (f==NULL)
  {
    printf("Can not open file with ingredient names. Please make sure it's in this directory\n");
    return;
  }
  printf("Reading ingredient names. Available ingredient are:\n");
  for (int i=0; i<n; i++)
  {
    fgets(&ingredients[i][0],MAX_STR_LEN,f);
    for (int j=0; j<strlen(ingredients[i]); j++)
      if (ingredients[i][j]==10||ingredients[i][j]==13) ingredients[i][j]=0;
    printf("%s\n",ingredients[i]);
  }
  fclose(f);
}



void print_ingredients(intNode *h)
{
    /*
     * This function prints out all the ingredients corresponding
     * to the ingredient indexes stored in the linked list
     * whose head is 'h'.
     */

    intNode *tmp;
    tmp = h;
    while(tmp != NULL){
      printf("%s\n", ingredients[tmp->x]);
      tmp = tmp->next;
    }
}

int ingredient_index(char source_ingredient[MAX_STR_LEN])
{
    /*
     * This function looks into the array with ingredient
     * names for one that matches the requested 
     * 'source_ingredient'. If a match is found, it
     * returns the index at which the matching ingredient
     * name was found.
     * 
     * If the 'source_ingredient' is *not* in the ingredients
     * array, the function returns -1
     */

    int i = 0;
    while(i < MAT_SIZE){
      if(strcmp(ingredients[i], source_ingredient) == 0){
        return i;
      }
      i ++;
    }
    return -1;
     return 0;
}

void related_ingredients(char source_ingredient[MAX_STR_LEN])
{
    /*
     * This function prints out all the ingredients related
     * to the source ingredient. 
     * 
     * One per line, with no additional characters or symbols.
     *
     * Format of the adjacency matrix:
     * 
     * AdjMat[i][j] = 0 if two ingredients i and j are not directly linked
     *                (no edge in the graph between them, this means
     *                 they never appeared together in one recipe)
     * AdjMat[i][j] > 0 if two ingredients i and j are neighbours (they
     * 			appeared together in at least a recipe). The
     * 			actual value indicates how many times these two
     * 			ingredients appeared together in a recipe
     * 
     */

    int index;
    index = ingredient_index(source_ingredient);
    for(int i = 0; i < MAT_SIZE; i++){
      if(AdjMat[index][i] > 0){
        printf("%s\n", ingredients[i]);
      }
    }

}

intNode *related_k_dist(intNode *h, char source_ingredient[MAX_STR_LEN], int k, int dist)
{
    /*
     * This function recursively determines the ingredients related to the
     * specified source ingredient by a distance of at most k.
     * k >= 1 
     * 
     * (for k=1, this produces the same list as related_ingredients)
     * 
     * For instance, if k=2, the list should contain all the
     * ingredients who are neighbours of source_ingredient[]
     * as well as the ingredients that are neighbours of
     * the neighbours (distance=2).
     * 
     * If k=3, then we want source_ingredients' neighbours, its
     * neighbours' neighbours, and its neighbours' neighbours'
     * neighbours. And so on.
     * 
     * 
     * Ingredients are returned as *indexes*, so, for instance,
     * if we find a related ingredient 'chicken' is stored at
     * index 7 in ingredients[][], then we store 7 in the
     * linked list of related ingredients.
     * 
     * The returned list contains no duplicates.
     * example:
     * intNode *head=NULL;
     * head=related_k_dist(head,"rice",2,0);
     * 
     * After that call, 'head' must point to a linked list with
     * all the ingredients related to 'rice' up to a distance of
     * 2 away.
     * 
     */

    if(k < 1){
      return NULL;
    }
    if(k == dist + 1){
      int index;
        index = ingredient_index(source_ingredient);

      for(int i = 0; i < MAT_SIZE; i++){
          if(AdjMat[index][i] > 0 && searchInt(h, i) == 0){
            h = insertInt(h, i);
          }

      }
      return h;
    }
    else if(k > dist + 1){
      if(ingredient_index(source_ingredient) != -1){

        int index;
        index = ingredient_index(source_ingredient);

        for(int j = 0; j < MAT_SIZE; j ++){
          if(AdjMat[index][j] > 0){
            h = related_k_dist(h, ingredients[j], k, dist + 1);
            if(searchInt(h, j) == 0){
              h = insertInt(h, j);
            }
          }
        }

      }
    }
    return h;

    return NULL;
}


intNode *related_with_restrictions(char source_ingredient[MAX_STR_LEN], char avoid[MAX_STR_LEN], int k_source, int k_avoid)
{
    /*
     * This function returns a linked list that contains the indexes of
     * all ingredients related to source_ingredient[] with a distance
     * of at most k_source.
     * 
     * the list doesn't contain any ingredients related to avoid[]
     * (including avoid[] itself) by a distance of up to k_avoid.
     * 
     * Example:
     * 
     * intNode *head=NULL;
     * head=related_with_restrictions("rice", "nuts", 2, 0);
     * 
     * Should return a pointer to the head of a list of ingredients related to 
     * 'rice' by a distance of up to 2, NOT INCLUDING 'nuts'.
     * 
     * intNode *head=NULL;
     * head=related_with_restrictions("rice", "chicken", 2, 1);
     * 
     * Should return a list of ingredients related to 'rice' by a distance
     * of up to 2, NOT INCLUDING 'nuts' and any ingredients related
     * to 'nuts' with a distance of up to 1.
     * 
     */
    


    intNode *avoidlist = NULL;
    intNode *unoperated = NULL;
    intNode *result = NULL;
    unoperated = related_k_dist(unoperated, source_ingredient, k_source, 0);
    if(k_avoid == 0){
      avoidlist = insertInt(avoidlist, ingredient_index(avoid));
    }
    else{
      avoidlist = related_k_dist(avoidlist, avoid, k_avoid, 0);
    }
    intNode *tmp = unoperated;
    while(tmp != NULL){
      if(searchInt(avoidlist, tmp->x) == 0 && ingredient_index(avoid) != tmp->x){
        result = insertInt(result, tmp->x);
      }
      tmp = tmp->next;
    }
    deleteList(avoidlist);
    deleteList(unoperated);
    return result;


    return NULL;

}


void substitute_ingredient(char recipe[10][MAX_STR_LEN], char to_change[MAX_STR_LEN])
{
  /*
   * This function takes a recipe (which is an array of ingredients with up to 10
   * ingredients), and replaces the one in 'to_change' by *the most compatible
   * ingredient from the graph*
   * 
   * By most compatible, we mean the ingredient that appears most often with 
   * the remaining ingredients in the recipe.

   */

  int tch;
  for(int i = 0; i < 10; i ++){//locate the to_change's index in the recipe
    if(strcmp(recipe[i], to_change) == 0){
      tch = i;
      break;
    }
  }


  int originalrecipe[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  double neighbours[MAT_SIZE];
  int rootindex;

  for(int i = 0; i < MAT_SIZE; i ++){//initialize neighbour array;
    neighbours[i] = 0;
  }

  for(int i = 0; i < 10; i ++){//record valid index of the ingredients in the recipe
    rootindex = ingredient_index(recipe[i]);
    if(rootindex != -1){
      originalrecipe[i] = rootindex;
    }
  }

  for(int i = 0; i < 10; i ++){
    if(originalrecipe[i] != -1){//find every valid index
      for(int j = 0; j < MAT_SIZE; j ++){//add up the connections numbers
        neighbours[j] = neighbours[j] + AdjMat[originalrecipe[i]][j];
      }
    }
  }

  for(int i = 0; i < 10; i ++){//ignore the original ingredients, go find sth new.
    if(originalrecipe[i] != -1){
      neighbours[originalrecipe[i]] = 0;
    }
  }

  double max = 0;
  for(int i = 0; i < MAT_SIZE; i ++){//find maximum value
    if(max <= neighbours[i]){
      max = neighbours[i];
    }
  }

  for(int i = 0; i < MAT_SIZE; i ++){//locate target, replace to_change with target
    if(max == neighbours[i]){
      strcpy(recipe[tch], ingredients[i]);
      return;
    }
  }


}

