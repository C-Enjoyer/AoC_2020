// 13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#define NO_ID 5000

using namespace std;

int main()
{
    int count = 0;
    int minutes = 0;
    int ids[500] = { 0 };
    int id_len = 0;
    while (1)
    {
        string line;
        getline(cin, line);

        if (line.length())
        {
            /*if (count == 0)
            {
                sscanf(line.c_str(), "%d", &minutes);
                //printf("Minutes = %d\n", minutes);
                count++;
            }
            else */if (count == 0)
            {
                int last_comma = -1;
                while (1)
                {
                    int next_comma = line.find(",", last_comma + 1);
                    //printf("Next comma = %d\n", next_comma);
                    int end = next_comma;
                    bool isend = false;
                    if (next_comma == -1)
                    {
                        isend = true;
                        end = line.length();
                    }
                    string test = line.substr(last_comma + 1, end - last_comma - 1);
                    if (test[0] == 'x')
                    {
                        //printf("Substring = %s, Number = x\n", test.c_str());
                        ids[id_len] = NO_ID;
                    }
                    else
                    {
                        int num = stoi(test, 0, 10);
                        //printf("Substring = %s, Number = %d\n", test.c_str(), num);
                        ids[id_len] = num;
                    }
                    id_len++;

                    if (isend) break;
                    last_comma = next_comma;
                }
            }
        }
        else
        {
            break;
        }

    }

    /*int mindif = minutes;
    int mindif_i = 0;
    //printf("Minutes = %d\n", minutes);
    for (int i = 0;i < id_len;i++)
    {
        //printf("ID = %d\n", ids[i]);
        if (ids[i] != NO_ID)
        {
            int dif = ids[i] * (minutes / ids[i]) + ids[i] - minutes;
            printf("MinDif for %d is %d\n", ids[i], dif);
            printf("NextBus for %d is %d\n", ids[i], ids[i] * (minutes / ids[i]) + ids[i]);
            if (dif < mindif)
            {
                mindif = dif;
                mindif_i = i;
            }
        }
    }

    printf("Result = %d * %d = %d\n", ids[mindif_i], mindif, ids[mindif_i] * mindif);*/

    int ggV = ids[0] * ids[id_len - 1];
    int offset = 0;
    int i = 1;
    while (1)
    {
        if ((id_len-1 + i * ids[id_len - 1]) % ids[0] == 0)
        {
            offset = id_len-1 + i * ids[id_len - 1];
            break;
        }
        i++;
    }

    printf("ggV is %d and offset is %d\n", ggV, offset);
    i = 0;
    uint64_t ts = offset;
    while (1)
    {
        ts += ggV;
        printf("TS is %d\n",ts);
        if (ts > 1068797) break;
        i++;
    }
    printf("Fock\n");
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
