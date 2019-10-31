#pragma once
#include "Body.h"

class Collider
{
private:
	



public:
	Collider();
	~Collider();
	static bool CheckCollision(const Body& body1, const Body& body2);
	static void handleCollision(Body& body1, Body& body2);
};

