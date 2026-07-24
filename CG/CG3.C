#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>

int n,i,a[20][2],fx,fy,y,tx,ty,temp;
float sx,sy,k;

void input()
{
    printf("Enter the no. of vertices:");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nEnter the co-ordinates:");
        scanf("%d%d",&a[i][0],&a[i][1]);
    }
}

void output()
{
    cleardevice();

    for(i=0;i<n-1;i++)
    {
        line(a[i][0],a[i][1],a[i+1][0],a[i+1][1]);
    }
    line(a[i][0],a[i][1],a[0][0],a[0][1]);
}

void rotation()
{
    output();

    printf("Enter the rotating angle:");
    scanf("%d",&y);
    printf("Enter the pivot point:");
    scanf("%d%d",&fx,&fy);

    k=(y*3.14)/180;

    for(i=0;i<=n;i++)
    {
        temp=a[i][0]-a[i][1]*sin(k);
        a[i][1]=a[i][0]*sin(k)+a[i][1];
        a[i][0]=temp;
    }

    output();
}

void scaling()
{
    output();

    printf("\n\n\n\nEnter the scaling factor sx,sy:");
    scanf("%f%f",&sx,&sy);
    printf("Enter the fixed point:");
    scanf("%d%d",&fx,&fy);

    for(i=0;i<=n;i++)
    {
        a[i][0]=a[i][0]*sx+fy*(1-sx);
        a[i][1]=a[i][1]*sy+fy*(1-sy);
    }

    rotation();
}

void composite()
{
    output();

    printf("Enter the transformation vertex tx,ty:");
    scanf("%d%d",&tx,&ty);

    for(i=0;i<=n;i++)
    {
        a[i][0]=a[i][0]+tx;
        a[i][1]=a[i][1]+ty;
    }

    scaling();
}

void main()
{
    int gd=DETECT,gm;

    initgraph(&gd,&gm,"C:/TURBOC3/BIN");

    input();
    composite();

    getch();
}
