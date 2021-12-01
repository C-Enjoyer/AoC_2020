// 11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef enum x_t
{
    x_none = 0,
    x_left = 1,
    x_right = 2
}x_t;

typedef enum y_t
{
    y_none = 0,
    y_up = 1,
    y_down = 2
}y_t;

void grid_print(vector<vector<char>>, int, int);
vector<vector<char>> grid_copy(vector<vector<char>>, int, int);
vector<vector<char>> grid_do_nasty_stuff(vector<vector<char>>, int, int);
char grid_get_part(vector<vector<char>>, int, int, x_t, y_t, int, int);
bool grid_equals(vector<vector<char>>, vector<vector<char>>, int, int);
uint64_t grid_count_char(char, vector<vector<char>>, int, int);

int main()
{
    vector<vector<char>> grid1;
    vector<vector<char>> grid2;

    int size_x = 0;
    int size_y = 0;
    while (1)
    {
        string line;
        getline(cin, line);
        if (line.length())
        {
            size_y = line.length();
            grid1.push_back(vector<char>());
            grid2.push_back(vector<char>());
            for (int i = 0;i < size_y;i++)
            {
                grid1[size_x].push_back(line[i]);
                grid2[size_x].push_back(line[i]);
            }
            size_x++;
        }
        else break;
    }


    printf("Grid is %d * %d\n", size_x, size_y);

    //grid2 = grid_do_nasty_stuff(grid1, size_x, size_y);

    while (1)
    {
        grid2 = grid_do_nasty_stuff(grid1, size_x, size_y);
        if (grid_equals(grid1, grid2, size_x, size_y))
        {
            printf("No more Changes!\n");
            break;
        }
        else
        {
            grid_print(grid1, size_x, size_y);
            grid1 = grid_copy(grid2, size_x, size_y);
        }
    }

    //grid_print(grid2, size_x, size_y);

    uint64_t count = grid_count_char('#', grid2, size_x, size_y);
    printf("%llu seats are occupied\n", count);
}

vector<vector<char>> grid_do_nasty_stuff(vector<vector<char>> grid_in, int xmax, int ymax)
{
    vector<vector<char>> grid_out = grid_copy(grid_in, xmax, ymax);
    for (int x = 0;x < xmax;x++)
    {
        for (int y = 0;y < ymax;y++)
        {
            if (grid_in[x][y] == 'L')
            {
                int o = 8;

                if (grid_get_part(grid_in, x, y, x_left, y_up, xmax, ymax) != '#') o--;
                if (grid_get_part(grid_in, x, y, x_left, y_none, xmax, ymax) != '#') o--;
                if (grid_get_part(grid_in, x, y, x_left, y_down, xmax, ymax) != '#') o--;
                if (grid_get_part(grid_in, x, y, x_none, y_up, xmax, ymax) != '#') o--;
                if (grid_get_part(grid_in, x, y, x_none, y_down, xmax, ymax) != '#') o--;
                if (grid_get_part(grid_in, x, y, x_right, y_up, xmax, ymax) != '#') o--;
                if (grid_get_part(grid_in, x, y, x_right, y_none, xmax, ymax) != '#') o--;
                if (grid_get_part(grid_in, x, y, x_right, y_down, xmax, ymax) != '#') o--;

                if (o == 0)
                {
                    grid_out[x][y] = '#';
                }
                else
                {
                    grid_out[x][y] = grid_in[x][y];
                }
            }
            else if(grid_in[x][y] == '#')
            {
                int o = 0;
                if (grid_get_part(grid_in, x, y, x_left, y_up, xmax, ymax) == '#') o++;
                if (grid_get_part(grid_in, x, y, x_left, y_none, xmax, ymax) == '#') o++;
                if (grid_get_part(grid_in, x, y, x_left, y_down, xmax, ymax) == '#') o++;
                if (grid_get_part(grid_in, x, y, x_none, y_up, xmax, ymax) == '#') o++;
                if (grid_get_part(grid_in, x, y, x_none, y_down, xmax, ymax) == '#') o++;
                if (grid_get_part(grid_in, x, y, x_right, y_up, xmax, ymax) == '#') o++;
                if (grid_get_part(grid_in, x, y, x_right, y_none, xmax, ymax) == '#') o++;
                if (grid_get_part(grid_in, x, y, x_right, y_down, xmax, ymax) == '#') o++;

                if (o >= 5)
                {
                    grid_out[x][y] = 'L';
                }
                else
                {
                    grid_out[x][y] = grid_in[x][y];
                }

            }
            else
            {
                grid_out[x][y] = grid_in[x][y];
            }

        }
    }
    return grid_out;
}

char grid_get_part(vector<vector<char>> grid, int x, int y, x_t x_dir, y_t y_dir, int xmax, int ymax)
{
    int x_in = x;
    int y_in = y;
    // check valid
    /*if (x_dir == x_left && x <= 0) return ' ';
    if (x_dir == x_right && (x >= (xmax - 1))) return ' ';

    if (y_dir == y_up && y <= 0) return ' ';
    if (y_dir == y_down && (y >= (ymax - 1))) return ' ';*/

    //shift
    /*if (x_dir == x_left) x--;
    else if (x_dir == x_right) x++;

    if (y_dir == y_up) y--;
    else if (y_dir == y_down) y++;*/

    if (x_dir == x_left && y_dir == y_up)
    {
        for (;x > -1 && y > -1;x--,y--)
        {
            if (x != x_in && y!=y_in)
            {
                if (grid[x][y] == 'L') return '.';
                if (grid[x][y] == '#') return '#';
            }
        }
    }
    else if (x_dir == x_none && y_dir == y_up)
    {
        for (;y > -1; y--)
        {
            if (y != y_in)
            {
                if (grid[x][y] == 'L') return '.';
                if (grid[x][y] == '#') return '#';
            }
        }
    }
    else if (x_dir == x_right && y_dir == y_up)
    {
        for (;x < xmax && y > -1;x++, y--)
        {
            if (x != x_in && y != y_in)
            {
                if (grid[x][y] == 'L') return '.';
                if (grid[x][y] == '#') return '#';
            }
        }
    }
    else if (x_dir == x_left && y_dir == y_none)
    {
        for (;x > -1;x--)
        {
            if (x != x_in)
            {
                if (grid[x][y] == 'L') return '.';
                if (grid[x][y] == '#') return '#';
            }
        }
    }
    else if (x_dir == x_right && y_dir == y_none)
    {
        for (;x < xmax;x++)
        {
            if (x != x_in)
            {
                if (grid[x][y] == 'L') return '.';
                if (grid[x][y] == '#') return '#';
            }
        }
    }
    else if (x_dir == x_left && y_dir == y_down)
    {
        for (;x > -1 && y < ymax;x--, y++)
        {
            if (x != x_in && y != y_in)
            {
                if (grid[x][y] == 'L') return '.';
                if (grid[x][y] == '#') return '#';
            }
        }
    }
    else if (x_dir == x_none && y_dir == y_down)
    {
        for (; y < ymax; y++)
        {
            if (y != y_in)
            {
                if (grid[x][y] == 'L') return '.';
                if (grid[x][y] == '#') return '#';
            }
        }
    }
    else if (x_dir == x_right && y_dir == y_down)
    {
        for (;x <xmax && y < ymax;x++, y++)
        {
            if (x != x_in && y != y_in)
            {
                if (grid[x][y] == 'L') return '.';
                if (grid[x][y] == '#') return '#';
            }
        }
    }

    //return
    return '.';
}

void grid_print(vector<vector<char>> grid, int xmax, int ymax)
{
    for (int x = 0;x < xmax;x++)
    {
        for (int y = 0;y < ymax;y++)
        {
            printf("%c", grid[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

vector<vector<char>> grid_copy(vector<vector<char>> grid_in, int xmax, int ymax)
{
    vector<vector<char>> grid_out;
    for (int x = 0;x < xmax;x++)
    {
        grid_out.push_back(vector<char>());
        for (int y = 0;y < ymax;y++)
        {
            grid_out[x].push_back(grid_in[x][y]);
        }
    }
    return grid_out;
}

bool grid_equals(vector<vector<char>> grid1, vector<vector<char>> grid2, int xmax, int ymax)
{
    for (int x = 0;x < xmax;x++)
    {
        for (int y = 0;y < ymax;y++)
        {
            if (grid1[x][y] != grid2[x][y]) return false;
        }
    }
    return true;
}

uint64_t grid_count_char(char c, vector<vector<char>> grid, int xmax, int ymax)
{
    uint64_t count = 0;
    for (int x = 0;x < xmax;x++)
    {
        for (int y = 0;y < ymax;y++)
        {
            if (grid[x][y] == c) count++;
        }
    }
    return count;
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
