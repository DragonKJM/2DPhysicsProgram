#pragma once

#include "MeshLoader.h"

class SceneObject
{
private:
	float timeSinceStart;
	float oldTime;

protected:
	Vector2 mVelocity;
	float mMass;
	float mDeltaTime;

public:
	Vector2 mPosition;//temp public, should use getter
	float mHeight;// ^
	float mWidth;// ^
	float mRadius; //here just to fix maths.cpp stuff for now

	SceneObject();
	~SceneObject();


	virtual void Update();
	virtual void Draw() = 0; // = 0 makes it pure virtual, must be overridden
	virtual Vector2 CalcForce() = 0;

};

