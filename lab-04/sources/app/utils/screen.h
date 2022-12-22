#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <vector>
#include "../objects/2d_objects/all.h"
#include "../objects/3d_objects/all.h"

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

	static std::vector<std::shared_ptr<Shape3D>> k_shapes;

	static Color k_selectedColor;
	
	static int k_hasSelection;

	static int k_selectedIndex;

private: // state 

    static void glut_initialize();

	static void onScreenSizeChanged(int w, int h);

	static void onMouseEvent(int btn, int state, int x, int y);

	static void onMouseMovement(int x, int y);

	static void onMouseMotion(int x, int y);

	static void onKeyBoardEvent(uint8_t key, int x, int y);

	static void onKeyBoardEvent_Extend(int key, int x, int y);

	static void onIdle(int);

private:
	int m_glut_screen_id;

	static float k_rotationState;

	static const int WINDOW_HEIGHT;

	static const int WINDOW_WIDTH;

	static std::map<int, std::function<void()>> buildMenuEntries();

	static std::function<void()> changeCurrentSelectedColor;

	static const Point3i CAMERA_POSITION;
};

#endif