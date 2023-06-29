#pragma once

#include "MeshLoader.h"

class SceneObject
{
protected:
	Mesh* _mesh;

public:
	SceneObject(Mesh* mesh);
	~SceneObject();
	Vector2 _position;
	float _radius; //only for spheres, but update in HelloPhysics uses the object class base
	float height;
	float width;
	float _rotationSpeed;

	virtual void Update() {}
	virtual void Draw() {}
	virtual void DefineMaterial() {}

};

