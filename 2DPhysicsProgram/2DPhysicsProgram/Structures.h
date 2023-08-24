#pragma once

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <Windows.h>
#include <string>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include <vector>

class SceneObject; //forward dec so it knows what sceneobjects are, by the time it needs them it has them included

//structs for camera and movement
struct Vector2
{
	float x, y;
	Vector2() : x(0.0f), y(0.0f) {} //default constructor because otherwise all Vector2s needed to follow below constructor format
	Vector2(float x, float y) : x(x), y(y) {} //constructor for functions that return a Vector2 construction

	//operand overloads //https://en.cppreference.com/w/cpp/language/operators
	Vector2 operator- (const Vector2& other) const //defines what the - operator does for this structure, only works against other vector3s, const after means it won't change the parameters themselves
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator+ (const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2& operator-= (const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this; //You use *this when modifying the value directly
	}

	Vector2& operator+= (const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2 operator* (float scalar) const //for the movement calculations of the camera, Vector3 has to come before float
	{
		return Vector2(x * scalar, y * scalar);
	}
};

struct Vector3
{
	float x, y, z;

};

struct Camera
{
	Vector3 eye, center, up;
};

//structs for shapes
struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat	x, y;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Vector2* Normals;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount, NormalCount, IndexCount, TexCoordCount;
};

#endif // STRUCTURES_H