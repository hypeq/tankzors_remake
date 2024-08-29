#include "global.h"
void setGrid(int x, int y);
void blit(SDL_Texture* texture, int x, int y, int w, int h, int xx, int yy, int ww, int hh);
extern Prog prog;
extern float scale_multiplier;
static int i;
static int j;
int cur_cell;
int cell_size;
int multiplier;
SDL_Rect dest;
SDL_Rect clip;
SDL_Rect rect;
