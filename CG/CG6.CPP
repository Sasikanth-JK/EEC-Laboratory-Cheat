#include<graphics.h>
#include<iostream.h>
#include<conio.h>

int gd,gm;

void main()
{
    initgraph(&gd,&gm,"C:/TURBOC3/BIN");

    setbkcolor(BLUE);
    setcolor(RED);

    rectangle(150,150,250,200);
    line(150,200,120,180);
    line(120,180,120,130);

    setcolor(LIGHTRED);
    line(120,130,150,150);
    line(150,150,200,100);
    line(200,100,250,150);
    fillellipse(200,125,10,10);
    line(120,130,170,80);
    line(170,80,200,100);

    setcolor(BROWN);
    rectangle(190,170,210,200);
    line(190,170,200,180);
    line(200,180,200,200);

    setcolor(CYAN);
    line(190,200,190,270);
    line(210,200,210,250);
    line(190,270,300,270);
    line(210,250,300,250);

    setcolor(LIGHTGRAY);
    circle(230,260,5);
    circle(270,260,5);

    setcolor(BROWN);
    line(230,259,270,259);
    line(230,261,270,261);
    line(230,230,230,261);
    line(232,230,232,260);
    line(227,230,237,230);
    line(227,231,237,231);
    line(270,260,250,245);
    line(271,260,251,245);
    line(250,245,230,245);
    line(250,246,230,245);
    line(250,246,230,246);
    line(248,245,248,240);
    line(247,245,247,240);
    fillellipse(248,238,3,1);

    setcolor(LIGHTGRAY);
    line(252,245,265,245);
    line(252,246,265,246);

    getch();
}
