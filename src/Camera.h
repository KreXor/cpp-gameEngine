#ifndef CAMERA_H
#define CAMERA_H

#include "SDL2/SDL.h"

class Camera
{

private:

	struct Position{
		float x;
		float y;
	};

	Position position;
	Position targetMovePosition;
	float moveToTargetSpeed;
	float moveToTargetTime;

	float zoomLevel;
	int screen_width;
	int screen_height;

public:
    void init(int w, int h);
	void update(float millisecondFTime);
	void reset();
	void setPosition(float x, float y);
	float getXPosition();
	float getYPosition();
	void setZoomLevel(float level);
	float getZoomLevel();
	void zoomIn();
	void zoomOut();
	void setFocus(float x, float y);

	void addCameraShake(float strength, int time);
	void moveCameraTo(float x, float y, int time);

};

#endif
