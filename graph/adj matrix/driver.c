
#include<stdio.h>
#include<stdlib.h>
#include"ingredient_graph.c"

int main()
{

   
   intNode *head=NULL;
   char recipe[10][MAX_STR_LEN]={"fresh breadcrumbs",
				 "artichoke hearts",
				 "quinoa",
				 "",
				 "",
				 "",
				 "",
				 "",
				 "",
				 ""};
   

   load_ingredients();
   printf("------- The available ingredients should appear above this line -------\n");
   // Call related ingredients
   printf("\n ****** Related ingredients for quinoa:\n");
   related_ingredients("quinoa");  // Make sure this
				   // ingredient exists
   
   printf("\n ****** Related to 'quinoa' k-dist, k=1 - Updtaed\n");
   head=related_k_dist(head,"quinoa",1,0);
   print_ingredients(head);
   head=deleteList(head);
 
   printf("\n ****** Related to 'quinoa' k-dist, k=2 - Updated\n");
   head=related_k_dist(head,"quinoa",2,0);
   print_ingredients(head);
   head=deleteList(head);

   printf("\n ****** Related to 'artichoke hearts' k-dist, k=1 - Updated\n");
   head=related_k_dist(head,"artichoke hearts",1,0);
   print_ingredients(head);
   head=deleteList(head);

   printf("\n ****** Related to 'tomato juice' k-dist, k=1 - Updated\n");
   head=related_k_dist(head,"tomato juice",1,0);
   print_ingredients(head);
   head=deleteList(head);

   printf("\n ****** Related to 'tomato juice' k-dist, k=2 - Updated\n");
   head=related_k_dist(head,"tomato juice",2,0);
   print_ingredients(head);
   head=deleteList(head);

   printf("\n ****** Related with restrictions, 'quinoa', 'artichoke hearts', k_source=1, k_dest=1 - Updated;\n");
   head=related_with_restrictions("quinoa","artichoke hearts",1,1);
   print_ingredients(head);
   head=deleteList(head);

   printf("\n ****** Related with restrictions, 'quinoa', 'tomato juice', k_source=2, k_dest=1 - Updated;\n");
   head=related_with_restrictions("quinoa","tomato juice",2,1);
   print_ingredients(head);
   head=deleteList(head);

   printf("\n ****** Related with restrictions, 'quinoa', 'tomato juice', k_source=2, k_dest=2 - Updated;\n");
   head=related_with_restrictions("quinoa","tomato juice",2,2);
   print_ingredients(head);
   head=deleteList(head);

   printf("\n ****** substituting ingredient 'quinoa' in recipe\n");
   substitute_ingredient(recipe,"quinoa");
   for (int i=0; i<10; i++)
     if (strlen(recipe[i])>0) printf("%s\n",recipe[i]);

   /* output for sample call:

 ****** Related ingredients for quinoa:
artichoke hearts
sunflower seeds

 ****** Related to 'quinoa' k-dist, k=1 - Updtaed
sunflower seeds
artichoke hearts

 ****** Related to 'quinoa' k-dist, k=2 - Updated
gruyere cheese
turkey
medium shrimp
quinoa
soymilk
sunflower seeds
artichoke hearts

 ****** Related to 'artichoke hearts' k-dist, k=1 - Updated
quinoa
gruyere cheese
turkey
medium shrimp

 ****** Related to 'tomato juice' k-dist, k=1 - Updated
fresh breadcrumbs
prepared horseradish

 ****** Related to 'tomato juice' k-dist, k=2 - Updated
medium shrimp
gruyere cheese
tomato juice
fresh breadcrumbs
prepared horseradish

 ****** Related with restrictions, 'quinoa', 'artichoke hearts', k_source=1, k_dest=1 - Updated;
sunflower seeds

 ****** Related with restrictions, 'quinoa', 'tomato juice', k_source=2, k_dest=1 - Updated;
artichoke hearts
sunflower seeds
soymilk
quinoa
medium shrimp
turkey
gruyere cheese

 ****** Related with restrictions, 'quinoa', 'tomato juice', k_source=2, k_dest=2 - Updated;
artichoke hearts
sunflower seeds
soymilk
quinoa
turkey

 ****** substituting ingredient 'quinoa' in recipe
fresh breadcrumbs
artichoke hearts
gruyere cheese

*/

  return 0;   
}
