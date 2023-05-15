#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "player.h"

typedef union
{
    char character;
    Item item;
    Weapon weapon;
    Potion potion;
    Player player;
} Map;

void show_map(int sizeX, int sizeY, Map map[sizeY][sizeX]);
int move_player(int *x, int *y, int sizeX, int sizeY, Map (*map)[sizeX], Player player, Inventory(*player_inv), int win);
void item_checker(Map item, Inventory(*player_inv));

int main()
{
    srand(time(NULL));

    Player player;
    player.sprite = 'P';
    Inventory player_inv[20];
    player_inv->capacity = 0;

    int win_key = rand() % 9999999;
    int sizeX = rand() % 10 + 50;
    int sizeY = rand() % 10 + 10;
    int placed_key = 0;
    int random;
    int win;
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
            random = rand() % 60;
            if (y == player.pos[0] && x == player.pos[1])
                map[y][x].character = player.sprite;
            else
            {
                switch (random)
                {
                case 0:
                    map[y][x].character = 'G';
                    map[y][x].item.desc = "Just a simple gate";
                    map[y][x].item.code = rand() % 9999999;
                    break;
                case 1:
                    map[y][x].character = 'K';
                    if (placed_key == 0)
                    {
                        map[y][x].item.desc = "A key that seens special?";
                        map[y][x].item.code = win_key;
                        placed_key = 1;
                    }
                    else
                    {
                        map[y][x].item.desc = "A key found in the dungeon";
                        map[y][x].item.code = rand() % 9999999;
                    }
                    break;
                case 2:
                    map[y][x].character = 'S';
                    map[y][x].item.desc = "A Old sword found in the dungeon";
                    map[y][x].item.code = rand() % 9999999;
                    map[y][x].weapon.damage = rand() % 12 + 1;
                    map[y][x].weapon.durability = rand() % 300 + 1;
                    break;
                case 3:
                    map[y][x].character = 'T';
                    map[y][x].item.desc = "A potion almost empty";
                    map[y][x].item.code = rand() % 9999999;
                    map[y][x].potion.stack = rand() % 5 + 1;
                    map[y][x].potion.heal = rand() % 10 + 1;
                    break;
                default:
                    if (random > 10 && random < 20)
                    {
                        map[y][x].character = ' ';
                    }
                    else
                    {
                        map[y][x].character = '-';
                    }
                    break;
                }
            }
        }
    }

    while (1)
    {
        show_map(sizeX, sizeY, map);
        int found = move_player(&player.pos[1], &player.pos[0], sizeX, sizeY, map, player, player_inv, win_key);

        if (found == 1)
        {
            printf("You found the key that you was searching for!!!\n");
            printf("You win the game!!!\n");
            return 0;
        }
    }
}

int move_player(int *x, int *y, int sizeX, int sizeY, Map (*map)[sizeX], Player player, Inventory(*player_inv), int win)
{
    char dir;
    printf("Please enter the direction you want to move, or type 'i' for inventory: ");
    scanf(" %c", &dir);

    switch (dir)
    {
    case 'd':
        if (*x < sizeX - 1)
        {
            map[*y][*x].character = '-';
            item_checker(map[*y][*x + 1], player_inv);
            (*x)++;
            map[*y][*x].character = player.sprite;
        }
        break;
    case 'a':
        if (*x > 0)
        {
            map[*y][*x].character = '-';
            item_checker(map[*y][*x - 1], player_inv);
            (*x)--;
            map[*y][*x].character = player.sprite;
        }
        break;
    case 's':
        if (*y < sizeY - 1)
        {
            map[*y][*x].character = '-';
            item_checker(map[*y + 1][*x], player_inv);
            (*y)++;
            map[*y][*x].character = player.sprite;
        }
        break;
    case 'w':
        if (*y > 0)
        {
            map[*y][*x].character = '-';
            item_checker(map[*y - 1][*x], player_inv);
            (*y)--;
            map[*y][*x].character = player.sprite;
        }
        break;
    case 'i':
        printf("Inventory:\n");
        for (int x = 0; x < player_inv->capacity; x++)
        {
            printf("    Code: %d, ", player_inv[x].item.code);
            printf("Sprite: %c, ", player_inv[x].item.sprite);
            printf("Description: %s\n", player_inv[x].item.desc);
            if (player_inv[x].item.code == win && player_inv[x].item.sprite == 'K')
            {
                return 1;
            }
        }
        break;
    }
    return 0;
}

void item_checker(Map item, Inventory(*player_inv))
{
    if (player_inv->capacity < 20)
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
            player_inv[player_inv->capacity].item = item.item;
            player_inv->capacity += 1;
            break;
        case 'S':
            printf("You found a sword!\n");
            printf("Description: %s\n", item.item.desc);
            printf("Power: %d\n", item.weapon.damage);
            player_inv[player_inv->capacity].item = item.item;
            player_inv->capacity += 1;
            break;
        case 'T':
            printf("You found a potion!\n");
            printf("Description: %s\n", item.item.desc);
            printf("Heal: %d\n", item.potion.heal);
            player_inv[player_inv->capacity].item = item.item;
            player_inv->capacity += 1;
            break;
        default:
            if (item.character != '-')
                printf("ERROR\n");
            return;
        }
    }
    else
    {
        printf("Sorry, max capacity of inventory reached\n");
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
