#ifndef ARMOR_H
#define ARMOR_H

#include "SDL2/SDL.h"
#include "Item.h"
#include <vector>
#include <string>

class Armor : public Item
{
protected:

private:
	struct Armor_items{
		Sprite * sprite;
		Position position;
		std::string name;
	};

public:
	std::vector<Armor_items> a_item;
	void Initialize(GameEngine* game);
	void Draw(GameEngine *game, float gameTime);
};

#endif

