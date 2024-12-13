#include "tjbutton.h"

//dev by: mrtang
//email:810899799@qq.com
//gitee:guoguomumu
//date:2023.12.12
//此脚本用于高级语言程序设计课程学习与交流

//依据按钮的位置和尺寸来更新按钮的rect, rect是判定鼠标悬停的边界
void updateBtnRect(struct tjbutton *btn)
{
    btn->rect.left = (long)btn->pos.x - btn->width/2;
    btn->rect.top = (long)btn->pos.y - btn->height/2;
    btn->rect.right = (long)btn->pos.x + btn->width/2;
    btn->rect.bottom = (long)btn->pos.y + btn->height/2;
}

//依据鼠标的xy坐标和按钮的rect判定是否有鼠标悬停
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

//综合鼠标悬停和鼠标点击动作来判定按钮的四个状态
//return value: 0 无动作 1 鼠标悬停 2鼠标按下 3鼠标弹起
char updateBtnState(ExMessage mess, struct tjbutton *btn)
{
    if(!btn->enable)
        return 0;

    if(onButton(btn,mess.x,mess.y))  //鼠标悬停
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
        btn->state = 0;  //状态0 无动作
    return btn->state;
}

//通过跟踪前后两次的按钮状态变化来捕获一个新事件
char getNewAction(struct tjbutton *btn)
{
    if(btn->state != btn->lststate) //按键状态发生了改变
    {
        btn->lststate = btn->state;
        return btn->state;
    }
    else  //按钮状态没有改变
        return 0;
}


//绘制按钮，依据按钮的状态决定其填充颜色和边框颜色
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

