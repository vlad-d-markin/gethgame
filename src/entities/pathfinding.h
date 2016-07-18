#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "../map.h"
#include "../direction.h"
#include <vector>
#include <list>
#include "mob.h"

struct Cell
{
    oxygine::VectorT2<int> position;
    int F;
    int G;
    int H;
    Cell *parent;
    bool operator==(Cell that)
    {
        if( position == that.position &&
            F == that.F &&
            G == that.G &&
            H == that.H &&
            parent == that.parent)
            return true;
        else
            return false;
    }
    bool operator!=(Cell that)
    {
        return (! operator==(that));
    }
};

class pathFinding
{
private:
    std::vector< std::vector<bool> > collisionMap;
    int numberOfRows;
    int numberOfColumns;
    int calculateCost(VectorT2<int> _vector) const;
    void calculateG(Cell *_cell) const;
    void calculateH(Cell *_cell) const;
    void calculateF(Cell *_cell) const;
    std::list<Cell> openList;
    std::list<Cell> closedList;
    Cell start;
    Cell end;
    Cell *current;
    const int sideCost = 10;
    const int cornerCost = 14;
    void checkCellsAround(Cell *_cell);
    void checkCell(VectorT2<int> _position);
    bool isInList(VectorT2<int> _position, std::list<Cell> *_list, Cell *_cellForCheck = NULL);
    Map *mapa;

public:
    pathFinding(Map *map);
    std::vector<Direction> findPath(const VectorT2<int> _start, const VectorT2<int> _end);
};

#endif // PATHFINDING_H
