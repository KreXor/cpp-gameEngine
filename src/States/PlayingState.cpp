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
	inputHandler.Init();
	game->camera.reset();
	game->camera.setPosition(-100,-100);
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

	if(inputHandler.keyRunRight.pressed == true){
        player.position.x += player.movmentSpeed;
        player.direction = 1;
        player.sprite->SetCurrentBehaviour(2);
        //game->camera.moveCameraTo(-150,0,1000);
    }

    else if(inputHandler.keyRunLeft.pressed == true){
        player.position.x -= player.movmentSpeed;
        player.direction = -1;
        player.sprite->SetCurrentBehaviour(2);

        //game->camera.moveCameraTo(150,0,1000);
    }
    else if(inputHandler.keyRunUp.pressed == true){
        player.position.y -= player.movmentSpeed;
        player.direction = -1;
        player.sprite->SetCurrentBehaviour(3);

    }
    else if(inputHandler.keyRunDown.pressed == true){
        player.position.y += player.movmentSpeed;
        player.direction = -1;
        player.sprite->SetCurrentBehaviour(4);
    }
    else
	{
		//game->camera.moveCameraTo(0,0,5000);
		player.direction = 0;
		player.sprite->SetCurrentBehaviour(1);
	}

}

void PlayingState::Draw(GameEngine* game)
{
	//Draw the world
	worldmap.Draw(game);

	//do some fancy anitmation
	player.sprite->PlayAnimation();
	player.Draw(game, game->millisecondFTime);

	game->camera.setFocus(player.position.x, player.position.y);


}

