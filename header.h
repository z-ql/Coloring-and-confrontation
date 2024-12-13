#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define Maxregions 200
#define max_steps 3
#include "map.h"
#include <conio.h>
#include <pthread.h>
#include "tjbutton.h"
#include "multext.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "map.h"
#include "load.h"
#include "color.h"
#include "pvp.h"
#include "pve.h"

extern struct tjbutton loadBtn;
extern struct tjbutton colorBtn;
extern struct tjbutton battleBtn;
extern struct tjbutton battlePVEBtn;
extern struct tjbutton changemode;
extern struct tjbutton mapAreaBtn;
extern struct multext Info;
extern struct tjMap tmap;
extern int runningMode;
extern Region regions[Maxregions];                      //区域结构体数组
extern int adjacencyMatrix[Maxregions][Maxregions];     //连接矩阵
extern int steps;
extern int player;
extern int max_area;
extern int pre_chosen[max_steps];
extern int max_chosen[max_steps];    // id + 1
#endif // HEADER_H_INCLUDED
