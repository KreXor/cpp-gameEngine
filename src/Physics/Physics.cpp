#include "Physics.h"
#include <math.h>

void Physics::ApplyPhysicsOnPlayer(Player* player, Map map)
{
	this->CheckPlayerCollision(player, map);
	

}

void Physics::CheckPlayerCollision(Player* player, Map map)
{
	SDL_Rect tileRect;
	SDL_Rect playerRect;



	bool collide = false;


	
	Player tempPlayer = *player;

	if(player->direction == -1)
			tempPlayer.offset_x += player->movmentSpeed;

	if(player->direction == 1)
			tempPlayer.offset_x -= player->movmentSpeed;

	for(int i = 0; i < map.tilesCount; i++)
	{

		tileRect.x = map.mapTilePosition[i].worldPosition.x;
		tileRect.y = map.mapTilePosition[i].worldPosition.y;
		tileRect.w = 24;
		tileRect.h = 24;

		playerRect.x = (tempPlayer.position.x - tempPlayer.offset_x)+10;
		playerRect.y = (tempPlayer.position.y - tempPlayer.offset_y);
		playerRect.w = 22;
		playerRect.h = 70;

	

		if(CollideBoundingBox(playerRect, tileRect))
		{
			collide = true;


			/*TILE TYPE 1 '/' */
			if(player->direction == -1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 1)
				{
					collide = false;
					if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= ((playerRect.x+playerRect.w) - tileRect.x))
							tempPlayer.offset_y -= player->movmentSpeed;
				}
			}

			if(player->direction == 1)
			{

				if(map.mapTilePosition[i].boundingBoxType == 1)
				{
					collide = false;
					if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= ((playerRect.x+playerRect.w) - tileRect.x))
							tempPlayer.offset_y += player->movmentSpeed;
				}
			}

			/*TILE TYPE 2 '\' */
			if(player->direction == -1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 2)
				{
					collide = false;
					if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= ((tileRect.x+tileRect.w) - playerRect.x))
							tempPlayer.offset_y += player->movmentSpeed;
				}
			}

			if(player->direction == 1)
			{

				if(map.mapTilePosition[i].boundingBoxType == 2)
				{
					collide = false;
					if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= ((tileRect.x+tileRect.w) - playerRect.x))
							tempPlayer.offset_y -= player->movmentSpeed;
				}
			}


			/*TILE TYPE 3 '_-' */
			if(player->direction == -1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 3)
				{
					collide = false;
					if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= ((tileRect.x+tileRect.w) - playerRect.x)/2)
							tempPlayer.offset_y -= player->movmentSpeed/2;
				}
			}
			if(player->direction == 1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 3)
				{
					collide = false;

					if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= ((tileRect.x+tileRect.w) - playerRect.x)/2)
							tempPlayer.offset_y += player->movmentSpeed/2;
				}
			}
			//              _
			/*TILE TYPE 4 '- ' */
			if(player->direction == -1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 4)
				{
					collide = false;

					if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= (((tileRect.x+tileRect.w) - playerRect.x)/2)+12)
							tempPlayer.offset_y -= player->movmentSpeed/2;
				}
			}

			if(player->direction == 1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 4)
				{
					collide = false;

				if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= (((tileRect.x+tileRect.w) - playerRect.x)/2)+12)
							tempPlayer.offset_y += player->movmentSpeed/2;
				}
			}

			//             _ 
			/*TILE TYPE 5 ' -' */
			if(player->direction == -1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 5)
				{
					collide = false;

					if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= ceil(float(((tileRect.x+tileRect.w) - playerRect.x)/2+12)))
							tempPlayer.offset_y += player->movmentSpeed/2;
				
				}
			}

			if(player->direction == 1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 5)
				{
					collide = false;

					if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <= ceil(float(((tileRect.x+tileRect.w) - playerRect.x)/2+12)))
							tempPlayer.offset_y -= player->movmentSpeed/2;
				
				}
			}

			/*TILE TYPE 6 '-_' */
			if(player->direction == -1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 6)
				{
					collide = false;

					if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <=  ceil(float(((tileRect.x+tileRect.w) - playerRect.x)/2)))
							tempPlayer.offset_y += player->movmentSpeed/2;
				
				}
			}

			if(player->direction == 1)
			{
				if(map.mapTilePosition[i].boundingBoxType == 6)
				{
					collide = false;

					if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
						if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) <=  ceil(float(((tileRect.x+tileRect.w) - playerRect.x)/2)))
							tempPlayer.offset_y -= player->movmentSpeed/2;
				}
			}


		}	

		
	}

	if (!collide)
			*player = tempPlayer;



	collide = false;


	tempPlayer.offset_y -= 3;

	for(int i = 0; i < map.tilesCount; i++)
	{

		tileRect.x = map.mapTilePosition[i].worldPosition.x;
		tileRect.y = map.mapTilePosition[i].worldPosition.y;
		tileRect.w = 24;
		tileRect.h = 24;

		playerRect.x = (tempPlayer.position.x - tempPlayer.offset_x)+10;
		playerRect.y = (tempPlayer.position.y - tempPlayer.offset_y);
		playerRect.w = 22;
		playerRect.h = 70;

		
		if(CollideBoundingBox(playerRect, tileRect))
		{
			collide = true;

			if(map.mapTilePosition[i].boundingBoxType == 2)
			{
				if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
				{
					if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) >= ((tileRect.x+tileRect.w) - playerRect.x))
						collide = false;
				}

			}

			if(map.mapTilePosition[i].boundingBoxType == 1)
			{
				if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
				{
					if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) >= ((playerRect.x+playerRect.w) - tileRect.x))
						collide = false;
				}

			}

			
			if(map.mapTilePosition[i].boundingBoxType == 3)
			{
				if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
				{
					if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) >= ((tileRect.x+tileRect.w) - playerRect.x)/2)
						collide = false;
				}

			}

			if(map.mapTilePosition[i].boundingBoxType == 4)
			{
				if(((playerRect.x+playerRect.w) - tileRect.x) <= 24)
				{
					if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) >= (((tileRect.x+tileRect.w) - playerRect.x)/2)+12)
						collide = false;
				}

			}

			if(map.mapTilePosition[i].boundingBoxType == 5)
			{
				if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
				{
					if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) >= ceil(float(((tileRect.x+tileRect.w) - playerRect.x)/2+12)))
						collide = false;
				}

			}
			if(map.mapTilePosition[i].boundingBoxType == 6)
			{
				if(((tileRect.x+tileRect.w) - playerRect.x) <= 24)
				{
					if((tileRect.y+tileRect.h) - (playerRect.y+playerRect.h) >=  ceil(float(((tileRect.x+tileRect.w) - playerRect.x)/2)))
						collide = false;
				}

			}

		}

	}
	if (!collide)
		*player = tempPlayer;

}

bool Physics::CollideBoundingBox(SDL_Rect box1, SDL_Rect box2)
{
	if(box1.x + box1.w > box2.x && box1.x <box2.x + box2.w)
		if(box1.y + box1.h > box2.y && box1.y < box2.y + box2.h)
			return true;

	return false;


}
