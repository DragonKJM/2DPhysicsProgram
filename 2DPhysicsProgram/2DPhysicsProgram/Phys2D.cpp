#include "Phys2D.h"

#include "time.h"
#include <string>
#include <iomanip>

using namespace Maths;

Phys2D::Phys2D(int argc, char* argv[])
{
	srand(time(NULL));

	InitGL(argc, argv);
	InitObjects();
	glutMainLoop(); //the main game loop. Nothing after this function.
}

Phys2D::~Phys2D(void)
{
	delete camera;

	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
}

void Phys2D::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this); //Sets this as the pointer for 'helloGL' to point to in GLUTCallbacks

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple Physics Program");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //black background
	glutDisplayFunc(GLUTCallbacks::Display); //callback function which calls the display 
	glutKeyboardFunc(GLUTCallbacks::Keyboard); //callback function to make glut aware of the use of keyboard / name of function used
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutPassiveMotionFunc(GLUTCallbacks::Motion);//Same as keyboard but for mouse movement on button click
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE); //milliseconds before method is called, method called then parameter to pass into method called
	glMatrixMode(GL_PROJECTION); //2D Matrices (Projection to screen coords)
	glLoadIdentity(); // Loads identity matrix
	glViewport(0, 0, WIDTH, HEIGHT); //Set the viewport size
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	//glMatrixMode(GL_MODELVIEW); //3D Camera and Model matrices, breaks 2D scene
	//glEnable(GL_TEXTURE_2D);
}

void Phys2D::InitObjects()
{
	//Camera //Camera system based on https://learnopengl.com/Getting-started/Camera but slightly modified to accommodate no use of GLM
	camera = new Camera(); //Setting up the camera
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;  //Location of camera
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f; //Location camera looks at
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;//Defines which way is up

	//Shapes
	 
	//for (int i = 0; i < 350; i++) //rain, with random location and mass between 0.8 and 1.2
	//{
	//	objects.push_back(new Particle({ (rand() % 100 / 100.0f) - (rand() % 150 / 100.0f) , (rand() % 100 / 100.0f) + (rand() % 150 / 100.0f) }, 0.2f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX)) * 0.3f));
	//}
	
	//objects.push_back(new Particle({ 0.0f, 0.0f }, 1.0f));
	objects.push_back(new Box({ 0.0f, 0.0f }, 10.0f, 0.05f, 0.25f));

}

void Phys2D::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clears the scene

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}

	//Enable2DText(); //split enabling/disabling into different sections to prevent doing this code with every single text render

	//RenderText(("Current X Coord:" + std::to_string(camera->eye.x)).c_str(), 10.0f, 760.0f, 1.0f, 0.0f, 0.0f); //turns float to string, then turns string into const char with .c_str()
	//RenderText(("Current Y Coord:" + std::to_string(camera->eye.y)).c_str(), 10.0f, 740.0f, 1.0f, 0.0f, 0.0f);

	//Disable2DText();

	glFlush(); // flushes scene drawn to graphics card
	glutSwapBuffers();
}

void Phys2D::Update()
{
	glLoadIdentity(); //resets modelview matrix every frame so all previous frames aren't included in current one

	//camera
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z,
		camera->eye.x, camera->eye.y, 0,
		camera->up.x, camera->up.y, camera->up.z);

	//objects
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}

	//Redisplay
	glutPostRedisplay();
}

void Phys2D::Keyboard(unsigned char key, int x, int y)
{

	////slow motion would be cool later on
	//if (key == 'z')
	//{
	//	for (int i = 1; i < OBJECT_INSTANCES; i++)
	//	{
	//		objects[i]->Slow(true);
	//	}
	//}

	if (key == 27) //on escape key, exit. https://community.khronos.org/t/how-to-quit-opengl-by-a-key/59739/2
	{
		glutDestroyWindow(0);
		exit(0);
	}
}

void Phys2D::KeyboardUp(unsigned char key, int x, int y)
{
	//if (key == 'z')
	//{
	//	for (int i = 1; i < OBJECT_INSTANCES; i++)
	//	{
	//		objects[i]->Slow(false);
	//	}
	//}
}

void Phys2D::Motion(int x, int y)
{

}


//text rendering functions
void Phys2D::Enable2DText()
{
	glMatrixMode(GL_PROJECTION); // switch to projection matrix
	glPushMatrix(); // save previous projection matrix
	glLoadIdentity(); // reset projection matrix I think
	gluOrtho2D(0, WIDTH, 0, HEIGHT); // set up orthographic projection matrix, treats world as 2D

	glMatrixMode(GL_MODELVIEW); // switch to modelview matrix, text needs to be treated as a 3D object
	glPushMatrix(); // save previous modelview matrix
	glLoadIdentity(); // reset modelview matrix
}

void Phys2D::RenderText(const char* text, float x, float y, float r, float g, float b)
{
	glColor3f(r, g, b); // set text color
	glTranslatef(x, y, 0.0f); // translate correct position, this can be done in raster, but this method allows dynamic movement
	glRasterPos2i(0, 0); // set raster position to bottom left of the 2D screen
	glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)text); // draw text

	glLoadIdentity(); // reset modelview matrix for the next piece of text
}

void Phys2D::Disable2DText()
{
	glPopMatrix(); // restore previous modelview matrix
	glMatrixMode(GL_PROJECTION); // switch back to projection matrix
	glPopMatrix();
}