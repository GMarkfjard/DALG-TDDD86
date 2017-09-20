#include<string>
#ifndef LIFE_H
#define LIFE_H

#endif // LIFE_H

void animate(Grid<char>& grid);
int getAliveNeighbours(const Grid<char>& grid, int refX, int refY);
void evolve(Grid<char>& grid);
void printGrid(const Grid<char>& grid);
void loadGrid(const std::string& fileName, Grid<char>& grid);
