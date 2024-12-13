#include "tjbutton.h"

//dev by: mrtang
//email:810899799@qq.com
//gitee:guoguomumu
//date:2023.12.12
//�˽ű����ڸ߼����Գ�����ƿγ�ѧϰ�뽻��

//���ݰ�ť��λ�úͳߴ������°�ť��rect, rect���ж������ͣ�ı߽�
void updateBtnRect(struct tjbutton *btn)
{
    btn->rect.left = (long)btn->pos.x - btn->width/2;
    btn->rect.top = (long)btn->pos.y - btn->height/2;
    btn->rect.right = (long)btn->pos.x + btn->width/2;
    btn->rect.bottom = (long)btn->pos.y + btn->height/2;
}

//��������xy����Ͱ�ť��rect�ж��Ƿ��������ͣ
char onButton(struct tjbutton *btn,int x, int y)
{
    if(x > btn->rect.left && x < btn->rect.right && y > btn->rect.top && y < btn->rect.bottom)
        return 1;
    else
        return 0;
}

 void enableBtn(struct tjbutton *btn, int val)
 {
    btn->enable = val;
 }

//�ۺ������ͣ��������������ж���ť���ĸ�״̬
//return value: 0 �޶��� 1 �����ͣ 2��갴�� 3��굯��
char updateBtnState(ExMessage mess, struct tjbutton *btn)
{
    if(!btn->enable)
        return 0;

    if(onButton(btn,mess.x,mess.y))  //�����ͣ
    {
        btn->mousePos.x = mess.x;
        btn->mousePos.y = mess.y;

        btn->state = 1;
        switch(mess.message)
        {
            case WM_LBUTTONDOWN:
                btn->state = 2;
                break;
            case WM_LBUTTONUP:
                btn->state = 3;
                break;
        }
    }
    else
        btn->state = 0;  //״̬0 �޶���
    return btn->state;
}

//ͨ������ǰ�����εİ�ť״̬�仯������һ�����¼�
char getNewAction(struct tjbutton *btn)
{
    if(btn->state != btn->lststate) //����״̬�����˸ı�
    {
        btn->lststate = btn->state;
        return btn->state;
    }
    else  //��ť״̬û�иı�
        return 0;
}


//���ư�ť�����ݰ�ť��״̬�����������ɫ�ͱ߿���ɫ
char showButton(struct tjbutton *btn)
{
    if(!btn->enable)
    {
        setfillcolor(0x555555);
        solidrectangle(btn->rect.left,btn->rect.top,btn->rect.right,btn->rect.bottom);
        settextcolor(btn->textcolor);
        settextstyle(btn->textsize, 0, _T("arial"));
        drawtext(btn->text, &(btn->rect), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        return 0;
    }


    setlinestyle(PS_SOLID, 2);
    setlinecolor(btn->borderColors[btn->state]);
    setfillcolor(btn->colors[btn->state]);
    fillrectangle(btn->rect.left,btn->rect.top,btn->rect.right,btn->rect.bottom);
    settextcolor(btn->textcolor);
    settextstyle(btn->textsize, 0, _T("arial"));
    drawtext(btn->text, &(btn->rect), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    return 1;
}

