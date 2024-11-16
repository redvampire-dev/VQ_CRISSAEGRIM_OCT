#include <GL/glut.h>
#include <stdbool.h>
#include <string.h>
#include "../include/color.h"
#include "../include/game.h"
#include "../include/font.h"

#define RES           2
#define SCREENWIDTH   320
#define SCREENHEIGHT  200
#define SCREENWIDTH2  SCREENWIDTH/2
#define SCREENHEIGHT2 SCREENHEIGHT/2
#define WINDOWWIDTH   SCREENWIDTH*RES
#define WINDOWHEIGHT  SCREENHEIGHT*RES

typedef struct {
    int frA, frB;
}time; time Time;

extern state State;

void pixel(int x,int y, int c)                  //draw a pixel at x/y with rgb
{
    uint8_t rgb[3];
    rgb[0] = PALETTE[c].r;
    rgb[1] = PALETTE[c].g;
    rgb[2] = PALETTE[c].b;
    glColor3ub(rgb[0],rgb[1],rgb[2]);
    glBegin(GL_POINTS);
    glVertex2i(x*RES,WINDOWHEIGHT-y*RES);
    glEnd();
}

void ColorMath(int x, int y, int c, uint8_t mode) //TODO: I'll get back to this one
{

}

void printChar(uint8_t c, int16_t x, int16_t y, uint8_t bg, uint8_t fg) {
    int16_t _x; int16_t _y;
    uint8_t p; uint8_t ac = c;

    for (_y = 0; _y < FONTSIZE; _y++ ){
        for(_x = 0; _x < FONTSIZE; _x++ ) {
            p = font[ac*FONTSIZE+_x+_y*(ASCII_W*FONTSIZE)];
            if(p > 0) { pixel(x+_x, y+_y,fg); }
            else      { pixel(x+_x, y+_y,bg); }
        }
    }
}


void printString(char* str, int16_t x, int16_t y) {
    int16_t _x=0, _y=0; uint16_t c;
    uint8_t ascii = 0;
    uint8_t p[4] = { 255,  47, 172, 165 };

    for (c = 0; c < strlen(str); c++ ) {
        if(str[c]=='\n') { _x = 0; _y++; }
        else {
                 if(str[c]=='\'') { ascii = 4; }
            else if( ((int) str[c] > 0 )&& ((int) str[c] < ASCII_W) ) { ascii = (int) str[c]; }
            else { ascii = 0; }

            printChar(ascii, x+_x*FONTSIZE, y+_y*FONTSIZE, 0, 15);

            if((_x+1)*FONTSIZE >= SCREENWIDTH-FONTSIZE)          { _x = 0; _y++;}
            else                       {  _x++; }
        }
    }
}



void clearScreen()
{
    int x, y;
    for(y=0; y < SCREENHEIGHT; y++) {
        for(x=0; x < SCREENWIDTH; x++) {
            pixel(x,y,0);
        }
    }
}

void display(){
    //printString("Hello World!\nGreets from RED", 8, 8);
    if(Time.frA-Time.frB>=50) {
        clearScreen();
        update();
        Time.frB = Time.frA;
        glutSwapBuffers();
        glutReshapeWindow(WINDOWWIDTH, WINDOWHEIGHT);
    }
    Time.frA=glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
}

void KeysDown(unsigned char key,int x,int y) {
     if(key=='w'==1){ State.Buttons.up =     1;}
     if(key=='s'==1){ State.Buttons.down =   1;}
     if(key=='a'==1){ State.Buttons.left =   1;}
     if(key=='d'==1){ State.Buttons.right =  1;}
     if(key=='n'==1){ State.Buttons.select = 1;}
     if(key=='m'==1){ State.Buttons.start =  1;}
     if(key==','==1){ State.Buttons.b =      1;}
     if(key=='.'==1){ State.Buttons.a =      1;}
     if(key=='k'==1){ State.Buttons.y =      1;}
     if(key=='l'==1){ State.Buttons.x =      1;}
}

void KeysUp(unsigned char key,int x,int y) {
     if(key=='w'==1){ State.Buttons.up =     0;}
     if(key=='s'==1){ State.Buttons.down =   0;}
     if(key=='a'==1){ State.Buttons.left =   0;}
     if(key=='d'==1){ State.Buttons.right =  0;}
     if(key=='n'==1){ State.Buttons.select = 0;}
     if(key=='m'==1){ State.Buttons.start =  0;}
     if(key==','==1){ State.Buttons.b =      0;}
     if(key=='.'==1){ State.Buttons.a =      0;}
     if(key=='k'==1){ State.Buttons.y =      0;}
     if(key=='l'==1){ State.Buttons.x =      0;}
}

int main(int argc, char* argv[]) {
     gameinit();
    setActor(&State.Player, 1, 1);
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowPosition(WINDOWWIDTH/2,WINDOWHEIGHT/2);
     glutInitWindowSize(WINDOWWIDTH,WINDOWHEIGHT);
     glutCreateWindow("Crissaegrim V0.02501 Hardware renderer");
     glPointSize(RES);
     gluOrtho2D(0,WINDOWWIDTH,0,WINDOWHEIGHT);
     glutDisplayFunc(display);
     glutKeyboardFunc(KeysDown);
     glutKeyboardUpFunc(KeysUp);
     glutMainLoop();
     return 0;
}
