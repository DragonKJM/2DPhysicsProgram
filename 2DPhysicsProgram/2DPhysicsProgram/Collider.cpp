#include "Collider.h"

//default collider methods (if needed)

//BoxCollider methods
BoxCollider::BoxCollider(float width, float height) : mHeight(height), mWidth(width)
{
    mColliderType = BOX_COLLIDER;
}

void BoxCollider::CalcCollider()
{
    //Create an AABB
     mMin.x = mPos.x - (mWidth / 2.0f); //left side, not a corner
     mMin.y = mPos.y - (mHeight / 2.0f);
     mMax.x = mPos.x + (mWidth / 2.0f);
     mMax.y = mPos.y + (mHeight / 2.0f);

     //Do rotation calculations in narrow phase


}

//other collider type methods