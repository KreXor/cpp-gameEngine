#ifndef ITEM_H
#define ITEM_H

#include "SDL2/SDL.h"
#include "../Drawable.h"

class Item : public Drawable
{
protected:
	int itemID;
	int animationFrame;
	string type;

public:
	Item();

};

#endif
