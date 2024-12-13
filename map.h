#pragma once
#include "tjbutton.h"

//dev by: mrtang
//email:810899799@qq.com
//gitee:guoguomumu
//date:2023.12.12
//此脚本用于高级语言程序设计课程学习与交流

struct tjMap
{
    //rawMap存储地图原始数据，最大支持100x100地图
    char rawMap[100][100];
    //digitMap和rawMap地图数组形状一致，用于记录每一个点所属的区域编号,编号从0开始
    //注意原始地图数据中字符并不能唯一区分区域，不相邻区域也可能使用同样的字符
    int digitMap[100][100];
    int areaNum;     //记录地图中有多少个区域
    int colors[100]; //记录每一个区域对应的颜色，数组下标对应区域编号，数组元素值取值0/1/2/3/4,其中0一般为白色（相当于不上色），1~4对应四种颜色
    int colorlist[7];//采用四色定理，0一般为白色，对应非着色区域，1~4为彩色，对应上色的四种颜色
    int datasizeW;  //实际读入的地图大小：宽
    int datasizeH;  //实际读入的地图大小：高
    int mapscaleU;  //显示区域为770*770，mapscaleU用来将地图放大充满显示区
    int maporiginx; //地图显示区域原点在坐标系中的位置
    int maporiginy;
    int vcount;     //vcount执行一次+1操作，将触发后台更新绘图
    char running;   //控制绘图是否进行
    RECT rects[100][100]; //为每个地图元素对应建立一个像素管理结构体
    LPCTSTR backimg;      //棋盘背景贴图
};
//区域结构体
typedef struct {
    int id = -1;            //区域编号
    int area = 0;           //区域面积
    int isBorder = 0;       //是否为边界区域，默认0（不是）
    int isSurrounded = 0;   //是否为被包围区域，默认0（不是）
    int ocuppied = 0;       //是否被占领，0-没有 1-玩家1 -1-玩家2
} Region;

void initMap(); //初始化地图
void* showMap(void* args); //显示棋盘
void updateRects(struct tjMap *ttmap);
int xyinArea(int x,int y,tjMap *tmap);
