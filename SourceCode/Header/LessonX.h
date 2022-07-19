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

/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
enum Scenes
{
	MENU = -1,
	SAVE = -1,
	KINGS_PATH = 0,
	DIRT_MOUTH = 1,
	CROSS_RODE = 2,
	CROSS_RODE_LEFT = 3,
	CROSS_RODE_RIGHT = 4,
};
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������
	LibParallexScroll kings_parallex = LibParallexScroll();
	void trigger_scene_callback(std::string src_name, std::string tar_name);
	void update_scene();
	bool is_inited = false;
	void init_scene();
	void load_scene(int scene_id);
	int current_scene = 0;
	int lats_scene = 0;
	void init_kings_path();
	void init_dirtmouth();
	void load_dirtmouth();
	KnightAnimator	animator = KnightAnimator("Knight");
	SimplePhysics kings_physics = SimplePhysics();
	Kontrol kings_kontrol = Kontrol("knight_placeholder");
	CoreLogic kings_logic = CoreLogic("knight_placeholder");
	HUD hud = HUD("hp_mask_0", "soul_orb");
	GameUI game_ui = GameUI();
	//SceneManager scene_manager = SceneManager();

public:
	CGameMain();            //���캯��
	~CGameMain();           //��������  

	// Get����
	int				GetGameState()											{ return m_iGameState; }
	
	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }
	
	// ��Ϸ��ѭ����
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

	bool test_flag = false;
};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_