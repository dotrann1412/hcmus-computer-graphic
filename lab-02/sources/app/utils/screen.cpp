#include "screen.h"

#include "renderer.h"

#include "../objects/Line.h"

Screen::Screen(char** args_v, int args_c) {
	m_glut_screen_id = Renderer::glut_initialize(args_v, args_c);
	attach_menu();
	Line object = {{10, 10}, {500, 500}};
	glutDisplayFunc(Renderer::display);
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
	
	int incremental_code = 1;
	
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
	glutAddMenuEntry("Clear", incremental_code++);
	
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

	k_choice = code;
	glutPostRedisplay();
}

void Screen::terminate() {
	if (k_instance)
		delete k_instance;
	k_instance = nullptr;
}

Screen* Screen::k_instance = nullptr;


int Screen::k_menu_id;
int Screen::k_choice;
std::vector<int> Screen::k_menu_slots;