#include "screen.h"
#include <memory>
#include <ctime>
#include <iostream>
#include "./timer.h"

void Screen::display() 
{
	static std::vector<std::shared_ptr<Shape3D>> shapes = {
		std::shared_ptr<Shape3D>(new Cube({-10, 8, -40 }, {5, 5, 5})),
		std::shared_ptr<Shape3D>(new Sphere({0, 8, -40 }, {5, 5, 5})),
		std::shared_ptr<Shape3D>(new Cube({10, 8, -40 }, {5, 5, 5})),

		std::shared_ptr<Shape3D>(new Sphere({-10, 0, -40 }, {5, 5, 5})),
		std::shared_ptr<Shape3D>(new Cube({0, 0, -40 }, {5, 5, 5})),
		std::shared_ptr<Shape3D>(new Sphere({10, 0, -40 }, {5, 5, 5})),

		std::shared_ptr<Shape3D>(new Cube({-10, -8, -40 }, {5, 5, 5})),
		std::shared_ptr<Shape3D>(new Sphere({0, -8, -40 }, {5, 5, 5})),
		std::shared_ptr<Shape3D>(new Cube({10, -8, -40 }, {5, 5, 5})),
	};
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix

	for (auto x : shapes) {
		glColor3ub(255, 255, 0);
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
	// glutMotionFunc(Screen::onMouseMotion);
	glutTimerFunc(0, Screen::onIdle, 0);
	glut_initialize();
	glutMainLoop();
}

void Screen::onIdle(int) {
	glutPostRedisplay();
	glutTimerFunc(20, Screen::onIdle, 0);
}

Screen::~Screen() {
	glutDestroyWindow(this->m_glut_screen_id);
}

Screen* Screen::show(char** args_v, int args_c) {
	if (k_instance)
		return k_instance;
	return k_instance = new Screen(args_v, args_c);
}

void Screen::shape_menu(int code) {
	if (code == 4) {
		delete k_instance;
		exit(0);
	}

	k_menuSlots[code]();
}

void Screen::menu(int code) {
	if (code == 4) {
		delete k_instance;
		exit(0);
	}

	k_menuSlots[code]();
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

void Screen::onMouseEvent(int btn, int state, int x, int y) {

}

void Screen::onMouseMovement(int x, int y) {
	
}

void Screen::onMouseMotion(int x, int y) {

}

void Screen::onKeyBoardEvent_Extend(int key, int x, int y) {
	if (k_selectedIndex >= 0 && k_selectedIndex < k_shapes.size()) {
		switch (key)
		{
			
			default:
				break;
		}
	}
}

void Screen::onKeyBoardEvent(uint8_t key, int x, int y) {
	if (k_selectedIndex >= 0 && k_selectedIndex < k_shapes.size()) {
		switch (key)
		{
		
		default:
			break;
		}
	}
}

std::map<int,  std::function<void()>> Screen::buildMenuEntries () {
	std::map<int,  std::function<void()>> res;

	std::vector<std::pair<std::string, std::function<void()>>> shapes_list = {

	};

	std::vector<std::pair<std::string, std::function<void()>>> colors_list = {
		
	};

	std::vector<std::pair<std::string, std::function<void()>>> root_entry = {
		{"Clear", [&]() {
			glutPostRedisplay();
		}},
		{"Choose shape", []() {}},
		{"Choose color", []() {}},
		{"Exit", [&] () {}},
	};

	int iter = 10;

	int shape_menu_id = glutCreateMenu(menu);
	
	for (int i = 0; i < shapes_list.size(); ++i) {
		res[iter] = shapes_list[i].second;
		glutAddMenuEntry(shapes_list[i].first.c_str(), iter++);
	}

	int color_menu_id = glutCreateMenu(menu);

	for (int i = 0; i < colors_list.size(); ++i) {
		res[iter] = colors_list[i].second;
		glutAddMenuEntry(colors_list[i].first.c_str(), iter++);
	}

	k_menu_id = glutCreateMenu(menu);

	glutAddMenuEntry(root_entry[0].first.c_str(), 0);
	res[0] = root_entry[0].second;

	glutAddSubMenu(root_entry[1].first.c_str(), shape_menu_id);

	glutAddSubMenu(root_entry[2].first.c_str(), color_menu_id);

	glutAddMenuEntry(root_entry[3].first.c_str(), 4);
	// res[4] = root_entry[4].second;

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return res;
};

Screen* Screen::k_instance = nullptr;

int Screen::k_menu_id;

int Screen::k_choice;

int Screen::k_mouse_btn;

int Screen::k_mouse_state;

Point Screen::k_pressed;


Color Screen::k_selectedColor = Color::CYAN;

const int Screen::WINDOW_HEIGHT = 480;

const int Screen::WINDOW_WIDTH = 640;

std::vector<std::shared_ptr<Shape3D>> Screen::k_shapes;

std::map<int,  std::function<void()>> Screen::k_menuSlots;

int Screen::k_hasSelection = true;

int Screen::k_selectedIndex = -1;

float Screen::k_rotationState = 0;

std::function<void()> Screen::changeCurrentSelectedColor = []() {
	
};

const Point3i Screen::CAMERA_POSITION = {0, 0, 0};