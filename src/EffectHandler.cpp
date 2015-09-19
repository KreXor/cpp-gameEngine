#include "EffectHandler.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include <math.h>
#include <vector>

// Swap the values of A and B
void Swap(int *a, int *b) {
    int *c = a;
    a = b;
    b = c;
}

struct Position{
		int x;
		int y;
	};

// Returns the list of points from (x0, y0) to (x1, y1)
vector<Position> BresenhamLine(int x0, int y0, int x1, int y1) {
    // Optimization: it would be preferable to calculate in
    // advance the size of "result" and to use a fixed-size array
    // instead of a list.
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

bool CollideBoundingBox(SDL_Rect box1, SDL_Rect box2)
{
	if(box1.x + box1.w > box2.x && box1.x <box2.x + box2.w)
		if(box1.y + box1.h > box2.y && box1.y < box2.y + box2.h)
			return true;

	return false;


}


void calculateLightSource(GameEngine* game, SDL_Texture *texture, Map map, int source_x, int source_ys, Player player)
{
/*    SDL_SetRenderTarget(game->renderer, texture);
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_NONE);


    SDL_SetRenderDrawColor(game->renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(game->renderer, NULL);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

    int render_y_start = floor(player.position.y/map.getTileSize())-10;
	render_y_start = (render_y_start < 0) ? 0 : render_y_start;
	render_y_start = (render_y_start > map.getTilesHeightCount()) ? map.getTilesHeightCount() : render_y_start;

	//get Y start postion
	int render_y_end = floor(player.position.y/map.getTileSize())+10;
	render_y_end = (render_y_end < 0) ? 0: render_y_end;
	render_y_end = (render_y_end > map.getTilesHeightCount()) ? map.getTilesHeightCount(): render_y_end;

	//get X start postion
	int render_x_start = floor(player.position.x/map.getTileSize())-10;
	render_x_start = (render_x_start < 0) ? 0 : render_x_start;
	render_x_start = (render_x_start > map.getTilesWidthCount()) ? map.getTilesWidthCount() : render_x_start;

	//get X end postion
	int render_x_end = floor(player.position.x/map.getTileSize())+10;
	render_x_end = (render_x_end < 0) ? 0 : render_x_end;
	render_x_end = (render_x_end > map.getTilesWidthCount()) ? map.getTilesWidthCount(): render_x_end;
	//Render all tiles on screen

	vector<Position> lightPos;
    for(int y = render_y_start; y < render_y_end; y++)
    {
        for(int x = render_x_start; x < render_x_end; x++)
        {
            vector<Position> ray;

            if(floor((player.position.y+50)/map.getTileSize())<y && floor((player.position.x+15)/map.getTileSize())<x)
            {
                ray = BresenhamLine(floor((player.position.y+50)/map.getTileSize()),floor((player.position.x+15)/map.getTileSize()), y, x);

                for(int j = 0; j < ray.size(); j++)
                {

                    if(map.mapTilePosition[ray[j].y][ray[j].x].blockid == 5 || map.mapTilePosition[ray[j].y][ray[j].x].blockid == 6)
                    {
                        SDL_RenderDrawLine(game->renderer,
                                        player.position.x+15+game->camera.getXPosition(),
                                        player.position.y+50+game->camera.getYPosition(),
                                        ray[j].x*map.getTileSize()+game->camera.getXPosition(),
                                        ray[j].y*map.getTileSize()+game->camera.getYPosition());

                        Position pos;
                        pos.x = ray[j].x;
                        pos.y = ray[j].y;
                        lightPos.push_back(pos);

                        break;

                    }
                }
            }
            else if(floor((player.position.y+50)/map.getTileSize())>y && floor((player.position.x+15)/map.getTileSize())>x)
            {
                ray = BresenhamLine(floor((player.position.y+50)/map.getTileSize()),floor((player.position.x+15)/map.getTileSize()), y, x);

                for(int j = ray.size()-1; j >0; j--)
                {

                    if(map.mapTilePosition[ray[j].y][ray[j].x].blockid == 5 || map.mapTilePosition[ray[j].y][ray[j].x].blockid == 6)
                    {
                        SDL_RenderDrawLine(game->renderer,
                                        player.position.x+15+game->camera.getXPosition(),
                                        player.position.y+50+game->camera.getYPosition(),
                                        ray[j].x*map.getTileSize()+game->camera.getXPosition(),
                                        ray[j].y*map.getTileSize()+game->camera.getYPosition());
                         Position pos;
                        pos.x = ray[j].x;
                        pos.y = ray[j].y;
                        lightPos.push_back(pos);

                        break;

                    }
                }

            }



        }

    }

    for(int i = 0; i < lightPos.size()-1; i++)
    {
        filledTrigonColor(game->renderer,player.position.x+15+game->camera.getXPosition(), player.position.y+50+game->camera.getYPosition(), lightPos[i].x*map.getTileSize()+game->camera.getXPosition(), lightPos[i].y*map.getTileSize()+game->camera.getYPosition(), lightPos[i+1].x*map.getTileSize()+game->camera.getXPosition(), lightPos[i+1].y*map.getTileSize()+game->camera.getYPosition(), 0xFFFFFFFF);
    }*/
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


    fillTexture(game->renderer, redTexture, lightTexture);

    prepareForRendering(game->renderer);


    SDL_RenderCopy(game->renderer, redTexture, NULL, NULL);

    SDL_DestroyTexture(redTexture);
    redTexture = NULL;


}


