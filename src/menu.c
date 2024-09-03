#include "menu.h"

int showMenu()
{
    SDL_Texture* backgroundTexture = IMG_LoadTexture(prog.renderer, "textures/menu_pict_fade.png");
    TTF_Font* font = TTF_OpenFont("fonts/RobotoCondensed_Regular.ttf", 24);

    SDL_Color textColor = { 255, 0, 0, 255 };
    SDL_Color buttonColor = { 50, 50, 50, 255 };
    SDL_Color borderColor = { 0, 0, 0, 255 };
    SDL_Color hoverBorderColor = { 169, 169, 169, 255 };

    SDL_Rect button1, button2;
    SDL_Texture* message1, * message2;
    SDL_Rect textRect1, textRect2;

    Mix_Music *music = Mix_LoadMUS("music/intro.ogg");
    if(!music)
    {
        printf("Mix_LoadMUS error: %s\n", Mix_GetError());
    }
    Mix_PlayMusic(music, -1);

    int running = 1, button1Hovered = 0, button2Hovered = 0;

    while (running) {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(prog.window, &windowWidth, &windowHeight);

        int buttonWidth = windowWidth / 4, buttonHeight = windowHeight / 10;
        int startY = (windowHeight - (2 * buttonHeight + 20)) / 2;

        button1.x = (windowWidth - buttonWidth) / 2;
        button1.y = startY;
        button1.w = buttonWidth;
        button1.h = buttonHeight;

        button2.x = (windowWidth - buttonWidth) / 2;
        button2.y = startY + buttonHeight + 20;
        button2.w = buttonWidth;
        button2.h = buttonHeight;

        SDL_Surface* surfaceMessage1 = TTF_RenderText_Solid(font, "Load game", textColor);
        SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(font, "Quit", textColor);

        message1 = SDL_CreateTextureFromSurface(prog.renderer, surfaceMessage1);
        message2 = SDL_CreateTextureFromSurface(prog.renderer, surfaceMessage2);

        SDL_QueryTexture(message1, NULL, NULL, &textRect1.w, &textRect1.h);
        SDL_QueryTexture(message2, NULL, NULL, &textRect2.w, &textRect2.h);

        textRect1.x = button1.x + (button1.w - textRect1.w) / 2;
        textRect1.y = button1.y + (button1.h - textRect1.h) / 2;

        textRect2.x = button2.x + (button2.w - textRect2.w) / 2;
        textRect2.y = button2.y + (button2.h - textRect2.h) / 2;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point mousePoint = { x, y };

                if (SDL_PointInRect(&mousePoint, &button1)) {
                    initMap();
                    initStage();
                } else if (SDL_PointInRect(&mousePoint, &button2)) {
                    running = 0;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point mousePoint = { x, y };

                button1Hovered = SDL_PointInRect(&mousePoint, &button1);
                button2Hovered = SDL_PointInRect(&mousePoint, &button2);
            }
        }

        SDL_SetRenderDrawColor(prog.renderer, 0, 0, 0, 255);
        SDL_RenderClear(prog.renderer);
        SDL_RenderCopy(prog.renderer, backgroundTexture, NULL, NULL);

        SDL_SetRenderDrawColor(prog.renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
        SDL_RenderFillRect(prog.renderer, &button1);
        SDL_RenderFillRect(prog.renderer, &button2);

        SDL_SetRenderDrawColor(prog.renderer, button1Hovered ? hoverBorderColor.r : borderColor.r, button1Hovered ? hoverBorderColor.g : borderColor.g, button1Hovered ? hoverBorderColor.b : borderColor.b, button1Hovered ? hoverBorderColor.a : borderColor.a);
        SDL_RenderDrawRect(prog.renderer, &button1);

        SDL_SetRenderDrawColor(prog.renderer, button2Hovered ? hoverBorderColor.r : borderColor.r, button2Hovered ? hoverBorderColor.g : borderColor.g, button2Hovered ? hoverBorderColor.b : borderColor.b, button2Hovered ? hoverBorderColor.a : borderColor.a);
        SDL_RenderDrawRect(prog.renderer, &button2);

        SDL_RenderCopy(prog.renderer, message1, NULL, &textRect1);
        SDL_RenderCopy(prog.renderer, message2, NULL, &textRect2);

        SDL_RenderPresent(prog.renderer);

        SDL_DestroyTexture(message1);
        SDL_DestroyTexture(message2);
        SDL_FreeSurface(surfaceMessage1);
        SDL_FreeSurface(surfaceMessage2);
    }

    SDL_DestroyTexture(backgroundTexture);
    return 0;
}
