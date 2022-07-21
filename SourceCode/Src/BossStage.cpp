#include "BossStage.h"
#include <string>

BossStage::BossStage()
{
}

void BossStage::main_loop(float dt)
{
CTextSprite *hp1;
				hp1 = new CTextSprite("HP");
				hp1->SetTextValue(hp);
				hp1->SetSpritePosition(-39.714,-30.000);
				srand(time(NULL));
				CSprite *npc;
				npc = new CSprite("npc");
				npc->SetSpriteCollisionSend(1);
				//T2=time(NULL);
				CAnimateSprite *attack1;
				attack1 = new CAnimateSprite("Attack1");
				CSprite *dan11,*dan22,*dan33,*Q1,*Q2,*Q3;
				float fSpeedY=npc->GetSpriteLinearVelocityY(),fSpeedX;
							Q1 = new CSprite("Q1", "Q");
							Q2 = new CSprite("Q2","Q");
							Q3 = new CSprite("Q3", "Q");
							dan11 = new CSprite("dan11", "dan1");
							dan22 = new CSprite("dan22", "dan2");
							dan33 = new CSprite("dan33", "dan3");
				if (fabs(fSpeedY-0)<=0.001 && IsPressed == false) npc->SetSpriteLinearVelocity(0,0);
				if (FirstStage<=10){
					float PosX = npc->GetSpritePositionX();
					if (PosX>34.7) npc->SetSpritePositionX(34.7);
					attack1->SetSpritePosition(35.684,25.259);
					int Type;
					T4=time(NULL);
					if ((FirstStage == 0 || T4-T3>=0.1) &&!Typed){
					Type=rand()%2+1;
					if (FirstStage == 10) Type = 1;
						if (Type==1){
							dan11 = new CSprite("dan11", "dan1");
							dan22 = new CSprite("dan22", "dan2");
							dan33 = new CSprite("dan33", "dan3");
							dan11->SetSpritePosition(20.399,-3.526);
							dan22->SetSpritePosition(20.181,10.181);
							dan33->SetSpritePosition(20.176,24.809);
							dan11->SetSpriteAutoRot(-750);
							dan22->SetSpriteAutoRot(-750);
							dan33->SetSpriteAutoRot(-750);
							Typed=Type;
							T1=time(NULL);
						}
						if (Type == 2){
							Q1 = new CSprite("Q1", "Q");
							Q2 = new CSprite("Q2","Q");
							Q3 = new CSprite("Q3", "Q");
							Typed=Type;
							dan1=false;
							T1=time(NULL);
						}
					}
					if (Typed){
						if (Typed == 2){
							if (!dan1){
								attack1->AnimateSpritePlayAnimation(  "shotCAnimation", 0 );			
								Q1->SetSpritePosition(23.652,32);			
								Q1->SetSpriteLinearVelocityX(-70);
								dan1=true;
								T2=time(NULL);
							}
							if (dan1 && !dan2 && time(NULL)-T2 > 0.7){
								attack1->AnimateSpritePlayAnimation("shotCAnimation", 0 );			
								Q2->SetSpritePosition(23.652,32);			
								Q2->SetSpriteLinearVelocityX(-70);
								dan2=true;
								T2=time(NULL);
							}
							if (dan1 && dan2 && !dan3 && time(NULL)-T2 > 0.7){
								attack1->AnimateSpritePlayAnimation( "shotCAnimation", 0 );			
								Q3->SetSpritePosition(23.652,32);			
								Q3->SetSpriteLinearVelocityX(-70);
								dan3=true;
								T2=time(NULL);
							}
							// float Pos3 = Q3->GetSpritePositionX();
							// float Speed = Q3->GetSpriteLinearVelocityX();
							if (dan1 && dan2 && dan3 &&time(NULL)-T2>0.1) {
								FirstStage++;
								dan1=false;
								dan2=false;
								dan3=false;
								if (FirstStage == 11) IsEnded =true;
								T3=time(NULL);
								Typed=0;
							}
						}
						if (Typed==1){
							float Speed1 = dan11->GetSpriteLinearVelocityX();
							float Speed2 = dan22->GetSpriteLinearVelocityX();
							float Speed3 = dan33->GetSpriteLinearVelocityX();
							if (!dan1) {
								T2=time(NULL);
								if (T2-T1>=0.4) 
									attack1->AnimateSpritePlayAnimation(  "shotCAnimation", 0 );
								if (T2-T1>=0.5) {
									dan11->SpriteMoveTo(-66.952,40.176,80,1);
									dan1=true;
									T1=time(NULL);
								}
							}
							if (dan1&&!dan2){
								T2=time(NULL);
								if (T2-T1>=0.4) 
									attack1->AnimateSpritePlayAnimation(  "shotCAnimation", 0 );
								if (T2-T1>=0.5) {
									dan22->SpriteMoveTo(-76.359,50.181,80,1);
									dan2=true;
									T1=time(NULL);
								}
							}
							if (dan1&&dan2&&!dan3){
								T2=time(NULL);
								if (T2-T1>=0.4) 
									attack1->AnimateSpritePlayAnimation( "shotCAnimation", 0 );
								if (T2-T1>=0.5){
									dan33->SpriteMoveTo(-58.512,40.399,80,1);
									dan3=true;
								}
							}
							if (dan1 && dan2 && dan3){
								//if (fabs(Speed3 - 0) <= 0.001 && fabs(Speed2 - 0) <= 0.001 && fabs(Speed2 - 0) <= 0.001){
									Typed=0;
									dan1=false;
									dan2=false;
									dan3=false;
									FirstStage++;
									if (FirstStage == 11) IsEnded = true;
									T3=time(NULL);
								//}
							}
						}
					}
				}
				CTextSprite *wenzi;
				wenzi = new CTextSprite("wenzi");
				CSprite *lihui;
				lihui = new CSprite("lihui");
				CAnimateSprite *reimu;
				reimu = new CAnimateSprite("reimu");
				CSprite *point,*test1,*test2;
				point = new CSprite("point");
				test1 = new CSprite("test1");
				test2 = new CSprite("test2");
				if (IsEnded){
				attack1->SetSpritePosition(105.684,37.241);
				if (ST1==false && !T5){//set�����ӡ
					wenzi->SetTextString("[���]�����ӡ");
					lihui->SetSpritePosition(29.310,8.750);
					wenzi->SetSpritePosition(-1.005,-32.500);
					reimu->AnimateSpritePlayAnimation("SpellDAnimation2", 0 );
					T5=time(NULL);
				}
				T6=time(NULL);
				if (ST1==false && (T6-T5)>=1.5){
					reimu->SetSpritePosition(-2,-19.528);
					point->SetSpritePosition(-1.68,-19.177);
					lihui->SetSpritePosition(29.310,66.250);
					wenzi->SetSpritePosition(82.188,-32.500);
					ST1=true;
				}
				if (ST1&&Times<=5){//�����ӡ
				test1->SetSpriteAutoMountRotation(50);
				test1->SetSpriteMountForce(1);
				//dSpriteMountToSprite("point","test",0,0);
				T2=time(NULL);
				if (cnt<=8 && T2-T1>=0.1||cnt == 2){
					reimu->AnimateSpritePlayAnimation("SpellDAnimation2", 0 );
					cnt++;
					char *szName=NULL;
					int type=rand();
					szName=CSystem::MakeSpriteName("test",cnt);
					CSprite *szname;
					szname = new CSprite(szName);
					if (type%2) szname->CloneSprite("test2");
					else szname->CloneSprite("test1");
					int Id1=szname->SpriteMountToSpriteLinkPoint("point",cnt-1);
					//if (dGetSpriteIsMounted(szName)) dSetSpriteLinearVelocity("test",-10,0);
					szname->SetSpriteAngularVelocity(500);
					szname->SetSpriteMountTrackRotation(1);
					szname->SetSpriteAutoMountRotation(15);
					float fposPX=point->GetSpritePositionX();
					float fposPY=point->GetSpritePositionY();
					//dSetSpritePosition(szName,fposPX+20,fposPY+20);
					point->SetSpriteAutoRot(200);
					//dSpriteDismount("test1");
					float fPosY=npc->GetSpritePositionY();
					float fPosX=npc->GetSpritePositionX();
					//dSpriteMoveTo("point",fPosX,fPosY,3,0);
					//Sleep(500);
					T1=time(NULL);
				}
				T4=time(NULL);
				if (cnt==9&&(T4-T3>=0.1||cnt1==2)&&cnt1<=8){
					char *szName=NULL;
					int Cnt=cnt1%8+1;
					//if (T4-T3>=1) dSetSpriteLinearVelocity("test",-10,0);
					CSprite *szname;
					szName=CSystem::MakeSpriteName("test",Cnt);
					szname = new CSprite(szName);
					szname->SetSpriteCollisionPhysicsReceive(1);
					szname->SpriteDismount();
					float fPosY=npc->GetSpritePositionY();
					float fPosX=npc->GetSpritePositionX();
					szname->SpriteMoveTo(fPosX,fPosY,20,0);
					T3=time(NULL);
					cnt1++;
					float iPosX	=	CSystem::RandomRange( CSystem::GetScreenLeft()+15, CSystem::GetScreenRight()-15 );
					float iPosY	=	CSystem::RandomRange( CSystem::GetScreenTop()+10,CSystem::GetScreenTop()+30);
					point->SpriteMoveTo(iPosX,iPosY,20,1);
					reimu->SpriteMoveTo(iPosX,iPosY,20,1);
					reimu->AnimateSpritePlayAnimation(  "dashfrontairAnimation", 0 );
					}
					if (cnt1==8){
						cnt=2;
						cnt1=2;
						Times++;
						T4=time(NULL);
						}
					}
				}
				if (Times == 6 && cnt==2 && cnt1 == 2 && time(NULL) - T4 >=5){
					reimu->SetSpritePosition(81.678,12.211);
					point->SetSpritePosition(81.678,12.211);
					ST1end=true;
				}
				CSprite *marisa,*mari;
				marisa = new CSprite("marisa");
				if (ST2==false && ST1end && !Showed){//set1
					wenzi->SetTextString("[����]shooting star");
					marisa->SetSpritePosition(29.310,8.750);
					wenzi->SetSpritePosition(-1.005,-32.500);
					//dAnimateSpritePlayAnimation( "marisa", "SpellDAnimation2", 0 );
					T5=time(NULL);
					Showed=true;
				}
				if (ST2==false && Showed && (time(NULL)-T5)>=1.5){
					marisa->SetSpritePosition(29.310,66.250);
					wenzi->SetSpritePosition(100,-32.500);
					mari->SetSpritePosition(-0.657,-22.412);
					wenzi->SetTextString("111");
					Seted=false;
					ST2=true;
				}
				if (ST2 && !Seted){//�����׶�1
					for (int i=1;i<=60;i++){
						char *szName=CSystem::MakeSpriteName("Star",i);
						float PosX=CSystem::RandomRange(-46.313,46.313),PosY=CSystem::RandomRange(-33.813,1.313);
						int Col=rand()%4+1;
						char *color = CSystem::MakeSpriteName("star",Col);
						CSprite *szname;
						szname = new CSprite(szName);
						szname->CloneSprite(color);
						szname->SetSpritePosition(PosX,PosY);
						float Y=48.688,X=CSystem::RandomRange(-46.313,46.313);
						float Speed = CSystem::RandomRange(10,30);
						szname->SpriteMoveTo(X,Y,Speed,1);
						szname->SetSpriteAutoRot(-80);
					}
					Seted=true;
					T5=time(NULL);
				}
				if (!Set1&&Seted && time(NULL) - T5 >1){//�����׶�2
					if (Line <=15){
						if (Line == 0 && time(NULL) -T5 >0.5 || time(NULL) -TT >0.3){
							for (int i=1;i<=10;i++){
								cntt++;
								char *szName=CSystem::MakeSpriteName("Stara",cntt);
								CSprite *szname;
								szname = new CSprite(szName);
								szname->CloneSprite("star3");
								szname->SetSpriteAutoRot(-80);
								if (Line & 1) szname->SetSpritePosition(-50+10*i,-31);
								else szname->SetSpritePosition(-60+13*i,-31);
								szname->SetSpriteLinearVelocityY(30);
							}
							Line++;
							TT=time(NULL);
						}
					}
					if (Line == 15) Set1=true;
				}
				if (Set1) {
					mari->SetSpritePosition(82.075,-58.945);
				}
}
