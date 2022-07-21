#pragma once
#include <math.h>
#include <time.h>
#include "CommonClass.h"
class BossStage
{
public:
BossStage();
void main_loop(float dt);

private:
int cnt=2,cnt1=2,cntt=0;
time_t T1,T2;
time_t T3,T4,T5,T6,TT;
int Line;
bool First=false,ST2 ,ST1end,Showed=false;
int Times=0;
bool ST1=false,IsEnded = false;
bool Set1=false;
int FirstStage=0;
int Typed = 0;
int hp=3;
bool Seted;
bool IsPressed = false;
bool dan1=false,dan2=false,dan3=false;

CSprite* dan11 = new CSprite("dan11");
CSprite* dan22 = new CSprite("dan11");
CSprite* dan33 = new CSprite("dan11");
CSprite* Q1 = new CSprite("Q1");
CSprite* Q2 = new CSprite("Q2");
CSprite* Q3 = new CSprite("Q3");

void duplicate();
};

