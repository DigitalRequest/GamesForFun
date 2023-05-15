#include <stdio.h>
#include "items.h"

typedef struct
{
    int inv_id;
    int capacity;
    Item item;
} Inventory;

typedef struct
{
    int health;
    char sprite;
    int pos[2];
    Inventory inv;
} Player;
