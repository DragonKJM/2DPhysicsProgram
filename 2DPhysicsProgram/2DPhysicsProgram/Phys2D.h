#pragma once
#define WIDTH 800
#define HEIGHT 800
#define REFRESHRATE 16 // (16ms = 60fps)

#include "GLUTCallbacks.h"
#include "Maths.h"
#include "SceneObject.h" //temp, remove when have actual objects
#include "Particle.h"
#include "Box.h"
#include <vector>

	class Phys2D
	{
	private:
		Camera* camera;
		float _timeElapsed;

		std::vector<SceneObject*> objects;

		void InitObjects();
		void InitGL(int argc, char* argv[]);

		void Enable2DText();
		void RenderText(const char* text, float x, float y, float r, float g, float b);
		void Disable2DText();

		void CheckCollisions(std::vector<SceneObject*>& objects);
		bool CheckCollisionSAT(SceneObject* objA, SceneObject* objB);

	public:

		//Constructor definition
		Phys2D(int argc, char* argv[]);

		//destructor
		~Phys2D(void);

		void Display();
		void Update();

		void Keyboard(unsigned char key, int x, int y);
		void KeyboardUp(unsigned char key, int x, int y);
		void Motion(int x, int y);

	};

