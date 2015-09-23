#include "Raycast.h"

vector<Raycast::Position> Raycast::bresenhamLine(int x0, int y0, int x1, int y1)
{

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

//Returns true if two target is insight of eachother
bool Raycast::raycast_insight(int x0, int y0, int x1, int y1, Map map)
{
    vector<Raycast::Position> ray;

    ray = bresenhamLine(y0, x0, y1, x1);


    for(int j = 0; j < ray.size(); j++)
    {
        int x = ray[j].x;
        int y = ray[j].y;

        if(map.isWall(map.mapTilePosition[y/map.getTileSize()][x/map.getTileSize()]))
        {
            return false;
            break;
        }
    }

    return true;
}
