//
// Created by GOD婴宁 on 2023/4/10.
//
#ifndef DEMO_GAME_H
#define DEMO_GAME_H

#define ROWS ROW+2
#define COLS COL+2
#define ROW 9
#define COL 9
#define GAME_EASY 10
#define TEST_MINE 80

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialboard(char board[ROWS][COLS], int row, int col, char set);

void DispalyBoard(char board[ROWS][COLS], int row, int col);

void SetMine(char board[ROWS][COLS], int row, int col);

void FindMine(char Hide[ROWS][COLS], char Show[ROWS][COLS], int row, int col);

#endif //DEMO_GAME_H
