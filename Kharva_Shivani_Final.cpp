// Shivani Kharva
// CIS 5 Online
// 23 July 2021
// Final Project - Tic Tac Toe

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// struct definition
struct Player
{
	string name;
	char symbol;
	// initializing the wins, losses, and ties to 0
	int wins = 0;
	int losses = 0;
	int ties = 0;
};

// function prototypes
bool isValid(int num, int min, int max);
int getChoice();
void showStats(Player p1, Player p2, int totalGames);
void quitApplication();
int playGame(Player& p1, Player& p2, int& totalGames);
void getPlayerInfo(Player& p1, Player& p2);
void displayBoard(char board[][3], int size);
void playerTurn(char board[][3], char playerSymbol);
bool gameOver(char board[][3], char p1Symbol, char p2Symbol, int totalMoves);
void displayWinner(char board[][3], Player& p1, Player& p2, int totalMoves);
void getPlayerInfoAI(Player& human, Player& computer);
void versusComputer(Player& human, Player& computer, int& totalGames);
void computerTurn(char board[][3], char computerSymbol);


int main()
{
	// Declarations
	Player player1, player2, human, computer;
	int choice, totalGames = 0, totalComputerGames = 0;  // initialized total games played
	char again;


	// Creating a switch for menu choice inside of do-while loop so player can play again
	do
	{
		// Calling getChoice
		choice = getChoice();

		switch (choice)
		{
			// Play game
			case 1:
				totalGames = playGame(player1, player2, totalGames);
				break;

			// Play with computer
			case 2:
				computer.name = "Computer";
				versusComputer(human, computer, totalComputerGames);
				break;
			
			// Show stats
			case 3:
				// Calling showStats
				showStats(player1, player2, totalGames);
				break;

			// Quit
			case 4:
				// Calling quitApplication
				quitApplication();
				break;
		}
		
		// Asking if they wish to repeat program
		cout << "Do you wish to play again? (y/n)\n";
		cin >> again;

		// Clear screen
		system("CLS");

	} while (again == 'Y' || again == 'y');

	return 0;
}


// isValid functions validates input
bool isValid(int num, int min, int max)
{
	if (num < min || num > max)
		return false;
	else
		return true;
}

// getChoice function displays welcome message, menu choices, and returns the choice of the user
int getChoice()
{
	int choice;

	// welcome message
	cout << "Welcome to the Tic Tac Toe game!\n\n";

	// menu choices
	cout << "Please select an option.\n";
	cout << "1. Play game\n";
	cout << "2. Play with computer (stats will be showed at end)\n";
	cout << "3. Show stats (not applicable when playing against computer)\n";
	cout << "4. Quit\n";
	cin >> choice;

	// input validation
	while (!isValid(choice, 1, 4))
	{
		cout << "Please enter a valid option between 1 and 4.\n";
		cin >> choice;
	}

	return choice;
}

int playGame(Player& p1, Player& p2, int& totalGames)
{
	// Declarations
	// initializing game board to contain asterisks
	char gameBoard[3][3] = { '*', '*', '*',
							 '*', '*', '*',
							 '*', '*', '*' };
	int totalMoves = 0;

	// Calling getPlayerInfo
	getPlayerInfo(p1, p2);

	// creating a loop to play the game
	do
	{
		// Calling displayBoard
		displayBoard(gameBoard, 3);
		if (totalMoves != 9 && !gameOver(gameBoard, p1.symbol, p2.symbol, totalMoves))
		{
			// Prompting player 1 to input their choice
			cout << "Player " << p1.name << " (" << p1.symbol << "), please input row and column number.\n";
			// Calling playerTurn
			playerTurn(gameBoard, p1.symbol);
			totalMoves += 1;
		}

		displayBoard(gameBoard, 3);
		if (totalMoves != 9 && !gameOver(gameBoard, p1.symbol, p2.symbol, totalMoves))
		{
			// Prompting player 2 to input their choice
			cout << "Player " << p2.name << " (" << p2.symbol << "), please input row and column number.\n";
			// Calling playerTurn
			playerTurn(gameBoard, p2.symbol);
			totalMoves += 1;
		}

	} while (!gameOver(gameBoard, p1.symbol, p2.symbol, totalMoves));

	// Calling displayWinner
	displayWinner(gameBoard, p1, p2, totalMoves);

	// Adding to the amount of games played so it can be used in showStats
	totalGames += 1;


	return totalGames;
}

// getPlayerInfo function gets the player's name and randonly assigns them X or O
void getPlayerInfo(Player& p1, Player& p2)
{
	// getting the names
	cout << "Please enter Player 1's name.\n";
	cin.ignore();
	getline(cin, p1.name);
	
	cout << "Please enter Player 2's name.\n";
	getline(cin, p2.name);

	// randomly assigning X or O
	int randNum, min = 1, max = 2;
	srand(time(0));

	randNum = min + rand() % (max - min + 1);
	if (randNum == 1)
	{
		p1.symbol = 'X';
		p2.symbol = 'O';
	}
	else if (randNum == 2)
	{
		p1.symbol = 'O';
		p2.symbol = 'X';
	}
}

// displayBoard function displays the game board
void displayBoard(char board[][3], int size)
{
	cout << setw(3) << " " << setw(6) << "Column" << right << setw(2) << "1" << setw(2) << "2" << setw(2) << "3" << endl;
	cout << left << "Row" << endl;

	for (int i = 0; i < size; i++)
	{
		cout << left << setw(9) << i + 1;

		for (int j = 0; j < 3; j++)
		{
			cout << right << setw(2) << board[i][j];
		}

		cout << endl;
	}
}

// playerTurn function lets the player take their turn
void playerTurn(char board[][3], char playerSymbol)
{
	int rowIndex, colIndex;

	cout << "Row: ";
	cin >> rowIndex;
	// Validating input
	while (!isValid(rowIndex, 1, 3))
	{
		cout << "INVALID INPUT. TRY AGAIN.\n";
		cin >> rowIndex;
	}
	cout << "Column: ";
	cin >> colIndex;
	// Validating input
	while (!isValid(colIndex, 1, 3))
	{
		cout << "INVALID INPUT. TRY AGAIN.\n";
		cin >> colIndex;
	}

	// making sure spot is open
	while (board[rowIndex-1][colIndex-1] != '*')
	{
		cout << "Please input a new row and column number that have not been filled.\n";
		cout << "Row: ";
		cin >> rowIndex;
		// Validating input
		while (!isValid(rowIndex, 1, 3))
		{
			cout << "INVALID INPUT. TRY AGAIN.\n";
			cin >> rowIndex;
		}
		cout << "Column: ";
		cin >> colIndex;
		// Validating input
		while (!isValid(colIndex, 1, 3))
		{
			cout << "INVALID INPUT. TRY AGAIN.\n";
			cin >> colIndex;
		}
	}
	
	// inputting into game board
	board[rowIndex-1][colIndex-1] = playerSymbol;
}

// playerWins function returns if the player has won
bool playerWins(char board[][3], char pSymbol)
{
	if (board[0][0] == pSymbol && board[0][1] == pSymbol && board[0][2] == pSymbol)
		return true;
	else if (board[1][0] == pSymbol && board[1][1] == pSymbol && board[1][2] == pSymbol)
		return true;
	else if (board[2][0] == pSymbol && board[2][1] == pSymbol && board[2][2] == pSymbol)
		return true;
	else if (board[0][0] == pSymbol && board[1][0] == pSymbol && board[2][0] == pSymbol)
		return true;
	else if (board[0][1] == pSymbol && board[1][1] == pSymbol && board[2][1] == pSymbol)
		return true;
	else if (board[0][2] == pSymbol && board[1][2] == pSymbol && board[2][2] == pSymbol)
		return true;
	else if (board[0][0] == pSymbol && board[1][1] == pSymbol && board[2][2] == pSymbol)
		return true;
	else if (board[0][2] == pSymbol && board[1][1] == pSymbol && board[2][0] == pSymbol)
		return true;
	else
		return false;
}

// gameOver function determines if a player has won or if there was a tie
bool gameOver(char board[][3], char p1Symbol, char p2Symbol, int totalMoves)
{
	if (playerWins(board, p1Symbol))
		return true;
	else if (playerWins(board, p2Symbol))
		return true;
	else if (totalMoves != 9)
		return false;
	else if (totalMoves == 9)
		return true;
}

// displayWinner function displays the winner
void displayWinner(char board[][3], Player& p1, Player& p2, int totalMoves)
{
	if (playerWins(board, p1.symbol))
	{
		cout << "Congratulations, " << p1.name << ", you have won the game!\n";
		p1.wins += 1;
	}
	else if (playerWins(board, p2.symbol))
	{
		cout << "Congratulations, " << p2.name << ", you have won the game!\n";
		p2.wins += 1;
	}
	else if (totalMoves == 9)
	{
		cout << "This game was a tie!\n";
		p1.ties += 1;
		p2.ties += 1;
	}
}

// showStats function shows the current stats of the players and total number of games played
void showStats(Player p1, Player p2, int totalGames)
{

	cout << "Player " << p1.name << "s stats:\n";
	cout << "Wins: " << p1.wins << endl;
	cout << "Losses: " << p1.losses << endl;
	cout << "Ties: " << p1.ties << endl << endl;

	cout << "Player " << p2.name << "s stats:\n";
	cout << "Wins: " << p2.wins << endl;
	cout << "Losses: " << p2.losses << endl;
	cout << "Ties: " << p2.ties << endl << endl;

	cout << "Total number of games played: " << totalGames << endl;
}

// quitApplication function quits the application
void quitApplication()
{
	cout << "You chose to quit the application.\n";
	exit(0);
}

// getPlayerInfoAI function gets player's name and assigns letter to human and computer
void getPlayerInfoAI(Player& human, Player& computer)
{
	// getting the names
	cout << "Please enter your name.\n";
	cin.ignore();
	getline(cin, human.name);

	// randomly assigning X or O
	int randNum, min = 1, max = 2;
	srand(time(0));

	randNum = min + rand() % (max - min + 1);
	if (randNum == 1)
	{
		human.symbol = 'X';
		computer.symbol = 'O';
	}
	else if (randNum == 2)
	{
		human.symbol = 'O';
		computer.symbol = 'X';
	}
}

void computerTurn(char board[][3], char computerSymbol)
{
	int rowIndex, colIndex;


	// middle
	if (board[1][1] == '*')
	{
		board[1][1] = computerSymbol;
	}
	// diagonal from left to right
	else if ((board[0][0] == board[1][1]) && (board[2][2] == '*'))
	{
		board[2][2] = computerSymbol;
	}
	else if ((board[0][0] == board[2][2]) && (board[1][1] == '*'))
	{
		board[1][1] = computerSymbol;
	}
	else if ((board[1][1] == board[2][2]) && (board[0][0] == '*'))
	{
		board[0][0] = computerSymbol;
	}
	// row 1
	else if ((board[0][0] == board[0][1]) && (board[0][2] == '*'))
	{
		board[0][2] = computerSymbol;
	}
	else if ((board[0][0] == board[0][2]) && (board[0][1] == '*'))
	{
		board[0][1] = computerSymbol;
	}
	else if ((board[0][1] == board[0][2]) && (board[0][0] == '*'))
	{
		board[0][0] = computerSymbol;
	}
	// column 1
	else if ((board[0][0] == board[1][0]) && (board[2][0] == '*'))
	{
		board[2][0] = computerSymbol;
	}
	else if ((board[0][0] == board[2][0]) && (board[1][0] == '*'))
	{
		board[1][0] = computerSymbol;
	}
	else if ((board[1][0] == board[2][0]) && (board[0][0] == '*'))
	{
		board[0][0] = computerSymbol;
	}
	// column 2
	else if ((board[0][1] == board[1][1]) && (board[2][1] == '*'))
	{
		board[2][1] = computerSymbol;
	}
	else if ((board[0][1] == board[2][1]) && (board[1][1] == '*'))
	{
		board[1][1] = computerSymbol;
	}
	else if ((board[1][1] == board[2][1]) && (board[0][1] == '*'))
	{
		board[0][1] = computerSymbol;
	}
	// column 3
	else if ((board[0][2] == board[1][2]) && (board[2][2] == '*'))
	{
		board[2][2] = computerSymbol;
	}
	else if ((board[0][2] == board[2][2]) && (board[1][2] == '*'))
	{
		board[1][2] = computerSymbol;
	}
	else if ((board[1][2] == board[2][2]) && (board[0][2] == '*'))
	{
		board[0][2] = computerSymbol;
	}
	// diagonal from right to left
	else if ((board[0][2] == board[1][1]) && (board[2][0] == '*'))
	{
		board[2][0] = computerSymbol;
	}
	else if ((board[0][2] == board[2][0]) && (board[1][1] == '*'))
	{
		board[1][1] = computerSymbol;
	}
	else if ((board[2][0] == board[1][1]) && (board[0][2] == '*'))
	{
		board[0][2] = computerSymbol;
	}
	// row 2
	else if ((board[1][0] == board[1][1]) && (board[1][2] == '*'))
	{
		board[1][2] = computerSymbol;
	}
	else if ((board[1][0] == board[1][2]) && (board[1][1] == '*'))
	{
		board[1][1] = computerSymbol;
	}
	else if ((board[1][1] == board[1][2]) && (board[1][0] == '*'))
	{
		board[1][0] = computerSymbol;
	}
	// row 3
	else if ((board[2][0] == board[2][1]) && (board[2][2] == '*'))
	{
		board[2][2] = computerSymbol;
	}
	else if ((board[2][0] == board[2][2]) && (board[2][1] == '*'))
	{
		board[2][1] = computerSymbol;
	}
	else if ((board[2][1] == board[2][2]) && (board[2][0] == '*'))
	{
		board[2][0] = computerSymbol;
	}
	// if no winning move or center not open -> random
	else
	{
		int randNum1, minRow = 1, maxRow = 3;
		srand(time(0));
		randNum1 = minRow + rand() % (maxRow - minRow + 1);
		rowIndex = randNum1;

		int randNum2, minCol = 1, maxCol = 3;
		srand(time(0));
		randNum2 = minCol + rand() % (maxCol - minCol + 1);
		colIndex = randNum2;

		// making sure spot is open and validating computer choice
		while (board[rowIndex - 1][colIndex - 1] != '*')
		{
			// row
			randNum1 = minRow + rand() % (maxRow - minRow + 1);
			rowIndex = randNum1;

			// column
			randNum2 = minCol + rand() % (maxCol - minCol + 1);
			colIndex = randNum2;
		}

		board[rowIndex - 1][colIndex - 1] = computerSymbol;
	}
}

void versusComputer(Player& human, Player& computer, int& totalGames)
{
	// Declarations
	// initializing game board to contain asterisks
	char gameBoard[3][3] = { '*', '*', '*',
							 '*', '*', '*',
							 '*', '*', '*' };
	int totalMoves = 0;

	// Calling getPlayerInfoAI
	getPlayerInfoAI(human, computer);

	// creating a loop to play the game
	do
	{
		// Calling displayBoard
		displayBoard(gameBoard, 3);
		if (totalMoves != 9 && !gameOver(gameBoard, human.symbol, computer.symbol, totalMoves))
		{
			// Prompting player 1 to input their choice
			cout << "Player " << human.name << " (" << human.symbol << "), please input row and column number.\n";
			// Calling playerTurn
			playerTurn(gameBoard, human.symbol);
			totalMoves += 1;
		}

		if (totalMoves != 9 && !gameOver(gameBoard, human.symbol, computer.symbol, totalMoves))
		{
			// Getting computer choice
			computerTurn(gameBoard, computer.symbol);
			totalMoves += 1;
		}

	} while (!gameOver(gameBoard, human.symbol, computer.symbol, totalMoves));

	// Calling displayWinner
	displayWinner(gameBoard, human, computer, totalMoves);

	// Adding to the amount of games played so it can be used in showStats
	totalGames += 1;

	displayBoard(gameBoard, 3);
	showStats(human, computer, totalGames);
}
