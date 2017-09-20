/**
  This file contains all the necessary code to run the game of life
  In short the game will kill or create cells on a grid depending on the
  amount of alive neighbours.
  **/

#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <stack>
#include "life.h"

using namespace std;

const char DEAD = '-';
const char ALIVE = 'X';

/**
 * @brief main
 * @return
 */
int main() {

    cout << "Welcome to the TDDD86 Game of Life," << endl
         << "a simulation of the lifecycle of a bacteria colony." << endl
         << "Cells (X) live and die by the following rules:" << endl
         << "- A cell with 1 or fewer neighbours dies." << endl
         << "- Locations with 2 neighbours remain stable." << endl
         << "- Locations with 3 neighbours will create life." << endl
         << "- A cell with 4 or more neighbours dies." << endl;

    cout << endl << "Grid input file name? ";
    string fileName;
    Grid<char> grid;
    cin >> fileName;
    loadGrid(fileName, grid);
    printGrid(grid);
    while(true){
        cout << "a)nimate, t)ick, q)uit" << endl;
        string option;
        cin >> option;
        if(option == "a"){
            animate(grid);
        }
        else if(option == "t"){
            evolve(grid);
            printGrid(grid);
        }
        else if(option == "q"){
            cout << "Have a nice Life!" << std::endl;
            return 0;
        }
    }
    return 0;
}

/**
 * @brief animate Animate the grid evolving, i.e just evolve
 * the grid and print it between each evolvement.
 * @param grid The grid to run the animation on
 */
void animate(Grid<char>& grid){
    clearConsole();
    while(true){
        evolve(grid);
        printGrid(grid);
        pause(500);
        clearConsole();
    }
}

/**
 * @brief getAliveNeighbours Gets the amount of cell-neighbours that are alive to the given cell
 * @param grid The grid to look in
 * @param refX The X cord of the reference cell
 * @param refY The Y cord of the reference cell
 * @return
 */
int getAliveNeighbours(const Grid<char>& grid, int refX, int refY){
    int amount = 0;
    for(int x = refX -1; x<=refX +1; x++){
        for(int y = refY -1; y <= refY + 1; y++){
            if(grid.inBounds(y, x) && !(x == refX && y == refY)){
                if(grid.get(y,x) == ALIVE){
                    amount++;
                }
            }
        }
    }
    return amount;
}


/**
 * @brief evolve Evolves the given grid to the next state based on the amount
 * of alive neighbours
 * @param grid The grid to be evolved
 */
void evolve(Grid<char>& grid){
    int height = grid.numRows();
    int width = grid.numCols();
    Grid<char> tempGrid;
    tempGrid.resize(height, width);
    for(int col = 0; col < height; col++){
        for(int row = 0; row < width; row++){
            int amountNeighbours = getAliveNeighbours(grid, row, col);
            if(amountNeighbours == 2){
                tempGrid.set(col, row, grid.get(col, row));
            }
            else if(amountNeighbours == 3){
                tempGrid.set(col, row, ALIVE);
            }
            else {
                tempGrid.set(col,row, DEAD);
            }
        }
    }
    grid.deepCopy(tempGrid);
}


/**
 * @brief printGrid Prints the given grid to the console
 * @param grid The grid to be printed
 */
void printGrid(const Grid<char>& grid){
    int height = grid.numRows();
    int width = grid.numCols();
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            cout << grid.get(h,w);
        }
        cout << endl;
    }
}


/**
 *
 * @brief Changes the grid to the default size and look given by the file
 * @param fileName The name of the file containing the grid
 * @param grid The grid to be modified
 */
void loadGrid(const string& fileName, Grid<char>& grid){
    ifstream lifeFile(fileName);
    if(lifeFile.is_open()){
        int height;
        int width;
        string input;
        getline(lifeFile, input);
        height = stoi(input);
        getline(lifeFile, input);
        width = stoi(input);
        grid.resize(height, width);
        for(int h = 0; h < height; h++){
            getline(lifeFile, input);
            for(int w = 0; w < width; w++){
                grid.set(h, w, input[w]);
            }
        }
    }
}
