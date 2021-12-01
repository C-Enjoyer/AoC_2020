// 6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#define FIRSTLETTER 'a'
#define LASTLETTER 'z'

int main()
{
    int overall = 0;
   
    while (1)
    {
        std::string group;
        std::string grouplines[20];
        int lines = 0;
        while (1)
        {
            std::string line;
            std::getline(std::cin, line);
            group += line;
            grouplines[lines] = line;
            lines++;
            if (!line.length())
            {
                lines -= 1;
                /*int count = 0;
                for (char c = FIRSTLETTER; c < LASTLETTER + 1; c++)
                {
                    if (group.find(c) != std::string::npos)
                    {
                        count++;
                    }
                }
                */

                int countall = 0;
                int countletter = 0;

                for (char c = FIRSTLETTER; c < LASTLETTER + 1; c++)
                {
                    countletter = 0;
                    for (int i = 0;i < lines;i++)
                    {
                        if (grouplines[i].find(c) != std::string::npos)
                        {
                            countletter++;
                        }
                    }

                    printf("%c found %d times and lines is %d\n", c, countletter, lines);
                    if (countletter == lines)
                    {
                        countall++;
                    }

                }

                overall += countall;

                printf("Count : %d\n", countall);
                break;
            }
            else if (line[0] == '.') goto end;

        }
    }

end:
    printf("Overall was %d\n", overall);


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
