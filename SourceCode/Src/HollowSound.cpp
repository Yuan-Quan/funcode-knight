#include "HollowSound.h"
#include <random>

HollowSound::HollowSound()
{
	menu_bgm = new CSound("main_menu.wav", true, 0.8);
	kings_path_bgm = new CSound("kings_path.wav", true, 0.8);
	dirtmouth_bgm = new CSound("dirtmouth.wav", true, 0.8);
	crossroad_bgm = new CSound("crossroad.wav", true, 0.8);

	sword_1 = new CSound("sword_1.wav", false, 1);
	sword_2 = new CSound("sword_2.wav", false, 1);
	sword_3 = new CSound("sword_3.wav", false, 1);
	sword_4 = new CSound("sword_4.wav", false, 1);
	sword_5 = new CSound("sword_5.wav", false, 1);
	
	fireball = new CSound("hero_fireball.wav", false, 1);
	jump = new CSound("hero_jump.wav", false, 0.65);
	hurt = new CSound("hero_damage.wav", false, 1);
	dash = new CSound("hero_dash.wav", false, 1);
	land_soft = new CSound("hero_land_soft.wav", false, 0.75);
	land_hard = new CSound("hero_land_hard.wav", false, 1);
	run = new CSound("hero_run_footsteps_stone", true, 0.7);
}

void HollowSound::play_menu_bgm()
{
	menu_bgm->PlaySound();
}

void HollowSound::stop_menu_bgm()
{
	menu_bgm->StopSound();
}

void HollowSound::play_kings_path_bgm()
{
	kings_path_bgm->PlaySound();
}

void HollowSound::play_dirtmouth_bgm()
{
	dirtmouth_bgm->PlaySound();
}

void HollowSound::play_corssroad_bgm()
{
	crossroad_bgm->PlaySound();
}

void HollowSound::play_sword_swing()
{
	// generate random int 0 to 4
   std::random_device rd; // obtain a random number from hardware
   std::mt19937 gen(rd()); // seed the generator
   std::uniform_int_distribution<> distr(0, 4); // define the range

   int rand = distr(gen);

   switch (rand)
   {
   case 0:
	   sword_1->PlaySound();
	   break;
   case 1:
	   sword_2->PlaySound();
	   break;
   case 2:
	   sword_3->PlaySound();
	   break;
   case 3:
	   sword_4->PlaySound();
	   break;
   case 4:
	   sword_5->PlaySound();
	   break;
   }
}

void HollowSound::play_fire_ball()
{
	fireball->PlaySound();
}

void HollowSound::play_jump()
{
	jump->PlaySound();
}

void HollowSound::play_hurt()
{
	hurt->PlaySound();
}

void HollowSound::play_land_soft()
{
	land_soft->PlaySound();
}

void HollowSound::play_land_hard()
{
	land_hard->PlaySound();
}

void HollowSound::play_dash()
{
	dash->PlaySound();
}

void HollowSound::play_run()
{
	run->PlaySound();
}

void HollowSound::stop_run()
{
	run->StopSound();
}

void HollowSound::stop_all()
{
	CSound::StopAllSound();
}
