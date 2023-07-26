#include "ColliderFactory.h"

Collider* ColliderFactory::createCollider(ColliderType colliderType, float height, float width, float radius)
{
    switch (colliderType)
    {
    case BOX_COLLIDER:
        return new BoxCollider(height, width);
    //case CIRCLE_COLLIDER:
        //if (radius == 0.0f) 
        //{
        //    radius = width / 2.0f;
        //}
        //return new CircleCollider(pos, radius);
    //other collider types:
    default:
        return nullptr;
    }
}