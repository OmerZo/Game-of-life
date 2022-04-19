#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <chrono>
#include <thread>
#include "Game_of_life.h"

using namespace std;

int main()
{
    const size_t rows{ 10 };
    const size_t cols{ 10 };

    Board board = initBoard(rows, cols);
    mainLoop(board, rows, cols);
    freeBoard(board, rows, cols);
}

void printBoard(const Board board, const size_t rows, const size_t cols)
{
    char ch{};

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            ch = board[i][j] == Cell_State::Alive ? (char)254u : ' ';
            cout << " " << ch << " ";
        }
        
        cout << endl;
    }
}

Board initBoard(const size_t rows, const size_t cols)
{
    Board board = new Cell_State*[rows];
    Cell_State state{};
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < rows; i++)
    {
        board[i] = new Cell_State[cols];
    }

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            state = (rand() % 2) == 1 ? Cell_State::Alive : Cell_State::Dead;
            board[i][j] = state;
        }
    }

    return board;
}

void freeBoard(Board board, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        delete[] board[i];
    }

    delete[] board;
}

void mainLoop(Board board, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < 50; i++)
    {
        printBoard(board, rows, cols);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        changeState(board, rows, cols);
        system("cls");
    }
}

void changeState(Board board, const size_t rows, const size_t cols)
{
    Cell_State state{};
    size_t neighbors{ 0 };
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            neighbors = countNeighbors(board, rows, cols, i, j);
            board[i][j] = newState(board[i][j], neighbors);
        }
    }
}

Cell_State newState(const Cell_State state, const size_t neighbors)
{
    if (state == Cell_State::Alive)
    {
        if (neighbors <= 1 or neighbors > 3)
        {
            return Cell_State::Dead;
        }
    }
    else // state == Dead
    {
        if (neighbors == 3)
        {
            return Cell_State::Alive;
        }
    }

    return state;
}

size_t countNeighbors(const Board board, const size_t rows, const size_t cols, const size_t row_index, const size_t col_index)
{
    size_t neighbors{ 0 };

    if (row_index == 0) // first row
    {
        if (col_index == 0) //[0][0]
        {
            neighbors =
                isAlive(board[0][1]) +
                isAlive(board[1][0]) +
                isAlive(board[1][1]);
        }
        else if (col_index == cols - 1) // [0][last]
        {
            neighbors =
                isAlive(board[0][cols - 2]) +
                isAlive(board[1][cols - 1]) +
                isAlive(board[1][cols - 2]);
        }
        else //[0][middle]
        {
            neighbors =
                isAlive(board[0][col_index - 1]) +
                isAlive(board[1][col_index - 1]) +
                isAlive(board[1][col_index]) +
                isAlive(board[1][col_index + 1]) +
                isAlive(board[0][col_index + 1]);
        }
    }
    else if (row_index == rows - 1) // last row
    {
        if (col_index == 0) //[last][0]
        {
            neighbors =
                isAlive(board[rows - 2][0]) +
                isAlive(board[rows - 2][1]) +
                isAlive(board[rows - 1][1]);
        }
        else if (col_index == cols - 1) // [last][last]
        {
            neighbors =
                isAlive(board[rows - 2][cols - 2]) +
                isAlive(board[rows - 2][cols - 1]) +
                isAlive(board[rows - 1][cols - 2]);
        }
        else //[last][middle]
        {
            neighbors =
                isAlive(board[row_index - 1][col_index - 1]) +
                isAlive(board[row_index][col_index - 1]) +
                isAlive(board[row_index][col_index + 1]) +
                isAlive(board[row_index - 1][col_index + 1]) +
                isAlive(board[row_index - 1][col_index]);
        }
    }
    else // middle rows
    {
        neighbors =
            isAlive(board[row_index - 1][col_index - 1]) +
            isAlive(board[row_index][col_index - 1]) +
            isAlive(board[row_index + 1][col_index - 1]) +
            isAlive(board[row_index + 1][col_index]) +
            isAlive(board[row_index + 1][col_index + 1]) +
            isAlive(board[row_index][col_index + 1]) +
            isAlive(board[row_index - 1][col_index + 1]) +
            isAlive(board[row_index - 1][col_index]);
    }

    return neighbors;
}

int isAlive(const Cell_State state)
{
    return state == Cell_State::Alive ? 1 : 0;
}