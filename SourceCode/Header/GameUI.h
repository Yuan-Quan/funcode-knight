#pragma once
#include "SimplePhysics.h"
#include "Kontrol.h"
class GameUI
{
public:
	GameUI();
	bool key_press_callback(int key);
	void set_physics_instance(SimplePhysics* ins);
	void main_loop();
private:
	bool is_in_main_menu;
	bool is_in_pause_menu;
	bool is_interact;

	CSprite* pause_resume;
	CSprite* pause_quit;
	CSprite* pause_option;

	int pause_menue_option;

	void display_pause();

	SimplePhysics* physics_instance_;
};

