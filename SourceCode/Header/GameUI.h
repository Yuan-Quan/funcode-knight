#pragma once
#include "SimplePhysics.h"
#include "Kontrol.h"

struct SaveFile
{
	int scene;
	long time;
	int difficulty;
};

class GameUI
{
public:
	GameUI();
	bool key_press_callback(int key);
	bool key_release_callback(int key);
	void set_physics_instance(SimplePhysics* ins);
	void set_main_menu(bool b);
	void set_save_menu(bool b);
	void main_loop();
	void set_scene_switch_handler(std::function<void(int)> fun);
	int difficulty_option;
	SaveFile* save;
	bool is_in_main_menu;
	bool is_in_save_menu;
	bool is_in_pause_menu;
	bool is_in_difficulty_menu;
	bool is_interact;
private:

	int requested_scene_switch = -1;

	CSprite* pause_resume;
	CSprite* pause_quit;
	CSprite* pause_option;
	CSprite* save_menu_selector;
	CSprite* main_menu_selector;
	CSprite* save_black;
	CSprite* save_dirt;
	CSprite* save_kings;
	CSprite* save_forgotten;
	CSprite* difficulty_selector;

	CTextSprite* txt_save_area;
	CTextSprite* txt_save_time;
	CTextSprite* txt_save_difficulty;

	int main_menu_option;
	int pause_menu_option;
	int save_menu_option;

	void display_pause();

	SimplePhysics* physics_instance_;
	std::function<void(int)> scene_switch_handler_ = NULL;
};

