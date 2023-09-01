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
         corners.clear();

         //convert rotation from degrees to radians
         float rotationRad = mRotation * 3.14159265358979323846 / 180.0f;

         //calculate the sine and cosine of the rotation angle
         float cosAngle = std::cos(rotationRad); //used for width
         float sinAngle = std::sin(rotationRad); //used for height

         ////calculate the rotated bounding box's half-width and half-height - used if finding the new min / max
         //float rotatedHalfWidth = (cosAngle * halfWidth) - (sinAngle * halfHeight);
         //float rotatedHalfHeight = (sinAngle * halfWidth) + (cosAngle * halfHeight);

         //calculate the vectors from the center of the box to the corners - this is the AABB stretched to fit the rotation values, but not yet rotated
         Vector2 bottomLeft(-halfWidth, -halfHeight);
         Vector2 bottomRight(halfWidth, -halfHeight);
         Vector2 topRight(halfWidth, halfHeight);
         Vector2 topLeft(-halfWidth, halfHeight);

         //rotate the corner vectors using the rotation matrix, this doesn't yet take into account the object pos
         Vector2 rotatedBottomLeft
         (
            cosAngle * bottomLeft.x - sinAngle * bottomLeft.y,
            sinAngle * bottomLeft.x + cosAngle * bottomLeft.y
         );

         Vector2 rotatedBottomRight
         (
            cosAngle * bottomRight.x - sinAngle * bottomRight.y,
            sinAngle * bottomRight.x + cosAngle * bottomRight.y
         );

         Vector2 rotatedTopRight
         (
            cosAngle * topRight.x - sinAngle * topRight.y,
            sinAngle * topRight.x + cosAngle * topRight.y
         );

         Vector2 rotatedTopLeft
         (
            cosAngle * topLeft.x - sinAngle * topLeft.y,
            sinAngle * topLeft.x + cosAngle * topLeft.y
         );

        //translate the rotated corner vectors to the actual position of the OBB
        Vector2 bottomLeftCorner = rotatedBottomLeft + mPos;
        Vector2 bottomRightCorner = rotatedBottomRight + mPos;
        Vector2 topRightCorner = rotatedTopRight + mPos;
        Vector2 topLeftCorner = rotatedTopLeft + mPos;

        corners.push_back(bottomLeftCorner); // bottom left
        corners.push_back(bottomRightCorner); // bottom right
        corners.push_back(topRightCorner); // top right
        corners.push_back(topLeftCorner); // top left
     }

}

//other collider type methods