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

		float dx = sphere1->_position.x - sphere2->_position.x; //can put this all into one float, but this helps to visualise it better
		float dy = sphere1->_position.y - sphere2->_position.y;
		float distanceSquared = dx * dx + dy * dy;
		float sumOfRadiiSquared = pow(sphere1->_radius + sphere2->_radius, 2);
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
		float sphereSideX = sphere->_position.x;
		if (sphereSideX < box->_position.x - box->width / 2) //if sphere is left of cube's left face
		{
			sphereSideX = box->_position.x - box->width / 2; //clamp x to cube's left face
		}
		else if (sphereSideX > box->_position.x + box->width / 2) //if sphere is to right of right face
		{
			sphereSideX = box->_position.x + box->width / 2;//clamp x to right face
		}

		float sphereSideY = sphere->_position.y;
		if (sphereSideY < box->_position.y - box->height / 2)
		{
			sphereSideY = box->_position.y - box->height / 2;
		}
		else if (sphereSideY > box->_position.y + box->height / 2)
		{
			sphereSideY = box->_position.y + box->height / 2;
		}

		//compare each relative face from above calculations to sphere's location
		float distanceSquared = (sphereSideX - sphere->_position.x) * (sphereSideX - sphere->_position.x) + (sphereSideY - sphere->_position.y) * (sphereSideY - sphere->_position.y);

		// check if the distance is less than the sum of the radii of the sphere
		float radiusSquared = pow(sphere->_radius, 2);
		if (distanceSquared < radiusSquared) //rather than comparing two sums, we just compare if distance to centre of cuboid is smaller than the sphere - we already finished w cuboid size
		{
			return true;
		}

		return false;
	}
}