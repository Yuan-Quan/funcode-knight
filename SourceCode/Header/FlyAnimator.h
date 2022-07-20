#ifndef FLYANIMATOR_H
#define FLYANIMATOR_H
#include <string>
#include "LibParallexScroll.h"
using namespace std;


class FlyAnimator
{
public:
    FlyAnimator(const char* name, const int lvl, const int num);
    virtual ~FlyAnimator();

    // set,get方法用于操作状态，等
    void            GetFace(int face);
    void set_parallex_instance_(LibParallexScroll* nh);

    //用来对接api的回调函数
    void            key_press_callback(int key);
    void            key_release_callback(const int key);
    void            get_col_callback(const char* script);

    //主处理循环，用于更新状态，计算进度等
    void update_knight_pos();
    void            main_loop(float dt);
    void            main_init(const int lvl);

protected:

private:
    CSprite* m_pKnight = new CSprite("knight_placholder");
    CAnimateSprite* m_pfly;                     // 蚊子实例
    CAnimateSprite* m_pa;                      // 边界实例
    CAnimateSprite* m_peffect;					// 特效实例
    int             stop;                       // 暂停状态
    int             m_iface;                    // 朝向状态，1：左；-1：右
    int             getface;
    int             m_ilvl;                     // 难度等级，1：简单；2：普通；3：困难
    int             m_icon;                     // 蚊子状态，0:未受伤；1：受伤；2：受伤冷却；3：死亡
    float           m_fvel;                     // 蚊子移动速度
    float           m_ftime;                    // 受伤后的无敌时间
    float           m_fmtime;                   // 移动时间
    int             m_iHP;                      // 蚊子血量，初值为10
    int				m_ieffect;					// 特效释放状态，0：不可释放；1：可以释放；
    char*           m_canimation;               // 记录当前动画
    char*           m_ceffectani;               // 记录当前特效动画
    char*           nameF;                      // 怪物名
    char*           nameA;                      // 边界名
    int             ESC;
    int             ONE;
    int             TWO;
    int             THREE;
    float           KnightPosX;
    float           KnightPosY;
    float           hHIGHT;
    float           hWIDTH;
    void            face();
    void            move();
    void            hurt();
    void            Animation(char* szAnim);
    void            Show();
    CTextSprite*    m_tface;					// face示数
    CTextSprite*    m_tcon;					    // con示数
    CTextSprite*    m_tanimation;				// 正在播放的动画
    CTextSprite*    m_ttime;					// 冷却计时
    CTextSprite*    m_tHP;	    				// 血量
    LibParallexScroll* parallex_instance_;

};

#endif // FLYANIMATOR_H
