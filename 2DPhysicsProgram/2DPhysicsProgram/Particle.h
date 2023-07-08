#pragma once

#include "SceneObject.h"

class Particle : public SceneObject
{
	Vector2 mOldPosition;

public:
	Particle(Vector2 pos, float mass);
	~Particle();

	void Draw() override;
	void Update() override;
	Vector2 CalcForce() override;
};

