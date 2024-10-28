#include "global.h"
extern short int enemy_count;
extern int id;
int entityCollideWorld(Cell*,int,int,int,int,int);
int use_r_table(void);
void fire(struct Entity **, struct Entity*);
void changeDir(struct Entity *e);
void playSound(unsigned short int id);
void move(struct Entity*);
void makeHudEnemy(void);
void cleanHud(struct Hud **hud,int type);
void spawnExplosion(struct Entity**,struct Entity*,int);
void handleSpr(struct Entity*);
int c_enemy = 0;
int enemy_killed = 0;
struct Entity *enemy;
