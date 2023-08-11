#include "Collider.h"
#include <cmath> //cos, sin, etc.

//default collider methods (if needed)

//boxCollider methods
BoxCollider::BoxCollider(float height, float width) : mHeight(height), mWidth(width)
{
    mColliderType = BOX_COLLIDER;
}

void BoxCollider::CalcCollider()
{
    float halfWidth = mWidth / 2.0f;
    float halfHeight = mHeight / 2.0f;

    if (mInNarrowPhase == false)
    {
        //create an AABB
        mMin.x = mPos.x - halfWidth; //left side, not a corner
        mMin.y = mPos.y - halfHeight;
        mMax.x = mPos.x + halfWidth;
        mMax.y = mPos.y + halfHeight;
    }

     //do rotation calculations in narrow phase
     if (mInNarrowPhase)
     {
         //convert rotation from degrees to radians
         float rotationRad = mRotation * 3.14159265358979323846 / 180.0f;

         //calculate the sine and cosine of the rotation angle
         float cosAngle = std::cos(rotationRad); //used for width
         float sinAngle = std::sin(rotationRad); //used for height

         //calculate the rotated bounding box's half-width and half-height - this is causing a 0.01 error margin, unsure how to fix
         float rotatedHalfWidth = std::abs(cosAngle * halfWidth) + std::abs(sinAngle * halfHeight); 
         float rotatedHalfHeight = std::abs(sinAngle * halfWidth) + std::abs(cosAngle * halfHeight);

         //calculate the left, right, top, and bottom edges of the rotated bounding box
         mMin.x = mPos.x - rotatedHalfWidth;
         mMin.y = mPos.y - rotatedHalfHeight;
         mMax.x = mPos.x + rotatedHalfWidth;
         mMax.y = mPos.y + rotatedHalfHeight;
     }

}

//other collider type methods