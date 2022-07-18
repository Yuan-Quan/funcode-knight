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

void CoreLogic::attack_callback(int atk_dir)
{
	for (auto& enemy : enemies_)
	{
		if (is_in_atk_range(enemy->sp, atk_dir))
		{
			enemy->hp--;
			// knock back it
		}
	}
}

void CoreLogic::die()
{
	is_alive = false;
}

bool CoreLogic::is_in_atk_range(CSprite* sp, int atk_dir)
{

	auto atk_sp = atk_hit_boxs_.at(atk_dir);
	auto atk_box = new Box();
	atk_box->height = atk_sp->GetSpriteHeight();
	atk_box->width = atk_sp->GetSpriteWidth();
	atk_box->position << atk_sp->GetSpritePositionX(), atk_sp->GetSpritePositionY();

	auto sp_box = new Box();
	sp_box->height = sp->GetSpriteHeight();
	sp_box->width = sp->GetSpriteWidth();
	sp_box->position << sp->GetSpritePositionX(), sp->GetSpritePositionY();

	return is_col(atk_box, sp_box);
}

bool CoreLogic::is_col(Box* a, Box* b)
{
	float rect1x = a->position.x() - a->width / 2;
	float rect1y = a->position.y() - a->height / 2;
	float rect1w = a->width;
	float rect1h = a->height;

	float rect2x = b->position.x() - b->width / 2;
	float rect2y = b->position.y() - b->height / 2;
	float rect2w = b->width;
	float rect2h = b->height;

	return (rect1x < rect2x + rect2w &&
		rect1x + rect1w > rect2x &&
		rect1y < rect2y + rect2h &&
		rect1h + rect1y > rect2y);
}

void CoreLogic::set_atk_box(std::string up, std::string down, std::string side)
{
	atk_hit_boxs_.push_back(new CSprite(up.c_str()));
	atk_hit_boxs_.push_back(new CSprite(down.c_str()));
	atk_hit_boxs_.push_back(new CSprite(side.c_str()));
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

void CoreLogic::update_enemy_status()
{
	for (auto& item : enemies_)
	{
		if (item->hp <= 0)
		{
			item->sp->SetSpriteColorAlpha(100);
		}
	}
}

void CoreLogic::main_loop(float dt)
{
	update_immortal_state(dt);
	update_enemy_status();
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
