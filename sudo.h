#ifndef SUDO_H
#define SUDO_H


class sudo
{
public:
    sudo();
    bool Con_Judge(int x,int y,int var);
    void reset(int x,int y);
    void RandY(int Ry[9]);
    bool is_full(int x , int var);
    void DigHole(int Count);
    ~sudo();

public:
    int x;
    int y;
    int var;
    int hole[9][9];
    int sudu[9][9];
};

#endif // SUDO_H
