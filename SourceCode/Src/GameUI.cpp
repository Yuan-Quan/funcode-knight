#include "GameUI.h"

GameUI::GameUI()
{
	pause_resume = new CSprite("pause_resume");
	pause_quit = new CSprite("pause_quit");
	pause_option = new CSprite("pause_option");
}

bool GameUI::key_press_callback(int key)
{
	if (key == hk_config::KeyBinds::KEY_PAUSE)
	{
		if (is_in_main_menu)
		{
			return false;
		}
		is_in_pause_menu = true;
		physics_instance_->freeze();
		pause_resume->SetSpriteVisible(true);
		pause_menue_option = 0;
	}

	if (is_in_pause_menu)
	{
		if (key == hk_config::KeyBinds::KEY_UP)
		{
			if (pause_menue_option > 0)
			{
				pause_menue_option--;
			}
		}

		if (key == hk_config::KeyBinds::KEY_DOWN)
		{
			if (pause_menue_option < 2)
			{
				pause_menue_option++;
			}

		}

		switch (pause_menue_option)
		{
		case 0:
			pause_quit->SetSpriteVisible(false);
			pause_option->SetSpriteVisible(false);
			pause_resume->SetSpriteVisible(true);
		case 1:
			pause_resume->SetSpriteVisible(false);
			pause_quit->SetSpriteVisible(false);
			pause_option->SetSpriteVisible(true);
		case 2:
			pause_resume->SetSpriteVisible(false);
			pause_option->SetSpriteVisible(false);
			pause_quit->SetSpriteVisible(true);
		default:
			break;
		}
	}

	if (is_in_main_menu || is_in_pause_menu)
	{
		return true;
	}
	return false;
}

void GameUI::set_physics_instance(SimplePhysics* ins)
{
	physics_instance_ = ins;
}

void GameUI::main_loop()
{
}
