#include <Stdio.h>
#include "CommonClass.h"
#include "KnightAnimator.h"
#include "Kontrol.h"
#include "time.h"
#include <string>
#include <math.h>
using namespace std;

KnightAnimator::KnightAnimator(const char* name)
{
	stop = 0;
	m_imove = -1;
	m_iface = 0;
	m_ijump = 2;
	m_iattack = 0;
	m_imagic = 0;
	m_idash = 0;
	m_ihurt = 0;
	m_ifocus = 0;
	m_idjump = 2;
	m_ieffect = 0;
	m_pknight = new CAnimateSprite(name);
    m_pPlaceHolder = new CSprite("knight_placeholder");
	m_peffect = new CAnimateSprite("Blank");
	m_tmove = new CTextSprite("move");
	m_tface = new CTextSprite("face");
	m_tjump = new CTextSprite("jump");
	m_tattack = new CTextSprite("attack");
	m_tmagic = new CTextSprite("magic");
	m_tdash = new CTextSprite("dash");
	m_thurt = new CTextSprite("hurt");
	m_tfocus = new CTextSprite("focus");
	m_tdjump = new CTextSprite("djump");
	m_teffect = new CTextSprite("effect");
	//m_sslash = new CSound(game / data / audio / slash.wav);
	//m_sjump = new CSound(game / data / audio / jump.wav);
	m_canimation = "I";
	m_ceffectani = "SEA";
	J = KEY_J;
	K = KEY_K;
	L = KEY_L;
	I = KEY_I;
	W = KEY_W;
	S = KEY_S;
	A = KEY_A;
	D = KEY_D;
	Q = KEY_Q;
	P = KEY_P;
	ESC = KEY_ESCAPE;
	SIZE = 20.0f;
	VEL = 400.0f;

}

KnightAnimator::~KnightAnimator()
{
	//dtor
}

//==========================================================================
//
// 单流程主程序
void KnightAnimator::main_loop(float dt)
{
	if (stop != 0)return;
	m_ftime = dt;
	Show();
	hurt();
	dash();
	magic();
	move();
	Delete();
	if (strcmp("D", m_canimation) == 0)
	{
		attack();
		if (m_pknight->IsAnimateSpriteAnimationFinished() == false) return;
	}
	else if (strcmp("DD", m_canimation) == 0 || strcmp("S", m_canimation) == 0 || strcmp("W", m_canimation) == 0)
	{
		if (m_pknight->IsAnimateSpriteAnimationFinished() == false) return;
	}
	attack();
	face();
	jump();
	if(m_fjump >= 0)m_fjump -= m_ftime;
}
void KnightAnimator::set_gound_status_handler(std::function<bool()> fun)
{
	is_grounded_nh_ = fun;
}
//==========================================================================
//
// 键盘按下
// 参数 key：被按下的键
void KnightAnimator::key_press_callback(int key)
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
	if (stop != 0)return;
	srand(time(NULL));
	//if (key == P) { m_ijump = 1; }//调试专用通道
	if ((key == J) && (m_iattack == 0))m_iattack = rand() % 2 + 1;
	if (key == I)m_imagic = 1;
	if (key == Q)m_ifocus = 1;
	if (key == S) { m_iface = -1; }
	if (key == W) { m_iface = 1; }
	if (key == D) { m_imove = -2;/*右移*/; }
	if (key == A) { m_imove = 2;/*左移*/; }
	if (key == L && m_idash == 0)m_idash = 1;
	if (key == KEY_K && m_ihurt == 0 && m_imagic == 0 && m_idash != 1)
	{
		switch( m_ijump )
		{
			case 0:m_ijump = 4;break;
			case 1:m_ijump = 5;break;
			case 2:if ( m_idjump > 0 ) m_ijump= 3;break;
		}
	}
}
//==========================================================================
//
// 键盘弹起
// 参数 key：弹起的键
void KnightAnimator::key_release_callback(const int key)
{
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
	if (stop != 0)return;
	//if (key == P) { m_ijump = 6; }//调试专用通道
	if (key == J) { m_iattack = 0; }
	if (key == I) { m_imagic = 0; }
	if (key == Q) { m_ifocus = 0; }
	if ((key == S) && (m_iface == -1)) { m_iface = 0; }
	if ((key == W) && (m_iface == 1)) { m_iface = 0; }
	if ((key == D) && (m_imove == -2)) { m_imove = -1;/*右移停止*/; }
	if ((key == A) && (m_imove == 2)) { m_imove = 1;/*左移停止*/; }
}
//===========================================================================
//
// 小骑士朝向
void KnightAnimator::face()
{
	//m_pknight->SetSpritePositionY(0);
	float shift = m_pknight->GetSpriteWidth()*0.12;
	if (m_imove < 0)
	{
		m_pknight->SetSpritePositionX(m_pPlaceHolder->GetSpritePositionX() - shift);
		m_pknight->SetSpriteFlipX(true);
		m_pPlaceHolder->SetSpriteFlipX(true);
	}
	else if (m_imove > 0)
	{
		m_pknight->SetSpritePositionX(m_pPlaceHolder->GetSpritePositionX() + shift);
		m_pknight->SetSpriteFlipX(false);
		m_pPlaceHolder->SetSpriteFlipX(false);
	}
}
//===========================================================================
//
// 小骑士移动
void KnightAnimator::move()
{
	if (m_ihurt == 0 && m_imagic == 0 && m_iattack == 0 && m_idash == 0 && m_ijump == 0)
	{
		switch (m_imove)
		{
		case -2:
		case 2:Animation("RK");break;
		case -1:
		case 1:
			switch (m_iface)
			{
			case 0:
				if (m_ifocus == 1)
				{
					Animation("F");
					Release("FE",9);
					focus();
				}
				else
				{
					Animation("I");
				}
				break;
			case -1:Animation("LDK");break;
			case 1:Animation("LUK");break;
			}
		}
	}
}
//===========================================================================
//
// 小骑士跳跃
void KnightAnimator::jump()
{
	switch (m_ijump)
	{
		case 0:
		case 1:
		{
			refresh();
			break;
		}
	}
	if ((m_ihurt == 0) && (m_imagic == 0) && (m_iattack == 0) && (m_idash != 1))
	{
		switch (m_ijump)
		{
			case 0:break;
			case 1:
			{
				if(is_grounded_nh_())
				{
					m_ijump=6;
				}
				/*if (离墙)
				{
					m_ijump=3;
					m_idjump=1;
				}
				else 匀速下滑;*/
				Animation("WSd");
				break;
			}
			case 2:
			{	
				if (is_grounded_nh_() && m_fjump<0)
				{
					m_ijump=6;
					m_idjump=2;
				}
				/*else if (触墙)
				{
					m_ijump=1;
					refresh();
				}*/
				Animation("AK");
				break;
			}
			case 3:
			{
				m_ijump = 2;
				m_idjump = 0;
				/*重置上升速度*/
				Animation("DJ");
				Release("DJE",8);
				break;
			}
			case 4:
			{
				m_ijump = 2;
				m_idjump = 1;
				m_fjump = 0.1f;
				Animation("A");
				/*正上跳跃*/
				break;
			}
			case 5:
			{
				m_imove =  0 - m_imove;
				face();
				m_ijump = 2;
				m_idjump = 1;
				Animation("WJ");
				/*斜上跳跃*/
				Release("WJE", 7);
				break;
			}
			case 6:
			{
				m_ijump = 0;
				Animation("L");
				break;
			}
		}
	}
}
//===========================================================================
//
// 小骑士攻击
void KnightAnimator::attack()
{
	if ((m_ihurt == 0) && (m_imagic == 0))
	{
		if (m_iattack != 0)
		{
			if (strcmp("D",m_canimation)==0)
			{
				Release("DSSE", 5);
				m_iattack = 0;
			}
			else if (m_ijump == 1)
			{
				Animation("WS");
				if (m_iattack == 1)
				{
					Release("SAE", 13);
					m_iattack = 2;
				}
				else
				{
					Release("SBE", 12);
					m_iattack = 1;
				}
			}
			else if ((m_ijump >= 2) && (m_iface == -1))
			{
				Animation("DS");
				Release("DSE", 4);
			}
			else if (m_iface == 1)
			{
				Animation("US");
				Release("USE", 11);
			}
			else
			{
				if (m_iattack == 1)
				{
					Animation("SA");
					Release("SAE", 2);
					m_iattack = 2;
				}
				else
				{
					Animation("SB");
					Release("SBE", 1);
					m_iattack = 1;
				}
			}
		}
	}
}
//===========================================================================
//
// 小骑士受伤
void KnightAnimator::hurt()
{
	if ((m_idash == 0) && (m_imagic == 0))
	{
		if (m_ihurt == 1)
		{
			Animation("H");
			Release("SH", 0);
			/*血量-1*/
			m_ihurt = 0;
		}
	}
	else m_ihurt = 0;
	if (/*血量小于零*/false)
	{
		Animation("Dth");
		/*结束游戏*/
	}
}
//===========================================================================
//
// 小骑士冲刺
void KnightAnimator::dash()
{
	if ((m_imagic == 0) && (m_ihurt == 0))
	{
		if (m_idash == 1)
		{
			if (m_ijump == 1)
			{
				m_imove = 0 - m_imove;
				face();
				m_ijump = 2;
				m_idjump = 1;
				m_idash--;
			}
			switch (m_iface)
			{
			case -1:if (m_ijump >= 2)
			{
				Animation("DD");/*向下冲刺*/break;
			}
			case 1:
			case 0:Animation("D");
				Release("DE", 3);
				/*向面向方向冲刺*/break;
			}
			m_idash++;
			jump();
		}
	}
	else m_idash = 0;
}
//===========================================================================
//
// 小骑士施法
void KnightAnimator::magic()
{
	if ((m_ihurt == 0) && (m_idash == 0))
	{
		if (m_imagic == 1)
		{
			if (m_iface == 1)
			{
				Animation("S");
				Release("SE", 6);
			}
			else
			{
				Animation("W");
				Release("B", 10);
			}
		}
	}
	else m_imagic = 0;
}
//===========================================================================
//
// 释放特效
void KnightAnimator::Release(char* szAnim, int LinkPoint)
{
	float sizelvl=(m_pknight->GetSpriteHeight())/SIZE;
	if (
		(m_ieffect == 1) ||
		(
			strcmp("D", m_canimation) == 0 &&
			strcmp("DSSE", szAnim) == 0 &&
			strcmp("DSSE", m_ceffectani) != 0
			)
		)
	{
		char* tmpEffect;
		tmpEffect = CSystem::MakeSpriteName(szAnim, 0);
		m_peffect->DeleteSprite();
		m_peffect->CloneSprite(tmpEffect);
		m_peffect->SetSpriteHeight((m_peffect->GetSpriteHeight()) * sizelvl);
		m_peffect->SetSpriteWidth((m_peffect->GetSpriteWidth()) * sizelvl);
		if (strcmp("F", m_canimation) == 0)
		{
			m_peffect->SetSpriteColorAlpha(200);
		}
		else
		{
			m_peffect->SetSpriteColorAlpha(255);
		}
		m_peffect->SetSpriteVisible(true);
		m_peffect->SetSpriteCollisionSend(true);
		m_peffect->SetSpriteEnable(true);
		bool bFlipX = m_pknight->GetSpriteFlipX();
		if (strcmp("WJ", m_canimation) == 0 || strcmp("W" , m_canimation) == 0)
		{
			float fPosX, fPosY;
			fPosX = m_pknight->GetSpriteLinkPointPosX(LinkPoint);
			fPosY = m_pknight->GetSpriteLinkPointPosY(LinkPoint);
			m_peffect->SetSpritePositionX(fPosX);
			m_peffect->SetSpritePositionY(fPosY);
			/*尘土向斜下方移动*/
			m_peffect->SetSpriteFlipX(bFlipX);
		}
		else
		{
			m_peffect->SpriteMountToSpriteLinkPoint("Knight", LinkPoint);
			if (strcmp("WSd", m_canimation) == 0 || strcmp("WS", m_canimation) == 0)
			{
				m_peffect->SpriteDismount();
				m_peffect->SetSpriteFlipX(!bFlipX);
			}
		}
		m_peffect->AnimateSpritePlayAnimation(szAnim, false);
		if (strcmp("B", szAnim) == 0)
		{
			//m_peffect->SpriteDismount();
			m_peffect->SetSpriteLinearVelocity(VEL * sizelvl * (2 * bFlipX - 1), 0);
		}
		m_ceffectani = szAnim;
	}
}
//===========================================================================
//
// 小骑士动作变化
void KnightAnimator::Animation(char* szAnim)
{
	if (AnimationBreak(szAnim))
	{
		if (
			strcmp("D", szAnim) == 0 ||
			strcmp("DD", szAnim) == 0 ||
			strcmp("S", szAnim) == 0 ||
			strcmp("W", szAnim) == 0 
			)
		{
			m_pknight->SetSpriteColorAlpha(160);
		}
		else
		{
			m_pknight->SetSpriteColorAlpha(255);
		}
		m_ieffect = 1;
		m_pknight->AnimateSpritePlayAnimation(szAnim, false);
		m_canimation = szAnim;
		return;
	}
	m_ieffect = 0;
}
//===========================================================================
//
// 判定是否可以打断当前动画
int KnightAnimator::AnimationBreak( char* szAnim )
{
	int same = strcmp(szAnim, m_canimation);
	if ( same != 0)
		if
			(
				(
					strcmp("D", szAnim) == 0 || 
					strcmp("DD", szAnim) == 0 ||
					strcmp("S", szAnim) == 0 || 
					strcmp("W", szAnim) == 0 ||
					strcmp("H", szAnim) == 0 || 
					strcmp("Dth", szAnim) == 0
					) 
				||
				(
					strcmp("I", m_canimation) == 0 ||
					strcmp("RK", m_canimation) == 0 ||
					strcmp("LUK", m_canimation) == 0 ||
					strcmp("LDK", m_canimation) == 0 ||
					strcmp("AK", m_canimation) == 0 ||
					strcmp("WSd", m_canimation) == 0 ||
					strcmp("F", m_canimation) == 0
					)
				||
				(
					(
						strcmp("A", m_canimation) == 0 ||
						strcmp("WJ", m_canimation) == 0
						) 
					&& strcmp("AK", szAnim) != 0
					)
				||
				(
					(
						strcmp("SA", m_canimation) == 0 &&
						strcmp("SB", szAnim) != 0
						)||
					(
						strcmp("SB", m_canimation) == 0 &&
						strcmp("SA", szAnim) != 0
						)
					)
				)
			return(true);
	bool end = m_pknight->IsAnimateSpriteAnimationFinished();
	return(end);
}
//===========================================================================
//
// 展示数值
void KnightAnimator::Show()
{
	m_tmove->SetTextValue(m_imove);
	m_tface->SetTextValue(m_iface);
	m_tjump->SetTextValue(m_ijump);
	m_tattack->SetTextValue(m_iattack);
	m_tmagic->SetTextValue(m_imagic);
	m_tdash->SetTextValue(m_idash);
	m_thurt->SetTextValue(m_ihurt);
	m_tfocus->SetTextValue(m_ifocus);
	m_tdjump->SetTextValue(m_idjump);
	m_teffect->SetTextValue(m_ieffect);
}
//===========================================================================
//
// 封印特效
void KnightAnimator::Delete()
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
// 聚集
void KnightAnimator::focus()
{
	//掉魂
	if (m_peffect->IsAnimateSpriteAnimationFinished())
	{
		m_ifocus = 0;
		//加一滴血；
	}
}
//===========================================================================
//
// 刷新冲刺和二段跳
void KnightAnimator::refresh()
{
	m_idjump = 2;
	m_idash = 0;
}
//===========================================================================
//
// 受击
void KnightAnimator::hit()
{
	m_ihurt = 1;
}