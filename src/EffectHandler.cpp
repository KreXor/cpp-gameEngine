#include "EffectHandler.h"


SDL_Texture *Load_image2( string filename, GameEngine* game )
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

void fillTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *lightTexture)
{
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);


    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(renderer, NULL);

    SDL_Rect rect;
    rect.x = (1280/2)-(600/2);
    rect.y = (1024/2)-(512/2);
    rect.w = 600;
    rect.h = 512;

    SDL_RenderCopy(renderer, lightTexture , NULL, &rect);
}

void prepareForRendering(SDL_Renderer *renderer)
{
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
}

void checkSdlError()
{
    const char *sdlError = SDL_GetError();
    if(sdlError && *sdlError)
    {
        ::std::cout << "SDL ERROR: " << sdlError << ::std::endl;
    }
}

void EffectHandler::Init(GameEngine* game)
{
    lightTexture = Load_image2( "Data/Effects/light.bmp", game );
}

void EffectHandler::Draw(GameEngine* game)
{
    SDL_Texture *redTexture = SDL_CreateTexture(game->renderer,
    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, game->screenWidth, game->screenHeigth);

    SDL_SetTextureBlendMode(redTexture, SDL_BLENDMODE_MOD );


    fillTexture(game->renderer, redTexture, lightTexture);

    prepareForRendering(game->renderer);


    SDL_RenderCopy(game->renderer, redTexture, NULL, NULL);

    SDL_DestroyTexture(redTexture);
    redTexture = NULL;
}


