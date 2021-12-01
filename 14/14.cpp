// 14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

uint64_t get_add_from_trans(uint64_t);
bool is_in_trans(uint64_t);

uint64_t memory_trans[10000000] = { 0 };
uint64_t memory_trans_cnt = 0;
uint64_t memory[10000000] = { 0 };
uint64_t memory_max = 0;

uint64_t memory_sum = 0;
uint64_t end_xs_max = 0;

string mask_act = "";

int main()
{
    while (1)
    {
        string line;
        getline(cin, line);
        if (line.length())
        {
            if (line[1] == 'a')
            {
                char bits_c[200] = {0};
                sscanf(line.c_str(), "mask = %s", bits_c);
                mask_act = bits_c;
            }
            else if(line[1] == 'e')
            {
                int element = 0;
                uint64_t number = 0;
                sscanf(line.c_str(), "mem[%d] = %llu", &element, &number);

                //memory_sum -= memory[element];

                string endstring = "000000000000000000000000000000000000";
                int end_xs = 0;
                
                for (uint64_t i = 0;i < mask_act.length();i++)
                {
                    switch (mask_act[mask_act.length() - 1 - i])
                    {
                        case 'X':
                        {
                            endstring[i] = 'X';
                            end_xs++;
                        }break;
                        case '0':
                        {
                            if (element & ((uint64_t)1 << i)) endstring[i] = '1';//memory[element] |= ((uint64_t)1 << i);
                            else endstring[i] = '0';//memory[element] &= ~((uint64_t)1 << i);
                        }break;
                        case '1':
                        {
                            //memory[element] |= ((uint64_t)1 << i);
                            endstring[i] = '1';
                        }break;
                    }
                }

                uint64_t cnt_strange = pow(2, end_xs);
                if (end_xs == 9)
                {
                    printf("Terst");
                }

                if (end_xs > end_xs_max) end_xs_max = end_xs;

                for (uint64_t cnt = 0; cnt < cnt_strange;cnt++)
                {
                    uint64_t bitcnt = 0;
                    uint64_t curnum = 0;
                    for (int i = 0;i < 37;i++)
                    {
                        if (endstring[i] == 'X')
                        {
                            if(cnt & ((uint64_t)1<<bitcnt)) curnum |= ((uint64_t)1 << i);
                            else curnum &= ~((uint64_t)1 << i);
                            bitcnt++;
                        }
                        else if (endstring[i] == '1')
                        {
                            curnum |= ((uint64_t)1 << i);
                        }
                        else if (endstring[i] == '0')
                        {
                            curnum &= ~((uint64_t)1 << i);
                        }
                    }
                    if(bitcnt != end_xs)
                    {
                        printf("Terst");
                    }


                    if (is_in_trans(curnum))
                    {
                        memory_sum -= memory[get_add_from_trans(curnum)];
                    }
                    else
                    { 
                        memory_trans[memory_trans_cnt] = curnum;
                        memory_trans_cnt++;
                    }
                    //else memory_trans[get_add_from_trans(curnum)] = curnum;
                    memory[get_add_from_trans(curnum)] = number;
                    memory_sum += number;
                    if (memory_sum >= 10446744073709551616)
                    {
                        printf("Fock!!!!");
                    }
                }
                printf("\n\nNew sum is %llu\n\n", memory_sum);
                
                
            }
        }
        else break;
    }

    

    uint64_t memory_sum2 = 0;
    for (uint32_t i = 0;i < memory_trans_cnt;i++)
    {
        memory_sum2 += memory[i];
        printf("Memory on %llu was %llu\n", memory_trans[i], memory[i]);
    }
    printf("The dumb sum is %llu you dumbass\n", memory_sum);
    printf("The dumb sum is %llu you dumbass\n", memory_sum2);

    for (uint32_t i = 0;i < memory_trans_cnt;i++)
    {
        for (uint32_t j = 0;j < memory_trans_cnt;j++)
        {
            if (memory_trans[i] == memory_trans[j] && i!=j)
            {
                printf("Oh god no\n");
            }
        }
    }

}

uint64_t get_add_from_trans(uint64_t num)
{
    for (uint64_t i = 0;i < memory_trans_cnt;i++)
    {
        if (memory_trans[i] == num) return i;
    }
    return 0;
}

bool is_in_trans(uint64_t num)
{
    for (uint64_t i = 0;i < memory_trans_cnt;i++)
    {
        if (memory_trans[i] == num) return true;
    }
    return false;
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
