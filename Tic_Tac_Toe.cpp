#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3

#define computermove 'O'
#define humanmove 'x'
void showboard(char board[][SIDE])
{
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}
void initialise(char board[SIDE][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            board[i][j] = '*';
        }
    }
}
void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
        printf("COMPUTER has won\n");
    else
        printf("HUMAN has won\n");
}

void showInstructions()
{
    cout << "choose a cell numbered from 1 to 9 as below and play\n\n";

    cout << "\t1|2|3" << endl;
    cout << "\t-----" << endl;
    cout << "\t4|5|6" << endl;
    cout << "\t-----" << endl;
    cout << "\t7|8|9" << endl;
}

bool horizontalCross(char board[SIDE][SIDE])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }
    return false;
}

bool verticalCross(char board[SIDE][SIDE])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] &&
                board[1][i] == board[2][i] &&
                board[0][i] != '*')
            return true;
    }
    return false;
}

bool diagonalCross(char board[SIDE][SIDE])
{
    if (board[0][2] == board[1][1] &&
            board[1][1] == board[2][0] &&
            board[0][2] != '*')
        return true;

    if (board[0][0] == board[1][1] &&
            board[1][1] == board[2][2] &&
            board[0][0] != '*')
        return true;

    return false;


}

bool gameOver(char board[SIDE][SIDE])
{
    return (horizontalCross(board) || verticalCross(board) || diagonalCross(board));
}
int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
            return -10;
        if (isAI == false)
            return +10;
    }
    else
    {
        if (depth < 9)
        {
            if (isAI == true)
            {
                bestScore = -999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = computermove;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if (score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = humanmove;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
    return false;
}
int bestMove(char board[SIDE][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = computermove;
                score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';
                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return (x * 3) + y;
}

void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;
    initialise(board);
    showInstructions();
    while (gameOver(board) == false && moveIndex != SIDE * SIDE)
    {
        int n;
        if (whoseTurn == COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = computermove;
            printf("COMPUTER has put a %c in cell %d\n\n", computermove,
                   n + 1);
            showboard(board);
            moveIndex ++;
            whoseTurn = HUMAN;
        }
        else if (whoseTurn == HUMAN)
        {
            printf("You can insert in the following positions : ");
            for (int i = 0; i < SIDE; i++)
                for (int j = 0; j < SIDE; j++)
                    if (board[i][j] == '*')
                        printf("%d ", (i * 3 + j) + 1);
            printf("\n\nEnter the position = ");
            scanf("%d", &n);
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if (board[x][y] == '*' && n < 9 && n >= 0)
            {
                board[x][y] = humanmove;
                printf ("\nHUMAN has put a %c in cell %d\n\n", humanmove,
                        n + 1);
                showboard(board);
                moveIndex ++;
                whoseTurn = COMPUTER;
            }
            else if (board[x][y] != '*' && n < 9 && n >= 0)
            {
                printf("\nPosition is occupied, select any one place from the available places\n");
            }
            else if (n < 0 || n > 8)
            {
                printf("Invalid position\n");
            }
        }
    }
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        printf("It's a draw\n");
    else
    {
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;
        declareWinner(whoseTurn);
    }
}


int main()
{

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\tTIC-TAC-TOE" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    char cont = 'y';

    do {
        cout << "Do you want to start frist (y/n):\n";
        cin >> cont;
        if (cont == 'n' || cont == 'N')
            playTicTacToe(COMPUTER);
        else if (cont == 'y' || cont == 'Y')
            playTicTacToe(HUMAN);
        else
            cout << "\nyou have selected invalid choice :) try again!";

        cout << "Do you want to quit";
        cin >> cont;
    } while (cont == 'n' || cont == 'N');

    return 0;
}
