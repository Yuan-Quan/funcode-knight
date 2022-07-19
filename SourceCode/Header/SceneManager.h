#pragma once
#include <string>
enum Scenes
{
	KINGS_PATH = 0,
	DIRT_MOUTH = 1,
	CROSS_RODE = 2,
	CROSS_RODE_LEFT = 3,
	CROSS_RODE_RIGHT = 4,
};
class SceneManager
{
public:
	void on_sp_col_callback(std::string src_name, std::string tar_name);
	void update_scene();
	void load_scene(int scene_id);
private:
	int current_scene = 0;
	int lats_scene = 0;
	void load_dirtmouth();
};

