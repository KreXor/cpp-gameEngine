#ifndef RAYCAST_H
#define RAYCAST_H

#include <math.h>
#include <vector>
#include "../Map/Map.h"

class Raycast
{

private:


public:
    struct Position{
		float x;
		float y;
	};

	vector<Position> bresenhamLine(int x0, int y0, int x1, int y1);
	bool raycast_insight(int x0, int y0, int x1, int y1, Map map);


};

#endif
