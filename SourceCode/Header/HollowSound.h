#pragma once

#include <AL/al.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bit>
#include <AL/alc.h>
#include "CommonClass.h"

class HollowSound
{
public:
	HollowSound();
	void play_menu_bgm();
	void stop_menu_bgm();
	void play_kings_path_bgm();
	void stop_kings_path_bgm();
	void play_dirtmouth_bgm();
	void play_corssroad_bgm();
	void play_sword_swing();
	void play_fire_ball();
	void play_jump();
	void play_hurt();
	void play_land_soft();
	void play_land_hard();
	void play_dash();
	void play_run();
	void stop_run();
	void play_enemy_damage();
	void play_foucs();
	void stop_foucs();
	void play_heal();
	void stop_all();
private:
	CSound* menu_bgm;
	CSound* kings_path_bgm;
	CSound* dirtmouth_bgm;
	CSound* crossroad_bgm;

	CSound* sword_1;
	CSound* sword_2;
	CSound* sword_3;
	CSound* sword_4;
	CSound* sword_5;
	
	CSound* fireball;
	CSound* jump;
	CSound* hurt;
	CSound* dash;
	CSound* land_soft;
	CSound* land_hard;
	CSound* run;
	CSound* enemey_damage;
	CSound* foucs;
	CSound* heal;

};
