#include "load.h"

int visited1[100][100] = {0};
int visited2[100][100] = {0};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     通过深度搜索更新digitmap，给每个区域标id号，记录面积以及是否为边界
// 参数说明     *tmap           地图结构体指针
// 参数说明     x               深度搜索的起点横坐标
// 参数说明     y               深度搜索的起点纵坐标
// 参数说明     letter          rawmap中所要搜索区域的字母
// 参数说明     id              区域的id
// 返回参数     void
// 使用示例     dfs1(&tmap, 0, 0, 1)                       //从（0，0）处开始搜索，同时给该区域标号为1，记录面积以及是否为边界
// 备注信息     该函数需要配合双层循环使用，当检测到未标号区域时启动此函数
//-------------------------------------------------------------------------------------------------------------------
void dfs1(struct tjMap *tmap, int x, int y, char letter, int id) {
    if (x < 0 || x >= tmap->datasizeH || y < 0 || y >= tmap->datasizeW || visited1[x][y] || tmap->rawMap[x][y] != letter) {
        return;
    }
    if (x == 0 || x == tmap->datasizeH || y == 0 || y == tmap->datasizeW) {
        regions[id].isBorder = 1;
    }
    visited1[x][y] = 1;
    regions[id].area++;
    tmap->digitMap[x][y] = id;
    dfs1(tmap, x - 1, y, letter, id);
    dfs1(tmap, x + 1, y, letter, id);
    dfs1(tmap, x, y - 1, letter, id);
    dfs1(tmap, x, y + 1, letter, id);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     通过深度搜索检测区域之间的邻接关系，并存入邻接矩阵中，1-相邻  0-不相邻
// 参数说明     *tmap           地图结构体指针
// 参数说明     x               深度搜索的起点横坐标
// 参数说明     y               深度搜索的起点纵坐标
// 参数说明     id              区域的id
// 返回参数     void
// 使用示例     dfs1(&tmap,0,0, &tmap, 1)                            //从（0，0）开始搜索id为1区域的相邻区域
// 备注信息     请在dfs1之后使用
//-------------------------------------------------------------------------------------------------------------------
void dfs2(struct tjMap *tmap, int x, int y, int id)
{
    int otherId;
    if (x < 0 || x >= tmap->datasizeH || y < 0 || y >= tmap->datasizeW || visited2[x][y])
        return;
    if (tmap->digitMap[x][y] != id) {
        otherId = tmap->digitMap[x][y];

        adjacencyMatrix[id][otherId] = 1;
        adjacencyMatrix[otherId][id] = 1;
        return;
    }
    visited2[x][y] = 1;
    dfs2(tmap, x - 1, y, id);
    dfs2(tmap, x + 1, y, id);
    dfs2(tmap, x, y - 1, id);
    dfs2(tmap, x, y + 1, id);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     加载地图，在其他文件中只需要使用这个函数
// 参数说明     str0[]           地图文件地址
// 返回参数     void
// 使用示例     loadNewMap()
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void loadNewMap(char str0[])
{
    int id=0;
    char ch;
    int i = 0; // 行索引
    int j = 0; // 列索引
    int m;

    //从文件读取地图数据
    FILE *file = fopen(str0, "r");
     if (!file)             //打不开文件
    {
        perror("File opening failed");
        return;
    }
    while ((ch = fgetc(file)) != EOF && i < 100)// 读取字符直到文件末尾或数组满
    {
        if (ch == '\n')         // 遇到换行符，增加行索引，重置列索引
        {
            i++;
            j=0;
            if (i >= 100) break;
            continue; // 防止数组越界
        }
        tmap.rawMap[i][j] = ch; // 存储字符
        j++; // 增加列索引
        if (j >= 100)
        {
            i++;
            j = 0;
            if (i >= 100) break; // 如果列索引超出100，强制换行，防止数组越界
        }
    }
    tmap.datasizeH = i+1; // 更新地图高度
    tmap.datasizeW = j;   // 更新地图宽度
    fclose(file);


    m = (tmap.datasizeH > tmap.datasizeW) ? tmap.datasizeH : tmap.datasizeW;
    tmap.mapscaleU = 770 / m;  //将地图保持原始比例放大到770x770区域显示


    tmap.areaNum = 0;

    //统计有多少区域并编号，并在digitMap中为每一个元素标记好其所属的区域编号
    for (int i = 0; i < tmap.datasizeH; i++) {
        for (int j = 0; j < tmap.datasizeW; j++) {
            if (visited1[i][j] == 0) {
                dfs1(&tmap, i, j, tmap.rawMap[i][j], id);
                regions[id].id = id;
                id++;
                tmap.areaNum++;
            }
        }
    }
    //确定连接矩阵
    id = 0;
    for (int i = 0; i < tmap.datasizeH; i++) {
        for (int j = 0; j < tmap.datasizeW; j++) {
            if (visited2[i][j] == 0) {
                dfs2(&tmap, i, j, id);
                id++;
            }
        }
    }

    //5.调用updateArea更新
    updateRects(&tmap);
    //6.定义颜色
    tmap.colorlist[0] = 0xFFFFFF; //0号为白色，代表未确定的颜色
    tmap.colorlist[1] = 0xFF0000;
    tmap.colorlist[2] = 0x00FF00;
    tmap.colorlist[3] = 0x0000FF;
    tmap.colorlist[4] = 0xFF00FF;
    tmap.colorlist[5] = 0x000000; //黑色
    tmap.colorlist[6] = 0x888888;//灰色
    //初始化颜色,统一为白色
    for (int i = 0; i < tmap.areaNum; i++)
        tmap.colors[i] = 0;

    //触发绘图更新
    tmap.vcount++;

    //显示一些信息
    char str1[20];
    sprintf(str1, "总区域数：%d", tmap.areaNum);
    appendText(&Info, _T(str1)); //文本显示按钮事件
    ////////////////////////////////输出//////////////////////////////////////
    FILE *file2 = fopen("AreaInformation.txt", "w");
    if (file2 == NULL) {
        printf("无法打开文件\n");
    }

        fprintf(file2, "总区域数: %d\n",tmap.areaNum);
    for (int i = 0; i < tmap.areaNum; i++) {
        if (!regions[i].isBorder) { // 如果区域不是边界区域
            int adjacentCount = 0;   // 邻接区域计数器
            for (int j = 0; j < tmap.areaNum; j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    adjacentCount++;
                }
            }
            if (adjacentCount == 1) { // 如果邻接区域只有一个
                regions[i].isSurrounded = 1; // 标记为被包围区域
            }
        }
        fprintf(file2, "区域 ID: %d, 面积: %d, 是否是边界区域: %d, 是否是被包围区域: %d\n",
                regions[i].id, regions[i].area, regions[i].isBorder, regions[i].isSurrounded);
    }


    fprintf(file2, "\n------------------------邻接表-----------------------\n");
    for (int i = 0; i < tmap.areaNum; i++) {
        fprintf(file2, "区域 %d: ", i);
        for (int j = 0; j < tmap.areaNum; j++) {
            if (adjacencyMatrix[i][j] != 0) { // 假设0表示没有边
                fprintf(file2, "-> %d ", j);
            }
        }
        fprintf(file2, "\n");
    }


    fprintf(file2, "\n------------------------邻接矩阵-----------------------\n   ");
    for(int i=0;i<tmap.areaNum;i++)
    fprintf(file2, "%3d",i);
    fprintf(file2, "\n");
    for (int i = 0; i < tmap.areaNum; i++) {
    fprintf(file2, "%3d",i);
        for (int j = 0; j < tmap.areaNum; j++) {
            fprintf(file2, "%3d", adjacencyMatrix[i][j]);
        }
        fprintf(file2, "\n");
    }

    fclose(file2);
}


