#include "hud.h"
void makeHudObj(struct Hud **hud,int x, int y, int w, int h, int z, int type){
  for(int i = 0;i<ENTITY_MAX;i++){
    if(hud[i] != NULL){
      if(!hud[i]->is){
        hud[i]->w = w;
        hud[i]->h = h;
        hud[i]->x = x;
        hud[i]->y = y;
        hud[i]->type = type;
        hud[i]->cur_spr = z;
        hud[i]->is = 1;
	break;
      }
    }
  }
}

void makeHudEnemy(struct Hud **hud){
  int i;
  for(i = 2;i < enemy_count + 2;i++){
    makeHudObj(hud,(i % 2) == 0 ? 512:528, 48 + (i / 2 * 16),16,16,10,11);
  }
}

void hudNumber(struct Hud **hud){
  makeHudObj(hud,528,272,16,16,player->hp < 10 ? player->hp : 9 ,2);
  makeHudObj(hud,528,388,16,16,5,12);
}

void initHud(struct Hud **hud){
  makeHudEnemy(hud);
  makeHudObj(hud,512,256,32,32,11, 10);
  makeHudObj(hud,512,352,32,32,13, 10);
  hudNumber(hud);

}

void cleanHud(struct Hud **hud, int type){
  for(int i = 0;i<ENTITY_MAX;i++){
    if(hud[i]->type == type){
      hud[i]->is = 0;
    }
  }
}
