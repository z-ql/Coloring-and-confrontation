#include "pvp.h"

//-------------------------------------------------------------------------------------------------------------------
// �������     ʹĳ�����ɫ��˸
//����˵��      chosen_id             ��ѡ�����id
// ���ز���     void
// ��ע��Ϣ     �����ѡ���������ʱִ�У��������
//-------------------------------------------------------------------------------------------------------------------
void shine(int chosen_id)
{
                int time=150;
                int area_color = tmap.colors[chosen_id];
                for(int k=0;k<2;k++)
                {
                    tmap.colors[chosen_id] = 6; //��ɫ
                    tmap.vcount++;
                    Sleep(time);
                    tmap.colors[chosen_id] = area_color; //��ɫ
                    tmap.vcount++;
                    Sleep(time);
                }
                tmap.colors[chosen_id] = area_color; //��ɫ
                tmap.vcount++;
                return;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �ж��Ƿ������ͬʱ�����ʱ˫�������
// ���ز���     int     0��ʾδ����    1��ʾ����
// ��ע��Ϣ     Ӧ�÷���ִ������Ĵ����ж�������ѭ���У������ظ����
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


        //���˫��Ŀǰ�����С
            for(int i=0;i<tmap.areaNum;i++)
            {
                if(regions[i].ocuppied==1)area1+=regions[i].area;
                else if(regions[i].ocuppied==-1)area2+= regions[i].area;
            }
            char str10[50]={};
            sprintf(str10, "�׷� %d   �ڷ� %d", area2,area1);
            appendText(&Info, _T(str10));



	    if(finish || finish1 || finish2)                    //����
        {
            char *strArray[] = {"�ڷ�ʤ����", "�׷�ʤ����"};
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
// �������     �Ƚ���ѡ�������������˫��ռ��������С
//����˵��      id             ��ѡ�����id
// ���ز���     int            ���һ��
// ��ע��Ϣ
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
// �������     ��-�˶Կ���������
// ���ز���     void
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void occupy_PVP()  //ÿ���һ���������һ���µ�ռ��ͶԿ�
{
player = 1;
int area1=0,area2=0;                  //ͳ�������С
int chosen_area[tmap.areaNum]={0};    //�Ƿ�ռ���־����������ռ��
int num_chosen_area = tmap.areaNum;   //�ж��Ƿ�ռ����
int finish1 = 0,finish2=0,round=0;         //������־
int region1[tmap.areaNum] = {0};      //���1ռ�������id+1
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

            //�ж��Ƿ���ռ��
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
            //�ж��Ƿ�ռ��
            if(chosen_area[chosen_id]==1)
            {
                appendText(&Info, _T("��������ѱ�ռ�죡"));
                    continue;
            }
            if(!xianglin && round/2 >= 1)
            {
                appendText(&Info, _T("�ⲻ����������"));
                shine(chosen_id);

                    continue;
            }

            regions[chosen_id].ocuppied = player;


            //������
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


            //����Ƿ��п�ռ������
            if(round>=2 && Finish())break;

		}
}
return;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��-�˶�̬�Կ���������
// ���ز���     void
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void dyn_occupy_PVP()  //ÿ���һ���������һ���µ�ռ��ͶԿ�
{
int chose_id;
player = 1;
int finish = 0,finish1,finish2,round=0;         //������־
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

            //�ж��Ƿ���ռ��

            //�ж��Ƿ�ռ��
            if(regions[chosen_id].ocuppied==player)
            {
                appendText(&Info, _T("��������Ѿ�ռ�죡"));
                    continue;
            }
            else if(regions[chosen_id].ocuppied==-player)
            {

                if(xianglin_area(chosen_id)!=player)
                {
                appendText(&Info, _T("����������㣬�޷�ռ��"));
                 shine(chosen_id);

                    continue;
                }
                else
                {
                    regions[chosen_id].ocuppied = player;
                }
            }

            //�ж��Ƿ�����
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
                appendText(&Info, _T("�ⲻ����������"));

                shine(chosen_id);
                    continue;
            }

            regions[chosen_id].ocuppied = player;


            //������
            //��ɫ����
			tmap.colors[chosen_id] = (player==1?5:0);
            tmap.vcount++;
            player = -1*player;
            round++;

        //������
            if(round>=2&&Finish())break;
		}
}
return;
}
