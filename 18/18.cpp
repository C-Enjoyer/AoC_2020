// 18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

uint64_t solve(string*);
uint64_t solve2(string*);
string replace_equ(string, int, int, uint64_t);
int find_open_bracket(string, int, int);

int main()
{
    uint64_t sum = 0;
    while (1)
    {
        string line;
        getline(cin, line);
        if (line.length())
        {
            uint64_t sum_part = solve2(&line);
            sum += sum_part;
            printf("Sum is %llu\n", sum_part);
        }
        else break;
    }

    printf("Answer is %llu\n", sum);
}

uint64_t solve(string *line)
{
    int first_bracket = line->find('(');
    int first_plus = line->find('+');
    int first_mult = line->find('*');
    bool is_wobrackets = (first_bracket == -1) ? (true) : (false);
    bool is_woplus = (first_plus == -1) ? (true) : (false);
    bool is_womult = (first_mult == -1) ? (true) : (false);
    
    if (!is_wobrackets) //brackets 
    {
        int cnt_open = 0;
        int cnt_close = 0;
        int cnt = 0;
        
        for (int i=0;i<line->length();i++)
        {
            string helper = line->substr(i, 1);
            char c = helper[0];
            if (c == '(') cnt_open++;
            else if (c == ')') cnt_close++;

            if (cnt_open == cnt_close && cnt_open)
            {
                int inner_open = 0, inner_close = 0;
                //inner_open = line->rfind('(', i);
                inner_open = find_open_bracket(*line, i, cnt_open);
                inner_close = line->find(')');

                string help = line->substr(inner_open + 1, inner_close - inner_open - 1);

                uint64_t res = solve(&help);

                *line = replace_equ(*line, inner_open, inner_close+1, res);

                cnt_open = 0;
                cnt_close = 0;
                i = -1;
            }
        }

        return solve(line);
    }
    else //no more brackets
    {
        uint64_t result = 0;
        while (1)
        {
            int next_plus = line->find('+');
            int next_mult = line->find('*');
            if (next_plus == -1 && next_mult == -1) break; // no more signs

            if (next_plus == -1) next_plus = line->length() + 1;
            if (next_mult == -1) next_mult = line->length() + 1;

            int next_sign = (next_mult > next_plus) ? (next_plus) : (next_mult);
            bool is_plus = (next_mult > next_plus) ? (true) : (false);


            uint64_t left = 0, right = 0, partsum = 0;

            sscanf(line->substr(0, next_sign - 1).c_str(), "%llu", &left);

            int right_operator_mult = line->find('*', next_sign + 1);
            int right_operator_plus = line->find('+', next_sign + 1);

            if (right_operator_mult == -1) right_operator_mult = line->length() + 1;
            if (right_operator_plus == -1) right_operator_plus = line->length() + 1;
            int right_operator = (right_operator_mult > right_operator_plus) ? (right_operator_plus) : (right_operator_mult);

            sscanf(line->substr(next_sign + 2, right_operator - next_sign - 3).c_str(), "%llu", &right);
            int right_end = next_sign + 2 + (right_operator - next_sign - 3);
            result = (is_plus) ? (left + right) : (left * right);
            *line = replace_equ(*line, 0, right_end, result);
        }
        return result;
    }

    return 0;
}

uint64_t solve2(string* line)
{
    int first_bracket = line->find('(');
    int first_plus = line->find('+');
    int first_mult = line->find('*');
    bool is_wobrackets = (first_bracket == -1) ? (true) : (false);
    bool is_woplus = (first_plus == -1) ? (true) : (false);
    bool is_womult = (first_mult == -1) ? (true) : (false);

    if (!is_wobrackets) //brackets 
    {
        int cnt_open = 0;
        int cnt_close = 0;
        int cnt = 0;

        for (int i = 0;i < line->length();i++)
        {
            string helper = line->substr(i, 1);
            char c = helper[0];
            if (c == '(') cnt_open++;
            else if (c == ')') cnt_close++;

            if (cnt_open == cnt_close && cnt_open)
            {
                int inner_open = 0, inner_close = 0;
                //inner_open = line->rfind('(', i);
                inner_open = find_open_bracket(*line, i, cnt_open);
                inner_close = line->find(')');

                string help = line->substr(inner_open + 1, inner_close - inner_open - 1);

                uint64_t res = solve2(&help);

                *line = replace_equ(*line, inner_open, inner_close + 1, res);

                cnt_open = 0;
                cnt_close = 0;
                i = -1;
            }
        }

        return solve2(line);
    }
    else //no more brackets
    {
        if (!is_woplus)//plus
        {
            while (1)
            {
                int plus = line->find('+');
                if (plus != -1)
                {
                    uint64_t left = 0, right = 0, partsum = 0;

                    int left_operator = line->rfind('*', plus);
                    if (left_operator == -1) left_operator = 0; // in case there is none
                    else left_operator += 2; // from operator to number
                    sscanf(line->substr(left_operator, plus - left_operator - 1).c_str(), "%llu", &left);

                    int right_operator_mult = line->find('*', plus);
                    int right_operator_plus = line->find('+', plus + 1);

                    if (right_operator_mult == -1) right_operator_mult = line->length() + 1;
                    if (right_operator_plus == -1) right_operator_plus = line->length() + 1;
                    int right_operator = (right_operator_mult > right_operator_plus) ? (right_operator_plus) : (right_operator_mult);

                    sscanf(line->substr(plus + 2, right_operator - plus - 3).c_str(), "%llu", &right);
                    int right_end = plus + 2 + (right_operator - plus - 3);
                    *line = replace_equ(*line, left_operator, right_end, left + right);
                }
                else break;
            }

            //printf("No more +'s\n");
            //printf("Leftover: %s\n", line->c_str());
        }

        if (is_womult) // no mults left
        {
            return stoi(*line);
        }
        else //mults left
        {
            uint64_t part_solution = 0;
            while (1)
            {
                int mult = line->find('*');
                if (mult != -1)
                {
                    uint64_t left = 0, right = 0, partsum = 0;

                    int left_operator = 0;
                    sscanf(line->substr(left_operator, mult - left_operator - 1).c_str(), "%llu", &left);

                    int right_operator = line->find('*', mult + 1);
                    if (right_operator == -1) right_operator = line->length() + 1;
                    sscanf(line->substr(mult + 2, right_operator - mult - 3).c_str(), "%llu", &right);

                    int right_end = mult + 2 + (right_operator - mult - 3);
                    part_solution = left * right;
                    *line = replace_equ(*line, left_operator, right_end, part_solution);

                }
                else break;
            }

            //printf("END!!! Solution is %llu\n", solution);
            return part_solution;
        }
    }

    return 0;
}

string replace_equ(string line, int startpos, int endpos, uint64_t result)
{
    string partsum_s = to_string(result);

    string res_str = line;

    res_str.erase(startpos, endpos - startpos);

    res_str.insert(startpos, partsum_s);
    return res_str;
}

int find_open_bracket(string line, int init_last, int bracket_cnt)
{
    int app_cnt = 0;
    for (int i = init_last;i > -1;i--)
    {
        if (line[i] == '(')
        {
            app_cnt++;
            if (app_cnt >= bracket_cnt - 1) return i;
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
