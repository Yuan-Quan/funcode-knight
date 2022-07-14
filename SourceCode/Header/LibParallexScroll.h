#pragma once
#include <vector>
#include <string>
#include "CommonClass.h"
#include <Eigen/Dense>
#include "pid.h"

class LibParallexScroll
{
private:
	struct SceneryObj
	{
		float z;
		CSprite* scenery;
	};

	std::vector<CSprite*> player_;
	std::vector<CSprite*> npc_;
	std::vector<SceneryObj*> scenery_;
	std::vector<CSprite*> camera_locks_;

	Eigen::Vector2f player_position_;
	Eigen::Vector2f player2cam_target_;

	Eigen::Vector2f player2map_velocity_;
	Eigen::Vector2f camera2map_velocity_;
	Eigen::Vector2f player2cam_velocity_;

	Eigen::Vector2f target_framing_temporary_offset_;
	Eigen::Vector2f cam_vel_temp_offset_;

	bool is_cam_left_lim_ = false;
	bool is_cam_right_lim_ = false;
	bool is_cam_up_lim_ = false;
	bool is_cam_down_lim_ = false;
	bool is_velocity_update_ = true;
	bool pid_new_state_ = false;

	float screen_bondary_left_ = 0.f;
	float screen_bondary_right_ = 0.f;
	float screen_bondary_top_ = 0.f;
	float screen_bondary_bottom_ = 0.f;

	float camera_bondary_left_ = 0.f;
	float camera_bondary_right_ = 0.f;
	float camera_bondary_top_ = 0.f;
	float camera_bondary_bottom_ = 0.f;


	PID cam_pid_controller_ = PID(0.01f, 100.f, 100.f, 0.001f, 0.f, 0.f);
	Eigen::Vector2f camera_pos_setpoint_;
	Eigen::Vector2f cam_velocity_pid_warper_(Eigen::Vector2f error);
	float cam_acc_lim = 0.1;

	inline float relu(float input)
	{
		return input > 0 ? input : 0;
	}
	/// <summary>
	/// return the z depth of the scenery based on its name
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	float parse_scenery_z_deepth(std::string name);
	void update_camera_velocity();
	void update_player_velocity();
	void update_scenery_velocity();
	void update_camera_lock_velocity();
	void update_player_stats();
	void update_current_camera_lock_zone();
	void process_camera_lock();

	Eigen::Vector2f velocity_conversion_function(float z, Eigen::Vector2f velocity);

	Eigen::Vector4f get_rectangle_region(CSprite* sp);

public:
	/// <summary>
	/// Parameter less constructor for LibParallexScroll
	/// </summary>
	LibParallexScroll();

	/// <summary>
	/// Constructor for lib parallax scroll
	/// </summary>
	/// <param name="player"></param> program interface of player, which camera follows
	/// what? you want muiltiplayer??? place second player in npc section
	/// <param name="npc"></param> array of program interface of NPCs
	/// <param name="scenery"></param> array of program interface of environment objects
	/// program interface of scenery should start with 'Lxx_', where xx is the z depth of the object
	LibParallexScroll(std::vector<std::string> player, std::vector<std::string> npc, std::vector<std::string> scenery);	// Constructor

	void set_player_linear_velocity(float v_x, float v_y);
	void set_target_framing(float x, float y);
	void set_cam_lim_left(bool is_lim);
	void set_cam_lim_right(bool is_lim);
	void set_cam_lim_up(bool is_lim);
	void set_cam_lim_down(bool is_lim);
	void set_screen_bondary(float left, float right, float top, float bottom);

	Eigen::Vector2f get_current_actual_framing();

	void add_player(std::vector<std::string> player);
	void add_npc(std::vector<std::string> npc);
	void add_scenery(std::vector<std::string> scenery);
	void add_camera_lock(std::vector<std::string> camera_lock);

	/// <summary>
	/// please don't use this shit, it will break things
	/// </summary>
	void force_target_framing();

	void main_loop(float dt);
};

