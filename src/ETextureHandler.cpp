#include "ETextureHandler.h"

ETextureHandler* ETextureHandler::instance = NULL;

ETextureHandler::ETextureHandler()
{
}

ETextureHandler::~ETextureHandler()
{
	removeTexture();
}

ETextureHandler* ETextureHandler::getInstance() {
	if (instance == NULL) {
		instance = new ETextureHandler();
	}

	return instance;
}

void ETextureHandler::createTexture(int x, int y)
{
	static int maxCount = 0;
	if (maxCount < 10) {
		ETexture*	texture = new ETexture(x, y);
		textureList.push_front(texture);

		INFO("New texture created.");
		INFO("    ( %d, %d ) / total: %d", x, y, textureList.size());
	}
}

void ETextureHandler::removeTexture()
{
	list<ETexture*>::iterator	iter;
	while (textureList.empty() == false) {
		iter = textureList.begin();
		delete *iter;
		textureList.erase(iter);
	}
}

void ETextureHandler::handleEvent(SDL_Event e)
{
	INFO("texture handle event!");
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		SDL_MouseButtonEvent *me = &e.button;
		INFO("Handle event! type: %d", e.button.button);
		if (me->button == SDL_BUTTON_LEFT) {
			createTexture(me->x, me->y);
			propagateEvent(e);
		}
		else if (me->button == SDL_BUTTON_RIGHT) {
			removeTexture();
		}
	}
}

void ETextureHandler::propagateEvent(SDL_Event e)
{
	list<ETexture*>::iterator	iter = textureList.begin();
	while (iter != textureList.end()) {
		ETexture* texture = *iter;
		texture->animateStart(SDL_GetTicks());
		iter++;
	}
}

void ETextureHandler::render()
{
	list<ETexture*>::iterator	iter = textureList.begin();
	while (iter != textureList.end()) {
		ETexture* texture = *iter;
		if (texture != NULL) {
			texture->draw();
			INFO("List Texture(%p) rendered !", texture);
		} else {
			INFO("List Texture is NULL. count: %d", textureList.size());
		}
		iter++;
	}
}

void ETextureHandler::update(Uint32 currentTime, Uint32 accumulator)
{
	list<ETexture*>::iterator	iter = textureList.begin();
	while (iter != textureList.end()) {
		ETexture* texture = *iter;
		if (texture != NULL)
			texture->calculate(currentTime, accumulator);
		iter++;
	}
}