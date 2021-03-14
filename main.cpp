#include <graphics.h>
#include <mmsystem.h>
#include <winbgim.h>
#include <cstring>
#define MAX 50
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#define infinit INT_MAX
#define epsi 0.0001
#define  MAX 100
#define MAX1 20

using namespace std;

ifstream f("maxim.in");
ofstream out("schema.out");

int BLACKNOU=COLOR(18,18,18);
int GREY=COLOR(30,30,30);
int PURPLE=COLOR(151,69,252);
int YELLOWP=COLOR(251,228,116);
int REDP=COLOR(229,116,121);
int GREENP=COLOR(102,200,149);
int FINISH=COLOR(89,32,159);
bool exista=0;
int mat[15][15];
int hrectangle=40,htriunghi=60;
int vs=95,wc=140,wi=110,wt=112;
int nr_Blocuri=0;
int oks=1;
int nr_leg=0,nr_leg_total;
int ox=830,oy=95;
int cx=830, cy=315;
bool nrstop=0;
bool okd;
int maxim_stanga=800,maxim_dreapta=0;

struct memory
{
    int x,y;
    int val,nr_cif;
    char str[10];
} mem[30];

struct punct
{
    int x,y;
};

struct linii
{
    punct p1,p2;
};

struct elem
{
    punct pct1,pct2,pct3,pct4;
    int width;
    int nr;
    char id;
    punct mc1, mc2, mc3;
    int v1=-1,v2=-1,v3=-1;
    char var[50];
    int dim;
    bool dr_imd;
    bool lin; //daca are sau nu linie st/dreapta
    bool st,dr; //daca e pe if si este in partea stanga sau dreapta
} v[10];

struct nod
{
    elem info;
    nod *st;
    nod *dr;
}*start;

void citesteSir_INTRARE(char s[MAX],int x, int y)
{
    strcpy(s,"");
    char s1[MAX];
    char t[2];
    char tasta;
    t[0]=tasta;
    t[1]='\0';
    strcat(s,t);
    strcpy(s1,s);
    strcat(s1,"");
    setcolor(WHITE);
    outtextxy(x,y,s1);
    do
    {
        tasta=getch();
        if (tasta==8) // backspace
            if (strlen(s)>0)
            {
                setcolor(WHITE);
                strcpy(s1,s);
                strcat(s1,"");
                outtextxy(x,y,s1);
                s[strlen(s)-1]='\0';
                strcpy(s1,s);
                strcat(s1,"");
                outtextxy(x,y,s1);
                setcolor(WHITE);
                outtextxy(x,y,s1);
            }
            else
                Beep(1000,100);
        else if(tasta!=13)
        {
            t[0]=tasta;
            t[1]='\0';
            strcat(s,t);
            strcpy(s1,s);
            strcat(s1,"");
            setcolor(WHITE);
            outtextxy(x,y,s1);
        }
    }
    while (tasta!=13);
    t[0]=tasta;
    t[1]='\0';
    strcat(s,t);
    strcpy(s1,s);
    setcolor(WHITE);
    outtextxy(x,y,s1);
    s[strlen(s)-1]='\0';
}

void trapez_iesire(int x1,int y1,int x2,int y2,int cul) //iesire
{
    setcolor(cul);
    line(x1,y1,x2-20,y1);
    line(x2-20,y1,x2,y2);
    line(x2,y2,x1-20,y2);
    line(x1-20,y2,x1,y1);
    setfillstyle(1,cul);
    floodfill(x1+20,y1+10,cul);
}

void trapez_intrare(int x1,int y1,int x2,int y2,int cul) //intrare
{
    setcolor(cul);
    line(x1,y1,x2+20,y1);
    line(x2+20,y1,x2,y2);
    line(x2,y2,x1+20,y2);
    line(x1+20,y2,x1,y1);
    setfillstyle(1,cul);
    floodfill(x1+20,y1+10,cul);
}

void linie_st(int i,int j,int cul)
{
    //j e blocul de sus
    setcolor(cul);
    line(maxim_stanga-30,v[j].mc1.y-5,v[j].mc1.x,v[j].mc1.y-5);
    line(maxim_stanga-30,v[i].mc2.y+10,maxim_stanga-30,v[j].mc1.y-5);
    line(maxim_stanga-30,v[i].mc2.y+10,v[i].mc2.x,v[i].mc2.y+10);
    line(v[i].mc2.x,v[i].mc2.y,v[i].mc2.x,v[i].mc2.y+10);
}

void linie_dr(int i,int j,int cul)
{
    //j e blocul de sus
    setcolor(cul);
    line(maxim_dreapta+30,v[j].mc1.y-5,v[j].mc1.x,v[j].mc1.y-5);
    line(maxim_dreapta+30,v[i].mc2.y+10,maxim_dreapta+30,v[j].mc1.y-5);
    line(maxim_dreapta+30,v[i].mc2.y+10,v[i].mc2.x,v[i].mc2.y+10);
    line(v[i].mc2.x,v[i].mc2.y,v[i].mc2.x,v[i].mc2.y+10);
}

void triunghi(int x1,int y1,int x2,int y2,int x3,int y3,int cul)
{
    int arr[]= {x1,y1,x2,y2,x3,y3,x1,y1};
    setcolor(cul);
    setfillstyle(1,cul);
    line(x1,y1,x2,y2);
    line(x1,y1,x3,y3);
    line(x2,y2,x3,y3);
    fillpoly(4,arr);
}

void interfata()
{
    setbkcolor(BLACKNOU);
    setcolor(GREY);
    setfillstyle(1,GREY);
    bar(20,20,790,580);
    bar(810,20,1180,280);
    bar(20,600,790,780);
    bar(810,300,1180,780);
    setcolor(PURPLE);
    setfillstyle(1,PURPLE);
    bar(50,35,150,75);
    bar(170,35,270,75);
    bar(290,35,390,75);
    bar(410,35,510,75);
    bar(530,35,630,75);
    bar(650,35,750,75);
    bar(830,35,985,85);
    bar(1005,35,1160,85);
    setcolor(BLACK);
    setbkcolor(PURPLE);
    settextstyle(8,0,1.5);
    outtextxy(70,45,"START");
    outtextxy(180,45,"INTRARE");
    outtextxy(310,45,"CALCUL");
    outtextxy(420,45,"DECIZIE");
    outtextxy(545,45,"IESIRE");
    outtextxy(675,45,"STOP");
    outtextxy(875,40,"OPRIRE");
    outtextxy(865,60,"DESENARE");
    outtextxy(1050,40,"OPRIRE");
    outtextxy(1045,60,"SCRIERE");
}
void deseneaza_START(int x1,int y1,int x2,int y2,int m,int cul)
{
    setcolor(cul);
    setfillstyle(1,cul);
    bar(x1,y1,x2,y2);
    setcolor(WHITE);
    setbkcolor(cul);
    outtextxy(x1+20,y1+10,"START");
    v[m].pct1.x=x1;
    v[m].pct1.y=y1;
    v[m].pct2.x=x1;
    v[m].pct2.y=y1+hrectangle;
    v[m].pct3.x=x2;
    v[m].pct3.y=y2-hrectangle;
    v[m].pct4.x=x2;
    v[m].pct4.y=y2;
    v[m].mc2.x=(x2-x1)/2+x1;
    v[m].mc2.y=y2;
    setcolor(YELLOWP);
    setfillstyle(1,YELLOWP);
    circle((x2-x1)/2+x1,y2,7);
    floodfill((x2-x1)/2+x1,y2,YELLOWP);
    if(v[m].pct1.x<maxim_stanga)
        maxim_stanga=v[m].pct1.x;
    if(v[m].pct4.x>maxim_dreapta)
        maxim_dreapta=v[m].pct4.x;
}

void START(int x1,int y1,int x2,int y2)
{
    deseneaza_START(x1,y1,x2,y2,nr_Blocuri,PURPLE);
    v[nr_Blocuri].id='S';
    v[nr_Blocuri].width=vs;
    v[nr_Blocuri].nr=0;
    nr_leg_total++;
}

void deseneaza_INTRARE(int x1,int y1,int x2,int y2,int m,char sir[],int cul)
{
    trapez_intrare(x1,y1,x2,y2,cul);
    setcolor(WHITE);
    setbkcolor(cul);
    outtextxy(x1+45,y1+10,sir);
    v[m].pct1.x=x1;
    v[m].pct1.y=y1;
    v[m].pct2.x=x1+20;
    v[m].pct2.y=y2;
    v[m].pct3.x=x2+20;
    v[m].pct3.y=y1;
    v[m].pct4.x=x2;
    v[m].pct4.y=y2;
    v[m].mc1.x=(x2-x1+20)/2+x1;
    v[m].mc1.y=y1;
    v[m].mc2.x=(x2-x1+20)/2+x1;
    v[m].mc2.y=y2;
    setcolor(WHITE);
    setfillstyle(1,WHITE);
    circle((x2-x1+20)/2+x1,y1,7);
    floodfill((x2-x1+20)/2+x1,y1,WHITE);
    setcolor(YELLOWP);
    setfillstyle(1,YELLOWP);
    circle((x2-x1+20)/2+x1,y2,7);
    floodfill((x2-x1+20)/2+x1,y2,YELLOWP);
    if(v[m].pct1.x<maxim_stanga)
        maxim_stanga=v[m].pct1.x;
    if(v[m].pct3.x>maxim_dreapta)
        maxim_dreapta=v[m].pct3.x;
}

void intrare(int x1,int y1,int x2,int y2)
{
    nr_Blocuri++;
    v[nr_Blocuri].id='I';
    deseneaza_INTRARE(x1,y1,x2,y2,nr_Blocuri,"",PURPLE);
    v[nr_Blocuri].width=vs;
    v[nr_Blocuri].nr=nr_Blocuri;
    nr_leg_total++;
}

void deseneaza_CALCUL(int x1,int y1,int x2,int y2,int m, char sir[], int cul)
{
    setcolor(cul);
    setfillstyle(1,cul);
    bar(x1,y1,x2,y2);
    setcolor(BLACK);
    setbkcolor(cul);
    setcolor(WHITE);
    outtextxy(x1+(v[m].width-v[m].dim*11)/2,y1+10,sir);
    v[m].pct1.x=x1;
    v[m].pct1.y=y1;
    v[m].pct2.x=x1;
    v[m].pct2.y=y1+hrectangle;
    v[m].pct3.x=x2;
    v[m].pct3.y=y2-hrectangle;
    v[m].pct4.x=x2;
    v[m].pct4.y=y2;
    v[m].mc1.x=(x2-x1)/2+x1;
    v[m].mc1.y=y1;
    v[m].mc2.x=(x2-x1)/2+x1;
    v[m].mc2.y=y2;
    setcolor(WHITE);
    setfillstyle(1,WHITE);
    circle((x2-x1)/2+x1,y1,7);
    floodfill((x2-x1)/2+x1,y1,WHITE);
    setcolor(YELLOWP);
    setfillstyle(1,YELLOWP);
    circle((x2-x1)/2+x1,y2,7);
    floodfill((x2-x1)/2+x1,y2,YELLOWP);
    if(v[m].pct1.x<maxim_stanga)
        maxim_stanga=v[m].pct1.x;
    if(v[m].pct4.x>maxim_dreapta)
        maxim_dreapta=v[m].pct4.x;
}

void calcul(int x1,int y1,int x2,int y2)
{
    nr_Blocuri++;
    v[nr_Blocuri].id='C';
    deseneaza_CALCUL(x1,y1,x2,y2,nr_Blocuri, "", PURPLE);
    v[nr_Blocuri].width=wc;
    v[nr_Blocuri].nr=nr_Blocuri;
    nr_leg_total++;
}

void deseneaza_DECIZIE(int x1,int y1,int x2,int y2,int x3,int y3,int m,char sir[], int cul)
{
    triunghi(x1,y1,x2,y2,x3,y3,cul);
    setcolor(BLACK);
    setbkcolor(cul);
    v[m].pct1.x=x1;
    v[m].pct1.y=y1;
    v[m].pct2.x=x2;
    v[m].pct2.y=y2;
    v[m].pct3.x=x3;
    v[m].pct3.y=y3;
    v[m].pct4.x=-1;
    v[m].pct4.y=-1;
    v[m].mc1.x=x1;
    v[m].mc1.y=y1;
    v[m].mc2.x=x2;
    v[m].mc2.y=y2;
    v[m].mc3.x=x3;
    v[m].mc3.y=y3;
    setcolor(WHITE);
    outtextxy((v[m].width-v[m].dim*10)/2+v[m].pct2.x-5,y1+35,sir);
    setcolor(WHITE);
    setfillstyle(1,WHITE);
    circle(x1,y1,7);
    floodfill(x1,y1,WHITE);
    setcolor(YELLOWP);
    setfillstyle(1,YELLOWP);
    circle(x2,y2,7);
    floodfill(x2,y2,YELLOWP);
    setcolor(YELLOWP);
    setfillstyle(1,YELLOWP);
    circle(x3,y3,7);
    floodfill(x3,y3,YELLOWP);
    if(v[m].pct2.x<maxim_stanga)
        maxim_stanga=v[m].pct2.x;
    if(v[m].pct3.x>maxim_dreapta)
        maxim_dreapta=v[m].pct3.x;
}

void decizie(int x1,int y1,int x2,int y2,int x3,int y3)
{
    nr_Blocuri++;
    v[nr_Blocuri].id='D';
    deseneaza_DECIZIE(x1,y1,x2,y2,x3,y3,nr_Blocuri,"", PURPLE);
    v[nr_Blocuri].width=wt;
    v[nr_Blocuri].nr=nr_Blocuri;
    oks++;
    nr_leg_total++;
    nr_leg_total++;
}

void deseneaza_IESIRE(int x1,int y1,int x2,int y2,int m,char sir[],int cul)
{
    trapez_iesire(x1,y1,x2,y2,cul);
    setcolor(BLACK);
    setbkcolor(cul);
    setcolor(WHITE);
    outtextxy(x1+17,y1+10,sir);
    v[m].pct1.x=x1;
    v[m].pct1.y=y1;
    v[m].pct2.x=x1-20;
    v[m].pct2.y=y2;
    v[m].pct3.x=x2-20;
    v[m].pct3.y=y1;
    v[m].pct4.x=x2;
    v[m].pct4.y=y2;
    v[m].mc1.x=(x2-x1-20)/2+x1;
    v[m].mc1.y=y1;
    v[m].mc2.x=(x2-x1-20)/2+x1;
    v[m].mc2.y=y2;
    setcolor(WHITE);
    setfillstyle(1,WHITE);
    circle((x2-x1-20)/2+x1,y1,7);
    floodfill((x2-x1-20)/2+x1,y1,WHITE);
    setcolor(YELLOWP);
    setfillstyle(1,YELLOWP);
    circle((x2-x1-20)/2+x1,y2,7);
    floodfill((x2-x1-20)/2+x1,y2,YELLOWP);
    if(v[m].pct2.x<maxim_stanga)
        maxim_stanga=v[m].pct1.x;
    if(v[m].pct4.x>maxim_dreapta)
        maxim_dreapta=v[m].pct4.x;
}

void iesire(int x1,int y1,int x2,int y2)
{
    nr_Blocuri++;
    v[nr_Blocuri].id='E';
    deseneaza_IESIRE(x1,y1,x2,y2,nr_Blocuri,"",PURPLE);
    v[nr_Blocuri].width=wi;
    v[nr_Blocuri].nr=nr_Blocuri;
    nr_leg_total++;
}

void deseneaza_STOP(int x1,int y1,int x2,int y2,int m,int cul)
{
    setcolor(cul);
    setfillstyle(1,cul);
    bar(x1,y1,x2,y2);
    setcolor(BLACK);
    setbkcolor(cul);
    setcolor(WHITE);//
    outtextxy(x1+20,y1+10,"STOP");
    v[m].pct1.x=x1;
    v[m].pct1.y=y1;
    v[m].pct2.x=x1;
    v[m].pct2.y=y1+hrectangle;
    v[m].pct3.x=x2;
    v[m].pct3.y=y2-hrectangle;
    v[m].pct4.x=x2;
    v[m].pct4.y=y2;
    v[m].mc1.x=(x2-x1)/2+x1;
    v[m].mc1.y=y1;
    v[m].mc2.y=y1+hrectangle;
    setcolor(WHITE);
    setfillstyle(1,WHITE);
    circle((x2-x1)/2+x1,y1,7);
    floodfill((x2-x1)/2+x1,y1,WHITE);
    if(v[m].pct1.x<maxim_stanga)
        maxim_stanga=v[m].pct1.x;
    if(v[m].pct4.x>maxim_dreapta)
        maxim_dreapta=v[m].pct4.x;
}

void stop(int x1,int y1,int x2,int y2)
{
    nr_Blocuri++;
    v[nr_Blocuri].id='G';
    deseneaza_STOP(x1,y1,x2,y2,nr_Blocuri,PURPLE);
    v[nr_Blocuri].width=vs;
    v[nr_Blocuri].nr=nr_Blocuri;
    oks--;
}

void linie(int i,int j,int cul)
{
    setcolor(cul);
    line(v[i].mc2.x,v[i].mc2.y,v[i].mc2.x,(v[j].mc1.y-v[i].mc2.y)/2+v[i].mc2.y);
    line(v[i].mc2.x,(v[j].mc1.y-v[i].mc2.y)/2+v[i].mc2.y,v[j].mc1.x,(v[j].mc1.y-v[i].mc2.y)/2+v[i].mc2.y);
    line(v[j].mc1.x,v[j].mc1.y,v[j].mc1.x,(v[j].mc1.y-v[i].mc2.y)/2+v[i].mc2.y);
}

void linie_spec(int i,int j,int cul)
{
    setcolor(cul);
    line(v[i].mc3.x,v[i].mc3.y,v[i].mc3.x,(v[j].mc1.y-v[i].mc3.y)/2+v[i].mc3.y);
    line(v[i].mc3.x,(v[j].mc1.y-v[i].mc3.y)/2+v[i].mc3.y,v[j].mc1.x,(v[j].mc1.y-v[i].mc3.y)/2+v[i].mc3.y);
    line(v[j].mc1.x,v[j].mc1.y,v[j].mc1.x,(v[j].mc1.y-v[i].mc3.y)/2+v[i].mc3.y);
}
void sterge_rectangle(int i) //start,stop,calcul
{
    setcolor(GREY);
    setfillstyle(1,GREY);
    rectangle(v[i].pct1.x,v[i].pct1.y-7,v[i].pct4.x,v[i].pct4.y+7);
    floodfill(v[i].pct1.x+2,v[i].pct1.y+2, GREY);
}

void sterge_triangle(int i)
{
    setcolor(GREY);
    setfillstyle(1,GREY);
    triunghi(v[i].pct1.x,v[i].pct1.y-10,v[i].pct2.x-30,v[i].pct2.y+7,v[i].pct3.x+30,v[i].pct3.y+7,GREY);
}

void sterge_trapez_intrare(int i)
{
    trapez_intrare(v[i].pct1.x-7,v[i].pct1.y-7,v[i].pct4.x+7,v[i].pct4.y+7,GREY);
}

void sterge_trapez_iesire(int i)
{
    trapez_iesire(v[i].pct1.x-7,v[i].pct1.y-7,v[i].pct4.x+7,v[i].pct4.y+7,GREY);
}
void citesteSir_CALCUL(char s[MAX],int x, int y,int i)
{
    char s1[MAX];
    char t[2];
    char tasta;
    setcolor(WHITE);
    if(strlen(v[i].var))
    {
        strcpy(s,v[i].var);
        strcpy(s1,s);
    }
    else
    {
        t[0]='\0';
        strcat(s,t);
        strcpy(s1,s);
        strcat(s1,"");
    }
    sterge_rectangle(i);
    deseneaza_CALCUL(v[i].mc1.x-v[i].width/2,v[i].pct1.y,v[i].width/2+v[i].mc1.x,v[i].pct2.y,i,v[i].var, PURPLE);
    do
    {
        tasta=getch();
        if (tasta==8) // backspace
            if (strlen(s)>0)
            {
                setcolor(PURPLE);
                strcpy(s1,s);
                strcat(s1,"");
                s[strlen(s)-1]='\0';
                strcpy(s1,s);
                strcat(s1,"");
                v[i].dim--;
                setcolor(WHITE);
                v[i].width-=12;
            }
            else
                Beep(1000,100);
        else if(tasta!=13)
        {
            t[0]=tasta;
            t[1]='\0';
            strcat(s,t);
            strcpy(s1,s);
            strcat(s1,"");
            setcolor(WHITE);
            v[i].dim++;
            if(v[i].dim*10+50>=v[i].width)
                v[i].width+=12;
        }
        sterge_rectangle(i);
        deseneaza_CALCUL(v[i].mc1.x-v[i].width/2,v[i].pct1.y,v[i].width/2+v[i].mc1.x,v[i].pct2.y,i,v[i].var, PURPLE);
    }
    while (tasta!=13);
    s[v[i].dim]='\0';
}

void citesteSir_DECIZIE(char s[MAX],int x, int y,int i)
{
    char s1[MAX];
    char t[2];
    char tasta;
    setcolor(WHITE);
    if(strlen(v[i].var))
    {
        strcpy(s,v[i].var);
        strcpy(s1,s);
    }
    else
    {
        t[0]='\0';
        strcat(s,t);
        strcpy(s1,s);
        strcat(s1,"");
    }
    do
    {
        tasta=getch();
        if (tasta==8)
            if (strlen(s)>0)
            {
                setcolor(PURPLE);
                strcpy(s1,s);
                s[strlen(s)-1]='\0';
                strcpy(s1,s);
                setcolor(WHITE);
                v[i].width-=10;
                v[i].dim--;
                sterge_triangle(i);
                linie_spec(i,v[i].v3,GREY);
                linie(i,v[i].v2,GREY);
                deseneaza_DECIZIE(v[i].pct1.x,v[i].pct1.y,v[i].pct1.x-v[i].width/2,v[i].pct2.y,v[i].pct1.x+v[i].width/2,v[i].pct2.y,i,s1, PURPLE);
                linie_spec(i,v[i].v3,WHITE);
                linie(i,v[i].v2,WHITE);
            }
            else
                Beep(1000,100);
        else if(tasta!=13)
        {
            t[0]=tasta;
            t[1]='\0';
            strcat(s,t);
            strcpy(s1,s);
            setcolor(WHITE);
            v[i].width+=10;
            v[i].dim++;
            sterge_triangle(i);
            linie_spec(i,v[i].v3,GREY);
            linie(i,v[i].v2,GREY);
            deseneaza_DECIZIE(v[i].pct1.x,v[i].pct1.y,v[i].pct1.x-v[i].width/2,v[i].pct2.y,v[i].pct1.x+v[i].width/2,v[i].pct2.y,i,s1, PURPLE);
            linie_spec(i,v[i].v3,WHITE);
            linie(i,v[i].v2,WHITE);
        }
    }
    while (tasta!=13);
    s[v[i].dim]='\0';
}

void citesteSir_IESIRE(char s[MAX],int x, int y,int i)
{
    char s1[MAX];
    char t[2];
    char tasta;
    t[0]='\0';
    if(strlen(v[i].var))
    {
        strcpy(s,v[i].var);
        strcpy(s1,s); //strcat(s1,"");
    }
    else
    {
        t[0]='\0';
        strcat(s,t);
        strcpy(s1,s);
        strcat(s1,"");
    }
    setcolor(WHITE);
    sterge_trapez_iesire(i);
    deseneaza_IESIRE(v[i].mc1.x-(v[i].width-40)/2,v[i].pct1.y,(v[i].width)/2+v[i].mc1.x,v[i].pct2.y,i,v[i].var, PURPLE);
    do
    {
        tasta=getch();
        if (tasta==8) // backspace
            if (strlen(s)>0)
            {
                setcolor(PURPLE);
                strcpy(s1,s);
                strcat(s1,"");
                s[strlen(s)-1]='\0';
                strcpy(s1,s);
                strcat(s1,"");
                setcolor(WHITE);
                v[i].width-=12;
                v[i].dim--;

            }
            else
                Beep(1000,100);
        else if(tasta!=13)
        {
            t[0]=tasta;
            t[1]='\0';
            strcat(s,t);
            strcpy(s1,s);
            strcat(s1,"");
            setcolor(WHITE);
            v[i].dim++;
            if(v[i].dim*12+60>=v[i].width)
                v[i].width+=12;
        }
        sterge_trapez_iesire(i);
        deseneaza_IESIRE(v[i].mc1.x-v[i].width/2+20,v[i].pct1.y,v[i].width/2+v[i].mc1.x,v[i].pct2.y,i,v[i].var, PURPLE);
    }
    while (tasta!=13);
    s[v[i].dim]='\0';
}

void verifica(int x, int y)
{
    for(int i=0; i<=nr_Blocuri; i++)
    {
        if(x>=v[i].pct1.x && y>=v[i].pct1.y && x>=v[i].pct2.x && y<=v[i].pct2.y+7 && x<=v[i].pct3.x && y>=v[i].pct3.y && x<=v[i].pct4.x && y<=v[i].pct4.y+7)
        {
            if(v[i].id=='S') //start
            {
                int ok=1;
                clearmouseclick(WM_LBUTTONDOWN);
                if(x>=v[i].mc2.x-7 && x<=v[i].mc2.x+7 && y>=v[i].mc2.y-7 && y<=v[i].mc2.y+7)
                {
                    while(ok)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            int xx=mousex();
                            int yy=mousey();
                            clearmouseclick(WM_LBUTTONDOWN);
                            for(int j=0; j<=nr_Blocuri; j++)
                            {
                                if(xx>=v[j].mc1.x-7 && xx<=v[j].mc1.x+7 && yy>=v[j].mc1.y-7 && yy<=v[j].mc1.y+7 && mat[i][j]==0)
                                {
                                    linie(i,j,WHITE);
                                    nr_leg++;
                                    ok=0;
                                    mat[i][j]=1;
                                    v[i].v2=j;
                                    v[j].v1=i;
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    sterge_rectangle(i);
                    if(v[i].v2!=-1)
                        linie(i,v[i].v2,GREY);
                    ok=1;
                    while(ok)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            int xx=mousex();
                            int yy=mousey();
                            if(xx+v[i].width>=790 || yy+hrectangle>=580 || xx<=20 || yy<=80)
                                clearmouseclick(WM_LBUTTONDOWN);
                            else
                            {
                                clearmouseclick(WM_LBUTTONDOWN);
                                ok=0;
                                deseneaza_START(xx,yy,xx+vs,yy+hrectangle,i,PURPLE);
                                if(v[i].v2!=-1)
                                    linie(i,v[i].v2,WHITE);
                            }
                        }
                    }
                }
                break;
            }
            else
                if(v[i].id=='I')
                {
                    int ok=1;
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x>=v[i].mc2.x-7 && x<=v[i].mc2.x+7 && y>=v[i].mc2.y-7 && y<=v[i].mc2.y+7)
                    {
                        while(ok)
                        {
                            if(ismouseclick(WM_LBUTTONDOWN))
                            {
                                int xx=mousex();
                                int yy=mousey();
                                clearmouseclick(WM_LBUTTONDOWN);
                                for(int j=0; j<=nr_Blocuri; j++)
                                {
                                    if(xx>=v[j].mc1.x-7 && xx<=v[j].mc1.x+7 && yy>=v[j].mc1.y-7 && yy<=v[j].mc1.y+7 && mat[i][j]==0)
                                    {
                                        if(v[i].dr==1)
                                            v[j].dr=1;
                                        if(v[i].st==1)
                                            v[j].st=1;
                                        if(v[j].mc2.y<=v[i].mc1.y)
                                        {
                                            if(v[i].st==1)
                                            {
                                                linie_st(i,j,WHITE);
                                                v[i].lin=1;
                                            }
                                            else if(v[i].dr==1)
                                            {
                                                linie_dr(i,j,WHITE);
                                                v[i].lin=1;
                                            }
                                        }
                                        else
                                            linie(i,j,WHITE);
                                        nr_leg++;
                                        ok=0;
                                        mat[i][j]=1;
                                        v[i].v2=j;
                                        v[j].v1=i;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        sterge_trapez_intrare(i);
                        if(v[i].lin)
                        {
                            if(v[i].st==1)
                                linie_st(i,v[i].v2,GREY);
                            else if(v[i].dr==1)
                                linie_dr(i,v[i].v2,GREY);
                        }
                        else if(v[i].v2!=-1)
                            linie(i,v[i].v2,GREY);

                        if(v[i].v1!=-1)
                        {
                            if(v[i].dr_imd==1)
                                linie_spec(v[i].v1,i,GREY);
                            else
                                linie(v[i].v1,i,GREY);
                        }
                        ok=1;
                        while(ok)
                        {
                            if(ismouseclick(WM_LBUTTONDOWN))
                            {
                                int xx=mousex();
                                int yy=mousey();
                                if(xx+v[i].width>=790 || yy+hrectangle>=580 || xx<=20 || yy<=80)
                                    clearmouseclick(WM_LBUTTONDOWN);
                                else
                                {
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    ok=0;
                                    deseneaza_INTRARE(xx,yy,xx+wi-20,yy+hrectangle,i,v[i].var, PURPLE);
                                    if(v[i].lin)
                                    {
                                        if(v[i].st==1)
                                            linie_st(i,v[i].v2,WHITE);
                                        else if(v[i].dr==1)
                                            linie_dr(i,v[i].v2,WHITE);
                                    }
                                    else if(v[i].v2!=-1)
                                        linie(i,v[i].v2,WHITE);
                                    if(v[i].v1!=-1)
                                    {
                                        if(v[i].dr_imd==1)
                                            linie_spec(v[i].v1,i,WHITE);
                                        else
                                            linie(v[i].v1,i,WHITE);
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                else

                    if(v[i].id=='C')
                    {
                        int ok=1;
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(x>=v[i].mc2.x-7 && x<=v[i].mc2.x+7 && y>=v[i].mc2.y-7 && y<=v[i].mc2.y+7)
                        {
                            while(ok)
                            {
                                if(ismouseclick(WM_LBUTTONDOWN))
                                {
                                    int xx=mousex();
                                    int yy=mousey();
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    for(int j=0; j<=nr_Blocuri; j++)
                                    {
                                        if(xx>=v[j].mc1.x-7 && xx<=v[j].mc1.x+7 && yy>=v[j].mc1.y-7 && yy<=v[j].mc1.y+7 && mat[i][j]==0)
                                        {
                                            if(v[i].dr==1)
                                                v[j].dr=1;
                                            if(v[i].st==1)
                                                v[j].st=1;
                                            if(v[j].mc2.y<=v[i].mc1.y)
                                            {
                                                if(v[i].st==1)
                                                {
                                                    linie_st(i,j,WHITE);
                                                    v[i].lin=1;
                                                }
                                                else if(v[i].dr==1)
                                                {
                                                    linie_dr(i,j,WHITE);
                                                    v[i].lin=1;
                                                }
                                            }
                                            else
                                                linie(i,j,WHITE);
                                            nr_leg++;
                                            ok=0;
                                            mat[i][j]=1;
                                            v[i].v2=j;
                                            v[j].v1=i;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            sterge_rectangle(i);
                            if(v[i].lin)
                            {
                                if(v[i].st==1)
                                    linie_st(i,v[i].v2,GREY);
                                else if(v[i].dr==1)
                                    linie_dr(i,v[i].v2,GREY);
                            }
                            else if(v[i].v2!=-1)
                                linie(i,v[i].v2,GREY);

                            if(v[i].v1!=-1)
                            {
                                if(v[i].dr_imd==1)
                                    linie_spec(v[i].v1,i,GREY);
                                else
                                    linie(v[i].v1,i,GREY);
                            }
                            ok=1;
                            while(ok)
                            {
                                if(ismouseclick(WM_LBUTTONDOWN))
                                {
                                    int xx=mousex();
                                    int yy=mousey();
                                    if(ismouseclick(WM_LBUTTONDOWN))
                                        if(xx+v[i].width>=790 || yy+hrectangle>=580 || xx<=20 || yy<=80)
                                            clearmouseclick(WM_LBUTTONDOWN);
                                        else
                                        {
                                            clearmouseclick(WM_LBUTTONDOWN);
                                            ok=0;
                                            deseneaza_CALCUL(xx,yy,xx+wc,yy+hrectangle,i,v[i].var, PURPLE);
                                            if(v[i].lin)
                                            {
                                                if(v[i].st==1)
                                                    linie_st(i,v[i].v2,WHITE);
                                                else if(v[i].dr==1)
                                                    linie_dr(i,v[i].v2,WHITE);
                                            }
                                            else if(v[i].v2!=-1)
                                                linie(i,v[i].v2,WHITE);

                                            if(v[i].v1!=-1)
                                            {
                                                if(v[i].dr_imd==1)
                                                    linie_spec(v[i].v1,i,WHITE);
                                                else
                                                    linie(v[i].v1,i,WHITE);
                                            }
                                        }
                                }
                            }
                        }
                        break;
                    }

                    else if(v[i].id=='E')
                    {
                        int ok=1;
                        //  cout<<"E";
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(x>=v[i].mc2.x-7 && x<=v[i].mc2.x+7 && y>=v[i].mc2.y-7 && y<=v[i].mc2.y+7)
                        {
                            //int c;
                            while(ok)
                            {
                                if(ismouseclick(WM_LBUTTONDOWN))
                                {
                                    int xx=mousex();
                                    int yy=mousey();
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    for(int j=0; j<=nr_Blocuri; j++)
                                    {
                                        if(xx>=v[j].mc1.x-7 && xx<=v[j].mc1.x+7 && yy>=v[j].mc1.y-7 && yy<=v[j].mc1.y+7 && mat[i][j]==0)
                                        {
                                            if(v[i].dr==1)
                                                v[j].dr=1;
                                            if(v[i].st==1)
                                                v[j].st=1;
                                            if(v[j].mc1.y<=v[i].mc2.y)
                                            {
                                                if(v[i].st==1)
                                                {
                                                    linie_st(i,j,WHITE);
                                                    v[i].lin=1;
                                                }
                                                else if(v[i].dr==1)
                                                {
                                                    linie_dr(i,j,WHITE);
                                                    v[i].lin=1;
                                                }
                                            }
                                            else
                                                linie(i,j,WHITE);
                                            ok=0;
                                            nr_leg++;
                                            mat[i][j]=1;
                                            v[i].v2=j;
                                            v[j].v1=i;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            sterge_trapez_iesire(i);
                            if(v[i].lin)
                            {
                                if(v[i].st==1)
                                    linie_st(i,v[i].v2,GREY);
                                else if(v[i].dr==1)
                                    linie_dr(i,v[i].v2,GREY);
                            }
                            else if(v[i].v2!=-1)
                                linie(i,v[i].v2,GREY);

                            if(v[i].v1!=-1)
                            {
                                if(v[i].dr_imd==1)
                                    linie_spec(v[i].v1,i,GREY);
                                else
                                    linie(v[i].v1,i,GREY);
                            }
                            ok=1;
                            while(ok)
                            {
                                if(ismouseclick(WM_LBUTTONDOWN))
                                {
                                    int xx=mousex();
                                    int yy=mousey();
                                    if(ismouseclick(WM_LBUTTONDOWN))
                                        if(xx+v[i].width>=790 || yy+hrectangle>=580 || xx<=20 || yy<=80)
                                            clearmouseclick(WM_LBUTTONDOWN);
                                        else
                                        {
                                            clearmouseclick(WM_LBUTTONDOWN);
                                            ok=0;
                                            deseneaza_IESIRE(xx,yy,xx+wi-20,yy+hrectangle,i,v[i].var, PURPLE);
                                            if(v[i].lin)
                                            {
                                                if(v[i].st==1)
                                                    linie_st(i,v[i].v2,WHITE);
                                                else if(v[i].dr==1)
                                                    linie_dr(i,v[i].v2,WHITE);
                                            }
                                            else if(v[i].v2!=-1)
                                                linie(i,v[i].v2,WHITE);

                                            if(v[i].v1!=-1)
                                            {
                                                if(v[i].dr_imd==1)
                                                    linie_spec(v[i].v1,i,WHITE);
                                                else
                                                    linie(v[i].v1,i,WHITE);
                                            }
                                        }
                                }
                            }
                        }
                        break;
                    }
                    else if(v[i].id=='G') //stop
                    {
                        int ok=1;
                        clearmouseclick(WM_LBUTTONDOWN);
                        sterge_rectangle(i);
                        if(v[i].v1!=-1)
                            linie(v[i].v1,i,GREY);
                        ok=1;
                        while(ok)
                        {
                            if(ismouseclick(WM_LBUTTONDOWN))
                            {
                                int xx=mousex();
                                int yy=mousey();
                                if(ismouseclick(WM_LBUTTONDOWN))
                                    if(xx+v[i].width>=790 || yy+hrectangle>=580 || xx<=20 || yy<=80)
                                        clearmouseclick(WM_LBUTTONDOWN);
                                    else
                                    {
                                        clearmouseclick(WM_LBUTTONDOWN);
                                        ok=0;
                                        deseneaza_STOP(xx,yy,xx+vs,yy+hrectangle,i,PURPLE);
                                        if(v[i].v1!=-1)
                                            linie(v[i].v1,i,WHITE);
                                    }
                            }
                        }
                        break;
                    }

        }
        else if(v[i].id=='D' && x>=v[i].pct2.x-7 && y>=v[i].pct1.y-7 && x<=v[i].pct3.x+7 && y<=v[i].pct2.y+7)
        {
            int ok=1;
            clearmouseclick(WM_LBUTTONDOWN);
            if(x>=v[i].mc2.x-7 && x<=v[i].mc2.x+7 && y>=v[i].mc2.y-7 && y<=v[i].mc2.y+7)//stanga
            {
                // STANGA
                while(ok)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int xx=mousex();
                        int yy=mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        for(int j=0; j<=nr_Blocuri; j++)
                        {
                            if(xx>=v[j].mc1.x-7 && xx<=v[j].mc1.x+7 && yy>=v[j].mc1.y-7 && yy<=v[j].mc1.y+7 && mat[i][j]==0)
                            {
                                linie(i,j,WHITE);
                                ok=0;
                                nr_leg++;
                                mat[i][j]=1;
                                v[i].v2=j;
                                v[j].v1=i;
                                v[j].st=1;
                                break;
                            }
                        }
                    }
                }
            }
            else if(x>=v[i].mc3.x-7 && x<=v[i].mc3.x+7 && y>=v[i].mc3.y-7 && y<=v[i].mc3.y+7)//dreapta
            {
                ok=1;
                // DREAPTA
                while(ok)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int xx=mousex();
                        int yy=mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        for(int j=0; j<=nr_Blocuri; j++)
                        {
                            if(xx>=v[j].mc1.x-7 && xx<=v[j].mc1.x+7 && yy>=v[j].mc1.y-7 && yy<=v[j].mc1.y+7 && mat[i][j]==0)
                            {
                                linie_spec(i,j,WHITE);
                                ok=0;
                                mat[i][j]=2;
                                nr_leg++;
                                v[i].v3=j;
                                v[j].v1=i;
                                v[j].dr=1; //
                                v[j].dr_imd=1;
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                sterge_triangle(i);
                if(v[i].v2!=-1)
                    linie(i,v[i].v2,GREY);
                if(v[i].v1!=-1)
                    linie(v[i].v1,i,GREY);
                if(v[i].v3!=-1)
                    linie_spec(i,v[i].v3,GREY);
                ok=1;
                while(ok)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int xx=mousex();
                        int yy=mousey();
                        if(ismouseclick(WM_LBUTTONDOWN))
                            if(xx+v[i].width/2>=790 || yy+htriunghi>=580 || xx<=20 || yy<=80)
                                clearmouseclick(WM_LBUTTONDOWN);
                            else
                            {
                                clearmouseclick(WM_LBUTTONDOWN);
                                ok=0;
                                deseneaza_DECIZIE(xx,yy,xx-wt/2,yy+htriunghi,xx+wt/2,yy+htriunghi,i,v[i].var, PURPLE);
                                if(v[i].v2!=-1)
                                    linie(i,v[i].v2,WHITE);
                                if(v[i].v1!=-1)
                                    linie(v[i].v1,i,WHITE);
                                if(v[i].v3!=-1)
                                    linie_spec(i,v[i].v3,WHITE);
                            }
                    }
                }
            }
            break;
        }

    }
}

void verifica_scriere(int x, int y)
{
    for(int i=0; i<=nr_Blocuri; i++)
    {
        if(x>=v[i].pct1.x && y>=v[i].pct1.y && x>=v[i].pct2.x && y<=v[i].pct2.y+7 && x<=v[i].pct3.x && y>=v[i].pct3.y && x<=v[i].pct4.x && y<=v[i].pct4.y+7)
        {
            if(v[i].id=='I') //intrare
            {
                clearmouseclick(WM_RBUTTONDOWN);
                citesteSir_INTRARE(v[i].var,v[i].pct1.x+50,v[i].pct1.y+10);
            }
            else if(v[i].id=='C')
            {
                clearmouseclick(WM_RBUTTONDOWN);
                citesteSir_CALCUL(v[i].var,v[i].pct1.x+50,v[i].pct1.y+10,i);
                break;
            }
            else if(v[i].id=='E')
            {
                clearmouseclick(WM_RBUTTONDOWN);
                citesteSir_IESIRE(v[i].var,v[i].pct1.x+50,v[i].pct1.y+10,i);
                break;
            }
        }
        else if(v[i].id=='D' && x>=v[i].pct2.x-7 && y>=v[i].pct1.y-7 && x<=v[i].pct3.x+7 && y<=v[i].pct2.y+7)
        {
            clearmouseclick(WM_RBUTTONDOWN);
            citesteSir_DECIZIE(v[i].var,v[i].pct1.x+50,v[i].pct1.y+10,i);
        }
    }
}
void deseneaza()
{

    int incx,incy,j,ok_test=5,x,y;
    bool ok,ok_oprire=1;
    incx=340;
    incy=100;
    while((oks || nr_leg<nr_leg_total) && ok_oprire)
    {
        ok=1;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if(x>=50 && y>=35 && x<=150 && y<=75) //start
            {
                START(incx,incy,incx+vs,incy+hrectangle);
                incy=incy+hrectangle+50;
                clearmouseclick(WM_LBUTTONDOWN);
            }
            if(x>=170 && y>=35 && x<=270 && y<=75) //intrare
            {
                intrare(incx,incy,incx+wi-20,incy+hrectangle);
                incy=incy+hrectangle+50;
                clearmouseclick(WM_LBUTTONDOWN);
            }
            if(x>=290 && y>=35 && x<=390 && y<=75)//calcul
            {
                int incx=315;
                calcul(incx,incy,incx+wc,incy+hrectangle);
                incy=incy+hrectangle+50;
                clearmouseclick(WM_LBUTTONDOWN);
            }
            if(x>=410 && y>=35 && x<=510 && y<=75)//decizie
            {
                decizie(incx+wt/2-10,incy,incx-10,incy+htriunghi,incx+wt-10,incy+htriunghi);
                incy=incy+20+htriunghi;
                clearmouseclick(WM_LBUTTONDOWN);
            }
            if(x>=530 && y>=35 && x<=630 && y<=75)//iesire
            {
                iesire(incx,incy,incx+wi-20,incy+hrectangle);
                incy=incy+hrectangle+50;
                clearmouseclick(WM_LBUTTONDOWN);
            }
            if(x>=650 && y>=35 && x<=750 && y<=75)//stop
            {
                stop(incx,incy,incx+vs,incy+hrectangle);
                incy=incy+hrectangle+50;
                clearmouseclick(WM_LBUTTONDOWN);
            }
            if(x>=830 && y>=35 && x<=1160 && y<=85)
            {
                ok_oprire=0;
                clearmouseclick(WM_LBUTTONDOWN);
            }
            verifica(x,y);
        }
    }
}

void scriere()
{
    int x,y;
    bool ok=1;
    while(ok)
    {
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            verifica_scriere(x,y);
        }
        else if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(x>=1005 && y>=35 && x<=1160 && y<=85)
                ok=0;
        }
    }
}

void creare(nod *p,int i)
{
    if(p!=NULL)
    {
        if(v[i].v2==-1)
        {
            p->st=NULL;
            p->dr=NULL;
            return;
        }
        nod *q;
        q=new nod;
        q->info=v[v[i].v2];
        q->st=NULL;
        q->dr=NULL;
        p->st=q;
        creare(p->st,v[i].v2);
        if(v[i].v3!=-1)
        {
            nod *o;
            o=new nod;
            o->info=v[v[i].v3];
            o->st=NULL;
            o->dr=NULL;
            p->dr=o;
            creare(p->dr,v[i].v3);
        }
        else
            p->dr=NULL;
    }
    else
        return;
}
int top1,top2; // varfurile celor doua stive
const int max_stiva=100;

double Opd[max_stiva]; // stiva operanzilor
char Op[max_stiva]; // stiva operatorilor

char OperatiiBinare[200]="+-*/^<>=#";
char OperatiiUnare[200]="scarel";
char Operatii[200]="+-*/^<>=#scarel";

int Prioritate(char c)  // prioritate operatorilor
{
    if(c=='(' || c==')')
        return 0;
    if(c=='+' || c=='-')
        return 1;
    if(c=='*' || c=='/')
        return 2;
    if(c=='^')
        return 3;
    if(c=='=' || c=='#' || c=='<' || c=='>')
        return 4;
    if(c=='c' || c=='s' || c=='l' || c=='e' || c=='t' || c=='a' || c=='r')
        return 5;
}

const float pi=3.1415926; // se da sub forma literei q

bool DifInf(float x)
{
    return fabs(infinit-fabs(x)) > infinit / 2.0;
}

float Logaritm(float x)
{
    if (x>epsi && DifInf(x))
        return log(x);
    else
        return infinit;
}

float Exponential(float x)
{
    if (DifInf(x))
        return exp(x);
    else
        return infinit;
}

float Inmultit(float x, float y)
{
    if (fabs(x < epsi) || fabs(y) < epsi)
        return 0;
    else if (DifInf(x) && DifInf(y))
        return x*y;
    else
        return infinit;
}

float Putere(float x, float y)
{
    if (x==0)
        return 0;
    else if (y==0)
        return 1;
    else if (x==infinit || y==infinit)
        return infinit;
    else
        return pow(x,y);
}

float Egal(float x, float y)
{
    return x==y;
}

float Diferit(float x, float y)
{
    return x!=y;
}

float MaiMic(float x, float y)
{
    return x < y;
}

bool MaiMare(float x, float y)
{
    return x > y;
}

float Plus(float x, float y)
{
    if(DifInf(x) && DifInf(y))
        return x+y;
    else
        return infinit;
}

float Minus(float x, float y)
{
    if (DifInf(x) && DifInf(y))
        return x-y;
    else
        return infinit;
}
float Impartit(float x, float y)
{
    if (fabs(y)>epsi)
        return x/y;
    else
        return infinit;
}

float Sinus(float x)
{
    if (DifInf(x))
        return sin(x);
    else
        return infinit;
}

float Cosinus(float x)
{
    if (DifInf(x))
        return cos(x);
    else
        return infinit;
}

float Modul(float x)
{
    if (DifInf(x))
        return fabs(x);
    else
        return infinit;
}

float Radical(float x)
{
    if (DifInf(x) && (x>epsi))
        return sqrt(x);
    else
        return infinit;
}

bool EsteNumar(char sir[MAX1])
{
    return (atof(sir)!=0.0 &&
            strchr("0123456789",sir[0]));
}

struct functie
{
    char expresie[300];
    char vect[MAX+1][MAX1];
    // vectorul cuprinzand “cuvintele”ce formeaza expresia}
    int lung; // lungimea efectiva a vectorului
    float a,b; // intervalul de evaluare a functiei
    int n; //numarul de puncte de evaluare
};

void depanare()
{
    printf("Stiva operanzilor: ");
    for (int i=1; i<=top1; i++)
        printf("%f,",Opd[i]);
    printf("\nStiva operatorilor: ");
    for (int i=1; i<=top2; i++)
        printf("%c,",Op[i]);
    printf("\n");
}

double ValoareFunctie(functie E, double x)
{
    int i;
    // returneaza valoarea functiei E in punctul x
    double valo,x_1,x_2;
    //calculul expresiei
    for (i=1; i<=max_stiva; i++)
    {
        Opd[i]=0;
        Op[i]='@';
    }
    top1=0;
    top2=1;
    Op[top2]='(';
    i=0;
    while (i<=E.lung && top2>0)
    {
        i++;
        if (isdigit(E.vect[i][0]))
        {
            top1++;
            int k=0,nr=0;
            while(isdigit(E.vect[i][k]))
            {
                nr=nr*10+E.vect[i][k]-'0';
                k++;
            }
            valo=nr;
            Opd[top1]=nr;
            // depanare();
        }
        else
            switch (E.vect[i][0])
            {
            /* constanta pi=3.1415926 se da sub forma literei q */
            case 'q':
                top1++;
                Opd[top1]=pi;
                break;
            case 'X': /* variabila x */
                top1++;
                Opd[top1]=x;
                /* printf("\n-->x=%f\n",x); */ break;
            case '(': /* inceput de bloc */
                top2++;
                Op[top2]='(';
                break;
            default:
                /* operatii binare si unare */
                while ((top2>0) && !(strchr("()",Op[top2])) &&
                        Prioritate(Op[top2])>=Prioritate(E.vect[i][0]))
                {
                    if (top1>1)
                        x_1=Opd[top1-1];
                    x_2=Opd[top1];
                    /* functii scrise in OPERATII */
                    switch (Op[top2])
                    {
                    case '=':
                        valo=Egal(x_1,x_2);
                        break;
                    case '#':
                        valo=Diferit(x_1,x_2);
                        break;
                    case '<':
                        valo=MaiMic(x_1,x_2);
                        break;
                    case '>':
                        valo=MaiMare(x_1,x_2);
                        break;
                    case '+':
                        valo=Plus(x_1,x_2);
                        break;
                    case '-':
                        valo=Minus(x_1,x_2);
                        break;
                    case '*':
                        valo=Inmultit(x_1,x_2);
                        break;
                    case '/':
                        valo=Impartit(x_1,x_2);
                        break;
                    case '^':
                        valo=Putere(x_1,x_2);
                        break;
                    case 's':
                        valo=Sinus(x_2);
                        break;
                    case 'c':
                        valo=Cosinus(x_2);
                        break;
                    case 'l':
                        valo=Logaritm(x_2);
                        break;
                    case 'e':
                        valo=Exponential(x_2);
                        break;
                    case 'a':
                        valo=Modul(x_2);
                        break;
                    case 'r':
                        valo=Radical(x_2);
                        break;
                    }
                    if (strchr(OperatiiBinare,Op[top2]))
                        top1--;
                    if (strchr(Operatii,Op[top2]))
                        Opd[top1]=valo;
                    top2--;
                }
                // depanare();
                if (top2>0)
                    if ((Op[top2]!='(') || (strcmp(E.vect[i],")")))
                    {
                        top2++;
                        Op[top2] = E.vect[i][0];
                    }
                    else
                        top2--;
            }
    }
    return Opd[1];
}

float eval(char s[300])
{
    functie F;
    int i,pas=1;
    char aux[300];
    strcpy(F.expresie,s);
    strcat(F.expresie,")");
    strcpy(F.vect[0],"(");
    for(int i=0; i<strlen(s); i++)
    {
        int k=0;
        while((isdigit(s[i])))
        {
            aux[k]=s[i];
            k++;
            i++;
        }
        if(k==0)
        {
            aux[k]=s[i];
            aux[k+1]=NULL;
        }
        else
        {
            i--;
            aux[k]=NULL;
        }
        strcpy(F.vect[pas],aux);
        pas++;
    }
    strcpy(F.vect[strlen(s)+1],")");
    F.lung=strlen(F.expresie);
    float a=ValoareFunctie(F,1);
    return a;
}

int nr_cif(int numar)
{
    int nr=0;
    while(numar)
    {
        numar=numar/10;
        nr++;
    }
    return nr;
}

void desenare_litera(int x,int y, char lit)
{
    char lit1[4];
    lit1[0]=lit;
    lit1[1]='=';
    lit1[2]='0';
    lit1[3]=NULL;
    setbkcolor(GREY);
    setcolor(WHITE);
    outtextxy(x,y,lit1);
    mem[lit-65].x=x+24;
    mem[lit-65].y=y;
    mem[lit-65].str[0]=0+'0';
    mem[lit-65].str[1]=NULL;
}

int xl=40,yl=640;

void litere()
{
    int i,cxl;
    cxl=xl;
    for(i=0; i<9; i++)
    {
        desenare_litera(cxl,yl,char(i+65));
        cxl=cxl+83;
    }
    cxl=xl;
    yl=yl+40;
    for(i=9; i<18; i++)
    {
        desenare_litera(cxl,yl,char(i+65));
        cxl=cxl+83;
    }
    cxl=xl;
    yl=yl+40;
    for(i=18; i<26; i++)
    {
        desenare_litera(cxl,yl,char(i+65));
        cxl=cxl+83;
    }
}

void calculeaza()
{
    nod *p;
    int ok1=1;
    p=start;
    settextstyle(8,0,1);
    setbkcolor(GREY);
    setcolor(WHITE);
    while(ok1!=0 && p!=NULL)
    {
        elem h=p->info;
        if(h.id=='S')
        {
            deseneaza_START(h.pct1.x,h.pct1.y,h.pct4.x,h.pct4.y,50,FINISH);
            p=p->st;
        }
        else if(h.id=='I')
        {
            deseneaza_INTRARE(h.pct1.x,h.pct1.y,h.pct4.x,h.pct4.y,50,h.var,FINISH);
            setcolor(WHITE);
            char textt[100], s[100];
            strcpy(textt,"Dati variabila ");
            strcat(textt,h.var);
            strcat(textt," : ");
            setbkcolor(GREY);
            setcolor(WHITE);
            outtextxy(ox,oy,textt);
            citesteSir_INTRARE(s,ox+210,oy);
            delay(20);
            setbkcolor(GREY);
            setcolor(WHITE);
            outtextxy(mem[h.var[0]-65].x,mem[h.var[0]-65].y,mem[h.var[0]-65].str);
            int i=0, nr=0;
            bool ok=0;
            if(s[0]=='-')
            {
                i++;
                ok=1;
            }
            while(isdigit(s[i]))
            {
                nr=nr*10+s[i]-'0';
                i++;
            }
            mem[h.var[0]-65].nr_cif=i;
            if(ok==1)
                mem[h.var[0]-65].val=-nr;
            else
                mem[h.var[0]-65].val=nr;
            strcpy(mem[h.var[0]-65].str, s);
            oy=oy+20;
            p=p->st;
            setbkcolor(GREY);
            setcolor(WHITE);
            outtextxy(mem[h.var[0]-65].x,mem[h.var[0]-65].y,mem[h.var[0]-65].str);
        }
        else if(h.id=='C')
        {
            deseneaza_CALCUL(h.pct1.x,h.pct1.y,h.pct4.x,h.pct4.y,50,h.var,FINISH);
            setcolor(BLACK);
            outtextxy(h.pct1.x+(h.width-h.dim*11)/2,h.pct1.y+10,h.var);
            char s1[100];
            s1[0]=NULL;
            int poz=0;
            delay(20);
            setbkcolor(GREY);
            setcolor(WHITE);
            outtextxy(mem[h.var[0]-65].x,mem[h.var[0]-65].y,mem[h.var[0]-65].str);
            for(int i=2; i<h.dim; i++)
            {
                if(h.var[i]>='A'&& h.var[i]<='Z')
                {
                    if(strlen(s1)==0)
                        strcpy(s1,mem[h.var[i]-65].str);
                    else
                        strcat(s1,mem[h.var[i]-65].str);
                    poz=poz+mem[h.var[i]-65].nr_cif;
                }
                else
                {
                    s1[poz]=h.var[i];
                    poz++;
                    s1[poz]=NULL;
                }
            }
            int e=eval(s1);
            mem[h.var[0]-65].val=e;
            int nrc=nr_cif(e);
            bool ok=0;
            if(e<0)
            {
                e=-e;
                ok=1;
                mem[h.var[0]-65].str[0]='-';
                nrc++;
            }
            mem[h.var[0]-65].str[nrc]=NULL;
            while(e)
            {
                mem[h.var[0]-65].str[nrc-1]=e%10+'0';
                nrc=nrc-1;
                e=e/10;
            }
            p=p->st;
            setcolor(WHITE);
            outtextxy(mem[h.var[0]-65].x,mem[h.var[0]-65].y,mem[h.var[0]-65].str);
        }
        else if(h.id=='D')
        {
            deseneaza_DECIZIE(h.pct1.x,h.pct1.y,h.pct2.x,h.pct2.y,h.pct3.x,h.pct3.y,50,h.var,FINISH);
            setcolor(WHITE);
            outtextxy((h.width-h.dim*10)/2+h.pct2.x-5,h.pct1.y+35,h.var);
            char semn;
            char s2[100],s3[100];
            s2[0]=NULL;
            s3[0]=NULL;
            int poz=0;
            int i=0;
            while(h.var[i]!='>'&&h.var[i]!='<'&&h.var[i]!='=')
            {
                if(h.var[i]>='A'&& h.var[i]<='Z')
                {
                    if(strlen(s2)==0)
                        strcpy(s2,mem[h.var[i]-65].str);
                    else
                        strcat(s2,mem[h.var[i]-65].str);
                    poz=poz+mem[h.var[i]-65].nr_cif;
                }
                else
                {
                    s2[poz]=h.var[i];
                    poz++;
                    s2[poz]=NULL;
                }
                i++;
            }
            semn=h.var[i];
            i++;
            poz=0;
            while(h.var[i]!=NULL)
            {
                if(h.var[i]>='A'&& h.var[i]<='Z')
                {
                    if(strlen(s3)==0)
                        strcpy(s3,mem[h.var[i]-65].str);
                    else
                        strcat(s3,mem[h.var[i]-65].str);
                    poz=poz+mem[h.var[i]-65].nr_cif;
                }
                else
                {
                    s3[poz]=h.var[i];
                    poz++;
                    s3[poz]=NULL;
                }
                i++;
            }
            int e2=eval(s2);
            char aux[100];
            aux[0]=NULL;
            int nrc2=nr_cif(e2);
            int e3=eval(s3);
            int nrc3=nr_cif(e3);
            setbkcolor(GREY);
            aux[nrc2+1]=NULL;
            aux[nrc3+nrc2+1]=NULL;
            aux[nrc2]=semn;
            int nr_elem;
            nr_elem=nr_cif(e2);
            while(e2)
            {
                aux[nrc2-1]=e2%10+'0';
                nrc2=nrc2-1;
                e2=e2/10;
            }
            while(e3)
            {
                aux[nrc3+nr_elem]=e3%10+'0';
                nrc3=nrc3-1;
                e3=e3/10;
            }
            int e4=eval(aux);
            if(e4==1)
            {
                p=p->st;
                setcolor(WHITE);
                outtextxy(ox,oy,"Expresia este adevarata");
            }
            else
            {
                p=p->dr;
                setcolor(WHITE);
                outtextxy(ox,oy,"Expresia este falsa");
            }
            ox=830;
            oy=oy+20;
        }
        else if(h.id=='E')
        {
            deseneaza_IESIRE(h.pct1.x,h.pct1.y,h.pct4.x,h.pct4.y,50,h.var,FINISH);
            setcolor(BLACK);
            char s4[100];
            s4[0]=NULL;
            int poz=0;
            for(int i=0; i<h.dim; i++)
            {
                if(h.var[i]>='A'&& h.var[i]<='Z')
                {
                    if(strlen(s4)==0)
                        strcpy(s4,mem[h.var[i]-65].str);
                    else
                        strcat(s4,mem[h.var[i]-65].str);
                    poz=poz+mem[h.var[i]-65].nr_cif;
                }
                else
                {
                    s4[poz]=h.var[i];
                    poz++;
                    s4[poz]=NULL;
                }
            }
            int e5=eval(s4);
            char text[10];
            int nrc4=nr_cif(e5);
            text[nrc4]=NULL;
            while(e5)
            {
                text[nrc4-1]=e5%10+'0';
                nrc4=nrc4-1;
                e5=e5/10;
            }
            setbkcolor(GREY);
            setcolor(WHITE);
            outtextxy(ox,oy,"Rezultatul este: ");
            outtextxy(ox+17*12,oy,text);
            p=p->st;
            oy=oy+20;
        }
        else if(h.id=='G')
        {
            deseneaza_STOP(h.pct1.x,h.pct1.y,h.pct4.x,h.pct4.y,50,FINISH);
            ok1=0;
            p=p->st;
            break;
        }
    }
}

void structura_date()
{
    nod *p,*q;
    start=new nod;
    start->st=NULL;
    start->dr=NULL;
    start->info=v[0];
    creare(start,0);
}

void code(nod *start)
{
    char text[30];
    settextstyle(3,0,1);
    setbkcolor(GREY);
    setcolor(WHITE);
    if(start!=NULL)
    {
        if(start->info.id=='S')
        {
            outtextxy(cx,cy,"#include<iostream>");
            cy=cy+20;
            outtextxy(cx,cy,"using namespace std;");
            cy=cy+20;
            outtextxy(cx,cy,"int main()");
            cy=cy+20;
            outtextxy(cx,cy,"{");
            cy=cy+20;
            cx=cx+20;
            code(start->st);
        }
        else if(start->info.id=='I')
        {
            strcpy(text,"cout<<''Dati valorea lui ");
            strcat(text, start->info.var);
            strcat(text, ": '';");
            outtextxy(cx,cy,text);
            cy=cy+20;
            strcpy(text, "cin>>");
            strcat(text, start->info.var);
            strcat(text, ";");
            outtextxy(cx,cy,text);
            cy=cy+20;
            code(start->st);
        }
        else if(start->info.id=='C')
        {
            strcpy(text, start->info.var);
            strcat(text,";");
            outtextxy(cx,cy,text);
            cy=cy+20;
            code(start->st);
        }
        else if(start->info.id=='D')
        {
            nrstop=1;
            exista=1;
            strcpy(text,"if(");
            strcat(text,start->info.var);
            strcat(text,"){");
            outtextxy(cx,cy,text);
            cy=cy+20;
            cx=cx+20;
            code(start->st);
            code(start->dr);
        }
        else if(start->info.id=='E')
        {
            strcpy(text, "cout<<");
            strcat(text,start->info.var);
            strcat(text,";");
            outtextxy(cx,cy,text);
            cy=cy+20;
            code(start->st);
        }

        else if(start->info.id=='G')
        {

            if(nrstop==0)
            {
                if(exista==1)
                {
                    outtextxy(cx-20,cy,"}");
                    cy=cy+20;
                    cx=cx-20;
                }
                else
                {
                    outtextxy(cx,cy,"return 0;");
                    outtextxy(cx-20,cy+20,"} ");
                    cy=cy+20;
                    cx=cx-20;
                }
            }
            else
            {
                outtextxy(cx-20,cy,"}");
                nrstop=0;
                cy=cy+20;
                outtextxy(cx-20,cy,"else {");
                cy=cy+20;
            }
            code(start->st);
        }
    }
    else
        return ;
}

void citire_maxim()
{
    char text[50];
    int x1,y1,x2,y2,x3,y3,j;
    int xi,yi;
    int ok=0,ok2=0,ok3=0;
    f>>nr_Blocuri;
    for(j=0; j<nr_Blocuri; j++)
    {
        f>>v[j].id;
        f>>x1>>y1>>x2>>y2;
        if(v[j].id=='S')
        {
            deseneaza_START(x1,y1,x2,y2,j,PURPLE);
            v[j].v2=1;
            v[j].width=vs;
            v[j].nr=0;
            mat[0][1]=1;
        }
        else if(v[j].id=='I')
        {
            if(ok==0)
            {
                strcpy(v[j].var,"A");
                ok=1;
            }
            else
                strcpy(v[j].var,"B");
            deseneaza_INTRARE(x1,y1,x2,y2,j,v[j].var,PURPLE);
            v[j].v1=j-1;
            v[j].v2=j+1;
            linie(j-1,j,WHITE);
        }
        else if(v[j].id=='D')
        {
            f>>x3>>y3;
            v[j].width=wt;
            v[j].dim=3;
            deseneaza_DECIZIE(x1,y1,x2,y2,x3,y3,j,"A>B",PURPLE);
            strcpy( v[j].var,"A>B");
            setbkcolor(PURPLE);
            setcolor(BLACK);
            v[j].v1=j-1;
            v[j].v2=j+1;
            v[j].v3=j+3;
            linie(j-1,j,WHITE);
        }
        else if(v[j].id=='E')
        {
            v[j].width=wt;
            v[j].dim=1;
            if(ok2==0)
            {
                deseneaza_IESIRE(x1,y1,x2,y2,j,"A",PURPLE);
                v[j].v1=j-1;
                v[j].v2=j+1;
                ok2=1;
                linie(j-1,j,WHITE);
                strcpy( v[j].var,"A");
            }
            else
            {
                deseneaza_IESIRE(x1,y1,x2,y2,j,"B",PURPLE);
                v[j].v1=j-3;
                v[j].v2=j+1;
                linie_spec(j-3,j,WHITE);
                strcpy( v[j].var,"B");
            }
        }
        else if(v[j].id=='G')
        {
            deseneaza_STOP(x1,y1,x2,y2,j,PURPLE);
            linie(j-1,j,WHITE);
            v[j].v1=j-1;
        }
    }
    int ok_oprire=1;
    while(ok_oprire)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x=mousex();
            int y=mousey();
            if(x>=830 && y>=35 && x<=1160 && y<=85)
            {
                ok_oprire=0;
                clearmouseclick(WM_LBUTTONDOWN);
            }
            else
                verifica(x,y);
        }
    }
    structura_date();
    litere();
    code(start);
    outtextxy(cx-20,cy,"}");
    calculeaza();
    getch();
}

void salveaza_schema(nod *start)
{
    if(start!=NULL)
    {
        out<<start->info.id<<" ";
        out<<start->info.var<<endl;
        if(start->info.id!='D')
            out<<start->info.pct1.x<<" "<<start->info.pct1.y<<" "<<start->info.pct4.x<<" "<<start->info.pct4.y<<endl;
        else
            out<<start->info.pct1.x<<" "<<start->info.pct1.y<<" "<<start->info.pct2.x<<" "<<start->info.pct2.y<<start->info.pct3.x<<" "<<start->info.pct3.y<<endl;
        salveaza_schema(start->st);
        salveaza_schema(start->dr);
    }
    else return;
}

void meniu()
{
    int okn=1;
    int sunet=1;
    initwindow(1200,800,"Interschem Ianovici Mara si Stoica Dragos");
    setbkcolor(COLOR(18,18,18));
    setcolor(GREY);
    setfillstyle(1,GREY);
    bar(20,20,1180,780);
    setcolor(PURPLE);
    setfillstyle(1,PURPLE);
    bar(321,215,321+558,215+60);
    bar(321,315,321+558,315+60);
    bar(321,415,321+558,415+60);
    bar(321,515,321+558,515+60);
    settextstyle(8,0,3);
    setcolor(BLACK);
    setbkcolor(PURPLE);
    outtextxy(520,235,"SCHEMA NOUA");
    outtextxy(550,335,"MAXIMUL");
    outtextxy(555,435,"MUZICA");
    outtextxy(570,535,"EXIT");
    while(okn)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x=mousex();
            int y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if( x>=321 &&x<=321+558 && y>=215 && y<=275)
            {
                setbkcolor(COLOR(18,18,18));
                cleardevice();
                okn=0;
                interfata();
                deseneaza();
                scriere();
                structura_date();
                salveaza_schema(start);
                setcolor(BLACKNOU);
                setfillstyle(1,BLACKNOU);
                bar(20,580,790,600);
                litere();
                calculeaza();
                code(start);
                if(exista)
                    outtextxy(cx-20,cy,"} ");
            }
            else if(x>=321 &&x<=321+558 && y>=315 && y<=375)
            {
                setbkcolor(COLOR(18,18,18));
                cleardevice();
                okn=0;
                interfata();
                citire_maxim();
            }
            else if(x>=321 && x<=321+558 && y<=515+60 && y>=515)
                exit(0);
            else if(x>=321 && x<=321+558 && y>=415 && y<=465)
            {
                if(sunet==1)
                {
                    PlaySound(NULL, 0, 0);
                    sunet=0;
                }
                else
                {
                    PlaySound(TEXT("LedSpirals.wav"),NULL, SND_ASYNC);
                    sunet=1;
                }
            }
        }
    }
}
int main()
{
    PlaySound(TEXT("LedSpirals.wav"),NULL, SND_ASYNC);
    meniu();
    getch();
    closegraph();
    return 0;
}
