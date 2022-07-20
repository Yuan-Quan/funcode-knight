#include <Stdio.h>
#include "CommonClass.h"
#include "FlyAnimator.h"
#include "time.h"
#include <string>
#include <math.h>
using namespace std;

FlyAnimator::FlyAnimator(const char* name, const int lvl, const int num)
{
	nameF = CSystem::MakeSpriteName(name, num);
	nameA = CSystem::MakeSpriteName("AREA", num);
	m_pfly = new CAnimateSprite(nameF);
	m_pa = new CAnimateSprite(nameA);
	stop = 0;
	m_iface = 1;
	getface = -1;
	m_ilvl = lvl + 1;
	m_icon = 0;
	m_fvel = 5.0f * m_ilvl;
	m_ftime = 0;
	m_fmtime = 0;
	m_iHP = 10;
	ESC = KEY_ESCAPE;
	ONE = KEY_1;
	TWO = KEY_2;
	THREE = KEY_3;
	KnightPosX = 0;
	KnightPosY = 0;
	hHIGHT = 0;
	hWIDTH = 0;
	m_canimation = "O";
	m_tface = new CTextSprite("fface");
	m_tcon = new CTextSprite("fcon");
	m_tanimation = new CTextSprite("fanimation");
	m_ttime = new CTextSprite("ftime");
	m_tHP = new CTextSprite("fHP");
}

FlyAnimator::~FlyAnimator()
{
	//dtor
}

void FlyAnimator::update_knight_pos()
{
	KnightPosX = m_pKnight->GetSpritePositionX();
	KnightPosY = m_pKnight->GetSpritePositionY();
}

//==========================================================================
//
// 单流程主程序
void FlyAnimator::main_loop(float dt)
{
	update_knight_pos();
	Show();
	move();
	if (stop != 0)
	{
		m_pfly->SetSpriteCollisionSend(false);
		m_pfly->SetSpriteCollisionReceive(false);
		if (stop == 4 && m_ftime > 0)
		{
			m_ftime -= dt;
			Animation("Bm");
		}
		else
		{
			m_pfly->SetSpriteVisible(false);
			return;
		}
	}
	face();
	if (m_icon != 3)
	{
		if (m_ftime > 0)
		{
			m_icon = 2;
			m_ftime -= dt;
			m_pfly->SetSpriteColorAlpha(160);
		}
		else
		{
			m_icon = 0;
			m_pfly->SetSpriteColorAlpha(255);
		}
		if (m_fmtime > -0.01)
		{
			m_fmtime -= dt;
		}
	}
}
//==========================================================================
//
// 初始化
void FlyAnimator::main_init(const int lvl)
{
	srand(time(NULL));
	m_ilvl = lvl + 1;
	stop = 0;
	m_iface = 1;
	m_icon = 0;
	m_fvel = 5.0f * m_ilvl;
	m_ftime = 0;
	m_iHP = 20;
	m_pfly->SetSpriteVisible(true);
	m_pfly->SetSpriteCollisionSend(true);
	m_pfly->SetSpriteCollisionReceive(true);
	hHIGHT = m_pa->GetSpriteHeight() / 2;
	hWIDTH = m_pa->GetSpriteWidth() / 2;

	stop = false;
}
//==========================================================================
//
// 键盘按下
// 参数 key：被按下的键
void FlyAnimator::key_press_callback(int key)
{
	if (key == ESC)
	{
		if (stop == 0)
		{
			stop = 1;
		}
		else if (stop == 2)
		{
			stop = 3;
		}
	}
}
//==========================================================================
//
// 键盘弹起
// 参数 key：弹起的键
void FlyAnimator::key_release_callback(const int key)
{
	if (stop == 0 || stop == 4)
	{
		if (key == ONE) main_init(1);
		if (key == TWO) main_init(2);
		if (key == THREE) main_init(3);
	}
	if (key == ESC)
	{
		if (stop == 1)
		{
			stop = 2;
		}
		else if (stop == 3)
		{
			stop = 0;
		}
	}
}//==========================================================================
//
// 碰撞精灵
// 参数 script：碰撞到的精灵
void FlyAnimator::get_col_callback(const char* script)
{
	if (stop != 0) return;
	if (strcmp("Blank", script) == 0)
		hurt();
}
//===========================================================================
//
// 蚊子朝向
void FlyAnimator::face()
{
	float fPosX = m_pfly->GetSpritePositionX();
	m_iface = fPosX - KnightPosX;
	if (m_iface < 0)
	{
		m_pfly->SetSpriteFlipX(true);
	}
	else
	{
		m_pfly->SetSpriteFlipX(false);
	}
}
//===========================================================================
//
// 蚊子移动
void FlyAnimator::move()
{
	if (stop != 0)
	{
		m_pfly->SetSpriteLinearVelocity(0,0);
	}
	else
	{
		//if ((m_icon == 0 || m_icon == 2) && m_fmtime <= 0)
		if ((m_icon == 0 || m_icon == 2))
		{
			if (m_pa->IsPointInSprite(KnightPosX, KnightPosY))
			{
				float rvel = m_fvel * 2;
				float dx = KnightPosX - m_pfly->GetSpritePositionX();
				float dy = KnightPosY - m_pfly->GetSpritePositionY();
				parallex_instance_->set_npc_linear_velocity(m_pfly->GetName(), dx, dy);
				//m_pfly->SpriteMoveTo(KnightPosX, KnightPosY - 10, rvel, 0);
				m_fmtime = 2.0f;
			}
			else
			{
				float fPosX = m_pa->GetSpritePositionX();
				float fPosY = m_pa->GetSpritePositionY();
				float rvel = CSystem::RandomRange(m_fvel * 0.75, m_fvel * 1.75);
				fPosX = CSystem::RandomRange(fPosX - hHIGHT, fPosX + hHIGHT);
				fPosY = CSystem::RandomRange(fPosY - hWIDTH, fPosY + hWIDTH);
				m_pfly->SpriteMoveTo(fPosX, fPosY, rvel, 0);
				m_fmtime = CSystem::RandomRange(200, 500) / (m_ilvl * 100);
			}
			Animation("Fl");
		}
	}
}
//===========================================================================
//
// 蚊子受伤
void FlyAnimator::hurt()
{
	if (m_ftime > 0)return;
	float fPosX = m_pfly->GetSpritePositionX();
	float fPosY = m_pfly->GetSpritePositionY();
	float len = sqrt(pow(fPosX - KnightPosX, 2) + pow(fPosY - KnightPosY, 2));
	m_icon = 2;
	m_ftime = 0.15 * m_ilvl;
	if (m_pa->IsPointInSprite(fPosX,fPosY))
	{
		m_pfly->SpriteMoveTo((20.0F - m_ilvl) *(fPosX-KnightPosX) / len, (20.0F - m_ilvl) *(fPosY-KnightPosY) / len, 20 * (14.0f - m_ilvl), true);
	}
	if (m_iHP <= 0)
	{
		m_icon = 3;
		m_pfly->SetSpriteColorAlpha(255);
		stop = 4;
		m_ftime = 0.3f;
		Animation("Bm");
	}
	else
	{
		m_iHP -= 6 / (m_ilvl - 1);
	}
}
//===========================================================================
//
// 蚊子动作变化
void FlyAnimator::Animation(char* szAnim)
{
	if(strcmp(szAnim,m_canimation))
	{
		if (strcmp("Bm", m_canimation)!=0 ||
			m_pfly->IsAnimateSpriteAnimationFinished())
		{
			m_pfly->AnimateSpritePlayAnimation(szAnim, false);
			m_canimation = szAnim;
		}
	}
	
}
//===========================================================================
//
// 展示数值
void FlyAnimator::Show()
{
	m_tface->SetTextValue(m_iface);
	m_tcon->SetTextValue(m_icon);
	m_tanimation->SetTextString(m_canimation);
	m_ttime->SetTextValueFloat(m_ftime);
	m_tHP->SetTextValue(m_iHP);
}

void FlyAnimator::set_parallex_instance_(LibParallexScroll* nh)
{
	parallex_instance_ = nh;
}