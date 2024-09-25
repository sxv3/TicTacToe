#include <iostream>
#include <cstring>
#include <tuple>
#include <ctype.h>

//TicTacToe, a simple tictactoe game played with 2 players and the console by Tai Wong
//9/14/24



using namespace std;

//function to just print out the board
void printBoard(char board[3][4]) {
  cout << "  123" << std::endl;
  cout << "a ";
  cout << board[0] << std::endl;
  cout << "b ";
  cout << board[1] << std::endl;
  cout << "c ";
  cout << board[2] << std::endl;
}

//function to check for wins
bool gameCheck(char board[3][4]) {

  //just variables to store which player is which
  char playerX = 'X';
  char playerO = 'O';
  
  if ((board[0][0] == playerX) && (board[1][1] == playerX) && (board[2][2] == playerX)) {
    //game won diagnolly
    return true;
  }  
  if ((board[0][0] == playerO) && (board[1][1] == playerO) && (board[2][2] == playerO)) {
    //game won diagnolly
    return true;
  }

  if ((board[2][0] == playerX) && (board[1][1] == playerX) && (board[0][2] == playerX)) {
    //game won diagnolly
    return true;
  }

  if ((board[2][0] == playerO) && (board[1][1] == playerO) && (board[0][2] == playerO)) {
    //game won diagnolly
    return true;
  }

  for (int x=0; x<3; x++) {
    if ((board[x][0] == playerX) && (board[x][1] == playerX) && (board[x][2] == playerX)) {
      //game won horizontally
      return true;
    }
    
    if ((board[x][0] == playerO) && (board[x][1] == playerO) && (board[x][2] == playerO)) {
      //game won horizontally
      return true;
    }

    if ((board[0][x] == playerX) && (board[1][x] == playerX) && (board[2][x] == playerX)) {
      //game won vertically
      return true;
    }

    if ((board[0][x] == playerO) && (board[1][x] == playerO) && (board[2][x] == playerO)) {
      //game won vertically
      return true;
    }
  }
  //no wins
  return false;
}

//function to map the coordinate sent by player to indices 
std::tuple<int, int> moveMapper(char move[2]) {
  
  int yCord = 99;
  
  if (move[0] == 'a') {
    yCord = 0;
  } else if (move[0] == 'b') {
    yCord = 1;
  } else if (move[0] == 'c') {
    yCord = 2;
  } else {
    yCord = 99;
  }

  int xCord = 99;
  
  if (move[1] == '1') {
    xCord = 0;
  } else if (move[1] == '2') {
    xCord = 1;
  } else if (move[1] == '3') {
    xCord = 2;
  } else {
    xCord = 99;
  }


  
  return std::make_tuple(yCord, xCord);
  
}


//main function
int main() {

  //initailizes all variables
  char board[3][4];
  bool start = true;
  bool gameWon = false;
  int playerXwins = 0;
  int playerOwins = 0;
  int draws = 0;
  int moveCount = 0;

  //creates board
  for (int i=0; i<3; i++) {
    for (int n=0; n<3; n++) {
      board[i][n] = ' ';
      if (n == 2) {
	board[i][n+1] = '\0';
      }
    }
  }

  //lets user know the board state
  cout << "Here is the board:" << std::endl;
  printBoard(board);

  //while loop to repeat game
  while (start) {
    //checks if the player move is valid or game hasnt ended
      bool playervalid = false;
      
      if ((gameWon == false) && (moveCount != 9)) {
	while (playervalid == false) {
	  char input[3];

	  //asks for input from player x
	  cout << "Player X, your move (valid format: a1):" << std::endl;
	  cin.getline(input, 3);

	  std::tuple<int, int> coordinates = moveMapper(input);

	  //validity checker
	  if ((get<0>(coordinates) == 99) || (get<1>(coordinates) == 99)) {
	    cout << "Invalid Input!" << std::endl;
	  } else {
	    if (board[get<0>(coordinates)][get<1>(coordinates)] == 'O') {
	      cout << "Invalid Input!" << std::endl;
	    } else {

	      //if valid it places a move at the corrdinates and changes the move and other count variables
	      playervalid = true;
	      moveCount += 1;
	      board[get<0>(coordinates)][get<1>(coordinates)] = 'X';
	      printBoard(board);
	      //checks for win
	      if (gameCheck(board)) {
		cout << "Player X won" << std::endl;
		playerXwins += 1;
		gameWon = true;
	      }

	    }  

	  }

	}

      }

      //again, checks for player move is valid or game hasnt ended
      playervalid = false;

      if ((gameWon == false) && (moveCount != 9)) {
	while (playervalid == false) {
	  char input[3];

	  //asks for input from player o
	  cout << "Player O, your move (valid format: a1):" << std::endl;
	  cin.getline(input, 3);

	  std::tuple<int, int> coordinates = moveMapper(input);

	  //validity checker
	  if ((get<0>(coordinates) == 99) || (get<1>(coordinates) == 99)) {
	    cout << "Invalid Input!" << std::endl;
	  } else {
	    if (board[get<0>(coordinates)][get<1>(coordinates)] == 'X') {
	      cout << "Invalid Input!" << std::endl;
	    } else {

	      //if valid it places a move and changes the other variables
	      playervalid = true;
	      moveCount += 1;
	      board[get<0>(coordinates)][get<1>(coordinates)] = 'O';
	      printBoard(board);

	      //checks for win
	      if (gameCheck(board)) {
		cout << "Player O won" << std::endl;
		playerOwins += 1;
		gameWon = true;
	      }

	    }
      
	  }

	}

      }
      //if game was won, prints out stats
      if (gameWon) {
	cout << "Player X wins: ";
	cout << playerXwins << std::endl;

	cout << "Player O wins: ";
        cout << playerOwins << std::endl;

	cout << "Draws: ";
        cout << draws << std::endl;

        //reset game
	gameWon = false;
	moveCount = 0;
	
	for (int i=0; i<3; i++) {
	  for (int n=0; n<3; n++) {
	    board[i][n] = ' ';
	    if (n == 2) {
	      board[i][n+1] = '\0';
	    }
	  }
	}

	cout << "Here is the board:" << std::endl;
	printBoard(board);

      } else {
	//checks for draw
	if (moveCount == 9) {
	  cout << "Draw!" << std::endl;
	  draws += 1;
	  
	  cout << "Player X wins: ";
	  cout << playerXwins << std::endl;

	  cout << "Player O wins: ";
	  cout << playerOwins << std::endl;

	  cout << "Draws: ";
	  cout << draws << std::endl;

	  //reset game
	  gameWon = false;
	  moveCount = 0;

	  for (int i=0; i<3; i++) {
	    for (int n=0; n<3; n++) {
	      board[i][n] = ' ';
	      if (n == 2) {
		board[i][n+1] = '\0';
	      }
	    }
	  }

	  cout << "Here is the board:" << std::endl;
	  printBoard(board);

	}  
     }
      
  }

}
