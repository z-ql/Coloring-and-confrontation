#include "pve.h"

int steps;
int max_area=0;
int human = -1, computer = 1;
int pre_chosen[max_steps]={0};
int max_chosen[max_steps]={0};    // id + 1
void init()
{
    for(int i;i<tmap.areaNum;i++)  //��ͼ��ʼ��
{
    regions[i].ocuppied = 0;
}
}
//-------------------------------------------------------------------------------------------------------------------
// �������     �����ģ���������max_steps���ж���Ѱ�������������ѡ������
// ���ز���     void
// ��ע��Ϣ     computer�ĺ��Ĵ���
//-------------------------------------------------------------------------------------------------------------------
void xunhuan(int id,int steps)
{
    int pre_area = 0;
    if(steps==max_steps)  //ȡ������������max_chosen
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
        for(int j=0;j<steps;j++)     //û��Ԥѡ
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
// �������     ��-���Կ���������
// ���ز���     void
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void occupy_PVE()  //ÿ���һ���������һ���µ�ռ��ͶԿ�
{
int chosen_id;
int human = -1, computer = 1;
 player =1;
int finish = 0,finish1,finish2,round=0;         //������־
int xianglin;
//��ʼ��
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
            if(round/2==0)  //����
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
            //�ж��Ƿ���ռ��
            //�ж��Ƿ�ռ��
            if(regions[chosen_id2].ocuppied!=0)
            {
                appendText(&Info, _T("��������Ѿ���ռ�죡"));
                    continue;
            }

            //�ж��Ƿ�����
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
                appendText(&Info, _T("�ⲻ����������"));
                shine(chosen_id2);
                    continue;
            }

            regions[chosen_id2].ocuppied = human;
			tmap.colors[chosen_id2] = (human==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;
            Sleep(30);



        //������
            if(round>=2 && Finish())break;
            }

}
return;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��-����̬�Կ���������
// ���ز���     void
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void dyn_occupy_PVE()  //���һ���������һ���µ�ռ��ͶԿ�
{
int chosen_id;
player =1;
int round=0;         //������־
int xianglin;
//��ʼ��
init();
while (1)
	{
	    char cbtAct=0;
        cbtAct = getNewAction(&colorBtn);
        if(cbtAct==3)break;
	    if(player == computer)
        {
            for(int i=0;i<max_steps;i++)   //��ʼ��
            {
                max_chosen[i]=0;
                pre_chosen[i]=0;
            }
            max_area=0;
            if(round/2==0)  //����
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
            //�ж��Ƿ���ռ��
            //�ж��Ƿ�ռ��
            if(regions[chosen_id2].ocuppied==human)
            {
                appendText(&Info, _T("��������Ѿ�ռ�죡"));
                    continue;
            }

            else if(regions[chosen_id2].ocuppied==-player)
            {

                if(xianglin_area(chosen_id2)!=human)
                {
                appendText(&Info, _T("����������㣬�޷�ռ��"));
                 shine(chosen_id2);
                    continue;
                }
                else
                {
                    regions[chosen_id2].ocuppied = human;
                }
            }
            //�ж��Ƿ�����
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
                appendText(&Info, _T("�ⲻ����������"));

                shine(chosen_id2);
                    continue;
            }

            regions[chosen_id2].ocuppied = human;


            //������
			tmap.colors[chosen_id2] = (human==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;

        //�жϽ���
             if(round>=2 && Finish())break;
        }

}
return;
}
