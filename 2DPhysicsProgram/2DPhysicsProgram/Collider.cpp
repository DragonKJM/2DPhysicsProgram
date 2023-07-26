#include "Collider.h"

//default collider methods (if needed)

//BoxCollider methods
BoxCollider::BoxCollider(float width, float height) : mHeight(height), mWidth(width)
{
    mColliderType = BOX_COLLIDER;

    mMinX = 0.0f; mMinY = 0.0f;
    mMaxX = 0.0f; mMaxY = 0.0f;
}

void BoxCollider::CalcCollider()
{
     mMinX = mPos.x - (mWidth / 2.0f);
     mMinY = mPos.y - (mHeight / 2.0f);
     mMaxX = mPos.x + (mWidth / 2.0f);
     mMaxY = mPos.y + (mHeight / 2.0f);

     //rotation calculations? or maybe separate into broad / narrow phase where narrow phase calculates rotation??
}

//other collider type methods