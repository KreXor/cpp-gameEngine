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
    for(int i = 0; i < map.tilesCount; i++)
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
    }
    return false;

}

bool Physics::CollideBoundingBox(SDL_Rect box1, SDL_Rect box2)
{
	if(box1.x + box1.w > box2.x && box1.x <box2.x + box2.w)
		if(box1.y + box1.h > box2.y && box1.y < box2.y + box2.h)
			return true;

	return false;


}
