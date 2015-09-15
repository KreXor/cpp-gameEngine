#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include "Camera.h"
#include "SDL2/SDL.h"
#include "GraphicHelper.h"
#include <vector>



using namespace std;

class State;

class GameEngine
{
public:

	void Init(const char* title, int width=640, int height=480,
		      int bpp=0, bool fullscreen=false);
	void Cleanup();

	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	GraphicHelper graphicHelper;
	SDL_Surface* screen;
	SDL_Renderer* renderer;
	SDL_Window* window;

	int screenWidth;
	int screenHeigth;


	float millisecondFTime;

	Camera camera;

private:
	// the stack of states
	vector<State*> states;

	bool m_running;
	bool m_fullscreen;
};

#endif
