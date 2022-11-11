#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <vector>

#include "../objects/all.h"

#include <memory>

class Screen
{
private:
	~Screen();
	
	Screen(char** args_v, int args_c);
	
	static void menu(int);
	
	static void attach_menu(void);

	static void display();

public:
	static Screen* show(char** args_v, int args_c);
	
	static void terminate();

private:
	int m_glut_screen_id;

	static Screen* k_instance;		
	
	static int k_menu_id;
	
	static int k_choice;
	
	static std::vector<int> k_menu_slots;

	static std::vector<std::shared_ptr<Shape>> k_shapes;

	static int k_mouse_btn;
	
	static int k_mouse_state;
	
	static Point k_pressed;

private:
    static const int WINDOW_HEIGHT;
    
    static const int WINDOW_WIDTH;

    static int glut_initialize(char** args, int args_count);

	static void onScreenSizeChanged(int w, int h);

	static void onMouseEvent(int btn, int state, int x, int y);

	static void onMouseMovement(int x, int y);
	
private:
	
};

#endif