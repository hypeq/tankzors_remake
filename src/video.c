#include "video.h"

Prog prog;

void initVideo(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL error: %s\n", SDL_GetError());
		exit(1);
	}

	TTF_Init();

	prog.window = SDL_CreateWindow("Tankzors Remake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);

	if(!prog.window)
	{
        	printf("Window error: %s\n", SDL_GetError());
        	exit(1);
	}

	SDL_Surface *icon = IMG_Load("textures/icon.png");
	SDL_SetWindowIcon(prog.window, icon);
	SDL_FreeSurface(icon);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	prog.renderer = SDL_CreateRenderer(prog.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(!prog.renderer)
	{
	        printf("Renderer error: %s\n", SDL_GetError());
        	exit(1);
	}

	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
	{
		printf("SDL_image error: %s\n", SDL_GetError());
		exit(1);
	}
}

void cleanUp(void)
{
        SDL_DestroyWindow(prog.window);
        SDL_Quit();
        exit(0);
}
