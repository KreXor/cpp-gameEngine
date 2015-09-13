#ifndef WEAPON_H
#define WEAPON_H

#include "SDL2/SDL.h"
#include "Item.h"

class Weapon : public Item
{
protected:
	int damage;
	int range;
	int ammunition;

public:
	void Initialize(GameEngine* game);
};

#endif

