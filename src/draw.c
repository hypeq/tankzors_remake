#include "draw.h"
void prepareScene(void){
  SDL_SetRenderDrawColor(prog.renderer,
                         0,0,0,255);
  //SDL_RenderSetLogicalSize(prog.renderer, 480, 320);
  SDL_RenderClear(prog.renderer);
}

void presentScene(void){
  SDL_RenderPresent(prog.renderer);
}

SDL_Texture* loadTexture(char* file){
  SDL_Texture* texture;
  texture = IMG_LoadTexture(prog.renderer, file);

  return texture;
}
void makeGrid(SDL_Rect* dest1, int x, int y, int scale){
  cur_cell = 0; 
  cell_size = !scale ? CELL_SIZE : (scale == 1 ? CELL_SIZE : CELL_SIZE);
  multiplier = !scale ? 1 : (scale == 1 ? 2 : 4);
  for(i=0;i < x * multiplier;i++){

    for(j=0;j < y * multiplier;j++){
      dest1[cur_cell].x = cell_size * j + (CELL_SIZE * 2.5);
      dest1[cur_cell].y = cell_size * i + CELL_SIZE;
      dest1[cur_cell].w = cell_size;
      dest1[cur_cell].h = cell_size;

      cur_cell++;
    }
  }
}



void blit_grid(float off_x,float off_y,SDL_Rect rect1[], int x, int y, SDL_Texture *ground, SDL_Rect *gspr){
  int cur_spr;
  for(i=0;i < (x*y);i++){
    cur_spr = i % 4;
    blit(ground,rect1[i].x+off_x,rect1[i].y+off_y,rect1[i].w,rect1[i].h, gspr[cur_spr].x, gspr[cur_spr].y, gspr[cur_spr].w, gspr[cur_spr].h);
  }
}

void makeTextureArray(int from, __attribute__((unused)) SDL_Texture *texture, SDL_Rect clip1[], int amount, int x, int y, int w, int h, int width, __attribute__((unused)) int height){
  for(i=0;i < amount;i++){
    clip1[from + i].x = x + (width / amount) * i;
    clip1[from + i].y = y;
    clip1[from + i].w = w;
    clip1[from + i].h = h;

  }
}
void blit(SDL_Texture* texture, int x, int y, int w, int h, int xx, int yy, int ww, int hh){
  dest.x = x * scale_multiplier;dest.y = y * scale_multiplier;

  if(w || h){
    dest.w = h * scale_multiplier;dest.h = h * scale_multiplier;
  }
  else
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  if((xx || yy) || (ww || hh)){
    clip.y = yy;clip.x = xx;clip.w = ww;clip.h = hh;
    SDL_RenderCopy(prog.renderer, texture, &clip, &dest);
  }
  else
    SDL_RenderCopy(prog.renderer, texture, NULL, &dest);
}
void drawCell(float off_x,float off_y,SDL_Texture *sprsheet, SDL_Rect *cspr, Cell cell[], int mx, int my){
  for(i=0;i < (mx*my);i++){
    if(cell[i].obj){
      rect.x = cell[i].rx+off_x;rect.y = cell[i].ry+off_y;
      rect.w = cell[i].rw;rect.h = cell[i].rh;
      blit(sprsheet,rect.x,rect.y,rect.w,rect.h, cspr[cell[i].cur_spr].x,cspr[cell[i].cur_spr].y,cspr[cell[i].cur_spr].w,cspr[cell[i].cur_spr].h);
    }
  }
}


void drawEnemy(float off_x,float off_y,struct Entity **e, SDL_Texture *sprsheet, SDL_Rect* espr){
  for(i=0;i<ENTITY_MAX;i++){
    if(e[i]->type == 1 && e[i]->is){
      blit(sprsheet,e[i]->x+off_x,e[i]->y+off_y,e[i]->w,e[i]->h,espr[e[i]->cur_spr].x,espr[e[i]->cur_spr].y,espr[e[i]->cur_spr].w,espr[e[i]->cur_spr].h);
    }
  }
}

void drawBullet(float off_x,float off_y,struct Entity **ent, SDL_Texture* sprsheet, SDL_Rect* bspr){
    for(i=0;i < ENTITY_MAX;i++){
      if((ent[i]->type == 2 || ent[i]->type == 3) && ent[i]->is)
        blit(sprsheet,ent[i]->x+off_x,ent[i]->y+off_y,ent[i]->w,ent[i]->h, bspr[ent[i]->cur_spr].x,bspr[ent[i]->cur_spr].y,bspr[ent[i]->cur_spr].w,bspr[ent[i]->cur_spr].h);
  }
}

void drawExplosion(float off_x,float off_y,struct Entity **ex,SDL_Texture* sprsheet, SDL_Rect* exspr){
  for(i=0;i<ENTITY_MAX;i++){
    if(ex[i]->is && ex[i]->type == 20)
      blit(sprsheet,ex[i]->x+off_x,ex[i]->y+off_y,ex[i]->w,ex[i]->h, exspr[ex[i]->cur_spr].x,exspr[ex[i]->cur_spr].y,exspr[ex[i]->cur_spr].w,exspr[ex[i]->cur_spr].h);
  }
}

void drawHud(struct Hud **hud,SDL_Texture* sprsheet, SDL_Rect *hudspr){

  for(i = 0;i < ENTITY_MAX;i++){
    if(hud[i]->is)
      blit(sprsheet,hud[i]->x,hud[i]->y,hud[i]->w,hud[i]->h, hudspr[hud[i]->cur_spr].x, hudspr[hud[i]->cur_spr].y, hudspr[hud[i]->cur_spr].w, hudspr[hud[i]->cur_spr].h);
  }
}

