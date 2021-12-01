// 12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <complex> 
#include <math.h>

using namespace std;

typedef struct wp_t
{
    int ns; //n+ s-
    int ew; //e+ w-
};


int turn(int, int, int);
void rotate(wp_t*, wp_t*, int, int);


int main()
{
    /*int ew = 0; //e+ w-
    int ns = 0; //n+ s-
    int facing = 1; //n=0,e=1,s=2,w=3*/

    wp_t ship = { 0,0 };
    wp_t wp = { 1,10 };

    while (1)
    {
        string line;
        getline(cin, line);
        if (line.length())
        {
            char dir_in = '\0';
            int number = 0;
            sscanf(line.c_str(), "%c%d", &dir_in, &number);

            if (dir_in == 'N')
            {
                wp.ns += number;
            }
            else if (dir_in == 'S')
            {
                wp.ns -= number;
            }
            else if (dir_in == 'E')
            {
                wp.ew += number;
            }
            else if (dir_in == 'W')
            {
                wp.ew -= number;
            }
            else if (dir_in == 'L')
            {
                rotate(&ship, &wp, 0, number);
            }
            else if (dir_in == 'R')
            {
                rotate(&ship, &wp, 1, number);
            }
            else if (dir_in == 'F')
            {
                wp_t dif = { ship.ns - wp.ns, ship.ew - wp.ew };
                ship.ns -= dif.ns * number;
                ship.ew -= dif.ew * number;
                wp.ns -= dif.ns * number;
                wp.ew -= dif.ew * number;
            }

            printf("Current shipposition: ns = %d, ew = %d\n", ship.ns, ship.ew);
            printf("Current wpposition: ns = %d, ew = %d\n", wp.ns, wp.ew);
            /*char dir_in = '\0';
            int number = 0;
            sscanf(line.c_str(), "%c%d", &dir_in, &number);

            if (dir_in == 'N')
            {
                ns += number;
            }
            else if (dir_in == 'S')
            {
                ns -= number;
            }
            else if (dir_in == 'E')
            {
                ew += number;
            }
            else if (dir_in == 'W')
            {
                ew -= number;
            }
            else if (dir_in == 'L')
            {
                facing = turn(facing, 0, number);
            }
            else if (dir_in == 'R')
            {
                facing = turn(facing, 1, number);
            }
            else if (dir_in == 'F')
            {
                if (facing == 0) ns += number;
                else if(facing == 1) ew += number;
                else if (facing == 2) ns -= number;
                else if (facing == 3) ew -= number;
            }
            //printf("Dir is: %c with number %d\n", dir_in, number);
            //printf("NS: %d, EW: %d, Result: %d\n", ns, ew, abs(ns) + abs(ew));*/


        }
        else break;
    }

    printf("NS: %d, EW: %d, Result: %d\n", ship.ns, ship.ew, abs(ship.ns) + abs(ship.ew));
    

    
}

void rotate(wp_t* ship, wp_t* wp, int dir, int deg_in)
{
    int angle = 0; //0=l, 1=r, 2 = 180

    if (dir == 0) //l
    {
        if (deg_in == 270) angle = 90;
        else if (deg_in == 180) angle = 180;
        else angle = 270;
    }
    else if (dir == 1) //r
    {
        if (deg_in == 270) angle = 270;
        else if (deg_in == 180) angle = 180;
        else angle = 90;
    }

    //wp_t dif = { wp->ns - ship->ns , wp->ew - ship->ew };
    

    double coss = cos((M_PI * angle) / 180);
    double sins = sin((M_PI * angle) / 180);

    double temp;

    wp_t dif = { wp->ns - ship->ns , wp->ew - ship->ew };

    double cos_side = double (dif.ns) * coss,
        sin_side = double (dif.ew) * sins;

    temp = (cos_side - sin_side) + ship->ns;

    cos_side = double (dif.ew) * coss;
    sin_side = double (dif.ns) * sins;

    wp->ew = (sin_side + cos_side) + ship->ew;
    wp->ns = temp;




    /*if (rott == 0)//left
    {
        wp->ns = ship->ns + dif.ew;
        wp->ew = ship->ew - dif.ns;
    }
    else if (rott == 1) //right
    {
        wp->ns = ship->ns - dif.ew;
        wp->ew = ship->ew + dif.ns;
    }
    else //180
    {
        wp->ns = ship->ns - dif.ns;
        wp->ew = ship->ew + dif.ew;
    }*/
}

int turn(int facing, int dir, int deg_in)
{
    int rott = 0; //0=l, 1=r, 2 = 180

    if (dir == 0) //l
    {
        if (deg_in == 270) rott = 1;
        else if (deg_in == 180) rott = 2;
        else rott = 0;
    }
    else if (dir == 1) //r
    {
        if (deg_in == 270) rott = 0;
        else if (deg_in == 180) rott = 2;
        else rott = 1;
    }

    if (rott == 0)//left
    {
        if (facing > 0) facing--;
        else facing = 3;
    }
    else if (rott == 1) //right
    {
        if (facing < 3) facing++;
        else facing = 0;
    }
    else
    {
        if (facing == 0) facing = 2;
        else if (facing == 1) facing = 3;
        else if (facing == 2) facing = 0;
        else if (facing == 3) facing = 1;
    }
    return facing;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
