#ifndef TUTORIAL_H
#define TUTORIAL_H
#include <string>
#include "LibParallexScroll.h"
using namespace std;


class Tutorial
{
public:
    Tutorial(const char* name);
    virtual ~Tutorial();

    // set,get�������ڲ���״̬����
    void            GetFace(int face);

    //�����Խ�api�Ļص�����
    void            key_press_callback(int key);
    void            key_release_callback(const int key);
    void            get_col_callback(const char* script);

    //������ѭ�������ڸ���״̬��������ȵ�
    void            main_loop(float dt);
    void            main_init();

protected:

private:
    CStaticSprite*        m_ptutorial;
    int             stop;
    int             ESC;
    int             color;
    int             touch;
    int             calpha;
    int             getface;
    int             iface;
    void            armory();
};

#endif // TUTORIAL_H
