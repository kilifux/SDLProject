#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Actor.h"

const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 680;

bool init();

bool loadMedia();

void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

Actor gPixelUfo;
Actor gPixelCow;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{

	bool success = true;

	if (!gPixelUfo.loadFromFile("ufo.png", gRenderer))
	{
		printf("Failed to load ufo!\n");
		success = false;
	}

	if (!gPixelCow.loadFromFile("cow.png", gRenderer))
	{
		printf("Failed to load cow!\n");
		success = false;
	}

	return success;
}

void close()
{
	gPixelUfo.free();
	gPixelCow.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			double ufoX = 0;

			while (!quit)
			{
				ufoX += 0.1;

				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor(gRenderer, 220, 220, 220, 0xFF);
				SDL_RenderClear(gRenderer);

				gPixelCow.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 256, gRenderer);

				gPixelUfo.render(ufoX, 0, gRenderer);

				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();

	return 0;
}