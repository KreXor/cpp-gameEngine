#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Player.h"
#include "Map/Map.h"
#include "Physics/Physics.h"
#include "GameEngine.h"
class InputHandler
{

private:
	Player* player;
	Map* map;
	Physics physics;

    struct key{
		bool pressed = false;
		SDL_Keycode keycode;
	};



	void CheckPlayerMovement(SDL_Event* event, GameEngine* game);
public:
	void Init();
	void CheckInput(GameEngine* game);

	key keyRunUp;
	key keyRunLeft;
	key keyRunRight;
	key keyRunDown;
	key KeyEscape;

};
#endif
