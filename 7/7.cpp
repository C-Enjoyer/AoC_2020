// 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <iostream>
#include <string>

//#define _CRT_SECURE_NO_WARNINGS



#define MAXDIF 10

#define MAXBAGS 1000

typedef struct bag_t
{
    std::string color = {0};
    int difbags = 0;
    int i_num[MAXDIF] = {0};
    std::string i_colors[MAXDIF];
}bag_t;

void print_bag(bag_t);
bag_t get_bag(std::string);
void search_bag(std::string);
void inbag(std::string name, uint64_t);
bag_t find_mybag(std::string);

bag_t bags[MAXBAGS];
int numbags = 0;
uint64_t totalcount = 0;
int root = 1;
int prev_num = 0;
std::string mybag = "shiny gold";
bool already[MAXBAGS] = { false };
int branch = 0;


int main()
{
    while (1)
    {
        std::string line;
        std::getline(std::cin, line);

        if (line.length())
        {
            bags[numbags] = get_bag(line);
            numbags++;
            //print_bag(bags[numbags]);
        }
        else break;
    }

    //search_bag(mybag);

    //bag_t bag_my = find_mybag(mybag);
    uint64_t number = 1;
    inbag(mybag, number);

    printf("Result: %u\n", totalcount);
}

void inbag(std::string name, uint64_t num)
{
    uint64_t helper = 0;
    for (int i = 0;i < numbags;i++)
    {
        if (bags[i].color == name)
        {
            //num *= bags[i]
            for (int j = 0;j < bags[i].difbags;j++)
            {
                branch++;
                helper += num * bags[i].i_num[j];
                printf("%s contains %d %s\n", name.c_str(), bags[i].i_num[j], bags[i].i_colors[j].c_str());
                printf("Branch = %d\n", branch);
                printf("num = %llu\n", num);
                inbag(bags[i].i_colors[j], num * bags[i].i_num[j]);
            }
        }
    }
    branch--;
    totalcount += helper;
    printf("End of branch\n");
    printf("num = %llu totalcount = %llu\n", num, totalcount);
    
}

bag_t find_mybag(std::string name)
{
    for (int i = 0;i < numbags;i++)
    {
        if (bags[i].color == name)
        {
            return bags[i];
        }
    }
}


void search_bag(std::string actual)
{
    for (int i = 0;i < numbags;i++)
    {
        for (int j = 0;j < bags[i].difbags;j++)
        {
            if (bags[i].i_colors[j] == actual)
            {
                printf("%s can carry %d of %s\n", bags[i].color.c_str(), bags[i].i_num[j], actual.c_str());
                if (!already[i])
                {
                    already[i] = true;
                    totalcount++;
                    search_bag(bags[i].color);
                }

            }
        }
    }
    if (actual != mybag) printf("\n");
}

void print_bag(bag_t bag)
{
    printf("\n\nBagcolor: %s\nOther colors: %d\n", bag.color.c_str(), bag.difbags);
    for (uint8_t i = 0;i < bag.difbags;i++)
    {
        printf("%d of %s\n", bag.i_num[i], bag.i_colors[i].c_str());
    }
    printf("\n");
}

bag_t get_bag(std::string in)
{
    bag_t bag;
    std::string line = in;

    bag.color = line.substr(0, line.find("bags contain") - 1);
    line.erase(0, bag.color.length() + 13);
    if (line[1] == 'n')
    {
        bag.difbags = 0;
        return bag;
    }
    int i = 0;
    while (1)
    {
        int nextend = line.find(",");
        bool last = false;
        std::string container;
        if (nextend == std::string::npos)
        {
            nextend = line.find(".");
            last = true;
        }

        container = line.substr(0, nextend);
        container.erase(0, 1);

        //printf("Container is: %s\n", container.c_str());

        char colorhelper[200] = { 0 };
        sscanf(container.c_str(), "%d %[^\n]", &bag.i_num[i], colorhelper);
        bag.i_colors[i] = colorhelper;
        int bagat = bag.i_colors[i].find("bag");
        bag.i_colors[i].erase(bagat-1, bag.i_colors[i].length());
        i++;
        bag.difbags = i;



        line.erase(0, nextend + 1);


        if (last) break;
    }

    return bag;
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
