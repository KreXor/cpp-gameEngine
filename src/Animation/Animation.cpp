#include "Animation.h"
//#include "sprite.h"
#include <string>

void Animation::Init( int number_of_frames, float animationSpeed, string filename, GameEngine* game)
{
	this->myFilename = filename;
	this->animationSpeed = animationSpeed;
	this->image =  Load_image( filename, game );

	this->rectangles = new SDL_Rect[ number_of_frames ];

	this->NumberOfFrames = number_of_frames - 1;

	this->CurrentFrame = 0;
	this->timeSinceLastFrame = 0;
}

SDL_Rect* Animation::GetFrame(void)
{
	return &rectangles[ CurrentFrame ];
}

void Animation::SetFrame( int frame_number, int x, int y, int w, int h)
{
	this->rectangles[ frame_number ].x = x;
	this->rectangles[ frame_number ].y = y;
	this->rectangles[ frame_number ].w = w;
	this->rectangles[ frame_number ].h = h;
}


void Animation::PlayAnimation(void)
{
	if(animationSpeed <= timeSinceLastFrame)
	{
		NextFrame();
		timeSinceLastFrame = 0;
	}
}

void Animation::NextFrame(void)
{
	this->CurrentFrame++;
	if(CurrentFrame > NumberOfFrames) CurrentFrame = 0;
}

void Animation::LastFrame(void)
{
	this->CurrentFrame--;
	if(CurrentFrame < 0) CurrentFrame = NumberOfFrames;
}


void Animation::Draw(SDL_Rect* position, GameEngine* game, float gameTime, int direction)
{
	timeSinceLastFrame += gameTime;
	SDL_Rect* frame = GetFrame();
	position->h = frame->h;
	position->w =frame->w;

	if(direction == 1)
	{
		SDL_RenderCopyEx(game->renderer, image, GetFrame(), position, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		SDL_RenderCopy(game->renderer, image, GetFrame(), position);
	}
	//SDL_BlitSurface( image, , screen, position );
}

SDL_Texture *Load_image( string filename, GameEngine* game )
{

	SDL_Surface* loaded_image = NULL;

	if(filename.c_str() == NULL)
	{
		return NULL;
	}

	loaded_image = SDL_LoadBMP( filename.c_str() );

	if( loaded_image == NULL )
	{
		return NULL;
	}

	Uint32 colorkey = SDL_MapRGB( loaded_image->format, 255, 0, 255);

	SDL_SetColorKey( loaded_image, SDL_RLEACCEL | SDL_TRUE, colorkey);


	SDL_Texture *bitmapTex = SDL_CreateTextureFromSurface(game->renderer, loaded_image);

	SDL_FreeSurface(loaded_image);
	return bitmapTex;

}
