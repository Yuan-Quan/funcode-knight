#ifndef KNIGHTANIMATOR_H
#define KNIGHTANIMATOR_H
#include <string>
#include <functional>
using namespace std;


class KnightAnimator
{
    public:
        KnightAnimator( const char* name1 );
        virtual ~KnightAnimator();

        // set,get方法用于操作状态，等
        void			set_keybinds( const int key );
        void            stop_knight();
        void            set_gound_status_handler(function<bool()> fun);

        //用来对接api的回调函数
        void            key_press_callback( const int key );
        void            key_release_callback( const int key );

        //主处理循环，用于更新状态，计算进度等
        void            main_loop( float dt );
        void            refresh();
        void            hit();

    protected:

    private:
        int             stop;                       // 暂停状态
        int				m_imove;					// 朝向状态，1：面向左不动；-1：面向右不动；2：面向左移动；-2：面向右移动；
        int				m_iface;					// 视线状态，0：平视；1：仰视；-1：俯视；
        int				m_ijump;					// 跳跃状态，0：着地到着地；1：贴墙到贴墙；2：滞空；3：二段滞空；
                                                    //			 4：着地到滞空上升；5：贴墙到滞空上升；6:着陆；
        int				m_iattack;					// 攻击状态，0：不攻击；1：攻击A；2：攻击B；
        int				m_imagic;					// 施法状态，0：不施法；1：施法；
        int				m_idash;					// 冲刺状态，0：冲刺待命；1：冲刺；2：不能冲刺；
        int				m_ifocus;					// 聚集状态，0：不聚集；1：聚集；
        int				m_ihurt;					// 受伤状态，0：未受伤；1：受伤；
        int             m_idjump;                   // 二段跳状态，0：跳跃不可用；1：二段跳可用；2：第一段跳跃可也用；
        int				m_ieffect;					// 特效释放状态，0：不可释放；1：可以释放；
        CSprite*        m_pPlaceHolder;
        CAnimateSprite* m_pknight;					// 小骑士实例
        CAnimateSprite* m_peffect;					// 特效实例
        CTextSprite*	m_tmove;					// move示数
        CTextSprite*	m_tface;					// face示数
        CTextSprite*	m_tjump;					// jump示数
        CTextSprite*    m_tdjump;					// djump示数
        CTextSprite*	m_tattack;					// attack示数
        CTextSprite*	m_tmagic;					// magic示数
        CTextSprite*	m_tdash;					// dash示数
        CTextSprite*	m_thurt;					// hurt示数
        CTextSprite*    m_tfocus;					// focus示数
        CTextSprite*    m_teffect;					// efffect示数
        CSound*         m_sslash;					// 劈砍音效
        CSound*         m_sjump;					// 跳跃音效
        float			m_ftime;					// 单程差时
        float           m_fjump;                    // 跳跃计时
        char*           m_canimation;               // 记录当前动画
        char*           m_ceffectani;               // 记录当前特效动画
        int             J;                          // 攻击键
        int             K;                          // 跳跃键
        int             L;                          // 冲刺键
        int             I;                          // 法术键
        int             W;                          // 上键
        int             S;                          // 下键
        int             A;                          // 左键
        int             D;                          // 右键
        int             Q;                          // 聚集键
        int             P;                          // 调试键
        int             ESC;                        // 暂停键
        float           SIZE;                       // 大小
        float           VEL;                        // 你妈的面膜飞行速度
        void			move();
        void			face();
        void			jump();
        void			attack();
        void			magic();
        void			dash();
        void			hurt();
        void            focus();
        void			Release(char* szAnim, int LinkPoint);
        void			Animation(char* szAnim);
        void			Show();
        void			Delete();
        int             AnimationBreak(char* szAnim);
       	std::function<bool()> is_grounded_nh_;
};

#endif // KNIGHTANIMATOR_H
