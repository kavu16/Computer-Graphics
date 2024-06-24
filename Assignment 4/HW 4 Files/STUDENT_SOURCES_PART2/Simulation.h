/* SIMPLE MATHS LIBRARY
PREPARED BY GIZEM KAYAR FOR COMPUTER GRAPHICS COURSE/NEW YORK UNIVERSITY
YEAR: 2022
*/

#pragma once
#include "particle.h"

using namespace std;



class Simulation
{
public:
	float timestep;
	CubeMesh mesh;
	float commonMass;
	float kinEn;
	float potEn;
	float sprEn;
	IntegrationScheme is;

	float spring_constant;
	float damping_constant;

	float worldColldConst;
	vector3f world;
	vector3f halfWorld;

	Simulation()
	{
		commonMass = 1.0f;
		timestep = 0.0005f;

		world.setUp(20, 20, 20);
		halfWorld = world * 0.5f;
		initializeMesh();

		worldColldConst = 0.5f;

        //TO DO - Try different values and integration schemes
		is = EulerCromer;

		spring_constant = 1000;
		damping_constant = 10;
	}

	void initializeMesh();
	virtual void simulateEuler(Particle* p);
	virtual void simulateEulerCromer(Particle* p);
	virtual void simulateVerlet(Particle* p);

	virtual void simulate()
	{
		clearForces();
		applyForces();


		solveWorldCollision();

		for (int j = 0; j < mesh.particles.size(); j++)
		{
			switch (is)
			{
			case Euler:
				simulateEuler(&mesh.particles[j]);
				break;
			case EulerCromer:
				simulateEulerCromer(&mesh.particles[j]);
				break;
			case Verlet:
				simulateVerlet(&mesh.particles[j]);
				break;

			}
		}

		computeSystemEnergies();

	}

	void clearForces();
	virtual void applyForces() {};
	void destroyParticles();
	void solveWorldCollision();
	void computeSystemEnergies();

};

//Spring Mesh movement
class SimSpring : public Simulation
{
public:

	SimSpring() : Simulation()
	{
	}

	virtual void applyForces()
	{

        //TO DO - Apply gravity
        for (int i = 0; i < mesh.particles.size(); i++)
		{

		}

        //TO DO - Apply spring forces
		for (int i = 0; i < mesh.springs.size(); i++)
		{
			Particle& p1 = mesh.particles[mesh.springs[i].p1];
			Particle& p2 = mesh.particles[mesh.springs[i].p2];

                        //Add spring Force

                        //Add damping Force

		}
	}
};
