/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;	

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

void CGameMain::trigger_scene_callback(std::string src_name, std::string tar_name)
{
	if (strcmp(src_name.c_str(), "knight_placeholder") == 0 &&
	strcmp(tar_name.c_str(), "to_dirtmouth") == 0)
	{
		current_scene = 1;
	}
}

void CGameMain::update_scene()
{
	if (current_scene != lats_scene)
	{
		lats_scene = current_scene;
		load_scene(current_scene);
	}
}

void CGameMain::init_scene()
{
	switch (current_scene)
	{
	case Scenes::KINGS_PATH:
		init_kings_path();
		break;
	case Scenes::DIRT_MOUTH:
		init_dirtmouth();
		break;
	default:
		break;
	}
}

void CGameMain::load_scene(int scene_id)
{
	load_dirtmouth();
	SetGameState(1);
}

void CGameMain::init_kings_path()
{
	kings_parallex.add_player({ "knight_placeholder" });
	kings_parallex.add_scenery({
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
		"potato"
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

	kings_kontrol.set_physics_engine_handler(fun_tmp_vel,fun_const_vel, fun_tmp_force, fun_cont_force);
	kings_kontrol.set_gound_state_handler(fun_ground_state);
	game_ui.set_physics_instance(&kings_physics);
	animator.set_gound_status_handler(fun_ground_state);

	auto knight = new CSprite("Knight");
	auto atk_hitbox_side = new CSprite("atk_hitbox_side");
	auto atk_hitbox_up = new CSprite("atk_hitbox_up");
	auto atk_hitbox_down = new CSprite("atk_hitbox_down");
	knight->SpriteMountToSprite("knight_placeholder", 0.f, -0.4f);
	atk_hitbox_side->SpriteMountToSprite("knight_placeholder", -3.f, 0.f);
	atk_hitbox_up->SpriteMountToSprite("knight_placeholder", 0.f, -1.8f);
	atk_hitbox_down->SpriteMountToSprite("knight_placeholder", 0.f, 1.8f);
	kings_logic.set_hud_instance(&hud);
	kings_logic.set_physics_instance(&kings_physics);
	kings_logic.set_parallex_instance(&kings_parallex);
	kings_logic.add_enemy("potato", 2);
	kings_logic.set_atk_box("atk_hitbox_up", "atk_hitbox_down", "atk_hitbox_side");
	kings_kontrol.set_logic_instance(&kings_logic);
	//kings_physics.init();
	kings_logic.init();
	CSystem::SetWindowTitle("Hollow Knight - King's Path");
}

void CGameMain::init_dirtmouth()
{
	CSystem::SetWindowTitle("Hollow Knight - Dirtmouth");
}

void CGameMain::load_dirtmouth()
{	
	CSystem::LoadMap("dirtmouth.t2d");
}

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{
	m_iGameState			=	1;
}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬. 
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{				
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
	init_scene();
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
	switch (current_scene)
	{
	case Scenes::KINGS_PATH:
		kings_parallex.main_loop(fDeltaTime);
		kings_physics.main_loop(fDeltaTime);
		kings_kontrol.main_loop(fDeltaTime);
		animator.main_loop(fDeltaTime);
		kings_logic.main_loop(fDeltaTime);
		break;
	default:
		break;
	}

	update_scene();
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
}
//==========================================================================
//
// ����ƶ�
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// �����
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	test_flag = true;
}
//==========================================================================
//
// ��굯��
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// ���̰���
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	if (game_ui.key_press_callback(iKey))
	{
		return;
	}

	kings_kontrol.key_press_callback(iKey);
	animator.key_press_callback(iKey);
}
//==========================================================================
//
// ���̵���
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void CGameMain::OnKeyUp( const int iKey )
{
	kings_kontrol.key_relese_callback(iKey);
	animator.key_release_callback(iKey);
	switch (iKey)
	{
	case KEY_LEFT:
		kings_parallex.set_npc_linear_velocity("potato", 0, 0);
		break;
	case KEY_RIGHT:
		kings_parallex.set_npc_linear_velocity("potato", 0, 0);
		break;
	default:
		break;
	}
}
//===========================================================================
//
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	//kings_physics.on_colid_callback(szSrcName, szTarName);
	kings_logic.sp_col_callback(szSrcName, szTarName);
	trigger_scene_callback(szSrcName, szTarName);
}
//===========================================================================
//
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
}

