#include "Player.h"
#include "Animation/AnimationReader.h"

void Player::Initialize(GameEngine* game)
{

	this->movmentSpeed = 2;
	this->position.x = 600;
	this->position.y = 496;
	AnimationReader ar("Data/animation.json");

	this->sprite = ar.LoadAnimations("Data/animation.json", game);

	this->sprite->SetCurrentBehaviour(1);

}
