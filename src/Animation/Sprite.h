#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <sstream>
#include "Animation.h"
#include "AnimationNode.h"
#include "../GameEngine.h"

using namespace std;

#define BEHAVIOUR_DEFAULT	1
#define BEHAVIOUR_WALKING 	2
#define BEHAVIOUR_RUNNING 	3
#define BEHAVIOUR_JUMPING 	4


class Sprite {
	SDL_Surface* frames;
	int* NumberOfFrames;
	int NumberOfAnimations;
	int current_behaviour;
	AnimationNode* pAnimations;

public:
	Sprite();
	~Sprite();

	void Draw(SDL_Rect *position, GameEngine *game, float gameTime, int direction);
	void NextFrame();
	void LastFrame();

	void AddAnimation(Animation* anim, int behaviour_number);
	void SetCurrentBehaviour(int behaviour);
	void PlayAnimation();
	int GetCurrentBehaviour();

};



#endif
