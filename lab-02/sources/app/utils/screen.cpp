#include "screen.h"

#include <memory>

const int Screen::WINDOW_HEIGHT = 700;

const int Screen::WINDOW_WIDTH = 700;

std::vector<std::shared_ptr<Shape>> Screen::k_shapes;
#include <ctime>

#include <iostream>

#include "./timer.h"

#include <future>

void Screen::display() 
{
    glClear(GL_COLOR_BUFFER_BIT);
	static Timer timer;

	float point_size = max(1.0 * glutGet(GLUT_WINDOW_WIDTH) / Screen::WINDOW_WIDTH, 1.0 * glutGet(GLUT_WINDOW_HEIGHT) / Screen::WINDOW_HEIGHT);
	glPointSize(point_size);
	
	timer.start();
	for (const auto& x: k_shapes)
		x->render();

	// std::cerr << "Rendering takes: " << timer.stop() << " second(s)\n";

    glFlush();
}

Screen::Screen(char** args_v, int args_c) {
	Shape::initialize(Screen::WINDOW_WIDTH + 1, Screen::WINDOW_HEIGHT + 1);
	srand(time(nullptr));

	m_glut_screen_id = glut_initialize(args_v, args_c);
	attach_menu();
	Line object = {{10, 10}, {500, 500}};
	glutDisplayFunc(Screen::display);
	glutMainLoop();
}

Screen::~Screen() {
	glutDestroyWindow(this->m_glut_screen_id);
}

Screen* Screen::show(char** args_v, int args_c) {
	if (k_instance)
		return k_instance;
	return k_instance = new Screen(args_v, args_c);
}

void Screen::attach_menu(void) {
	
	int incremental_code = 2;
	
	std::vector<std::string> colors = {
		"Red", "White", "Yellow", "Green", "Blue"
	};

	std::vector<std::string> objects = {
		"Teapot", "Sphere", "Torus", "Cone"
	};

	k_menu_slots.assign(objects.size(), 0);

	for (int i = 0; i < objects.size(); ++i) {
		k_menu_slots[i] = glutCreateMenu(menu);
		for (int j = 0; j < colors.size(); ++j) {
			glutAddMenuEntry(colors[j].c_str(), incremental_code++);
		}
	}

	k_menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Clear", 1);
	
	for (int i = 0; i < objects.size(); ++i) {
		glutAddSubMenu(objects[i].c_str(), k_menu_slots[i]);
	}

	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Screen::menu(int code) {
	if (!code) {
		delete k_instance;
		exit(0);
	}

	if (code == 1) {
		k_shapes.clear();
		glutPostRedisplay();
	}
}

void Screen::terminate() {
	if (k_instance)
		delete k_instance;
	k_instance = nullptr;
}

int Screen::glut_initialize(char** argv, int argc) {
	glutInit(&argc, argv);
    glutInitWindowSize(Screen::WINDOW_WIDTH, Screen::WINDOW_HEIGHT);
    int id = glutCreateWindow("Student 20120057 - Lab 02");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluOrtho2D(0.0, Screen::WINDOW_WIDTH, 0.0, Screen::WINDOW_HEIGHT);

	// glutReshapeFunc(Screen::onScreenSizeChanged);
	glutMouseFunc(Screen::onMouseEvent);
	glutMotionFunc(Screen::onMouseMovement);    
	return id;
}

void Screen::onScreenSizeChanged(int w, int h) {
	
	if (w !=  WINDOW_WIDTH || h != WINDOW_HEIGHT)
		glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Screen::onMouseEvent(int btn, int state, int x, int y) {
	k_mouse_btn = btn;
	k_mouse_state = state;

	static std::vector<Color> random_set = {
		Color::RED,
		Color::BLUE,
		Color::GREEN
	};

	if (btn == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			k_pressed = {x, Screen::WINDOW_HEIGHT - y};
			k_shapes.push_back(std::shared_ptr<Shape> (
				new Elipse(k_pressed, k_pressed, Color::GREEN, random_set[rand() % random_set.size()]))
			);
		} else if(state == GLUT_UP) {
			if (k_pressed.x() == x && k_pressed.y() == Screen::WINDOW_HEIGHT - y)
				k_shapes.pop_back();
		}
	}
}

void Screen::onMouseMovement(int x, int y) {
	if (x < 0) x = 0;
	if (x >= Screen::WINDOW_WIDTH) x = Screen::WINDOW_WIDTH - 1;

	if (y < 0) y = 0;
	if (y >= Screen::WINDOW_HEIGHT) y = Screen::WINDOW_HEIGHT - 1;

	if (k_mouse_btn == GLUT_LEFT_BUTTON) {
		if (k_mouse_state != GLUT_UP) {
			k_shapes.back()->setBoundary(k_pressed, {x, Screen::WINDOW_HEIGHT - y});
			glutPostRedisplay();
		}
	}
}

Screen* Screen::k_instance = nullptr;


int Screen::k_menu_id;

int Screen::k_choice;

std::vector<int> Screen::k_menu_slots;

int Screen::k_mouse_btn;
	
int Screen::k_mouse_state;

Point Screen::k_pressed;