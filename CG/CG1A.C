#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>

void main()
{
    int x1,x2,y1,y2,gd=DETECT,gm,dx,dy,step;
    int x,y,const1,const2,p,x_end;

    initgraph(&gd,&gm,"C:/TURBOC3/BIN");

    printf("\n Enter the end point co-ordinates of the line \n");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

    dx=abs(x2-x1);
    dy=abs(y2-y1);
    p=2*dy-dx;
    const1=2*dy;
    const2=2*(dy-dx);

    if(x1>x2)
    {
        x=x2;
        y=y2;
        x_end=x1;
    }
    else
    {
        x=x1;
        y=y1;
        x_end=x2;
    }

    putpixel(x,y,15);

    while(x<x_end)
    {
        x++;
        if(p<0)
            p+=const1;
        else
        {
            y++;
            p+=const2;
        }
        putpixel(x,y,15);
    }

    getch();
    closegraph();
}
