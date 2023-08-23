#pragma once

//#include "Structures.h" //using this method to get the full information of Vector2 allows maths.h to be included in hellogl.cpp

class Vector2; //using this method means the full information of Vector2 isn't gotten yet, so maths.h needs to be included in a header file to allow it to compile together before an attempt to use it?
class SceneObject;

namespace Maths
{
	//general maths
	Vector2 Normalise(const Vector2& v);
	float Dot(const Vector2& v1, const Vector2& v2);

	//collisions (old)
	bool Sphere2Collision(const SceneObject* sphere1, const SceneObject* sphere2); //const in parameters means it won't modify them, const after means it won't modify any member vars
	bool SphereBoxCollision(const SceneObject* sphere, const SceneObject* box);
}
