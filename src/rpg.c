
#include "../include/rpg.h"

item items[ITEM_SIZE] =
{
    {
        .name = "TEST",
        .description = "Test article",
        .type = ACCESSORY,
        .restoreValue = 25,
        .att = 0,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    },   {
        .name = "Potion",
        .description = "Swirling blue liquid. DRINK to heal +16 HP",
        .type = DRINKHP,
        .restoreValue = 12,
        .att = 0,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "S Blood",
        .description = "Dark Red blood. DRINK to gain +4 VP",
        .type = DRINKVP,
        .restoreValue = 4,
        .att = 0,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "L Blood",
        .description = "Dark Red Blood. DRINK to heal +16 VP",
        .type = DRINKVP,
        .restoreValue = 16,
        .att = 0,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Kukri",
        .description = "Curved knife",
        .type = SWORD,
        .restoreValue = 0,
        .att = 20,
        .def = 1,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Basilard",
        .description = "Basic short sword",
        .type = SWORD,
        .restoreValue = 0,
        .att = 1,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Short Sword",
        .description = "Common Short Sword",
        .type = SWORD,
        .restoreValue = 0,
        .att = 2,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Gladius",
        .description = "Swirling blue liquid. DRINK to heal +16 HP",
        .type = SWORD,
        .restoreValue = 0,
        .att = 4,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Saber",
        .description = "Swirling blue liquid. DRINK to heal +16 HP",
        .type = SWORD,
        .restoreValue = 12,
        .att = 9,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Broadsword",
        .description = "Swirling blue liquid. DRINK to heal +16 HP",
        .type = SWORD,
        .restoreValue = 12,
        .att = 14,
        .def = -2,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Luminus",
        .description = "Swirling blue liquid. DRINK to heal +16 HP",
        .type = SWORD,
        .restoreValue = 12,
        .att = 26,
        .def = 0,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Dk Blade",
        .description = "Swirling blue liquid. DRINK to heal +16 HP",
        .type = SWORD,
        .restoreValue = 12,
        .att = 35,
        .def = 2,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Yendor Swd",
        .description = "Swirling blue liquid. DRINK to heal +16 HP",
        .type = SWORD,
        .restoreValue = 12,
        .att = 42,
        .def = 6,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }, {
        .name = "Crissaegrim",
        .description = "Swirling blue liquid. DRINK to heal +16 HP",
        .type = SWORD,
        .restoreValue = 12,
        .att = 36,
        .def = 1,
        .str = 0,
        .con = 0,
        .itl = 0,
        .wil = 0,
        .agi = 0,
        .lck = 0
    }
};

uint8_t Level(uint16_t xp)
{
    uint8_t level = 1, l;
    for(l = 1; l < 21; l++){
        if (LEVEL_TABLE[level] < xp) { level = l; }
    }
    return level;
}

uint8_t ATT(characterStats* base, characterStatus* status)
{
    //Get max ATT and str
    uint8_t maxATT = items[status->handR].att+items[status->handL].att;
    uint8_t str = base->str;

    //Half strength if wounded and or poisoned
    if(status->wounded) { str = str/2; }
    if(status->poison)  { str = str/2; }

    //Add in bonus str
    str += items[status->handR].str
         + items[status->handL].str
         + items[status->head].str
         + items[status->body].str
         + items[status->acc1].str
         + items[status->acc2].str;

      if(str == 255)    { return str;                  }
      if (maxATT > str) { return str+(maxATT-(str/2)); } //if Strength is less than max ATT, return a reduced attack
    else                { return str+maxATT;           }
}

uint8_t DEF(characterStats* base, characterStatus* status)
{
    uint8_t def = items[status->handR].def
                + items[status->handL].def
                + items[status->head].def
                + items[status->body].def
                + items[status->acc1].def
                + items[status->acc2].def;

    uint8_t con = base->con + items[status->handR].con
                            + items[status->handL].con
                            + items[status->head].con
                            + items[status->body].con
                            + items[status->acc1].con
                            + items[status->acc2].con;

    return con + def;
}

uint8_t VAM(characterStats* base, characterStatus* status)
{
    uint8_t con = base->con;
    uint8_t wil = base->wil;

    con += items[status->handR].con
         + items[status->handL].con
         + items[status->head].con
         + items[status->body].con
         + items[status->acc1].con
         + items[status->acc2].con;

    wil += items[status->handR].wil
         + items[status->handL].wil
         + items[status->head].wil
         + items[status->body].wil
         + items[status->acc1].wil
        + items[status->acc2].wil;

    return con/4+wil/3;
}

uint8_t CON(characterStats* base, characterStatus* status)
{
    return base->con
        + items[status->handR].con
        + items[status->handL].con
        + items[status->head].con
        + items[status->body].con
        + items[status->acc1].con
        + items[status->acc2].con;
}

uint8_t INL(characterStats* base, characterStatus* status)
{
    return base->itl
        + items[status->handR].itl
        + items[status->handL].itl
        + items[status->head].itl
        + items[status->body].itl
        + items[status->acc1].itl
        + items[status->acc2].itl;
}

uint8_t WIL(characterStats* base, characterStatus* status)
{
    return base->wil
        + items[status->handR].wil
        + items[status->handL].wil
        + items[status->head].wil
        + items[status->body].wil
        + items[status->acc1].wil
        + items[status->acc2].wil;
}

uint8_t LCK(characterStats* base, characterStatus* status)
{
    return base->lck
        + items[status->handR].lck
        + items[status->handL].lck
        + items[status->head].lck
        + items[status->body].lck
        + items[status->acc1].lck
        + items[status->acc2].lck;
}

uint8_t AGI(characterStats* base, characterStatus* status)
{
    return base->agi
        + items[status->handR].agi
        + items[status->handL].agi
        + items[status->head].agi
        + items[status->body].agi
        + items[status->acc1].agi
        + items[status->acc2].agi;
}

uint8_t BasicAttack(characterStats* AtkBase, characterStatus* AtkStatus, characterStats* DefBase, characterStatus* DefStatus)
{
    uint8_t attack = ATT(AtkBase, AtkStatus);
    uint8_t def = DEF(DefBase,DefStatus);
    if((RNGCall(0) <  12 + LCK(AtkBase, AtkStatus) || (AtkStatus->hp < AtkBase->hp/8 && RNGCall(0) < 43)) && attack <= 250)
    {
        attack += attack%16;
    }
    if (def >= attack)
    { return 0; }
    else
    { return attack-def;}
}

bool Evasion(characterStats* AtkBase, characterStatus* AtkStatus, characterStats* DefBase, characterStatus* DefStatus)
{
    return AGI(DefBase,DefStatus)>AGI(AtkBase,AtkStatus) || RNGCall(0) < 21;
}

bool AddItem(ItemsHeld* inv, uint8_t id, uint8_t quantity) {
         if (id >= ITEM_SIZE)              { return false; }
    else if (inv->held[id]==255 )          { return false; }
    else if (inv->held[id]+quantity > 255) { inv->held[id]=255; return true; }
    else { inv->held[id]+=quantity; return true; }
}

bool UseItem(ItemsHeld* inv, uint8_t id){
    if (inv->held[id] == 0) { return false; }
    else {
        inv->held[id]--;
        switch(items[id].type){
            case DRINKHP:
            default:
                printString("THATS ALL IT DOES NOW!!! WHAT THE DICK?!?", 50, 50);
                break;
        }

    }

}
