#include "stage.h"

void fire(struct Entity **bullet, struct Entity *e){
  if(!e->reload){
    for(i=0;i < ENTITY_MAX;i++){
      if(!bullet[i]->is){
        use_r_table();

        e->reload = e->i_reload;
        bullet[i]->hp = 1;
        bullet[i]->w = 24;
        bullet[i]->h = 24;
	bullet[i]->alive_for = 0;
        if(!e->type){
          playSound(2);
          bullet[i]->type = 2;
        }
        else{
          bullet[i]->type = 3;
        }
        if(e->dir == LEFT){
          bullet[i]->x = e->x + e->w - 35;
          bullet[i]->y = e->y;
          bullet[i]->dx = -5;bullet[i]->dy = 0;
          bullet[i]->cur_spr = 1;
          bullet[i]->dir = LEFT;
        }
        else if(e->dir == RIGHT){
          bullet[i]->x = e->x + e->w - 10;
          bullet[i]->y = e->y;
          bullet[i]->dx = 5;bullet[i]->dy = 0;
          bullet[i]->cur_spr = 3;
          bullet[i]->dir = RIGHT;
        }

        if(e->dir == DOWN){
          bullet[i]->x = e->x;
          bullet[i]->y = e->y + e->h - 10;
          bullet[i]->dx = 0;bullet[i]->dy = 5;
          bullet[i]->cur_spr = 2;
          bullet[i]->dir = DOWN;
        }
        else if(e->dir == UP){
          bullet[i]->x = e->x;
          bullet[i]->y = e->y + e->h - 35;
          bullet[i]->dx = 0;bullet[i]->dy = -5;
          bullet[i]->cur_spr = 0;
          bullet[i]->dir = UP;
        }
	bullet[i]->is = 1;
	break;
      }
    }
  }
}

void doBullets(struct Entity **b){
  for(int ii = 0;ii<ENTITY_MAX;ii++){
    if(b[ii]->is && (b[ii]->type == 2 ||b[ii]->type == 3)){
      b[ii]->x += b[ii]->dx;
      b[ii]->y += b[ii]->dy;
      b[ii]->alive_for++;
      if(b[ii]->alive_for > 240 || b[ii]->hp < 1){
        spawnExplosion(b,b[ii],0);
        playSound(4);
	b[ii]->is = 0;
      }
    }
  }
}
void spawnExplosion(struct Entity **ex,struct Entity *e, int size)
{
  for(int ii = 0;ii<ENTITY_MAX;ii++){
    if(!ex[ii]->is){
      if(!size){ex[ii]->w = 32;ex[ii]->h = 32;}
      else{ex[ii]->w=64;ex[ii]->h=64;}
      ex[ii]->x = (e->x - e->w / 2) - ex[ii]->w / 2;ex[ii]->y = (e->y + e->h / 2) - ex[ii]->h / 2;
      
      ex[ii]->type = 20;
      if(!size)ex[ii]->cur_spr = 0;
      else ex[ii]->cur_spr = 3;
      ex[ii]->alive_for = 1;
      ex[ii]->is = 1;
    }
  }
}

void doExplosion(struct Entity **ex){
  for(int ii = 0;ii<ENTITY_MAX;ii++){
    if(ex[ii]->type == 20 && ex[ii]->is){
      if(!(ex[ii]->alive_for % 2) && ex[ii]->cur_spr < 2){
        ex[ii]->cur_spr++;
      }    
      else if(!(ex[ii]->alive_for % 3) && ex[ii]->cur_spr > 2 && ex[ii]->cur_spr < 4){
        ex[ii]->cur_spr++;
      }    

      if(ex[ii]->alive_for > 10){
        ex[ii]->is = 0;
      }
      else ex[ii]->alive_for++;
    }
  }
}

void move(Cell *cell,struct Entity *ent){
  if(ent->busy){
    if(ent->dir == UP && ent->cur_spr == 8 && !entityCollideWorld(cell, 400,ent->x, ent->y - 1, ent->w, ent->h)){
      if(!ent->move_set){
        ent->dest = ent->y - CELL_SIZE;
        ent->move_set=1;
      }
      if(ent->y > ent->dest) ent->y -= ent->dy;
      else{
        ent->busy = 0;
        ent->input = 0;
        ent->move_set = 0;
      }
    }
    else if(ent->dir == DOWN  && ent->cur_spr == 0 && !entityCollideWorld(cell, 400,ent->x, ent->y + 1, ent->w, ent->h)){
      if(!ent->move_set){
        ent->dest = ent->y + CELL_SIZE;
        ent->move_set=1;
      }
      if(ent->y < ent->dest) ent->y += ent->dy;
      else{
        ent->busy = 0;
        ent->input = 0;
        ent->move_set = 0;
      }
    }
    else if(ent->dir == LEFT && ent->cur_spr == 4 && !entityCollideWorld(cell, 400,ent->x - 1, ent->y, ent->w, ent->h)){

      if(!ent->move_set){ 
        ent->dest = ent->x - CELL_SIZE;
        ent->move_set=1;
      }
      if(ent->x > ent->dest) ent->x -= ent->dx;
      else{
        ent->busy = 0;
        ent->move_set = 0;
      }
    }
    else if(ent->dir == RIGHT && ent->cur_spr == 12 && !entityCollideWorld(cell, 400,ent->x + 1, ent->y, ent->w, ent->h)){
      if(!ent->move_set){
        ent->dest = ent->x + CELL_SIZE;
        ent->move_set=1;
      }
      if(ent->x < ent->dest) ent->x += ent->dx;
      else{
        ent->busy = 0;
        ent->move_set = 0;
      }
    }
    else ent->busy = 0;
  }
}

void handleSpr(struct Entity *ent){
  if(ent->dir == UP && ent->cur_spr != 8){
    if(ent->cur_spr < 8) ent->cur_spr++;
    if(ent->cur_spr > 8) ent->cur_spr--;
  }
  else if(ent->dir == DOWN && ent->cur_spr != 0){
    if(ent->cur_spr > 8){
      if(ent->cur_spr == 15) ent->cur_spr = 0;
      else ent->cur_spr++;
    }
    else if(ent->cur_spr > 0) ent->cur_spr--;
  }
  else if(ent->dir == LEFT && ent->cur_spr != 4){
    if(ent->cur_spr > 12){
      if(ent->cur_spr == 15) ent->cur_spr = 0;
      else ent->cur_spr++;
    }
    else if(ent->cur_spr > 4) ent->cur_spr--;
    else ent->cur_spr++;
  }
  else if(ent->dir == RIGHT && ent->cur_spr != 12){
    if(ent->cur_spr > 12)ent->cur_spr--;
    else if(ent->cur_spr > 4) ent->cur_spr++;
    else{
      if(ent->cur_spr == 0) ent->cur_spr = 15;
      ent->cur_spr--;
    }
  }
}

void rectToCell(SDL_Rect* rect, Cell* cell, int mx, int my){
  for(i=0;i < mx*my;i++){
    cell[i].x = rect[i].x;
    cell[i].y = rect[i].y;
    cell[i].w = rect[i].w;
    cell[i].h = rect[i].h;
    cell[i].rx = rect[i].x;
    cell[i].ry = rect[i].y;
    cell[i].rw = rect[i].w;
    cell[i].rh = rect[i].h;
    cell[i].obj = 0;
    cell[i].cur_spr = 0;
  }
}

int collide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
  return (MAX(x1,x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1,y2) < MIN(y1 + h1, y2 + h2));
}


void clearCells(Cell* cell, int s){
  for(i=0;i < s;i++){
    cell[i].obj = 0;
  }
}

int entityCollideWorld(Cell cell[], int s,int x, int y, int w, int h){
  int r;
  for(i=0;i<s;i++){
    if(cell[i].obj && cell[i].obj != 3 && 
		    collide(x,y,w,h,cell[i].x,cell[i].y,cell[i].w,cell[i].h)){
      r = 1;
      break;
    }
    else r = 0;
  }
  return r;
}

/*
// Не для этих танчиков
int entityCollideEntity(struct Entity **ent,struct Entity *e){
  int r = 0;
  for(int ii = 0;ii<ENTITY_MAX;ii++){
    if(e->id != ent[ii]->id && (e->type == 1 || !e->type) && (ent[ii]->type == 1 || !ent[ii]->type)){
      if(e->dir == 0){
        if(collide(e->x,e->y - (e->dy*3),e->w,e->h + (e->dy*3),
      	      ent[ii]->x,ent[ii]->y,ent[ii]->w,ent[ii]->h) &&
	!collide(e->x,e->y,e->w,e->h,ent[ii]->x,ent[ii]->y,ent[ii]->w,ent[ii]->h)){
          r = 1;
          break;
        }
        else r = 0;
      }
      else if(e->dir == 2){
        if(collide(e->x,e->y + (e->dy*3),e->w,e->h + (e->dy*3),
      	      ent[ii]->x,ent[ii]->y,ent[ii]->w,ent[ii]->h) &&
	!collide(e->x,e->y,e->w,e->h,ent[ii]->x,ent[ii]->y,ent[ii]->w,ent[ii]->h)){
          r = 1;

          break;
        }
        else r = 0;
      }
      else if(e->dir == 1){
        if(collide(e->x + (e->dx*3),e->y,e->w + (e->dx*3),e->h,
      	      ent[ii]->x,ent[ii]->y,ent[ii]->w,ent[ii]->h) &&
	!collide(e->x,e->y,e->w,e->h,ent[ii]->x,ent[ii]->y,ent[ii]->w,ent[ii]->h)){
          r = 1;

          break;
        }
        else r = 0;
      }
      else if(e->dir == 3){
        if(collide(e->x -(e->dx*3),e->y,e->w + (e->dx*3),e->h,
      	      ent[ii]->x,ent[ii]->y,ent[ii]->w,ent[ii]->h) &&
	!collide(e->x,e->y,e->w,e->h,ent[ii]->x,ent[ii]->y,ent[ii]->w,ent[ii]->h)){
          r = 1;
          break;
        }
        else r = 0;
      }
    }
  }
  return r;
}
*/

void bulletCollideEntity(struct Entity **e){
  for(int ii = 0;ii<ENTITY_MAX;ii++){
    for(int j = 0;j<ENTITY_MAX;j++){
      if(e[ii]->is && e[j]->is){
        if(collide(e[ii]->x,e[ii]->y,e[ii]->w,e[ii]->h, e[j]->x,e[j]->y,e[j]->w,e[j]->h) && e[ii]->hp && e[j]->hp){
          if(e[ii]->type == 2 && (e[j]->type == 1 || e[j]->type == 3)){
            e[ii]->hp--;
            e[j]->hp--;
          }
          else if(e[ii]->type == 3 && (!e[j]->type || e[j]->type == 2)){
            e[ii]->hp--;
            e[j]->hp--;
          }
	  else if((e[ii]->type == 2 || e[ii]->type == 3) && e[j]->type == 9){
	    e[ii]->hp--;
	    e[j]->hp--;
	  }
        }
      }
    }
  }
}

void bulletCollideWorld(struct Entity **b,Cell cell[], int s){
  for(int j = 0;j<ENTITY_MAX;j++){
    for(i=0;i<s;i++){
      if(b[j]->is && (b[j]->type == 2 || b[j]->type == 3)){
        if(cell[i].obj && cell[i].obj != 3 && cell[i].obj != 4 &&

          	      collide(b[j]->x,b[j]->y,b[j]->w,b[j]->h,cell[i].x,cell[i].y,cell[i].w,cell[i].h)){
          if(b[j]->hp){
            if(cell[i].cur_spr < 6) cell[i].cur_spr += 2;else cell[i].obj = 0;
            b[j]->hp = 0;
          }
        }
      }
    }
  }
}


