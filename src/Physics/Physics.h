#ifndef PHYSICS_H
#define PHYSICS_H

#include "../Player.h"
#include "../Map/Map.h"

using namespace std;

class Physics {

public:
	void ApplyPhysics(Drawable player, Map map);
	void ApplyPhysicsOnPlayer(Player* player, Map map);
    bool CheckPlayerCollision(Player player, Map map);

private:

	bool CollideBoundingBox(SDL_Rect box1, SDL_Rect box2);
};

#endif
