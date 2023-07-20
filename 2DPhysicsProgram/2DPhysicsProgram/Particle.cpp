#include "Particle.h"

Particle::Particle(Vector2 pos, float mass)
{
	mPosition = pos;
	mMass = mass;

	CalcTerminalVelocity();
}

Particle::~Particle()
{

}

void Particle::Draw()
{
	glBegin(GL_POINTS);
	{
		glColor4f(0.0f, 0.6f, 1.0f, 1.0f); //defines the colour
		glVertex2f(mPosition.x, mPosition.y);
		glEnd(); // ends draw
	}
}

void Particle::Update()
{
	SceneObject::Update();

	//calculations
	CalcForce();
	Vector2 linearAcceleration = Vector2{ mForce.x / mMass, mForce.y / mMass };
	mLinearVelocity.x += linearAcceleration.x * mDeltaTime;
	mLinearVelocity.y += linearAcceleration.y * mDeltaTime;
	mPosition.x += mLinearVelocity.x * mDeltaTime;
	mPosition.y += mLinearVelocity.y * mDeltaTime;

	mLinearVelocity.x = 1.05f;// manual set wind, anywhere else would be acceleration

	//constraints 
	float randomValue = -1.0f - static_cast<float>(rand()) / (static_cast<float>(RAND_MAX)); // dividing rand by rand max creates a number between 0 and 1,
	if (mPosition.y < randomValue)
		mPosition.y = 1;

	randomValue = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
	if (mPosition.x > randomValue)
		mPosition.x = -1;

	//if (mLinearVelocity.y < -mTerminalVelocity) // should only apply when falling, not with applied force
	//	mLinearVelocity.y = -mTerminalVelocity;
}

void Particle::CalcForce()
{
	mForce = Vector2{ 0, mMass * -GRAVITY }; 
}

void Particle::CalcTerminalVelocity()
{
	mTerminalVelocity = std::sqrt((2 * mMass * GRAVITY) / AIRDENSITY); //basic version of terminal velocity equation, sqrt is bad but easier
}
