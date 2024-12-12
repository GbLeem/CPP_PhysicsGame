//#pragma once
//
//#include "Game2D.h"
//
//#include <vector>
//#include <GL/glut.h>
//
//#include <eigen3/Eigen/Dense>
//using namespace Eigen;
//
//namespace gb
//{
//	const static float H = 0.05f;
//	const static float EPS = 0.1f;
//
//	const static int WINDOW_WIDTH = 1024;
//	const static int WINDOW_HEIGHT = 768;
//
//	const static float VIEW_HEIGHT = 4.f;//50.f;
//	const static float VIEW_WIDTH = 4.f;//WINDOW_HEIGHT * VIEW_HEIGHT / WINDOW_WIDTH;
//
//	//const static float spacing = 2.f;			// particle spacing/radius
//	//const static float r = spacing * 1.25f;		// kernel radius	
//	//const static float k = spacing / 1000.f;	// far pressure weight
//
//	//const static float rest_density = 3.f;		// rest density
//	const static float SIGMA = 0.2f;			// visc parameters
//	const static float BETA = 0.2f;
//	const static Vector2d G(0.f, -0.0005f); // external (gravitational) forces
//	const static float SPRING_CONST = 0.005f / 8.; // boundary spring constant
//
//
//	//NEW
//	const static float R = 0.01f;
//	const static float K = R / 1000.f;
//	const static float REST_DENSITY = 0.03f;
//
//	struct Neighbor
//	{
//		int i, j;
//		float q, q2;
//	};
//
//	class Particle
//	{
//	public:
//		Particle(float _x, float _y)
//			:pos(Vector2d(_x, _y))
//			,pos_old(Vector2d(_x, _y))
//			,vel(Vector2d(0.f, 0.f))
//			,force(Vector2d(0.f, 0.f))
//			,rho(0.f)
//			,rho_near(0.f)
//			,press(0.f)
//			,press_near(0.f)			
//		{}
//
//		vec2 GetParticlePos()
//		{			
//			return vec2(pos(0), pos(1));
//		}
//
//	public:
//		void DrawParticle()
//		{			
//			BeginTransformation();
//			{
//				Translate(GetParticlePos());
//				DrawFilledCircle(Colors::blue, R);
//			}
//			EndTransformation();
//		}
//
//	public:
//		Vector2d pos;
//		Vector2d pos_old;
//		Vector2d vel;
//		Vector2d force;
//		
//		float mass;
//		float rho;
//		float rho_near;
//		float press;
//		float press_near;	
//		std::vector<Neighbor> neighbors;
//	};
//
//
//	class WaterBall
//	{
//	public:		
//
//		WaterBall()
//		{
//			Init();
//		}
//		void Init()
//		{						
//			for (float y = 0.1f; y < 0.3f; y += 2 * R)
//			{
//				for (float x = 0.1f; x < 0.3f; x += 2 * R)
//				{
//					Particle* particle = new Particle(x, y);
//					particles.push_back(particle);
//				}
//			}
//		}
//
//		void Integrate()
//		{
//			for (auto& p : particles)
//			{
//				// for simplicity, dt=1 assumed in Verlet integration
//				p->pos_old = p->pos;
//				p->pos += p->vel;
//				p->pos += p->force;
//				p->force = G; // external forces
//				p->vel = p->pos - p->pos_old;
//
//				// enforce boundary condition
//				if (p->pos(0) - EPS < 0.0f)
//					p->force(0) -= (p->pos(0) - EPS) * SPRING_CONST;
//				if (p->pos(0) + EPS > VIEW_WIDTH)
//					p->force(0) -= (p->pos(0) + EPS - VIEW_WIDTH) * SPRING_CONST;
//				if (p->pos(1) - EPS < 0.0f)
//					p->force(1) -= (p->pos(1) - EPS) * SPRING_CONST;
//				if (p->pos(1) + EPS > VIEW_HEIGHT)
//					p->force(1) -= (p->pos(1) + EPS - VIEW_HEIGHT) * SPRING_CONST;
//			}
//		}
//
//		void CalculateDensity()
//		{
//			for (int i = 0; i < particles.size(); i++)
//			{
//				Particle* pi = particles[i];
//				pi->rho = pi->rho_near = 0;
//
//				// We will sum up the 'near' and 'far' densities.
//				float d = 0.f, dn = 0.f;
//
//				// Now look at every other particle
//				pi->neighbors.clear();
//				for (int j = i + 1; j < particles.size(); j++)
//				{
//					Particle* pj = particles[j];
//
//					Vector2d rij = pj->pos - pi->pos;
//					float rij_len2 = rij.squaredNorm();
//
//					if (rij_len2 < R*R)
//					{
//						float rij_len = sqrt(rij_len2);
//
//						// weighted distance
//						float q = 1.f - rij_len / R;
//						float q2 = q * q;
//						float q3 = q2 * q;
//
//						d += q2;
//						dn += q3;
//
//						pj->rho += q2;
//						pj->rho_near += q3;
//
//						// add to neighbor list for faster access later
//						Neighbor n;
//						n.j = j;
//						n.q = q;
//						n.q2 = q2;
//						pi->neighbors.push_back(n);
//					}
//				}
//
//				pi->rho += d;
//				pi->rho_near += dn;
//			}
//		}
//
//		void CalculateForces()
//		{
//			// pressure
//			for (auto& pi : particles)
//			{
//				pi->press = K * (pi->rho - REST_DENSITY);
//				pi->press_near = K*10.f * pi->rho_near;
//
//				Vector2d dX = Vector2d(0, 0);
//				for (auto& n : pi->neighbors)
//				{
//					Particle* pj = particles[n.j];
//
//					Vector2d rij = pj->pos - pi->pos;
//					float dm = (pi->press + pi->press) * n.q + (pi->press_near + pj->press_near) * n.q2;
//
//					Vector2d D = rij.normalized() * dm;
//					dX += D;
//					pj->force += D;
//
//
//				}
//				pi->force -= dX;
//			}
//
//			// viscosity
//			for (auto& pi : particles)
//			{
//				for (auto& n : pi->neighbors)
//				{
//					Particle* pj = particles[n.j];
//
//					Vector2d rij = pj->pos - pi->pos;
//					float l = (rij).norm();
//					float q = l / R;
//
//					Vector2d rijn = (rij / l);
//					// get the projection of the velocities onto the vector between them
//					float u = (pi->vel - pj->vel).dot(rijn);
//					if (u > 0.f)
//					{
//						// calculate the viscosity impulse between the two particles
//						// based on the quadratic function of projected length
//						Vector2d I = (1.f - q) * (SIGMA * u + BETA * u * u) * rijn;
//
//						// apply the impulses on the two particles
//						pi->vel -= I * 0.5f;
//						pj->vel += I * 0.5f;
//					}
//				}
//			}
//		}
//
//		void Update(const float& dt)
//		{
//			Integrate();
//			CalculateDensity();
//			CalculateForces();
//
//			//??
//			//glutPostRedisplay();
//		}
//
//		void Draw()
//		{
//			for (const auto & p : particles)
//			{
//				p->DrawParticle();
//			}
//		}
//	private:
//		std::vector<Particle*> particles;
//	};
//}