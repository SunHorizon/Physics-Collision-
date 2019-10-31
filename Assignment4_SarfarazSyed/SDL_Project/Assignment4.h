#ifndef Assignment4_H
#define Assignment4_H
#include <SDL_image.h>
#include "MMath.h"
#include "Scene.h"
#include <cmath>
#include <SDL.h>
#include "Collider.h"

using namespace MATH;
#define NUM_BODIES 8
class Assignment4 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	class Body* bodies[NUM_BODIES];
	Vec3 direction;
	Vec3 direction2;
	Vec3 gForce;
	float dis;
	float dis2;
	float fg1;
	float fg2;
	float elapsedTime;
	unsigned long frameCount;
	bool keyCheck;
	bool checkC;
public:
	Assignment4(SDL_Window* sdlWindow);
	~Assignment4();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void KeyPress();
	bool closeWindow;
	bool GetCloseWindow();
};

#endif

