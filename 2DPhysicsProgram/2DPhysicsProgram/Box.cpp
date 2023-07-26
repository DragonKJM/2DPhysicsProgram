#include "Box.h"
#include "ColliderFactory.h"

Box::Box(Vector2 pos, float mass, float height, float width, ColliderType colliderType)
{
	mPosition = pos;
	mMass = mass;
	mHeight = height;
	mWidth = width;

	CalcInertia();
	//CalcTerminalVelocity(); // Calculate only in a pressurised simulation

	mCollider = ColliderFactory::createCollider(colliderType, mHeight, mWidth);
}

Box::~Box()
{
	delete mCollider;
}

void Box::Draw()
{
	glPushMatrix();  // Save the current matrix state
	glTranslatef(mPosition.x, mPosition.y, 0.0f);  // Translate to the position of the polygon
	glRotatef(mRotation, 0.0f, 0.0f, 1.0f);  // Apply the rotation around the z-axis
	glTranslatef(-mWidth / 2.0f, -mHeight / 2.0f, 0.0f); // translate to centre origin of polygon

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, mHeight);
	glVertex2f(mWidth, mHeight);
	glVertex2f(mWidth, 0.0f);
	glEnd();

	glPopMatrix();  // Restore the previous matrix state
}

void Box::Update()
{
	SceneObject::Update();

	mCollider->setPos(mPosition);
	mCollider->setRotation(mRotation); // these probably shouldn't be here, move to appropriate place
	mCollider->CalcCollider();

	//calculations
	CalcForce();
	Vector2 linearAcceleration = Vector2{ mForce.x / mMass, mForce.y / mMass };
	mLinearVelocity.x += linearAcceleration.x * mDeltaTime;
	mLinearVelocity.y += linearAcceleration.y * mDeltaTime;
	mPosition.x += mLinearVelocity.x * mDeltaTime;
	mPosition.y += mLinearVelocity.y * mDeltaTime;

	float angularAcceleration = mTorque / mMomentOfInertia;
	mAngularVelocity += angularAcceleration * mDeltaTime;
	mRotation += mAngularVelocity * mDeltaTime;

	std::cout << mPosition.y << "///" << mRotation << std::endl;

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
