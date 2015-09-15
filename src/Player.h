#ifndef PLAYER_H
#define PLAYER_H

#include "SDL2/SDL.h"
#include "Unit.h"
#include "Animation/Animation.h"
#include "GameEngine.h"
#include "Item/Armor.h"

class Player : public Unit
{
private:
	Armor armor;

public:
	void Initialize(GameEngine* game);

};
#endif
