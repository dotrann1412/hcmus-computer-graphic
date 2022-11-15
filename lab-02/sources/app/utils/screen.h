#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <vector>
#include "../objects/all.h"
#include <map>
#include <memory>
class Screen
{
private:
	~Screen();
	
	Screen(char** args_v, int args_c);
	
	static void menu(int);

	static void shape_menu(int);

	static void display();

public:
	static Screen* show(char** args_v, int args_c);
	
	static void close();

private:
	static int k_menu_id;

	static std::map<int, std::function<void()>> k_menuSlots; 

	static Screen* k_instance;
	
	static int k_choice;

	static int k_mouse_btn;
	
	static int k_mouse_state;
	
	static Point k_pressed;

	static std::vector<std::shared_ptr<Shape>> k_shapes;

	static std::function<std::shared_ptr<Shape>()> k_selectedCreator;

	static Color k_selectedColor;
	
	static int k_hasSelection;

	static int k_selectedIndex;

private:
    static const int WINDOW_HEIGHT;
    
    static const int WINDOW_WIDTH;

    static int glut_initialize(char** args, int args_count);

	static void onScreenSizeChanged(int w, int h);

	static void onMouseEvent(int btn, int state, int x, int y);

	static void onMouseMovement(int x, int y);

	static void onKeyBoardEvent(uint8_t key, int x, int y);

	static std::map<int, std::function<void()>> buildMenuEntries();

	static std::function<void()> changeCurrentSelectedColor;

private:
	int m_glut_screen_id;
};

#endif