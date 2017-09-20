// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
#include "Tile.h"

TileList::TileList()
{
    maxSize = 10;
    tiles = new Tile[maxSize];
    size = 0;
}

TileList::~TileList()
{
    delete[] tiles;
}

void TileList::addTile(Tile tile)
{
    if(size == maxSize) {
        maxSize *= 2;
        Tile* temp = new Tile[maxSize];
        for(uint i = 0; i < size; i++) {
            temp[i] = tiles[i];
        }

        delete[] tiles;
        tiles = temp;
    }

    tiles[size++] = tile;

}

void TileList::drawAll(QGraphicsScene* scene) const
{
    for(uint i = 0; i< size; i++){
        tiles[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y) const
{
    for(int i = size-1; i >= 0; i--){
        if(tiles[i].contains(x, y)){
            return i;
        }
    }
    return -1;
}

void TileList::raise(int x, int y)
{
    int last = findBackwards(x, y);
    if (last != -1){
        Tile moveTile = tiles[last];
        for (uint n = last; n < size-1; n++){
            tiles[n] = tiles[n+1];
        }
        tiles[size-1] = moveTile;
    }
}

void TileList::lower(int x, int y)
{
    int last = findBackwards(x, y);
    if (last != -1) {
        Tile moveTile = tiles[last];
        for (uint n = last; n > 0; n--){
            tiles[n] = tiles[n-1];
        }
        tiles[0] = moveTile;
    }
}

void TileList::remove(int x, int y)
{
    int last = findBackwards(x, y);
    if (last != -1) {
        remove(last);
    }
}

void TileList::removeAll(int x, int y)
{
    int last = findBackwards(x, y);
    while (last != -1){
        remove(last);
        last = findBackwards(x, y);
    }
}

int TileList::findBackwards(int x, int y) const
{
    for(int i = size-1; i >= 0; i--){
        if(tiles[i].contains(x, y)){
            return i;
        }
    }
    return -1;
}

void TileList::remove(int i)
{
    if (i >= 0 && (uint) i < size) {
        for (uint n = i; n < size - 1; n++){
            tiles[n] = tiles[n+1];
        }
        size--;
    }
}
