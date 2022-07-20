#include <Stdio.h>
#include "CommonClass.h"
#include "Tutorial.h"
#include "time.h"
#include <string>
#include <math.h>
using namespace std;

Tutorial::Tutorial(const char* name)
{
	name = CSystem::MakeSpriteName(name,0);
	m_ptutorial = new CStaticSprite(name);
	ESC = KEY_ESCAPE;
	color = 0;
	touch = 0;
	calpha = 255;
	getface = 1;
	iface = 1;
}

Tutorial::~Tutorial()
{
	//dtor
}

//==========================================================================
//
// ������������
void Tutorial::main_loop(float dt)
{
	armory();
	m_ptutorial->SetSpriteCollisionReceive(true);
}
//==========================================================================
//
// ��ʼ��
void Tutorial::main_init()
{
	color = 0;
	touch = 0;
	calpha = 255;
	m_ptutorial->SetSpriteCollisionReceive(true);
}
//==========================================================================
//
// ���̰���
// ���� key�������µļ�
void Tutorial::key_press_callback(int key)
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
// ���̵���
// ���� key������ļ�
void Tutorial::key_release_callback(const int key)
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
}
//==========================================================================
//
// ��ײ����
// ���� script����ײ���ľ���
void Tutorial::get_col_callback(const char* script)
{
	if (strcmp("Knight",script))
	{
		switch(touch)
		{
			case 0:
				iface = getface;
			case 4:
				touch++;
				break;
		}
	}
}
//===========================================================================
//
// ��ȡ��ʿ����
void Tutorial::GetFace(int face)
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
//===========================================================================
//
// ����״̬
void Tutorial::armory()
{
	int n = 10;
	float fPosX = m_ptutorial->GetSpritePositionX();
	float width = m_ptutorial->GetSpriteWidth();
	switch (touch)
	{
		case 0:
			m_ptutorial->SetStaticSpriteFrame(0);
			if (color == 0)
			{
				if (calpha > 80)
				{
					calpha--;
					m_ptutorial->SetSpriteColorAlpha(calpha);
				}
				else
				{
					color = 1;
				}
			}
			if (color == 1)
			{
				if (calpha < 255)
				{
					calpha++;
					m_ptutorial->SetSpriteColorAlpha(calpha);
				}
				else
				{
					color = 0;
				}
			}
			break;
		case 1:
			if (calpha > n)
			{
				calpha -= n;
				m_ptutorial->SetSpriteColorAlpha(calpha);
			}
			else
			{
				calpha = 0;
				m_ptutorial->SetSpriteColorAlpha(calpha);
				touch++;
				m_ptutorial->SetStaticSpriteFrame(1);
			}
			break;
		case 2:
			m_ptutorial->SetSpritePositionX(fPosX - width * iface);
			touch++;
			break;
		case 3:
			if (calpha < 255-n)
			{
				calpha += n;
				m_ptutorial->SetSpriteColorAlpha(calpha);
			}
			else
			{
				calpha = 225;
				m_ptutorial->SetSpriteColorAlpha(calpha);
				touch++;
			}
			break;
		case 5:
			if (calpha > n)
			{
				calpha -= n;
				m_ptutorial->SetSpriteColorAlpha(calpha);
			}
			else
			{
				calpha = 0;
				m_ptutorial->SetSpriteColorAlpha(calpha);
				touch++;
				m_ptutorial->SetStaticSpriteFrame(0);
			}
			break;
		case 6:
			m_ptutorial->SetSpritePositionX(fPosX + width * iface);
			touch++;
			break;
		case 7:
			if (calpha < 255-n)
			{
				calpha += n;
				m_ptutorial->SetSpriteColorAlpha(calpha);
			}
			else
			{
				calpha = 225;
				m_ptutorial->SetSpriteColorAlpha(calpha);
				touch = 0;
			}
			break;
	}
}