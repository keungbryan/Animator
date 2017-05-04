#include "force.h"

void Force::applyTo(Vec3<float>& speed, float deltaT) {
	speed += gravity * deltaT;
}