#pragma once

#include "SoundDevice.h"
#include "SoundEffectsPlayer.h"
#include "SoundEffectsLibrary.h"

namespace hk_sound {
SoundDevice* sd = LISTENER->Get();
int MenuBGM = SE_LOAD("./game/data/audio/main_menu.wav");
//int MenuBGM = SE_LOAD("C:\\Users\\metro\\source\\repos\\kings_physics\\Bin\\game\\data\\audio\\main_menu.wav");
SoundEffectsPlayer menu_bgm_sfx_;
ALint attunation = AL_INVERSE_DISTANCE_CLAMPED;

int current_scene_ = 0;
int last_scene_ = -1;

void init()
{
	sd->SetAttunation(attunation);
	sd->SetLocation(0.f, 0.f, 0.f);
	sd->SetOrientation(0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
	menu_bgm_sfx_.SetLooping(true);
	menu_bgm_sfx_.SetPosition(0, 0, 0);
	menu_bgm_sfx_.Play(hk_sound::MenuBGM);
}
inline void set_scene(int scene)
{
	current_scene_ = scene;
}

inline void main_loop(float dt)
{
	if (current_scene_ != last_scene_)
	{
		switch (current_scene_)
		{
		case 0:
			break;
		case 1:
			break;
		default:
			break;
		}
		last_scene_ = current_scene_;
	}
}

}
