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

        // set,get�������ڲ���״̬����
        void			set_keybinds( const int key );
        void            stop_knight();
        void            set_gound_status_handler(function<bool()> fun);

        //�����Խ�api�Ļص�����
        void            key_press_callback( const int key );
        void            key_release_callback( const int key );

        //������ѭ�������ڸ���״̬��������ȵ�
        void            main_loop( float dt );
        void            refresh();
        void            hit();

    protected:

    private:
        int             stop;                       // ��ͣ״̬
        int				m_imove;					// ����״̬��1�������󲻶���-1�������Ҳ�����2���������ƶ���-2���������ƶ���
        int				m_iface;					// ����״̬��0��ƽ�ӣ�1�����ӣ�-1�����ӣ�
        int				m_ijump;					// ��Ծ״̬��0���ŵص��ŵأ�1����ǽ����ǽ��2���Ϳգ�3�������Ϳգ�
                                                    //			 4���ŵص��Ϳ�������5����ǽ���Ϳ�������6:��½��
        int				m_iattack;					// ����״̬��0����������1������A��2������B��
        int				m_imagic;					// ʩ��״̬��0����ʩ����1��ʩ����
        int				m_idash;					// ���״̬��0����̴�����1����̣�2�����ܳ�̣�
        int				m_ifocus;					// �ۼ�״̬��0�����ۼ���1���ۼ���
        int				m_ihurt;					// ����״̬��0��δ���ˣ�1�����ˣ�
        int             m_idjump;                   // ������״̬��0����Ծ�����ã�1�����������ã�2����һ����Ծ��Ҳ�ã�
        int				m_ieffect;					// ��Ч�ͷ�״̬��0�������ͷţ�1�������ͷţ�
        CSprite*        m_pPlaceHolder;
        CAnimateSprite* m_pknight;					// С��ʿʵ��
        CAnimateSprite* m_peffect;					// ��Чʵ��
        CTextSprite*	m_tmove;					// moveʾ��
        CTextSprite*	m_tface;					// faceʾ��
        CTextSprite*	m_tjump;					// jumpʾ��
        CTextSprite*    m_tdjump;					// djumpʾ��
        CTextSprite*	m_tattack;					// attackʾ��
        CTextSprite*	m_tmagic;					// magicʾ��
        CTextSprite*	m_tdash;					// dashʾ��
        CTextSprite*	m_thurt;					// hurtʾ��
        CTextSprite*    m_tfocus;					// focusʾ��
        CTextSprite*    m_teffect;					// efffectʾ��
        CSound*         m_sslash;					// ������Ч
        CSound*         m_sjump;					// ��Ծ��Ч
        float			m_ftime;					// ���̲�ʱ
        float           m_fjump;                    // ��Ծ��ʱ
        char*           m_canimation;               // ��¼��ǰ����
        char*           m_ceffectani;               // ��¼��ǰ��Ч����
        int             J;                          // ������
        int             K;                          // ��Ծ��
        int             L;                          // ��̼�
        int             I;                          // ������
        int             W;                          // �ϼ�
        int             S;                          // �¼�
        int             A;                          // ���
        int             D;                          // �Ҽ�
        int             Q;                          // �ۼ���
        int             P;                          // ���Լ�
        int             ESC;                        // ��ͣ��
        float           SIZE;                       // ��С
        float           VEL;                        // �������Ĥ�����ٶ�
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
