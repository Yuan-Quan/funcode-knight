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
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	m_iGameState			=	1;
	kings_parallex.add_player({ "potato" });
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
		});


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
	kings_parallex.set_screen_bondary(CSystem::GetScreenLeft(), CSystem::GetScreenRight(), CSystem::GetScreenTop(), CSystem::GetScreenBottom());
	std::function<void(float, float)> f = std::bind(&LibParallexScroll::set_player_linear_velocity, &kings_parallex, std::placeholders::_1, std::placeholders::_2);
	kings_physics.add_entity("potato", f);
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
		});

	std::function<void(std::string, float, float)> fun_tmp_vel = std::bind(&SimplePhysics::set_vel_temp, &kings_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_const_vel = std::bind(&SimplePhysics::set_vel_offset, &kings_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_tmp_force = std::bind(&SimplePhysics::set_force_temp, &kings_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<void(std::string, float, float)> fun_cont_force = std::bind(&SimplePhysics::set_force_1, &kings_physics, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	std::function<bool()> fun_ground_state = std::bind(&SimplePhysics::get_is_on_ground, &kings_physics);

	kings_kontrol.set_physics_engine_handler(fun_tmp_vel,fun_const_vel, fun_tmp_force, fun_cont_force);
	kings_kontrol.set_gound_state_handler(fun_ground_state);

	for (size_t i = 0; i < 5; i++)
	{
		hud.apend_a_mask();
	}
	
	//kings_physics.init();
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
	kings_parallex.main_loop(fDeltaTime);
	kings_physics.main_loop(fDeltaTime);
	kings_kontrol.main_loop(fDeltaTime);
	hud.main_loop();
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
	kings_kontrol.key_press_callback(iKey);
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{
	kings_kontrol.key_relese_callback(iKey);
}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	//kings_physics.on_colid_callback(szSrcName, szTarName);
}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
}

