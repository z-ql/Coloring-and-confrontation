#pragma once
#include <graphics.h>
//dev by: mrtang
//email:810899799@qq.com
//gitee:guoguomumu
//date:2023.12.12
//此脚本用于高级语言程序设计课程学习与交流

struct position
{
    int x;
    int y;
};

struct tjbutton
{
    struct position pos;
    int enable;
    int width;
    int height;
    char state;     //0无动作 1获得鼠标焦点 2鼠标按下 3鼠标弹起
    char lststate;  //上一次状态
    int colors[4];
    int borderColors[4];
    RECT rect;
    int textcolor;
    int textsize;
    struct position mousePos; //记录鼠标点击的位置
    LPCTSTR text;
};

void updateBtnRect(struct tjbutton *btn); //更新按键的rect
char onButton(struct tjbutton *btn, int x, int y); //鼠标悬停
char updateBtnState(ExMessage mess, struct tjbutton *btn); //获取按键的最新状态
char showButton(struct tjbutton *btn); //绘制按键
char getNewAction(struct tjbutton *btn); //获取按钮新事件，触发型
void enableBtn(struct tjbutton *btn, int val);
