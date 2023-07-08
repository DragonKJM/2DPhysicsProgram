#include "Maths.h"
#include "SceneObject.h" //contains Vector3 and SceneObject

namespace Maths
{
	Vector2 Normalise(const Vector2& v) //https://stackoverflow.com/questions/17327906/what-glmnormalize-does
	{
		float length_of_v = sqrt((v.x * v.x) + (v.y * v.y));
		return Vector2(v.x / length_of_v, v.y / length_of_v);
	}

	float degreesToRadians(float degrees)
	{
		const float pi = 3.14159265358979323846f;
		return degrees * (pi / 180.0f);
	}

	//collisions
	bool Sphere2Collision(const SceneObject* sphere1, const SceneObject* sphere2) //change to sphereObj?
	{

		float dx = sphere1->mPosition.x - sphere2->mPosition.x; //can put this all into one float, but this helps to visualise it better
		float dy = sphere1->mPosition.y - sphere2->mPosition.y;
		float distanceSquared = dx * dx + dy * dy;
		float sumOfRadiiSquared = pow(sphere1->mRadius + sphere2->mRadius, 2);
		if (distanceSquared <= sumOfRadiiSquared)
		{
			return true;
		}

		return false;
	}

	bool SphereBoxCollision(const SceneObject* sphere, const SceneObject* box)
	{

		//I'm using bounding box collision for this: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
		// 
		//below is the same as "x = max(objects[0]->_position.x - cuboid_width / 2, min(objects[i]->position.x, objects[0]->_position.x + cuboid_width/2));" 
		float sphereSideX = sphere->mPosition.x;
		if (sphereSideX < box->mPosition.x - box->mWidth / 2) //if sphere is left of cube's left face
		{
			sphereSideX = box->mPosition.x - box->mWidth / 2; //clamp x to cube's left face
		}
		else if (sphereSideX > box->mPosition.x + box->mWidth / 2) //if sphere is to right of right face
		{
			sphereSideX = box->mPosition.x + box->mWidth / 2;//clamp x to right face
		}

		float sphereSideY = sphere->mPosition.y;
		if (sphereSideY < box->mPosition.y - box->mHeight / 2)
		{
			sphereSideY = box->mPosition.y - box->mHeight / 2;
		}
		else if (sphereSideY > box->mPosition.y + box->mHeight / 2)
		{
			sphereSideY = box->mPosition.y + box->mHeight / 2;
		}

		//compare each relative face from above calculations to sphere's location
		float distanceSquared = (sphereSideX - sphere->mPosition.x) * (sphereSideX - sphere->mPosition.x) + (sphereSideY - sphere->mPosition.y) * (sphereSideY - sphere->mPosition.y);

		// check if the distance is less than the sum of the radii of the sphere
		float radiusSquared = pow(sphere->mRadius, 2);
		if (distanceSquared < radiusSquared) //rather than comparing two sums, we just compare if distance to centre of cuboid is smaller than the sphere - we already finished w cuboid size
		{
			return true;
		}

		return false;
	}
}