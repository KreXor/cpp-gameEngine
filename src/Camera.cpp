#include "Camera.h"


void Camera::reset()
{
	position.x = 0;
	position.y = 0;
	zoomLevel = 1;
	moveToTargetSpeed = 0;
	moveToTargetTime = 0;
}

void Camera::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;

}

float Camera::getXPosition()
{
	return position.x;
}

float Camera::getYPosition()
{
	return position.y;
}

void Camera::update(float millisecondFTime)
{
	if(moveToTargetTime > 0)
	{
		if(position.x > targetMovePosition.x)
		{

			position.x -= millisecondFTime*moveToTargetSpeed;
			moveToTargetTime -= millisecondFTime;
		}
		else if(position.x < targetMovePosition.x)
		{
			position.x += millisecondFTime*moveToTargetSpeed;
			moveToTargetTime -= millisecondFTime;
		}
	}
}

void Camera::moveCameraTo(float x, float y, int time)
{


	targetMovePosition.x = x;
	targetMovePosition.y = y;
	moveToTargetTime = time;
	moveToTargetSpeed = 0;

	int distanceToTravel = 0;
	if(targetMovePosition.x > position.x)
		distanceToTravel = targetMovePosition.x - position.x;
	else
		distanceToTravel = position.x - targetMovePosition.x;

	moveToTargetSpeed = (float)distanceToTravel/(float)moveToTargetTime;



}

void Camera::addCameraShake(float strength, int time)
{

}

void Camera::setZoomLevel(float level)
{
	this->zoomLevel = level;
}

float Camera::getZoomLevel()
{
	return this->zoomLevel;
}

void Camera::zoomIn()
{
	this->zoomLevel +=0.5;
}
void Camera::zoomOut()
{
	this->zoomLevel -=0.5;
}
