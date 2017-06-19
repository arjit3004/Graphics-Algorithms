#include <iostream>
#include <graphics.h>
#include <math.h>
#include "circle.h"
using namespace std;
void print1(int x,int y,int a,int col)
{
    int xleft=320,yright=240;
    print_circle(x,y,320,240,col);
    print_circle(x,y,xleft+y*sin(a*3.14/180),yright+y*cos(a*3.14/180),col);
    print_circle(x,y,xleft+y*sin((a+60)*3.14/180),yright+y*cos((a+60)*3.14/180),col);
    print_circle(x,y,xleft+y*sin((a+120)*3.14/180),yright+y*cos((a+120)*3.14/180),col);
    print_circle(x,y,xleft+y*sin((a+180)*3.14/180),yright+y*cos((a+180)*3.14/180),col);
    print_circle(x,y,xleft+y*sin((a+240)*3.14/180),yright+y*cos((a+240)*3.14/180),col);
    print_circle(x,y,xleft+y*sin((a+300)*3.14/180),yright+y*cos((a+300)*3.14/180),col);

}
int main()
{
    int x=0,z=0,a=0,f=0,y=25,i=0,xleft=320,O=0,yright=240;
    int gm=DETECT,gd;
    int choice;
    cout<<"1.Rotate at own axis\n";
    cout<<"Enter your choice\t";
    cin>>choice;
    if(choice==1)
    {
        initgraph(&gm,&gd,"C:\\TC\\BGI");
        x=0;
        for(i=0; i<100000; i++)
        {
            print1(x,y,a,1);
            delay(1000);
            print1(x,y,a,0);
            a+=5;
            if(y<=60&&f==0)
            {
                y++;
                if(y>=60)
                {
                  f=1;
                }
            }
            if(f==1)
            {
                y--;
                if(y==0)
                    f=0;
            }
        }
        getch();
        closegraph();
    }
    return 0;
}
