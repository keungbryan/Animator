#pragma warning(disable : 4786)

#include "particleSystem.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <ctime>


/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() 
{
	// TODO
	srand(time(0));

}





/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
	particles.clear();

}


/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
    
	// TODO

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	bake_end_time = -1;
	simulate = true;
	dirty = true;
	clearBaked();
	bake_start_time = t;
}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{

	// TODO

	bake_fps = t - curr_time;
	curr_time = t;
	if (simulate) {
//		if (!isBakedAt(t)) {
			/*
			vector<Particle>::iterator iter;
			for (iter = particles.begin(); iter != particles.end(); iter++) {
				iter->move(bake_fps);
			}
			*/
			for (int i = 0; i < particles.size(); i++)
				particles[i].move(bake_fps);

			bakeParticles(t);
//		}
//		else {
//			particles = bakeData[t];
//		}
	}

}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{

	// TODO
	if (simulate) {
		vector<Particle>::iterator iter;
		for (iter = bakeData[t].begin(); iter != bakeData[t].end(); iter++) {
			iter->draw();
		}
	}
	else {
		if (isBakedAt(t)) {
			vector<Particle>::iterator iter;
			for (iter = bakeData[t].begin(); iter != bakeData[t].end(); iter++) {
				iter->draw();
			}
		}
	}

}





/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{

	// TODO
	bakeData.insert(pair<float, vector<Particle>>(t, particles));

}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{

	// TODO
	bakeData.clear();

}

void ParticleSystem::AddParticleStartingAt(Vec3<float> pos, int num, double xRotate, double yRotate, double zRotate)
{
	if (simulate) {
//		if (!isBakedAt(curr_time + bake_fps)) {
			for (int i = 0; i < num; i++) {
				Particle p(Vec3<float>(pos[0], pos[1], pos[2]), 1);

				/*
				float mag = rand() % 10 / 10.0 + 0.2;
				float theta = rand() % 360 / 57.3;

				float xVelocity = rand() % 10 / 10.0 + 2;
				float yVelocity = cos(theta) * mag;
				float zVelocity = sin(theta) * mag;
				
				p.setVelocity(Vec3<float>(xVelocity, yVelocity, zVelocity));
				*/

				float xvel = rand() % 3 - 1.5;
				float yvel = (rand() % 3 + 7);// *cos(xRotate*3.1415926535 / 180.0);
				float zvel = (rand() % 3 - 1.5);// *sin(xRotate*3.1415926535 / 180.0);

				xRotate *= 3.1415926535 / 180.0;
				yRotate *= 3.1415926535 / 180.0;
				zRotate *= 3.1415926535 / 180.0;

				Mat4f vecMatX(
					1, 0, 0, 0,
					0, cos(xRotate), -sin(xRotate), 0,
					0, sin(xRotate), cos(xRotate), 0,
					0, 0, 0, 1
				);
				Mat4f vecMatY(
					cos(yRotate), 0, sin(yRotate), 0,
					0, 1, 0, 0,
					-sin(yRotate), 0, cos(yRotate), 0,
					0, 0, 0, 1
				);
				Mat4f vecMatZ(
					cos(zRotate), -sin(zRotate), 0, 0,
					sin(zRotate), cos(zRotate), 0, 0, 
					0, 0, 1, 0,
					0, 0, 0, 1
				);

				Vec4f velocity(xvel, yvel, zvel, 1);
				velocity = vecMatX*vecMatZ * velocity;
				

				p.setVelocity(Vec3<float>(velocity[0], velocity[1], velocity[2]));

				/*
				vector<Force*>::iterator iter;
				for (iter = forces.begin(); iter != forces.end(); iter++) {
					p.addForce(*iter);
				}
				*/

				particles.push_back(p);
			}
//		}
	}
}

bool ParticleSystem::isBakedAt(float t) {
	map<float, vector<Particle>>::iterator it = bakeData.find(t);
	return (it != bakeData.end());
}





