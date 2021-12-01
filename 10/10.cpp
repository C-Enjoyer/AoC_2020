// 10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#define MAX 500
#define DIF 3

int cnt_dif1 = 0;
int cnt_dif3 = 0;
uint64_t ways = 0;
uint64_t depth = 0,
max_depth = 0;
uint64_t totalcall = 0;

void strange1(int*, int, int, int);
void strange2(int*, int, int, int, int);
void swap(int*, int*);
void bubbleSort(int[], int);

bool main()
{
    int arr[MAX] = { 0 };
    int arr_max = 0;
    int myadapter = 0;
    int maxjolts = 0;

    while (1)
    {
        std::string line;
        std::getline(std::cin, line);
        if (line.length())
        {
            int number = 0;
            sscanf(line.c_str(), "%d", &number);
            arr[arr_max] = number;
            arr_max++;
        }
        else break;
    }

    for (int i = 0;i < arr_max;i++)
    {
        if (arr[i] > maxjolts) maxjolts = arr[i];
    }
    myadapter = maxjolts + DIF;

    printf("Adapter = %d, jolts: %d\n", myadapter, maxjolts);

    /*strange1(arr, arr_max, 0, maxjolts);
    cnt_dif3++;

    printf("1dif: %d, 3dif: %d, Result: %d\n", cnt_dif1, cnt_dif3, cnt_dif3 * cnt_dif1);
    */

    bubbleSort(arr, arr_max);

    for (int i = 0;i < arr_max;i++)
    {
        printf("%d\n",arr[i]);
    }
    /*
    strange2(arr, arr_max, 0, maxjolts, 0);

    printf("There are %d ways you dumb cunt!!!\n", ways);
    printf("Max_depth: %llu, totalcall: %llu\n", max_depth, totalcall);*/

    uint64_t posways[MAX] = { 0 };

    for (int i = arr_max - 1; i > -2;i--)
    {
        if (i && arr[i] == maxjolts) posways[i] = 1;
        else
        {
            uint8_t suc_number = 0;
            int number = 0;
            if (i == -1) number = 0;
            else number = arr[i];

            if (number < arr[i + 1] && number + DIF >= arr[i + 1]) suc_number |= (1 << 0);
            if (number < arr[i + 2] && number + DIF >= arr[i + 2]) suc_number |= (1 << 1);
            if (number < arr[i + 3] && number + DIF >= arr[i + 3]) suc_number |= (1 << 2);

            if (suc_number)
            {
                if (i == -1)
                {
                    if (suc_number & (1 << 0)) ways += posways[i + 1];
                    if (suc_number & (1 << 1)) ways += posways[i + 2];
                    if (suc_number & (1 << 2)) ways += posways[i + 3];
                }
                else
                {
                    if(suc_number & (1 << 0)) posways[i] += posways[i + 1];
                    if(suc_number & (1 << 1)) posways[i] += posways[i + 2];
                    if(suc_number & (1 << 2)) posways[i] += posways[i + 3];
                }
            }
            
        }
    }

    
    for (int i = 0;i < arr_max;i++)
    {
        printf("Ways for %d is %llu\n", arr[i], posways[i]);
    }

    printf("Total Ways possible: %llu", ways);

}



/*
void strange1(int* arr, int arr_max, int act, int goal)
{
    int lowest = goal;
    bool success = false;
    for (int i = 0;i < arr_max;i++)
    {
        if (arr[i] > act && arr[i] <= act + DIF)
        {
            if (arr[i] <= lowest) lowest = arr[i];
        }
    }

    if (lowest - act == 3) cnt_dif3++;
    if (lowest - act == 1) cnt_dif1++;
    printf("OK with %d to %d\n", act, lowest);
    printf("dif1 = %d, dif3 = %d\n", cnt_dif1, cnt_dif3);

    if (!(lowest==goal)) strange1(arr, arr_max, lowest, goal);
    else printf("Alles durch\n");
}
*/



/*void strange2(int* arr, int arr_max, int act, int goal,int lower)
{
    for (int i = lower;i < arr_max;i++)
    {
        if (arr[i] > act && arr[i] <= act + DIF)
        {
            //printf("OK with %d to %d\n",act, arr[i]);
            if (arr[i] == goal)
            {
                //printf("Found way!!!\n");
                ways++;
            }
            else strange2(arr, arr_max, arr[i], goal, lower+1);
        }
        if (arr[i] > act + DIF) break;
    }
}*/

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort  
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
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
