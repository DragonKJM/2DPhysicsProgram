#pragma once

#include "Collider.h"

class ColliderFactory
{
public:
    static Collider* createCollider(ColliderType colliderType, float height = 0.0f, float width = 0.0f, float radius = 0.0f);
};

