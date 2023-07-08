#include "SceneObject.h"

SceneObject::SceneObject()
{
	timeSinceStart = 0;
	oldTime = 0;
	mDeltaTime = 0;

	mPosition = { 0, 0 };
	mVelocity = { 0, 0 };

	mHeight = 0;
	mWidth = 0;
	mMass = 0;
	mRadius = 0;

}

SceneObject::~SceneObject()
{
}

void SceneObject::Update()
{
	timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	mDeltaTime = (timeSinceStart - oldTime) / 1000.0f;
	oldTime = timeSinceStart; //Think this should go at end of update but this is easier
}
