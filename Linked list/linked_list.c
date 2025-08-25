#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

/* Compound data type declarations */


typedef struct castList_struct
{
    char name[1024];
    float salary;
    struct castList_struct *next;
} CastList;

typedef struct movieReview_struct
{
    char movie_title[1024];
    char movie_studio[1024];
    int year;
    float BO_total;
    int score;
    struct castList_struct *cast;
} MovieReview;

typedef struct reviewNode_struct
{
    MovieReview review;
    struct reviewNode_struct *next;
} ReviewNode;

ReviewNode *newMovieReviewNode()
{
    /*
     * This function allocates an empty ReviewNode, and initializes the
     * contents of the MovieReview for this node to reasonable (uninitialized) values.
     * The fields in the MovieReview should be set to:
     *  movie_title=""
     *  movie_studio=""
     *  year = -1
     *  BO_total = -1
     *  score = -1
     *  scoreList = NULL;???
     *
     * The *next pointer for the new node is set to NULL
     *
     * The function return a pointer to the newly allocated and initialized
     * node. If something goes wrong, the function returns NULL
     */


    ReviewNode *new_node = malloc(sizeof(ReviewNode));
    new_node->next = NULL;
    strcpy(new_node->review.movie_title, "");
    strcpy(new_node->review.movie_studio, "");
    new_node->review.year = -1;
    new_node->review.BO_total = -1;
    new_node->review.score = -1;
    new_node->review.cast = NULL;

    return (new_node);
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

    ReviewNode *p = head;
    while (p != NULL)
    {
        if (!strcmp(p->review.movie_title, title) &&
            !strcmp(p->review.movie_studio, studio) &&
            p->review.year == year)
        {
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

    if (findMovieReview(title, studio, year, head) != NULL)
    {
        return head;
    }
    else
    {
        ReviewNode *p = malloc(sizeof(ReviewNode));
        p->next = head;
        strcpy(p->review.movie_title, title);
        strcpy(p->review.movie_studio, studio);
        p->review.BO_total = BO_total;
        p->review.year = year;
        p->review.score = score;
        p->review.cast = NULL;
        return p;
    }
    return head; // meaningless but to remove Warning

}

int countReviews(ReviewNode *head)
{
    /*
     * This function returns the number of reviews.
     */

    int cnt = 0;
    while (head != NULL)
    {
        cnt++;
        head = head->next;
    }
    return cnt;

}

void updateMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
    /*
     * This function looks for a review matching the input query [title, studio, year].
     * If such a review is found, then the function updates the Box-office total, and the score.
     * If no such review is found, the function prints out
     * "Sorry, no such movie exists in the database"
     */


    ReviewNode *p = head;
    while (p != NULL)
    {
        if (!strcmp(p->review.movie_title, title) &&
            !strcmp(p->review.movie_studio, studio) &&
            p->review.year == year)
        {
            p->review.BO_total = BO_total;
            p->review.score = score;
            return;
        }
        p = p->next;
    }
    printf("Sorry, no such movie exists in the database");
    return;
}

ReviewNode *deleteMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    /*
     * This function removes a review matching the input query from the database. If no such review can
     * be found, it does nothing.
     *
     * The function returns a pointer to the head of the linked list (which may have changed as a result
     * of the deletion process)
     */

    ReviewNode *p = head;
    ReviewNode *last_p = p;
    if (!strcmp(p->review.movie_title, title) &&
        !strcmp(p->review.movie_studio, studio) &&
        p->review.year == year)
    {
        p = p->next;
        free(last_p);
        return p;
    }
    while (p != NULL)
    { // last_p --> p --> NULL
        if (!strcmp(p->review.movie_title, title) &&
            !strcmp(p->review.movie_studio, studio) &&
            p->review.year == year)
        {
            last_p->next = p->next;
            free(p);
            return head;
        }
        last_p = p;
        p = p->next;
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
     * movies that match the query.???
     */

    float total = 0;
    while (head != NULL)
    {
        printf("%s\n", head->review.movie_title);
        printf("%s\n", head->review.movie_studio);
        printf("%d\n", head->review.year);
        printf("%f\n", head->review.BO_total);
        printf("%d\n", head->review.score);
        printf("*******************\n");
        total += head->review.BO_total;
        head = head->next;
    }
    return total;

}

float queryReviewsByStudio(char studio[MAX_STR_LEN], ReviewNode *head)
{
    /*
     * This function looks for reviews whose studio matches the input query.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     *
     * Additionally, it computes and returns the Box-office total, for all the
     * movies that match the query.
     */

    float total = 0;
    while (head != NULL)
    {
        if (!strcmp(head->review.movie_studio, studio))
        {
            printf("%s\n", head->review.movie_title);
            printf("%s\n", head->review.movie_studio);
            printf("%d\n", head->review.year);
            printf("%f\n", head->review.BO_total);
            printf("%d\n", head->review.score);
            printf("*******************\n");
            total += head->review.BO_total;
        }
        head = head->next;
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
     *
     * Additionally, it computes and returns the Box-office total, for all the
     * movies that match the query.
     */

    float total = 0;
    while (head != NULL)
    {
        if (head->review.score >= min_score)
        {
            printf("%s\n", head->review.movie_title);
            printf("%s\n", head->review.movie_studio);
            printf("%d\n", head->review.year);
            printf("%f\n", head->review.BO_total);
            printf("%d\n", head->review.score);
            printf("*******************\n");
            total += head->review.BO_total;
        }
        head = head->next;
    }
    return total;

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

    ReviewNode *p = head;
    ReviewNode *last_p = p;
    while (p != NULL)
    {
        last_p = p;
        p = p->next;
        free(last_p);
    }
    return NULL;

}



ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
    /*
     * This function sorts the list of movie reviews in ascending order of movie
     * title. If duplicate movie titles exist, the order is arbitrary (i.e. you
     * can choose which one goes first).
     */

    ReviewNode *p = head;
    ReviewNode *q = head;
    ReviewNode *tmp = NULL;
    ReviewNode *min_node = p;
    int cnt = 0;

    if (head == NULL)
    {
        return NULL;
    }

    while (p != NULL)
    {
        cnt++;
        p = p->next;
    }

    for (int i = 1; i < cnt; i++)
    { // skip head
        p = head;
        for (int j = 0; j < i - 1; j++)
        { // stop 1 node before unsorted part
            p = p->next;
        }
        q = p;
        min_node = q;
        while (q->next != NULL)
        {
            if (strcmp(q->next->review.movie_title, min_node->next->review.movie_title) < 0)
            {
                min_node = q;
            }
            q = q->next;
        } // swap
        tmp = p->next;
        p->next = min_node->next;
        min_node->next = tmp;

        tmp = p->next->next;
        p->next->next = min_node->next->next;
        min_node->next->next = tmp;
    }

    p = head;
    q = p->next;
    if (strcmp(head->review.movie_title, q->review.movie_title) < 0)
    {
        return head; // head < head.next < ...
    }
    while (q->next != NULL)
    {
        if (strcmp(head->review.movie_title, q->next->review.movie_title) < 0)
        {
            p = head->next;
            head->next = q->next;
            q->next = head;
            return p;
        }
        // stop when qnext <= pnext
        q = q->next;
    }
    // q went to the end
    p = head->next;
    q->next = head;
    head->next = NULL;
    return p;

}

void insertCastMember(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head, char name[MAX_STR_LEN], float salary)
{
    /*
     * This function inserts the name of a cast member for the given movie into the
     * linked list of cast members. The new cast member must go to the end of the list.
     *
     * the function receives the title, studio, and year for the movie, as
     * well as a pointer to the movie DB linked list. The function must find the
     * correct movie and if such a movie exists, add the cast member's name to its
     * cast list.
     *
     * If no such movie is found, this function does nothing.
     */

    ReviewNode *p = head;
    while (p != NULL)
    {
        if (!strcmp(p->review.movie_title, title) &&
            !strcmp(p->review.movie_studio, studio) &&
            p->review.year == year)
        {
            CastList *q = p->review.cast;
            if (q == NULL)
            { // there is no end (no begin. nothing. its void.)
                CastList *new_cast = malloc(sizeof(CastList));
                strcpy(new_cast->name, name);
                new_cast->salary = salary;
                new_cast->next = NULL;
                p->review.cast = new_cast;
            }
            else
            {
                while (q->next != NULL)
                { // goto end
                    q = q->next;
                }
                CastList *new_cast = malloc(sizeof(CastList));
                strcpy(new_cast->name, name);
                new_cast->salary = salary;
                new_cast->next = NULL;
                q->next = new_cast;
            }
        }
        p = p->next;
    }
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
     *  The function simply prints out:
     *
     *  Name of cast member
     *  Average movie earnings (as a floating point number)
     *
     *  For the cast member whose movies make the greatest average earnings
     */

     //for movies
    float movie_earning = 0;
    float Earnings_of_Movie[1000]; // less than 1000 movies?
    int Total_Movie = 0;

    memset(Earnings_of_Movie, 0, sizeof(Earnings_of_Movie));

    // for Cast Members
    char *The_Stars[1000];          // 1000 x name
    float Earnings_of_Member[1000]; // 1000 x float
    int Movie_Count[1000];          // 1000 x amount of movies
    int Total_Member = 0;           // Num. of  all Members

    memset(The_Stars, 0, sizeof(The_Stars));
    memset(Earnings_of_Member, 0, sizeof(Earnings_of_Member));
    memset(Movie_Count, 0, sizeof(Movie_Count));

    ReviewNode *p = head;

    while (p != NULL)
    { // First Round: Count Earning for Each Movie
        movie_earning = p->review.BO_total;
        CastList *q = p->review.cast;
        while (q != NULL)
        {
            movie_earning -= q->salary;
            q = q->next;
        }
        Earnings_of_Movie[Total_Movie++] = movie_earning;
        p = p->next;
    }

    p = head;
    while (p != NULL)
    { // 2nd Round: A List of Members
        CastList *q = p->review.cast;
        int flag = 0;
        while (q != NULL)
        {
            for (int i = 0; i < Total_Member; i++)
            {
                if (!strcmp(q->name, The_Stars[i]))
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                The_Stars[Total_Member] = (char *)malloc(sizeof(q->name));
                strcpy(The_Stars[Total_Member], q->name);
                Total_Member++;
            }
            q = q->next;
        }
        p = p->next;
    }

    p = head;
    int index = 0;
    for (int i = 0; i < Total_Member; i++) // i = index of Member
    { // 3rd Round: Sum up Earnings for Each Member
        p = head;
        index = 0;
        while (p != NULL)
        {
            CastList *q = p->review.cast;
            while (q != NULL)
            {
                if (!strcmp(q->name, The_Stars[i]))
                {
                    Earnings_of_Member[i] += Earnings_of_Movie[index];
                    Movie_Count[i]++;
                }
                q = q->next;
            }
            index++;
            p = p->next;
        }
    }

    char Winner[1000];
    float max_earning = 0;
    for (int i = 0; i < Total_Member; i++)
    { // 4th Round: Pick the Max AVERAGE
        if (Earnings_of_Member[i]/(float)Movie_Count[i] > max_earning)
        {
            strcpy(Winner, The_Stars[i]);
            max_earning = Earnings_of_Member[i]/(float)Movie_Count[i];
        }
    }
    printf("%s\n%f\n", Winner, max_earning);
}
