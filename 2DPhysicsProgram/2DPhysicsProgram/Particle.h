#pragma once

#include "SceneObject.h"

class Particle : public SceneObject
{
public:
	Particle(Vector2 pos, float mass);
	~Particle();

	void Draw() override;
	void Update() override;
	void CalcForce() override;
	void CalcInertia() override {};
	void CalcTerminalVelocity() override;
};

