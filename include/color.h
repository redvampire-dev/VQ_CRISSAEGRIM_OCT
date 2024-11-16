#ifndef COLOR_H_
#define COLOR_H_

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color;


static color PALETTE [16] =
{
	{  0,  0,  0},
	{  0,  0,170},
	{  0,170,  0},
	{  0,170,170},
	{170,  0,  0},
	{170,  0,170},
	{170, 85,  0},
	{170,170,170},
	{ 85, 85, 85},
	{ 85, 85,255},
	{ 85,255, 85},
	{ 85,255,255},
	{255, 85, 85},
	{255, 85,255},
	{255,255, 85},
	{255,255,255}
};

static uint8_t TEXTPAL [] = { 15,  15, 15, 0 };

#endif
