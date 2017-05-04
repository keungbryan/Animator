#ifndef FORCE_H_
#define FORCE_H_

#include "vec.h"

class Force {
public:
	Force(Vec3<float> g) : gravity(g) {}
	virtual void applyTo(Vec3<float>& speed, float deltaT);

	Vec3<float> gravity;	
};

#endif 