
#include "GraphicHelper.h"

void GraphicHelper::PrintString(std::string text,SDL_Surface* screen, SDL_Color text_color, int posX, int posY, int fontSize)
{
	/*TTF_Font *font;
	SDL_Rect textLocation = {posX-(((text.length())*(fontSize))/3), posY, 0, 0};

	font = TTF_OpenFont("Fonts/FreeSerifBold.ttf", fontSize);
	if (font == NULL)
	{
		cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}

   // Write text to surface
	SDL_Surface *dtext;
	dtext = TTF_RenderText_Blended(font,
	text.c_str(),
	text_color);

	if (dtext == NULL)
	{
		cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}

   	if (SDL_BlitSurface(dtext, NULL, screen, &textLocation) != 0)
	{
		cerr << "SDL_BlitSurface() Failed: " << SDL_GetError() << endl;
	}*/
}



