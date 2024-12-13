#include "header.h"

Region regions[Maxregions];
int adjacencyMatrix[Maxregions][Maxregions]={0};
char lbtAct    = 0, cbtAct = 0, bbtAct = 0, bbtPVEAct = 0,baAct = 0,changemodeAct=0;
char FILE_[40] = _T(".\\��ɫ��ͼ.txt");
char textBuffer[20];
int curAreaId  = -1;
int player=1;
int changeflag=-1;
int main()
{
    initMap();
    pthread_t th_showmap;  //��ͼ��ʾ���߳��н���
    pthread_create(&th_showmap,NULL,showMap,NULL);
    char lbtAct = 0, cbtAct = 0, bbtAct = 0, baAct = 0,changemodeAct=0;
    int curAreaId = -1;
    char textBuffer[20];


    //��ѭ��
    while(1)
    {
        lbtAct = getNewAction(&loadBtn);
        if(lbtAct == 3)
        {
            //���ص�ͼʱ��������ť������
            enableBtn(&colorBtn,0);
            enableBtn(&battleBtn,0);
            enableBtn(&battlePVEBtn,0);
            enableBtn(&changemode,0);
            appendText(&Info,_T("��ͼ������......")); //�ı���ʾ��ť�¼�
            loadNewMap(FILE_); //����loadNewMap�����ص�ͼ
            appendText(&Info,_T("��ͼ�������! ")); //�ı���ʾ��ť�¼�
            enableBtn(&colorBtn,1); //�������ͼ�󣬿���Ϳɫ
        }


        cbtAct = getNewAction(&colorBtn); //������ɫ
        if(cbtAct == 3)
        {
            appendText(&Info,_T("��ɫ��......")); //�ı���ʾ��ť�¼�
            enableBtn(&loadBtn,0);
            enableBtn(&changemode,0);
            enableBtn(&battleBtn,0);
            enableBtn(&battlePVEBtn,0);
            colorateMap(adjacencyMatrix, 4, &tmap, 0);
            appendText(&Info,_T("��ɫ��ϣ�")); //�ı���ʾ��ť�¼�
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
            appendText(&Info,_T("PVP Fight!")); //�ı���ʾ��ť�¼�
             if(changeflag==1)dyn_occupy_PVP(); //���ݲ�ͬ����ִ�в�ͬ����
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

            appendText(&Info,_T("PVE Fight!"));//�ı���ʾ��ť�¼�
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
            appendText(&Info,_T("�л�ģʽΪ��̬ռ��"));
               else if(changeflag==-1)
            appendText(&Info,_T("�л�ģʽΪ��̬ռ��"));  //�ı���ʾ��ť�¼�

        }
    }
}
