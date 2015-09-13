#ifndef ANIMATIONREADER_H
#define ANIMATIONREADER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include "Sprite.h"
#include "Animation.h"
#include "../GameEngine.h"

using namespace std;

class AnimationReader
{
private:
	Sprite *sprite;

public:
	AnimationReader(string path);
	Sprite* LoadAnimations(string filename, GameEngine* game);



};
#endif
