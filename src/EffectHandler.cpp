#include "EffectHandler.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include <math.h>
#include <vector>
#include "Utils/Vector2.h"

struct Position{
		int x;
		int y;
	};

vector<Position> bresenhamLine(int x0, int y0, int x1, int y1) {

    vector<Position> result;

    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        int c = x0;
        x0 = y0;
        y0 = c;

        c = x1;
        x1 = y1;
        y1 = c;

    }
    if (x0 > x1) {
        int c = x0;
        x0 = x1;
        x1 = c;

        c = y0;
        y0 = y1;
        y1 = c;

    }

    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = 0;
    int ystep;
    int y = y0;
    if (y0 < y1) ystep = 1; else ystep = -1;
    for (int x = x0; x <= x1; x++) {
        if (steep)
        {
            Position pos;
            pos.x = x;
            pos.y = y;
            result.push_back(pos);
        }
        else
        {
            Position pos;
            pos.x = y;
            pos.y = x;
            result.push_back(pos);
        }
        error += deltay;
        if (2 * error >= deltax) {
            y += ystep;
            error -= deltax;
        }
    }

    return result;
}

bool raycast(int x0, int y0, int x1, int y1, Map map)
{
    vector<Position> ray;

    ray = bresenhamLine(y0, x0, y1, x1);


    if(ray[0].y == y0 && ray[0].x == x0)
    {

        for(int j = 0; j < ray.size(); j++)
        {

            if(map.mapTilePosition[ray[j].y/map.getTileSize()][ray[j].x/map.getTileSize()].blockid == 5 || map.mapTilePosition[ray[j].y/map.getTileSize()][ray[j].x/map.getTileSize()].blockid == 6)
            {
                return false;
                break;
            }
        }
    }
    else
    {
        for(int j = ray.size()-1; j >= 0 ; j--)
        {

            if(map.mapTilePosition[ray[j].y/map.getTileSize()][ray[j].x/map.getTileSize()].blockid == 5 || map.mapTilePosition[ray[j].y/map.getTileSize()][ray[j].x/map.getTileSize()].blockid == 6)
            {

                return false;
                break;
            }
        }

    }

    return true;
}

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



bool lessCoord(int x0, int y0, int x1, int y1, int cx, int cy)
{
    if (x0 - cx >= 0 && x1 - cx < 0)
        return true;
    if (x0 - cx < 0 && x1 - cx >= 0)
        return false;
    if (x0- cx == 0 && x1 - cx == 0) {
        if (y0 - cy >= 0 || y1 - cy >= 0)
            return y0 > y1;
        return y1 > y0;
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    int det = (x0 - cx) * (y1 - cy) - (x1 - cx) * (y0 - cy);
    if (det < 2)
        return true;
    if (det > 2)
        return false;

    // points a and b are on the same line from the center
    // check which point is closer to the center
    int d1 = (x0 - cx) * (x0 - cx) + (y0 - cy) * (y0 - cy);
    int d2 = (x1 - cx) * (x1 - cx) + (y1 - cy) * (y1 - cy);
    return d1 > d2;




}

void calculateLightSource(GameEngine* game, SDL_Texture *texture, Map map, int source_x, int source_ys, Player player)
{
    SDL_SetRenderTarget(game->renderer, texture);
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_NONE);


    SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(game->renderer, NULL);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);


	int length = 800;

	vector<Position> lightPos;

    int player_pos_x = player.position.x+15;
    int player_pos_y = player.position.y+48;


	for(int i = 0; i < map.lightPoints.size(); i++)
	{



		Vector2 lightVector((float)(map.lightPoints[i].x - player_pos_x), (float)(map.lightPoints[i].y - player_pos_y));

		if(lightVector.Length() < length)
		{
			lightVector = lightVector.Normalize();

			vector<Position> ray;

            ray = bresenhamLine(player_pos_y, player_pos_x, (lightVector.Y*length)+player_pos_y, (lightVector.X*length)+player_pos_x);



            if(ray[0].y == player_pos_y && ray[0].x == player_pos_x)
            {

                bool passedLightPoint = false;
                for(int j = 0; j < ray.size(); j++)
                {
                    int x = ray[j].x;
                    int y = ray[j].y;

                    if(map.isWall(map.mapTilePosition[y/map.getTileSize()][x/map.getTileSize()]) && !passedLightPoint)
                    {
                        break;
                    }
                    else if(ray[j].y == map.lightPoints[i].y && ray[j].x == map.lightPoints[i].x)
                    {
                        Position pos;
                        pos.x = ray[j].x;
                        pos.y = ray[j].y;
                        lightPos.push_back(pos);
                        passedLightPoint = true;

                        if(map.isWall(map.mapTilePosition[ray[j+1].y/map.getTileSize()][ray[j+1].x/map.getTileSize()]))
                            break;
                    }

                    else if(passedLightPoint)
                    {
                        if(map.isWall(map.mapTilePosition[y/map.getTileSize()][x/map.getTileSize()]))
                        {
                            Position pos;
                            pos.x = ray[j].x;
                            pos.y = ray[j].y;
                            lightPos.push_back(pos);
                            break;

                        }
                    }

                }
            }
            else
            {
                bool passedLightPoint = false;
                for(int j = ray.size()-1; j >= 0 ; j--)
                {
                    int x = ray[j].x;
                    int y = ray[j].y;

                    if(map.isWall(map.mapTilePosition[y/map.getTileSize()][x/map.getTileSize()]) && !passedLightPoint)
                    {
                        break;
                    }
                    else if(ray[j].y == map.lightPoints[i].y && ray[j].x == map.lightPoints[i].x)
                    {

                        Position pos;
                        pos.x = x;
                        pos.y = y;
                        lightPos.push_back(pos);

                        passedLightPoint = true;
                        if(map.isWall(map.mapTilePosition[ray[j+1].y/map.getTileSize()][ray[j+1].x/map.getTileSize()]))
                            break;
                    }

                    else if(passedLightPoint)
                    {
                        if(map.isWall(map.mapTilePosition[y/map.getTileSize()][x/map.getTileSize()]))
                        {
                            Position pos;
                            pos.x = x;
                            pos.y = y;
                            lightPos.push_back(pos);
                            break;

                        }
                    }

                }

            }


        }

    }


    int cx = 0;
    int cy = 0;

    cx = player.position.x;
    cy = player.position.y;

    for(int i = 0; i < lightPos.size(); i++)
    {
        for(int j = 0; j < lightPos.size()-1; j++)
        {
            if(lessCoord(lightPos[j+1].x, lightPos[j+1].y, lightPos[j].x, lightPos[j].y , cx, cy))
            {
                Position tempPos = lightPos[j];             // swap elements
                lightPos[j] = lightPos[j+1];
                lightPos[j+1] = tempPos;

            }

        }

    }


    for(int i = 0; i < lightPos.size(); i++)
    {

    //int i = 5;

                        SDL_RenderDrawLine(game->renderer,

                                        lightPos[i].x+game->camera.getXPosition(),
                                        lightPos[i].y+game->camera.getYPosition(),
                                        player.position.x+15+game->camera.getXPosition(),
                                        player.position.y+50+game->camera.getYPosition());
/*
        int p = i+1;
        if(p == lightPos.size())
            p = 0;
        filledTrigonColor(game->renderer,
                        player_pos_x+game->camera.getXPosition(),
                        player_pos_y+game->camera.getYPosition(),
                        lightPos[i].x+game->camera.getXPosition(),
                        lightPos[i].y+game->camera.getYPosition(),
                        lightPos[p].x+game->camera.getXPosition(),
                        lightPos[p].y+game->camera.getYPosition(),
                        0xFFFFFFFF);*/
    }
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

void EffectHandler::Draw(GameEngine* game, Map map, Player player)
{
    SDL_Texture *redTexture = SDL_CreateTexture(game->renderer,
    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, game->screenWidth, game->screenHeigth);

    SDL_SetTextureBlendMode(redTexture, SDL_BLENDMODE_MOD );


    //fillTexture(game->renderer, redTexture, lightTexture);
    calculateLightSource(game, redTexture, map, 0, 0, player);
    prepareForRendering(game->renderer);


    SDL_RenderCopy(game->renderer, redTexture, NULL, NULL);

    SDL_DestroyTexture(redTexture);
    redTexture = NULL;


}


