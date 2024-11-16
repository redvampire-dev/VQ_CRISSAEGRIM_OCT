
#ifndef RPG_H_
#define RPG_H_

#include <stdint.h>
#include <stdbool.h>
#include "../include/random.h"

#define ITEM_SIZE 2 //Number of items in the game


enum ItemTypes
{
    NOTHING = 0,
    SWORD = 1,
    STAFF = 2,
    AXE = 3,
    NUNCHUCK = 4,
    BODY = 5,
    SHIELD = 6,
    HEAD = 7,
    ACCESSORY = 8,
    CLOAK = 9,
    DRINKHP = 10,
    DRINKVP = 11,
    CUREPOISON = 12,
    CUREWOUND = 13,
    MAGIC = 14,
    COFFIN = 15

};

static uint16_t LEVEL_TABLE[] = {
    0, 113, 345, 632, 973, 1409, 1876, 2390, 2946, 3544,4180,5564, 6309, 7086, 7896, 8737, 9608, 10509, 12397, 18974, 55555
};

typedef struct {
    uint8_t held[2];
    uint16_t gold;
} ItemsHeld;

typedef struct {
    uint16_t hp;

    uint8_t str;
    uint8_t con;
    uint8_t itl;
    uint8_t wil;
    uint8_t agi;
    uint8_t lck;

    bool vampire;
    uint8_t canEquip;
    uint8_t weaponProfiencies;
    uint8_t canCast;
}characterStats;

typedef struct
{
    //Stats that matter
    uint16_t hp;
    uint8_t mp;
    uint8_t vp;
    uint16_t xp;

    //Status effects
    bool wounded;
    bool bleed;
    bool poison;
    bool fright;
    bool sunburn;
    bool frenzy;
    bool ghoul;
    bool bloodAbsorb;

    //Equipment
    uint8_t head;
    uint8_t body;
    uint8_t handR;
    uint8_t handL;
    uint8_t acc1;
    uint8_t acc2;
}characterStatus;

typedef struct
{
    //ItemTypes type;
    char* name;
    char* description;

    //Item data
    enum ItemTypes type;
    uint8_t restoreValue;


    //Buffs
    int8_t att;
    int8_t def;
    int8_t str;
    int8_t con;
    int8_t itl;
    int8_t wil;
    int8_t agi;
    int8_t lck;
}item;

typedef struct {
    char* name;
    char* description;
    //Elements element;

    bool causeBloodAbsorb;
    bool causePoison;
    bool causeWound;
    bool causeBleed;
    bool curePoison;
    bool cureVampireEffects;
    bool damageAll;
    bool cureAll;
} skill;

extern item items[ITEM_SIZE];

uint8_t Level(uint16_t xp);

uint8_t ATT(characterStats* base, characterStatus* status);
uint8_t DEF(characterStats* base, characterStatus* status);
uint8_t VAM(characterStats* base, characterStatus* status);
uint8_t CON(characterStats* base, characterStatus* status);
uint8_t INL(characterStats* base, characterStatus* status);
uint8_t WIL(characterStats* base, characterStatus* status);
uint8_t LCK(characterStats* base, characterStatus* status);
uint8_t AGI(characterStats* base, characterStatus* status);

uint8_t BasicAttack(characterStats* AtkBase, characterStatus* AtkStatus, characterStats* DefBase, characterStatus* DefStatus);
bool Evasion(characterStats* AtkBase, characterStatus* AtkStatus, characterStats* DefBase, characterStatus* DefStatus);

bool AddItem(ItemsHeld*, uint8_t, uint8_t);
bool UseItem(ItemsHeld*, uint8_t);

#endif
