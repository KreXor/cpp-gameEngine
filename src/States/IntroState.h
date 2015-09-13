#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "SDL2/SDL.h"
#include "State.h"

class IntroState : public State
{
public:
	void Init(GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static IntroState* Instance() {
		return &m_IntroState;
	}

protected:
	IntroState() { }

private:
	static IntroState m_IntroState;

	SDL_Surface* bg;
	SDL_Surface* fader;
	int alpha;
};

#endif
