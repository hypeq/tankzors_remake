#include "map.h"
SDL_Texture *rings;

int initMap()
{
	SDL_Texture *spritesheet;
	SDL_Texture *light;
	SDL_Texture *bullets;
	SDL_Texture *ground;
	SDL_Texture *walls;
	SDL_Rect map[400];
	Cell cell[400];
	int x = 400;
	long then = SDL_GetTicks();
	float remainder = 0.0f;
	float off_x, off_y;
    SDL_Color green = {0, 255, 0, 255};
    SDL_Texture *fps_texture = NULL;
    SDL_Rect fps_rect = {10, 10, 0, 0};
    TTF_Font *font = TTF_OpenFont("assets/fonts/OpenSans_Regular.ttf", 18);
	for(i=0;i<ENTITY_MAX;i++)
	{
		entity[i] = malloc(sizeof(struct Entity));
		memset(entity[i],0, sizeof(struct Entity));
		entity[i]->is=0;
	}

	for(i=0;i<ENTITY_MAX;i++)
	{
		hud[i] = malloc(sizeof(struct Hud));
		memset(hud[i],0, sizeof(struct Hud));
		hud[i]->is=0;
 	}

	spritesheet = loadTexture("assets/textures/walls.png");
	light = loadTexture("assets/textures/light.png");
    rings = loadTexture("assets/textures/rings.png");
	bullets = loadTexture("assets/textures/bullets.png");
	ground = loadTexture("assets/textures/ground.png");
	walls = loadTexture("assets/walls.png");
	i_map = map_x * map_y;

	makeGrid(map,map_x,map_y,0);
	rectToCell(map,cell,map_x,map_y);
	atexit(cleanUp);
  makeTextureArray(0,light, sprites,  16, 0,  0, 24,24,  16*24,0);
  makeTextureArray(0,rings, r_spr,  6, 0,  0, 28,28,  6*28,0);
  makeTextureArray(0,ground, brick,    8, 0,0,20,20,  8*20,0);
  makeTextureArray(0,spritesheet, e_spr,    8, 256,128,32,32,  8*20,0);
  makeTextureArray(0,bullets, b_spr,    4, 0,0,24,24,  4*24,0);
  makeTextureArray(0,spritesheet, ex_spr,   3, 512,256,20,20,  3*20,0);
  makeTextureArray(3,spritesheet, ex_spr,   2, 608,256,64,64,  2*20,0);

  makeTextureArray(0,spritesheet, hud_spr,  5, 656,368,16,16,  5*20,0);
  makeTextureArray(5,spritesheet, hud_spr,  5, 656,384,16,16,  5*20,0);
  makeTextureArray(10,spritesheet, hud_spr,  1, 640,384,16,16,   20,0);
  makeTextureArray(11,spritesheet, hud_spr,  1, 752,272,32,32,   20,0);
  makeTextureArray(12,spritesheet, hud_spr,  1, 752,320,32,32,   20,0);
  makeTextureArray(13,spritesheet, hud_spr,  1, 752,368,32,32,   20,0);


  for(i=0;i < x;i++){
    cell[i].obj = level[i];
    cell[i].cur_spr = 0;
    if(cell[i].obj == 2) cell[i].cur_spr = 9;
    if(cell[i].obj == 3) cell[i].cur_spr = 10;
    if(cell[i].obj == 4) cell[i].cur_spr = 12;
  }
initStage();
  uint64_t start,end;

  float elapsed;

  float fps = 0.0f;

  while (1) {
    tick++;
    moveCamera(player->x, player->y, &off_x, &off_y);
    start = SDL_GetPerformanceCounter();

    prepareScene();
    logic(hud, entity, player, map, cell);
    draw(off_x, off_y, cell, map, spritesheet, light, bullets, ground, walls, sprites, brick, b_spr, ex_spr, hud_spr);

    displayFPS(font, green, &fps_rect, &fps_texture, fps);

    presentScene();

    capFrameRate(&then, &remainder);
    end = SDL_GetPerformanceCounter();

    elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    fps = 1.0f / elapsed;
  }

  return 0;
}

void displayFPS(TTF_Font *font, SDL_Color color, SDL_Rect *fps_rect, SDL_Texture **fps_texture, float fps) {
  char fps_text[10];
  int fps_int = (int)fps;

  snprintf(fps_text, sizeof(fps_text), "FPS: %d", fps_int);

  SDL_Surface *fps_surface = TTF_RenderText_Blended(font, fps_text, color);
  if (fps_surface != NULL) {
    SDL_DestroyTexture(*fps_texture);
    *fps_texture = SDL_CreateTextureFromSurface(prog.renderer, fps_surface);
    fps_rect->w = fps_surface->w;
    fps_rect->h = fps_surface->h;
    SDL_FreeSurface(fps_surface);
  }

  if (*fps_texture != NULL) {
    SDL_RenderCopy(prog.renderer, *fps_texture, NULL, fps_rect);
  }
}

static void capFrameRate(long *then, float *remainder) {
  long wait, frameTime;
  wait = 0 + *remainder;
  *remainder -= (int)*remainder;
  frameTime = SDL_GetTicks() - *then;
  wait -= frameTime;

  if (wait < 1) {
    wait = 1;
  }
  SDL_Delay(wait);
  *remainder += 0.667f;
  *then = SDL_GetTicks();
}

void moveCamera(float player_x, float player_y, float *off_x, float *off_y)
{
  static float camera_x = 0.0f;
  static float camera_y = 0.0f;
  float lag_factor = 0.07f;
  float desired_x = (window_width / (2*scale_multiplier)) - 12 - player_x;
  float desired_y = (window_height / (2*scale_multiplier)) - 12 - player_y;

  camera_x += (desired_x - camera_x) * lag_factor;
  camera_y += (desired_y - camera_y) * lag_factor;

  *off_x = (int)(camera_x + 0.5f);
  *off_y = (int)(camera_y + 0.5f);
}



void draw(float off_x,float off_y,Cell* cell, SDL_Rect* map,SDL_Texture* sprsheet,SDL_Texture* light, SDL_Texture *bullets, SDL_Texture *ground, __attribute__((unused)) SDL_Texture *walls, SDL_Rect* espr,SDL_Rect *cspr, SDL_Rect* bspr, SDL_Rect *exspr, __attribute__((unused)) SDL_Rect *hudspr){
  blit_grid(off_x,off_y,map,map_x,map_y,ground,bspr);
  drawExplosion(off_x,off_y,entity,sprsheet,exspr);
  drawBullet(off_x,off_y,entity,bullets,bspr);
  blit(rings, player->x + off_x - 2, player->y + off_y - 2, player->w + 4, player->h + 4, 0, 0, 28, 28);
  blit(player->texture, player->x + off_x, player->y + off_y,player->w,player->h,sprites[player->cur_spr].x,sprites[player->cur_spr].y,sprites[player->cur_spr].w,sprites[player->cur_spr].h);

  drawEnemy(off_x,off_y,entity,light,espr);
  drawCell(off_x,off_y,sprsheet,cspr,cell, map_x, map_y);
}

void logic(struct Hud **hud1,struct Entity **ent, struct Entity *player1, SDL_Rect* rect, Cell* cell){
  doInput();
  doPlayer(hud1,ent,player1,rect, cell, map_x*map_y);
  //doEnemies(entity,cell,map_x*map_y,rect);
  doBullets(entity);
  doExplosion(entity);
  bulletCollideWorld(entity,cell,map_x*map_y);
  bulletCollideEntity(entity);
  if(player1->reload > 0)player1->reload--;
  if(player1->hp < 1){
    printf("Player fucked up! hp->%d\n",player1->hp);
    exit(0);
  }
}
void initPlayer(void)
{
	player = malloc(sizeof(struct Entity));
	memset(player, 0, sizeof(struct Entity));
	for(i=0;i<ENTITY_MAX && !player_initialized;i++)
	{
		if(!entity[i]->is)
		{
			player->dir = 0;
			player->reload = 0;
			player->i_reload = 60;
			player->moving = 0;
			player->type = 0;
			player->hp = 2;
			player->x = CELL_SIZE * 2.5 + 96;
			player->y = 48;
			player->w = CELL_SIZE;
			player->h = CELL_SIZE;
			player->dx = 1;player->dy = player->dx;
			player->texture = loadTexture("assets/textures/light.png");
			player->id = 0;
			player->busy = 0;
			player->input = 0;
			player->is=1;
			id++;
			entity[i] = player;
			player_initialized = 1;
			break;
		}
	}
}


void initStage(void)
{
	prog.delegate.logic = logic;
	prog.delegate.draw = draw;
	initPlayer();
    playMusic();
}
