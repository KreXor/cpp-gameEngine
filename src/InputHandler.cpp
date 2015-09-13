#include "InputHandler.h"
#include <iostream>

void InputHandler::Init()
{
	keyRunUp.keycode = SDLK_UP;
	keyRunLeft.keycode = SDLK_LEFT;
	keyRunRight.keycode = SDLK_RIGHT;
	keyRunDown.keycode = SDLK_DOWN;
	KeyEscape.keycode = SDLK_ESCAPE;

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
}

void InputHandler::CheckPlayerMovement(SDL_Event* event, GameEngine* game)
{

	if (event->type == SDL_KEYDOWN)
	{
		if(event->key.keysym.sym == keyRunRight.keycode){
            keyRunRight.pressed = true;
		}

		if(event->key.keysym.sym == keyRunLeft.keycode){
            keyRunLeft.pressed = true;
		}
		if(event->key.keysym.sym == keyRunUp.keycode){
			keyRunUp.pressed = true;

		}
		if(event->key.keysym.sym == keyRunDown.keycode){
			keyRunDown.pressed = true;
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
	if (event->type == SDL_KEYUP)
	{
		if(event->key.keysym.sym == keyRunRight.keycode){
            keyRunRight.pressed = false;
		}

		if(event->key.keysym.sym == keyRunLeft.keycode){
            keyRunLeft.pressed = false;
		}
		if(event->key.keysym.sym == keyRunUp.keycode){
			keyRunUp.pressed = false;

		}
		if(event->key.keysym.sym == keyRunDown.keycode){
			keyRunDown.pressed = false;
		}
	}



}
