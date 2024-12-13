#include "color.h"
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     判断某个区域能否涂某个颜色
// 参数说明     v               区域id（int）
// 参数说明     graph           二维邻接矩阵（0表示不连接，1表示相连接）
// 参数说明     tmap            地图结构体指针
// 参数说明     c               颜色代号 范围是[1,4]
// 返回参数     int             0表示不能填，1表示能填
// 使用示例     isSafe(0, graph, &tmap, 1)                            //根据graph判断0区域能否填入颜色1
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
int isSafe(int v, int graph[Maxregions][Maxregions], struct tjMap *tmap, int c)
{
    for (int i = 0; i < tmap->areaNum; i++) {
        if (graph[v][i] && c == tmap->colors[i]) {
            return 0;
        }
    }
    return 1;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     迭代函数给所有区域填上合适的颜色
// 参数说明     graph           二维邻接矩阵（0表示不连接，1表示相连接）
// 参数说明     m               最大颜色数，填上的颜色id范围为[1,m],最小为4
// 参数说明     tmap            地图结构体指针
// 参数说明     v               该次迭代的区域id 范围[0,Maxregions]
// 返回参数     int             0表示不能填，1表示能填
// 使用示例     colorateMap(graph, 4, &tmap, 0)//根据graph判断从0开始所有区域的填色，最大颜色数为4
// 备注信息     在其他文件中使用四色定理，只需要调用这个函数
//-------------------------------------------------------------------------------------------------------------------
int colorateMap(int graph[Maxregions][Maxregions], int m, struct tjMap *tmap, int v)
{
    if (v == tmap->areaNum) {
        return 1;
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, tmap, c)) {
            tmap->colors[v] = c;
            tmap->vcount++;
            Sleep(10);              //控制着色过程快慢
            if (colorateMap(graph, m, tmap, v + 1)) {
                return 1;
            }

            tmap->colors[v] = 0; // 回溯
        }
    }

    return 0;

}
