#include "Collider.h"
#include "VMath.h"


Collider::Collider()
{
}
bool Collider::CheckCollision(const Body& body1, const Body& body2){
	//VMath::distance(body1.pos, body2.pos)

	float distance;
	distance = VMath::distance(body1.pos, body2.pos);
	
	if (distance <= body1.radius + body2.radius) {
		return true;
	}
	return false;
}

void Collider::handleCollision(Body& body1, Body& body2) {

		float res = 1.0f;

		Vec3 Normal = VMath::normalize(body2.pos - body1.pos);

		float InVel1 = VMath::dot(body1.vel, Normal);
		float inVel2 = VMath::dot(body2.vel, Normal);

		float finalVel1 = (((body1.mass - res * body2.mass) * InVel1) + ((1.0f + res) * body2.mass * inVel2)) / (body1.mass + body2.mass);
		float finalVel2 = (((body2.mass - res * body1.mass) * inVel2) + ((1.0f + res) * body1.mass * InVel1)) / (body1.mass + body2.mass);

		body1.vel += ((finalVel1 - InVel1) * Normal);
		body2.vel += ((finalVel2 - inVel2) * Normal);


}

Collider::~Collider()
{
}
