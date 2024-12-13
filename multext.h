#pragma once
#include <graphics.h>

//dev by: mrtang
//email:810899799@qq.com
//gitee:guoguomumu
//date:2023.12.12
//此脚本用于高级语言程序设计课程学习与交流

//多行文本
struct multext
{
    char strs[100][100];//二维字符数组，最多管理100个字符串,实际管理的数量可由maxsize来裁剪
    RECT rect;  //多行文本的rect区域
    RECT crec;  //用于动态调整多行打印时的rect
    int textsize;
    int textcolor;
    int curIndex;
    int maxsize;  //最多打印的文本数，超过则清空
    int bkcolor;
};

void initMulText(multext *mt);            //初始化多行文本
void appendText(multext *mt, char *text); //添加一条文本
void showMulText(multext *mt);            //显示文本
