#include "sudo.h"
#include <QDebug>

sudo::sudo()
{
    x=0;
    y=0;
    var=0;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            sudu[i][j]=0;
            hole[i][j]=0;
        }
    }

}

bool sudo::Con_Judge(int x,int y,int var)
{
    if(sudu[x][y]!=0)
        return false;
    for(int i=0; i<9; i++)
    {
        if(sudu[x][i]==var)
            return false;
    }
    for(int j=0; j<9; j++)
    {
        if(sudu[j][y]==var)
            return false;
    }
    for(int i=x/3*3; i<x/3*3+3; i++)
    {
        for(int j=y/3*3; j<y/3*3+3; j++)
        {
            if(sudu[i][j]==var)
                return false;
        }
    }
    sudu[x][y]=var;
    return true;
}


void sudo::reset(int x,int y)
{
    sudu[x][y]=0;
}

void sudo::RandY(int Ry[9])
{
    int temp;
    for(int i=0; i<9; i++)
        Ry[i]=i;
    for(int i=0; i<9; i++)
    {
        int j;
        j=rand()%9;
        temp=Ry[j];
        Ry[j]=Ry[i];
        Ry[i]=temp;
    }
}

bool sudo::is_full(int x,int var)
{
    int Ry[9]= {0};
    RandY(Ry);
    for (int i=0; i<9; i++)
    {
        int y = Ry[i];
        if (Con_Judge(x, y, var))
        {
            if (x == 8)
            {

                if (var == 9 || is_full(0, var+1))
                    return true;
            }
            else
            {
                if (is_full(x+1, var))
                    return true;
            }
            reset(x,y);
        }
    }
    return false;

}

void sudo::DigHole(int Count)
{
    int index[81];
    int k;
    for (int i=0; i<81; i++)
    {
        hole[i / 9][i % 9] = 0;
        index[i] = i;
    }
    for (int i=0; i<Count; i++)
    {
        k = rand() % 81;
        int tmp = index[k];
        index[k] = index[i];
        index[i] = tmp;
    }
    for (int i=0; i<Count; i++)
    {
        hole[index[i] / 9][index[i] % 9] = 1;
    }
}



sudo::~sudo()
{

}

