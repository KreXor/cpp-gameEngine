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

	SDL_Keycode keyJump;
	SDL_Keycode keyRunLeft;
	SDL_Keycode keyRunRight;
	SDL_Keycode keyDuck;
	SDL_Keycode KeyEscape;


	void CheckPlayerMovement(SDL_Event* event, GameEngine* game);
public:
	void Init(Player* player, Map* map);
	void CheckInput(GameEngine* game);

};
#endif
