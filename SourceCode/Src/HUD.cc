#include "HUD.h"
#include <format>
#include <ctime>

using namespace std;

void HUD::process_mask_flash()
{
	long current_time = std::time(0);
	if (current_time - last_mask_flash_time_ >= mask_flash_interval_)
	{
		last_mask_flash_time_ = current_time;
		for (auto& item : hp_masks_)
		{
			if (item->is_full)
			{
				item->hp_mask->AnimateSpritePlayAnimation("hp_mask_flashAnimation", false);
			}
		}
	}
}

void HUD::process_soul_level()
{
	if (last_soul_level_animation_ == soul_level_)
	{
		return;
	}

	switch (soul_level_)
	{
	case 10:
		soul_orb_->SetSpriteVisible(true);
		soul_orb_->AnimateSpritePlayAnimation("soul_orb_glowAnimation", false);
		break;
	case 9:
	case 8:
		soul_orb_->SetSpriteVisible(true);
		soul_orb_->AnimateSpritePlayAnimation("soul_orb_fill_80Animation", false);
		break;
	case 7:
		soul_orb_->SetSpriteVisible(true);
		soul_orb_->AnimateSpritePlayAnimation("soul_orb_fill_70Animation", false);
		break;
	case 6:
		soul_orb_->SetSpriteVisible(true);
		soul_orb_->AnimateSpritePlayAnimation("soul_orb_fill_60Animation", false);
		break;
	case 5:
		soul_orb_->SetSpriteVisible(true);
		soul_orb_->AnimateSpritePlayAnimation("soul_orb_fill_50Animation", false);
		break;
	case 4:
		soul_orb_->SetSpriteVisible(true);
		soul_orb_->AnimateSpritePlayAnimation("soul_orb_fill_40Animation", false);
		break;
	case 3:
		soul_orb_->SetSpriteVisible(true);
		soul_orb_->AnimateSpritePlayAnimation("soul_orb_fill_30Animation", false);
		break;
	case 2:
	case 1:
		soul_orb_->SetSpriteVisible(true);
		soul_orb_->AnimateSpritePlayAnimation("soul_orb_fill_20Animation", false);
		break;
	case 0:
		soul_orb_->SetSpriteVisible(false);
	default:
		break;
	}

	if (soul_level_ <= 3)
	{
		soul_orb_->SetSpriteColorAlpha(100);
	}
	else
	{
		soul_orb_->SetSpriteColorAlpha(255);
	}

	last_soul_level_animation_ = soul_level_;
}

HUD::HUD(std::string hp_mask_template_name, std::string soul_orb_name)
{
	auto hp_mask_template = new HpMask();
	hp_mask_template->hp_mask = new CAnimateSprite(hp_mask_template_name.c_str());
	hp_masks_.push_back(hp_mask_template);

	hp_mask_template_name_ = hp_mask_template_name;

	soul_orb_ = new CAnimateSprite(soul_orb_name.c_str());
}

void HUD::apend_a_mask()
{
	auto item = new HpMask();
	item->hp_mask = new CAnimateSprite(("hp_mask_" + to_string(hp_masks_.size())).c_str(), hp_mask_template_name_.c_str());
	auto x = hp_masks_.back()->hp_mask->GetSpritePositionX();
	item->hp_mask->SetSpritePositionX(x + mask_distance_);
	hp_masks_.push_back(item);
}

void HUD::set_mask_distance_(float distance)
{
	mask_distance_ = distance;
}

void HUD::break_a_mask()
{
	for (size_t i = hp_masks_.size() - 1; i >= 0; i--)
	{
		auto item = hp_masks_.at(i);
		if (item->is_full)
		{
			item->hp_mask->AnimateSpritePlayAnimation("hp_mask_breakAnimation", false);
			item->is_full = false;
			return;
		}
	}
}

void HUD::set_soul_level(int level)
{
	soul_level_ = level;
}

void HUD::main_loop()
{
	process_mask_flash();
	process_soul_level();
}

void HUD::heal_a_mask()
{
	for ( auto& item : hp_masks_)
	{
		if (!item->is_full)
		{
			item->hp_mask->AnimateSpritePlayAnimation("hp_mask_healAnimation", false);
			item->is_full = true;
			return;
		}
	}
}

