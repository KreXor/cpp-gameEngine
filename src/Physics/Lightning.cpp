#include "Lightning.h"
/*
*This function calculates a dynamic lightning cast from player.
*Do raycasts to all close corners (lightpoints) to the player and
*draw triangles on blendmode to the target renderer texture.
*/
void Lightning::calculateLightSource(GameEngine* game, SDL_Texture *texture, Map map, Player player)
{
	//Setup new texture as render target
    SDL_SetRenderTarget(game->renderer, texture);
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_NONE);

    SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(game->renderer, NULL);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

	int length = 2000;

	vector<Position> lightPos;

    int player_pos_x = player.position.x+15;
    int player_pos_y = player.position.y+48;

	//Go through all lightpoints on map
	for(int i = 0; i < map.lightPoints.size(); i++)
	{
		//Convert ligthpoints to vector2 in local space
		Vector2 lightVector((float)(map.lightPoints[i].x - player_pos_x), (float)(map.lightPoints[i].y - player_pos_y));

		if(lightVector.Length() < 900)
		{
			lightVector = lightVector.Normalize();

			//Do raycast to all close lightpoints.
			vector<Raycast::Position> ray;
            ray = raycast.bresenhamLine(player_pos_y, player_pos_x, (lightVector.Y*length)+player_pos_y, (lightVector.X*length)+player_pos_x);


			bool passedLightPoint = false;
			int j = 0;

            j = (ray[0].y == player_pos_y && ray[0].x == player_pos_x) ? 0 : ray.size()-1;

			while(true)
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
					if(ray[0].y == player_pos_y && ray[0].x == player_pos_x)
                    {
                        pos.x = ray[j-1].x;
                        pos.y = ray[j-1].y;
                    }
                    else
                    {
                        pos.x = ray[j+1].x;
                        pos.y = ray[j+1].y;
                    }
					pos.lightPoint = true;
					pos.id = i;
					lightPos.push_back(pos);
					passedLightPoint = true;

					/*if(map.isWall(map.mapTilePosition[(int)(ray[j+4].y/map.getTileSize())][(int)(ray[j+4].x/map.getTileSize())]))
						break;
                    if(map.isWall(map.mapTilePosition[(int)(ray[j-4].y/map.getTileSize())][(int)(ray[j-4].x/map.getTileSize())]))
						break;*/

				}

				else if(passedLightPoint)
				{
					if(map.isWall(map.mapTilePosition[y/map.getTileSize()][x/map.getTileSize()]))
					{
						Position pos;
						if(ray[0].y == player_pos_y && ray[0].x == player_pos_x)
						{
                            pos.x = ray[j-1].x;
                            pos.y = ray[j-1].y;
						}
						else
						{
                            pos.x = ray[j+1].x;
                            pos.y = ray[j+1].y;
						}
						pos.id = i;
						pos.lightPoint = false;
						lightPos.push_back(pos);
						break;

					}
				}

				if(ray[0].y == player_pos_y && ray[0].x == player_pos_x)
				{
					j++;
					if(j >= ray.size()) break;
				}
				else
				{
					j--;
					if(j < 0) break;
				}
			}
        }
    }

/*
	for(int i = 0; i < lightPos.size(); i++)
    {
		for(int j = 0; j < lightPos.size()-1; j++)
		{
			Vector2 tempvector1((float)(lightPos[j+1].x - player_pos_x), (float)(lightPos[j+1].y - player_pos_y));
			Vector2 tempvector2((float)(lightPos[j].x - player_pos_x), (float)(lightPos[j].y - player_pos_y));

			if(floor(tempvector1.Normalize().Direction()) > floor(tempvector2.Normalize().Direction()))
			{
				Position tmp = lightPos[j];
				lightPos[j] = lightPos[j+1];
				lightPos[j+1] = tmp;
			}

			}


		}
	}
*/
	//Draw light to texture
    for(int i = 0; i < lightPos.size(); i++)
    {

    //int i = 7;

           /*             SDL_RenderDrawLine(game->renderer,

                                        lightPos[i].x+game->camera.getXPosition(),
                                        lightPos[i].y+game->camera.getYPosition(),
                                        player.position.x+15+game->camera.getXPosition(),
                                        player.position.y+50+game->camera.getYPosition());
*/

        for(int j = i; j < lightPos.size(); j++)
        {
            if(raycast.raycast_insight(lightPos[i].x, lightPos[i].y, lightPos[j].x, lightPos[j].y, map))
            {
                filledTrigonColor(game->renderer,
                    player_pos_x+game->camera.getXPosition(),
                    player_pos_y+game->camera.getYPosition(),
                    lightPos[i].x+game->camera.getXPosition(),
                    lightPos[i].y+game->camera.getYPosition(),
                    lightPos[j].x+game->camera.getXPosition(),
                    lightPos[j].y+game->camera.getYPosition(),
                    0xFFFFFFFF);
                //break;
            }
        }
          //  else if(raycast.raycast_insight(lightPos[i].x, lightPos[i].y, lightPos[x].x, lightPos[x].y, map))
         /*   else
            {
                p++;
                if(p == lightPos.size())
                    p = 0;
            }*/

     //   }
/*
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

void Lightning::prepareForRendering(SDL_Renderer *renderer)
{
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

}

void Lightning::checkSdlError()
{
    const char *sdlError = SDL_GetError();
    if(sdlError && *sdlError)
    {
        ::std::cout << "SDL ERROR: " << sdlError << ::std::endl;
    }
}

void Lightning::Init(GameEngine* game)
{
    //lightTexture = Load_image2( "Data/Effects/light.bmp", game );
}

void Lightning::Draw(GameEngine* game, Map map, Player player)
{
    SDL_Texture *redTexture = SDL_CreateTexture(game->renderer,
    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, game->screenWidth, game->screenHeigth);

    SDL_SetTextureBlendMode(redTexture, SDL_BLENDMODE_MOD );

    calculateLightSource(game, redTexture, map, player);
    prepareForRendering(game->renderer);

    SDL_RenderCopy(game->renderer, redTexture, NULL, NULL);

    SDL_DestroyTexture(redTexture);
    redTexture = NULL;
}

SDL_Texture *Lightning::Load_image2( string filename, GameEngine* game )
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

