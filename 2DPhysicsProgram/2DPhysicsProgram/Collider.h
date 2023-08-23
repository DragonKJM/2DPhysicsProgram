#pragma once

#include "Structures.h"

enum ColliderType
{
    UNKNOWN_COLLIDER,
    BOX_COLLIDER,
    //CIRCLE_COLLIDER,
    //other collider types
};

class Collider
{
public:
    Collider() : mColliderType(UNKNOWN_COLLIDER) {} //default unknown
    virtual ~Collider() {}

    ColliderType getType() const { return mColliderType; }

    void setPos(Vector2 pos) { mPos = pos; }
    void setRotation(float angle) { mRotation = angle; }

    virtual void CalcCollider() = 0;

    Vector2 mMin{ 0.0f, 0.0f }, mMax{ 0.0f, 0.0f };

    bool mInNarrowPhase {false};
    float mRotation{ 0.0f };

protected:
    ColliderType mColliderType;
    Vector2 mPos{ 0.0f, 0.0f };

};

class BoxCollider : public Collider
{
public:
    BoxCollider(float height, float width);

    void CalcCollider() override;

private:
    float mWidth; 
    float mHeight;
};

//class CircleCollider : public Collider
//{
//    //CircleCollider stuff
//};

