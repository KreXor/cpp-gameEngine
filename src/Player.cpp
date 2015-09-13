#include "Player.h"
#include "Animation/AnimationReader.h"

void Player::Initialize(GameEngine* game)
{

	offset_x = 0;
	offset_y = 200;

	this->movmentSpeed = 2;
	this->position.x = 600;
	this->position.y = 496;
	AnimationReader ar("Data/animation.json");

	this->sprite = ar.LoadAnimations("Data/animation.json", game);

	this->sprite->SetCurrentBehaviour(1);

}

void Player::Draw(GameEngine *game, float gameTime){
	drawpos.x = position.x+game->camera.getXPosition();
	drawpos.y = position.y+game->camera.getYPosition();
	sprite->Draw(&drawpos, game, gameTime, direction);
}
