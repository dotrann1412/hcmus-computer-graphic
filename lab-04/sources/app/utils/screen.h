#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <vector>
#include "../objects/all.h"

#include <map>
#include <memory>
#include <functional>


class Screen
{
private:
	~Screen();
	
	Screen(char** args_v, int args_c);
	
	static void menu(int);

	static void shape_menu(int);

	static void display();

	static void onIdle(int);

public:
	static Screen* show(char** args_v, int args_c);
	
	static void close();

private:
	static Screen* k_instance;

	static std::vector<std::shared_ptr<Shape3D>> k_shapes;

private: // state 

    static void glut_initialize();

	static void onScreenSizeChanged(int w, int h);

private:
	int m_glut_screen_id;

private:
	static const int WINDOW_HEIGHT;

	static const int WINDOW_WIDTH;
};

#endif