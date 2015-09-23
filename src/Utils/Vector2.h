#ifndef VECTOR2_H
#define VECTOR2_H

#include "math.h"
class Vector2
{
public:
    Vector2(void);
    Vector2(float X, float Y);
    ~Vector2(void);
    float Length();
    Vector2 Normalize();
	float Direction();
    float X,Y;
};

#endif
