#include "Physics.h"
#include <math.h>

void Physics::ApplyPhysicsOnPlayer(Player* player, Map map)
{
	//this->CheckPlayerCollision(player, map);


}

bool Physics::CheckPlayerCollision(Player player, Map map)
{

    SDL_Rect tileRect;
    SDL_Rect playerRect;

    //Calculate where the camera is in the matrice

	//get Y start postion
	int render_y_start = floor(player.position.y/map.getTileSize())-2;
	render_y_start = (render_y_start < 0) ? 0 : render_y_start;
	render_y_start = (render_y_start > map.getTilesHeightCount()) ? map.getTilesHeightCount() : render_y_start;

	//get Y start postion
	int render_y_end = floor(player.position.y/map.getTileSize())+2;
	render_y_end = (render_y_end < 0) ? 0: render_y_end;
	render_y_end = (render_y_end > map.getTilesHeightCount()) ? map.getTilesHeightCount(): render_y_end;

	//get X start postion
	int render_x_start = floor(player.position.x/map.getTileSize())-2;
	render_x_start = (render_x_start < 0) ? 0 : render_x_start;
	render_x_start = (render_x_start > map.getTilesWidthCount()) ? map.getTilesWidthCount() : render_x_start;

	//get X end postion
	int render_x_end = floor(player.position.x/map.getTileSize())+2;
	render_x_end = (render_x_end < 0) ? 0 : render_x_end;
	render_x_end = (render_x_end > map.getTilesWidthCount()) ? map.getTilesWidthCount(): render_x_end;

    for(int y = render_y_start; y < render_y_end; y++)
    {
        for(int x = render_x_start; x < render_x_end; x++)
        {
            if(map.mapTilePosition[y][x].blockid == 5 || map.mapTilePosition[y][x].blockid == 6)
            {
                tileRect.x = map.mapTilePosition[y][x].worldPosition.x;
                tileRect.y = map.mapTilePosition[y][x].worldPosition.y;
                tileRect.w = map.getTileSize()/2;
                tileRect.h = map.getTileSize()/2;

                playerRect.x = player.position.x-17;
                playerRect.y = player.position.y+22;
                playerRect.w = 34;
                playerRect.h = 30;

                if(CollideBoundingBox(playerRect, tileRect))
                {
                    return true;
                }
            }
        }
    }

    return false;
 /*   for(int i = 0; i < map.tilesCount; i++)
	{
        if(map.mapTilePosition[i].blockid == 5 || map.mapTilePosition[i].blockid == 6)
        {
            tileRect.x = map.mapTilePosition[i].worldPosition.x;
            tileRect.y = map.mapTilePosition[i].worldPosition.y;
            tileRect.w = 24;
            tileRect.h = 24;

            playerRect.x = player.position.x-17;
            playerRect.y = player.position.y+22;
            playerRect.w = 34;
            playerRect.h = 30;

            if(CollideBoundingBox(playerRect, tileRect))
            {
                return true;
            }
		}
    }*/
    return false;

}

bool Physics::CollideBoundingBox(SDL_Rect box1, SDL_Rect box2)
{
	if(box1.x + box1.w > box2.x && box1.x <box2.x + box2.w)
		if(box1.y + box1.h > box2.y && box1.y < box2.y + box2.h)
			return true;

	return false;


}
