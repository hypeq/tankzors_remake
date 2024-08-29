#include "input.h"

void doKeyUp(SDL_KeyboardEvent* event)
{
	if(event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		keyboard[event->keysym.scancode] = 0;
	}
}

void doKeyDown(SDL_KeyboardEvent* event)
{
	if(event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		keyboard[event->keysym.scancode] = 1;
	}
}

void doPlayer(__attribute__((unused)) struct Hud **hud, struct Entity **ent, struct Entity *player, __attribute__((unused)) SDL_Rect* rect, __attribute__((unused)) Cell* cell1, __attribute__((unused)) int s)
{
  if(keyboard[SDL_SCANCODE_RIGHT])
{
    if(player->dir == 1 && !player->busy)
{
      player->busy = 1;
    }
    else if(!player->busy)
{
      player->dir = 1;
    }
  }

  if(keyboard[SDL_SCANCODE_LEFT])
{
    use_r_table();
    if(player->dir == 3 && !player->busy)
{
      player->busy = 1;
    }
    else if(!player->busy)
{
      player->dir = 3;
    } 
  }

  if(keyboard[SDL_SCANCODE_DOWN])
{
    use_r_table();
    if(player->dir == 2 && !player->busy)
{
      player->busy = 1;
    }
    else if(!player->busy)
{
      player->dir = 2;
    }
  }

  if(keyboard[SDL_SCANCODE_UP])
{
      player->input = 1;
      use_r_table();
      if(player->dir == 0 && !player->busy)
{
        player->busy = 1;
      }
     else if(!player->busy){
        player->dir = 0;
      }
  }
  if(keyboard[SDL_SCANCODE_Z])
  {
    fire(ent,player);
  }
  if(keyboard[SDL_SCANCODE_MINUS])
  {
    if(!minus_press)
    {
      if(scale_multiplier >= 0.75f) scale_multiplier -= 0.25f;
      minus_press = 1;
    }
  }
  else minus_press = 0;

  if(keyboard[SDL_SCANCODE_EQUALS])
  {
    if(!plus_press)
    {
      if(scale_multiplier <= 3.75f) scale_multiplier += 0.25f;
      plus_press = 1;
    }
  }
  else plus_press = 0;

  handleSpr(player);
  move(cell1,player);

}

void doInput(void)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
        		exit(0);
			break;
			case SDL_KEYDOWN:
            doKeyDown(&event.key);
			break;
			case SDL_KEYUP:
			doKeyUp(&event.key);
            break;
			case SDL_WINDOWEVENT:
			  SDL_GetWindowSize(prog.window, &window_width, &window_height);
              break;
			default:
			break;
		}
	}
}
