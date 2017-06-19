#include <iostream>
#include <vector>
#include <graphics.h>

using namespace std;

struct point
{
    int x, y;
};
struct edge
{
    int ymax;
    double x,m;
    edge *link;
};
point getMousePoints();
void fillPoly(vector<point> poly);

int main()
{
    initwindow(640,480,"Scanline Polygon Fill");
    vector<point> poly;
    cout << "Enter Polygon Points (Right click to stop): ";
    while(!ismouseclick(WM_RBUTTONDOWN))
        poly.push_back(getMousePoints());
    poly.push_back(poly[0]);
    setcolor(WHITE);
    drawpoly(poly.size(), (int*) &poly[0]);
    fillPoly(poly);
    getch();
    closegraph();
    return 0;
}
point getMousePoints()
{
    point p;
    while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, p.x, p.y);
    return p;
}
void fillPoly(vector<point> poly)
{
    edge **getable;
    int i, n;
    n = poly.size()-1;
    int ymin, ymax;
    ymin = ymax = poly[0].y;
    for(i=1; i<n; i++)
    {
        if(poly[i].y<ymin)
            ymin = poly[i].y;
        else if(poly[i].y>ymax)
            ymax = poly[i].y;
    }
    getable = new edge*[ymax+1];
    memset(getable, 0, sizeof(edge*)*(ymax+1));
    for(i=1; i<=n; i++)
    {
        if(poly[i].y == poly[i-1].y)
            continue;
        edge *ptr = new edge;
        ptr->link = NULL;
        ptr->ymax = max(poly[i-1].y, poly[i].y);
        if(ptr->ymax == poly[i-1].y)
            ptr->x = poly[i].x;
        else
            ptr->x = poly[i-1].x;
        ptr->m = ((double)(poly[i].x-poly[i-1].x))/(poly[i].y-poly[i-1].y);
        int y = min(poly[i].y, poly[i-1].y);
        if(getable[y]==NULL)
            getable[y] = ptr;
        else
        {
            if(ptr->x<getable[y]->x || (ptr->x==getable[y]->x && ptr->m<getable[y]->m))
            {
                ptr->link = getable[y];
                getable[y] = ptr;
            }
            else
            {
                edge *p = getable[y];
                edge *prev = p;
                while(p!=NULL && (p->x<ptr->x || (p->x==ptr->x && p->m<ptr->m)))
                {
                    prev = p;
                    p = p->link;
                }
                prev->link = ptr;
                ptr->link = p;
            }
        }
    }
    setcolor(RED);
    edge *cur = getable[ymin];
    for(i=ymin; i<=ymax; i++)
    {
        line(cur->x, i, cur->link->x, i);
        edge *k = cur;
        while(k!=NULL)
            k = k->link;
        edge *p = cur;
        while(p!=NULL)
        {
            p->x += p->m;
            p = p->link;
        }
        if(i==ymax)
            break;
        edge *next = getable[i+1];
        if(next!=NULL)
        {
            p = cur;
            edge *fn, *ln, *t;
            fn = ln = NULL;
            while(1)
            {
                if(p==NULL)
                {
                    ln->link = next;
                    break;
                }
                else if(next==NULL)
                {
                    ln->link = p;
                    break;
                }
                if(p->x<next->x || (p->x==next->x && p->m>next->m))
                {
                    t = p;
                    p = p->link;
                }
                else
                {
                    t = next;
                    next = next->link;
                }
                if(fn==NULL)
                {
                    fn = ln = t;
                }
                else
                {
                    ln->link = t;
                    ln = t;
                }
            }
            t = fn;
            while(t!=NULL)
            {
                if(t->ymax==i+1)
                {
                    if(t==fn)
                    {
                        fn = fn->link;
                        delete t;
                        t = fn;
                    }
                    else
                    {
                        p->link = t->link;
                        delete t;
                        t = p->link;
                    }
                }
                else
                {
                    p = t;
                    t = t->link;
                }
            }
            cur = fn;
        }
        delay(10);
    }
}
