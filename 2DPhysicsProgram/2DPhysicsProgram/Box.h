#pragma once

#include "SceneObject.h"

class Box : public SceneObject
{
public:
	Box(Vector2 pos, float mass, float height, float width, ColliderType colliderType);
	~Box();

	void Draw() override;
	void Update() override;
	void CalcForce() override;
	void CalcInertia() override;
	void CalcTerminalVelocity() override;
};

