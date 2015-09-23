#ifndef LIGHTNING_H
#define LIGHTNING_H

#include <math.h>
#include <vector>
#include "../Map/Map.h"
#include "../Player.h"
#include "Raycast.h"
#include "../Utils/Vector2.h"
#include "SDL2/SDL2_gfxPrimitives.h"

class Lightning
{

private:

	struct Position{
		float x;
		float y;
		int id;
		bool lightPoint;
	};

	void calculateLightSource(GameEngine* game, SDL_Texture *texture, Map map, Player player);
	void prepareForRendering(SDL_Renderer *renderer);
	void checkSdlError();
	SDL_Texture *Load_image2( string filename, GameEngine* game );
	Raycast raycast;

public:
	void Init(GameEngine* game);
	void Draw(GameEngine* game, Map map, Player player);


};

#endif
