#ifndef _GAME_OF_LIFE_H
#define _GAME_OF_LIFE_H

enum Cell_State { Dead, Alive };
typedef Cell_State** Board;
void printBoard(const Board, const size_t, const size_t);
Board initBoard(const size_t = 5, const size_t = 5);
void freeBoard(Board, const size_t = 5, const size_t = 5);
void mainLoop(Board, const size_t = 5, const size_t = 5);
void changeState(Board, const size_t, const size_t);
Cell_State newState(const Cell_State, const size_t);
size_t countNeighbors(const Board, const size_t, const size_t, const size_t, const size_t);
int isAlive(const Cell_State);

#endif // !_GAME_OF_LIFE_H