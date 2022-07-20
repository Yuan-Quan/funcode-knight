#ifndef ENEMYANIMATOR_H
#define ENEMYANIMATOR_H
#include <string>
#include "LibParallexScroll.h"
using namespace std;


class EnemyAnimator
{
public:
    EnemyAnimator(const char* name,const int lvl,const int num);
    virtual ~EnemyAnimator();

    // set,get�������ڲ���״̬����
    void            GetFace(int face);
    void set_parallex_instance_(LibParallexScroll* nh);

    //�����Խ�api�Ļص�����
    void            key_press_callback(int key);
    void            key_release_callback(const int key);
    void            get_col_callback(const char* script);

    //������ѭ�������ڸ���״̬��������ȵ�
    void            main_loop(float dt);
    void            main_init(const int lvl);

protected:

private:
    CAnimateSprite* m_pcrawler;                 // ����ʵ��
    CAnimateSprite* m_pcl;                      // ��߽�ʵ��
    CAnimateSprite* m_pcr;                      // �ұ߽�ʵ��
    CAnimateSprite* m_peffect;					// ��Чʵ��
    int             stop;                       // ��ͣ״̬
    int             m_iface;                    // ����״̬��1����-1����
    int             getface;
    int             m_ilvl;                     // �Ѷȵȼ���1���򵥣�2����ͨ��3������
    int             m_icon;                     // ����״̬��0:δ���ˣ�1�����ˣ�2��������ȴ��3������
    float           m_fvel;                     // �����ƶ��ٶ�
    float           m_ftime;                    // ���˺���޵�ʱ��
    int             m_iHP;                      // ����Ѫ������ֵΪ10
    int				m_ieffect;					// ��Ч�ͷ�״̬��0�������ͷţ�1�������ͷţ�
    char*           m_canimation;               // ��¼��ǰ����
    char*           m_ceffectani;               // ��¼��ǰ��Ч����
    char*           nameE;                      // ������
    char*           nameL;                      // ��߽���
    char*           nameR;                      // �ұ߽���
    int             ESC;
    int             ONE;
    int             TWO;
    int             THREE;
    float           SIZE;
    float           INIX;
    float           INIY;
    void            face();
    void            move();
    void            hurt(char* szAnim);
    void            Release(char* szAnim, int LinkPoint);
    void            Animation(char* szAnim);
    void            Delete();
    int             AnimationBreak(char* szAnim);
    void            Show();
    CTextSprite* m_tface;					// faceʾ��
    CTextSprite* m_tcon;					// conʾ��
    CTextSprite* m_tanimation;				// ���ڲ��ŵĶ���
    CTextSprite* m_teffect;					// ���ڲ��ŵ���Ч
    CTextSprite* m_ttime;					// ��ȴ��ʱ
    CTextSprite* m_tHP;	    				// Ѫ��
    LibParallexScroll* parallex_instance_;

};

#endif // ENEMYANIMATOR_H
