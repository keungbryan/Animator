#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>
#include "vec.h"
//#include "force.h"
#include "modelerdraw.h"

class Particle {
public:
	Particle(Vec3<float> p, float m) : pos(p), mass(m), gravity(Vec3<float>(0, -5, 0)) {}

	void setPos(Vec3<float> p) {
		pos = p;
	}

	void setVelocity(Vec3<float> v) {
		velocity = v;
	}

	Vec3<float> getPos() const {
		return pos;
	}

	Vec3<float> getVelocity() const {
		return velocity;
	}

	//void addForce(Force* f);
	void move(float deltaT);
	void draw();

private:
	float mass;
	Vec3<float> pos;
	Vec3<float> velocity;
	Vec3<float> gravity;
	//vector<Force*> forces;
};

#endif