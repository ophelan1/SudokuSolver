#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <regex>
#include "sudokuBoard.h"

int main(int argc, char *argv[]){
	int boardSize = 9;
	char input[3];
	sudokuBoard<int> board_test(boardSize);

	if(argc > 1){
		char* file = argv[1];
		board_test.loadBoard(file);
	}

	while(1){
		board_test.printBoard();
		cin >> input;
		if(input[0]=='q') break;
		else if(sizeof(input) == 3){
			board_test.insertNumber(input);
		}
		else cout << "ERROR: Your Input Was Not the Correct Length" << endl;

		if(board_test.winCheck()){
			cout << "###### CONGRATULATIONS #####\n##### YOU SOLVED IT #####\n" << endl;
			break;
		}
	}
	if(input[0]!='q')board_test.printBoard();

	return(0);
}