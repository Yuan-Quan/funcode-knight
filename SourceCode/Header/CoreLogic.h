#pragma once
#include <string>
#include "CommonClass.h"
#include <vector>
#include "HUD.h"

struct NPC
{
	int hp;
	CSprite* sp;
};

class CoreLogic
{
private:
	std::vector<NPC*> enemies_;
	std::string player_name_;
	int player_hp_ = 5;
	int player_soul_ = 10;
	bool is_immortal_ = false;
	float immortal_timer_ = 0.f;
	bool is_alive = true;
	void die();

	void set_immortal_after_damage();
public:
	CoreLogic(std::string player_name);
	HUD* hud_instance_;
	void set_player_name(std::string name);
	void set_hud_instance(HUD* hud);
	void add_enemy(std::string name, int hp);
	// some of them here are not meant to be public 
	// the only reason that they're public, is for the ease of debug
	void take_damange();
	void heal_a_mask();
	void drain_1_soul();
	void attack_npc(NPC* npc);
	void respawn();
	int get_soul_level();

	void attack_callback();
	void heal_callback();
	void sp_col_callback(std::string src_name, std::string tar_name);

	void update_immortal_state(float dt);
	void update_hud_status();
	void main_loop(float dt);
	void init();
};
