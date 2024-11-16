#include "../include/game.h"

state State;

char randtext [5];
char d20text [20];

uint8_t protoMap[] = {
    1,1,1,1,1,1,1,1,
    1,0,0,1,0,1,0,0,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};


Chest chests[] = {
    {   .Actor = {.x = 3, .y = 3},
        .itemId = 1,
        .quantity = 255,
        .opened = true
    }, {
        .Actor = {.x = 2, .y = 5},
        .itemId = 1,
        .quantity = 1,
        .opened = false
    }
};

npc NPCS[] = {
    {
        .Actor = {.x = 5, .y = 4},
        .behavior = 1,
        .stats = {
                    .hp = 13,
                    .str = 2,
                    .con = 3,
                    .agi = 2,
                },
        .status = {
                    .hp = 13,
                 }
    }, {
        .Actor = {.x = 6, .y = 6},
        .behavior = 1,
        .stats = {
                    .hp = 13,
                    .str = 2,
                    .con = 3,
                    .agi = 2,
                },
        .status = {
                    .hp = 13,
                 }
    },
};


void gameinit() {
    State.playerStatus.xp = 0;
    State.playerStat.hp = 67;
    State.playerStatus.hp = State.playerStat.hp;
}

void title() {
    printString(".  .                    .__.          , ", 0,0);
    printString("\\  / _.._ _ ._ *._. _   |  |. . _  __-+-", 0,8);
    printString(" \\/ (_][ | )[_)|[  (/,  |__\\(_|(/,_) | ", 0,16);
    printString("            |                           ", 0,24);

}

void update() {
    printString(State.message, 0, 150);

       if (State.messageTimer > MESSAGE_TIMEOUT) { strncpy(State.message, "", 51); }
    else { State.messageTimer++; }

    printString(randtext, 220,184);
    printString(d20text,  220,192);

    if(State.moved == 0 ) {
        if(State.inMenu == 0) {
                     if (State.Buttons.up    > 0) {
                        moveActor(&State.Player,  0, -1);
                        interact(State.Player.x  ,State.Player.y-1);
                        State.moved = 1;
                        advanceTurn(); }
                else if (State.Buttons.down  > 0) {
                        moveActor(&State.Player,  0,  1);
                        interact(State.Player.x  ,State.Player.y+1);
                        State.moved = 1;
                        advanceTurn(); }
                     if (State.Buttons.left  > 0) {
                        moveActor(&State.Player, -1,  0);
                        interact(State.Player.x-1,State.Player.y  );
                        State.moved = 1;
                        advanceTurn(); }
                else if (State.Buttons.right > 0) {
                        moveActor(&State.Player,  1,  0);
                        interact(State.Player.x+1,State.Player.y  );
                        State.moved = 1;
                        advanceTurn(); }
                }
             if (State.Buttons.start > 0) { State.inMenu = !State.inMenu;  State.moved = 1;}
    }

    sprintf(d20text, "Moves: %i", State.turns);
    printString(d20text,  220,192);

    if (State.Buttons.up == 0 &&
        State.Buttons.down == 0 &&
        State.Buttons.left == 0 &&
        State.Buttons.right == 0 &&
        State.Buttons.start == 0) { State.moved = 0; }

    if (State.inMenu) { displayMenu(); }
                 else { displayMap();  }

}

void advanceTurn() {
    State.turns++;
    updateNPCs();
}

void updateNPCs() {
    uint8_t i, spin, dx, dy;
    for (i = 0; i < sizeof(NPCS) / sizeof(npc); i++) {
        spin = RNGCall() % 4;
        switch(spin){
            case D_UP:
                dx = NPCS[i].Actor.x; dy =  NPCS[i].Actor.y+1;
                break;
            case D_LEFT:
                dx = NPCS[i].Actor.x+1; dy =  NPCS[i].Actor.y;
                break;
            case D_DOWN:
                dx = NPCS[i].Actor.x; dy =  NPCS[i].Actor.y-1;
                break;
            case D_RIGHT: default:
                dx = NPCS[i].Actor.x-1; dy =  NPCS[i].Actor.y;
                break;
        }
        if (checkMap(dx, dy) < 1 ) { NPCS[i].Actor.x = dx; NPCS[i].Actor.y = dy; }
        else if (checkMap(dx, dy) == PC && RNGCall()%6 > 4) {  }
    }
}

void setActor(actor* Actor, uint8_t x, uint8_t y) { Actor->x = x; Actor->y = y; }

void moveActor(actor* Actor, int8_t x, int8_t y) {
    if (checkMap(Actor->x+x, Actor->y+y) == 0) { Actor->x += x; Actor->y += y; }
}

void printMessage(char* m) {
    strncpy(State.message, m, 151);
    State.messageTimer = 0;
}

void displayMap() {
    uint8_t x = 0, y = 0, c;
    for (y = 0; y < 8; y++){
        for(x = 0; x < 8; x++) {
            c = checkMap(x,y);
            if( x == State.Player.x && y == State.Player.y) { printChar('@', State.Player.x*8, State.Player.y*8, 0,14); }
            else if( c == NPC        ) { printChar('E', x*8, y*8, 0,4 ); }
            else if( c == CHEST_OPEN ) { printChar('H', x*8, y*8, 0,6); }
            else if( c == CHEST      ) { printChar('-', x*8, y*8, 0,6); }
            else if( c == 1          ) { printChar('#', x*8, y*8, 0,15); }
                                 else  { printChar(' ', x*8, y*8, 0,15); }

        }
    }
}

void displayMenu() {
    uint8_t i, lv;
    char strbld[151];
    lv = Level(State.playerStatus.xp);

    for (i = 0; i < 40; i++) { printChar('*', i*8,0,0,15); }
    printString("COUNT PLACEHOLDER", 8, 8, 0,15);

    if(lv >= 20) { sprintf(strbld, "Level %i    Exp:%i", lv, State.playerStatus.xp);}
    else         { sprintf(strbld, "Level %i    Exp:%i  To Next:%i", lv, State.playerStatus.xp, LEVEL_TABLE[lv]-State.playerStatus.xp);}
    printString(strbld, 8, 16, 0,15); //Display XP

    sprintf(strbld, "HP: %i/%i   BLOOD: OOO--", State.playerStatus.hp, State.playerStat.hp); printString(strbld, 8, 24, 0,15); //Display HP
    sprintf(strbld, "   STR:%i  CON:%i  INT:%i    ATT:%i", State.playerStat.str, State.playerStat.con, State.playerStat.itl, ATT(&State.playerStat, &State.playerStatus)); printString(strbld, 8, 32, 0, 15);
    sprintf(strbld, "   WIL:%i  AGI:%i  LCK:%i    DEF:%i", State.playerStat.wil, State.playerStat.agi, State.playerStat.lck, DEF(&State.playerStat, &State.playerStatus)); printString(strbld, 8, 40, 0, 15);

    sprintf(strbld, "GOLD: %i", State.itemsHeld.gold); printString(strbld, 8, 48, 0, 15); //Display money

    /*for (i = 0; i < ITEM_SIZE;     i++) { //Iterate through items
        if ( State.itemsHeld.held[i] > 0 ) {
            printString(items[i].name, 8, 36+i*8, 0,15);
            sprintf(strbld, "%i", State.itemsHeld.held[i]);
            printString(strbld, 200, 36+i*8, 0,15); //Display item name and count
        }
    }*/
}

void interact(int8_t x, int8_t y)
{
    uint8_t i = 0;
    char mes[150];
    bool success = false;

    for (i = 0; i < sizeof(NPCS) / sizeof(npc); i++) {
        if (NPCS[i].Actor.x == x && NPCS[i].Actor.y == y) { printMessage("That\'s a bad guy!"); }
    }

    for (i = 0; i < sizeof(chests) / sizeof(Chest); i++) {
        if (chests[i].Actor.x == x && chests[i].Actor.y == y) {
            if (chests[i].opened) { printMessage("Nothing in here!"); } //Already Checked.
            else{ //Not checked so far.
                 if (chests[i].itemId == 255) {
                    sprintf(
                            mes,
                            "Inside the chest is \n%i Ducats. Took them.",
                            chests[i].quantity
                            );
                    State.itemsHeld.gold += chests[i].quantity;
                    }
                else {
                    success = AddItem(&State.itemsHeld, chests[i].itemId, chests[i].quantity);
                    if (!success) {
                        sprintf(
                                mes,
                                "Inside the chest is %i %ss.\n But you have too many already!.",
                                chests[i].quantity,
                                items[chests[i].itemId].name
                                );
                    }
                    else if ( chests[i].quantity > 1) {
                        sprintf(
                                mes,
                                "Inside the chest is %i %ss.\n Took them.",
                                chests[i].quantity,
                                items[chests[i].itemId].name
                                );
                    }
                    else {
                        sprintf(
                                mes,
                                "Inside the chest is a %s.\n Took it.",
                                items[chests[i].itemId].name
                                );
                    }
                }
                chests[i].opened = true;
                printMessage(mes);
                break;
            }
        }
    }
}

uint8_t checkMap(uint8_t x, uint8_t y){
    uint8_t i = 0;
    if (State.Player.x == x && State.Player.y == y) { return PC; }
    for (i = 0; i < sizeof(chests) / sizeof(Chest); i++) {
        if (chests[i].Actor.x == x && chests[i].Actor.y == y) {
            if (chests[i].opened) { return CHEST_OPEN; }
            else { return CHEST; }
        }
    }
    for (i = 0; i < sizeof(NPCS) / sizeof(npc); i++) {
        if (NPCS[i].Actor.x == x && NPCS[i].Actor.y == y) { return NPC; }
    }
    return protoMap[x+y*8];
}

void attackPlayer(NPC* attacker){
    uint16_t att = ATT(attacker->stat, attacker->status)
}
