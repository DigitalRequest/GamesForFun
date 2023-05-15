#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "player.h"
#include "items.h"

typedef union
{
    char character;
    Item item;
    Weapon weapon;
    Potion potion;
    Player player;
} Map;

void show_map(int sizeX, int sizeY, Map map[sizeY][sizeX]);
void move_player(int *x, int *y, int sizeX, int sizeY, Map (*map)[sizeX], Player player);
void item_checker(Map item);

int main()
{
    srand(time(NULL));

    Player player;
    Item gate;
    Item key;
    Weapon sword;
    Potion potion;

    player.sprite = 'P';
    /*
    gate.sprite = 'G';
    key.sprite = 'K';
    sword.item.sprite = 'S';
    sword.item.desc = "A Old sword found in the dungeon";
    potion.item.sprite = 'T';
    potion.item.desc = "A potion almost empty";
    */

    int sizeX = rand() % 10 + 50;
    int sizeY = rand() % 10 + 10;
    int random;
    Map map[sizeY][sizeX];

    player.pos[0] = rand() % 10 + 50;
    player.pos[1] = rand() % 10 + 10;

    while (player.pos[0] > sizeY || player.pos[1] > sizeX)
    {
        player.pos[0] = rand() % 10;
        player.pos[1] = rand() % 50;
    }

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            random = rand() % 90;
            if (y == player.pos[0] && x == player.pos[1])
                map[y][x].character = player.sprite;
            else
            {
                switch (random)
                {
                case 0:
                    map[y][x].character = 'G';
                    map[y][x].item.desc = "Just a simple gate";
                    map[y][x].item.code = rand() % 123213;
                    break;
                case 1:
                    map[y][x].character = 'K';
                    map[y][x].item.desc = "A key found in the dungeon";
                    map[y][x].item.code = rand() % 123213;
                    break;
                case 2:
                    map[y][x].character = 'S';
                    map[y][x].item.desc = "A Old sword found in the dungeon";
                    map[y][x].item.code = rand() % 123123;
                    map[y][x].weapon.damage = rand() % 12 + 1;
                    map[y][x].weapon.durability = rand() % 300 + 1;
                    break;
                case 3:
                    map[y][x].character = 'T';
                    map[y][x].item.desc = "A potion almost empty";
                    map[y][x].item.code = rand() % 123213;
                    map[y][x].potion.stack = rand() % 5 + 1;
                    map[y][x].potion.heal = rand() % 10 + 1;
                    break;
                default:
                    if (random > 20 && random < 40)
                        map[y][x].character = ' ';
                    else
                        map[y][x].character = '-';
                    break;
                }
            }
        }
    }

    while (1)
    {
        show_map(sizeX, sizeY, map);
        move_player(&player.pos[1], &player.pos[0], sizeX, sizeY, map, player);
    }
}

void move_player(int *x, int *y, int sizeX, int sizeY, Map (*map)[sizeX], Player player)
{
    char dir;
    printf("Please enter the direction you want to move: ");
    scanf(" %c", &dir);

    printf("(%d, %d)\n", *y, *x);
    printf("(%d, %d)\n", sizeY, sizeX);
    switch (dir)
    {
    case 'd':
        if (*x < sizeX - 1)
        {
            map[*y][*x].character = '-';
            item_checker(map[*y][*x + 1]);
            (*x)++;
            map[*y][*x].character = player.sprite;
        }
        break;
    case 'a':
        if (*x > 0)
        {
            map[*y][*x].character = '-';
            item_checker(map[*y][*x - 1]);
            (*x)--;
            map[*y][*x].character = player.sprite;
        }
        break;
    case 's':
        if (*y < sizeY - 1)
        {
            map[*y][*x].character = '-';
            item_checker(map[*y + 1][*x]);
            (*y)++;
            map[*y][*x].character = player.sprite;
        }
        break;
    case 'w':
        if (*y > 0)
        {
            map[*y][*x].character = '-';
            item_checker(map[*y - 1][*x]);
            (*y)--;
            map[*y][*x].character = player.sprite;
        }
        break;
    }
}

void item_checker(Map item)
{
    switch (item.character)
    {
    case 'G':
        printf("You found a gate!\n");
        printf("Description: %s\n", item.item.desc);
        break;
    case 'K':
        printf("You found a key!\n");
        printf("Description: %s\n", item.item.desc);
        break;
    case 'S':
        printf("You found a sword!\n");
        printf("Description: %s\n", item.item.desc);
        printf("Power: %d\n", item.weapon.damage);
        break;
    case 'T':
        printf("You found a potion!\n");
        printf("Description: %s\n", item.item.desc);
        printf("Heal: %d\n", item.potion.heal);
        break;
    default:
        if (item.character != '-')
            printf("ERROR\n");
        return;
    }
}

void show_map(int sizeX, int sizeY, Map map[sizeY][sizeX])
{
    printf("\n");
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX + 1; x++)
        {
            if (x < sizeX)
                printf("%c", map[y][x]);
            else
                printf("\n");
        }
    }
    printf("\n");
}