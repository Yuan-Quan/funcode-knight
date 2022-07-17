#pragma once
#include <string>
#include <functional>
#include <Eigen/Dense>

namespace hk_config {
enum KeyBinds
{
	KEY_UP			= 0x037, //W
	KEY_DOWN		= 0x033, //S
	KEY_LEFT		= 0x021, //A
	KEY_RIGHT		= 0x024, //D
	KEY_JUMP		= 0x02b, //K
	KEY_ATTACK		= 0x02a, //J
	KEY_DASH		= 0x02c, //L
	KEY_SUPER_DASH	= 0x000, //NULL
	KEY_FOCUS		= 0x031, //Q
	KEY_QUCIK_CAST	= 0x029, //I
	KEY_DREAM_NAIL	= 0x000, //NULL
	KEY_INVENTORY	= 0x000  //NULL
};
}

class Kontrol
{
private:
	std::string player_name_;
	std::function<void(std::string, float, float)> tmp_vel_nh_;
	std::function<void(std::string, float, float)> const_vel_nh_;
	std::function<void(std::string, float, float)> tmp_force_nh_;
	std::function<void(std::string, float, float)> const_force_nh_;
	std::function<bool()> is_grounded_nh_;

	Eigen::Vector2f tmp_vel_;
	Eigen::Vector2f const_vel_;
	Eigen::Vector2f tmp_force_;
	Eigen::Vector2f const_force_;

	Eigen::Vector2f tmp_vel_jump;
	Eigen::Vector2f const_force_jump;
	Eigen::Vector2f const_vel_left_;
	Eigen::Vector2f const_vel_right_;
	Eigen::Vector2f const_vel_dash_;

	float jump_time_ = 0.f;
	bool is_jumping_ = false;
	float dash_time_ = 0.f;
	float dash_cd_time = 0.f;
	bool is_dashing_ = false;
	bool heading_left_ = false;
	bool is_dash_cd_ = false;

	void update_jump_stat(float dt);
	void update_dash_stat(float dt);
	void update_cool_down(float dt);
	void update_velocity();
	void summing();

	void on_jump_key_press();
	void on_jump_key_release();
	void on_dash_key_press();
	void set_left();
	void unset_left();
	void set_right();
	void unset_right();
	void set_jump();
	void unset_jump();
	void set_dash();
	void unset_dash();

public:
	/// <summary>
	/// keyboard control
	/// </summary>
	/// <param name="name"></param> give me the name of the player
	Kontrol(std::string name);

	void key_press_callback(int key);
	void key_relese_callback(int key);

	void set_physics_engine_handler(
		std::function<void(std::string, float, float)> tmp_vel,
		std::function<void(std::string, float, float)> const_vel,
		std::function<void(std::string, float, float)> tmp_force,
		std::function<void(std::string, float, float)> const_force
	);

	void set_gound_state_handler(std::function<bool()> is_grounded);

	void main_loop(float dt);
};

