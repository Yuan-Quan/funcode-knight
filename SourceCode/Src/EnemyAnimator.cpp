#include <Stdio.h>
#include "CommonClass.h"
#include "EnemyAnimator.h"
#include "time.h"
#include <string>
#include <math.h>
using namespace std;

EnemyAnimator::EnemyAnimator(const char* name, const int lvl,const int num)
{
	nameE = CSystem::MakeSpriteName(name, num);
	nameL = CSystem::MakeSpriteName("CL", num);
	nameR = CSystem::MakeSpriteName("CR", num);
	m_pcrawler = new CAnimateSprite(nameE);
	m_pcl = new CAnimateSprite(nameL);
	m_pcr = new CAnimateSprite(nameR);
	m_peffect = new CAnimateSprite("effect");
	stop = 0;
	m_iface = 1;
	getface = -1;
	m_ilvl = lvl+1;
	m_icon = 0;
	m_fvel = 5.0f*m_ilvl;
	m_ftime = 0;
	m_iHP = 20;
	ESC = KEY_ESCAPE;
	ONE = KEY_1;
	TWO = KEY_2;
	THREE = KEY_3;
	SIZE = 20.0f;
	m_canimation = "O";
	m_tface = new CTextSprite("eface");
	m_tcon = new CTextSprite("econ");
	m_tanimation = new CTextSprite("eanimation");
	m_teffect = new CTextSprite("eeffect");
	m_ttime = new CTextSprite("etime");
	m_tHP = new CTextSprite("HP");
}

EnemyAnimator::~EnemyAnimator()
{
	//dtor
}

//==========================================================================
//
// 单流程主程序
void EnemyAnimator::main_loop(float dt)
{
	Show();
	move();
	if (stop != 0)
	{
		m_pcrawler->SetSpriteCollisionSend(false);
		if (stop == 4 && m_ftime>0)
		{
			m_ftime -= dt;
			Animation("K");
		}
		else return;
	}
	face();
	Delete();
	if (m_icon != 3)
	{
		if (m_ftime > 0)
		{
			m_icon = 2;
			m_ftime -= dt;
			m_pcrawler->SetSpriteColorAlpha(160);
		}
		else
		{
			m_icon = 0;
			m_pcrawler->SetSpriteColorAlpha(255);
		}
	}
}
//==========================================================================
//
// 初始化
void EnemyAnimator::main_init(const int lvl)
{
	m_ilvl = lvl+1;
	stop = 0;
	m_iface = 1;
	m_icon = 0;
	m_fvel = 5.0f*m_ilvl;
	m_ftime = 0;
	m_iHP = 20;
	m_pcrawler->SetSpriteCollisionReceive(true);
	m_pcrawler->SetSpriteCollisionSend(true);
	m_pcl->SetSpriteCollisionReceive(true);
	m_pcl->SetSpriteCollisionSend(true);
	m_pcr->SetSpriteCollisionReceive(true);
	m_pcr->SetSpriteCollisionSend(true);
}
//==========================================================================
//
// 键盘按下
// 参数 key：被按下的键
void EnemyAnimator::key_press_callback(int key)
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
void EnemyAnimator::key_release_callback(const int key)
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
void EnemyAnimator::get_col_callback(const char* script)
{
	if (stop != 0) m_ilvl = 1;
	if (
		strcmp(nameL, script) == 0 &&
		m_iface == 1
		)
	{
		m_iface = -1;
		Animation("T");
	}
	if (
		strcmp(nameR, script) == 0 &&
		m_iface == -1
		)
	{
		m_iface = 1;
		Animation("T");
	}
	if ( strcmp("Blank", script) == 0 )
		hurt("SS");
}
//===========================================================================
//
// 爬虫朝向
void EnemyAnimator::face()
{
	if (strcmp("T", m_canimation)==0)return;
	if (m_iface < 0)
	{
		m_pcrawler->SetSpriteFlipX(true);
	}
	else if (m_iface > 0)
	{
		m_pcrawler->SetSpriteFlipX(false);
	}
}
//===========================================================================
//
// 爬虫移动
void EnemyAnimator::move()
{
	if (stop != 0)
	{
		parallex_instance_->set_npc_linear_velocity(m_pcrawler->GetName(), 0, 0);
		//m_pcrawler->SetSpriteLinearVelocityX(0);
	}
	else if (m_icon == 0 || m_icon == 2)
	{
		parallex_instance_->set_npc_linear_velocity(m_pcrawler->GetName(), -m_ilvl * m_fvel * m_iface, 0);
		//m_pcrawler->SetSpriteLinearVelocityX(-m_ilvl * m_fvel * m_iface);
		Animation("Wk");
	}
}
//===========================================================================
//
// 爬虫受伤
void EnemyAnimator::hurt(char* szAnim)
{
	if (m_ftime > 0)return;
	float fPosX = m_pcrawler->GetSpritePositionX();
	float fPosY = m_pcrawler->GetSpritePositionY();
	float XL = m_pcl->GetSpritePositionX();
	float XR = m_pcr->GetSpritePositionX();
	m_icon = 2;
	m_ftime = 0.2 * m_ilvl;
	Animation("H");
	if (fPosX > XL && fPosX < XR)
	{
		m_pcrawler->SpriteMoveTo(fPosX - (14.0F - m_ilvl) * getface, fPosY, 20 * (14.0f - m_ilvl), true);
	}
	Release(szAnim,1);
	if (m_iHP <= 0) 
	{
		m_icon = 3;
		m_pcrawler->SetSpriteColorAlpha(255);
		stop = 4;
		m_ftime = 0.3f;
	}
	else
	{
		m_iHP -= 6 / (m_ilvl - 1);
	}
}
//===========================================================================
//
// 释放特效
void EnemyAnimator::Release(char* szAnim, int LinkPoint)
{
	if (m_ieffect == 1)
	{
		float sizelvl = (m_pcrawler->GetSpriteHeight()) / SIZE;
		char* tmpEffect;
		tmpEffect = CSystem::MakeSpriteName(szAnim, 0);
		m_peffect->DeleteSprite();
		m_peffect->CloneSprite(tmpEffect);
		m_peffect->SetSpriteHeight((m_peffect->GetSpriteHeight()) * sizelvl);
		m_peffect->SetSpriteWidth((m_peffect->GetSpriteWidth()) * sizelvl);
		m_peffect->SetSpriteVisible(true);
		m_peffect->SetSpriteCollisionSend(false);
		m_peffect->SetSpriteEnable(true);
		bool bFlipX = m_pcrawler->GetSpriteFlipX();
		m_peffect->SpriteMountToSpriteLinkPoint("Crawler", LinkPoint);
		m_peffect->AnimateSpritePlayAnimation(szAnim, false);
		m_ceffectani = szAnim;
	}
}
//===========================================================================
//
// 爬虫动作变化
void EnemyAnimator::Animation(char* szAnim)
{
	if (AnimationBreak(szAnim))
	{
		if (strcmp("H", szAnim) != 0)
		{
			m_pcrawler->AnimateSpritePlayAnimation(szAnim, false);
			m_canimation = szAnim;
		}
		m_ieffect = 1;
		return;
	}
	m_ieffect = 0;
}
//===========================================================================
//
// 封印特效
void EnemyAnimator::Delete()
{
	if (m_peffect->IsAnimateSpriteAnimationFinished())
	{
		if (m_peffect->GetSpriteIsMounted())
		{
			m_peffect->SpriteDismount();
		}
		m_peffect->SetSpriteVisible(false);
		m_peffect->SetSpriteEnable(false);
	}
}
//===========================================================================
//
// 判定是否可以打断当前动画
int EnemyAnimator::AnimationBreak(char* szAnim)
{
	int same = strcmp(szAnim, m_canimation);
	if (same != 0)
		if (strcmp("K", szAnim) == 0 || strcmp("Wk", m_canimation) == 0)
		{
			return(true);
		}
	bool end = m_pcrawler->IsAnimateSpriteAnimationFinished();
	return(end);
}
//===========================================================================
//
// 展示数值
void EnemyAnimator::Show()
{
	m_tface->SetTextValue(getface);
	m_tcon->SetTextValue(m_icon);
	m_tanimation->SetTextString(m_canimation);
	m_teffect->SetTextValue(m_ieffect);
	m_ttime->SetTextValueFloat(m_ftime);
	m_tHP->SetTextValue(m_iHP);
}
//===========================================================================
//
// 获取骑士朝向
void EnemyAnimator::GetFace(int face)
{
	if (face > 0)
	{
		getface = 1;
	}
	else
	{
		getface = -1;
	}
}

void EnemyAnimator::set_parallex_instance_(LibParallexScroll* nh)
{
	parallex_instance_ = nh;
}
