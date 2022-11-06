#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <vector>

class Screen
{
private:
	~Screen();
	Screen(char** args_v, int args_c);
	static void menu(int);
	static void attach_menu(void);

public:
	static Screen* show(char** args_v, int args_c);
	static void terminate();

private:
	int m_glut_screen_id;

	static Screen* k_instance;		
	static int k_menu_id;
	static int k_choice;
	static std::vector<int> k_menu_slots;
};

#endif