#pragma once
#include <string>
#include "CommonClass.h"
#include <vector>
#include <Eigen/Dense>
#include "HUD.h"

struct NPC
{
	int hp;
	CSprite* sp;
};

enum AtkDirection
{
	UP = 0,
	DOWN = 1,
	SIDE = 2,
};

struct Box {
	Eigen::Vector2f position;
	float width;
	float height;
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

	bool is_in_atk_range(CSprite* sp, int atk_dir);
	std::vector<CSprite*> atk_hit_boxs_;
	bool is_col(Box* a, Box* b);

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
	void respawn();
	int get_soul_level();

	void attack_callback(int atk_dir);
	void heal_callback();
	void set_atk_box(std::string up, std::string down, std::string side);
	void sp_col_callback(std::string src_name, std::string tar_name);

	void update_immortal_state(float dt);
	void update_hud_status();
	void update_enemy_status();
	void main_loop(float dt);
	void init();
};

