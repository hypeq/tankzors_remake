#include "global.h"
int level[] =
{
0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,
0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,
0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,
0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,
0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,
0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,
0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,
0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,
1,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,
0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,
};

static void capFrameRate(long *then, float *remainder);
void moveCamera(float player_x, float player_y, float *off_x, float *off_y);
static int i;
struct Entity *entity[ENTITY_MAX];
int tick = 0;
int id = 0;
short int enemy_count = 20;

int window_width = 640;
int window_height = 480;
float scale_multiplier = 1;

int map_x_pos = 0;
int map_y_pos = 0;
int map_x = 20;
int map_y = 20;
SDL_Rect sprites[16];
SDL_Rect brick[15];
SDL_Rect e_spr[16];
SDL_Rect b_spr[4];
SDL_Rect ex_spr[5];
SDL_Rect hud_spr[14];
SDL_Rect r_spr[6];
SDL_Point* p_point;

int i_map;
static void draw(float,float,Cell* cell1, SDL_Rect* map,SDL_Texture*,SDL_Texture*,SDL_Texture*, SDL_Texture*, SDL_Texture*,SDL_Rect*,SDL_Rect*,SDL_Rect*,SDL_Rect*,SDL_Rect*);
void prepareScene(void);
void presentScene(void);
void makeTextureArray(int,SDL_Texture*, SDL_Rect[], int, int, int, int, int,int,int);
struct Entity *player;
SDL_Texture* loadTexture(char* file);
void cleanUp(void);
void makeGrid(SDL_Rect* dest, int x, int y, int scale);
static void logic(struct Hud**,struct Entity **ent, struct Entity *player, SDL_Rect* rect, Cell* cell);
void initStage(void);
void rectToCell(SDL_Rect* rect, Cell* cell, int mx, int my);
struct Hud *hud[ENTITY_MAX];
void doBullets(struct Entity**);
static void draw(float,float,Cell* cell1, SDL_Rect* map,SDL_Texture*,SDL_Texture*,SDL_Texture*, SDL_Texture*, SDL_Texture*,SDL_Rect*,SDL_Rect*,SDL_Rect*,SDL_Rect*,SDL_Rect*);
static void logic(struct Hud**,struct Entity **ent, struct Entity *player, SDL_Rect* rect, Cell* cell);
void initPlayer(void);
void bulletCollideWorld(struct Entity**,Cell cell[], int s);
void bulletCollideEntity(struct Entity**);
int entityCollideWorld(Cell cell[], int s, int,int,int,int);
void manageCells(Cell* cell1, Cell* cell2, int s1, int s2);
void clearCells(Cell* cell, int s);
void spawnEnemy(struct Hud **,struct Entity **ent);
void doEnemies(struct Entity **,Cell* cell, int s, SDL_Rect*);
void doExplosion(struct Entity**);
int entityCollideEntity(void);
void drawEnemy(float,float,struct Entity **,SDL_Texture*,SDL_Rect*);
void drawBullet(float,float,struct Entity **ent,SDL_Texture*,SDL_Rect*);
void drawExplosion(float,float,struct Entity**,SDL_Texture*,SDL_Rect*);
static uint8_t player_initialized = 0;
void doPlayer(struct Hud **,struct Entity **ent,struct Entity *player, SDL_Rect* rect, Cell* cell, int s);
void doInput(void);
void drawCell(float,float,SDL_Texture*,SDL_Rect*,Cell cell[], int mx, int my);
void blit_grid(float,float,SDL_Rect[],int,int,SDL_Texture*,SDL_Rect*);
void blit(SDL_Texture* texture, int x, int y, int w, int h, int xx, int yy, int ww, int hh);
void playMusic(void);
void displayFPS(TTF_Font *font, SDL_Color color, SDL_Rect *fps_rect, SDL_Texture **fps_texture, float fps);
extern Prog prog;
