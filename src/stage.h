#include "global.h"

int sprByCellState(Cell cell);
void spawnExplosion(struct Entity**,struct Entity *e,int);
void playSound(unsigned short int id);
extern struct Entity *player;
extern struct Entity *eagle;
extern int map_x_pos;
extern int map_y_pos;
extern int map_x;
extern int map_y;
extern int id;
int collide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int use_r_table(void);
int entityCollideWorld(Cell cell[], int s,int x, int y, int w, int h);
static int i;
