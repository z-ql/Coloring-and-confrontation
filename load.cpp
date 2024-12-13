#include "load.h"

int visited1[100][100] = {0};
int visited2[100][100] = {0};

//-------------------------------------------------------------------------------------------------------------------
// �������     ͨ�������������digitmap����ÿ�������id�ţ���¼����Լ��Ƿ�Ϊ�߽�
// ����˵��     *tmap           ��ͼ�ṹ��ָ��
// ����˵��     x               �����������������
// ����˵��     y               ������������������
// ����˵��     letter          rawmap����Ҫ�����������ĸ
// ����˵��     id              �����id
// ���ز���     void
// ʹ��ʾ��     dfs1(&tmap, 0, 0, 1)                       //�ӣ�0��0������ʼ������ͬʱ����������Ϊ1����¼����Լ��Ƿ�Ϊ�߽�
// ��ע��Ϣ     �ú�����Ҫ���˫��ѭ��ʹ�ã�����⵽δ�������ʱ�����˺���
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
// �������     ͨ����������������֮����ڽӹ�ϵ���������ڽӾ����У�1-����  0-������
// ����˵��     *tmap           ��ͼ�ṹ��ָ��
// ����˵��     x               �����������������
// ����˵��     y               ������������������
// ����˵��     id              �����id
// ���ز���     void
// ʹ��ʾ��     dfs1(&tmap,0,0, &tmap, 1)                            //�ӣ�0��0����ʼ����idΪ1�������������
// ��ע��Ϣ     ����dfs1֮��ʹ��
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
// �������     ���ص�ͼ���������ļ���ֻ��Ҫʹ���������
// ����˵��     str0[]           ��ͼ�ļ���ַ
// ���ز���     void
// ʹ��ʾ��     loadNewMap()
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void loadNewMap(char str0[])
{
    int id=0;
    char ch;
    int i = 0; // ������
    int j = 0; // ������
    int m;

    //���ļ���ȡ��ͼ����
    FILE *file = fopen(str0, "r");
     if (!file)             //�򲻿��ļ�
    {
        perror("File opening failed");
        return;
    }
    while ((ch = fgetc(file)) != EOF && i < 100)// ��ȡ�ַ�ֱ���ļ�ĩβ��������
    {
        if (ch == '\n')         // �������з�������������������������
        {
            i++;
            j=0;
            if (i >= 100) break;
            continue; // ��ֹ����Խ��
        }
        tmap.rawMap[i][j] = ch; // �洢�ַ�
        j++; // ����������
        if (j >= 100)
        {
            i++;
            j = 0;
            if (i >= 100) break; // �������������100��ǿ�ƻ��У���ֹ����Խ��
        }
    }
    tmap.datasizeH = i+1; // ���µ�ͼ�߶�
    tmap.datasizeW = j;   // ���µ�ͼ���
    fclose(file);


    m = (tmap.datasizeH > tmap.datasizeW) ? tmap.datasizeH : tmap.datasizeW;
    tmap.mapscaleU = 770 / m;  //����ͼ����ԭʼ�����Ŵ�770x770������ʾ


    tmap.areaNum = 0;

    //ͳ���ж������򲢱�ţ�����digitMap��Ϊÿһ��Ԫ�ر�Ǻ���������������
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
    //ȷ�����Ӿ���
    id = 0;
    for (int i = 0; i < tmap.datasizeH; i++) {
        for (int j = 0; j < tmap.datasizeW; j++) {
            if (visited2[i][j] == 0) {
                dfs2(&tmap, i, j, id);
                id++;
            }
        }
    }

    //5.����updateArea����
    updateRects(&tmap);
    //6.������ɫ
    tmap.colorlist[0] = 0xFFFFFF; //0��Ϊ��ɫ������δȷ������ɫ
    tmap.colorlist[1] = 0xFF0000;
    tmap.colorlist[2] = 0x00FF00;
    tmap.colorlist[3] = 0x0000FF;
    tmap.colorlist[4] = 0xFF00FF;
    tmap.colorlist[5] = 0x000000; //��ɫ
    tmap.colorlist[6] = 0x888888;//��ɫ
    //��ʼ����ɫ,ͳһΪ��ɫ
    for (int i = 0; i < tmap.areaNum; i++)
        tmap.colors[i] = 0;

    //������ͼ����
    tmap.vcount++;

    //��ʾһЩ��Ϣ
    char str1[20];
    sprintf(str1, "����������%d", tmap.areaNum);
    appendText(&Info, _T(str1)); //�ı���ʾ��ť�¼�
    ////////////////////////////////���//////////////////////////////////////
    FILE *file2 = fopen("AreaInformation.txt", "w");
    if (file2 == NULL) {
        printf("�޷����ļ�\n");
    }

        fprintf(file2, "��������: %d\n",tmap.areaNum);
    for (int i = 0; i < tmap.areaNum; i++) {
        if (!regions[i].isBorder) { // ��������Ǳ߽�����
            int adjacentCount = 0;   // �ڽ����������
            for (int j = 0; j < tmap.areaNum; j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    adjacentCount++;
                }
            }
            if (adjacentCount == 1) { // ����ڽ�����ֻ��һ��
                regions[i].isSurrounded = 1; // ���Ϊ����Χ����
            }
        }
        fprintf(file2, "���� ID: %d, ���: %d, �Ƿ��Ǳ߽�����: %d, �Ƿ��Ǳ���Χ����: %d\n",
                regions[i].id, regions[i].area, regions[i].isBorder, regions[i].isSurrounded);
    }


    fprintf(file2, "\n------------------------�ڽӱ�-----------------------\n");
    for (int i = 0; i < tmap.areaNum; i++) {
        fprintf(file2, "���� %d: ", i);
        for (int j = 0; j < tmap.areaNum; j++) {
            if (adjacencyMatrix[i][j] != 0) { // ����0��ʾû�б�
                fprintf(file2, "-> %d ", j);
            }
        }
        fprintf(file2, "\n");
    }


    fprintf(file2, "\n------------------------�ڽӾ���-----------------------\n   ");
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


