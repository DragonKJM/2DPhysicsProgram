#include "Box.h"

Box::Box(Vector2 pos, float mass, float height, float width)
{
	mPosition = pos;
	mMass = mass;
	mHeight = height;
	mWidth = width;

	CalcInertia();
	//CalcTerminalVelocity(); // Calculate only in a pressurised simulation

	std::cout << mTerminalVelocity << std::endl;
}

Box::~Box()
{
}

void Box::Draw()
{
	glPushMatrix();  // Save the current matrix state
	glTranslatef(mPosition.x, mPosition.y, 0.0f);  // Translate to the position of the polygon
	glRotatef(mAngle, 0.0f, 0.0f, 1.0f);  // Apply the rotation around the z-axis
	glTranslatef(-mWidth, -mHeight, 0.0f);  // Translate back to the origin of the polygon

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 2 * mHeight); //multiply by 2 cause we want the position to be centered, however this messes up scale, size is doubled 
	glVertex2f(2 * mWidth, 2 * mHeight);
	glVertex2f(2 * mWidth, 0.0f);
	glEnd();

	glPopMatrix();  // Restore the previous matrix state
}

void Box::Update()
{
	SceneObject::Update();

	//calculations
	CalcForce();
	Vector2 linearAcceleration = Vector2{ mForce.x / mMass, mForce.y / mMass };
	mLinearVelocity.x += linearAcceleration.x * mDeltaTime;
	mLinearVelocity.y += linearAcceleration.y * mDeltaTime;
	mPosition.x += mLinearVelocity.x * mDeltaTime;
	mPosition.y += mLinearVelocity.y * mDeltaTime;

	float angularAcceleration = mTorque / mMomentOfInertia;
	mAngularVelocity += angularAcceleration * mDeltaTime;
	mAngle += mAngularVelocity * mDeltaTime;

	std::cout << mPosition.y << "///" << mAngle << std::endl;

	//constraints
	if (mPosition.y < -1.5f)
		mPosition.y = 1.5f;

	if (mLinearVelocity.y < -mTerminalVelocity)
		mLinearVelocity.y = -mTerminalVelocity;
}

void Box::CalcForce()
{

	mForce = Vector2{ 0 , mMass * -GRAVITY };
	// r is the 'arm vector' that goes from the center of mass to the point of force application
	Vector2 r = Vector2{ mWidth / 2, mHeight / 2 };
	mTorque = r.x * mForce.y - r.y * mForce.x;
}

void Box::CalcInertia()
{
	mMomentOfInertia = mMass * (mWidth * mWidth + mHeight * mHeight) / 12; // equation only applies to boxes
}

void Box::CalcTerminalVelocity()
{
	float areaOfSide = mWidth; // should be whichever side is hitting the wind, but that's too much work
	mTerminalVelocity = std::sqrt((2 * mMass * GRAVITY) / (AIRDENSITY * areaOfSide));
}
