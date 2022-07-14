#include "LibParallexScroll.h"
#include <iostream>
#include "pid.h"
using namespace std;

Eigen::Vector2f LibParallexScroll::velocity_conversion_function(float z, Eigen::Vector2f velocity)
{
	return exp(0.4 * ( - z + 15)) * velocity;
}

void LibParallexScroll::update_camera_lock_velocity()
{
	for (auto& item : camera_locks_)
	{
		auto temp_vel = velocity_conversion_function(15.0, -camera2map_velocity_);
		item->SetSpriteLinearVelocity(temp_vel.x(), temp_vel.y());
	}
}

void LibParallexScroll::update_current_camera_lock_zone()
{
	std::vector<float> camera_lock_x;
	std::vector<float> camera_lock_y;
	camera_lock_x.clear();
	camera_lock_y.clear();
	for (auto& item :camera_locks_)
	{
		auto region = get_rectangle_region(item);
		if (region(0) <= 0.f && region(1) >= 0.f && region(2) <= 0.f && region(3) >= 0.f)
		{
			camera_lock_x.push_back(region(0));
			camera_lock_x.push_back(region(1));
			camera_lock_y.push_back(region(2));
			camera_lock_y.push_back(region(3));
		}
	}

	if (camera_lock_x.size() != 0)
	{
		camera_bondary_left_ = *std::min_element(camera_lock_x.begin(), camera_lock_x.end());
		camera_bondary_right_ = *std::max_element(camera_lock_x.begin(), camera_lock_x.end());
	}
	else
	{
		camera_bondary_left_ = screen_bondary_left_ - 1;
		camera_bondary_right_ = screen_bondary_right_ + 1;
	}

	if (camera_lock_y.size() != 0)
	{
		camera_bondary_top_ = *std::min_element(camera_lock_y.begin(), camera_lock_y.end());
		camera_bondary_bottom_ = *std::max_element(camera_lock_y.begin(), camera_lock_y.end());
	}
	else
	{
		camera_bondary_top_ = screen_bondary_top_ - 1;
		camera_bondary_bottom_ = screen_bondary_bottom_ + 1;
	}
}

Eigen::Vector4f LibParallexScroll::get_rectangle_region(CSprite* sp)
{
	Eigen::Vector4f result;
	float center_x = sp->GetSpritePositionX();
	float center_y = sp->GetSpritePositionY();
	float width = sp->GetSpriteWidth();
	float height = sp->GetSpriteHeight();
	result << center_x - (0.5 * width), center_x + (0.5 * width), center_y - (0.5 * height), center_y + (0.5 * height);
	return result;
}

void LibParallexScroll::process_camera_lock()
{
	if (camera_bondary_left_ < screen_bondary_left_)
	{
		// then you're good
		is_cam_left_lim_ = false;
		cam_vel_temp_offset_ = Eigen::Vector2f(0.f, 0.f);
	}
	else
	{
		is_cam_left_lim_ = true;
		// there is some spaghetti code here
		// someone please come and fix it
		if (camera_bondary_left_ - screen_bondary_left_ >= 5)
		{
			cam_vel_temp_offset_ = Eigen::Vector2f(18, 0);
			return;
		}
		cam_vel_temp_offset_ = Eigen::Vector2f(0.f, 0.f);
	}

	if (camera_bondary_right_ > screen_bondary_right_)
	{
		// then you're good
		is_cam_right_lim_ = false;
		cam_vel_temp_offset_ = Eigen::Vector2f(0.f, 0.f);
	}
	else
	{
		is_cam_right_lim_ = true;
		if (screen_bondary_right_ - camera_bondary_right_ >= 5)
		{
			cam_vel_temp_offset_ = Eigen::Vector2f(-18, 0);
			return;
		}
		cam_vel_temp_offset_ = Eigen::Vector2f(0.f, 0.f);
	}

	if (camera_bondary_bottom_ > screen_bondary_bottom_)
	{
		// then you're good
		is_cam_up_lim_ = false;
		cam_vel_temp_offset_ = Eigen::Vector2f(0.f, 0.f);
	}
	else
	{
		is_cam_up_lim_ = true;
		// there is some spaghetti code here
		// someone please come and fix it
		if (screen_bondary_bottom_ - camera_bondary_bottom_ >= 5)
		{
			cam_vel_temp_offset_ = Eigen::Vector2f(0, -18);
			return;
		}
		cam_vel_temp_offset_ = Eigen::Vector2f(0.f, 0.f);
	}

	if (screen_bondary_top_ > camera_bondary_top_)
	{
		// then you're good
		is_cam_down_lim_ = false;
		cam_vel_temp_offset_ = Eigen::Vector2f(0.f, 0.f);
	}
	else
	{
		is_cam_down_lim_ = true;
		// there is some spaghetti code here
		// someone please come and fix it
		if (camera_bondary_top_ - screen_bondary_top_ >= 5)
		{
			cam_vel_temp_offset_ = Eigen::Vector2f(-18, 0);
			return;
		}
		cam_vel_temp_offset_ = Eigen::Vector2f(0.f, 0.f);
	}
}

LibParallexScroll::LibParallexScroll()
{
	player2map_velocity_ = Eigen::Vector2f(0, 0);
	camera2map_velocity_ = Eigen::Vector2f(0, 0);
	camera_pos_setpoint_ << 0.f, 0.f;
	player2cam_target_ << 0.f, 0.f;

}

LibParallexScroll::LibParallexScroll(std::vector<std::string> player, std::vector<std::string> npc, std::vector<std::string> scenery)
{
	for (auto& i_player : player)
	{
		player_.push_back(new CSprite(i_player.c_str()));
	}
	for (auto &i_npc : npc)
	{
		npc_.push_back(new CSprite(i_npc.c_str()));
	}
	for (auto& i_scenery : scenery)
	{
		LibParallexScroll::SceneryObj* item = new LibParallexScroll::SceneryObj();
		item->scenery = new CSprite(i_scenery.c_str());
		item->z = parse_scenery_z_deepth(i_scenery);
		scenery_.push_back(item);
	}

	player2map_velocity_ = Eigen::Vector2f(0, 0);
	camera2map_velocity_ = Eigen::Vector2f(0, 0);

	camera_pos_setpoint_ << 0.f, 0.f;
	player2cam_target_ << 0.f, 0.f;
}

void LibParallexScroll::main_loop(float dt)
{
	update_player_stats();
	update_current_camera_lock_zone();
	process_camera_lock();
	update_camera_velocity();
	update_scenery_velocity();
	update_camera_lock_velocity();
	update_player_velocity();
}

void LibParallexScroll::add_player(std::vector<std::string> player)
{
	for (auto& i_player : player)
	{
		player_.push_back(new CSprite(i_player.c_str()));
	}
}

void LibParallexScroll::add_npc(std::vector<std::string> npc)
{
	for (auto &i_npc : npc)
	{
		npc_.push_back(new CSprite(i_npc.c_str()));
	}
}

void LibParallexScroll::add_camera_lock(std::vector<std::string> camera_lock)
{
	for (auto& item : camera_lock)
	{
		camera_locks_.push_back(new CSprite(item.c_str()));
	}
}

Eigen::Vector2f LibParallexScroll::get_current_actual_framing()
{
	return Eigen::Vector2f(player_.at(0)->GetSpritePositionX(), player_.at(0)->GetSpritePositionY());
}

void LibParallexScroll::add_scenery(std::vector<std::string> scenery)
{
	for (auto& i_scenery : scenery)
	{
		LibParallexScroll::SceneryObj* item = new LibParallexScroll::SceneryObj();
		item->scenery = new CSprite(i_scenery.c_str());
		item->z = parse_scenery_z_deepth(i_scenery);
		scenery_.push_back(item);
	}
}

void LibParallexScroll::force_target_framing()
{
	Eigen::Vector2f player2target = player2cam_target_ - player_position_;
	for (auto& item : player_)
	{
		Eigen::Vector2f cur_pos;
		cur_pos << item->GetSpritePositionX(), item->GetSpritePositionY();
		auto tar_pos = cur_pos + player2target;
		item->SetSpritePosition(tar_pos.x(), tar_pos.y());
	}
	for (auto& item : npc_)
	{
		Eigen::Vector2f cur_pos;
		cur_pos << item->GetSpritePositionX() , item->GetSpritePositionY();
		auto tar_pos = cur_pos + player2target;
		item->SetSpritePosition(tar_pos.x(), tar_pos.y());
	}
	for (auto& item: scenery_)
	{
		Eigen::Vector2f cur_pos;
		cur_pos << item->scenery->GetSpritePositionX(), item->scenery->GetSpritePositionY();
		auto tar_pos = cur_pos + velocity_conversion_function(item->z, player2target);
		item->scenery->SetSpritePosition(tar_pos.x(), tar_pos.y());
	}
	for (auto& item : camera_locks_)
	{
		Eigen::Vector2f cur_pos;
		cur_pos << item->GetSpritePositionX(), item->GetSpritePositionY();
		auto tar_pos = cur_pos + velocity_conversion_function(15.0, player2target);
		item->SetSpritePosition(tar_pos.x(), tar_pos.y());
	}
}

void LibParallexScroll::set_screen_bondary(float left, float right, float top, float bottom)
{
	screen_bondary_left_ = left;
	screen_bondary_right_ = right;
	screen_bondary_top_ = top;
	screen_bondary_bottom_ = bottom;
}

void LibParallexScroll::set_target_framing(float x, float y)
{
	player2cam_target_ << x, y;
}

void LibParallexScroll::set_cam_lim_left(bool is_lim)
{
	is_cam_left_lim_ = is_lim;
}

void LibParallexScroll::set_cam_lim_right(bool is_lim)
{
	is_cam_right_lim_ = is_lim;
}

void LibParallexScroll::set_cam_lim_up(bool is_lim)
{
	is_cam_up_lim_ = is_lim;
}

void LibParallexScroll::set_cam_lim_down(bool is_lim)
{
	is_cam_down_lim_ = is_lim;
}

Eigen::Vector2f LibParallexScroll::cam_velocity_pid_warper_(Eigen::Vector2f error)
{
	double scala_error = error.norm();
	double scala_control_effort = 5 * scala_error;
	//double scala_control_effort = cam_pid_controller_.calculate(0, scala_error);
	return scala_control_effort * error.normalized();
}

float LibParallexScroll::parse_scenery_z_deepth(std::string name)
{
	// strip right to first underscore
	size_t trim_idx = name.find('_');
	// if the first char is not L
	if (!name[0] == 'L')
	{
		cout << "error parsing scenery program interface: " << name << endl;
		return 0.f;
	}
	// if the first underscore is not found
	if (trim_idx == std::string::npos)
	{
		cout << "error parsing scenery program interface: " << name << endl;
		return 0.f;
	}
	// remove first 'L' and everyting after first underscore
	// leaving only the number
	auto trimed = name.substr(1, trim_idx - 1);
	float result = stof(trimed);
	return result;
}

void LibParallexScroll::update_camera_velocity()
{
	//camera2map_velocity_ = player2map_velocity_;
	auto error = player_position_ - (player2cam_target_ + target_framing_temporary_offset_) ;

	camera2map_velocity_ = cam_velocity_pid_warper_(error);

	// get the component of camera velocity on each axis
	Eigen::Vector2f e_left;
	e_left<< -1, 0;
	Eigen::Vector2f left_component = relu(e_left.dot(camera2map_velocity_)) * e_left;

	Eigen::Vector2f e_right;
	e_right<< 1, 0;
	Eigen::Vector2f right_component = relu(e_right.dot(camera2map_velocity_)) * e_right;

	Eigen::Vector2f e_up;
	e_up<< 0, 1;
	Eigen::Vector2f up_component = relu(e_up.dot(camera2map_velocity_)) * e_up;

	Eigen::Vector2f e_down;
	e_down<< 0, -1;
	Eigen::Vector2f down_component = relu(e_down.dot(camera2map_velocity_)) * e_down;

	Eigen::Vector2f player2target = player_position_ - player2cam_target_;

	if (is_cam_left_lim_)
	{
		camera2map_velocity_ -= left_component;
		if (player2target.dot(e_left) > 0.01) // when player is left to the target position
		{
			camera2map_velocity_ -= right_component; // also remove it's right component
		}
	}
	if (is_cam_right_lim_)
	{
		camera2map_velocity_ -= right_component;
		if (player2target.dot(e_right) > 0.01) // when player is right to the target position
		{
			camera2map_velocity_ -= left_component; // also remove it's left component
		}
	}
	if (is_cam_up_lim_)
	{
		camera2map_velocity_ -= up_component;
		if (player2target.dot(e_up) > 0.01)
		{
			camera2map_velocity_ -= down_component;
		}
	}
	if (is_cam_down_lim_)
	{
		camera2map_velocity_ -= down_component;
		if (player2target.dot(e_down) > 0.01)
		{
			camera2map_velocity_ -= up_component;
		}
	}

	camera2map_velocity_ += cam_vel_temp_offset_;
	//camera_velocity_ = player_velocity_;
}

void LibParallexScroll::update_player_velocity()
{
	player2cam_velocity_ = player2map_velocity_ - camera2map_velocity_;
	for (auto &item : player_)
	{
		item->SetSpriteLinearVelocity(player2cam_velocity_.x(), player2cam_velocity_.y());
	}
}

void LibParallexScroll::update_player_stats()
{
	player_position_ << player_.at(0)->GetSpritePositionX(), player_.at(0)->GetSpritePositionY();
}

void LibParallexScroll::update_scenery_velocity()
{
	for (auto& i_scenery : scenery_)
	{
		auto temp_vel = velocity_conversion_function(i_scenery->z, -camera2map_velocity_);
		i_scenery->scenery->SetSpriteLinearVelocity(temp_vel.x(), temp_vel.y());
	}
}

void LibParallexScroll::set_player_linear_velocity(float v_x, float v_y)
{
	player2map_velocity_ << v_x, v_y;
	is_velocity_update_ = true;
}
