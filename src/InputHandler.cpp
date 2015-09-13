#include "InputHandler.h"


void InputHandler::Init(Player* player, Map* map)
{
	this->map = map;
	this->player = player;

	keyJump = SDLK_UP;
	keyRunLeft = SDLK_LEFT;
	keyRunRight = SDLK_RIGHT;
	keyDuck = SDLK_DOWN;
	KeyEscape = SDLK_ESCAPE;

}
void InputHandler::CheckInput(GameEngine* game)
{

	SDL_Event event;



	while (SDL_PollEvent(&event) )
		{
			// SDL_QUIT event has come in, quit.
			if ( event.type == SDL_QUIT )
			{
				SDL_Quit();
				exit(1);
			}

			CheckPlayerMovement(&event, game);


		}
	/*
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		//CheckPlayerMovement(keystate);

		if(keystate[KeyEscape]){
			SDL_Quit();
			exit(1);
		}
	}*/

	//this->physics.ApplyPhysicsOnPlayer(player, *map);

}

void InputHandler::CheckPlayerMovement(SDL_Event* event, GameEngine* game)
{

	if (event->type == SDL_KEYDOWN)
	{
		Player tempPlayer = *player;
		if(event->key.keysym.sym == keyRunRight){
			player->direction = 1;
			player->sprite->SetCurrentBehaviour(2);
			game->camera.moveCameraTo(-150,0,1000);
		}

		else if(event->key.keysym.sym == keyRunLeft){
			player->direction = -1;
			player->sprite->SetCurrentBehaviour(2);
			game->camera.moveCameraTo(150,0,1000);
		}
		else if(event->key.keysym.sym == keyJump){
			//if(player->inAir == false)
			//{
				player->currentFallingSpeed = -10;
				player->sprite->SetCurrentBehaviour(3);
			//}

		}
		else if(event->key.keysym.sym == keyDuck){
			player->sprite->SetCurrentBehaviour(4);
		}

		if(event->key.keysym.sym == SDLK_KP_PLUS)
		{
			game->camera.zoomIn();
		}
		if(event->key.keysym.sym == SDLK_KP_MINUS)
		{
			game->camera.zoomOut();
		}
		if ( event->key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_Quit();
			exit(1);
		}
	}
	else
	{
		//game->camera.moveCameraTo(0,0,5000);
		player->direction = 0;
		player->sprite->SetCurrentBehaviour(1);
	}


}
