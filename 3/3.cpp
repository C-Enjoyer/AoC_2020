// 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>

#define XMAX 31
#define STEPX 1
#define STEPY 2

int main()
{
    char grid[XMAX][3000];
    std::string line;
    int xmax = XMAX;
    int ymax = 0;
    int numtree = 0;
    int numspace = 0;
    int numother = 0;

    int bumptree = 0;
    int bumpspace = 0;
    int bumpother = 0;
    while (1)
    {
        std::getline(std::cin, line);
        if (!line.length()) break;

        for (uint16_t i = 0;i < XMAX;i++)
        {
            grid[i][ymax] = line[i];
        }
        ymax++;
    }

    for (uint16_t x = 0;x < xmax;x++)
    {
        for (uint16_t y = 0;y < ymax;y++)
        {
            if (grid[x][y] == '#') numtree++;
            else if (grid[x][y] == '.') numspace++;
            else numother++;
        }
    }

    printf("Grid is %d * %d\nTrees: %d, Spaces: %d, Other: %d\n", xmax, ymax, numtree, numspace, numother);

    int curx = 0;

    for (int cury = 0;cury < ymax; cury+=STEPY)
    {
        if (grid[curx][cury] == '#') bumptree++;
        else if (grid[curx][cury] == '.') bumpspace++;
        else bumpother++;

        if (curx + STEPX < xmax) curx += STEPX;
        else curx = (curx + STEPX) - xmax;
    }

    printf("On the way out:\nTrees: %d, Spaces: %d, Other: %d\n", bumptree, bumpspace, bumpother);

    

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
