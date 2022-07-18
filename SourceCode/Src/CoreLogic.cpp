#include "CoreLogic.h"

void CoreLogic::set_immortal_after_damage()
{
	is_immortal_ = true;
}

CoreLogic::CoreLogic(std::string player_name)
{
	player_name_ = player_name;
}

void CoreLogic::set_hud_instance(HUD* hud)
{
	hud_instance_ = hud;
}

void CoreLogic::add_enemy(std::string name, int hp)
{
	auto enemy = new NPC();
	enemy->hp = hp;
	enemy->sp = new CSprite(name.c_str());

	enemies_.push_back(enemy);
}

void CoreLogic::take_damange()
{
	if (!is_alive)
	{
		return;
	}
	player_hp_--;
	hud_instance_->break_a_mask();
	set_immortal_after_damage();
	if (player_hp_ <= 0)
	{
		die();
	}
}

void CoreLogic::heal_a_mask()
{
	hud_instance_->heal_a_mask();
	player_hp_++;
}

void CoreLogic::drain_1_soul()
{
	player_soul_ --;
}

int CoreLogic::get_soul_level()
{
	return player_soul_;
}

void CoreLogic::die()
{
	is_alive = false;
}

void CoreLogic::sp_col_callback(std::string src_name, std::string tar_name)
{
	if (is_immortal_)
	{
		return;
	}
	if (strcmp(src_name.c_str(), player_name_.c_str()) == 0)
	{
		for (auto& item : enemies_)
		{
			if (strcmp(tar_name.c_str(), item->sp->GetName()) == 0)
			{
				take_damange();
			}
		}
	}
}

void CoreLogic::update_immortal_state(float dt)
{
	immortal_timer_ += dt;
	if (immortal_timer_ >= 1.5f)
	{
		immortal_timer_ = 0.f;
		is_immortal_ = false;
	}
}

void CoreLogic::update_hud_status()
{
	hud_instance_->set_soul_level(player_soul_);
}

void CoreLogic::main_loop(float dt)
{
	update_immortal_state(dt);
	update_hud_status();
	hud_instance_->main_loop();
}

void CoreLogic::init()
{
	for (size_t i = 1; i < player_hp_; i++)
	{
		hud_instance_->apend_a_mask();
	}
}
