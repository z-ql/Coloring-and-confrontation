#include "multext.h"
#include "string.h"

//dev by: mrtang
//email:810899799@qq.com
//gitee:guoguomumu
//date:2023.12.12
//此脚本用于高级语言程序设计课程学习与交流

//向多行文本数组中添加一条字符串
void appendText(multext *mt, char *text)
{
    if(mt->curIndex == mt->maxsize) //已经满了，则从头来
        mt->curIndex = 0;

    strcpy(mt->strs[mt->curIndex++],text);
}

//显示多行文本
void showMulText(multext *mt)
{
    setbkcolor(mt->bkcolor);
    clearrectangle(mt->rect.left,mt->rect.top,mt->rect.right,mt->rect.bottom);

    settextstyle(mt->textsize, 0, _T("arial"));
    settextcolor(mt->textcolor);

    int u = (int)mt->textsize * 1; //1倍行距
    for(int i=0;i<mt->curIndex;i++)
    {
        mt->crec.top = mt->rect.top + i * u;
        drawtext(mt->strs[i], &mt->crec, DT_LEFT | DT_TOP| DT_SINGLELINE);
    }
}

