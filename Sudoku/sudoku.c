#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_sudoku(int sudoku[9][9])
{
  printf("The Sudoku contains:\n");
  for (int j=0; j<9; j++)
  {
    for (int i=0; i<9;i++)
    {
      printf("%d  ",sudoku[j][i]);
    }
    printf("\n");
  }
}

int check_sudoku(int sudoku[9][9])
{
  /*
   *  This function checks whether a 9*9 Sudoku is properly
   * solved. That means that each row, column, and
   * 3x3 subgrid uses each digit only once.
   */
  
  for(int i = 0; i < 9; i++){//row
    for(int j = 0; j < 9; j ++){//column
    if(sudoku[i][j] != 0){

      for(int k = 0; k < 9; k++){
        if(j != k && sudoku[i][j] == sudoku[i][k]){//row repeat check
          return 0;
        }
      }

      for(int k = 0; k < 9; k++){
        if(i != k && sudoku[i][j] == sudoku[k][j]){//column repeat check
          return 0;
        }
      }
      int x = (i / 3) * 3;
      int y = (j / 3) * 3;
      for(int p = 0; p < 3; p++){
        for(int q = 0; q < 3; q++){
          if(x + p != i && y+ q != j && sudoku[x + p][y + q] == sudoku[i][j]){//chunk repeat check
            return 0;
          }
        }
      }
    }

    }
  }
  return 1;


   return 0;  
}

int solved(int sudoku[9][9])
{
  /*
   * This function checks whether a given Sudoku is
   * completely solved (it has no zeros, all digits
   * are used once per row, column, and sub-grid.
   * It returns 1 if the Sudoku is solved, zero
   * otherwise
   */
  
  if(check_sudoku(sudoku) == 0){
    return 0;
  }
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j ++){
      if(sudoku[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}


int rowclmrepeat(int sudoku[9][9], int row, int column, int num){//if repeat return 0, else(valid) return 1

  for(int i = 0; i < 9; i ++){
    if(sudoku[i][column] == num){
      return 0;
    }
  }

  for(int i = 0; i < 9; i++){
    if(sudoku[row][i] == num){
      return 0;
    }
  }
  return 1;
}

int chunkrepeat(int sudoku[9][9], int row, int column, int num){//if repeat return 0; else(valid) return 1
  int rstart, clstart;
  rstart = (row/3)*3;
  clstart = (column/3)*3;
  for(int i = rstart; i < rstart + 3; i++){
    for(int j = clstart; j < clstart + 3; j++){
      if(row != i && column != j && sudoku[i][j] == num){
        return 0;
      }
    }

  }
  return 1;

}

int operate(int sudoku[9][9], int row, int column){
 
    if(row > 8){
        return 1;
    }
 
    if(sudoku[row][column] == 0)
    {
        for(int i = 1; i < 10; i++)
        {
            if(rowclmrepeat(sudoku, row, column, i) == 1 && chunkrepeat(sudoku, row, column, i) == 1)
            {
                sudoku[row][column] = i;
                if(operate(sudoku, row + (column + 1)/9, (column + 1)%9)==1)
                    return 1;
            }
            sudoku[row][column] = 0;
        }
    }
    else
    {
        if(operate(sudoku, row + (column + 1)/9, (column + 1)%9)==1)
            return 1;
    }

    return 0;
}
 

void solve_sudoku(int sudoku[9][9], int depth)
{
  /*
   * This function solves an input Sudoku, the
   * input has a value of 0 for any entries that
   * are not yet decided. If no solution exists
   * the function returns the input array *exactly
   * as it was* when the function was called.
   * 
   */
  

  if(check_sudoku(sudoku) == 1){
    operate(sudoku,  0, 0);
  }
}


#ifndef __testing

int main()
{

  
   int Sudoku[9][9]={{5, 3, 0, 0, 7, 0, 0, 0, 0},
		     {6, 0, 0, 1, 9, 5, 0, 0, 0},
		     {0, 9, 8, 0, 0, 0, 0, 6, 0},
		     {8, 0, 0, 0, 6, 0, 0, 0, 3},
		     {4, 0, 0, 8, 0, 3, 0, 0, 1},
		     {7, 0, 0, 0, 2, 0, 0, 0, 6},
		     {0, 6, 0, 0, 0, 0, 2, 8, 0},
		     {0, 0, 0, 4, 1, 9, 0, 0, 5},
		     {0, 0, 0, 0, 8, 0, 0, 7, 9}};


  printf("Input puzzle is:\n");
  print_sudoku(Sudoku);
  
  solve_sudoku(Sudoku,0);
  
  printf("Solution is:\n");
  print_sudoku(Sudoku);
  
}

#endif