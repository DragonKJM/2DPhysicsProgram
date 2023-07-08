#include "Particle.h"

Particle::Particle(Vector2 pos, float mass)
{
	mPosition = pos;
	mMass = mass;
}

Particle::~Particle()
{

}

void Particle::Draw()
{
	glBegin(GL_POINTS); //Starts to draw a polygon, change "polygon" to "points" for points instead
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f); //defines the colour
		glVertex2f(mPosition.x, mPosition.y); // first point of polygon
		glEnd(); // ends draw
	}
}

void Particle::Update()
{
	SceneObject::Update();

	Vector2 force = CalcForce();
	Vector2 acceleration = Vector2{ force.x / mMass, force.y / mMass };
	mVelocity.x += acceleration.x * mDeltaTime;
	mVelocity.y += acceleration.y * mDeltaTime;
	mPosition.x += mVelocity.x * mDeltaTime;
	mPosition.y += mVelocity.y * mDeltaTime;

	//if (mPosition.y < -1) // cool lines
	//	mPosition.y = 1;
}

Vector2 Particle::CalcForce()
{
	return Vector2{ 0, mMass * -0.981f }; //Gravity
}
