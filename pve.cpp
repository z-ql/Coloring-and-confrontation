#include "pve.h"

int steps;
int max_area=0;
int human = -1, computer = 1;
int pre_chosen[max_steps]={0};
int max_chosen[max_steps]={0};    // id + 1
void init()
{
    for(int i;i<tmap.areaNum;i++)  //地图初始化
{
    regions[i].ocuppied = 0;
}
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     计算机模拟接下来的max_steps步行动，寻找能让面积最大的选择区域
// 返回参数     void
// 备注信息     computer的核心代码
//-------------------------------------------------------------------------------------------------------------------
void xunhuan(int id,int steps)
{
    int pre_area = 0;
    if(steps==max_steps)  //取最大面积，更新max_chosen
    {
        for(int j=0;j<max_steps;j++)
        {
            if(pre_chosen[j]==0)break;
            pre_area+=regions[pre_chosen[j]-1].area;
        }
        if(pre_area>max_area)
        {
            max_area=pre_area;

            for(int i=0;i<max_steps;i++)
            {if(pre_chosen[i]==0)break;
                max_chosen[i]=pre_chosen[i];
            }
        }
        return;
    }
    int flag2=1;
    for(int i=0;i<tmap.areaNum;i++)
    {
        int flag=0,flag1=0;
        for(int j=0;j<steps;j++)     //没有预选
        {
            if(i==pre_chosen[j]-1)
                {
                    flag=1;
                    break;}
            else if(adjacencyMatrix[i][pre_chosen[j]-1]==1)flag1=1;
        }
        if(flag)continue;

        if((adjacencyMatrix[id][i]==1||flag1) && regions[i].ocuppied==0)
            {
                flag2=0;
                pre_chosen[steps]=i+1;
                xunhuan(i,steps+1);

            }
    }
    if(flag2)
    {
        xunhuan(0,max_steps);
    }
    pre_chosen[steps]=0;
    return;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     人-机对抗的主函数
// 返回参数     void
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void occupy_PVE()  //每点击一块区域进行一次新的占领和对抗
{
int chosen_id;
int human = -1, computer = 1;
 player =1;
int finish = 0,finish1,finish2,round=0;         //结束标志
int xianglin;
//初始化
init();
while (1)
	{
	    char cbtAct=0;
        cbtAct = getNewAction(&colorBtn);
        if(cbtAct==3)break;
	    if(player == computer)
        {
            for(int i=0;i<max_steps;i++)
            {
                max_chosen[i]=0;
            }
            max_area=0;
            if(round/2==0)  //开局
            {
            for(int i=0;i<tmap.areaNum;i++)
                if(regions[i].ocuppied==0 && regions[i].area>max_area)
                    {chosen_id=i;
                    max_area = regions[i].area;
            }
            }

            else
            {

            for(int i=0;i<tmap.areaNum;i++)
            {
                if(regions[i].ocuppied==computer)
                {
                    steps=0;
                    xunhuan(i,steps);
                }
            }
            chosen_id = max_chosen[0]-1;
            }
            regions[chosen_id].ocuppied = computer;
            tmap.colors[chosen_id] = (player==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;
        }

        MOUSEMSG msg = GetMouseMsg();
	    if (msg.uMsg==WM_LBUTTONDOWN && player == human)
		{
            int chosen_id2 = xyinArea(msg.x,msg.y,&tmap);
            printf("%d",xyinArea(msg.x,msg.y,&tmap));
            //判断是否能占领
            //判断是否被占领
            if(regions[chosen_id2].ocuppied!=0)
            {
                appendText(&Info, _T("这块区域已经被占领！"));
                    continue;
            }

            //判断是否相邻
            xianglin = 0;
            for(int k = 0;k<tmap.areaNum;k++)
            {
                    if(adjacencyMatrix[k][chosen_id2] == 1 && regions[k].ocuppied==human)
                    {
                        xianglin = 1;
                        break;
                    }
            }
            if(!xianglin && round/2 >= 1)
            {
                appendText(&Info, _T("这不是相邻区域！"));
                shine(chosen_id2);
                    continue;
            }

            regions[chosen_id2].ocuppied = human;
			tmap.colors[chosen_id2] = (human==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;
            Sleep(30);



        //检测结束
            if(round>=2 && Finish())break;
            }

}
return;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     人-机动态对抗的主函数
// 返回参数     void
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void dyn_occupy_PVE()  //点击一块区域进行一次新的占领和对抗
{
int chosen_id;
player =1;
int round=0;         //结束标志
int xianglin;
//初始化
init();
while (1)
	{
	    char cbtAct=0;
        cbtAct = getNewAction(&colorBtn);
        if(cbtAct==3)break;
	    if(player == computer)
        {
            for(int i=0;i<max_steps;i++)   //初始化
            {
                max_chosen[i]=0;
                pre_chosen[i]=0;
            }
            max_area=0;
            if(round/2==0)  //开局
            {
            for(int i=0;i<tmap.areaNum;i++)
                if(regions[i].ocuppied==0 && regions[i].area>max_area)
                    {chosen_id=i;
                    max_area = regions[i].area;
            }
            }

            else
            {

            for(int i=0;i<tmap.areaNum;i++)
            {
                if(regions[i].ocuppied==computer)
                {
                    steps=0;
                    xunhuan(i,steps);
                }
            }
            chosen_id = max_chosen[0]-1;
            for(int l=0;l<tmap.areaNum;l++)
            {

                if(regions[l].ocuppied==human && xianglin_area(l)==1)
                {
                    chosen_id=l;
                }
            }
            Sleep(300);
            }
            regions[chosen_id].ocuppied = computer;
            tmap.colors[chosen_id] = (player==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;
        }

        MOUSEMSG msg = GetMouseMsg();
	    if (msg.uMsg==WM_LBUTTONDOWN && player == human)
		{
            int chosen_id2 = xyinArea(msg.x,msg.y,&tmap);
            //判断是否能占领
            //判断是否被占领
            if(regions[chosen_id2].ocuppied==human)
            {
                appendText(&Info, _T("这块区域已经占领！"));
                    continue;
            }

            else if(regions[chosen_id2].ocuppied==-player)
            {

                if(xianglin_area(chosen_id2)!=human)
                {
                appendText(&Info, _T("相邻面积不足，无法占领"));
                 shine(chosen_id2);
                    continue;
                }
                else
                {
                    regions[chosen_id2].ocuppied = human;
                }
            }
            //判断是否相邻
             int i=0;
            xianglin = 0;
            for(int k = 0;k<tmap.areaNum;k++)
            {
                    if(adjacencyMatrix[k][chosen_id2] == 1 && regions[k].ocuppied==human)
                    {
                        xianglin = 1;
                        break;
                    }
            }
            if(!xianglin && round/2 >= 1)
            {
                appendText(&Info, _T("这不是相邻区域！"));

                shine(chosen_id2);
                    continue;
            }

            regions[chosen_id2].ocuppied = human;


            //处理部分
			tmap.colors[chosen_id2] = (human==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;

        //判断结束
             if(round>=2 && Finish())break;
        }

}
return;
}
