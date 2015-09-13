#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "SDL2/SDL.h"
#include "State.h"

class MenuState : public State
{
public:
	void Init(GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static MenuState* Instance() {
		return &m_MenuState;
	}

protected:
	MenuState() { }

private:
	static MenuState m_MenuState;

	SDL_Surface* bg;
	SDL_Surface* fader;
	int alpha;

};

#endif
