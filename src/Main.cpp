#include "GameEngine.h"
#include "States/IntroState.h"
#include "Player.h"

#define WIDTH 1280
#define HEIGHT 1024

#define TICK_INTERVAL 10

Uint32 TimeLeft(void)
{
    static Uint32 next_time = 0;
    Uint32 now;

    now = SDL_GetTicks();
    if ( next_time <= now ) {
        next_time = now+TICK_INTERVAL;
        return(0);
    }
    return(next_time-now);
}

int main ( int argc, char *argv[] )
{
	GameEngine game;

	game.Init( "The game", WIDTH, HEIGHT,32,false);

	game.ChangeState( IntroState::Instance() );

	Uint32 old_time, current_time;
	current_time = SDL_GetTicks();

	bool quit = true;

	while ( quit )
	{

		//Get time since last frame.
		old_time = current_time;
		current_time = SDL_GetTicks();
		game.millisecondFTime = (current_time - old_time);

		SDL_SetRenderDrawColor( game.renderer, 0, 0, 0, 255 );
		SDL_RenderClear(game.renderer);

		game.HandleEvents();
		game.Update();
		game.Draw();


		SDL_RenderPresent(game.renderer);
		SDL_Delay(TimeLeft());
	}

	game.Cleanup();

	return 0;
}
