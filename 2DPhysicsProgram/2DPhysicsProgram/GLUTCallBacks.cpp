#include "GLUTCallbacks.h"
#include "Phys2D.h"

//Namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		//Initialise to a null pointer before we do anything
		Phys2D* phys2D = nullptr;
	}

	void Init(Phys2D* gl) //gl is assigned to "this" in HelloPhysics cpp
	{
		phys2D = gl; //Assigns pointer to entire Phys2D cpp file, allows reference to all functions for callbacks.
	}

	void Display() //In constructor on Phys2D.cpp, calls this function, which then calls display - but why have this here and not in same cpp? Ask 
	{

		if (phys2D != nullptr)
		{
			phys2D->Display();
		}
	}

	void Timer(int preferredRefresh) //Same as display, called in cpp constructor, then this calls update
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		phys2D->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		phys2D->Keyboard(key, x, y);
	}

	void KeyboardUp(unsigned char key, int x, int y)
	{
		phys2D->KeyboardUp(key, x, y);
	}

	void Motion(int x, int y)
	{
		phys2D->Motion(x, y);
	}
}