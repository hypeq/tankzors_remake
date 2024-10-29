#pragma once

#define TABLE 255
#define CELL_SIZE 24
#define ENTITY_MAX 100
#define MAX_KEYBOARD_KEYS 350
#define MAX_SND_CHANNELS 16

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define UP 0
#define DOWN 2
#define RIGHT 1
#define LEFT 3

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct{
  int x,y;
  int w,h;
  int rx,ry;
  int rw,rh;
  int pos_x,pos_y;
  int obj;
  int cur_spr;
  int moved;
} Cell;

struct Entity{
  float x,y;
  int w,h;
  int hp;
  int type;
  float dx,dy;
  int reload;
  int i_reload;
  int dir;
  int moving;
  int cur_spr;
  int alive_for;
  int id;
  uint8_t busy;
  uint8_t input;
  int dest;
  uint8_t move_set;
  uint8_t is;
  SDL_Texture* texture;

  struct Entity *next;
};

struct Hud{
  int x,y,w,h,type,cur_spr,is;
};

typedef struct{
  void(*logic)(struct Hud**,struct Entity **ent, struct Entity *player, SDL_Rect* rect, Cell* cell);
  void(*draw)(float,float,Cell* cell, SDL_Rect* map,SDL_Texture*,SDL_Texture*,SDL_Texture*,SDL_Texture*,SDL_Texture*,SDL_Rect*,SDL_Rect*, SDL_Rect*,SDL_Rect*,SDL_Rect*);
} Delegate;

typedef struct{
  SDL_Renderer* renderer;
  SDL_Window* window;
  Delegate delegate;
}Prog;

