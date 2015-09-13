#include <iostream>


#include "SDL2/SDL.h"
#include "GameEngine.h"
#include "State.h"
#include "SDL2/SDL_ttf.h"


void GameEngine::Init(const char* title, int width, int height,
						 int bpp, bool fullscreen)
{

	screenWidth = width;
	screenHeigth = height;

	// Initialize SDL_ttf library
/*	if (TTF_Init() != 0)
	{
		cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
		SDL_Quit();
		exit(1);
	}*/

	int flags = 0;

	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);


/*	if ( fullscreen ) {
		flags = SDL_FULLSCREEN;
	}*/

	SDL_Window* window = SDL_CreateWindow("Maximized text",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      width,
                                      height,
                                      SDL_WINDOW_SHOWN);

	screen = SDL_GetWindowSurface(window);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//screen = SDL_SetVideoMode(width, height, bpp, flags);

	m_fullscreen = fullscreen;
	m_running = true;

}

void GameEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// switch back to windowed mode so other
	// programs won't get accidentally resized
	if ( m_fullscreen ) {
		SDL_Window* window = SDL_CreateWindow("Maximized text",
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      screenWidth,
                                      screenHeigth,
                                      SDL_WINDOW_RESIZABLE);

		screen = SDL_GetWindowSurface(window);
	}


	// shutdown SDL
	SDL_Quit();
}

void GameEngine::ChangeState(State* state)
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back() ->Init(this);
}

void GameEngine::PushState(State* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void GameEngine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}


void GameEngine::HandleEvents()
{
	states.back()->HandleEvents(this);
}

void GameEngine::Update()
{
	states.back()->Update(this);
}

void GameEngine::Draw()
{
	states.back()->Draw(this);
}
