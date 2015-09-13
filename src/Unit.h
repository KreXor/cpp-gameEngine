#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string.h>
#include "Drawable.h"
#include "ScriptReader.h"


class Unit : public Drawable
{
public:
	float movmentSpeed;
	bool inAir;
	float currentFallingSpeed;

protected:
	int id;
	int health;
	int animationFrame;


	string type;

};

#endif