// 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#define _CRT_SECURE_NO_WARNINGS
#define LENGTH 10

int main()
{
    int highestid = 0;
    bool ids[871] = { false };
    while (1)
    {
        std::string line;
        std::getline(std::cin, line);
        if (!line.length()) break;
        uint8_t row = 0;
        uint8_t column = 0;
        int id = 0;
        for (uint8_t i = 0;i < LENGTH;i++)
        {
            if (i >= 0 && i <= 6)
            {
                if (line[i] == 'B') row |= (1 << (6 - i));
            }
            else
            {
                if (line[i] == 'R') column |= (1 << (9 - i));
            }
        }
        id = row * 8 + column;
        if (id > highestid) highestid = id;
        printf("Row: %d, column: %d, id: %d\n", row, column, id);
        ids[id] = true;
    }

    for (uint16_t i = 0;i < 871;i++)
    {
        if (!ids[i]) printf("ID: %d not seated\n",i);
    }

    printf("Highest ID: %d\n", highestid);

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
