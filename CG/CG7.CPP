#include<graphics.h>
#include<iostream.h>
#include<conio.h>

int gd,gm,x1,y1,x2,y2,dep,ch;

void main()
{
    cout<<"\nenter the TOP-LEFT and BOTTOM-RIGHT CORNER:";
    cin>>x1>>y1>>x2>>y2;

    cout<<"\nenter the depth along z-axis";
    cin>>dep;

    do
    {
        cout<<"choose any projection:\n\t1.parallel projection\n\t2.perspective projection\n enter your choice:";
        cin>>ch;

        initgraph(&gd,&gm,"C:/TURBOC3/BIN");

        switch(ch)
        {
            case 1:
                rectangle(x2+100,y1,x2+100+dep,y2);
                outtextxy(x2+100,y1-10,"SIDEVIEW");

                rectangle(x1,y1,x2,y2);
                outtextxy(x1,y1-10,"FRONTVIEW");

                rectangle(x1,y1-(y2-y1),x2,x1+dep-(y2-y1));
                outtextxy(x1,y1-(y2-y1)-10,"TOPVIEW");

                getch();
                closegraph();
                break;

            case 2:
                bar3d(x1,y1,x2,y2,dep,1);
                getch();
                closegraph();
                break;
        }
    } while(ch<3);
}
