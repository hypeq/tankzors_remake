#include "global.h"

extern Prog prog;
extern Cell* cell;
extern int window_width, window_height;
extern int keyboard[];
extern int enemy_count;
extern float scale_multiplier;
void fire(struct Entity **ent, struct Entity* e);
void move(Cell *cell, struct Entity *e);
int entityCollideWorld(Cell cell[],int,int,int,int,int);
int entityCollideEntity(struct Entity **,struct Entity*);
uint8_t minus_press = 0;
uint8_t plus_press = 0; 
short int use_r_table(void);
void playSound(unsigned short int id);
void cleanHud(struct Hud**,int);
void makeHudEnemy(struct Hud **hud);
void handleSpr(struct Entity*);
int keyboard[MAX_KEYBOARD_KEYS];
