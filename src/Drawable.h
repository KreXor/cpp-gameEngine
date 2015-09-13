#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "SDL2/SDL.h"
#include "GameEngine.h"
#include "Animation/Sprite.h"

class Drawable
{

protected:

	struct Position{
		float x;
		float y;
	};


	string type;

	SDL_Rect drawpos;

public:
	Sprite *sprite;
	Position position;

	int direction;

	void Draw(GameEngine *game, float gameTime){
		drawpos.x = position.x+game->camera.getXPosition();
		drawpos.y = position.y+game->camera.getYPosition();
		sprite->Draw(&drawpos, game, gameTime, direction);
	}

};

#endif
