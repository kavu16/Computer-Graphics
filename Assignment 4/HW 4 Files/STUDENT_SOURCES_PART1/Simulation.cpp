/* SIMPLE MATHS LIBRARY
PREPARED BY GIZEM KAYAR FOR COMPUTER GRAPHICS COURSE/NEW YORK UNIVERSITY
YEAR: 2022
*/

#include "pch.h"
#include "Simulation.h"
#define SIGN(x) (x >= 0 ? 1.0 : -1.0)
#include <stdlib.h>
#include "math3d.h"


void Simulation::initializeParticles()
{
	srand(0);

	float x, y, z;
	for (int i = 0; i < noPt; i++)
	{
		Particle  particle;

		//TO DO: Set particle positions and velocities using srand and world positions
		



		particle.clearForce();

		//TO DO: Compute particle's old position for Verlet integration scheme
		

		particle.setIntegration(Euler);
		particle.setColor(vector3f(0, 0, 255));
		particle.setPosition(vector3f(particle.getPosition().getX(),
			(particle.getPosition().getY() + 0.1, 0), particle.getPosition().getZ()));


		particleList.push_back(particle);

	}
}

void Simulation::simulateEuler(Particle* p)
{
	//TO DO
	
	
	
}

void Simulation::simulateEulerCromer(Particle* p)
{
	//TO DO
	

}

void Simulation::simulateVerlet(Particle* p)
{
	//TO DO
	

}

void Simulation::clearForces()
{
	for (int i = 0; i < noPt; i++)
		particleList[i].clearForce();
}

void Simulation::destroyParticles()
{
	particleList.clear();
}

void Simulation::solveWorldCollision()
{
	vector3f tempVel;
	vector3f tempPos;

	for (int i = 0; i < noPt; i++)
	{
		tempVel = particleList[i].getVelocity();
		tempPos = particleList[i].getPosition();

		if (particleList[i].getPosition().getX() <= -halfWorld.getX() || particleList[i].getPosition().getX() >= halfWorld.getX())
		{
			tempVel.setX(tempVel.getX() * -worldColldConst);
			tempPos.setX(SIGN(tempPos.getX()) * halfWorld.getX());
		}

		if (particleList[i].getPosition().getY() <= -halfWorld.getY() || particleList[i].getPosition().getY() >= halfWorld.getY())
		{
			tempVel.setY(tempVel.getY() * -worldColldConst);
			tempPos.setY(SIGN(tempPos.getY()) * halfWorld.getY());
		}

		if (particleList[i].getPosition().getZ() <= -halfWorld.getZ() || particleList[i].getPosition().getZ() >= halfWorld.getZ())
		{
			tempVel.setZ(tempVel.getZ() * -worldColldConst);
			tempPos.setZ(SIGN(tempPos.getZ()) * halfWorld.getZ());
		}

		particleList[i].setVelocity(tempVel);
		particleList[i].setPosition(tempPos);
	}
}

void Simulation::computeSystemEnergies()
{
	//TO DO
	


}
