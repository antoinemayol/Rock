#pragma once

void print_grid(int *grid);
int absentOnRow(int k,int *grid,int i);
int absentOnCol(int k,int *grid,int j);
int absentOnBloc(int k, int *grid,int i,int j);
int backtracking(int *grid,int position);


