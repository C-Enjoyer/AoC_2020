// 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <string.h>
#include <string>

int main()
{
    std::string line;
    int lower = 0, upper = 0;
    char c = '\0';
    char s[100] = "\0";
    int result = 0;
    int all = 0;

    while (1)
    {
        std::getline(std::cin, line);
        if (!line.length()) break;
        all++;
        sscanf(line.c_str(), "%d-%d %c: %s", &lower, &upper, &c, s);

        int count = 0;
        /*for (uint16_t i = 0;i < strlen(s);i++)
        {
            if (s[i] == c)
            {
                count++;
            }
        }

        if (count >= lower && count <= upper)
        {
            printf("\n\nOK\n\n");
            result++;
        }*/

        if (s[lower - 1] == c || s[upper - 1] == c)
        {
            if (!(s[lower - 1] == c && s[upper - 1] == c))
            {
                printf("\n\nOK\n\n");
                result++;
            }
        }

        //sscanf(line.c_str(), "%c", &c);
        printf("Line ok with %d to %d of %c and pw: %s\n\n", lower, upper, c, s);
    }

    printf("\n\nResult: %d of %d\n\n",result,all);
    

    /*while ( != 0)
    {
        printf("Line ok with %d to %d of %c and pw: %s\n\n", lower, upper, c, s);
        s[0] = '\0';
    }*/
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
