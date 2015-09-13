#include "Weapon.h"
#include "../Animation/AnimationReader.h"

void Weapon::Initialize(GameEngine* game)
{

	this->position.x = 600;
	this->position.y = 496;

	AnimationReader ar("Data/weapon.data");

	this->sprite = ar.LoadAnimations("gun", game);

	this->sprite->SetCurrentBehaviour(1);

}
