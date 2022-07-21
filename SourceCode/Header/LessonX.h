/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "LibParallexScroll.h"
#include "SimplePhysics.h"
#include "Kontrol.h"
#include "HUD.h"
#include "KnightAnimator.h"
#include "CoreLogic.h"
#include "GameUI.h"
#include <time.h>
#include "EnemyAnimator.h"
#include "FlyAnimator.h"
#include "Tutorial.h"
#include "BossStage.h"
#include "SoundDevice.h"
#include "SoundEffectsPlayer.h"
#include "SoundEffectsLibrary.h"
#include "HollowSound.h"

/////////////////////////////////////////////////////////////////////////////////
//
// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
enum Scenes
{
	MENU = 0,
	SAVE = 1,
	DIFFICULTY = 2,
	KINGS_PATH = 3,
	DIRT_MOUTH = 4,
	CROSS_ROAD = 5,
	BOSS_STAGE = 6,
};
//struct SaveFile
//{
//	int scene;
//	long time;
//};
//namespace hk_sound {
//}
class	CGameMain
{
private:
		
	int				m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中
	void trigger_scene_callback(std::string src_name, std::string tar_name);
	void update_scene();
	bool is_inited = false;
	void init_scene();
	void load_scene(int scene_id);
	int current_scene = 0;
	int last_scene = -1;
	void init_main_menu();
	void init_save_menu();
	void init_difficulty_menu();
	void init_kings_path();
	void init_dirtmouth();
	void init_crossroad();
	void init_boss_State();
	bool is_inited_main_menu;
	bool is_inited_kings_path;
	bool is_inited_dirtmouth;
	void load_main_menu();
	void load_save_menu();
	void load_difficulty();
	void load_kings_path();
	void load_dirtmouth();
	void load_crossroad();
	void load_boss_stage();
	int auto_save_interval = 60;
	long last_save_time = 0;
	void auto_save();
	void force_save();
	CSprite* knight;
	CSprite* atk_hitbox_side;
	CSprite* atk_hitbox_up;
	CSprite* atk_hitbox_down;
	EnemyAnimator	crawler0 = EnemyAnimator("Crawler", 1, 0);
	EnemyAnimator	crawler1 = EnemyAnimator("Crawler", 1, 1);
	EnemyAnimator	crawler2 = EnemyAnimator("Crawler", 1, 2);
	FlyAnimator		fly0	 = FlyAnimator("Fly", 1, 0);
	Tutorial		focus = Tutorial("Focus");
	Tutorial		ready = Tutorial("Ready");
	KnightAnimator	animator = KnightAnimator("Knight");
	LibParallexScroll kings_parallex = LibParallexScroll();
	LibParallexScroll dirt_parallex = LibParallexScroll();
	LibParallexScroll crossroad_parallex = LibParallexScroll();
	SimplePhysics kings_physics = SimplePhysics();
	SimplePhysics dirt_physics = SimplePhysics();
	SimplePhysics crossroad_physics = SimplePhysics();
	Kontrol kontrol = Kontrol("knight_placeholder");
	CoreLogic core_logic = CoreLogic("knight_placeholder");
	HUD hud = HUD("hp_mask_0", "soul_orb");
	GameUI game_ui = GameUI();
	BossStage boss_stage = BossStage();
	//SceneManager scene_manager = SceneManager();
	HollowSound hollow_sound = HollowSound();


public:
	CGameMain();            //构造函数
	~CGameMain();           //析构函数  

	// Get方法
	int				GetGameState()											{ return m_iGameState; }
	
	// Set方法
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }
	
	// 游戏主循环等
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	void 			OnMouseMove( const float fMouseX, const float fMouseY );
	void 			OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
	void 			OnKeyUp( const int iKey );
	void 			OnSpriteColSprite( const char *szSrcName, const char *szTarName );
	void 			OnSpriteColWorldLimit( const char *szName, const int iColSide );

	void SetScene(int idx);
	void hk_save_write(SaveFile& data, string path);
	void hk_save_read(SaveFile& data, string path);
	SaveFile* current_save;
	bool test_flag = false;
};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_