#include "header.h"

Region regions[Maxregions];
int adjacencyMatrix[Maxregions][Maxregions]={0};
char lbtAct    = 0, cbtAct = 0, bbtAct = 0, bbtPVEAct = 0,baAct = 0,changemodeAct=0;
char FILE_[40] = _T(".\\着色地图.txt");
char textBuffer[20];
int curAreaId  = -1;
int player=1;
int changeflag=-1;
int main()
{
    initMap();
    pthread_t th_showmap;  //地图显示在线程中进行
    pthread_create(&th_showmap,NULL,showMap,NULL);
    char lbtAct = 0, cbtAct = 0, bbtAct = 0, baAct = 0,changemodeAct=0;
    int curAreaId = -1;
    char textBuffer[20];


    //主循环
    while(1)
    {
        lbtAct = getNewAction(&loadBtn);
        if(lbtAct == 3)
        {
            //加载地图时，其他按钮不可用
            enableBtn(&colorBtn,0);
            enableBtn(&battleBtn,0);
            enableBtn(&battlePVEBtn,0);
            enableBtn(&changemode,0);
            appendText(&Info,_T("地图加载中......")); //文本显示按钮事件
            loadNewMap(FILE_); //调用loadNewMap来加载地图
            appendText(&Info,_T("地图加载完毕! ")); //文本显示按钮事件
            enableBtn(&colorBtn,1); //加载完地图后，可以涂色
        }


        cbtAct = getNewAction(&colorBtn); //触发着色
        if(cbtAct == 3)
        {
            appendText(&Info,_T("着色中......")); //文本显示按钮事件
            enableBtn(&loadBtn,0);
            enableBtn(&changemode,0);
            enableBtn(&battleBtn,0);
            enableBtn(&battlePVEBtn,0);
            colorateMap(adjacencyMatrix, 4, &tmap, 0);
            appendText(&Info,_T("着色完毕！")); //文本显示按钮事件
            enableBtn(&loadBtn,1);
            enableBtn(&changemode,1);
            enableBtn(&battleBtn,1);
            enableBtn(&battlePVEBtn,1);

        }


        bbtAct = getNewAction(&battleBtn); //PVP
        if(bbtAct == 3)
        {
            enableBtn(&battleBtn,0);
            enableBtn(&battlePVEBtn,0);
            enableBtn(&loadBtn,0);
            enableBtn(&changemode,0);
            appendText(&Info,_T("PVP Fight!")); //文本显示按钮事件
             if(changeflag==1)dyn_occupy_PVP(); //根据不同规则执行不同函数
             else occupy_PVP();
            enableBtn(&battleBtn,1);
            enableBtn(&battlePVEBtn,1);
            enableBtn(&loadBtn,1);
            enableBtn(&changemode,1);
        }

        bbtPVEAct = getNewAction(&battlePVEBtn);
        if(bbtPVEAct == 3)
        {
            enableBtn(&battleBtn,0);
            enableBtn(&battlePVEBtn,0);
            enableBtn(&loadBtn,0);
            enableBtn(&changemode,0);

            appendText(&Info,_T("PVE Fight!"));//文本显示按钮事件
            if(changeflag==1)dyn_occupy_PVE();
            else occupy_PVE();

            enableBtn(&battleBtn,1);
            enableBtn(&battlePVEBtn,1);
            enableBtn(&loadBtn,1);
            enableBtn(&changemode,1);
        }

        changemodeAct = getNewAction(&changemode);
        if(changemodeAct == 3)
        {
               changeflag*= -1;

               if(changeflag==1)
            appendText(&Info,_T("切换模式为动态占领"));
               else if(changeflag==-1)
            appendText(&Info,_T("切换模式为静态占领"));  //文本显示按钮事件

        }
    }
}
