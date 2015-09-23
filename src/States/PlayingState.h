#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "SDL2/SDL.h"
#include "State.h"
#include "../Player.h"
#include "../Map/Map.h"
#include "../Physics/Physics.h"
#include "../Physics/Lightning.h"
#include "../InputHandler.h"

class PlayingState : public State
{
public:
	void Init(GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static PlayingState* Instance() {
		return &m_PlayingState;
	}



protected:
	PlayingState() { }


private:

	Player player;
	Map worldmap;
	Lightning lightning;
	Physics physics;
	InputHandler inputHandler;
	static PlayingState m_PlayingState;

	SDL_Surface* bg;
	SDL_Surface* map;
	SDL_Surface* fader;
	int alpha;
};

#endif
