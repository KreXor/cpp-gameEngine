#ifndef EFFECTHANDLER_H
#define EFFECTHANDLER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameEngine.h"
#include <string.h>
#include <cstdlib>
#include <fstream>
#include "Map/Map.h"
#include "Player.h"

class EffectHandler
{

private:
    SDL_Texture *lightTexture;
public:
	void Draw(GameEngine* game, Map map, Player player);
	void Init(GameEngine* game);

};


#endif
