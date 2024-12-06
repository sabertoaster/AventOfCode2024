// https://github.com/p1neapplechoco/advent_of_code_2024/blob/main/day_5/day5.cpp
// mr senpai 

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void readFile(string, vector<vector<int>> &, int **&);

int part1();
int part2();

int main()
{
    // cout << part1();
    cout << part2();
}

void readFile(string filename, vector<vector<int>> &page_numbers, int **&rules)
{
    ifstream input(filename);
    string line;

    while (getline(input, line))
        if (line.empty())
            break;
        else
        {
            int first = stoi(line.substr(0, line.find('|')));
            int second = stoi(line.substr(line.find('|') + 1));
            rules[first][second]++;
        }

    while (getline(input, line))
    {
        vector<int> page;
        int i = 0;
        string tmp;

        while (i < line.size())
        {
            if (line[i] == ',')
            {
                page.push_back(stoi(tmp));
                tmp.clear();
            }
            else
                tmp += line[i];
            i++;
        }

        page.push_back(stoi(tmp));
        tmp.clear();

        page_numbers.push_back(page);
    }
    input.close();
    return;
}

int checkPart1(vector<int> &page, int **&rules)
{
    for (int i = 1; i < page.size(); i++)
        if (!rules[page[i - 1]][page[i]])
            return 0;
    return page[page.size() / 2];
}

int part1()
{
    int res = 0;
    int **rules = new int *[100]{};

    for (int i = 0; i < 100; i++)
        rules[i] = new int[100]{};

    vector<vector<int>> page_numbers;

    readFile("input.txt", page_numbers, rules);

    for (vector<int> &page : page_numbers)
        res += checkPart1(page, rules);

    delete[] rules;
    return res;
}

int checkPart2(vector<int> &page, int **&rules)
{

    if (checkPart1(page, rules))
        return 0;

    int n = page.size();

    // for (int &e : page)
    //     cout << e << " ";
    // cout << endl;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rules[page[i]][page[j]])
                swap(page[i], page[j]);

    for (int i = 0; i < n / 2; i++)
        swap(page[i], page[n - i - 1]);

    // for (int &e : page)
    //     cout << e << " ";
    // cout << endl;

    return page[n / 2];
}

int part2()
{
    int res = 0;
    int **rules = new int *[100]{};

    for (int i = 0; i < 100; i++)
        rules[i] = new int[100]{};

    vector<vector<int>> page_numbers;

    readFile("input.txt", page_numbers, rules);

    for (vector<int> &page : page_numbers)
        res += checkPart2(page, rules);

    delete[] rules;
    return res;
}
