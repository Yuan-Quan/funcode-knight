#include "Kontrol.h"
using namespace hk_config;

void Kontrol::update_jump_stat(float dt)
{
	if (is_jumping_)
	{
		jump_time_ += dt;
	}
	if (jump_time_ >= 0.35)
	{
		unset_jump();
	}

}

void Kontrol::update_dash_stat(float dt)
{
	if (is_dashing_)
	{
		dash_time_ += dt;
	}
	if (dash_time_ >= 0.25)
	{
		unset_dash();
	}
}

void Kontrol::update_heal_stat(float dt)
{
	if (is_healing)
	{
		if (core_logic_instance_->get_soul_level() <= 1)
		{
			unset_heal();
			return;
		}
		heal_timer_ += dt;
		soul_drain_timer_ += dt;
		if (heal_timer_ >= 1.f)
		{
			core_logic_instance_->heal_a_mask();
			heal_timer_ = 0.f;
		}
		if (soul_drain_timer_ >= 0.33f)
		{
			core_logic_instance_->drain_1_soul();
			soul_drain_timer_ = 0.f;
		}
	}

}

void Kontrol::update_cool_down(float dt)
{
	if (is_dash_cd_)
	{
		dash_cd_time += dt;
		if (dash_cd_time >= 0.5)
		{
			dash_cd_time = 0;
			is_dash_cd_ = false;
		}
	}
	
	if (is_attack_cd_)
	{
		attack_cd_time += dt;
		if (attack_cd_time >= 0.4)
		{
			attack_cd_time = 0.f;
			is_attack_cd_ = false;
		}
	}
}

void Kontrol::update_land(float dt)
{
	if (waiting_land)
	{
		land_timer += dt;
		if (is_grounded_nh_())
		{
			if (land_timer >= 2.f)
			{
				hollow_sound.play_land_hard();
				waiting_land = false;
				land_timer = 0.f;
			}
			else if (land_timer >= 0.6)
			{
				hollow_sound.play_land_soft();
				waiting_land = false;
				land_timer = 0.f;
			}
		}
	}
}

void Kontrol::update_runing()
{
	bool current_running = (is_running_l || is_running_r) && is_grounded_nh_();
	if (current_running!=last_running_status)
	{
		last_running_status = current_running;
		if (current_running)
		{
			hollow_sound.play_run();
		}
		else
		{
			hollow_sound.stop_run();
		}
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
	if (is_dashing_)
	{
		const_vel_ = const_vel_dash_;
	}
	else
	{
		const_vel_ = const_vel_left_ + const_vel_right_;
	}
	const_force_ = const_force_jump;

	tmp_vel_ += tmp_vel_jump;
	tmp_vel_jump << 0, 0;
}

void Kontrol::on_jump_key_press()
{
	if (jump_refresh>0)
	{
		if (!is_grounded_nh_())
		{
			unset_jump();
		}
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

void Kontrol::on_dash_key_press()
{
	if (!is_dash_cd_)
	{
		set_dash();
	}
}

void Kontrol::set_left()
{
	is_running_l = true;
	const_vel_left_ << -40, 0;
	heading_left_ = true;
}

void Kontrol::unset_left()
{
	is_running_l = false;
	const_vel_left_ << 0, 0;
}

void Kontrol::set_right()
{
	is_running_r = true;
	const_vel_right_ << 40, 0;
	heading_left_ = false;
}

void Kontrol::unset_right()
{
	is_running_r = false;
	const_vel_right_ << 0, 0;
}

void Kontrol::set_jump()
{
	hollow_sound.play_jump();
	tmp_vel_jump << 0, -60;
	const_force_jump << 0, -450;

	jump_refresh--;
	is_jumping_ = true;
	waiting_land = true;
}

void Kontrol::unset_jump()
{
	tmp_vel_jump << 0, 0;
	const_force_jump << 0, 0;
	is_jumping_ = false;

	jump_time_ = 0.f;
}

void Kontrol::set_dash()
{
	if (dash_refresh)
	{
		hollow_sound.play_dash();
		is_dashing_ = true;
		is_dash_cd_ = true;
		dash_refresh = false;
		if (dash_down)
		{
			const_vel_dash_ << 0, 140;
		}
		else
		{
			unset_jump();
			jump_refresh -= 2;
			const_force_jump << 0, -298;
			if (heading_left_)
			{
				const_vel_dash_ << -140, 0;
			}
			else
			{
				const_vel_dash_ << 140, 0;
			}
		}
	}
	
}


void Kontrol::unset_dash()
{
	is_dashing_ = false;
	const_vel_dash_ << 0, 0;
	unset_jump();
	jump_refresh += 2;

	dash_time_ = 0.f;
}

void Kontrol::set_heal()
{
	is_healing = true;
}

void Kontrol::unset_heal()
{
	if (is_healing)
	{
		is_healing = false;
	}
}

void Kontrol::attack()
{
	if (!is_attack_cd_)
	{
		hollow_sound.play_sword_swing();
		int atk_dir = AtkDirection::SIDE;
		if (is_up_atk_override)
		{
			atk_dir = AtkDirection::UP;
		}
		if (is_down_atk_override)
		{
			atk_dir = AtkDirection::DOWN;
		}
		bool response = core_logic_instance_->attack_callback(atk_dir);
		is_attack_cd_ = true;

		if (is_down_atk_override && response)
		{
			tmp_vel_jump << 0, -160;
			land_timer = 0.f;
		}
	}
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
	case KeyBinds::KEY_DOWN:
		is_down_atk_override = true;
		dash_down = true;
		break;
	case KeyBinds::KEY_UP:
		is_up_atk_override = true;
		break;
	case KeyBinds::KEY_JUMP:
		on_jump_key_press();
		break;
	case KeyBinds::KEY_DASH:
		on_dash_key_press();
		break;
	case KeyBinds::KEY_FOCUS:
		set_heal();
		break;
	case KeyBinds::KEY_ATTACK:
		attack();
		break;
	case KeyBinds::KEY_QUCIK_CAST:
		hollow_sound.play_fire_ball();
		core_logic_instance_->drain_1_soul();
		core_logic_instance_->drain_1_soul();
		core_logic_instance_->drain_1_soul();
		core_logic_instance_->shock();
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
	case KeyBinds::KEY_UP:
		is_up_atk_override = false;
		break;
	case KeyBinds::KEY_DOWN:
		is_down_atk_override = false;
		dash_down = false;
		break;
	case KeyBinds::KEY_JUMP:
		on_jump_key_release();
		break;
	case KeyBinds::KEY_DASH:
		break;
	case KeyBinds::KEY_FOCUS:
		unset_heal();
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

void Kontrol::set_logic_instance(CoreLogic* cl)
{
	core_logic_instance_ = cl;
}

void Kontrol::main_loop(float dt)
{
	update_jump_stat(dt);
	update_dash_stat(dt);
	update_cool_down(dt);
	update_heal_stat(dt);
	update_land(dt);
	update_runing();
	summing();
	update_velocity();
	refresh();
}

void Kontrol::refresh()
{
	if (is_grounded_nh_())
	{
		jump_refresh = 1;
		dash_refresh = true;
	}
}

