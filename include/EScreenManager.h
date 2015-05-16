#pragma once
#include "Ecore.h"
#include "drawable/ETexture.h"
#include "drawable/ETextureHandler.h"

class ETextureHandler;

class EScreenManager
{
public:
	EScreenManager();
	~EScreenManager();

	/* Temporary Functions for adaptation */
	bool loadMedia();

	/* Primitive functions */
	void render();
	void update(Uint32 currentTime, Uint32 accumulator);
	void handleEvent(SDL_Event e);

private:
	ETextureHandler *textureHandler;
};
