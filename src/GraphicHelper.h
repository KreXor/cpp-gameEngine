#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <iostream>

#include "SDL2/SDL.h"
#include <string>
#include "vector"
#include "SDL2/SDL_ttf.h"

using namespace std;

class GraphicHelper
{
public:

	void PrintString(std::string text,SDL_Surface* screen, SDL_Color text_color, int posX, int posY, int fontSize);
	void LoadSprites();
};

#endif
