#pragma once
#include "tjbutton.h"

//dev by: mrtang
//email:810899799@qq.com
//gitee:guoguomumu
//date:2023.12.12
//�˽ű����ڸ߼����Գ�����ƿγ�ѧϰ�뽻��

struct tjMap
{
    //rawMap�洢��ͼԭʼ���ݣ����֧��100x100��ͼ
    char rawMap[100][100];
    //digitMap��rawMap��ͼ������״һ�£����ڼ�¼ÿһ����������������,��Ŵ�0��ʼ
    //ע��ԭʼ��ͼ�������ַ�������Ψһ�������򣬲���������Ҳ����ʹ��ͬ�����ַ�
    int digitMap[100][100];
    int areaNum;     //��¼��ͼ���ж��ٸ�����
    int colors[100]; //��¼ÿһ�������Ӧ����ɫ�������±��Ӧ�����ţ�����Ԫ��ֵȡֵ0/1/2/3/4,����0һ��Ϊ��ɫ���൱�ڲ���ɫ����1~4��Ӧ������ɫ
    int colorlist[7];//������ɫ����0һ��Ϊ��ɫ����Ӧ����ɫ����1~4Ϊ��ɫ����Ӧ��ɫ��������ɫ
    int datasizeW;  //ʵ�ʶ���ĵ�ͼ��С����
    int datasizeH;  //ʵ�ʶ���ĵ�ͼ��С����
    int mapscaleU;  //��ʾ����Ϊ770*770��mapscaleU��������ͼ�Ŵ������ʾ��
    int maporiginx; //��ͼ��ʾ����ԭ��������ϵ�е�λ��
    int maporiginy;
    int vcount;     //vcountִ��һ��+1��������������̨���»�ͼ
    char running;   //���ƻ�ͼ�Ƿ����
    RECT rects[100][100]; //Ϊÿ����ͼԪ�ض�Ӧ����һ�����ع���ṹ��
    LPCTSTR backimg;      //���̱�����ͼ
};
//����ṹ��
typedef struct {
    int id = -1;            //������
    int area = 0;           //�������
    int isBorder = 0;       //�Ƿ�Ϊ�߽�����Ĭ��0�����ǣ�
    int isSurrounded = 0;   //�Ƿ�Ϊ����Χ����Ĭ��0�����ǣ�
    int ocuppied = 0;       //�Ƿ�ռ�죬0-û�� 1-���1 -1-���2
} Region;

void initMap(); //��ʼ����ͼ
void* showMap(void* args); //��ʾ����
void updateRects(struct tjMap *ttmap);
int xyinArea(int x,int y,tjMap *tmap);
