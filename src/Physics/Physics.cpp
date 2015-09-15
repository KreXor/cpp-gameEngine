#include "Physics.h"
#include <math.h>

void Physics::ApplyPhysicsOnPlayer(Player* player, Map map)
{
	this->CheckPlayerCollision(player, map);


}

void Physics::CheckPlayerCollision(Player* player, Map map)
{


}

bool Physics::CollideBoundingBox(SDL_Rect box1, SDL_Rect box2)
{
	if(box1.x + box1.w > box2.x && box1.x <box2.x + box2.w)
		if(box1.y + box1.h > box2.y && box1.y < box2.y + box2.h)
			return true;

	return false;


}
