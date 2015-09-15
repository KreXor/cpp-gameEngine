#ifndef MAP_H
#define MAP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../GameEngine.h"
#include <string.h>
#include <cstdlib>
#include <fstream>

class Map
{

private:

	struct Tile{
		SDL_Rect worldPosition;
		SDL_Rect imagePosition;
		int layer;
		int type;
		int t_size;
		int boundingBoxType; // so we know if there is gound have a slope or note, see physics.c for more info.
	};

	SDL_Texture* tilesImage[10];



	SDL_Texture *Load_image( string filename, GameEngine* game );

	void readMapData(GameEngine* game);

public:
	int tilesCount;
	Tile* mapTilePosition;
	void LoadMap(GameEngine* game);
	void Draw(GameEngine* game);



};


#endif
