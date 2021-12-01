// 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

int main()
{
    int n = 0;
    int64_t largest = 0;
    int first = 0, second = 0, third = 0;
    std::vector<int> in;

    while (scanf_s("%d", &n) != 0)
    {
        in.push_back(n);
    }

    for (uint16_t i = 0;i < in.size() ;i++)
    {
        for (uint16_t j = 0;j < in.size();j++)
        {
            for (uint16_t k = 0;k < in.size();k++)
            {
                if (in[i] + in[j] + in[k] == 2020)
                {
                    int64_t mult = in[i] * in[j] * in[k];
                    printf("\n%d * %d *%d = %d\n", in[i], in[j], in[k], mult);
                    if (mult > largest)
                    {
                        largest = mult;
                        first = i;
                        second = j;
                        third = k;
                    }
                }
            }

        }
    }

    printf("\n\nLargest multiplication is %d * %d * %d = %d\n\n", in[first], in[second], in[third], largest);

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
