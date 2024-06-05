#ifndef _ITEM_H_
#define _ITEM_H_

#include "Utilities.h"

enum ItemType
{
    ITEM_GROW,
    ITEM_SHRINK,
    ITEM_SPEED_UP,
    ITEM_SPEED_DOWN
};

class Item
{
public:
    Vector2 position;
    ItemType type;

    Item(Vector2 pos, ItemType t) : position(pos), type(t) {}
};

#endif