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
//�˽ű����ڸ߼����Գ�����ƿγ�ѧϰ�뽻��

//�����Ҫ���ÿ���̨�����Ϣ����DEBUG����Ϊ1
//�������Ҫ����̨����DEBUG����Ϊ0
#define DEBUG 0

struct tjbutton loadBtn;      //������ص�ͼ��ť��ȫ�ֱ���
struct tjbutton colorBtn;      //������ɫ��ť��ȫ�ֱ���
struct tjbutton battleBtn;      //����Կ���ť��ȫ�ֱ���
struct tjbutton battlePVEBtn;
struct tjbutton changemode;
struct tjbutton mapAreaBtn;
struct multext Info;          //��������ı���ȫ�ֱ���
struct tjMap tmap;            //�����ͼ�ṹ��
int runningMode;

void initMap()
{
    //��ʼ��һЩ��������
    runningMode = -1;
    tmap.maporiginx = 5;
    tmap.maporiginy = 78;
    tmap.areaNum = 0;
    tmap.running = 1;
    tmap.vcount = 0;
    tmap.backimg = _T(".\\bkimg.png"); //����ͼƬ�ļ����ڹ��̵�ǰĿ¼
}

//��ͼ�е�ÿһ����ӳ�䵽��ͼ���󣬶�Ӧһ��С���飬��rect
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


//��ʾ��ͼ
void* showMap(void* args)
{
    #if DEBUG==1
    initgraph(1104, 855,EX_SHOWCONSOLE);     // ��ͼ���ڳ�ʼ��
    #elif DEBUG==0
    initgraph(1104, 855);     // ��ͼ���ڳ�ʼ��
    #endif

    setbkmode(TRANSPARENT);   // �ı�͸��
    IMAGE img;
    loadimage(&img, tmap.backimg); //���ر���ͼƬ

    int areaIndx=0, pIndx = 0;
    int lstvcount = 0;

    ExMessage mess;  //��Ϣ
    bool newmess = false;

    //��ʼ����ť����
    //���ص�ͼ��ť
    loadBtn.pos.x = 940;  //��ť��λ�úʹ�С
    loadBtn.pos.y = 110;
    loadBtn.width = 300;
    loadBtn.height = 40;
    loadBtn.colors[0] = 0xFFFFFF; //��ť�ĸ�״̬�������ɫ�ͱ߿���ɫ
    loadBtn.colors[1] = 0xFFFFFF;
    loadBtn.colors[2] = 0x666666;
    loadBtn.colors[3] = 0xFFFFFF;
    loadBtn.borderColors[0] = 0x666666;
    loadBtn.borderColors[1] = 0x0000FF;
    loadBtn.borderColors[2] = 0x0000FF;
    loadBtn.borderColors[3] = 0x666666;
    loadBtn.textcolor = 0x0000FF;
    loadBtn.textsize = 25;
    loadBtn.text = _T("���ص�ͼ");
    loadBtn.state = 0;
    loadBtn.lststate = 0;
    loadBtn.enable = 1;
    updateBtnRect(&loadBtn);

    //��ʼ����ť����
    //���ص�ͼ��ť
    colorBtn.pos.x = 940;  //��ť��λ�úʹ�С
    colorBtn.pos.y = 170;
    colorBtn.width = 300;
    colorBtn.height = 40;
    colorBtn.colors[0] = 0xFFFFFF; //��ť�ĸ�״̬�������ɫ�ͱ߿���ɫ
    colorBtn.colors[1] = 0xFFFFFF;
    colorBtn.colors[2] = 0x666666;
    colorBtn.colors[3] = 0xFFFFFF;
    colorBtn.borderColors[0] = 0x666666;
    colorBtn.borderColors[1] = 0x0000FF;
    colorBtn.borderColors[2] = 0x0000FF;
    colorBtn.borderColors[3] = 0x666666;
    colorBtn.textcolor = 0x0000FF;
    colorBtn.textsize = 25;
    colorBtn.text = _T("��ɫ/���¿�ʼ");
    colorBtn.state = 0;
    colorBtn.lststate = 0;
    colorBtn.enable = 0;
    updateBtnRect(&colorBtn);

    //��ʼ����ť����
    //���ص�ͼ��ť
    battleBtn.pos.x = 860;  //��ť��λ�úʹ�С
    battleBtn.pos.y = 220;
    battleBtn.width = 140;
    battleBtn.height = 40;
    battleBtn.colors[0] = 0xFFFFFF; //��ť�ĸ�״̬�������ɫ�ͱ߿���ɫ
    battleBtn.colors[1] = 0xFFFFFF;
    battleBtn.colors[2] = 0x666666;
    battleBtn.colors[3] = 0xFFFFFF;
    battleBtn.borderColors[0] = 0x666666;
    battleBtn.borderColors[1] = 0x0000FF;
    battleBtn.borderColors[2] = 0x0000FF;
    battleBtn.borderColors[3] = 0x666666;
    battleBtn.textcolor = 0x0000FF;
    battleBtn.textsize = 25;
    battleBtn.text = _T("���˶Կ�");
    battleBtn.state = 0;
    battleBtn.lststate = 0;
    battleBtn.enable = 0;
    updateBtnRect(&battleBtn);
    //�˻��Կ���ť
    battlePVEBtn.pos.x = 1020;  //��ť��λ�úʹ�С
    battlePVEBtn.pos.y = 220;
    battlePVEBtn.width = 140;
    battlePVEBtn.height = 40;
    battlePVEBtn.colors[0] = 0xFFFFFF; //��ť�ĸ�״̬�������ɫ�ͱ߿���ɫ
    battlePVEBtn.colors[1] = 0xFFFFFF;
    battlePVEBtn.colors[2] = 0x666666;
    battlePVEBtn.colors[3] = 0xFFFFFF;
    battlePVEBtn.borderColors[0] = 0x666666;
    battlePVEBtn.borderColors[1] = 0x0000FF;
    battlePVEBtn.borderColors[2] = 0x0000FF;
    battlePVEBtn.borderColors[3] = 0x666666;
    battlePVEBtn.textcolor = 0x0000FF;
    battlePVEBtn.textsize = 25;
    battlePVEBtn.text = _T("�˻��Կ�");
    battlePVEBtn.state = 0;
    battlePVEBtn.lststate = 0;
    battlePVEBtn.enable = 0;
    updateBtnRect(&battlePVEBtn);

    //�л�ģʽ��ť
    changemode.pos.x = 1020;  //��ť��λ�úʹ�С
    changemode.pos.y = 275;
    changemode.width = 80;
    changemode.height = 30;
    changemode.colors[0] = 0xFFFFFF; //��ť�ĸ�״̬�������ɫ�ͱ߿���ɫ
    changemode.colors[1] = 0xFFFFFF;
    changemode.colors[2] = 0x666666;
    changemode.colors[3] = 0xFFFFFF;
    changemode.borderColors[0] = 0x666666;
    changemode.borderColors[1] = 0x0000FF;
    changemode.borderColors[2] = 0x0000FF;
    changemode.borderColors[3] = 0x666666;
    changemode.textcolor = 0x0000FF;
    changemode.textsize = 20;
    changemode.text = _T("�л�����");
    changemode.state = 0;
    changemode.lststate = 0;
    changemode.enable = 0;
    updateBtnRect(&changemode);

    //��ͼ����Ϊһ����ť
    mapAreaBtn.pos.x = 390;  //��ť��λ�úʹ�С
    mapAreaBtn.pos.y = 463;
    mapAreaBtn.width = 770;
    mapAreaBtn.height = 770;
    mapAreaBtn.text = _T("");
    mapAreaBtn.state = 0;
    mapAreaBtn.lststate = 0;
    mapAreaBtn.enable = 1;
    updateBtnRect(&mapAreaBtn);

    //��ʼ�������ı�
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

    //��ʼ��ͼ
    BeginBatchDraw();  //����˫�����ͼ
    cleardevice();     //�������Ԫ��
    putimage(0,0,&img);//������ͼ
    showButton(&loadBtn);
    showButton(&colorBtn);
    showButton(&battleBtn);
    showButton(&battlePVEBtn);
    showButton(&changemode);
    showMulText(&Info);
    FlushBatchDraw(); //ˢ��

    int r,c,p,colorid;
    RECT rec;
    int width;
    while(tmap.running)
    {
        if(tmap.vcount != lstvcount) //tmap.vcount������ͼ����
        {
            settextstyle(tmap.mapscaleU, 0, _T("arial"));
            settextcolor(0x000000);

            //vcount������ͼ����
            lstvcount = tmap.vcount;
            BeginBatchDraw();  //����˫�����ͼ
            cleardevice();     //�������Ԫ��
            putimage(0,0,&img);//������ͼ

            setlinecolor(0x333333);

            for(r=0;r<tmap.datasizeH;r++)
            {
                for(c=0;c<tmap.datasizeW;c++)
                {

                    p = tmap.digitMap[r][c]; //��ǰ��ͼԪ��ֵ�����õ��Ӧ��������
                    colorid = tmap.colors[p]; //�����ŵ���ɫid��ӳ��
                    setfillcolor(tmap.colorlist[colorid]);//���õ�ǰ�����ɫ

                    rec = tmap.rects[r][c]; //��ǰ���ص�
                    solidrectangle(rec.left,rec.top,rec.right,rec.bottom);

                    }
                    //drawtext(tmap.rawMap[tmp.y][tmp.x], &tmp.rect, DT_CENTER | DT_VCENTER| DT_SINGLELINE);
                }
            //���Ʊ߿�
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


        //��ʾ��ť�Ͷ����ı�
        showButton(&loadBtn);
        showButton(&colorBtn);
        showButton(&battleBtn);
        showButton(&battlePVEBtn);
        showButton(&changemode);
        showMulText(&Info);

        //��ʾ���
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

        FlushBatchDraw(); //ˢ��

        //��������¼� --------------------------------------------------------------------------------------
        newmess = peekmessage(&mess,EX_MOUSE); //��������������¼�

        if(newmess) //���������¼�
        {
            //��ť�¼�
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


int xyinArea(int x,int y,tjMap *tmap) //�����ǰ��������������
{
    int r,c;
    int indx;
    if(x<tmap->maporiginx || x>tmap->maporiginx+770 || y<tmap->maporiginy || y>tmap->maporiginy+770)
        return -1;

    r = (y-tmap->maporiginy)/tmap->mapscaleU;
    c = (x-tmap->maporiginx)/tmap->mapscaleU;
    return tmap->digitMap[r][c];
}
