//sudBoard.h

#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
using namespace std;


// sudokuBoard class definition
template <typename T>
class sudokuBoard {

 public:

  sudokuBoard( int = 9 ); // default constructor  
  void loadBoard(char *);
  void printBoard();  
  void insertNumber(char*);    
  int getSize();
  int boardCheck(int, int);
  int winCheck(void);                                       

 private:

  int size; // pointer-based array size
  vector< vector<T> > board;
}; // SudokuBoard


template<typename T>
sudokuBoard<T>::sudokuBoard( int boardSize )  {
  int i,j;

  size = ( boardSize%3==0 ? boardSize : 9 ); // validate arraySize

  for(i = 0 ; i < size ; i++){ 
    vector<T> tmp;

    for(j = 0 ; j < size ; j++){
      tmp.push_back(0);
    }
    board.push_back(tmp);
  }

} // end sudokuBoard default construct

template<typename T>
void sudokuBoard<T>::printBoard(){
  int i, j;

  //Print the blank Spaces to Clear the Screen
  //Print the Welcome Menue and Instructions
  cout << "#########<~~~  WELCOME TO SODOKU  ~~~>########" << endl;
  cout << "| Enter A Number, Row, and Column (i.e. 739) |" << endl;


  //Print the Rows
  for(i = 0 ; i < size ; i++){
    std::cout << "\n     ";
    if(i%3==0) cout << " --------------------------------\n     ";

    //Print The elements of each Row
    for(j = 0 ; j < size ; j++){
      if(j%3==0) cout << "| ";
      if(board[i][j] != 0) cout << board[i][j] << "  ";
      else cout << "#  ";
    }
    cout << "|";
  }
  cout << "\n      --------------------------------\n\n" << endl;
} //end printboard

template<typename T>
int sudokuBoard<T>::getSize(){
  int sizeResult = size;
  return(sizeResult);
}

template<typename T>
void sudokuBoard<T>::loadBoard(char* inputFile){
  int i = 0, j = 0;
  char c;
  int ic;

  FILE* file;
  file = fopen(inputFile, "r");

  while(1){
    c = fgetc(file);
    if(c == '\n'){
      i++;
      j=0;
    }
    else if(c == EOF) break;
    else{
      ic = c - '0';
      board[i][j]=ic;
      j++;
    }
  }

  fclose(file);
}

template<typename T>
int sudokuBoard<T>::boardCheck(int rowNum, int colNum){
  int check = 1;
  int i, j;
  T num=board[rowNum][colNum];

  //Check to see if it contadicts a different identical element in the row  
    for( j = 0 ; j < size ; j++){
      if( (board[rowNum][j] == num) && (colNum != j) ) check = 0;
    }

  //Check to see if it contadicts a different identical element in the column
    for(j = 0 ; j < size ; j++){
      if( (board[j][colNum] == num) && (rowNum != j) ){
        check = 0;
      }
    }


  //Check to see if it contradicts a different identical element in it's box
  int rowStart=rowNum-(rowNum%3);
  int colStart=colNum-(colNum%3);

    for(i = 0 ; i < 3 ; i++){
    for(j = 0 ; j < 3 ; j++){
      if( (board[rowStart+i][colStart+j] == num) && (( rowNum != rowStart+i) || (colNum != colStart+j)) ){
        check=0;
      }
    }
    }

  return(check);
}

template<typename T>
void sudokuBoard<T>::insertNumber(char selection[3]){


  string input_pattern = "^[1-9][1-9][1-9]$";
  regex pattern(input_pattern, regex_constants::grep);

  if(!regex_match(selection, pattern)) cout << "ERROR: Your Input Pattern Didn't Match The Template" << endl;
  else {
    int number = selection[0] - '0';
    int row = selection[1] - '0';
    int col = selection[2] - '0';
    cout << "The Number You selected was " << number << " Row: " << row << " Column: " << col << endl;
    row--; //This adjust for computer numbering versus human numbering of rows and columns
    col--;

    if(board[row][col]==0){
      board[row][col]=number;
      if(!boardCheck(row, col)){
        cout << "ERROR: INVALID PLACEMENT" << endl;
        board[row][col]=0;
      }
    }
    else cout << "ERROR: Already A number at that Positon" << endl;
  }
}

template<typename T>
int sudokuBoard<T>::winCheck(){
  int i,j;
  int winCheck=1;

  for(i = 0 ; i < size ; i++){
    for(j = 0 ; j < size ; j++){
      if (board[i][j]==0) winCheck = 0;
    }
  }

  return(winCheck);
}

template,typename T>
int sudokuBoard<T>::winCheck(){

}
#endif
