/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;	

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

void CGameMain::trigger_scene_callback(std::string src_name, std::string tar_name)
{
	if (strcmp(src_name.c_str(), "knight_placeholder") == 0 &&
		strcmp(tar_name.c_str(), "to_dirtmouth") == 0)
	{
		current_scene = Scenes::DIRT_MOUTH;
	}

	if (strcmp(src_name.c_str(), "knight_placeholder") == 0 &&
	strcmp(tar_name.c_str(), "to_crossroad") == 0)
	{
		current_scene = Scenes::CROSS_ROAD;
	}
}

void CGameMain::update_scene()
{
	if (current_scene != last_scene)
	{
		last_scene = current_scene;
		load_scene(current_scene);
	}
}

void CGameMain::init_scene()
{
	switch (current_scene)
	{
	case Scenes::MENU:
		init_main_menu();
		break;
	case Scenes::SAVE:
		init_save_menu();
		break;
	case Scenes::KINGS_PATH:
		init_kings_path();
		break;
	case Scenes::DIRT_MOUTH:
		init_dirtmouth();
		break;
	case Scenes::CROSS_ROAD:
		init_crossroad();
		break;
	default:
		break;
	}
}

void CGameMain::load_scene(int scene_id)
{
	switch (current_scene)
	{
	case Scenes::MENU:
		load_main_menu();
		break;
	case Scenes::SAVE:
		load_save_menu();
		break;
	case Scenes::KINGS_PATH:
		load_kings_path();
		break;
	case Scenes::DIRT_MOUTH:
		load_dirtmouth();
		break;
	case Scenes::CROSS_ROAD:
		load_crossroad();
		break;
	default:
		break;
	}
	SetGameState(1);
}

void CGameMain::init_main_menu()
{
	if (is_inited_main_menu)
	{
		// init every round
		game_ui.set_main_menu(true);
		CSystem::SetWindowTitle("Hollow Knight");
		return;
	}
	// init onece
	CSystem::SetWindowTitle("Hollow Knight");
	game_ui.set_scene_switch_handler(std::bind(&CGameMain::SetScene, this, std::placeholders::_1));
	is_inited_main_menu = true;
}

void CGameMain::init_save_menu()
{
	hk_save_read(*current_save, "save.dat");
	game_ui.save = current_save;
	game_ui.set_save_menu(true);
	last_save_time = time(0);
	CSystem::SetWindowTitle("Hollow Knight - Saves");
}

void CGameMain::init_kings_path()
{
	if (is_inited_kings_path)
	{
		// init every round
	knight->SpriteMountToSprite("knight_placeholder", 0.f, -0.4f);
	atk_hitbox_side->SpriteMountToSprite("knight_placeholder", -3.f, 0.f);
	atk_hitbox_up->SpriteMountToSprite("knight_placeholder", 0.f, -1.8f);
	atk_hitbox_down->SpriteMountToSprite("knight_placeholder", 0.f, 1.8f);
	core_logic.set_hud_instance(&hud);
	core_logic.set_physics_instance(&kings_physics);
	core_logic.set_parallex_instance(&kings_parallex);
	kontrol.set_logic_instance(&core_logic);
	crawler0.set_parallex_instance_(&kings_parallex);
	crawler1.set_parallex_instance_(&kings_parallex);
	crawler2.set_parallex_instance_(&kings_parallex);
	fly0.set_parallex_instance_(&kings_parallex);
	//kings_physics.init();
	//core_logic.init();
	CSystem::SetWindowTitle("Hollow Knight - King's Path");
		return;
	}
	// init onece
	kings_parallex.add_player({ "knight_placeholder" });
	kings_parallex.add_scenery({
		"L12_tutor_txt_1",
		"L12_tutor_txt_2",
		"L12_tutor_txt_3",
		"L12_tutor_txt_4",

		"L15_kings_path_P1",
		"L15_kings_path_P2",
		"L15_kings_path_P3",
		"L15_kings_path_P4",
		"L15_kings_path_P5",
		"L15_kings_path_P6",
		"L15_kings_path_P7",
		"L15_kings_path_P8",

		"map_tile_1",
		"map_tile_2",
		"map_tile_3",
		"map_tile_4",
		"map_tile_5",
		"map_tile_6",
		"map_tile_7",
		"map_tile_8",
		"map_tile_9",
		"map_tile_10",
		"map_tile_11",
		"map_tile_12",
		"map_tile_13",
		"map_tile_14",
		"map_tile_15",
		"map_tile_16",
		"map_tile_17",
		"map_tile_18",
		"map_tile_19",
		"map_tile_20",
		"map_tile_21",
		"map_tile_22",
		"map_tile_23",
		"map_tile_24",
		"map_tile_25",
		"map_tile_26",
		"map_tile_27",
		"map_tile_28",
		"map_tile_29",
		"map_tile_30",
		"map_tile_31",
		"map_tile_32",
		"map_tile_33",
		"map_tile_34",
		"map_tile_35",
		"map_tile_36",
		"map_tile_37",
		"map_tile_38",
		"map_tile_39",
		"map_tile_40",
		"map_tile_41",
		"map_tile_42",
		"map_tile_43",
		"map_tile_44",
		"map_tile_45",
		"map_tile_46",
		"map_tile_47",
		"map_tile_48",
		"map_tile_49",
		"map_tile_50",
		"map_tile_51",
		"map_tile_52",
		"map_tile_53",
		"map_tile_54",
		"map_tile_55",
		"map_tile_56",
		"map_tile_57",
		"map_tile_58",
		"map_tile_59",

		"to_dirtmouth",

		"CL0",
		"CR0",
		"CL1",
		"CR1",
		"CL2",
		"CR2",
		"AREA0",
		"Focus0",
		"Ready0",
	});
	kings_parallex.add_camera_lock({
		"cam_lck_1",
		"cam_lck_2",
		"cam_lck_3",
		"cam_lck_4",
		"cam_lck_5",
		"cam_lck_6",
		"cam_lck_7",
		"cam_lck_8",
		"cam_lck_9",
		"cam_lck_10",
		"cam_lck_11",
		"cam_lck_12",
		"cam_lck_13",
		});
	kings_parallex.add_npc({
		"potato",
		"Crawler0",
		"Crawler1",
		"Crawler2",
		"Fly0",
		});
	kings_parallex.set_screen_bondary(CSystem::GetScreenLeft(), CSystem::GetScreenRight(), CSystem::GetScreenTop(), CSystem::GetScreenBottom());
	kings_physics.set_parallex_instance(&kings_parallex);
	std::function<void(float, float)> f = std::bind(&LibParallexScroll::set_player_linear_velocity, &kings_parallex, std::placeholders::_1, std::placeholders::_2);
	kings_physics.add_entity("knight_placeholder", f);
	kings_physics.add_entity("potato");
	kings_physics.add_map_tile({
		"map_tile_1",
		"map_tile_2",
		"map_tile_3",
		"map_tile_4",
		"map_tile_5",
		"map_tile_6",
		"map_tile_7",
		"map_tile_8",
		"map_tile_9",
		"map_tile_10",
		"map_tile_11",
		"map_tile_12",
		"map_tile_13",
		"map_tile_14",
		"map_tile_15",
		"map_tile_16",
		"map_tile_17",
		"map_tile_18",
		"map_tile_19",
		"map_tile_20",
		"map_tile_21",
		"map_tile_22",
		"map_tile_23",
		"map_tile_24",
		"map_tile_25",
		"map_tile_26",
		"map_tile_27",
		"map_tile_28",
		"map_tile_29",
		"map_tile_30",
		"map_tile_31",
		"map_tile_32",
		"map_tile_33",
		"map_tile_34",
		"map_tile_35",
		"map_tile_36",
		"map_tile_37",
		"map_tile_38",
		"map_tile_39",
		"map_tile_40",
		"map_tile_41",
		"map_tile_42",
		"map_tile_43",
		"map_tile_44",
		"map_tile_45",
		"map_tile_46",
		"map_tile_47",
		"map_tile_48",
		"map_tile_49",
		"map_tile_50",
		"map_tile_51",
		"map_tile_52",
		"map_tile_53",
		"map_tile_54",
		"map_tile_55",
		"map_tile_56",
		"map_tile_57",
		"map_tile_58",
		"map_tile_59",
		});

	std::function<void(std::string, float, float)> fun_tmp_vel = std::bind(&SimplePhysics::set_vel_temp, &kings_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_const_vel = std::bind(&SimplePhysics::set_vel_offset, &kings_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_tmp_force = std::bind(&SimplePhysics::set_force_temp, &kings_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_cont_force = std::bind(&SimplePhysics::set_force_1, &kings_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<bool()> fun_ground_state = std::bind(&SimplePhysics::get_is_on_ground, &kings_physics);

	kontrol.set_physics_engine_handler(fun_tmp_vel,fun_const_vel, fun_tmp_force, fun_cont_force);
	kontrol.set_gound_state_handler(fun_ground_state);
	game_ui.set_physics_instance(&kings_physics);
	animator.set_gound_status_handler(fun_ground_state);

	knight = new CSprite("Knight");
	atk_hitbox_side = new CSprite("atk_hitbox_side");
	atk_hitbox_up = new CSprite("atk_hitbox_up");
	atk_hitbox_down = new CSprite("atk_hitbox_down");

	knight->SpriteMountToSprite("knight_placeholder", 0.f, -0.4f);
	atk_hitbox_side->SpriteMountToSprite("knight_placeholder", -3.f, 0.f);
	atk_hitbox_up->SpriteMountToSprite("knight_placeholder", 0.f, -1.8f);
	atk_hitbox_down->SpriteMountToSprite("knight_placeholder", 0.f, 1.8f);
	core_logic.set_hud_instance(&hud);
	core_logic.set_physics_instance(&kings_physics);
	core_logic.set_parallex_instance(&kings_parallex);
	core_logic.add_enemy("potato", 2);
	core_logic.add_enemy("Crawler0", 4);
	core_logic.add_enemy("Crawler1", 4);
	core_logic.add_enemy("Crawler2", 4);
	core_logic.add_enemy("Fly0", 4);
	core_logic.set_atk_box("atk_hitbox_up", "atk_hitbox_down", "atk_hitbox_side");
	kontrol.set_logic_instance(&core_logic);
	crawler0.set_parallex_instance_(&kings_parallex);
	crawler1.set_parallex_instance_(&kings_parallex);
	crawler2.set_parallex_instance_(&kings_parallex);
	fly0.set_parallex_instance_(&kings_parallex);
	crawler0.main_init(1);
	crawler1.main_init(1);
	crawler2.main_init(1);
	fly0.main_init(1);
	focus.main_init();
	ready.main_init();
	//kings_physics.init();
	core_logic.init();
	CSystem::SetWindowTitle("Hollow Knight - King's Path");
	is_inited_kings_path = true;
}

void CGameMain::init_dirtmouth()
{	
	knight = new CSprite("Knight");
	atk_hitbox_side = new CSprite("atk_hitbox_side");
	atk_hitbox_up = new CSprite("atk_hitbox_up");
	atk_hitbox_down = new CSprite("atk_hitbox_down");

	knight->SpriteMountToSprite("knight_placeholder", 0.f, -0.4f);
	atk_hitbox_side->SpriteMountToSprite("knight_placeholder", -3.f, 0.f);
	atk_hitbox_up->SpriteMountToSprite("knight_placeholder", 0.f, -1.8f);
	atk_hitbox_down->SpriteMountToSprite("knight_placeholder", 0.f, 1.8f);

	core_logic.set_hud_instance(&hud);
	core_logic.set_physics_instance(&dirt_physics);
	core_logic.set_parallex_instance(&dirt_parallex);
	kontrol.set_logic_instance(&core_logic);

	dirt_parallex.add_player({ "knight_placeholder" });
	dirt_parallex.add_scenery({
			"L12_dirtmouth_P1",
			"L12_dirtmouth_p2",
			"L13_dirtmouth_P1",
			"L13_dirtmouth_p2",
			"L14_dirtmouth_P1",
			"L14_dirtmouth_P2",
			"L15_dirtmouth_P1",
			"L15_dirtmouth_P2",
			"L15_dirtmouth_P3",
			"L15_dirtmouth_P4",
			"L16_dirtmouth_P1",
			"L16_dirtmouth_P2",
			"L17_dirtmouth_P1",
			"L17_dirtmouth_P2",
			"L18_dirtmouth_P1",
			"L18_dirtmouth_P2",
			"L19_dirtmouth_P1",
			"L19_dirtmouth_P2",
			"L20_dirtmouth_P1",

		"map_tile_1",
		"map_tile_2",
		"map_tile_3",
		"map_tile_4",
		"map_tile_5",
		"map_tile_6",
		"map_tile_7",
		"map_tile_8",
		"map_tile_9",

		"to_crossroad"

	});
	dirt_parallex.add_camera_lock({
		"camera_lock_1",
		"camera_lock_2",
		"camera_lock_3",
		"camera_lock_4",
		});
	
	dirt_parallex.set_screen_bondary(CSystem::GetScreenLeft(), CSystem::GetScreenRight(), CSystem::GetScreenTop(), CSystem::GetScreenBottom());

	dirt_parallex.set_target_framing(0.f, 10.f);
	dirt_physics.set_parallex_instance(&dirt_parallex);
	std::function<void(float, float)> f = std::bind(&LibParallexScroll::set_player_linear_velocity, &dirt_parallex, std::placeholders::_1, std::placeholders::_2);
	dirt_physics.add_entity("knight_placeholder", f);
	//dirt_physics.add_entity("potato");
	dirt_physics.add_map_tile({
		"map_tile_1",
		"map_tile_2",
		"map_tile_3",
		"map_tile_4",
		"map_tile_5",
		"map_tile_6",
		"map_tile_7",
		"map_tile_8",
		"map_tile_9",
	});

	std::function<void(std::string, float, float)> fun_tmp_vel = std::bind(&SimplePhysics::set_vel_temp, &dirt_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_const_vel = std::bind(&SimplePhysics::set_vel_offset, &dirt_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_tmp_force = std::bind(&SimplePhysics::set_force_temp, &dirt_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_cont_force = std::bind(&SimplePhysics::set_force_1, &dirt_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<bool()> fun_ground_state = std::bind(&SimplePhysics::get_is_on_ground, &dirt_physics);

	kontrol.set_physics_engine_handler(fun_tmp_vel,fun_const_vel, fun_tmp_force, fun_cont_force);
	kontrol.set_gound_state_handler(fun_ground_state);
	game_ui.set_physics_instance(&kings_physics);
	animator.set_gound_status_handler(fun_ground_state);

	core_logic.set_atk_box("atk_hitbox_up", "atk_hitbox_down", "atk_hitbox_side");
	//kings_physics.init();
	core_logic.init();

	CSystem::SetWindowTitle("Hollow Knight - Dirtmouth");
}

void CGameMain::init_crossroad()
{	
	knight = new CSprite("Knight");
	atk_hitbox_side = new CSprite("atk_hitbox_side");
	atk_hitbox_up = new CSprite("atk_hitbox_up");
	atk_hitbox_down = new CSprite("atk_hitbox_down");

	knight->SpriteMountToSprite("knight_placeholder", 0.f, -0.4f);
	atk_hitbox_side->SpriteMountToSprite("knight_placeholder", -3.f, 0.f);
	atk_hitbox_up->SpriteMountToSprite("knight_placeholder", 0.f, -1.8f);
	atk_hitbox_down->SpriteMountToSprite("knight_placeholder", 0.f, 1.8f);

	core_logic.set_hud_instance(&hud);
	core_logic.set_physics_instance(&crossroad_physics);
	core_logic.set_parallex_instance(&crossroad_parallex);
	kontrol.set_logic_instance(&core_logic);

	crossroad_parallex.parallex_coefficient = 0.2;
	crossroad_parallex.add_player({ "knight_placeholder" });
	crossroad_parallex.add_scenery({
		"L15_crossroad_P1",
		"L15_crossroad_P2",
		"L15_crossroad_P3",
		"L15_crossroad_P4",
		"L15_crossroad_P5",
		"L15_crossroad_P6",
		"L15_crossroad_P7",
		"L15_crossroad_P8",
		"L16_crossroad_P1",
		"L16_crossroad_P2",
		"L17_crossroad_P1",
		"L18_crossroad_P1",
		"L19_crossroad_P1",
		"L20_crossroad_P1",

		"map_tile_1",
		"map_tile_2",
		"map_tile_3",
		"map_tile_4",
		"map_tile_5",
		"map_tile_6",
		"map_tile_7",
		"map_tile_8",
		"map_tile_9",
		"map_tile_10",
		"map_tile_11",
		"map_tile_12",
		"map_tile_13",
		"map_tile_14",
		"map_tile_15",
		"map_tile_16",
		"map_tile_17",
		"map_tile_18",
		"map_tile_19",
		"map_tile_20",
		"map_tile_21",
		"map_tile_22",
		"map_tile_23",
		"map_tile_24",
		"map_tile_25",
		"map_tile_26",
		"map_tile_27",
		"map_tile_28",

	});
	crossroad_parallex.add_camera_lock({
		"cam_lck_1",
		"cam_lck_2",
		"cam_lck_3",
		"cam_lck_4",
		"cam_lck_5",
		});
	
	crossroad_parallex.set_screen_bondary(CSystem::GetScreenLeft(), CSystem::GetScreenRight(), CSystem::GetScreenTop(), CSystem::GetScreenBottom());

	crossroad_parallex.set_target_framing(0.f, 6.f);
	crossroad_physics.set_parallex_instance(&dirt_parallex);
	std::function<void(float, float)> f = std::bind(&LibParallexScroll::set_player_linear_velocity, &crossroad_parallex, std::placeholders::_1, std::placeholders::_2);
	crossroad_physics.add_entity("knight_placeholder", f);
	//dirt_physics.add_entity("potato");
	crossroad_physics.add_map_tile({
		"map_tile_1",
		"map_tile_2",
		"map_tile_3",
		"map_tile_4",
		"map_tile_5",
		"map_tile_6",
		"map_tile_7",
		"map_tile_8",
		"map_tile_9",
		"map_tile_10",
		"map_tile_11",
		"map_tile_12",
		"map_tile_13",
		"map_tile_14",
		"map_tile_15",
		"map_tile_16",
		"map_tile_17",
		"map_tile_18",
		"map_tile_19",
		"map_tile_20",
		"map_tile_21",
		"map_tile_22",
		"map_tile_23",
		"map_tile_24",
		"map_tile_25",
		"map_tile_26",
		"map_tile_27",
		"map_tile_28",
	});

	std::function<void(std::string, float, float)> fun_tmp_vel = std::bind(&SimplePhysics::set_vel_temp, &crossroad_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_const_vel = std::bind(&SimplePhysics::set_vel_offset, &crossroad_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_tmp_force = std::bind(&SimplePhysics::set_force_temp, &crossroad_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_cont_force = std::bind(&SimplePhysics::set_force_1, &crossroad_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<bool()> fun_ground_state = std::bind(&SimplePhysics::get_is_on_ground, &crossroad_physics);

	kontrol.set_physics_engine_handler(fun_tmp_vel,fun_const_vel, fun_tmp_force, fun_cont_force);
	kontrol.set_gound_state_handler(fun_ground_state);
	game_ui.set_physics_instance(&kings_physics);
	animator.set_gound_status_handler(fun_ground_state);

	core_logic.set_atk_box("atk_hitbox_up", "atk_hitbox_down", "atk_hitbox_side");
	//kings_physics.init();
	core_logic.init();

	CSystem::SetWindowTitle("Hollow Knight - Forgotten Crossroad");
}

void CGameMain::load_main_menu()
{
	CSystem::LoadMap("main_menu.t2d");
}

void CGameMain::load_save_menu()
{
	CSystem::LoadMap("save_menu.t2d");
}

void CGameMain::load_kings_path()
{
	CSystem::LoadMap("kings_path.t2d");
}

void CGameMain::load_dirtmouth()
{	
	CSystem::LoadMap("dirtmouth.t2d");
}

void CGameMain::load_crossroad()
{
	CSystem::LoadMap("crossroad.t2d");
}

void CGameMain::auto_save()
{
	if (time(0) - last_save_time >= auto_save_interval)
	{
		current_save->time += auto_save_interval / 60;
		if (current_scene >= 2)
		{
			current_save->scene = current_scene;
		}
		hk_save_write(*current_save, "save.dat");
		last_save_time = time(0);
	}
}

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	current_save = new SaveFile();
	current_save->scene = 0;
	current_save->time = 0;
	m_iGameState = 1;
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态. 
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			SetGameState(2); // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
			{				
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
	init_scene();
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
	switch (last_scene)
	{
	case Scenes::KINGS_PATH:
		kings_parallex.main_loop(fDeltaTime);
		kings_physics.main_loop(fDeltaTime);
		kontrol.main_loop(fDeltaTime);
		animator.main_loop(fDeltaTime);
		core_logic.main_loop(fDeltaTime);	
		crawler0.main_loop(fDeltaTime);
		crawler0.GetFace(animator.m_imove);
		crawler1.main_loop(fDeltaTime);
		crawler1.GetFace(animator.m_imove);
		crawler2.main_loop(fDeltaTime);
		crawler2.GetFace(animator.m_imove);
		fly0.main_loop(fDeltaTime);
		focus.main_loop(fDeltaTime);
		focus.GetFace(animator.m_imove);
		ready.main_loop(fDeltaTime);
		ready.GetFace(animator.m_imove);
		auto_save();
		break;
	case Scenes::DIRT_MOUTH:
		dirt_parallex.main_loop(fDeltaTime);
		dirt_physics.main_loop(fDeltaTime);
		kontrol.main_loop(fDeltaTime);
		animator.main_loop(fDeltaTime);
		core_logic.main_loop(fDeltaTime);
		auto_save();
		break;
	case Scenes::CROSS_ROAD:
		crossroad_parallex.main_loop(fDeltaTime);
		crossroad_physics.main_loop(fDeltaTime);
		kontrol.main_loop(fDeltaTime);
		animator.main_loop(fDeltaTime);
		core_logic.main_loop(fDeltaTime);
		auto_save();
		break;
	default:
		break;
	}
	game_ui.main_loop();
	update_scene();
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
}
//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	test_flag = true;
}
//==========================================================================
//
// 鼠标弹起
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// 键盘按下
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	if (game_ui.key_press_callback(iKey))
	{
		return;
	}

	kontrol.key_press_callback(iKey);
	animator.key_press_callback(iKey);
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{
	if (game_ui.key_release_callback(iKey))
	{
		return;
	}

	kontrol.key_relese_callback(iKey);
	animator.key_release_callback(iKey);
}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	//kings_physics.on_colid_callback(szSrcName, szTarName);
	core_logic.sp_col_callback(szSrcName, szTarName);
	trigger_scene_callback(szSrcName, szTarName);
	if (strcmp("Crawler0", szTarName) == 0)
	{
		crawler0.get_col_callback(szSrcName);
	}
	if (strcmp("Crawler1", szTarName) == 0)
	{
		crawler1.get_col_callback(szSrcName);
	}
	if (strcmp("Crawler2", szTarName) == 0)
	{
		crawler2.get_col_callback(szSrcName);
	}
	if (strcmp("Fly0", szTarName) == 0)
	{
		fly0.get_col_callback(szSrcName);
	}
	if (strcmp("Focus0", szTarName) == 0)
	{
		focus.get_col_callback(szSrcName);
	}
	if (strcmp("Ready0", szTarName) == 0)
	{
		ready.get_col_callback(szSrcName);
	}
}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
}

void CGameMain::SetScene(int idx)
{
	current_scene = idx;
}

void CGameMain::hk_save_write(SaveFile& data, string path)
{
	std::ofstream out;
	out.open(path,std::ios::binary);
	out.write(reinterpret_cast<char*>(&data), sizeof(SaveFile));
	out.close();
}

void CGameMain::hk_save_read(SaveFile& data, string path)
{
	std::ifstream in;
	in.open(path,std::ios::binary);
	if (!in)
	{
		current_save->scene = 0;
		current_save->time = 0;
		hk_save_write(*current_save, "save.dat");
	}
	in.read(reinterpret_cast<char*>(&data), sizeof(SaveFile));
	in.close();
}

