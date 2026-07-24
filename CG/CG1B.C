#include<stdio.h>
#include<conio.h>
#include<graphics.h>

void plotpoint(int xc,int yc,int x,int y)
{
    putpixel(xc+x,yc+y,15);
    putpixel(xc-x,yc+y,15);
    putpixel(xc+x,yc-y,15);
    putpixel(xc-x,yc-y,15);
    putpixel(xc+y,yc+x,15);
    putpixel(xc-y,yc+x,15);
    putpixel(xc+y,yc-x,15);
    putpixel(xc-y,yc-x,15);
}

void main()
{
    int xc,yc,r,x,y,p;
    int gd=DETECT,gm;

    clrscr();
    initgraph(&gd,&gm,"C:/TURBOC3/BIN");

    printf("Enter the center co-ordinates of the circle:\n");
    scanf("%d%d",&xc,&yc);
    printf("Enter the radius of the circle:\n");
    scanf("%d",&r);

    x=0;
    y=r;
    plotpoint(xc,yc,x,y);
    p=1-r;

    while(x<y)
    {
        if(p<0)
            x=x+1;
        else
        {
            x=x+1;
            y=y-1;
        }

        if(p<0)
            p=p+2*x+1;
        else
            p=p+2*(x-y)+1;

        plotpoint(xc,yc,x,y);
    }

    getch();
    closegraph();
}
