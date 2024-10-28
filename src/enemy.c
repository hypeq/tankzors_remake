#include "enemy.h"
void spawnEnemy(struct Hud **hud, struct Entity **ent){
  for(int i = 0;i < ENTITY_MAX;i++){
    if(!ent[i]->is){
      c_enemy++;
      ent[i]->dir = 2;
      ent[i]->reload = 0;
      ent[i]->i_reload = 30;
      ent[i]->moving = 0;
      ent[i]->hp = 1;
      ent[i]->type = 1;
      ent[i]->x = (c_enemy % 3 ? (c_enemy % 2 ? CELL_SIZE * 2.5 : CELL_SIZE * 2.5 + (CELL_SIZE * 6)) : 496 - CELL_SIZE);
      ent[i]->y = 86;
      ent[i]->w = CELL_SIZE;
      ent[i]->h = CELL_SIZE;
      ent[i]->dx = 1;ent[i]->dy = ent[i]->dx;
      ent[i]->id = id;
      ent[i]->is = 1;
      id++;
      if(enemy_count > 0) enemy_count--;
      cleanHud(hud,11);
      makeHudEnemy();
      break;
    }
  }
}

void doEnemies(struct Entity **e, Cell* cell, int s, __attribute__((unused)) SDL_Rect *rect){

  for(int i = 0;i<ENTITY_MAX;i++){
    if(e[i]->type == 1){
      if(e[i]->dir == UP){
	if(!entityCollideWorld(cell,s, e[i]->x,e[i]->y - e[i]->dy,e[i]->w,e[i]->h)){
          move(e[i]);
	  e[i]->busy = 1;
          playSound(1);
        }
        else{
	  changeDir(e[i]);
	  Mix_HaltChannel(2);
        }
      }

      if(e[i]->dir == DOWN){
        if(!entityCollideWorld(cell,s,
          		      e[i]->x,e[i]->y + e[i]->dy,e[i]->w,e[i]->h)){
          move(e[i]);
	  e[i]->busy = 1;
          playSound(1);
        }
        else{
	  changeDir(e[i]);
	  Mix_HaltChannel(2);
        }
      }
      if(e[i]->dir == RIGHT){
        if(!entityCollideWorld(cell,s,
          		      e[i]->x + e[i]->dx,e[i]->y,e[i]->w,e[i]->h)){
          move(e[i]);
	  e[i]->busy = 1;
          playSound(1);
        }
        else{
	  changeDir(e[i]);
	  Mix_HaltChannel(2);
        }
      }


      if(e[i]->dir == LEFT){
        if(!entityCollideWorld(cell,s,
          		      e[i]->x - e[i]->dx,e[i]->y,e[i]->w,e[i]->h)){
          move(e[i]);
	  e[i]->busy = 1;
          playSound(1);
        }
        else{
          changeDir(e[i]);
	  Mix_HaltChannel(2);
	}
      }
      handleSpr(e[i]);
      if(use_r_table() > 250)
	      fire(e,e[i]);
      if(use_r_table() > 250) changeDir(e[i]);
      if(e[i]->reload > 0)
	      e[i]->reload--;
      if(e[i]->hp < 1){
	Mix_HaltChannel(2);
        spawnExplosion(e,e[i],1);
        e[i]->is = 0;
	enemy_killed++;
      }
    }
  }
}


void changeDir(struct Entity *e){
  if(e->dir == UP || e->dir == DOWN) e->dir = use_r_table() > 125 ? 1:3;
  else if(e->dir == RIGHT || e->dir == LEFT) e->dir = use_r_table() > 125 ? 0:2;
}
