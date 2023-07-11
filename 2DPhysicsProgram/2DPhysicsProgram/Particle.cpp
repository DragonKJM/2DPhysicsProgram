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
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //defines the colour
		glVertex2f(mPosition.x, mPosition.y); // first point of polygon
		glEnd(); // ends draw
	}
}

void Particle::Update()
{
	SceneObject::Update();

	CalcForce();
	Vector2 linearAcceleration = Vector2{ mForce.x / mMass, mForce.y / mMass };
	mLinearVelocity.x += linearAcceleration.x * mDeltaTime;
	mLinearVelocity.y += linearAcceleration.y * mDeltaTime;
	mPosition.x += mLinearVelocity.x * mDeltaTime;
	mPosition.y += mLinearVelocity.y * mDeltaTime;
}

void Particle::CalcForce()
{
	mForce = Vector2{ 0, mMass * -0.981f }; //Gravity
}
