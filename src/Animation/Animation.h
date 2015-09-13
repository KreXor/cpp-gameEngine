#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../GameEngine.h"
#include <string>
#include <sstream>

using namespace std;

class Animation {
	int NumberOfFrames;
	int CurrentFrame;

	float animationSpeed;
	float timeSinceLastFrame;

	SDL_Rect* rectangles;
	SDL_Texture* image;
	string myFilename;
public:

	//Animation();
	//~Animation();
	void Init( int number_of_frames, float animationSpeed, string filename, GameEngine* game );
	SDL_Rect* GetFrame(void);
	void SetFrame( int frame_number, int x, int y, int w, int h);
	void NextFrame(void);
	void LastFrame(void);
	void Draw(SDL_Rect* position, GameEngine* game, float gameTime, int direction);
	void PlayAnimation();
};

extern SDL_Texture *Load_image( std::string filename, GameEngine* game );

#endif
