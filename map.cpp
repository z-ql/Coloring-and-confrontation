#include <conio.h>
#include <time.h>
#include "map.h"
#include "tjbutton.h"
#include "multext.h"
#include "string.h"
#include "map.h"
#include <stdio.h>
#include "header.h"
//dev by: mrtang
//email:810899799@qq.com
//gitee:guoguomumu
//date:2023.12.12
//此脚本用于高级语言程序设计课程学习与交流

//如果需要利用控制台输出信息，则将DEBUG定义为1
//如果不需要控制台，则将DEBUG定义为0
#define DEBUG 0

struct tjbutton loadBtn;      //定义加载地图按钮，全局变量
struct tjbutton colorBtn;      //定义着色按钮，全局变量
struct tjbutton battleBtn;      //定义对抗按钮，全局变量
struct tjbutton battlePVEBtn;
struct tjbutton changemode;
struct tjbutton mapAreaBtn;
struct multext Info;          //定义多行文本，全局变量
struct tjMap tmap;            //定义地图结构体
int runningMode;

void initMap()
{
    //初始化一些基本参数
    runningMode = -1;
    tmap.maporiginx = 5;
    tmap.maporiginy = 78;
    tmap.areaNum = 0;
    tmap.running = 1;
    tmap.vcount = 0;
    tmap.backimg = _T(".\\bkimg.png"); //棋盘图片文件放在工程当前目录
}

//地图中的每一个点映射到绘图区后，对应一个小方块，即rect
void updateRects(struct tjMap *ttmap)
{
    for(int r=0;r<ttmap->datasizeH;r++)
    {
        for(int c=0;c<ttmap->datasizeW;c++)
        {
            ttmap->rects[r][c].left = 10+c*ttmap->mapscaleU+ttmap->maporiginx;
            ttmap->rects[r][c].right = 10+(c+1)*ttmap->mapscaleU+ttmap->maporiginx;
            ttmap->rects[r][c].top = 10+r*ttmap->mapscaleU+ttmap->maporiginy;
            ttmap->rects[r][c].bottom = 10+(r+1)*ttmap->mapscaleU+ttmap->maporiginy;
        }
    }
}


//显示地图
void* showMap(void* args)
{
    #if DEBUG==1
    initgraph(1104, 855,EX_SHOWCONSOLE);     // 绘图窗口初始化
    #elif DEBUG==0
    initgraph(1104, 855);     // 绘图窗口初始化
    #endif

    setbkmode(TRANSPARENT);   // 文本透明
    IMAGE img;
    loadimage(&img, tmap.backimg); //加载背景图片

    int areaIndx=0, pIndx = 0;
    int lstvcount = 0;

    ExMessage mess;  //消息
    bool newmess = false;

    //初始化按钮布局
    //加载地图按钮
    loadBtn.pos.x = 940;  //按钮的位置和大小
    loadBtn.pos.y = 110;
    loadBtn.width = 300;
    loadBtn.height = 40;
    loadBtn.colors[0] = 0xFFFFFF; //按钮四个状态的填充颜色和边框颜色
    loadBtn.colors[1] = 0xFFFFFF;
    loadBtn.colors[2] = 0x666666;
    loadBtn.colors[3] = 0xFFFFFF;
    loadBtn.borderColors[0] = 0x666666;
    loadBtn.borderColors[1] = 0x0000FF;
    loadBtn.borderColors[2] = 0x0000FF;
    loadBtn.borderColors[3] = 0x666666;
    loadBtn.textcolor = 0x0000FF;
    loadBtn.textsize = 25;
    loadBtn.text = _T("加载地图");
    loadBtn.state = 0;
    loadBtn.lststate = 0;
    loadBtn.enable = 1;
    updateBtnRect(&loadBtn);

    //初始化按钮布局
    //加载地图按钮
    colorBtn.pos.x = 940;  //按钮的位置和大小
    colorBtn.pos.y = 170;
    colorBtn.width = 300;
    colorBtn.height = 40;
    colorBtn.colors[0] = 0xFFFFFF; //按钮四个状态的填充颜色和边框颜色
    colorBtn.colors[1] = 0xFFFFFF;
    colorBtn.colors[2] = 0x666666;
    colorBtn.colors[3] = 0xFFFFFF;
    colorBtn.borderColors[0] = 0x666666;
    colorBtn.borderColors[1] = 0x0000FF;
    colorBtn.borderColors[2] = 0x0000FF;
    colorBtn.borderColors[3] = 0x666666;
    colorBtn.textcolor = 0x0000FF;
    colorBtn.textsize = 25;
    colorBtn.text = _T("着色/重新开始");
    colorBtn.state = 0;
    colorBtn.lststate = 0;
    colorBtn.enable = 0;
    updateBtnRect(&colorBtn);

    //初始化按钮布局
    //加载地图按钮
    battleBtn.pos.x = 860;  //按钮的位置和大小
    battleBtn.pos.y = 220;
    battleBtn.width = 140;
    battleBtn.height = 40;
    battleBtn.colors[0] = 0xFFFFFF; //按钮四个状态的填充颜色和边框颜色
    battleBtn.colors[1] = 0xFFFFFF;
    battleBtn.colors[2] = 0x666666;
    battleBtn.colors[3] = 0xFFFFFF;
    battleBtn.borderColors[0] = 0x666666;
    battleBtn.borderColors[1] = 0x0000FF;
    battleBtn.borderColors[2] = 0x0000FF;
    battleBtn.borderColors[3] = 0x666666;
    battleBtn.textcolor = 0x0000FF;
    battleBtn.textsize = 25;
    battleBtn.text = _T("人人对抗");
    battleBtn.state = 0;
    battleBtn.lststate = 0;
    battleBtn.enable = 0;
    updateBtnRect(&battleBtn);
    //人机对抗按钮
    battlePVEBtn.pos.x = 1020;  //按钮的位置和大小
    battlePVEBtn.pos.y = 220;
    battlePVEBtn.width = 140;
    battlePVEBtn.height = 40;
    battlePVEBtn.colors[0] = 0xFFFFFF; //按钮四个状态的填充颜色和边框颜色
    battlePVEBtn.colors[1] = 0xFFFFFF;
    battlePVEBtn.colors[2] = 0x666666;
    battlePVEBtn.colors[3] = 0xFFFFFF;
    battlePVEBtn.borderColors[0] = 0x666666;
    battlePVEBtn.borderColors[1] = 0x0000FF;
    battlePVEBtn.borderColors[2] = 0x0000FF;
    battlePVEBtn.borderColors[3] = 0x666666;
    battlePVEBtn.textcolor = 0x0000FF;
    battlePVEBtn.textsize = 25;
    battlePVEBtn.text = _T("人机对抗");
    battlePVEBtn.state = 0;
    battlePVEBtn.lststate = 0;
    battlePVEBtn.enable = 0;
    updateBtnRect(&battlePVEBtn);

    //切换模式按钮
    changemode.pos.x = 1020;  //按钮的位置和大小
    changemode.pos.y = 275;
    changemode.width = 80;
    changemode.height = 30;
    changemode.colors[0] = 0xFFFFFF; //按钮四个状态的填充颜色和边框颜色
    changemode.colors[1] = 0xFFFFFF;
    changemode.colors[2] = 0x666666;
    changemode.colors[3] = 0xFFFFFF;
    changemode.borderColors[0] = 0x666666;
    changemode.borderColors[1] = 0x0000FF;
    changemode.borderColors[2] = 0x0000FF;
    changemode.borderColors[3] = 0x666666;
    changemode.textcolor = 0x0000FF;
    changemode.textsize = 20;
    changemode.text = _T("切换规则");
    changemode.state = 0;
    changemode.lststate = 0;
    changemode.enable = 0;
    updateBtnRect(&changemode);

    //绘图区视为一个按钮
    mapAreaBtn.pos.x = 390;  //按钮的位置和大小
    mapAreaBtn.pos.y = 463;
    mapAreaBtn.width = 770;
    mapAreaBtn.height = 770;
    mapAreaBtn.text = _T("");
    mapAreaBtn.state = 0;
    mapAreaBtn.lststate = 0;
    mapAreaBtn.enable = 1;
    updateBtnRect(&mapAreaBtn);

    //初始化多行文本
    Info.rect.top = 350;
    Info.rect.left = 800;
    Info.rect.right = 1080;
    Info.rect.bottom = 815;
    Info.crec = Info.rect;
    Info.curIndex = 0;
    Info.maxsize = 15;
    Info.textcolor = 0x000000;
    Info.textsize = 20;
    Info.bkcolor = RGB(195,195,195);
    strcpy(Info.strs[Info.curIndex],"");

    int modex = 940, modey = 275;

    //初始绘图
    BeginBatchDraw();  //开启双缓冲绘图
    cleardevice();     //清空所有元素
    putimage(0,0,&img);//贴背景图
    showButton(&loadBtn);
    showButton(&colorBtn);
    showButton(&battleBtn);
    showButton(&battlePVEBtn);
    showButton(&changemode);
    showMulText(&Info);
    FlushBatchDraw(); //刷新

    int r,c,p,colorid;
    RECT rec;
    int width;
    while(tmap.running)
    {
        if(tmap.vcount != lstvcount) //tmap.vcount触发绘图更新
        {
            settextstyle(tmap.mapscaleU, 0, _T("arial"));
            settextcolor(0x000000);

            //vcount触发绘图更新
            lstvcount = tmap.vcount;
            BeginBatchDraw();  //开启双缓冲绘图
            cleardevice();     //清空所有元素
            putimage(0,0,&img);//贴背景图

            setlinecolor(0x333333);

            for(r=0;r<tmap.datasizeH;r++)
            {
                for(c=0;c<tmap.datasizeW;c++)
                {

                    p = tmap.digitMap[r][c]; //当前地图元素值，即该点对应的区域编号
                    colorid = tmap.colors[p]; //区域编号到颜色id号映射
                    setfillcolor(tmap.colorlist[colorid]);//设置当前填充颜色

                    rec = tmap.rects[r][c]; //当前像素点
                    solidrectangle(rec.left,rec.top,rec.right,rec.bottom);

                    }
                    //drawtext(tmap.rawMap[tmp.y][tmp.x], &tmp.rect, DT_CENTER | DT_VCENTER| DT_SINGLELINE);
                }
            //绘制边框
            //setfillcolor(0x000000);
            //rectangle(tmap.maporiginx,tmap.maporiginy,tmap.maporiginx+tmap.datasizeW*tmap.mapscaleU,tmap.maporiginy+tmap.datasizeH*tmap.mapscaleU);
            for(r=0;r<tmap.datasizeH;r++)
            {
                for(c=0;c<tmap.datasizeW;c++)
                {

                    rec = tmap.rects[r][c];
                    setfillcolor(0x666666);
                    if(c==0)solidrectangle(rec.left-1,rec.top,rec.left+1,rec.bottom);
                    if(c==tmap.datasizeW-1)solidrectangle(rec.right-1,rec.top-1,rec.right+1,rec.bottom+1);
                    if(r==0)solidrectangle(rec.left-1,rec.top-1,rec.right+1,rec.top+1);
                    if(r==tmap.datasizeH-1)solidrectangle(rec.left-1,rec.bottom-1,rec.right+1,rec.bottom+1);
                          if(c!=tmap.datasizeW-1)
                    {
                        if(tmap.digitMap[r][c] != tmap.digitMap[r][c+1])
                        {
                        setfillcolor(0x666666);
                        width = 1;
                        //solidrectangle(rec.right-width,rec.top-1,rec.right+width,rec.bottom+1);

                        solidrectangle(rec.right-width,rec.top,rec.right+width,rec.bottom);
                        }
                        else
                        {
                        setfillcolor(0x000000);
                        width = 0.5;
                        //solidrectangle(rec.right-width,rec.top,rec.right+width,rec.bottom);
                        }
                    }
                    if(r!=tmap.datasizeH-1)
                    {
                         if (tmap.digitMap[r][c] != tmap.digitMap[r+1][c])
                        {
                        setfillcolor(0x666666);
                        width = 1;
                        solidrectangle(rec.left,rec.bottom-width,rec.right,rec.bottom+width);
                        }
                        else
                        {
                            setfillcolor(0x000000);
                             width = 0.5;
                            // solidrectangle(rec.left-1,rec.bottom-width,rec.right+1,rec.bottom+width);
                            // solidrectangle(rec.left,rec.bottom-width,rec.right,rec.bottom+width);
                        }
                    }
                }
            }
            }


        //显示按钮和多行文本
        showButton(&loadBtn);
        showButton(&colorBtn);
        showButton(&battleBtn);
        showButton(&battlePVEBtn);
        showButton(&changemode);
        showMulText(&Info);

        //显示玩家
        switch(player)
        {
            case -1:
                setfillcolor(0xFFFFFF);
                solidcircle(modex,modey,16);
                break;
            case 1:
                setfillcolor(0x000000);
                solidcircle(modex,modey,16);
                break;
        }

        FlushBatchDraw(); //刷新

        //处理鼠标事件 --------------------------------------------------------------------------------------
        newmess = peekmessage(&mess,EX_MOUSE); //非阻塞捕获鼠标事件

        if(newmess) //如果有鼠标事件
        {
            //按钮事件
            updateBtnState(mess,&loadBtn);
            updateBtnState(mess,&colorBtn);
            updateBtnState(mess,&battleBtn);
            updateBtnState(mess,&battlePVEBtn);
            updateBtnState(mess,&changemode);
            updateBtnState(mess,&mapAreaBtn);
        }
        Sleep(5);
    }
	closegraph();
	return NULL;
}


int xyinArea(int x,int y,tjMap *tmap) //从鼠标前搜索所属的区域
{
    int r,c;
    int indx;
    if(x<tmap->maporiginx || x>tmap->maporiginx+770 || y<tmap->maporiginy || y>tmap->maporiginy+770)
        return -1;

    r = (y-tmap->maporiginy)/tmap->mapscaleU;
    c = (x-tmap->maporiginx)/tmap->mapscaleU;
    return tmap->digitMap[r][c];
}
