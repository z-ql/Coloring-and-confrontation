#include "pvp.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     使某区域灰色闪烁
//参数说明      chosen_id             所选区域的id
// 返回参数     void
// 备注信息     在玩家选择错误区域时执行，提醒玩家
//-------------------------------------------------------------------------------------------------------------------
void shine(int chosen_id)
{
                int time=150;
                int area_color = tmap.colors[chosen_id];
                for(int k=0;k<2;k++)
                {
                    tmap.colors[chosen_id] = 6; //灰色
                    tmap.vcount++;
                    Sleep(time);
                    tmap.colors[chosen_id] = area_color; //灰色
                    tmap.vcount++;
                    Sleep(time);
                }
                tmap.colors[chosen_id] = area_color; //灰色
                tmap.vcount++;
                return;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     判断是否结束，同时输出此时双方的面积
// 返回参数     int     0表示未结束    1表示结束
// 备注信息     应该放在执行左键的处理中而不是死循环中，避免重复输出
//-------------------------------------------------------------------------------------------------------------------
int Finish()
{

            int area1=0,area2=0;
            int finish1=1,finish2=1,finish=1;
            for(int m=0;m<tmap.areaNum;m++)
            {
                for(int j=0;j<tmap.areaNum;j++)
                {
                    if((adjacencyMatrix[m][j] == 1 && regions[j].ocuppied==0 && regions[m].ocuppied==1))
                    {
                        finish1 = 0;
                        break;
                    }
                }
            }
             for(int i=0;i<tmap.areaNum;i++)
            {

                for(int j=0;j<tmap.areaNum;j++)
                {
                    if((adjacencyMatrix[i][j] == 1 && regions[j].ocuppied==0 && regions[i].ocuppied==-1))
                    {
                        finish2 = 0;
                        break;
                    }
                }
            }
        for(int i=0;i<tmap.areaNum;i++)
        {
            if(regions[i].ocuppied==0)
            {finish = 0;break;}
        }


        //输出双方目前面积大小
            for(int i=0;i<tmap.areaNum;i++)
            {
                if(regions[i].ocuppied==1)area1+=regions[i].area;
                else if(regions[i].ocuppied==-1)area2+= regions[i].area;
            }
            char str10[50]={};
            sprintf(str10, "白方 %d   黑方 %d", area2,area1);
            appendText(&Info, _T(str10));



	    if(finish || finish1 || finish2)                    //结束
        {
            char *strArray[] = {"黑方胜利！", "白方胜利！"};
                if(area1>area2)
                appendText(&Info, _T(strArray[0]));
                else
                appendText(&Info, _T(strArray[1]));
            return 1;
        }
        else
        {

            return 0;
}
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     比较所选区域的相邻区域被双方占领的面积大小
//参数说明      id             所选区域的id
// 返回参数     int            大的一方
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
int xianglin_area(int id)
{
    int xianglinarea1=0;
    int xianglinarea2=0;
    for(int i=0;i<tmap.areaNum;i++)
    {
        if(adjacencyMatrix[id][i]==1 && regions[i].ocuppied==1)
                xianglinarea1+= regions[i].area;
        else if(adjacencyMatrix[id][i]==1 && regions[i].ocuppied==-1)
                        xianglinarea2 += regions[i].area;
    }
    if(xianglinarea1>xianglinarea2)
        return 1;
    else if(xianglinarea1==xianglinarea2)
        return 0;
    else if(xianglinarea1<xianglinarea2)
        return -1;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     人-人对抗的主函数
// 返回参数     void
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void occupy_PVP()  //每点击一块区域进行一次新的占领和对抗
{
player = 1;
int area1=0,area2=0;                  //统计面积大小
int chosen_area[tmap.areaNum]={0};    //是否被占领标志，不能两次占领
int num_chosen_area = tmap.areaNum;   //判断是否占领完
int finish1 = 0,finish2=0,round=0;         //结束标志
int region1[tmap.areaNum] = {0};      //玩家1占领的区域id+1
int region2[tmap.areaNum] = {0};
int *region;
int xianglin;
init();
while (1)
	{
        char cbtAct=0;
        cbtAct = getNewAction(&colorBtn);
        if(cbtAct==3)break;

        MOUSEMSG msg = GetMouseMsg();
	    if (msg.uMsg==WM_LBUTTONDOWN)
		{
            int chosen_id = xyinArea(msg.x,msg.y,&tmap);

            //判断是否能占领
            int i=0;
            region = (player==1)?region1:region2;
            xianglin = 0;
            while(region[i]!=0)
            {
                    if(adjacencyMatrix[region[i]-1][chosen_id] == 1)
                    {
                        xianglin = 1;
                        break;
                    }

                i++;
            }
            //判断是否被占领
            if(chosen_area[chosen_id]==1)
            {
                appendText(&Info, _T("这块区域已被占领！"));
                    continue;
            }
            if(!xianglin && round/2 >= 1)
            {
                appendText(&Info, _T("这不是相邻区域！"));
                shine(chosen_id);

                    continue;
            }

            regions[chosen_id].ocuppied = player;


            //处理部分
            if(player==1)
            {area1+= regions[chosen_id].area;
            region1[(int)round/2]=chosen_id+1;
            }
            else if(player==-1)
            {area2+= regions[chosen_id].area;
            region2[(int)round/2]=chosen_id+1;}
            num_chosen_area-=1;
            chosen_area[chosen_id]=1;
			tmap.colors[chosen_id] = (player==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;


            //检测是否还有可占领区域
            if(round>=2 && Finish())break;

		}
}
return;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     人-人动态对抗的主函数
// 返回参数     void
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void dyn_occupy_PVP()  //每点击一块区域进行一次新的占领和对抗
{
int chose_id;
player = 1;
int finish = 0,finish1,finish2,round=0;         //结束标志
int *region;
int xianglin;
init();
while (1)
	{
        char cbtAct=0;
        cbtAct = getNewAction(&colorBtn);
        if(cbtAct==3)break;
        MOUSEMSG msg = GetMouseMsg();
	    if (msg.uMsg==WM_LBUTTONDOWN)
		{
            int chosen_id = xyinArea(msg.x,msg.y,&tmap);

            //判断是否能占领

            //判断是否被占领
            if(regions[chosen_id].ocuppied==player)
            {
                appendText(&Info, _T("这块区域已经占领！"));
                    continue;
            }
            else if(regions[chosen_id].ocuppied==-player)
            {

                if(xianglin_area(chosen_id)!=player)
                {
                appendText(&Info, _T("相邻面积不足，无法占领"));
                 shine(chosen_id);

                    continue;
                }
                else
                {
                    regions[chosen_id].ocuppied = player;
                }
            }

            //判断是否相邻
             int i=0;
            xianglin = 0;
            for(int i = 0;i<tmap.areaNum;i++)
            {
                    if(adjacencyMatrix[i][chosen_id] == 1 && regions[i].ocuppied==player)
                    {
                        xianglin = 1;
                        break;
                    }
            }
            if(!xianglin && round/2 >= 1)
            {
                appendText(&Info, _T("这不是相邻区域！"));

                shine(chosen_id);
                    continue;
            }

            regions[chosen_id].ocuppied = player;


            //处理部分
            //颜色更新
			tmap.colors[chosen_id] = (player==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;

        //检测结束
            if(round>=2&&Finish())break;
		}
}
return;
}
