// 9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <string>

#define MAXNUM 2000
#define PREAMBLE 25

bool is_ok(uint64_t*, uint64_t);

int main()
{
    uint64_t nums[MAXNUM] = { 0 };
    int32_t maxnums = 0;
    while (1)
    {
        std::string line;
        std::getline(std::cin, line);
        if (line.length())
        {
            sscanf(line.c_str(), "%llu", &nums[maxnums]);
            maxnums++;
        }
        else break;
    }

    printf("Got %d numbers\n", maxnums);

    uint64_t preambles[PREAMBLE] = { 0 };
    uint32_t pre_cnt = 0;
    uint64_t result = 0;

    for (uint32_t i = 0;i < maxnums;i++)
    {
        //printf("Number is: %llu\n", nums[i]);
        if (i < PREAMBLE) //first preamble
        {
            preambles[pre_cnt] = nums[i];
            pre_cnt++;
        }
        else
        {
            if (!is_ok(preambles, nums[i]))
            {
                printf("Afuera at %llu\n", nums[i]);
                result = nums[i];
                break;
            }
            
            if (pre_cnt < PREAMBLE - 1) pre_cnt++;
            else pre_cnt = 0;
            preambles[pre_cnt] = nums[i];
        }
    }

    printf("Result was %llu\n", result);

    uint32_t lower = 0;
    uint32_t upper = 0;
    uint64_t cursum = 0;

    for (uint32_t i = 0;i < maxnums;i++)
    {
        if (cursum + nums[i] == result)
        {
            printf("Hurray!!!\n");
            break;
        }
        else if (cursum + nums[i] > result)
        {
            printf("Too high\n");
            while (cursum + nums[i] > result)
            {
                cursum -= nums[lower];
                lower++;
            }

            if (cursum + nums[i] == result)
            {
                printf("Hurray!!!\n");
                break;
            }

            cursum += nums[i];
            upper++;
        }
        else
        {
            printf("Too low\n");
            cursum += nums[i];
            upper++;
        }
    }

    printf("From %d to %d\n", lower, upper);
    uint64_t low = 1000000000000000;
    uint64_t high = 0;

    for (uint32_t i = lower;i < upper;i++)
    {
        if (nums[i] > high) high = nums[i];
        if (nums[i] < low) low = nums[i];
    }

    printf("%llu + %llu = %llu\n", low, high, low + high);

    printf("Fertig\n");
}

bool is_ok(uint64_t* pre, uint64_t num)
{
    for (uint32_t i = 0;i < PREAMBLE;i++)
    {
        for (uint32_t j = 0;j < PREAMBLE;j++)
        {
            if (pre[i] + pre[j] == num) return 1;
        }
    }
    return 0;
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
