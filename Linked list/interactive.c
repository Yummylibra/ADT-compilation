#include "MDB-c.c" 
/**
 * Reads a movie's name, title, and year from the terminal.
 * Required for inserting new reviews, search, updating, and deletion.
 *
 * INPUT: from terminal only
 *
 * OUTPUT:
 *  - title:
 *      an allocated char buffer (of length MAX_STR_LEN) in which the movie's title will be stored
 *  - studio:
 *      an allocated char buffer (of length MAX_STR_LEN) in which the movie's studio will be stored
 *  - year: an allocated integer buffer in which the movie's year will be stored
 */
void getTitleStudioYear(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int *year)
{
    printf("Please enter the movie's title:\n");
    fgets(title, MAX_STR_LEN, stdin);
    printf("Please enter the movie's studio:\n");
    fgets(studio, MAX_STR_LEN, stdin);
    printf("Please enter the movie's year:\n");
    scanf("%d", year);
    getchar();
}

/**
 * Reads a movie's Box-Office total and score from the terminal.
 * Required for inserting a new movie review, or for updating an existing review.
 *
 * INPUT: from terminal only
 *
 * OUTPUT:
 *  - BO_total:
 *      an allocated floating point buffer in which the movie's Box Office earnings will be stored
 *  - studio: an allocated integer buffer in which the movie's review score will be stored
 */
void getBOtotalScore(float *BO_total, int *score)
{
    printf("Please enter the Box Office total:\n");
    scanf("%f", BO_total);
    getchar();
    printf("Please enter the review score:\n");
    scanf("%d", score);
    getchar();
}

int main()
{
    ReviewNode *MDB_head = NULL;
    ReviewNode *temp = NULL;
    int choice = 0;
    char title[MAX_STR_LEN];
    char studio[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    int year;
    float BO_total, salary;
    int score;

    while (true)
    {
        printf("Please choose one of the following options:\n");
        printf("1 - Insert a new movie review.\n");
        printf("2 - Search for a movie review.\n");
        printf("3 - Modify an existing movie review.\n");
        printf("4 - Delete a movie review.\n");
        printf("5 - Print out existing reviews.\n");
        printf("6 - Query reviews by studio.\n");
        printf("7 - Query reviews by score.\n");
        printf("8 - Sort reviews by movie title.\n");
        printf("9 - Insert cast member.\n");
        printf("10 - Find who's the star.\n");
        printf("11 - Delete list of reviews and exit.\n");
        scanf("%d", &choice);
        getchar();

        // Read in review information from terminal where needed.
        if (choice >= 1 && choice <= 4)
        {
            getTitleStudioYear(title, studio, &year);
        }
        if (choice == 1 || choice == 3)
        {
            getBOtotalScore(&BO_total, &score);
        }
        if (choice == 1)
        {
            MDB_head = insertMovieReview(title, studio, year, BO_total, score, MDB_head);
        }
        else if (choice == 2)
        {
            temp = findMovieReview(title, studio, year, MDB_head);
            if (temp != NULL)
            {
                printf("Found the query movie:\n");
                printf("It had a box office total of %f\n", temp->review.BO_total);
                printf("And has a score of %d\n", temp->review.score);
            }
            else
            {
                printf("No such movie in the current list\n");
            }
        }
        else if (choice == 3)
        {
            updateMovieReview(title, studio, year, BO_total, score, MDB_head);
        }
        else if (choice == 4)
        {
            MDB_head = deleteMovieReview(title, studio, year, MDB_head);
        }
        else if (choice == 5)
        {
            printMovieReviews(MDB_head);
        }
        else if (choice == 6)
        {
            printf("Please enter the name of the studio you want to list movies for:\n");
            fgets(studio, MAX_STR_LEN, stdin);
            queryReviewsByStudio(studio, MDB_head);
        }
        else if (choice == 7)
        {
            printf("Enter the minimum score to be used to search for movies:\n");
            scanf("%d", &score);
            getchar();
            queryReviewsByScore(score, MDB_head);
        }
        else if (choice == 8)
        {
            printf("Sorting movies by title!\n");
            MDB_head = sortReviewsByTitle(MDB_head);
        }
        else if (choice == 9)
        {
            getTitleStudioYear(title, studio, &year);
            printf("Enter the name of the actor you want to add to this movie:\n");
            fgets(name, MAX_STR_LEN, stdin);
	    printf("Enter the salary for this cast member:\n");
            scanf("%f", &salary);
            getchar();
            insertCastMember(title, studio, year, MDB_head, name, salary);
            printNames(findMovieReview(title, studio, year, MDB_head));
        }
        else if (choice == 10)
        {
	    whosTheStar(MDB_head);
        }
        else if (choice == 11) break;
    }

    MDB_head = deleteReviewList(MDB_head);
    printf("Done!\n");
    return 0;
}
