#pragma once

#include <vector>
#include "CommonClass.h"
#include <string>

class HUD
{
private:

	struct HpMask
	{
		bool is_full = true; // which means its not broken
		bool is_busy = false; // reserved, no use for now
		CAnimateSprite* hp_mask;
	};
	
	CAnimateSprite* soul_orb_;
	std::vector<HpMask*> hp_masks_;
	std::vector<HpMask*> mask_to_break_;
	std::string hp_mask_template_name_;

	int mask_flash_interval_ = 5;
	int last_soul_level_animation_ = 10;
	int soul_level_ = 10;
	long last_mask_flash_time_ = 0;
	float mask_distance_ = 8;

	void process_mask_flash();
	void process_soul_level();

public:
	// parameter name should be self-explainitory enough
	HUD(std::string hp_mask_template_name, std::string soul_orb_name);
	
	void apend_a_mask();
	void set_mask_distance_(float distance); // we're not gonna to use this, just for testing
	void heal_a_mask();
	void break_a_mask();
	void set_soul_level(int level); // just give me a number between 0~10

	void main_loop(); // there is not much to do though
};

