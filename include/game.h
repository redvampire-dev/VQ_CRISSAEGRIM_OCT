#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../include/color.h"
#include "../include/random.h"
#include "../include/rpg.h"

#define MESSAGE_TIMEOUT 100

#define STATE_INIT      0
#define STATE_TITLE     1
#define STATE_MAP       2
#define STATE_MENU      3
#define STATE_DEAD      4
#define STATE_EXIT      15

#define CHEST           2
#define CHEST_OPEN      3
#define NPC             4
#define PC              255

#define D_UP            0
#define D_LEFT          1
#define D_DOWN          2
#define D_RIGHT         3

#define TILE_WIDTH      64

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t icon;
    uint16_t angle;
} actor;

typedef struct {
    uint8_t behavior;
    uint8_t type;
    characterStats stats;
    characterStatus status;
    actor Actor;
} npc;

typedef struct {
    actor Actor;
    uint8_t itemId;
    uint16_t quantity;
    uint8_t id;
    bool opened;
} Chest;

typedef struct {
    bool b, y, start, select, up, down, left, right, a, x, l, r;
} buttons;

typedef struct {
    buttons Buttons;
    actor Player;
    ItemsHeld itemsHeld;
    characterStats playerStat;
    characterStatus playerStatus;
    bool moved;
    uint16_t turns;
    char message [151];
    uint8_t gameState;
    bool inMenu;
    uint8_t messageTimer;
} state;

void gameinit();
void title();
void initMapActors();
void update();
void advanceTurn();
void updateNPCs();
void printMessage(char*);
void displayMap();
void displayMenu();
void setActor(actor*, uint8_t, uint8_t);
void moveActor(actor*, int8_t, int8_t);
void interact(int8_t, int8_t);
uint8_t checkMap(uint8_t, uint8_t);
void attackPlayer(uint8_t);


#endif // GAME_H_
