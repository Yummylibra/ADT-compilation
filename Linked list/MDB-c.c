#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 1024

/* Compound data type declarations */


typedef struct castList_struct{
    char name[MAX_STR_LEN];
    float salary;
    struct castList_struct *next;

} CastList;

typedef struct movieReview_struct
{
    char movie_title[MAX_STR_LEN];
    char movie_studio[MAX_STR_LEN];
    int year;
    float BO_total;
    int score;
    struct castList_struct *cast;
    
} MovieReview;

typedef struct reviewNode_struct
{
    struct movieReview_struct review;
    struct reviewNode_struct *next;

    
} ReviewNode;



ReviewNode *newMovieReviewNode()
{
    /*
     * This function allocates an empty ReviewNode, and initializes the
     * contents of the MovieReview for this node to reasonable (uninitialized) values.
     * The fields in the MovieReview are intialized to:
     *  movie_title=""
     *  movie_studio=""
     *  year = -1
     *  BO_total = -1
     *  score = -1
     *  scoreList = NULL;
     * 
     * The *next pointer for the new node is initialized as NULL
     * 
     * The function return a pointer to the newly allocated and initialized
     * node. If something goes wrong, the function returns NULL
     */


    ReviewNode *new_node = (ReviewNode *)calloc(1, sizeof(ReviewNode));
    if (new_node == NULL) {
        return NULL;
    }
    strcpy(new_node->review.movie_title,"");
    strcpy(new_node->review.movie_studio,"");
    new_node->review.year = -1;
    new_node->review.BO_total = -1;
    new_node->review.score = -1;
    new_node->review.cast =  NULL;
    new_node->next = NULL;
    return(new_node);

}

ReviewNode *findMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    /*
     * This function searches through the linked list for a review that matches the input query. 
     * The movie review must match the title, studio, and year provided in the 
     * parameters for this function.
     * 
     * If a review matching the query is found, this function returns the address of the node that
     * contains that review. 
     * 
     * If no such review is found, this function returns NULL
     */

    ReviewNode *p;
    p = head;
    while(p != NULL){
        if((strcmp(p->review.movie_title, title) == 0)&&(strcmp(p->review.movie_studio, studio) == 0)&&(p->review.year==year)){
            return p;
        }
        p = p->next;
    }
    return NULL;  
}

ReviewNode *insertMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
    /*
     * This function inserts a new movie review into the linked list.
     * 
     * The function takes as input parameters the data neede to fill-in the review,
     * as well as apointer to the current head of the linked list.
     * 
     * If head==NULL, then the list is still empty.
     * 
     * The function inserts the new movie review *AT THE HEAD* of the linked list,
     * and returns the pointer to the new head node.
     * 
     * The function checks that the movie is not already in the list before
     * inserting (there should be no duplicate entries). If a movie with matching
     * title, studio, and year is already in the list, nothing is inserted and the
     * function returns the current list head.
     */

    ReviewNode *p;
    p = head;
    while(p != NULL){
        if((strcmp(p->review.movie_title, title)==0)&&(strcmp(p->review.movie_studio, studio)==0)){
            if((p->review.year == year)&&(p->review.BO_total == BO_total)){
                return head;
            }
        }
        p = p->next;
    }
    ReviewNode *new_node = (ReviewNode *)calloc(1, sizeof(ReviewNode));
    if (!new_node) {
        return NULL;
    }
    new_node = (ReviewNode *)calloc(1,sizeof(ReviewNode));
    strcpy(new_node->review.movie_title, title);
    strcpy(new_node->review.movie_studio, studio);
    new_node->review.year = year;
    new_node->review.BO_total = BO_total;
    new_node->review.score = score;
    new_node->next = head;
    return new_node;
    
}

int countReviews(ReviewNode *head)
{
  /*
   * This function returns the number of reviews. 
   */


    ReviewNode *p;
    int count;
    p = head;
    count = 0;
    while(p != NULL){
        count ++;
        p = p->next;
    }
    return count;

}

void updateMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
    /*
     * This function looks for a review matching the input query [title, studio, year].
     * If such a review is found, then the function updates the Box-office total, and the score.
     * If no such review is found, the function prints out 
     * "Sorry, no such movie exists in the database"
     */

    ReviewNode *p;
    p = head;
    int founded;
    founded = 0;
    while(p != NULL){
        if((strcmp(p->review.movie_title, title)==0)&&(strcmp(p->review.movie_studio, studio)==0)&&(p->review.year == year)){
            p->review.BO_total = BO_total;
            p->review.score = score;
            founded = 1;
        }
        p = p->next;
    }
    if(founded == 0){
        printf("Sorry, no such movie exists in the database");
    }
    
}

ReviewNode *deleteMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN],int year, ReviewNode *head)
{
    /*
     * This function removes a review matching the input query from the database. If no such review can
     * be found, it does nothing.
     * 
     * The function returns a pointer to the head of the linked list (which may have changed as a result
     * of the deletion process)
     */


    ReviewNode *prev = NULL, *cur = head;
    while (cur) {
        if (strcmp(cur->review.movie_title, title) == 0 &&
            strcmp(cur->review.movie_studio, studio) == 0 &&
            cur->review.year == year) {

            if (prev) {
                prev->next = cur->next;
            }
            else {
                head = cur->next;
            }

            free(cur);
            return head;
        }
        prev = cur;
        cur = cur->next;
    }
    return head;

}

float printMovieReviews(ReviewNode *head)
{
    /*
     * This function prints out all the reviews in the database, one after another.
     * Each field in the review is printed in a separate line, with *no additional text*
     * (that means, the only thing printed is the value of the corresponding field).
     * 
     * Reviews are separated from each other by a line of
     * "*******************"

     * The function also computes and returns the Box-office total, for all the
     * movies that match the query.
     */

    ReviewNode *p;
    p = head;
    float result = 0;
    while(p != NULL){
        printf("%s\n", p->review.movie_title);
        printf("%s\n", p->review.movie_studio);
        printf("%d\n",p->review.year);
        printf("%f\n",p->review.BO_total);
        printf("%d\n",p->review.score);
        printf("*******************");
        result = result + p->review.BO_total;
        p = p->next;
    }
    return result;

}

float queryReviewsByStudio(char studio[MAX_STR_LEN], ReviewNode *head)
{
    /*
     * This function looks for reviews whose studio matches the input query.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     * 
     * It also computes and returns the Box-office total, for all the
     * movies that match the query.
     */

    ReviewNode *p;
    p = head;
    float total;
    total = 0;
    while(p != NULL){
        if(strcmp(p->review.movie_studio, studio)==0){
            printf("%s\n", p->review.movie_title);
            printf("%s\n", p->review.movie_studio);
            printf("%d\n",p->review.year);
            printf("%f\n",p->review.BO_total);
            printf("%d\n",p->review.score);
            printf("*******************");
            total = total + p->review.BO_total;
        }
        p = p->next;
    }

    return total;


}

float queryReviewsByScore(int min_score, ReviewNode *head)
{
    /*
     * This function looks for reviews whose score is greater than, or equal to
     * the input 'min_score'.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     */
    float result = 0;
    ReviewNode *p;
    p = head;
    while(p != NULL){
        if(p->review.score >= min_score){
            printf("%s\n", p->review.movie_title);
            printf("%s\n", p->review.movie_studio);
            printf("%d\n",p->review.year);
            printf("%f\n",p->review.BO_total);
            printf("%d\n",p->review.score);
            printf("*******************");
            result = result + p->review.BO_total;
        }
        p = p->next;
    }
    return result;
    
    return 0;
}

ReviewNode *deleteReviewList(ReviewNode *head)
{
  /*
   * This function deletes the movie review database, releasing all the
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   */
      
    ReviewNode *p = NULL;
    ReviewNode *q = NULL;
    p = head;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    
    return head; 
}



ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
  /*
   * This function sorts the list of movie reviews in ascending order of movie
   * title. If duplicate movie titles exist, the order is arbitrary.
   * 
   * It return a pointer to the head node of the sorted list.
   */

    int sorted;
    ReviewNode *p;
    ReviewNode *q;
    sorted = 0;

    while (sorted == 0)
    {
        p = head;
        sorted = 1;
        while(p->next != NULL){
            q = p->next;
            if(strcmp(q->review.movie_title,q->review.movie_title)<0){
                sorted = 0;

                char trans[MAX_STR_LEN];
                strcpy(trans,q->review.movie_title);
                strcpy(q->review.movie_title,p->review.movie_title);
                strcpy(p->review.movie_title,trans);

                strcpy(trans,q->review.movie_studio);
                strcpy(q->review.movie_studio, p->review.movie_studio);
                strcpy(p->review.movie_studio,trans);

                int ytrans;
                ytrans = q->review.year;
                q->review.year = p->review.year;
                p->review.year = ytrans;

                float totrans;
                totrans = q->review.BO_total;
                q->review.BO_total = p->review.BO_total;
                p->review.BO_total = totrans;

                int strans;
                strans = q->review.score;
                q->review.score = p->review.score;
                p->review.score = strans;

                struct castList_struct *ttrans;
                ttrans = q->review.cast;
                q->review.cast = p->review.cast;
                p->review.cast = ttrans;
            }
            p = p->next;
        }
    }
    return head;

}

void insertCastMember(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head, char name[MAX_STR_LEN], float salary)
{
  /*
   * This function inserts the name of a cast member for the given movie into the
   * linked list of cast members. The new cast member should go to the end of the list.
   * The function receives the title, studio, and year for the movie, as
   * well as a pointer to the movie DB linked list. The function will find the 
   * correct movie and if such a movie exists, add the cast member's name to its
   * cast list.
   * 
   * If no such movie is found, this function does nothing.
   * 
   */   


  ReviewNode *p;
  p = head;
  while(p != NULL){
      if((strcmp(p->review.movie_title, title)==0)&&(p->review.movie_studio, studio)&&(p->review.year == year)){
          struct castList_struct *q;
          q = p->review.cast;
          while(q->next != NULL){
              q = q->next;
          }
          CastList new_cast;
          strcpy(new_cast.name, name);
          new_cast.salary = salary;
          new_cast.next = NULL;
          q->next = &new_cast;

      }

      p = p->next;
  }
}

float cal(ReviewNode *ptr){
    float result;
    float count;
    result = 0;
    count = 0;
    CastList *p;
    p = ptr->review.cast;
    while(p != NULL){
        count = count + p->salary;
        p = p->next;
    }
    result = (ptr->review.BO_total - count);
    return result; 
}



typedef struct actorlist{
    char name[MAX_STR_LEN];
    float earn;
    float movienum;
    float avgearn;
    struct actorlist *next;
}actor;

int movieofactor[1000][100];



static double avg_for_actor(ReviewNode *head, const char *name) {
    double total = 0.0;
    int cnt = 0;
    ReviewNode *p = head;
    while (p) {
        if (actor_in_cast(p->review.cast, name)) {
            total += movie_earnings(p);
            cnt += 1;
        }
        p = p->next;
    }
    if (cnt == 0) return -1e300;
    return total / cnt;
}


void whosTheStar(ReviewNode *head)
{
  /*
   *  This function goes through the movie database and determines who is
   * the cast members whose movies have the greatest average earnings.
   *
   * Earnings are defined as the box office total minus the salaries of all
   * cast members involved with the movie.
   *
   *
   *  The function simply prints out:
   *
   *  Name of cast member
   *  Average movie earnings (as a floating point number)
   *
   *  For the cast member whose movies make the greatest average earnings
   */
  if (head == NULL){
    return NULL;
  }

  char best_name[MAX_STR_LEN] = "";
  double best_avg = -1e300;
  ReviewNode *p = head;

  while(p!=NULL){
      CastList *c = p->review.cast;
      while(c != NULL){
        double avg = avg_for_actor(head, c->name);
        if (avg > best_avg) {
                strncpy(best_name, c->name, MAX_STR_LEN - 1);
                best_name[MAX_STR_LEN - 1] = '\0';
                best_avg = avg;
            }
        c = c->next;
      }
      p = p->next;
  }

  if (best_name[0] != '\0') {
    printf("%s\n", best_name);
    printf("%f\n", (float)best_avg);
  }
}

void printNames(ReviewNode *movie){
    CastList *p;
    if(movie==NULL||movie->review.cast==NULL)return;

    p = movie->review.cast;
    printf("The cast for this movie are:\n");
    while (p!=NULL)
    {
        printf("Cast Member: %s, Salary: %f\n",p->name,p->salary);
        p = p->next;
    }
    
}