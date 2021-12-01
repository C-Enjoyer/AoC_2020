// 8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_COMMANDS 1000

#include <iostream>
#include <string>

typedef struct command_t
{
    std::string cmd;
    int number = 0;
}command_t;

uint64_t do_command(command_t, uint32_t*);
bool is_infinite(command_t*, uint32_t, uint32_t*);

int main()
{
    command_t commands[MAX_COMMANDS];
    int commands_len = 0;
    while (1)
    {
        std::string line;
        std::getline(std::cin, line);
        if (line.length())
        {
            char cmd_c[4] = "\0";
            int number = 0;
            sscanf(line.c_str(), "%3s %d", cmd_c, &number);
            cmd_c[3] = '\0';
            std::string cmd = cmd_c;

            commands[commands_len].cmd = cmd;
            commands[commands_len].number = number;
            //printf("Command is: %s with number: %d\n", cmd_c, number);
            commands_len++;
        }
        else break;
    }

    printf("Got all commands\n");

    
    for (uint32_t i = 0;i < commands_len; i++)
    {
        bool infinite = true;
        bool success = false;
        uint32_t acc = 0;
        if (commands[i].cmd == "nop")
        {
            commands[i].cmd = "jmp";
            infinite = is_infinite(commands, commands_len, &acc);
            if (infinite)
            {
                commands[i].cmd = "nop";
            }
            else success = true;
        }
        else if (commands[i].cmd == "jmp")
        {
            commands[i].cmd = "nop";
            infinite = is_infinite(commands, commands_len, &acc);
            if (infinite)
            {
                commands[i].cmd = "jmp";
            }
            else success = true;
        }

        if (success)
        {
            printf("FOUND an option when changing line %d!!! Accumulator was %d\n", i, acc);
            break;
        }
    }

    /*bool infinite = is_infinite(commands, commands_len);

    if (infinite) printf("Command was infinite\n");
    else printf("Command wasn't infinite!!!\n");*/


    //printf("Command %d was invoked a second time, accumulator was %llu\n", in_pt, accumulator);

}

bool is_infinite(command_t* cmds, uint32_t len, uint32_t *acc)
{
    bool already[MAX_COMMANDS] = { false };

    uint64_t accumulator = 0;
    uint32_t in_pt = 0;
    while (1)
    {
        if (!already[in_pt])
        {
            already[in_pt] = true;
            accumulator += do_command(cmds[in_pt], &in_pt);
            if (in_pt >= len)
            {
                *acc = accumulator;
                return 0;
            }
            //printf("Accumulator: %llu, in_pt: %d\n", accumulator, in_pt);
        }
        else
        {
            *acc = accumulator;
            return 1;
        }
    }
}

uint64_t do_command(command_t cmd, uint32_t* in_pt)
{
    uint64_t acc = 0;
    if (cmd.cmd == "acc")
    {
        acc += cmd.number;
        (*in_pt)++;
    }
    else if (cmd.cmd == "nop")
    {
        (*in_pt)++;
    }
    else if (cmd.cmd == "jmp")
    {
        (*in_pt) += cmd.number;
    }
    return acc;
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
