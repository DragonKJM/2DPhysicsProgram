#pragma once

#define GRAVITY 0.981f //these should go in a world values header, but its easier to have them here for now
#define AIRDENSITY 1.225f

#include "MeshLoader.h"

class SceneObject
{
private:
	float timeSinceStart;
	float oldTime;

protected:
	Vector2 mLinearVelocity;
	float mTerminalVelocity;
	float mAngularVelocity;
	float mAngle;
	float mTorque;
	Vector2 mForce;
	float mMass;
	float mDeltaTime;
	float mMomentOfInertia;

public:
	Vector2 mPosition;//temp public, should use getter
	float mHeight;// ^
	float mWidth;// ^
	float mRadius; //here just to fix maths.cpp stuff for now

	SceneObject();
	~SceneObject();


	virtual void Update();
	virtual void Draw() = 0; // = 0 makes it pure virtual, must be overridden
	virtual void CalcForce() = 0;
	virtual void CalcInertia() = 0;
	virtual void CalcTerminalVelocity() = 0;

};

