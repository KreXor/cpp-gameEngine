#include "Player.h"
#include "Animation/AnimationReader.h"

void Player::Initialize(GameEngine* game)
{

	this->movmentSpeed = 8;
	this->position.x = 300;
	this->position.y = 300;
	AnimationReader ar("Data/animation.json");

	this->sprite = ar.LoadAnimations("Data/animation.json", game);

	this->sprite->SetCurrentBehaviour(1);

}
