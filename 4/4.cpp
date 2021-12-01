// 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

//#define _CRT_SECURE_NO_WARNINGS

#define KEYWORDS 7


int main()
{
    std::string keywords[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
    size_t keywords_length = KEYWORDS;
    //while (!keywords[keywords_length].empty()) ++keywords_length;

    int valid = 0, invalid = 0;
    int passports = 0;

    std::string passport;
    std::string line;
    

    while (1)
    {
        std::getline(std::cin, line);
        passport = passport + " " + line;
        if (!line.length())
        {
            std::string helper = passport;
            char word_c[5]="\0", data_c[40]="\0";

            bool validdata[KEYWORDS] = { false };

            while (1)
            {
                sscanf(helper.c_str(), "%3s:%s ", word_c, data_c);
                std::string word = word_c;
                std::string data = data_c;
                printf("Keyword is: %s, with data: %s\n", word_c, data_c);
                helper.erase(0, word.length() + 1 + data.length() + 1);
                printf("Passport afterwards: %s\n", helper.c_str());
                printf("Passport length: %d\n", helper.length());

                if (word == "byr")
                {
                    int year = 0;
                    sscanf(data.c_str(), "%4d", &year);
                    if (year >= 1920 && year <= 2002) validdata[0] = true;
                }
                else if (word == "iyr")
                {
                    int year = 0;
                    sscanf(data.c_str(), "%4d", &year);
                    if (year >= 2010 && year <= 2020) validdata[1] = true;
                }
                else if (word == "eyr")
                {
                    int year = 0;
                    sscanf(data.c_str(), "%4d", &year);
                    if (year >= 2020 && year <= 2030) validdata[2] = true;
                }
                else if (word == "hgt")
                {
                    int height = 0;
                    char unit_c[3] = "\0";
                    sscanf(data.c_str(), "%4d%2s", &height, unit_c);
                    std::string unit = unit_c;
                    if (unit == "cm")
                    {
                        if(height >= 150 && height <= 193) validdata[3] = true;
                    }
                    else if (unit == "in")
                    {
                        if (height >= 59 && height <= 76) validdata[3] = true;
                    }
                }
                else if (word == "hcl")
                {
                    if (data[0] == '#' && data.length() == 7)
                    {
                        bool ok = true;
                        for (uint8_t i = 1;i < 7;i++)
                        {
                            if (!((data[i] >= '0' && data[i] <= '9') || (data[i] >= 'a' && data[i] <= 'f'))) ok = false;
                        }
                        if(ok) validdata[4] = true;
                    }
                }
                else if (word == "ecl")
                {
                    if(data == "amb" || data == "blu" || data == "brn" || data == "gry" || data == "grn" || data == "hzl" || data == "oth") validdata[5] = true;
                }
                else if (word == "pid")
                {
                    if (data.length() == 9)
                    {
                        int id = 0;
                        sscanf(data.c_str(), "%9d", &id);
                        if(id >= 0 && id < 1E10)  validdata[6] = true;
                    }
                }



                if (helper.length() <= 1) break;
            }


            int counter = 0;
            for (uint16_t i = 0;i < keywords_length; i++)
            {
                if (passport.find(keywords[i]) != std::string::npos)
                {
                    counter++;
                }
            }
            printf("Counter = %d\n", counter);
            printf("Length = %d\n", keywords_length);
            if (counter == keywords_length)
            {
                bool ok = true;
                for (uint8_t i = 0;i < KEYWORDS;i++)
                {
                    if (!validdata[i]) ok = false;
                }
                if (ok)
                {
                    printf("All keywords found, passport valid\n");
                    valid++;
                }
                else invalid++;
            }
            else invalid++;
            passport = "\0";
            line = "\0";
            passports++;
        }
        else if (line[0] == '.') break;
    }

    printf("\n\nChecked %d passports. %d are valid, %d are invalid\n\n", passports, valid, invalid);

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
