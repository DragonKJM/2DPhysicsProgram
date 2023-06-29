#pragma once
class Phys2D; //This is necessary as both files need one another to work I think, so because they can't load at the same time we just tell it this will exist.

namespace GLUTCallbacks
{
	void Init(Phys2D* gl);

	void Display();

	void Timer(int preferredRefresh);

	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void Motion(int x, int y);
}

