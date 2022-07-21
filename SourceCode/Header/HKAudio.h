#pragma once
#include "SoundDevice.h"
#include "SoundEffectsPlayer.h"
#include "SoundEffectsLibrary.h"

namespace HKaudio {
SoundDevice* sd = LISTENER->Get();
int SciFiSound = SE_LOAD("game\\data\\audio\\test.wav");
int MenuSound = SE_LOAD("game\\data\\audio\\main_menu.wav");
SoundEffectsPlayer sound_effects_player_forSciFiSound;
SoundEffectsPlayer sound_effects_player_forMainMenu;

void init()
{
	ALint attunation = AL_INVERSE_DISTANCE_CLAMPED;
	sd->SetAttunation(attunation);
	sd->SetLocation(0.f, 0.f, 0.f);
	sd->SetOrientation(0.f, 1.f, 0.f, 0.f, 0.f, 1.f);

	sound_effects_player_forSciFiSound.SetLooping(true);
	sound_effects_player_forSciFiSound.SetPosition(0, 0, 0);
	sound_effects_player_forSciFiSound.Play(SciFiSound);
}

void play_menu()
{
	ALint attunation = AL_INVERSE_DISTANCE_CLAMPED;
	sd->SetAttunation(attunation);
	sd->SetLocation(0.f, 0.f, 0.f);
	sd->SetOrientation(0.f, 1.f, 0.f, 0.f, 0.f, 1.f);

	sound_effects_player_forMainMenu.SetLooping(true);
	sound_effects_player_forMainMenu.SetPosition(0, 0, 0);
	sound_effects_player_forMainMenu.Play(MenuSound);
}
}  // end namespace TTD
