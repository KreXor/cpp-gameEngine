#include "Armor.h"
#include "../Animation/AnimationReader.h"

void Armor::Initialize(GameEngine* game)
{

	this->position.x = 600;
	this->position.y = 496;

	AnimationReader ar("Data/armor.data");

	Armor_items tmp_item;
	tmp_item.sprite = ar.LoadAnimations("hat", game);
	tmp_item.position.x = 600;
	tmp_item.position.y = 496;
	tmp_item.name = "hat";
	a_item.push_back(tmp_item);


	AnimationReader ar2("Data/armor.data");
	tmp_item.sprite = ar2.LoadAnimations("armor", game);
	tmp_item.position.x = 600;
	tmp_item.position.y = 496;
	tmp_item.name = "armor";
	a_item.push_back(tmp_item);



}

void Armor::Draw(GameEngine *game, float gameTime){

	for (int i=0; i < a_item.size(); i++) {
		drawpos.x = a_item[0].position.x+game->camera.getXPosition();
		drawpos.y = a_item[0].position.y+game->camera.getYPosition();
		a_item[i].sprite->Draw(&drawpos, game, gameTime, direction);
	}

}

