// 16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

#define TICKET_NUMS 20

typedef struct range_t
{
    string text = "";
    int as = 0, ae = 0, bs = 0, be = 0;
}range_t;

typedef struct ticket_t
{
    int nums[TICKET_NUMS] = { 0 };
}ticket_t;

bool ticket_check_valid(ticket_t, range_t*, int);
uint64_t ticket_get_error_rate(ticket_t, range_t*, int);
bool ticket_check_num(ticket_t, int, range_t*, int);

range_t range[40];
int ranges = 0;

ticket_t ticket_my;
ticket_t ticket[500];
ticket_t ticket_valid[500];
int tickets = 0;


int main()
{
    //strange things
    while (1)
    {
        string line;
        getline(cin, line);
        if (line.length())
        {
            int a=0, b=0, c=0, d=0;
            string text, sub;
            int pt = line.find(':');
            text = line.substr(0, pt);
            sub = line.substr(pt + 2);
            sscanf(sub.c_str(), "%d-%d or %d-%d", &a, &b, &c, &d);

            range[ranges].text = text;
            range[ranges].as = a;
            range[ranges].ae = b;
            range[ranges].bs = c;
            range[ranges].be = d;

            ranges++;
        }
        else break;
    }

    //my ticket
    while (1)
    {
        string line;
        getline(cin, line);
        if (line.length())
        {
            if (line[0] != 'y')
            {
                sscanf(line.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &ticket_my.nums[0], &ticket_my.nums[1], &ticket_my.nums[2], &ticket_my.nums[3], &ticket_my.nums[4], &ticket_my.nums[5], &ticket_my.nums[6], &ticket_my.nums[7], &ticket_my.nums[8], &ticket_my.nums[9], &ticket_my.nums[10], &ticket_my.nums[11], &ticket_my.nums[12], &ticket_my.nums[13], &ticket_my.nums[14], &ticket_my.nums[15], &ticket_my.nums[16], &ticket_my.nums[17], &ticket_my.nums[18], &ticket_my.nums[19]);
                printf("");
            }
        }
        else break;
    }

    //other
    while (1)
    {
        string line;
        getline(cin, line);
        if (line.length())
        {
            if (line[0] != 'n')
            {
                sscanf(line.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &ticket[tickets].nums[0], &ticket[tickets].nums[1], &ticket[tickets].nums[2], &ticket[tickets].nums[3], &ticket[tickets].nums[4], &ticket[tickets].nums[5], &ticket[tickets].nums[6], &ticket[tickets].nums[7], &ticket[tickets].nums[8], &ticket[tickets].nums[9], &ticket[tickets].nums[10], &ticket[tickets].nums[11], &ticket[tickets].nums[12], &ticket[tickets].nums[13], &ticket[tickets].nums[14], &ticket[tickets].nums[15], &ticket[tickets].nums[16], &ticket[tickets].nums[17], &ticket[tickets].nums[18], &ticket[tickets].nums[19]);
                tickets++;
            }
        }
        else break;
    }

    uint64_t tickets_valid = 0;

    for (int i = 0;i < tickets;i++)
    {
        if (ticket_check_valid(ticket[i], range, ranges)) ticket_valid[tickets_valid++] = ticket[i];
    }

    bool range_valids[40][TICKET_NUMS] = { false };



    for (int i = 0;i < TICKET_NUMS;i++)
    {
        int tickets_valid_counter[40] = { 0 };
        for (int j = 0;j < tickets_valid;j++)
        {
            for (int k = 0;k < ranges;k++)
            {
                if (ticket_check_num(ticket_valid[j], i, range, k))
                {
                    tickets_valid_counter[k] ++;
                }
            }
        }
        for (int k = 0;k < ranges;k++)
        {
            if (tickets_valid_counter[k] == tickets_valid)
            {
                range_valids[k][i] = true;
            }
        }
    }

    int range_is_num[40] = { -1 };
    for (int i = 0;i < ranges;i++) range_is_num[i] = -1;
    int ranges_cnt = 0;

    while (1)
    {
        for (int i = 0;i < TICKET_NUMS;i++)
        {
            //printf("col %d has following ok ranges: ",i);
            int cnt = 0;
            int val_num = 0;
            for (int j = 0;j < ranges;j++)
            {
                if (range_valids[j][i] && range_is_num[j] == -1)
                {
                    cnt++;
                    val_num = j;
                }
            }

            if (cnt == 1) // only 1 possibility left
            {
                printf("%s is surely col %d\n", range[val_num].text.c_str(), i);
                range_is_num[val_num] = i;
                ranges_cnt++;
                if (ranges_cnt == ranges)
                {
                    goto endofall;
                }
            }
            //printf("\n\n");
        }
    }


endofall:
    uint64_t result = 1;
    for (int i = 0;i < ranges;i++)
    {
        if (range[i].text.find("departure") != -1)
        {
            result *= ticket_my.nums[range_is_num[i]];
        }
    }

    printf("Result: %llu\n", result);


    //for()
    
}

bool ticket_check_valid(ticket_t tck, range_t *range_fun, int rng_num)
{
    for (int j = 0;j < TICKET_NUMS; j++) // all ticket nums
    {
        bool success = false;
        for (int i = 0;i < rng_num;i++) // all ranges
        {
            if (ticket_check_num(tck, j, range_fun, i))
            {
                success = true;
                break;
            }
        }
        if (!success)
        {
            return false;
        }
    }

    return true;
}

bool ticket_check_num(ticket_t tck, int num, range_t* range_fun, int rng_num)
{
    if ((tck.nums[num] >= range_fun[rng_num].as && tck.nums[num] <= range_fun[rng_num].ae) ||
        (tck.nums[num] >= range_fun[rng_num].bs && tck.nums[num] <= range_fun[rng_num].be))
    {
        return true;
    }
    return false;
}

uint64_t ticket_get_error_rate(ticket_t tck, range_t* range_fun, int rng_num)
{
    uint64_t error_rate = 0;
    for (int j = 0;j < TICKET_NUMS; j++) // all ticket nums
    {
        bool success = false;
        for (int i = 0;i < rng_num;i++) // all ranges
        {
            if ((tck.nums[j] >= range_fun[i].as && tck.nums[j] <= range_fun[i].ae) ||
                (tck.nums[j] >= range_fun[i].bs && tck.nums[j] <= range_fun[i].be))
            {
                success = true;
                break;
            }
        }
        if (!success)
        {
            error_rate += tck.nums[j];
        }
    }
    return error_rate;
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
