#include "Vector2.h"

Vector2::Vector2(void)
{
}

Vector2::Vector2(float X, float Y){
    this->X = X;
    this->Y = Y;
}

// Returns the length of the vector
float Vector2::Length(){
    return sqrt(X * X + Y * Y);
}

// Normalizes the vector
Vector2 Vector2::Normalize(){
    Vector2 vector;
    float length = this->Length();

    if(length != 0){
        vector.X = X/length;
        vector.Y = Y/length;
    }

    return vector;
}

Vector2::~Vector2(void)
{
}

float Vector2::Direction()
{
	if(X >= 0 && Y >= 0)
		return atan(Y/X);

	if(X < 0 && Y >= 0)
		return 90+(atan(Y/X));

	if(X < 0 && Y < 0)
		return 180+(atan(Y/X));

	if(X >= 0 && Y < 0)
		return 270+(atan(Y/X));

}
