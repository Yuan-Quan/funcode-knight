#include "GameUI.h"

GameUI::GameUI()
{
	pause_resume = new CSprite("pause_resume");
	pause_quit = new CSprite("pause_quit");
	pause_option = new CSprite("pause_option");
	main_menu_selector = new CSprite("main_menu_selector");
	save_menu_selector = new CSprite("save_selector");
	difficulty_selector = new CSprite("difficulty_selector");

	save_black = new CSprite("save_black");
	save_dirt = new CSprite("save_dirt");
	save_kings = new CSprite("save_kings");
	save_forgotten = new CSprite("save_forgotten");

	txt_save_area = new CTextSprite("txt_save_area");
	txt_save_time = new CTextSprite("txt_save_time");
	txt_save_difficulty = new CTextSprite("txt_save_difficulty");
	
	main_menu_option = 0;
	save_menu_option = 0;
	pause_menu_option = 0;
	difficulty_option = 0;

	save = new SaveFile();
	save->scene = 2;
	save->time = 0;
}

bool GameUI::key_press_callback(int key)
{
	if (is_in_main_menu)
	{

		if (key == hk_config::KeyBinds::KEY_DOWN)
		{
			if (main_menu_option < 2)
			{
				main_menu_option++;
			}
		}

		if (key == hk_config::KeyBinds::KEY_UP)
		{	
			if (main_menu_option > 0)
			{
				main_menu_option--;
			}
		}

		switch (main_menu_option)
		{
		case 0:
			main_menu_selector->SetSpritePositionY(15.f);
			break;
		case 1:
			main_menu_selector->SetSpritePositionY(23.f);
			break;
		case 2:
			main_menu_selector->SetSpritePositionY(31.f);
		default:
			break;
		}

		if (key == hk_config::KeyBinds::KEY_ATTACK || key == hk_config::KeyBinds::KEY_JUMP || key == hk_config::KeyBinds::KEY_ENTER)
		{
			switch (main_menu_option)
			{
			case 0:
				is_in_main_menu = false;
				requested_scene_switch = 1;
				break;
			case 1:
				break;
			case 2:
				exit(0);
				break;
			default:
				break;
			}
		}
	}
	if (is_in_save_menu)
	{
		if (key == hk_config::KeyBinds::KEY_DOWN)
		{
			save_menu_option = 2;
		}
		if (key == hk_config::KeyBinds::KEY_UP)
		{
			save_menu_option = 0;
		}
		if (key == hk_config::KeyBinds::KEY_LEFT)
		{
			save_menu_option = 0;
		}
		if (key == hk_config::KeyBinds::KEY_RIGHT)
		{
			save_menu_option = 1;
		}

		switch (save_menu_option)
		{
		case 0:
			save_menu_selector->SetSpritePositionX(-44.f);
			save_menu_selector->SetSpritePositionY(1.f);
			save_menu_selector->SetSpriteVisible(true);
			break;
		case 1:
			save_menu_selector->SetSpritePositionX(57.f);
			save_menu_selector->SetSpritePositionY(-1.f);
			save_menu_selector->SetSpriteVisible(true);
			break;
		case 2:
			save_menu_selector->SetSpritePositionX(2.f);
			save_menu_selector->SetSpritePositionY(27.5);
			save_menu_selector->SetSpriteVisible(true);
			break;
		default:
			break;
		}

		switch (save->scene)
		{
		case 0:
		case 1:
			save_black->SetSpriteVisible(false);
			save_dirt->SetSpriteVisible(false);
			save_kings->SetSpriteVisible(false);
			save_forgotten->SetSpriteVisible(false);
			txt_save_area->SetTextString("NULL");
			txt_save_time->SetTextString((std::to_string(save->time) + "M").c_str());
			break;
		case 2:
			save_black->SetSpriteVisible(false);
			save_dirt->SetSpriteVisible(false);
			save_kings->SetSpriteVisible(true);
			save_forgotten->SetSpriteVisible(false);
			txt_save_area->SetTextString("KING'S PATH");
			txt_save_time->SetTextString((std::to_string(save->time) + "M").c_str());
			break;
		case 3:
			save_black->SetSpriteVisible(false);
			save_dirt->SetSpriteVisible(true);
			save_kings->SetSpriteVisible(false);
			save_forgotten->SetSpriteVisible(false);
			txt_save_area->SetTextString("DIRTMOUTH");
			txt_save_time->SetTextString((std::to_string(save->time) + "M").c_str());
			break;
		case 4:
			save_black->SetSpriteVisible(false);
			save_dirt->SetSpriteVisible(false);
			save_kings->SetSpriteVisible(false);
			save_forgotten->SetSpriteVisible(true);
			txt_save_area->SetTextString("CROSSRODE");
			txt_save_time->SetTextString((std::to_string(save->time) + "M").c_str());
			break;
		case 5:
			save_black->SetSpriteVisible(true);
			save_dirt->SetSpriteVisible(false);
			save_kings->SetSpriteVisible(false);
			save_forgotten->SetSpriteVisible(false);
			txt_save_area->SetTextString("BOSS FIGHT");
			txt_save_time->SetTextString((std::to_string(save->time) + "M").c_str());
			break;
		default:
			break;
		}

		switch (save->difficulty)
		{
		case 0:
			txt_save_difficulty->SetTextString("EASY");
			break;
		case 1:
			txt_save_difficulty->SetTextString("NORMAL");
			break;
		case 2:
			txt_save_difficulty->SetTextString("HARD");
			break;
		default:
			break;
		}

		if (key == hk_config::KeyBinds::KEY_ATTACK || key == hk_config::KeyBinds::KEY_JUMP || key == hk_config::KeyBinds::KEY_ENTER)
		{
			switch (save_menu_option)
			{
			case 0:
				is_in_save_menu = false;
				if (save->scene >= 2)
				{
					requested_scene_switch = save->scene;
				}
				else
				{
					requested_scene_switch = 2;
				}
				break;
			case 1:
				remove("save.dat");
				break;
			case 2:
				is_in_main_menu = true;
				is_in_save_menu = false;
				is_in_difficulty_menu = false;
				requested_scene_switch = 0;
				break;
			default:
				break;
			}
		}

	}
	if (is_in_difficulty_menu)
	{
		if (key == hk_config::KeyBinds::KEY_DOWN)
		{
			if (difficulty_option < 2)
			{
				difficulty_option++;
				save->difficulty = difficulty_option;
			}
		}

		if (key == hk_config::KeyBinds::KEY_UP)
		{	
			if (difficulty_option > 0)
			{
				difficulty_option--;
				save->difficulty = difficulty_option;
			}
		}

		switch (difficulty_option)
		{
		case 0:
			difficulty_selector->SetSpritePositionY(2.f);
			break;
		case 1:
			difficulty_selector->SetSpritePositionY(12.f);
			break;
		case 2:
			difficulty_selector->SetSpritePositionY(23.f);
		default:
			break;
		}

		if (key == hk_config::KeyBinds::KEY_ATTACK || key == hk_config::KeyBinds::KEY_JUMP || key == hk_config::KeyBinds::KEY_ENTER)
		{
			switch (difficulty_option)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
			}
			requested_scene_switch = 3;
			is_in_difficulty_menu = false;
		}

	}
	if (is_in_pause_menu)
	{
		if (key == hk_config::KeyBinds::KEY_UP)
		{
			if (pause_menu_option > 0)
			{
				pause_menu_option--;
			}
		}

		if (key == hk_config::KeyBinds::KEY_DOWN)
		{
			if (pause_menu_option < 2)
			{
				pause_menu_option++;
			}
		}


		switch (pause_menu_option)
		{
		case 0:
			pause_resume->SetSpriteVisible(true);
			pause_option->SetSpriteVisible(false);
			pause_quit->SetSpriteVisible(false);
			break;
		case 1:
			pause_resume->SetSpriteVisible(false);
			pause_option->SetSpriteVisible(true);
			pause_quit->SetSpriteVisible(false);
			break;
		case 2:
			pause_resume->SetSpriteVisible(false);
			pause_option->SetSpriteVisible(false);
			pause_quit->SetSpriteVisible(true);
			break;
		default:
			break;
		}

		if (key == hk_config::KeyBinds::KEY_PAUSE || key == hk_config::KeyBinds::KEY_ATTACK || key == hk_config::KeyBinds::KEY_JUMP || key == hk_config::KeyBinds::KEY_ENTER)
		{
			if (key == hk_config::KeyBinds::KEY_PAUSE)
			{
				pause_menu_option = 0;
			}

			switch (pause_menu_option)
			{
			case 0:
				is_in_pause_menu = false;
				physics_instance_->unfreeze();
				break;
			case 1:
				// TODO: implement option menu
				is_in_pause_menu = false;
				physics_instance_->unfreeze();
				break;
			case 2:
				requested_scene_switch = 0;
				break;
			}

			pause_resume->SetSpriteVisible(false);
			pause_option->SetSpriteVisible(false);
			pause_quit->SetSpriteVisible(false);
		}
	}
	
	if (key == hk_config::KeyBinds::KEY_PAUSE)
	{
		is_in_pause_menu = true;
		physics_instance_->freeze();
		pause_resume->SetSpriteVisible(true);
		pause_menu_option = 0;
	}


	if (is_in_main_menu || is_in_pause_menu || is_in_save_menu)
	{
		return true;
	}
	return false;
}

bool GameUI::key_release_callback(int key)
{	
	if (is_in_main_menu || is_in_pause_menu || is_in_save_menu)
	{
		return true;
	}

	return false;
}

void GameUI::set_physics_instance(SimplePhysics* ins)
{
	physics_instance_ = ins;
}

void GameUI::set_main_menu(bool b)
{
	is_in_main_menu = b;
}

void GameUI::set_save_menu(bool b)
{
	is_in_save_menu = b;
}

void GameUI::main_loop()
{
	if (requested_scene_switch != -1)
	{
		if(scene_switch_handler_)
		{
			scene_switch_handler_(requested_scene_switch);
		}
		requested_scene_switch = -1;
	}
}

void GameUI::set_scene_switch_handler(std::function<void(int)> fun)
{
	scene_switch_handler_ = fun;
}
