#include "SceneManager.h"
#include "CommonClass.h"

void SceneManager::on_sp_col_callback(std::string src_name, std::string tar_name)
{
	if (strcmp(src_name.c_str(), "knight_placeholder") == 0 &&
		strcmp(tar_name.c_str(), "to_dirtmouth") == 0)
	{
		current_scene = 1;
	}
}

void SceneManager::update_scene()
{
	if (current_scene != lats_scene)
	{
		lats_scene = current_scene;
		load_scene(current_scene);
	}
}

void SceneManager::load_scene(int scene_id)
{
	load_dirtmouth();
}

void SceneManager::load_dirtmouth()
{
	CSystem::LoadMap("dirtmouth.t2d");
}
