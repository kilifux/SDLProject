#pragma once
#include <string>
#include <SDL_image.h>
class Actor
{
public:
	Actor();

	~Actor();

	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	void free();

	void render(int x, int y, SDL_Renderer* gRenderer);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
	
};

