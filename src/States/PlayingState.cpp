#include <stdio.h>

#include "SDL2/SDL.h"
#include "../GameEngine.h"
//#include "state.h"
#include "PlayingState.h"
#include "../Player.h"


PlayingState PlayingState::m_PlayingState;

bool play = false;

void PlayingState::Init(GameEngine* game)
{
	player.Initialize(game);
	worldmap.LoadMap(game);
	inputHandler.Init(&player, &worldmap);
	game->camera.reset();
	game->camera.setPosition(0,0);
	//game->camera.moveCameraTo(-1000,0,10000);
}

void PlayingState::Cleanup()
{


}

void PlayingState::Pause()
{
}

void PlayingState::Resume()
{


}

void PlayingState::HandleEvents(GameEngine* game)
{
	inputHandler.CheckInput(game);
}

void PlayingState::Update(GameEngine* game)
{

	game->camera.update(game->millisecondFTime);

}

void PlayingState::Draw(GameEngine* game)
{
	//Draw the world
	worldmap.Draw(game, player.offset_x+game->camera.getXPosition(), player.offset_y+game->camera.getYPosition());

	//do some fancy anitmation
	player.sprite->PlayAnimation();
	player.Draw(game, game->millisecondFTime);


}

