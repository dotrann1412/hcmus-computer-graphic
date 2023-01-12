#include "screen.h"
#include <memory>
#include <ctime>
#include <iostream>

#include "./timer.h"

#include <SOIL.h>

void Screen::display()
{
	static int texture = SOIL_load_OGL_texture
	(
		".\\res\\textures\\metal_bmp.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	static std::vector<std::shared_ptr<Shape3D>> shapes = {
		std::shared_ptr<Shape3D>(new Torus({0, 0, -40 }, {5, 5, 5}, texture)),
		std::shared_ptr<Shape3D>(new Cone({0, 8, -40 }, {5, 5, 5}, texture)),
		std::shared_ptr<Shape3D>(new Cube({0, -8, -40 }, {5, 5, 5}, texture)),

		std::shared_ptr<Shape3D>(new Cylinder({-10, 0, -40}, {5, 5, 5}, texture)),
		std::shared_ptr<Shape3D>(new Sphere({-10, 8, -40}, {5, 5, 5}, texture)),
		std::shared_ptr<Shape3D>(new Sphere({10, 0, -40 }, {5, 5, 5}, texture)),

		std::shared_ptr<Shape3D>(new Hyperpoloid({-10, -8, -40 }, {5, 5, 5}, texture)),
		std::shared_ptr<Shape3D>(new Cylinder({10, 8, -40 }, {5, 5, 5}, texture)),
		std::shared_ptr<Shape3D>(new Hyperpoloid({10, -8, -40 }, {5, 5, 5}, texture)),
	};
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix

	for (auto x : shapes) {
		x->render();
		x->rotate(0.02, 0.02, 0.02);
	}

	glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}

Screen::Screen(char** argv, int argc) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(960, 720); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("DEMO"); // Create window with the given title
	glutDisplayFunc(Screen::display); // Register callback handler for window re-paint event
	glutReshapeFunc(Screen::onScreenSizeChanged);
	glutTimerFunc(0, Screen::onIdle, 0);
	glut_initialize();
	glutMainLoop();

}

void Screen::onIdle(int) {
	glutPostRedisplay();
	glutTimerFunc(40, Screen::onIdle, 0);
}

Screen::~Screen() {
	glutDestroyWindow(this->m_glut_screen_id);
}

Screen* Screen::show(char** args_v, int args_c) {
	if (k_instance)
		return k_instance;
	return k_instance = new Screen(args_v, args_c);
}

void Screen::close() {
	if (k_instance)
		delete k_instance;
	k_instance = nullptr;
}

void Screen::glut_initialize() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f); // Set background depth to farthest
	glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL); // Set the type of depth-test
	glShadeModel(GL_SMOOTH); // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections
	glEnable(GL_TEXTURE_2D);
}

void Screen::onScreenSizeChanged(int w, int h) {
	// Compute aspect ratio of the new window
	if (h == 0) h = 1; // To prevent divide by 0
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	// Set the viewport to cover the new window
	glViewport(0, 0, w, h);
	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
	glLoadIdentity(); // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}


Screen* Screen::k_instance = nullptr;

const int Screen::WINDOW_HEIGHT = 480;

const int Screen::WINDOW_WIDTH = 640;

std::vector<std::shared_ptr<Shape3D>> Screen::k_shapes;