#include "Kontrol.h"
using namespace hk_config;

void Kontrol::update_jump_stat(float dt)
{
	if (is_jumping_)
	{
		jump_time += dt;
	}
	if (jump_time >= 0.35)
	{
		unset_jump();
	}

}

void Kontrol::update_velocity()
{
	tmp_vel_nh_(player_name_, tmp_vel_.x(), tmp_vel_.y());
	const_vel_nh_(player_name_, const_vel_.x(), const_vel_.y());
	tmp_force_nh_(player_name_, tmp_force_.x(), tmp_force_.y());
	const_force_nh_(player_name_, const_force_.x(), const_force_.y());
	tmp_vel_ << 0, 0;
	tmp_force_ << 0, 0;
}

void Kontrol::summing()
{
	const_vel_ = const_vel_left_ + const_vel_right_;
	const_force_ = const_force_jump;

	tmp_vel_ += tmp_vel_jump;
	tmp_vel_jump << 0, 0;
}

void Kontrol::on_jump_key_press()
{
	if (is_grounded_nh_())
	{
		set_jump();
	}

}

void Kontrol::on_jump_key_release()
{
	if (is_jumping_)
	{
		unset_jump();
	}
}

void Kontrol::set_left()
{
	const_vel_left_ << -40, 0;
}

void Kontrol::unset_left()
{
	const_vel_left_ << 0, 0;
}

void Kontrol::set_right()
{
	const_vel_right_ << 40, 0;
}

void Kontrol::unset_right()
{
	const_vel_right_ << 0, 0;
}

void Kontrol::set_jump()
{
	tmp_vel_jump << 0, -60;
	const_force_jump << 0, -450;

	is_jumping_ = true;
}

void Kontrol::unset_jump()
{
	const_force_jump << 0, 0;
	is_jumping_ = false;

	jump_time = 0.f;
}

Kontrol::Kontrol(std::string name)
{
	player_name_ = name;
}

void Kontrol::key_press_callback(int key)
{
	switch (key)
	{
	case KeyBinds::KEY_LEFT:
		set_left();
		break;
	case KeyBinds::KEY_RIGHT:
		set_right();
		break;
	case KeyBinds::KEY_JUMP:
		on_jump_key_press();
		break;
	default:
		break;
	}
}

void Kontrol::key_relese_callback(int key)
{
	switch (key)
	{
	case KeyBinds::KEY_LEFT:
		unset_left();
		break;
	case KeyBinds::KEY_RIGHT:
		unset_right();
		break;
	case KeyBinds::KEY_JUMP:
		on_jump_key_release();
		break;
	default:
		break;
	}
}

void Kontrol::set_physics_engine_handler(std::function<void(std::string, float, float)> tmp_vel, std::function<void(std::string, float, float)> const_vel, std::function<void(std::string, float, float)> tmp_force, std::function<void(std::string, float, float)> const_force)
{
	tmp_vel_nh_ = tmp_vel;
	const_vel_nh_ = const_vel;
	tmp_force_nh_ = tmp_force;
	const_force_nh_ = const_force;
}

void Kontrol::set_gound_state_handler(std::function<bool()> is_grounded)
{
	is_grounded_nh_ = is_grounded;
}

void Kontrol::main_loop(float dt)
{
	update_jump_stat(dt);
	summing();
	update_velocity();
}

