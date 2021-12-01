// 15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

void write_last_app(uint64_t, uint64_t);
uint64_t get_last_app(uint64_t);
void write_spoken(uint64_t);

#define MAX 30000000

uint64_t apps[MAX] = { 0 };
uint64_t apps_spoken[MAX] = { 0 };
uint64_t num_cnt = 0;
uint64_t prev_num = 0;

int main()
{
    
    while (1)
    {
        string line;
        getline(cin, line);
        if (line.length())
        {
            int cma_old = -1;
            int cma_new = 0;
            while (1)
            {
                bool end = false;
                cma_new = line.find(",", cma_old + 1);
                if (cma_new == -1)
                {
                    cma_new = line.length();
                    end = true;
                }
                string test = line.substr(cma_old + 1, cma_new - cma_old - 1);

                prev_num = atoi(test.c_str());
                write_last_app(prev_num, num_cnt);
                write_spoken(prev_num);
                num_cnt++;
                
                cma_old = cma_new;
                if (end) break;
            }



        }
        else break;
    }

    uint64_t result = 0;

    while (1)
    {
        uint64_t new_num = 0;
        uint64_t last_app = get_last_app(prev_num);
        if (last_app) //already
        {
            new_num = num_cnt - last_app;
        }
        else //first time
        {
            new_num = 0;
        }

        write_last_app(prev_num, num_cnt-1);
        write_spoken(new_num);
        write_spoken(prev_num);

        //printf("Turn %llu was number %llu\n", (num_cnt + 1), new_num);


        prev_num = new_num;
        num_cnt++;
        if (num_cnt == MAX)
        {
            result = new_num;
            break;
        }

        //if (!(num_cnt % 100000)) printf("Cnt = %llu\n", num_cnt);
    }

    printf("Number was %llu\n",result);
}

uint64_t get_last_app(uint64_t element)
{
    if (apps_spoken[element] > 1)
    {
        return (apps[element] + 1);
    }
    return 0;
}

void write_last_app(uint64_t element, uint64_t app)
{
    apps[element] = app;
}

void write_spoken(uint64_t element)
{
    apps_spoken[element]++;
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
