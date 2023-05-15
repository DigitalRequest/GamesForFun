#include <stdio.h>

typedef struct
{
    char sprite;
    char *desc;
    int code;
} Item;

typedef struct
{
    Item item;
    int damage;
    int durability;
} Weapon;

typedef struct
{
    Item item;
    int stack;
    int heal;
} Potion;