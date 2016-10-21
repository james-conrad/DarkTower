#include "Board.h"

Board::Board()
{
}

Tile* Board::getTile(int id)
{
    if (id < 0 || id >= num_tiles)
        return nullptr;

    return &tiles[id];
}

Direction clockwise(Direction in)
{
    switch (in)
    {
        case Direction_North:
            return Direction_NorthEast;

        case Direction_NorthEast:
            return Direction_SouthEast;

        case Direction_SouthEast:
            return Direction_South;

        case Direction_South:
            return Direction_SouthWest;

        case Direction_SouthWest:
            return Direction_NorthWest;

        case Direction_NorthWest:
            return Direction_North;
    }

    return Direction_Count;
}


Direction counter_clockwise(Direction in)
{
    switch (in)
    {
        case Direction_North:
            return Direction_NorthWest;
            break;

        case Direction_NorthWest:
            return Direction_SouthWest;

        case Direction_SouthWest:
            return Direction_South;

        case Direction_South:
            return Direction_SouthEast;

        case Direction_SouthEast:
            return Direction_NorthEast;

        case Direction_NorthEast:
            return Direction_North;
    }

    return Direction_Count;
}
