#include "screen.h"
#include <memory>
#include <ctime>
#include <iostream>
#include "./timer.h"
#include <future>

void Screen::display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix
	// Render a color-cube consisting of 6 quads with different colors
	glLoadIdentity(); // Reset the model-view matrix

	glLineWidth(5);
	glTranslatef(1.5f, 0.0f, -7.0f);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(300.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 300.0);
	glEnd();

	glTranslatef(1.5f, 0.0f, -7.0f); // Move right and into the screen
	glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
		// Top face (y = 1.0f)
		// Define vertices in counter-clockwise (CCW) order with normal pointing out
		glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		// Bottom face (y = -1.0f)
		glColor3f(1.0f, 0.5f, 0.0f); // Orange
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		// Front face (z = 1.0f)
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		// Back face (z = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		// Left face (x = -1.0f)
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		// Right face (x = 1.0f)
		glColor3f(1.0f, 0.0f, 1.0f); // Magenta
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd(); // End of drawing color-cube
	// Render a pyramid consists of 4 triangles
	glLoadIdentity(); // Reset the model-view matrix
	glTranslatef(-1.5f, 0.0f, -6.0f); // Move left and into the screen
	glBegin(GL_TRIANGLES); // Begin drawing the pyramid with 4 triangles
		// Front
		glColor3f(1.0f, 0.0f, 1.0f); // Red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		// Right
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		// Back
		glColor3f(0.0f, 1.0f, 0.0f); // Red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		// Left
		glColor3f(0.0f, 0.0f, 1.0f); // Red
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd(); // Done drawing the pyramid

	//glLoadIdentity(); // Reset the model-view matrix
	//glBegin(GL_POINT);
	//glVertex3f(-2.0f, -2.0f, 2.0f);
	//glEnd();
	

	glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}

Screen::Screen(char** argv, int argc) {
	Shape::initialize(Screen::WINDOW_WIDTH + 1, Screen::WINDOW_HEIGHT + 1);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(640, 480); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("DEMO"); // Create window with the given title
	glutDisplayFunc(Screen::display); // Register callback handler for window re-paint event
	glutReshapeFunc(Screen::onScreenSizeChanged);
	glut_initialize();
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
	k_mouse_btn = btn;
	k_mouse_state = state;

	if (btn == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			bool hehe = false;
			for (int i = k_shapes.size() - 1; i >= 0 && !hehe; --i) {
				if (k_shapes[i]->contain({ x, Screen::WINDOW_HEIGHT - y })) {
					if (i != k_selectedIndex) {
						if (k_selectedIndex != -1) {
							k_shapes[k_selectedIndex]->unselect();
						}
						k_shapes[i]->select();
						k_selectedIndex = i;
						glutPostRedisplay();
					}
					hehe = true;
				}
			}
			
			if (!hehe && k_selectedIndex >= 0 && k_selectedIndex < k_shapes.size()) {
				k_shapes[k_selectedIndex]->unselect();
				k_selectedIndex = -1;
				glutPostRedisplay();
			}

			if (k_selectedIndex == -1 && k_hasSelection) {
				k_pressed = { x, Screen::WINDOW_HEIGHT - y };
				k_shapes.push_back(k_selectedCreator());
				k_shapes.back()->setBoundary(k_pressed, k_pressed);
				k_shapes.back()->setFillColor(k_selectedColor);
			}
		} else if(state == GLUT_UP) {
			if (k_selectedIndex == -1 && k_hasSelection
				&& k_pressed.x() == x && k_pressed.y() == Screen::WINDOW_HEIGHT - y)
				k_shapes.pop_back(), glutPostRedisplay();
			
		}
	}
}

void Screen::onMouseMovement(int x, int y) {
	if (k_selectedIndex != -1)
		return;

	if (x < 0) x = 0;
	if (x >= Screen::WINDOW_WIDTH) x = Screen::WINDOW_WIDTH - 1;

	if (y < 0) y = 0;
	if (y >= Screen::WINDOW_HEIGHT) y = Screen::WINDOW_HEIGHT - 1;


	if (k_mouse_btn == GLUT_LEFT_BUTTON) {
		if (k_mouse_state != GLUT_UP && k_shapes.size()) {
			k_shapes.back()->setBoundary(k_pressed, {x, Screen::WINDOW_HEIGHT - y});
			glutPostRedisplay();
		}
	}
}

void Screen::onKeyBoardEvent_Extend(int key, int x, int y) {
	if (k_selectedIndex >= 0 && k_selectedIndex < k_shapes.size()) {
		switch (key)
		{
			case GLUT_KEY_LEFT: {
				k_shapes[k_selectedIndex]->shift(-1, 0);
				glutPostRedisplay();
				break;
			}

			case GLUT_KEY_RIGHT: {
				k_shapes[k_selectedIndex]->shift(1, 0);
				glutPostRedisplay();
				break;
			}

			case GLUT_KEY_UP: {
				k_shapes[k_selectedIndex]->shift(0, 1);
				glutPostRedisplay();
				break;
			}

			case GLUT_KEY_DOWN: {
				k_shapes[k_selectedIndex]->shift(0, -1);
				glutPostRedisplay();
				break;
			}


			default:
				break;

		}
	}
}

void Screen::onKeyBoardEvent(uint8_t key, int x, int y) {
	if (k_selectedIndex >= 0 && k_selectedIndex < k_shapes.size()) {
		switch (key)
		{
		case 127: {
			k_shapes.erase(k_shapes.begin() + k_selectedIndex);
			glutPostRedisplay();
			k_selectedIndex = -1;
			break;
		}

		case 'L': case 'l': {
			k_shapes[k_selectedIndex]->rotate(-0.0174532925 );
			glutPostRedisplay();
			break;
		}

		case 'R': case 'r': {
			k_shapes[k_selectedIndex]->rotate( 0.0174532925 );
			glutPostRedisplay();
			break;
		}

		case 61: {
			k_shapes[k_selectedIndex]->scale(1.1);
			glutPostRedisplay();
			break;
		}

		case 45: {
			k_shapes[k_selectedIndex]->scale(0.9);
			glutPostRedisplay();
			break;
		}

		default:
			break;
		}
	}
}

std::map<int,  std::function<void()>> Screen::buildMenuEntries () {
	std::map<int,  std::function<void()>> res;

	std::vector<std::pair<std::string, std::function<void()>>> shapes_list = {
		{"Rectangle", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) { return std::shared_ptr<Shape> ( new Rectangle(k_pressed, k_pressed, Color::BLACK, k_selectedColor)); }; }
		},
		{"Square", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Square(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Triangle", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Triangle(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Circle", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Circle(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Elipse", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Elipse(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Arrow", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Arrow(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Star", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Star(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Minus", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Minus(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Times", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Times(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Divide", [&]() {
			k_hasSelection = true,
			k_selectedCreator = []() {return std::shared_ptr<Shape>(new Divide(k_pressed, k_pressed, Color::BLACK, k_selectedColor)); }; }
		},
		{"Plus", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Plus(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Hexagon", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Hexagon(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Pentagon", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Pentagon(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; }
		},
		{"Line", [&] () {
			k_hasSelection = true, 
			k_selectedCreator  = [] ( ) {return std::shared_ptr<Shape> ( new Line(k_pressed, k_pressed, Color::BLACK, k_selectedColor));}; 
		}}
	};

	std::vector<std::pair<std::string, std::function<void()>>> colors_list = {
		{"Red", [&] () { 
			k_selectedColor = Color::RED; 
			changeCurrentSelectedColor();
		}},
		{"Green", [&] () { 
			k_selectedColor = Color::GREEN; 
			changeCurrentSelectedColor();
		}},
		{"Blue", [&] () { 
			k_selectedColor = Color::BLUE; 
			changeCurrentSelectedColor();
		}},
		{"Cyan", [&] () { 
			k_selectedColor = Color::CYAN; 
			changeCurrentSelectedColor();
		}},
		{"Yellow", [&] () { 
			k_selectedColor = Color::YELLOW; 
			changeCurrentSelectedColor(); 
		}},
		{"Black", [&] () { 
			k_selectedColor = Color::BLACK; 
			changeCurrentSelectedColor();
		}},
		{"Purble", [&]() {
			k_selectedColor = Color::PURBLE;
			changeCurrentSelectedColor();
		}},
		{"Orange", [&]() {
			k_selectedColor = Color::ORANGE;
			changeCurrentSelectedColor();
		}},
		{"Gray", [&]() {
			k_selectedColor = Color::GRAY;
			changeCurrentSelectedColor();
		}},
		{"None", [&] () { 
			k_selectedColor = Color::WHITE; 
			changeCurrentSelectedColor(); 
		}},
	};

	std::vector<std::pair<std::string, std::function<void()>>> root_entry = {
		{"Clear", [&]() {
			k_shapes.clear();

			k_hasSelection = true;
			k_selectedCreator = []() {
				return std::shared_ptr<Shape>(new Rectangle(k_pressed, k_pressed, Color::BLACK, k_selectedColor));
			};

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

std::function<std::shared_ptr<Shape>()> Screen::k_selectedCreator = [] ( ) { 
	return std::shared_ptr<Shape> ( new Rectangle(k_pressed, k_pressed, Color::BLACK, k_selectedColor)); 
}; 

Color Screen::k_selectedColor = Color::CYAN;

const int Screen::WINDOW_HEIGHT = 480;

const int Screen::WINDOW_WIDTH = 640;

std::vector<std::shared_ptr<Shape>> Screen::k_shapes;

std::map<int,  std::function<void()>> Screen::k_menuSlots;

int Screen::k_hasSelection = true;

int Screen::k_selectedIndex = -1;

std::function<void()> Screen::changeCurrentSelectedColor = []() {
	if (k_selectedIndex != -1 && k_selectedColor != k_shapes[k_selectedIndex]->getFillColor()) {
		k_shapes[k_selectedIndex]->setFillColor(k_selectedColor.darker());
		glutPostRedisplay();
	}
};
